#ifndef SLIDERVELOCITY_H
#define SLIDERVELOCITY_H
#include "amber_base/parameters/tpPar_/timecode.h"
#include "amber_base/parameters/base_/ambernumber.h"

class SliderVelocity : public TimeCode
{
public:
    SliderVelocity() : TimeCode(1.0, false, 0.1, 10.0){
    }

    SliderVelocity(AmberNumber value) : TimeCode(1.0, false, 0.1, 10.0){
        m_value = value;
    }

    SliderVelocity(const double &value) : TimeCode(1.0, false, 0.1, 10.0){
        m_value = value;
    }

    SliderVelocity(const TimeCode &value) : TimeCode(1.0, false, 0.1, 10.0){
        if (m_value != 0)
        {
            m_value = SV_CONV / value.value();
        } else {
            qDebug() << "SV triggered DivByZero";
        }
    }

    bool isBPM(){
        return false;
    }
    bool isSV(){
        return true;
    }

    operator QString() const{
        return QString::number(SV_CONV / m_value);
    }

    static constexpr double SV_CONV = -100.0;
};

#endif // SLIDERVELOCITY_H
