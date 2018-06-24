#include "amber_base/validity/AmberException.h"

void AmberException::assertIndex(const int &value, const int &max)
{
    if (value > max)
    {
        AmberException(AmberException::INDEX_OUT_OF_RANGE,
             QString("Given: %1\n"
             "(Inclusive)\n"
             "Maximum : %2")
             .arg(value)
             .arg(max));
    }
}

void AmberException::assertLengthMatch(const int &given, const int &expected)
{
    if (given != expected)
    {
        AmberException(AmberException::LENGTH_MISMATCH,
             QString("Length Mismatch: (Given: %1) (Expected: %2)")
             .arg(given)
             .arg(expected));
        return;
    }
}
