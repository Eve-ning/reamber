#ifndef COMMON_H
#define COMMON_H

#include <QColor>


template <typename T>
class QVector;
class QVector2D;

class Common
{
public:
    // Squeezes the value to the defined MIN and MAX limits below and returns it
    static double clipValue(double value, bool is_bpm);
    static QVector<double> clipValueV(QVector<double> valueV, bool isBpm);
    static QVector<QVector2D> sortByX(QVector<QVector2D> v);

    // Define "global" variables
    constexpr static double SV_MIN = 0.01;
    constexpr static double SV_MAX = 10.0;
    constexpr static double SV_DEFAULT = 1.0;
    constexpr static double SV_STEPSIZE = 0.1;

    constexpr static double BPM_MIN = 0.01;
    constexpr static double BPM_MAX = 10000000.0; // 10,000,000
    constexpr static double BPM_DEFAULT = 120.0;
    constexpr static double BPM_STEPSIZE = 1.0;

    constexpr static double OFFSET_MIN = 0.0;
    constexpr static double OFFSET_MAX = 100000000.0; // 100,000,000
    constexpr static double OFFSET_DEFAULT = 0.0;
    constexpr static double OFFSET_INTERVAL_DEFAULT = 100.0;

    class Color {
    public:
        const static QColor GREEN ;
        const static QColor RED   ;
        const static QColor GREY  ;
        const static QColor BLUE  ;
        const static QColor PURPLE;
        const static QColor BLACK ;
    };
    class ColorStyleSheet {
    public:
        const static QString GREEN ;
        const static QString RED   ;
        const static QString GREY  ;
        const static QString BLUE  ;
        const static QString PURPLE;
        const static QString BLACK ;
    };

    class ColorFade {
    public:
        const static QColor GREEN ;
        const static QColor RED   ;
        const static QColor GREY  ;
        const static QColor BLUE  ;
        const static QColor PURPLE;
    };

    constexpr static long double MATH_PI = 3.14159265358979323846l;

    // This value is to convert vertical slider values to val
    constexpr static double VS_TO_VAL = 100.0;

    class Suffix {
    public:
        const static QString SV;
        const static QString BPM;
        const static QString OFFSET;
    };
};

#endif // COMMON_H
