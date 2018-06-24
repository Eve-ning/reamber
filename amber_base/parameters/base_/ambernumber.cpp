#include "ambernumber.h"

void AmberNumber::clamp(){
    if (m_value > m_clampMax){
        qDebug() << "Clamped value " << m_value << " --> " << m_clampMax << endl;
        m_value = m_clampMax;
        return;
    } else if (m_value < m_clampMin){
        qDebug() << "Clamped value " << m_value << " --> " << m_clampMin << endl;
        m_value = m_clampMin;
        return;
    }
}

void AmberNumber::force_floor(){
    if (m_forceInt)
    {
        m_value = floor(m_value);
    }
}
