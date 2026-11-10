#pragma once

#include <qpoint.h>
#include <qlist.h>
#include <kritabrush_export.h>
#include <QString>
#include <qvector2d.h>

class BRUSH_EXPORT HAuthAction
{
public:

    //Stroke points are stored in screenspace coords
    QList<QVector2D> strokePoints;

    // Stroke points as percentage of the image being edited in X,Y coordinates in 0-1 
    QList<QVector2D> strokePointsCanvasspace; 

    long long strokeEndTimestamp;

    QString toString();
};