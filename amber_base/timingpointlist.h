#ifndef TimingPointLIST_H
#define TimingPointLIST_H
#include "amber_base/obj_impl/timingpointlist_impl.h"

class TimingPointList : public TimingPointList_impl
{
public:
    // CONSTRUCTORS
    TimingPointList()                          ;
    TimingPointList(QList<TimingPoint> newTimingPointList);
    TimingPointList(QTextBrowser *tb)          ;
    TimingPointList(QLineEdit *line)           ;
    TimingPointList(QPlainTextEdit *pte)       ;
    TimingPointList(QString str)               ;
    TimingPointList(QStringList strList)       ;


};

#endif // TimingPointLIST_H
