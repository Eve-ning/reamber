#include "include/io/outputeho.h"

OutputEHO::OutputEHO(QWidget *parent) : OutputHO(parent) {
    setTitle("output");
    setPlaceholderText("Editor Hit Object Output");
    hideKeyWidget();
}
OutputEHO::~OutputEHO() {}

QVector<double> OutputEHO::readOffsets(bool makeUnique) const {
    return QVector<double>();
}
