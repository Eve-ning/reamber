#ifndef TIMINGPOINTLIST_IMPL_H
#define TIMINGPOINTLIST_IMPL_H

#include "amber_base/timingpoint.h"
#include <cstdlib>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPlainTextEdit>

class TimingPointList_impl
{
public:
    TimingPointList_impl();

    operator QStringList() const { return toString(); }

    // LOADERS
    void loadTPList(QList<TimingPoint> newTimingPointList_impl);
    void loadTPList(QTextBrowser   *tb);
    void loadTPList(QLineEdit      *line);
    void loadTPList(QPlainTextEdit *pte);
    void loadTPList(QString        &str);
    void loadTPList(QStringList    &strList);

    // SETTERS
    void setOffsetList(const QList<Offset> &offsetList_);
    void setCodeList  (const QList<std::shared_ptr<TimeCode> > &codeList_);
    void setValueList (const QList<double> &valueList_);
    void convertToBPM(const BPM &referenceValue);
    void convertToSV(const BPM &referenceValue);

    // GETTERS
    QList<Offset> getOffsetList    (const Info &info = Info(true)) const;
    QList<std::shared_ptr<TimeCode>> getCodeList(const Info &info = Info(true)) const;
    QList<double> getValueList     (const Info &info = Info(true)) const;
    QList<Offset> getLengthList    (const Info &info = Info(true)) const;
    QList<Distance> getDistanceList(const Info &info = Info(true)) const;
    QList<Offset> getUnqOffsetList (const Info &info = Info(true)) const;

    TimingPointList_impl splitByType (const Info &info) const; // Splits the whole set by ISBPM Value

    Offset getMinOffset  () const;
    Offset getMaxOffset  () const;
    double getMinValue   (const Info &info) const;
    double getMaxValue   (const Info &info) const;
    Offset getLength     () const;
    Offset getLength     (int index);
    int getSize          (const Info &info = Info(true)) const;
    double getAverage    (const Info &info) const;
    Distance getDistance (const Info &info) const;
    Distance getDistance (int index);
    bool getLoadFail   () const { return loadFail; }
    QStringList toString () const;

    // OPERS
    TimingPoint   operator [](int i) const;
    TimingPoint & operator [](int i);

    void multiplyValue  (const TimingPointList_impl rhsTimingPointList_impl);
    void divideValue    (const TimingPointList_impl rhsTimingPointList_impl);
    void addValue       (const TimingPointList_impl rhsTimingPointList_impl);
    void subtractValue  (const TimingPointList_impl rhsTimingPointList_impl);

    void multiplyValue  (const double rhsDouble);
    void divideValue    (const double rhsDouble);
    void addValue       (const double rhsDouble);
    void subtractValue  (const double rhsDouble);

    void multiplyOffset (const double rhsDouble);
    void divideOffset   (const double rhsDouble);
    void addOffset      (const double rhsDouble);
    void subtractOffset (const double rhsDouble);

    void zero(); // Shifts the whole set such that the first TimingPoint is 0.0ms

    // SORTING
    void sortOffset (const bool isAscending = true);

    // MISC
    void append     (TimingPoint timingPoint_){ timingPointList.append(timingPoint_); }
    void append     (TimingPointList_impl timingPointList_);
    void deleteIndex(unsigned index){ timingPointList.removeAt(index); }
    bool isEmpty    () const;
    void deleteList (){ timingPointList.clear(); }

    // ADJUSTS A TP SO THAT THE AVERAGE IS MET
    void adjustToAverage(SliderVelocity average, int adjustIndex);
    void adjustToAverage(BPM average, int adjustIndex);

    // REMOVES TP THAT HAVE SIMILAR OFFSET
    void makeUnique();

    QList<int> indexList(Info &info); // Gets indexes of TimingPoint that match Info

protected:
    QList<TimingPoint> timingPointList;
    bool               loadFail = false;
};

#endif // TimingPointList_impl_H
