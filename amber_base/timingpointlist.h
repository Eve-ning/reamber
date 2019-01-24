#ifndef TimingPointLIST_H
#define TimingPointLIST_H

#include <cstdlib>
#include "timingpoint.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QPlainTextEdit>

class  TimingPointList
{
public:
    // CONSTRUCTORS
    TimingPointList()                          ;
    TimingPointList(QList<TimingPoint> newTimingPointList);
    TimingPointList(QTextBrowser *tb)          ;
    TimingPointList(QLineEdit *line)           ;
    TimingPointList(QPlainTextEdit *pte)       ;
    TimingPointList(QString str)               ;
    TimingPointList(QStringList strList)       ;

    operator QStringList() const { return toString(); }

    // LOADERS
    void loadTPList(QList<TimingPoint>  newTimingPointList);
    void loadTPList(QTextBrowser   *tb);
    void loadTPList(QLineEdit      *line);
    void loadTPList(QPlainTextEdit *pte);
    void loadTPList(QString        &str);
    void loadTPList(QStringList    &str);

    // SETTERS
    void setOffsetList(QList<double> offsetList_);
    void setCodeList  (QList<double> codeList_);
    void setValueList (QList<double> valueList_);

    // Gets Info of set
    Info getInfo();

    // GETTERS
    QList<double> getOffsetList    (const Info &info = Info(true)) const;
    QList<double> getCodeList      (const Info &info = Info(true)) const;
    QList<double> getValueList     (const Info &info = Info(true)) const;
    QList<double> getLengthList    (const Info &info = Info(true)) const;
    QList<double> getDistanceList  (const Info &info = Info(true)) const;
    QList<double> getUnqOffsetList (const Info &info = Info(true)) const;

    TimingPointList splitByType (const Info &info) const; // Splits the whole set by ISBPM Value

    double getMinOffset  () const;
    double getMaxOffset  () const;
    double getMinValue   (const Info &info) const;
    double getMaxValue   (const Info &info) const;
    double getLength     () const;
    double getLength     (int index);
    int    getSize       (const Info &info = Info(true)) const;
    double getAverage    (const Info &info) const;
    double getDistance   (const Info &info) const;
    double getDistance   (int index);
    bool   getLoadFail   () const { return loadFail; }
    QStringList toString () const;

    // OPERS
    TimingPoint   operator [](int i) const;
    TimingPoint & operator [](int i);

    void multiplyValue  (const TimingPointList rhsTimingPointList, bool limitFlag = false);
    void divideValue    (const TimingPointList rhsTimingPointList, bool limitFlag = false);
    void addValue       (const TimingPointList rhsTimingPointList, bool limitFlag = false);
    void subtractValue  (const TimingPointList rhsTimingPointList, bool limitFlag = false);

    void multiplyValue  (const double rhsDouble, bool limitFlag = false);
    void divideValue    (const double rhsDouble, bool limitFlag = false);
    void addValue       (const double rhsDouble, bool limitFlag = false);
    void subtractValue  (const double rhsDouble, bool limitFlag = false);

    void multiplyOffset (const double rhsDouble, bool limitFlag = false);
    void divideOffset   (const double rhsDouble, bool limitFlag = false);
    void addOffset      (const double rhsDouble, bool limitFlag = false);
    void subtractOffset (const double rhsDouble, bool limitFlag = false);

    void zero(); // Shifts the whole set such that the first TimingPoint is 0.0ms

    // SORTING
    void sortOffset (const bool isAscending = true);

    // MISC
    void append     (TimingPoint timingPoint_) { timingPointList.append(timingPoint_); }
    void append     (TimingPointList timingPointList_);
    void deleteIndex(unsigned index) { timingPointList.removeAt(index); }
    bool isEmpty    () const;

    // LIMITS VALUES DEPENDING ON THEIR ISBPM VALUE
    void limitValues(double maxSV = TimingPoint::MAXIMUM_SV,
                     double minSV = TimingPoint::MINIMUM_SV,
                     double maxBPM = TimingPoint::MAXIMUM_BPM,
                     double minBPM = TimingPoint::MINIMUM_BPM);
    void limitOffset(double minOffset = Common::MINIMUM_OFFSET,
                     double maxOffset = Common::MAXIMUM_OFFSET);

    // ADJUSTS A TP SO THAT THE AVERAGE IS MET
    void adjustToAverage(double averageSV, int adjustIndex);

    // REMOVES TP THAT HAVE SIMILAR OFFSET
    void makeUnique();

    QList<int> indexList(Info &info); // Gets indexes of TimingPoint that match Info

protected:
    QList<TimingPoint> timingPointList;
    bool               loadFail;
};

#endif // TimingPointLIST_H
