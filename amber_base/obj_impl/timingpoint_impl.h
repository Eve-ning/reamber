#ifndef TIMINGPOINT_IMPL_H
#define TIMINGPOINT_IMPL_H

#include <QLineEdit>
#include "amber_base/validity/amberexception.h"
#include "amber_base/validity/validobj.h"
#include "amber_base/info_impl/info.h"
#include "amber_base/baseclass_inc.h"

/* only for implementation
 * eg. loading, output, operators etc.
 *
 * This is to separate the menial stuff from the meat
 */

class TimingPoint_impl
{
public:
    TimingPoint_impl();
    operator QString() const { return toString(); }

    // LOADERS
    void loadTP(const QString &TP);
    void loadTP(QLineEdit* line);
    void loadTP(Offset offset_,
                double value_,
                bool isBPM_);

    // SETTERS
    void setOffset(Offset offset_)
    {
        offset = offset_;
    }
    void setOffset(double offset_)
    {
        offset = Offset(offset_);
    }
    void setCode(TimeCode code_)
    {
        timeCode = code_;
    }
    void setMetronome(Metronome metronome_)
    {
        metronome = metronome_;
    }
    void setSampleSet(SampleSet sampleSet_)
    {
        sampleSet = sampleSet_;
    }
    void setSampleSetIndex(SampleSetIndex sampleSetIndex_)
    {
        sampleSetIndex = sampleSetIndex_;
    }
    void setVolume(Volume volume_)
    {
        volume = volume_;
    }
    void setIsBPM(bool isBPM_)
    {
        isBPM = isBPM_;
    }
    void setIsSV(bool isSV_)
    {
        isBPM = !isSV_;
    }
    void setIsKiai(bool isKiai_)
    {
        isKiai = isKiai_;
    }
    void convertToSV(const BPM &referenceValue);
    void convertToBPM(const BPM &referenceValue);
    void setValue(double value_);

    // GETTERS
    void getInfo() const;
    Offset getOffset() const { return offset; }
    TimeCode getCode() const { return timeCode; }
    Metronome getMetronome() const { return metronome; }
    SampleSet getSampleSet() const { return sampleSet; }
    SampleSetIndex getSampleSetIndex() const { return sampleSetIndex; }
    Volume getVolume() const { return volume; }
    bool getIsBPM() const { return isBPM; }
    bool getIsSV() const { return !isBPM; }
    bool getIsKiai() const { return isKiai; }
    double getValue() const;
    QString toString() const;

    // OPERS
    bool operator<(TimingPoint_impl* curTP){ return offset.value() < curTP->getOffset().value(); }
    bool operator>(TimingPoint_impl* curTP){ return offset.value() > curTP->getOffset().value(); }
    bool operator<(TimingPoint_impl curTP){ return offset.value() < curTP.getOffset().value(); }
    bool operator>(TimingPoint_impl curTP){ return offset.value() > curTP.getOffset().value(); }

    // MISC


protected:
    Offset offset;
    TimeCode timeCode;
    Metronome metronome;
    SampleSet sampleSet;
    SampleSetIndex sampleSetIndex;
    Volume volume;
    bool isBPM;
    bool isKiai;
};

#endif // TIMINGPOINT_IMPL_H