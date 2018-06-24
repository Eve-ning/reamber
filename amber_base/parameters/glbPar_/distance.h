#ifndef DISTANCE_H
#define DISTANCE_H
#include "amber_base/parameters/glbPar_/offset.h"
#include "amber_base/parameters/tpPar_/bpm.h"
#include "amber_base/parameters/tpPar_/slidervelocity.h"
#include "amber_base/parameters/base_/ambernumber.h"

/* Distance is defined as
 * Offset <as length> x Slider Velocity
 * Offset <as length> x BPM
 */

class Distance : public AmberNumber
{
public:
    Distance() : AmberNumber(0, false){
    }

    Distance(const double &value) : AmberNumber(0, false){
        m_value = value;
    }

    Distance(AmberNumber value) : AmberNumber(0, false){
        m_value = value;
    }

    Distance(const Offset &offset_, const SliderVelocity &SV_) : AmberNumber(0, false){
        m_value = offset_.value() * SV_.value();
    }

    Distance(const Offset &offset_, const BPM &BPM_) : AmberNumber(0, false){
        m_value = offset_.value() * BPM_.value();
    }

    Distance(const Offset &offset_, const double &value_) : AmberNumber(0, false){
        m_value = offset_.value() * value_;
    }


};

#endif // DISTANCE_H
