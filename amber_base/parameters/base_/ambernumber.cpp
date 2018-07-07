#include "ambernumber.h"

void AmberNumber::clamp(){
    if (m_value > m_clampMax){
        qDebug() << "Clamped value " << m_value << " --> " << m_clampMax;
        m_value = m_clampMax;
        return;
    } else if (m_value < m_clampMin){
        qDebug() << "Clamped value " << m_value << " --> " << m_clampMin;
        m_value = m_clampMin;
        return;
    }
}

void AmberNumber::floorVal(){
    if (m_forceInt)
    {
        m_value = floor(m_value);
    }
}

