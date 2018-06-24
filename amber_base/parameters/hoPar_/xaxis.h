#ifndef XAXIS_H
#define XAXIS_H
#include <QDebug>
#include "amber_base/parameters/hoPar_/keys.h"
#include "amber_base/parameters/base_/ambernumber.h"

// 1-way conversion FROM Column, see Column for methods

class XAxis : public AmberNumber
{
public:
    XAxis() : AmberNumber(256, true, 0, 512){
    }

    XAxis(AmberNumber value) : AmberNumber(256, true, 0, 512){
        m_value = value;
    }

    XAxis(const int &value) : AmberNumber(256, true, 0, 512){
        m_value = value;
    }
};

#endif // XAXIS_H
