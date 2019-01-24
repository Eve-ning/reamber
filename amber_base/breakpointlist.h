#ifndef cOM_BreakPLIST_H
#define cOM_BreakPLIST_H

#include "breakpoint.h"
#include <QList>
#include <QDebug>

class BreakPointList
{
public:

    // CONSTRUCTORS
    BreakPointList();
    BreakPointList(QList<BreakPoint> newBreakPointList);

    // LOADERS
    void loadBreakPList(QList<BreakPoint> newBreakPointList);

    // SETTERS

    // GETTERS
    QList<double> getStartList () const;
    QList<double> getEndList   () const;
    QList<double> getLengthList() const;
    int           getSize      () const { return curBreakPointList.size(); }

    // OPERS
    BreakPoint   operator [](int i) const;
    BreakPoint & operator [](int i);

    // SORTING

    // MISC
    void append(BreakPoint newOM_BreakP){ curBreakPointList.append(newOM_BreakP); }
    void deleteIndex(int index)         { curBreakPointList.removeAt(index); }

protected:
    QList<BreakPoint> curBreakPointList;
};

#endif // cOM_BreakPLIST_H
