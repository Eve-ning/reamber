#ifndef SAMPLESETINDEX_H
#define SAMPLESETINDEX_H
#include "amber_base/parameters/base_/ambernumber.h"

class SampleSetIndex : public AmberNumber
{
public:
    SampleSetIndex() : AmberNumber(0, true){
    }

    SampleSetIndex(const int &value) : AmberNumber(0, true){
        m_value = value;
    }

    SampleSetIndex(AmberNumber value) : AmberNumber(0, true){
        m_value = value;
    }
};


#endif // SAMPLESETINDEX_H
