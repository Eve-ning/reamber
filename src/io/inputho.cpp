#include "include/io/inputho.h"
#include "object/multiple/hitobjectv.h"
#include <QLayout>
#include <QSpinBox>

InputHO::InputHO(QWidget *parent) : IO(parent) {
    setTitle("Input");
    setPlaceholderText("Hit Object Input");
}
InputHO::~InputHO() {}

HitObjectV InputHO::read() const {
    // Use lazy loading
    return HitObjectV(toPlainText(), key());
}

QVector<double> InputHO::readOffsets(bool makeUnique) const {
    return read().getOffsetV(makeUnique);
}

QVector<uint> InputHO::getColumns() const
{
    return read().getColumnV();
}
