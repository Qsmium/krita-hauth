#include "HAuthAction.h"
#include <qvector2d.h>
#include <qdatastream.h>

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

QByteArray HAuthAction::HAuthListToByteArray(QList<HAuthAction> hauthList)
{
    QByteArray returnArray;
    
    // Go through array
    // First we save the length of the array. I.e how many HAuthActions there are in the entire list
    returnArray.append(hauthList.count());

    // Then we go through each array and do the same there
    for (HAuthAction &action : hauthList) {
        // Save the timestamp of the action

        returnArray.append(reinterpret_cast<const char *>(&action.strokeEndTimestamp),
                           sizeof(action.strokeEndTimestamp));

        // Then save the length of the action arrays
        returnArray.append(action.strokePoints.count());

        // Then we save the actual action arrays
        for (int i = 0; i < action.strokePoints.count(); i++) 
        {
            QVector2D vec = action.strokePoints[i];
            returnArray.append(reinterpret_cast<const char *>(&vec), sizeof(vec));
        }

        for (int i = 0; i < action.strokePoints.count(); i++) 
        {
            QVector2D vec = action.strokePointsCanvasspace[i];
            returnArray.append(reinterpret_cast<const char *>(&vec), sizeof(vec));
        }
    }

    return returnArray;
}

QList<HAuthAction> HAuthAction::HAuthListFromByteArray(QByteArray *byteArray)
{
    //Construct the QList
    QList<HAuthAction> returnList;

    //We just the the same operation as the saving into byte array but reversed
    //First we get the amount of indices that are in the top level qlist
    int listCount = byteArray->at(0);

    //Then go through the list with the list count
    //During the time that we go through the list we keep count of what index we're at
    int byteArrayIndex = sizeof(listCount);
    for (int i = 0; i < listCount; i++)
    {
        //Construct new HAuthAction
        HAuthAction authAct;

        //Grab timestamp
        long long strokeEndTimestamp = 0;
        std::memcpy(&strokeEndTimestamp, byteArray->constData() + byteArrayIndex, sizeof(strokeEndTimestamp));
        authAct.strokeEndTimestamp = strokeEndTimestamp;
        byteArrayIndex += sizeof(strokeEndTimestamp);

        //Grab the action arrays
        int actionArrayLength = byteArray->at(byteArrayIndex);
        byteArrayIndex += sizeof(actionArrayLength);

        //Construct arrays
        QList<QVector2D> globalPosArray;
        QList<QVector2D> canvasPosArray;

        for (int k = 0; k < actionArrayLength; k++)
        {
            QVector2D strokePos;
            std::memcpy(&strokePos, byteArray->constData() + byteArrayIndex, sizeof(strokePos));
            byteArrayIndex += sizeof(strokePos);

            //Attach stroke pos to constructed arrays
            globalPosArray.append(strokePos);
        }

        for (int k = 0; k < actionArrayLength; k++) 
        {
            QVector2D strokePos;
            std::memcpy(&strokePos, byteArray->constData() + byteArrayIndex, sizeof(strokePos));
            byteArrayIndex += sizeof(strokePos);

            // Attach stroke pos to constructed arrays
            canvasPosArray.append(strokePos);
        }

        //Attach array to new HAuth
        authAct.strokePoints = globalPosArray;
        authAct.strokePointsCanvasspace = canvasPosArray;

        //Attach Hauth
        returnList.append(authAct);
    }

    return returnList;
}