#ifndef BPM_H
#define BPM_H
#include "amber_base/parameters/base_/ambernumber.h"
#include "amber_base/parameters/tpPar_/timecode.h"

class BPM : public TimeCode
{
public:
    BPM() : TimeCode(120.0, false, 0.0000000001, INT_MAX){
    }

    BPM(const double &value) : TimeCode(120.0, false, 0.0000000001, INT_MAX){
        m_value = value;
    }

    BPM(AmberNumber value) : TimeCode(120.0, false, 0.0000000001, INT_MAX){
        m_value = value;
    }

    BPM(const TimeCode &value) : TimeCode(120.0, false, 0.0000000001, INT_MAX){
        m_value = BPM_CONV / value.value();
    }

    bool isBPM(){
        return true;
    }
    bool isSV(){
        return false;
    }

    operator QString() const{
        return QString::number(BPM_CONV / m_value);
    }

    static constexpr double BPM_CONV = 60000.0;
};
#endif // BPM_H
