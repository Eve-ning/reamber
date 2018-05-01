#include "breakpoint.h"

// CONSTRUCTORS
BreakPoint::BreakPoint()
{
    startBreak = 0;
    endBreak   = 1;
}
BreakPoint::BreakPoint(QString newBreakPoint) : BreakPoint()
{
    loadBreakP(newBreakPoint);
}

// LOADERS
void BreakPoint::loadBreakP(QString newBreakPoint)
{
    QStringList BreakPList;

    BreakPList = newBreakPoint.split(",", QString::KeepEmptyParts);

    if (BreakPList.count() != 3) {
        qDebug() << ("Break Period Invalid");
        qDebug() << ("Input: " + newBreakPoint);
        BreakPoint();
    }

    startBreak = BreakPList[1].toDouble();
    endBreak   = BreakPList[2].toDouble();
}

// SETTERS

// GETTERS
void BreakPoint::getInfo() const
{
    qDebug() << ("[---- Break Info ----]");
    qDebug() << ("STARTBREAK : " + QString::number(startBreak));
    qDebug() << ("ENDBREAK   : " + QString::number(endBreak  ));
}

// OPERS

// SORTING

// MISC





