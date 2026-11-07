#include "HAuthAction.h"

QString HAuthAction::toString()
{
    QString outString = "";

    for (QPoint &meowPoint : strokePoints) 
    {
        outString += QString::number(meowPoint.x()) + "," + QString::number(meowPoint.y()) + ";";
    }

    return outString;
}