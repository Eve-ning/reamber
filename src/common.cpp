#include "common.h"
#include <QVector>
#include <QVector2D>

const QColor  Common::Color::GREEN             = QColor(100,250,100);
const QColor  Common::ColorFade::GREEN         = QColor(100,250,100,90);
const QString Common::ColorStyleSheet::GREEN   = QString("color:rgb(100,250,100);");
const QColor  Common::Color::RED               = QColor(220,0,80);
const QColor  Common::ColorFade::RED           = QColor(220,0,80,90);
const QString Common::ColorStyleSheet::RED     = QString("color:rgb(220,0,80);");
const QColor  Common::Color::GREY              = QColor(125,125,125);
const QColor  Common::ColorFade::GREY          = QColor(125,125,125,90);
const QString Common::ColorStyleSheet::GREY    = QString("color:rgb(125,125,125);");
const QColor  Common::Color::BLUE              = QColor(0,200,240);
const QColor  Common::ColorFade::BLUE          = QColor(0,200,240,90);
const QString Common::ColorStyleSheet::BLUE    = QString("color:rgb(0,150,240);");
const QColor  Common::Color::BLACK             = QColor(0,0,0);
const QString Common::ColorStyleSheet::BLACK   = QString("color:rgb(0,0,0);");
const QColor  Common::Color::WHITE             = QColor(255,255,255);
const QString Common::ColorStyleSheet::WHITE   = QString("color:rgb(255,255,255);");
const QColor  Common::Color::PURPLE            = QColor(200,20,240);
const QColor  Common::ColorFade::PURPLE        = QColor(200,20,240,90);
const QString Common::ColorStyleSheet::PURPLE  = QString("color:rgb(200,20,240);");

const QString Common::Suffix::SV     = QString(" (SV)");
const QString Common::Suffix::BPM    = QString(" (BPM)");
const QString Common::Suffix::OFFSET = QString("ms");

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
    for(double value : valueV) output.push_back(clipValue(value, isBpm));
    return output;
}

QVector<QVector2D> Common::sortByX(QVector<QVector2D> v) {
    std::sort(v.begin(), v.end(), [](QVector2D a, QVector2D b){ return a.x() < b.x(); });
    return v;
}
