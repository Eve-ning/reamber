#ifndef COM_BREAKP_H
#define COM_BREAKP_H
#include <QDebug>
#include "amber_base/common.h"
#include "amber_base/validity/amberexception.h"
#include "amber_base/baseclass_inc.h"

class BreakPoint
{
public:
    // CONSTRUCTORS
    BreakPoint();
    BreakPoint(QString newBreakPoint);

    // LOADERS
    void loadBreakP(QString newBreakPoint);

    // SETTERS}
    void setStartBreak(double value_){ offset = value_; }
    void setEndBreak(double value_){ offsetEnd = value_; }
    void setLength  (double value_){ offsetEnd = value_ - double(offset); }

    // GETTERS
    void   getInfo() const;
    double getStartBreak() const { return offset; } // Alias for getOffset
    double getEndBreak  () const { return offsetEnd;}
    double getLength    () const { return double(offsetEnd) - double(offset); }

    QString toString() const;

protected:
    Offset offset;
    Offset offsetEnd;

};

#endif // COM_BREAKP_H
