#include "HAuthAction.h"
#include <qvector2d.h>

QString HAuthAction::toString()
{
    QString outString = "Timestamp:" + QString::number(strokeEndTimestamp) + ";SP:";

    for (QVector2D &meowPoint : strokePoints) 
    {
        outString += QString::number(meowPoint.x()) + "," + QString::number(meowPoint.y()) + ";";
    }

    outString += "SPC:";
    
    for (QVector2D &meowPoint : strokePointsCanvasspace) {
        outString += QString::number(meowPoint.x()) + "," + QString::number(meowPoint.y()) + ";";
    }

    return outString;
}