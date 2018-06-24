#include "amber_base/timingpointlist.h"

// CONSTRUCTORS
TimingPointList::TimingPointList() : TimingPointList_impl()
{
}
TimingPointList::TimingPointList(QList<TimingPoint> newTimingPointList)
    : TimingPointList()
{
    loadTPList(newTimingPointList);
}
TimingPointList::TimingPointList(QTextBrowser* tb)
    : TimingPointList()
{
    loadTPList(tb);
}
TimingPointList::TimingPointList(QLineEdit* line)
    : TimingPointList()
{
    loadTPList(line);
}
TimingPointList::TimingPointList(QPlainTextEdit* pte)
{
    loadTPList(pte);
}
TimingPointList::TimingPointList(QString str)
{
    loadTPList(str);
}
TimingPointList::TimingPointList(QStringList strList)
{
    loadTPList(strList);
}


