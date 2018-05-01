#ifndef COM_BREAKP_H
#define COM_BREAKP_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include "common.h"

class BreakPoint
{
public:
    // CONSTRUCTORS
    BreakPoint();
    BreakPoint(QString newBreakPoint);

    // LOADERS
    void loadBreakP(QString newBreakPoint);

    // SETTERS
    void setStartBreak(double newStartBreak){ startBreak = newStartBreak; return; }
    void setEndBreak  (double newEndBreak  ){ endBreak   = newEndBreak  ; return; }

    // GETTERS
    void   getInfo() const;
    double getStartBreak() const { return startBreak; }
    double getEndBreak  () const { return endBreak;   }
    double getLength    () const { return endBreak - startBreak; }

    // OPERS

    // SORTING

    // MISC


protected:
    double startBreak,
           endBreak;

};

#endif // COM_BREAKP_H
