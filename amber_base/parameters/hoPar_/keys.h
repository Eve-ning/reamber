#ifndef KEYS_H
#define KEYS_H
#include "amber_base/parameters/base_/ambernumber.h"

class Keys : public AmberNumber
{
public:
    Keys() : AmberNumber(1, true, 1, 18){
    }

    Keys(AmberNumber value) : AmberNumber(1, true, 1, 18){
        m_value = value;
    }

    Keys(const int &value) : AmberNumber(1, true, 1, 18){
        m_value = value;
    }
};

#endif // KEYS_H
