#include "amber_base/parameters/hoPar_/column.h"

void Column::setValue(const XAxis &xAxis_, const Keys &keys_){
    m_value = round(((xAxis_.value()) / 256.0 * keys_.value() - 1.0) / 2.0);
}

XAxis Column::toXAxis(const Keys &keys_) const
{
    return XAxis(round((m_value + 0.5) * 512.0 / keys_.value()));
}
