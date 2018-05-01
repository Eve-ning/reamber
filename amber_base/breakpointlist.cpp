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
    amberCommon::assertIndex(i, getSize() - 1);
    return curBreakPointList[i];
}
BreakPoint BreakPointList::operator [](int i) const {
    amberCommon::assertIndex(i, getSize() - 1);
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

