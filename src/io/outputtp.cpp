#include "include/io/outputtp.h"
#include "object/multiple/timingpointv.h"

OutputTP::OutputTP(QWidget *parent) : IO(parent) {
    setTitle("Output");
    setPlaceholderText("Timing Point Output");
    hideKeyWidget();
}
OutputTP::~OutputTP() {}
void OutputTP::write(const TimingPointV &tpV) {
    textWidget()->setPlainText(tpV.getStringRaw("\n"));
}

QVector<double> OutputTP::readOffsets(bool makeUnique) const {
    return TimingPointV(toPlainText()).getOffsetV(makeUnique);
}
