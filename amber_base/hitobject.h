#ifndef COM_HO_H
#define COM_HO_H

#include <QLineEdit>
#include "common.h"

class  HitObject
{
public:

    // CONSTRUCTORS
    HitObject();
    HitObject(QString &HO, int newKeys = 0);
    HitObject(double newOffset, int newColumn, int newKeys = 0);
    HitObject(QLineEdit *line, int newKeys = 0);

    operator QString() const { return toString(); }

    // LOADERS
    void loadHO(QString &HO, int newKeys = 0);
    void loadHO(double &newOffset, int &newColumn, int &newKeys);
    void loadHO(QLineEdit *line, int newKeys = 0);

    // SETTERS
    void setXAxis        (unsigned short  newXAxis       ){ xAxis        = newXAxis       ; return; }
    void setYAxis        (unsigned short  newYAxis       ){ yAxis        = newYAxis       ; return; }
    void setOffset       (double          newOffset      );
    void setNoteType     (unsigned short  newNoteType    ){ noteType     = newNoteType    ; return; }
    void setHitsoundType (unsigned short  newHitsoundType){ hitsoundType = newHitsoundType; return; }
    void setSampleSet    (unsigned short  newSampleSet   ){ sampleSet    = newSampleSet   ; return; }
    void setAddition     (unsigned short  newAddition    ){ addition     = newAddition    ; return; }
    void setCustomSet    (unsigned short  newCustomSet   ){ customSet    = newCustomSet   ; return; }
    void setVolume       (unsigned short  newVolume      ){ volume       = newVolume      ; return; }
    void setHitsoundFile (QString         newHitsoundFile){ hitsoundFile = newHitsoundFile; return; }
    void setLNEnd        (double          newLNEnd       ){ lnEnd        = newLNEnd       ; return; }
    void setKeys         (unsigned short  newKeys        ){ keys         = newKeys        ; return; }
    bool setColumn       (unsigned short  newColumn);

    // GETTERS
    void            printInfo       () const;
    unsigned short  getXAxis        () const { return xAxis       ; }
    unsigned short  getYAxis        () const { return yAxis       ; }
    double          getOffset       () const { return offset      ; }
    unsigned short  getNoteType     () const { return noteType    ; }
    unsigned short  getHitsoundType () const { return hitsoundType; }
    unsigned short  getSampleSet    () const { return sampleSet   ; }
    unsigned short  getAddition     () const { return addition    ; }
    unsigned short  getCustomSet    () const { return customSet   ; }
    unsigned short  getVolume       () const { return volume      ; }
    QString         getHitsoundFile () const { return hitsoundFile; }
    double          getLNEnd        () const { return lnEnd       ; }
    unsigned short  getKeys         () const { return keys; }
    unsigned short  getLNLen        () const { return lnEnd == -1 ? 0 : lnEnd - offset; }
    bool            getLoadFail     () const { return loadFail; }
    unsigned short  getColumn       () const;
    QString         toString        () const;

    // OPERS
    void addColumn      (const int &rhsInt);
    void subtractColumn (const int &rhsInt);

    void multiplyOffset (const double &rhsDouble);
    void divideOffset   (const double &rhsDouble);
    void addOffset      (const double &rhsDouble);
    void subtractOffset (const double &rhsDouble);

    bool operator <(HitObject *OM_HO) { return offset < OM_HO->getOffset(); }
    bool operator >(HitObject *OM_HO) { return offset > OM_HO->getOffset(); }
    bool operator <(HitObject  OM_HO) { return offset < OM_HO.getOffset(); }
    bool operator >(HitObject  OM_HO) { return offset > OM_HO.getOffset(); }

           void assertColumnValid ()               const; // Checks w.r.t. current column
    static void assertColumnValid (int newColumn)       ; // Checks w.r.t. specified column
           void assertKeysValid   ()               const; // Checks w.r.t. current key
    static void assertKeysValid   (int newKeys  )       ; // Checks w.r.t. specified key
           void assertXAxisValid  ()               const; // Checks w.r.t. current xAxis
    static void assertXAxisValid  (int newXAxis  )      ; // Checks w.r.t. specified xAxis

    void limitColumn (int &maxColumn, int &minColumn);
    void limitColumn ();
    void limitOffset (double minOffset = amberCommon::MINIMUM_OFFSET, double maxOffset = amberCommon::MAXIMUM_OFFSET);

    static const int MINIMUM_KEYS   = 1;
    static const int MAXIMUM_KEYS   = 18;
    static const int MINIMUM_COLUMN = MINIMUM_KEYS - 1;
    static const int MAXIMUM_COLUMN = MAXIMUM_KEYS - 1;
    static const int MINIMUM_XAXIS  = 0;
    static const int MAXIMUM_XAXIS  = 512;

protected:

    //320,   192,   381333, 1,        0,            0:         0:        0:         0:      hitsound.wav
    //xAxis, yAxis, offset, noteType, hitsoundType, sampleSet: addition: customSet: volume: hitsoundFile

    unsigned short  xAxis       ;
    unsigned short  yAxis       ;
    double          offset      ;
    unsigned short  noteType    ;
    unsigned short  hitsoundType;
    double          lnEnd       ;
    unsigned short  sampleSet   ;
    unsigned short  addition    ;
    unsigned short  customSet   ;
    unsigned short  volume      ;
    QString         hitsoundFile;

    unsigned short  keys;

    bool            loadFail;
};

#endif // COM_HO_H
