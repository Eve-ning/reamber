#include "osuobject.h"

void osuObject::limitOffset(const double& minimum, const double& maximum)
{
    if (minimum > maximum)
    {
        AExc(AExc::GENERAL_ERROR,
            QString("Minimum is larger than Maximum: (%1 - %2)").arg(minimum).arg(maximum));
        return;
    }

    if (offset < minimum)
    {
        offset = minimum;
    }
    else if (offset > maximum)
    {
        offset = maximum;
    }
}

double osuObject::getOffset() const
{
    return offset;
}

void osuObject::setOffset(double value)
{
    offset = value;
}
