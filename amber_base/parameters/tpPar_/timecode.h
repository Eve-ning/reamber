#ifndef TIMECODE_H
#define TIMECODE_H
#include "amber_base/parameters/base_/ambernumber.h"

// TimeCode is the term for the 2nd Parameter in the TimingPoint Code
// This handles the conversion from number to BPM or SV

// 1-way conversion FROM BPM or SliderVelocity, see respective classes for methods

class TimeCode : public AmberNumber
{
public:
    TimeCode() : AmberNumber(-100.0, false){
    }

    TimeCode(AmberNumber value) : AmberNumber(-100.0, false){
        m_value = value;
    }

    TimeCode(const double &value) : AmberNumber(-100.0, false){
        m_value = value;
    }

};
#endif // TIMECODE_H
