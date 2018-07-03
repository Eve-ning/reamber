#ifndef TIMECODE_H
#define TIMECODE_H
#include "amber_base/parameters/base_/ambernumber.h"

// TimeCode is the term for the 2nd Parameter in the TimingPoint Code
// This handles the conversion from number to BPM or SV

// 1-way conversion FROM BPM or SliderVelocity, see respective classes for methods

class TimeCode : public AmberNumber
{
public:

    TimeCode(double value,
             bool forceInt = false,
             double clampMin = INT_MIN,
             double clampMax = INT_MAX) : AmberNumber(value, forceInt, clampMin, clampMax){
    }

    virtual ~TimeCode(){
    }

    virtual bool isBPM() = 0;
    virtual bool isSV() = 0;

// We make this virtual

//    TimeCode() : AmberNumber(-100.0, false){

//    }

//    TimeCode(AmberNumber value) : AmberNumber(-100.0, false){
//        m_value = value;
//    }

//    TimeCode(const double &value) : AmberNumber(-100.0, false){
//        m_value = value;
//    }

private:
    bool m_isBPM;

};
#endif // TIMECODE_H
