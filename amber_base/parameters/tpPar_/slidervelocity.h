#ifndef SLIDERVELOCITY_H
#define SLIDERVELOCITY_H
#include "amber_base/parameters/tpPar_/timecode.h"
#include "amber_base/parameters/base_/ambernumber.h"

class SliderVelocity : public AmberNumber
{
public:
    SliderVelocity() : AmberNumber(1.0, false, 0.1, 10.0){
    }

    SliderVelocity(AmberNumber value) : AmberNumber(1.0, false, 0.1, 10.0){
        m_value = value;
    }

    SliderVelocity(const double &value) : AmberNumber(1.0, false, 0.1, 10.0){
        m_value = value;
    }

    SliderVelocity(const TimeCode &value) : AmberNumber(1.0, false, 0.1, 10.0){
        if (m_value != 0)
        {
            m_value = SV_CONV / value.value();
        } else {
            qDebug() << "SV triggered DivByZero";
        }
    }

    TimeCode toTimeCode(){
        if (m_value != 0)
        {
            return TimeCode(SV_CONV / m_value);
        } else {
            qDebug() << "SV triggered DivByZero";
            return TimeCode(-100.0);
        }
    }

    operator TimeCode(){
        return toTimeCode();
    }

    static constexpr double SV_CONV = -100.0;
};

#endif // SLIDERVELOCITY_H
