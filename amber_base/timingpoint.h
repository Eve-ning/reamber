#ifndef COM_TP_H
#define COM_TP_H

#include <QLineEdit>
#include "common.h"

class  TimingPoint
{
public:

    // CONSTRUCTORS
    TimingPoint();
    TimingPoint(QString string_);
    TimingPoint(QLineEdit *line);
    TimingPoint(double offset_, double value_, bool isBPM_);

    operator QString() const { return toString(); }

    // LOADERS
    void loadTP(QString TP);
    void loadTP(QLineEdit *line);
    void loadTP(double offset_, double value_, bool isBPM_);

    // SETTERS
    void setOffset        (double offset_        );
    void setCode          (double code_          ){ code           = code_          ; return; }
    void setMetronome     (int    metronome_     ){ metronome      = metronome_     ; return; }
    void setSampleSet     (int    sampleSet_     ){ sampleSet      = sampleSet_     ; return; }
    void setSampleSetIndex(int    sampleSetIndex_){ sampleSetIndex = sampleSetIndex_; return; }
    void setVolume        (int    volume_        ){ volume         = volume_        ; return; }
    void setIsBPM         (bool   isBPM_         ){ isBPM          = isBPM_         ; return; }
    void setIsSV          (bool   isSV_          ){ isBPM          = !isSV_         ; return; }
    void setIsKiai        (bool   isKiai_        ){ isKiai         = isKiai_        ; return; }
    void setValue         (double value_) ;

    // GETTERS
    void    getInfo          () const;
    double  getOffset        () const { return offset        ; }
    double  getCode          () const { return code          ; }
    int     getMetronome     () const { return metronome     ; }
    int     getSampleSet     () const { return sampleSet     ; }
    int     getSampleSetIndex() const { return sampleSetIndex; }
    int     getVolume        () const { return volume        ; }
    bool    getIsBPM         () const { return isBPM         ; }
    bool    getIsSV          () const { return !isBPM        ; }
    bool    getIsKiai        () const { return isKiai        ; }
    bool    getLoadFail      () const { return loadFail; }
    double  getValue         () const;
    QString toString         () const;

    // OPERS
    bool operator <(TimingPoint *curTP) { return offset < curTP->getOffset(); }
    bool operator >(TimingPoint *curTP) { return offset > curTP->getOffset(); }
    bool operator <(TimingPoint  curTP) { return offset < curTP.getOffset(); }
    bool operator >(TimingPoint  curTP) { return offset > curTP.getOffset(); }

    void multiplyValue  (const TimingPoint rhsTimingPoint, bool limitFlag = false);
    void divideValue    (const TimingPoint rhsTimingPoint, bool limitFlag = false);
    void addValue       (const TimingPoint rhsTimingPoint, bool limitFlag = false);
    void subtractValue  (const TimingPoint rhsTimingPoint, bool limitFlag = false);

    void multiplyValue  (const double rhsDouble, bool limitFlag = false);
    void divideValue    (const double rhsDouble, bool limitFlag = false);
    void addValue       (const double rhsDouble, bool limitFlag = false);
    void subtractValue  (const double rhsDouble, bool limitFlag = false);

    void multiplyOffset (const double rhsDouble, bool limitFlag = false);
    void divideOffset   (const double rhsDouble, bool limitFlag = false);
    void addOffset      (const double rhsDouble, bool limitFlag = false);
    void subtractOffset (const double rhsDouble, bool limitFlag = false);

    // MISC
    void limitValues(double maxSV = MAXIMUM_SV,
                     double minSV = MINIMUM_SV,
                     double maxBPM = MAXIMUM_BPM,
                     double minBPM = MINIMUM_BPM);
    void limitOffset(double minOffset = Common::MINIMUM_OFFSET,
                     double maxOffset = Common::MAXIMUM_OFFSET);

    static const int MINIMUM_SV = 1;
    static const int MAXIMUM_SV = 18;
    static const int MINIMUM_BPM = 0;
    static const int MAXIMUM_BPM = INT_MAX;

protected:
    double offset        ;
    double code          ;
    int    metronome     ;
    int    sampleSet     ;
    int    sampleSetIndex;
    int    volume        ;
    bool   isBPM         ;
    bool   isKiai        ;
    bool   loadFail      ;

};

#endif // COM_TP_H
