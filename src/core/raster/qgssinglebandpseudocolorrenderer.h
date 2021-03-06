/***************************************************************************
                         qgssinglebandpseudocolorrenderer.h
                         ----------------------------------
    begin                : January 2012
    copyright            : (C) 2012 by Marco Hugentobler
    email                : marco at sourcepole dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSSINGLEBANDPSEUDOCOLORRENDERER_H
#define QGSSINGLEBANDPSEUDOCOLORRENDERER_H

#include "qgscolorramp.h"
#include "qgscolorrampshader.h"
#include "qgsrasterrenderer.h"
#include "qgsrectangle.h"

class QDomElement;
class QgsRasterShader;

/** \ingroup core
  * Raster renderer pipe for single band pseudocolor.
  */
class CORE_EXPORT QgsSingleBandPseudoColorRenderer: public QgsRasterRenderer
{

  public:

    //! Note: takes ownership of QgsRasterShader
    QgsSingleBandPseudoColorRenderer( QgsRasterInterface* input, int band = -1, QgsRasterShader* shader = nullptr );
    ~QgsSingleBandPseudoColorRenderer();
    QgsSingleBandPseudoColorRenderer * clone() const override;

    static QgsRasterRenderer* create( const QDomElement& elem, QgsRasterInterface* input );

    QgsRasterBlock* block( int bandNo, const QgsRectangle & extent, int width, int height, QgsRasterBlockFeedback* feedback = nullptr ) override;

    //! Takes ownership of the shader
    void setShader( QgsRasterShader* shader );

    //! Returns the raster shader
    QgsRasterShader* shader() { return mShader; }

    //! @note available in python as constShader
    const QgsRasterShader* shader() const { return mShader; }

    /** Creates a color ramp shader
     * @param colorRamp vector color ramp
     * @param colorRampType type of color ramp shader
     * @param classificationMode classification mode
     * @param classes number of classes
     * @param clip clip out of range values
     * @param extent extent used in classification (only used in quantile mode)
     */
    void createShader( QgsColorRamp* colorRamp = nullptr, QgsColorRampShader::Type colorRampType  = QgsColorRampShader::Interpolated, QgsColorRampShader::ClassificationMode classificationMode = QgsColorRampShader::Continuous, int classes = 0, bool clip = false, const QgsRectangle& extent = QgsRectangle() );

    void writeXml( QDomDocument& doc, QDomElement& parentElem ) const override;

    void legendSymbologyItems( QList< QPair< QString, QColor > >& symbolItems ) const override;

    QList<int> usesBands() const override;

    /** Returns the band used by the renderer
     * @note added in QGIS 2.7
     */
    int band() const { return mBand; }

    /** Sets the band used by the renderer.
     * @see band
     * @note added in QGIS 2.10
     */
    void setBand( int bandNo );

    double classificationMin() const { return mClassificationMin; }
    double classificationMax() const { return mClassificationMax; }
    void setClassificationMin( double min );
    void setClassificationMax( double max );

  private:

    QgsRasterShader* mShader;
    int mBand;

    // Minimum and maximum values used for automatic classification, these
    // values are not used by renderer in rendering process
    double mClassificationMin;
    double mClassificationMax;

    QgsSingleBandPseudoColorRenderer( const QgsSingleBandPseudoColorRenderer& );
    const QgsSingleBandPseudoColorRenderer& operator=( const QgsSingleBandPseudoColorRenderer& );
};

#endif // QGSSINGLEBANDPSEUDOCOLORRENDERER_H
