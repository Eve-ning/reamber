#ifndef COM_TP_H
#define COM_TP_H

#include "amber_base/obj_impl/timingpoint_impl.h"

class TimingPoint : public TimingPoint_impl {
public:
    // CONSTRUCTORS
    TimingPoint();
    TimingPoint(const QString &string_);
    TimingPoint(QLineEdit* line);
    TimingPoint(double offset_, double value_, bool isBPM_);

};

#endif // COM_TP_H
