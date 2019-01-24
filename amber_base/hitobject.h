#ifndef COM_HO_H
#define COM_HO_H

#include <QLineEdit>
#include "common.h"
#include "osuobject.h"

class  HitObject :
        public osuObject
{
public:

    // CONSTRUCTORS
    HitObject();
    HitObject(const QString &HO, const int newKeys = 0);
    HitObject(const double newOffset, const int newColumn, const int newKeys = 0);
    HitObject(const QLineEdit *line, const int newKeys = 0);

    operator QString() const { return toString(); }

    // LOADERS
    void loadHO(const QString &HO, const int &newKeys = 0);
    void loadHO(const double &newOffset, const int &newColumn, const int &newKeys);
    void loadHO(const QLineEdit *line, const int &newKeys = 0);

    // SETTERS
    void setXAxis        (const int     &xAxis_       ){ xAxis        = xAxis_       ; return; }
    void setYAxis        (const int     &yAxis_       ){ yAxis        = yAxis_       ; return; }
    void setNoteType     (const int     &noteType_    ){ noteType     = noteType_    ; return; }
    void setHitsoundType (const int     &hitsoundType_){ hitsoundType = hitsoundType_; return; }
    void setSampleSet    (const int     &sampleSet_   ){ sampleSet    = sampleSet_   ; return; }
    void setAddition     (const int     &addition_    ){ addition     = addition_    ; return; }
    void setCustomSet    (const int     &customSet_   ){ customSet    = customSet_   ; return; }
    void setVolume       (const int     &volume_      ){ volume       = volume_      ; return; }
    void setHitsoundFile (const QString &hitsoundFile_){ hitsoundFile = hitsoundFile_; return; }
    void setLNEnd        (const double  &lnEnd_       ){ lnEnd        = lnEnd_       ; return; }
    void setKeys         (const int     &keys_        ){ keys         = keys_        ; return; }

    bool setColumn       (const int     &newColumn);
    // GETTERS
    void    printInfo       () const;
    int     getXAxis        () const { return xAxis       ; }
    int     getYAxis        () const { return yAxis       ; }
    int     getNoteType     () const { return noteType    ; }
    int     getHitsoundType () const { return hitsoundType; }
    int     getSampleSet    () const { return sampleSet   ; }
    int     getAddition     () const { return addition    ; }
    int     getCustomSet    () const { return customSet   ; }
    int     getVolume       () const { return volume      ; }
    QString getHitsoundFile () const { return hitsoundFile; }
    double  getLNEnd        () const { return lnEnd       ; }
    int     getKeys         () const { return keys; }
    int     getLNLen        () const { return lnEnd == -1 ? 0 : lnEnd - offset; }
    bool    getLoadFail     () const { return loadFail; }
    int     getColumn       () const;

    QString toString        () const;

    // OPERS
    void addColumn      (const int &rhsInt);
    void subtractColumn (const int &rhsInt);

    void multiplyOffset (const double &rhsDouble);
    void divideOffset   (const double &rhsDouble);
    void addOffset      (const double &rhsDouble);
    void subtractOffset (const double &rhsDouble);

           bool isColumnValid() const; // Checks w.r.t. current column
    static bool isColumnValid(const int &newColumn); // Checks w.r.t. specified column
           bool isKeysValid  () const; // Checks w.r.t. current key
    static bool isKeysValid  (const int &newKeys); // Checks w.r.t. specified key
           bool isXAxisValid () const; // Checks w.r.t. current xAxis
    static bool isXAxisValid (const int &newXAxis); // Checks w.r.t. specified xAxis

           void assertColumnValid() const; // Checks w.r.t. current column
    static void assertColumnValid(const int &newColumn); // Checks w.r.t. specified column
           void assertKeysValid  () const; // Checks w.r.t. current key
    static void assertKeysValid  (const int &newKeys); // Checks w.r.t. specified key
           void assertXAxisValid () const; // Checks w.r.t. current xAxis
    static void assertXAxisValid (const int &newXAxis); // Checks w.r.t. specified xAxis

    void limitColumn (const int &maxColumn, const int &minColumn);
    void limitColumn ();

    static const int MINIMUM_KEYS   = 1;
    static const int MAXIMUM_KEYS   = 18;
    static const int MINIMUM_COLUMN = MINIMUM_KEYS - 1;
    static const int MAXIMUM_COLUMN = MAXIMUM_KEYS - 1;
    static const int MINIMUM_XAXIS  = 0;
    static const int MAXIMUM_XAXIS  = 512;

protected:

    //320,   192,   381333, 1,        0,            0:         0:        0:         0:      hitsound.wav
    //xAxis, yAxis, offset, noteType, hitsoundType, sampleSet: addition: customSet: volume: hitsoundFile

    int     xAxis       ;
    int     yAxis       ;
    int     noteType    ;
    int     hitsoundType;
    double  lnEnd       ;
    int     sampleSet   ;
    int     addition    ;
    int     customSet   ;
    int     volume      ;
    QString hitsoundFile;

    int     keys;

    bool    loadFail;
};

#endif // COM_HO_H
