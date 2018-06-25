#ifndef HITOBJECT_IMPL_H
#define HITOBJECT_IMPL_H

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

class HitObject_impl
{
public:

    HitObject_impl();

    operator QString() const { return toString(); }
    bool operator <(const HitObject_impl &value_) const {
        return (offset < value_.offset);
    }
    bool operator >(const HitObject_impl &value_) const {
        return (offset > value_.offset);
    }
    bool operator <=(const HitObject_impl &value_) const {
        return (offset <= value_.offset);
    }
    bool operator >=(const HitObject_impl &value_) const {
        return (offset >= value_.offset);
    }
    bool operator ==(const HitObject_impl &value_) const {
        return (offset == value_.offset);
    }

    // LOADERS
    void loadHO(const QString &HO, const int &keys_ = 0);
    void loadHO(const Offset &offset_, const Column &column_, const Keys &keys_);
    void loadHO(const QLineEdit *line, const int &keys_ = 0);

    // SETTERS
    void setColumn(const XAxis& xAxis_)
    {
        column = Column(xAxis_, keys);
    }
    void setColumn(const Column& column_)
    {
        column = column_;
    }
    void setColumn(const int& column_)
    {
        column = Column(column_);
    }
    void setYAxis(const YAxis& yAxis_)
    {
        yAxis = yAxis_;
    }
    void setNoteType(const NoteType& noteType_)
    {
        noteType = noteType_;
    }
    void setHitsoundType(const SampleSet& hitsoundType_)
    {
        hitsoundType = hitsoundType_;
    }
    void setSampleSet(const SampleSet& sampleSet_)
    {
        sampleSet = sampleSet_;
    }
    void setAddition(const SampleSet& addition_)
    {
        addition = addition_;
    }
    void setCustomSet(const SampleSet& customSet_)
    {
        customSet = customSet_;
    }
    void setVolume(const Volume& volume_)
    {
        volume = volume_;
    }
    void setHitsoundFile(const HitsoundFile& hitsoundFile_)
    {
        hitsoundFile = hitsoundFile_;
    }
    void setLNEnd(const Offset& lnEnd_)
    {
        lnEnd = lnEnd_;
    }
    void setKeys(const Keys& keys_)
    {
        keys = keys_;
    }
    void setOffset(const Offset& offset_)
    {
        offset = offset_;
    }

    // GETTERS
    void      printInfo() const;
    XAxis     getXAxis() const { return column.toXAxis(keys); }
    YAxis     getYAxis() const { return yAxis; }
    NoteType  getNoteType() const { return noteType; }
    SampleSet getHitsoundType() const { return hitsoundType; }
    SampleSet getSampleSet() const { return sampleSet; }
    SampleSet getAddition() const { return addition; }
    SampleSet getCustomSet() const { return customSet; }
    Volume    getVolume() const { return volume; }
    HitsoundFile   getHitsoundFile() const { return hitsoundFile; }
    Offset    getLNEnd() const { return lnEnd; }
    Keys      getKeys() const { return keys; }
    Offset    getLNLen() const { return lnEnd.value() == -1.0 ? Offset(0.0) : Offset(lnEnd - offset); }
    Column    getColumn() const { return column; }
    Offset    getOffset() const { return offset; }

    QString toString        () const;

protected:

    Column column;
    YAxis yAxis;
    NoteType noteType;
    SampleSet hitsoundType;
    Offset lnEnd;
    SampleSet sampleSet;
    SampleSet addition;
    SampleSet customSet;
    Volume volume;
    HitsoundFile hitsoundFile;
    Keys keys;
    Offset offset;

    bool loadFail = false;
};

#endif // HitObject_IMPL_H
