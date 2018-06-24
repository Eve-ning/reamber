#ifndef YAXIS_H
#define YAXIS_H
#include "amber_base/parameters/base_/ambernumber.h"

class YAxis : public AmberNumber
{
public:
    YAxis() : AmberNumber(256, true, 0, 512){
    }

    YAxis(AmberNumber value) : AmberNumber(256, true, 0, 512){
        m_value = value;
    }

    YAxis(const int &value) : AmberNumber(256, true, 0, 512){
        m_value = value;
    }
};

#endif // YAXIS_H
