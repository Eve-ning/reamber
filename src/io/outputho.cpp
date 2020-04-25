#include "include/io/outputho.h"
#include "object/multiple/hitobjectv.h"

OutputHO::OutputHO(QWidget *parent) : IO(parent) {
    setTitle("Output");
    setPlaceholderText("Hit Object Output");
    hideKeyWidget();
}
OutputHO::~OutputHO() {}
void OutputHO::write(const HitObjectV &hoV) {
    textWidget()->setPlainText(hoV.getStringRaw("\n"));
}

QVector<double> OutputHO::readOffsets(bool makeUnique) const {
    return HitObjectV(toPlainText()).getOffsetV(makeUnique);
}
