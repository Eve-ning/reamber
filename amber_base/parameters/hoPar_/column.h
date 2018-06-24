#ifndef COLUMN_H
#define COLUMN_H
#include "amber_base/parameters/hoPar_/keys.h"
#include "amber_base/parameters/base_/ambernumber.h"
#include "amber_base/parameters/hoPar_/xaxis.h"

// 1-way conversion to XAxis Class

class Column : public AmberNumber
{
public:
    Column() : AmberNumber(0, true, 0, 17){
    }

    Column(XAxis xAxis_,
           Keys keys_,
           int minColumn = 0,
           int maxColumn = 17) : AmberNumber(0, true, 0, 17){
        setValue(xAxis_, keys_);
        setClamps(minColumn, maxColumn);
    }

    Column(AmberNumber value,
           int minColumn = 0,
           int maxColumn = 17) : AmberNumber(0, true, 0, 17){
        m_value = value;
        setClamps(minColumn, maxColumn);
    }

    Column(const int &value,
           int minColumn,
           int maxColumn) : AmberNumber(0, true, 0, 17){
        m_value = value;
        setClamps(minColumn, maxColumn);
    }

    XAxis toXAxis(const Keys &keys_) const;

    void setValue(const XAxis &xAxis_, const Keys &keys_);


};

#endif // COLUMN_H
