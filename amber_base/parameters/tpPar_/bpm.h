#ifndef BPM_H
#define BPM_H
#include "amber_base/parameters/base_/ambernumber.h"
#include "amber_base/parameters/tpPar_/timecode.h"

class BPM : public AmberNumber
{
public:
    BPM() : AmberNumber(120.0, false, 0.0000000001, INT_MAX){
    }

    BPM(const double &value) : AmberNumber(120.0, false, 0.0000000001, INT_MAX){
        m_value = value;
    }

    BPM(AmberNumber value) : AmberNumber(120.0, false, 0.0000000001, INT_MAX){
        m_value = value;
    }

    BPM(const TimeCode &value) : AmberNumber(120.0, false, 0.0000000001, INT_MAX){
        m_value = BPM_CONV / value.value();
    }

    TimeCode toTimeCode(){
        return TimeCode(BPM_CONV / m_value);
    }

    operator TimeCode() {
        return toTimeCode();
    }

    static constexpr double BPM_CONV = 60000.0;
};
#endif // BPM_H
