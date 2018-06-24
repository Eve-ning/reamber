#ifndef VOLUME_H
#define VOLUME_H
#include "amber_base/parameters/base_/ambernumber.h"

class Volume : public AmberNumber
{
public:
    Volume() : AmberNumber(20, true, 0, 100){
    }

    Volume(AmberNumber value) : AmberNumber(20, true, 0, 100){
        m_value = value;
    }

    Volume(const int &value) : AmberNumber(20, true, 0, 100){
        m_value = value;
    }
};
#endif // VOLUME_H
