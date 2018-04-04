#include "com_breakplist.h"

cOM_BreakPList::cOM_BreakPList()
{
    OM_BreakPList = {};
}

cOM_BreakPList::cOM_BreakPList(QList<cOM_BreakP> newOM_BreakPList) : cOM_BreakPList()
{
    loadBreakPList(newOM_BreakPList);
}

void cOM_BreakPList::loadBreakPList(QList<cOM_BreakP> newOM_BreakPList)
{
    OM_BreakPList = newOM_BreakPList;
}

cOM_BreakP &cOM_BreakPList::operator [](int i) {
    if (i < OM_BreakPList.count()){
        return OM_BreakPList[i];
    } else {
        qDebug() << "cOM_BreakP Index Does not Exist, returning first index." << "\r\n";
        return OM_BreakPList[0];
    }
}
cOM_BreakP cOM_BreakPList::operator [](int i) const {
    if (i < OM_BreakPList.count()){
        return OM_BreakPList[i];
    } else {
        qDebug() << "cOM_BreakP Index Does not Exist, returning default." << "\r\n";
        return cOM_BreakP();
    }
}

QList<double> cOM_BreakPList::getStartList() const
{
    cOM_BreakP OM_BreakP;
    QList<double> output;

    foreach (OM_BreakP, OM_BreakPList) {
        output.append(OM_BreakP.getStartBreak());
    }
    return output;
}
QList<double> cOM_BreakPList::getEndList() const
{
    cOM_BreakP OM_BreakP;
    QList<double> output;

    foreach (OM_BreakP, OM_BreakPList) {
        output.append(OM_BreakP.getEndBreak());
    }
    return output;
}
QList<double> cOM_BreakPList::getLengthList() const
{
    cOM_BreakP OM_BreakP;
    QList<double> output;

    foreach (OM_BreakP, OM_BreakPList) {
        output.append(OM_BreakP.getLength());
    }
    return output;
}

