#include "include/io/outputeho.h"

OutputEHO::OutputEHO(QWidget *parent) : OutputHO(parent) {
    setTitle("Output");
    setPlaceholderText("Editor Hit Object Output");
    hideKeyWidget();
}
OutputEHO::~OutputEHO() {}

QVector<double> OutputEHO::readOffsets(bool makeUnique) const
{
    Q_UNUSED(makeUnique); // To be used next time.
    return QVector<double>();
}
