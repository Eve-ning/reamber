#include "amber_base/timingpoint.h"

// CONSTRUCTORS
TimingPoint::TimingPoint():
    TimingPoint_impl()
{
}
TimingPoint::TimingPoint(const QString &string_)
    : TimingPoint()
{
    loadTP(string_);
}
TimingPoint::TimingPoint(QLineEdit* line)
    : TimingPoint()
{
    loadTP(line);
}
TimingPoint::TimingPoint(double offset_, double value_, bool isBPM_)
    : TimingPoint()
{
    loadTP(offset_, value_, isBPM_);
}


