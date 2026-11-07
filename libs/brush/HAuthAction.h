#pragma once

#include <qpoint.h>
#include <qlist.h>
#include <kritabrush_export.h>
#include <QString>

class BRUSH_EXPORT HAuthAction
{
public:
    QList<QPoint> strokePoints;

    QString toString();
};