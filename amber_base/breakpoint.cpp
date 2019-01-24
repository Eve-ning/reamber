#include "breakpoint.h"

// CONSTRUCTORS
BreakPoint::BreakPoint()
{
    offset = 0;
    length = 1;
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

    offset = BreakPList[1].toDouble();
    length = BreakPList[2].toDouble() - offset;
}

// SETTERS

// GETTERS
void BreakPoint::getInfo() const
{
    qDebug() << ("[---- Break Info ----]");
    qDebug() << ("STARTBREAK : " + QString::number(offset));
    qDebug() << ("ENDBREAK   : " + QString::number(length + offset));
}

QString BreakPoint::toString() const
{
    QString output;

    output = QString("2,") +
             QString::number(offset) +
             QString::number(offset + length);
    return output;
}

// OPERS

// SORTING

// MISC





