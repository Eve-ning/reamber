#include "include/io/inputtp.h"
#include "object/multiple/timingpointv.h"

InputTP::InputTP(QWidget *parent) : IO(parent) {
    setTitle("input");
    setPlaceholderText("Timing Point Input");
    hideKeyWidget();
}
InputTP::~InputTP() {}
TimingPointV InputTP::read() const {
    return TimingPointV(toPlainText());
}

QVector<double> InputTP::readOffsets(bool makeUnique) const {
    return TimingPointV(toPlainText()).getOffsetV(makeUnique);
}
