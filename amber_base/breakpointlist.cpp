#include "breakpointlist.h"

BreakPointList::BreakPointList()
{
    curBreakPointList = {};
}

BreakPointList::BreakPointList(QList<BreakPoint> newBreakPointList) : BreakPointList()
{
    loadBreakPList(newBreakPointList);
}

void BreakPointList::loadBreakPList(QList<BreakPoint> newBreakPointList)
{
    curBreakPointList = newBreakPointList;
}

BreakPoint &BreakPointList::operator [](int i) {
    if (i >= getSize())
    {
        AExc(AExc::INDEX_OUT_OF_RANGE,
             QString("Within BreakPointList\n"
                     "Access: %1\n"
                     "Last i: %2"           )
             .arg(i).arg(getSize() - 1));
        return *(new BreakPoint());
    }
    return curBreakPointList[i];
}
BreakPoint BreakPointList::operator [](int i) const {
    if (i >= getSize())
    {
        AExc(AExc::INDEX_OUT_OF_RANGE,
             QString("Within BreakPointList\n"
                     "Access: %1\n"
                     "Last i: %2"           )
             .arg(i).arg(getSize() - 1));
        return BreakPoint();
    }
    return curBreakPointList[i];
}

QList<double> BreakPointList::getStartList() const
{
    BreakPoint OM_BreakP;
    QList<double> output;

    foreach (OM_BreakP, curBreakPointList) {
        output.append(OM_BreakP.getStartBreak());
    }
    return output;
}
QList<double> BreakPointList::getEndList() const
{
    BreakPoint OM_BreakP;
    QList<double> output;

    foreach (OM_BreakP, curBreakPointList) {
        output.append(OM_BreakP.getEndBreak());
    }
    return output;
}
QList<double> BreakPointList::getLengthList() const
{
    BreakPoint OM_BreakP;
    QList<double> output;

    foreach (OM_BreakP, curBreakPointList) {
        output.append(OM_BreakP.getLength());
    }
    return output;
}

