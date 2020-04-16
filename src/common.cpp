#include "common.h"
#include <QVector>

double Common::clipValue(double value, bool isBpm) {
    if (isBpm) {
        value = value > BPM_MAX ? BPM_MAX : value;
        value = value < BPM_MIN ? BPM_MIN : value;
    } else {
        value = value > SV_MAX ? SV_MAX : value;
        value = value < SV_MIN ? SV_MIN : value;
    }

    return value;
}
QVector<double> Common::clipValueV(QVector<double> valueV, bool isBpm)
{
    QVector<double> output;
    output.reserve(valueV.size());
    for (double value : valueV) output.push_back(clipValue(value, isBpm));
    return output;
}

const QColor Common::Color::GREEN = QColor(15, 232, 0);
const QColor Common::Color::RED   = QColor(214, 0, 68);
const QColor Common::Color::GREY  = QColor(125, 125, 125);

const QString Common::Suffix::SV     = QString(" (SV)");
const QString Common::Suffix::BPM    = QString(" (BPM)");
const QString Common::Suffix::OFFSET = QString("ms");
