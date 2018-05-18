#ifndef OSUOBJECT_H
#define OSUOBJECT_H
#include <QString>
#include "common.h"

/* osuObject acts as a base for all osu related objects:
 * HitObject, TimingPoint,   BreakPoint, etc.
 *
 * This class will handle:
 * Offset
 * Value
 */

class osuObject
{
public:
    osuObject(double offset_) : offset(offset_){}
    osuObject() : offset(0.0){}

    virtual ~osuObject(){}

    virtual bool operator <(const osuObject &rhs) const
    {
        return (offset < rhs.offset);
    }
    virtual bool operator >(const osuObject &rhs) const
    {
        return (offset > rhs.offset);
    }
    virtual bool operator <=(const osuObject &rhs) const
    {
        return (offset <= rhs.offset);
    }
    virtual bool operator >=(const osuObject &rhs) const
    {
        return (offset >= rhs.offset);
    }
    virtual bool operator ==(const osuObject &rhs) const
    {
        return (offset == rhs.offset);
    }
    virtual bool operator !=(const osuObject &rhs) const
    {
        return !(*this == rhs);
    }

    virtual osuObject &operator +=(const osuObject &rhs)
    {
        offset += rhs.offset;
        return *this;
    }
    virtual osuObject &operator +=(const double &rhs)
    {
        offset += rhs;
        return *this;
    }
    virtual osuObject &operator -=(const osuObject &rhs)
    {
        offset -= rhs.offset;
        return *this;
    }
    virtual osuObject &operator -=(const double &rhs)
    {
        offset -= rhs;
        return *this;
    }
    virtual osuObject &operator *=(const osuObject &rhs)
    {
        offset *= rhs.offset;
        return *this;
    }
    virtual osuObject &operator *=(const double &rhs)
    {
        offset *= rhs;
        return *this;
    }
    virtual osuObject &operator /=(const osuObject &rhs)
    {
        offset /= rhs.offset;
        return *this;
    }
    virtual osuObject &operator /=(const double &rhs)
    {
        offset /= rhs;
        return *this;
    }

    virtual osuObject &operator +(const osuObject &rhs)
    {
        offset += rhs.offset;
        return *this;
    }
    virtual osuObject &operator +(const double &rhs)
    {
        offset += rhs;
        return *this;
    }
    virtual osuObject &operator -(const osuObject &rhs)
    {
        offset -= rhs.offset;
        return *this;
    }
    virtual osuObject &operator -(const double &rhs)
    {
        offset -= rhs;
        return *this;
    }
    virtual osuObject &operator *(const osuObject &rhs)
    {
        offset *= rhs.offset;
        return *this;
    }
    virtual osuObject &operator *(const double &rhs)
    {
        offset *= rhs;
        return *this;
    }
    virtual osuObject &operator /(const osuObject &rhs)
    {
        offset /= rhs.offset;
        return *this;
    }
    virtual osuObject &operator /(const double &rhs)
    {
        offset /= rhs;
        return *this;
    }

    // All objects derived must eventually be converted to a QString
    virtual QString toString() const = 0;
    virtual void limitOffset(const double &minimum = MINIMUM_OFFSET,
                             const double &maximum = MAXIMUM_OFFSET);

    double getOffset() const;
    void setOffset(double value);

protected:
    static constexpr double MINIMUM_OFFSET = 0.0;
    static constexpr double MAXIMUM_OFFSET = 360000.0; // 1 hour in milliseconds
    double offset;
};

#endif // OSUOBJECT_H
