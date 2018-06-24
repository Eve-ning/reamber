#ifndef OFFSET_H
#define OFFSET_H
#include "amber_base/parameters/base_/ambernumber.h"

class Offset : public AmberNumber
{
public:
    Offset() : AmberNumber(0, false) {
    }

    Offset(AmberNumber value) : AmberNumber(0, false){
        m_value = value;
    }

    Offset(const double &value) : AmberNumber(0, false){
        m_value = value;
    }

};

#endif // OFFSET_H
