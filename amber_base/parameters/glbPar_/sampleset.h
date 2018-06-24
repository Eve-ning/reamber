#ifndef SAMPLESET_H
#define SAMPLESET_H
#include "amber_base/parameters/base_/ambernumber.h"

class SampleSet : public AmberNumber
{
public:

    enum SAMPLE_SET {
        AUTO = 0,
        NORMAL = 1,
        SOFT = 2,
        DRUM = 3
    };

    SampleSet() : AmberNumber(0, true, 0, 3) {
    }

    SampleSet(const SAMPLE_SET &value) : AmberNumber(0, true, 0, 3) {
        m_value = int(value);
    }

    SampleSet(const int &value) : AmberNumber(0, true, 0, 3) {
        m_value = value;
    }

    bool isAUTO(){
        return (m_value == SAMPLE_SET::AUTO);
    }
    bool isNORMAL(){
        return (m_value == SAMPLE_SET::NORMAL);
    }
    bool isSOFT(){
        return (m_value == SAMPLE_SET::SOFT);
    }
    bool isDRUM(){
        return (m_value == SAMPLE_SET::DRUM);
    }

    using AmberNumber::setValue;
    void setValue(const SAMPLE_SET &value){
        m_value = (int)value;
    }
};

#endif // SAMPLESET_H
