#include "amber_base/breakpoint.h"

// CONSTRUCTORS
BreakPoint::BreakPoint():
    offset(0),
    offsetEnd(1)
{ }
BreakPoint::BreakPoint(QString newBreakPoint) : BreakPoint()
{
    loadBreakP(newBreakPoint);
}

// LOADERS
void BreakPoint::loadBreakP(QString newBreakPoint)
{
    QStringList BreakPList;

    BreakPList = newBreakPoint.split(",", QString::KeepEmptyParts);

    if (BreakPList.count() != 3){
        qDebug() << ("Break Period Invalid");
        qDebug() << ("Input: " + newBreakPoint);
        BreakPoint();
    }

    offset = BreakPList[1].toDouble();
    offsetEnd = BreakPList[2].toDouble();
}

// SETTERS

// GETTERS
void BreakPoint::getInfo() const
{
    qDebug() << ("[---- Break Info ----]");
    qDebug() << ("STARTBREAK : " + QString(offset));
    qDebug() << ("ENDBREAK   : " + QString(offsetEnd));
}

QString BreakPoint::toString() const
{
    QString output;

    output = QString("2,") +
             QString(offset) +
             QString(offsetEnd);
    return output;
}

// OPERS

// SORTING

// MISC





