#ifndef COM_BREAKP_H
#define COM_BREAKP_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include "common.h"
#include "osuobject.h"

class BreakPoint : public osuObject
{
public:
    // CONSTRUCTORS
    BreakPoint();
    BreakPoint(QString newBreakPoint);

    // LOADERS
    void loadBreakP(QString newBreakPoint);

    // SETTERS}
    void setStartBreak(double startBreak){ offset = startBreak; } // Alias for setOffset
    void setEndBreak(double endBreak){ length = endBreak - offset; }
    void setLength  (double length_){ length = length_; }

    // GETTERS
    void   getInfo() const;
    double getStartBreak() const { return offset; } // Alias for getOffset
    double getEndBreak  () const { return offset + length;}
    double getLength    () const { return length; }

    QString toString() const;


protected:
    double length;

};

#endif // COM_BREAKP_H
