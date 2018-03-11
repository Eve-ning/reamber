#include "com_ho.h"

cOM_HO::cOM_HO()
{
    xAxis           =   256;
    yAxis           =   192;
    offset          =   0;
    noteType        =   1;
    hitsoundType    =   0;
    lnEnd           =   -1;
    sampleSet       =   0;
    addition        =   0;
    customSet       =   0;
    volume          =   0;
    hitsoundFile    =   "";

    keys            =   0;
}

cOM_HO::cOM_HO(QString HO)
{
    // NN

    // splitComma [0] [1] [2]  [3][4]
    // splitColon                     [0][1][2][3][4]
    // REFERENCE  448,192,1799,5, 6,  1: 1: 2: 70:audio.mp3

    // LN

    // splitComma [0] [1] [2]  [3][4]
    // splitColon                    [0]  [1][2][3][4][5]
    // REFERENCE  448,192,1799,5, 6, 2001:1: 1: 2: 70:audio.mp3

    QStringList HO_splitComma,
                HO_splitColon;
    HO_splitComma = HO.split(",", QString::KeepEmptyParts);
    HO_splitColon = HO_splitComma[HO_splitComma.size() - 1]
                        .split(":", QString::KeepEmptyParts);

    if (HO_splitColon.size() == 5 &&
        HO_splitComma.size() == 6) // Means it is a NN
    {
        //Assignment to Values
        xAxis           =   int     (HO_splitComma[0]);
        yAxis           =   int     (HO_splitComma[1]);
        offset          =   double  (HO_splitComma[2]);
        noteType        =   int     (HO_splitComma[3]);
        hitsoundType    =   int     (HO_splitComma[4]);
        sampleSet       =   int     (HO_splitColon[0]);
        addition        =   int     (HO_splitColon[1]);
        customSet       =   int     (HO_splitColon[2]);
        volume          =   int     (HO_splitColon[3]);
        hitsoundFile    =           (HO_splitColon[4]);

        //Default lnEnd Value
        lnEnd           =   -1;
    }
    else if (HO_splitColon.size() == 6 &&
             HO_splitComma.size() == 6) // Means it is a LN
    {
        //Assignment to Values
        xAxis           =   int     (HO_splitComma[0]);
        yAxis           =   int     (HO_splitComma[1]);
        offset          =   double  (HO_splitComma[2]);
        noteType        =   int     (HO_splitComma[3]);
        hitsoundType    =   int     (HO_splitComma[4]);
        lnEnd           =   double  (HO_splitColon[0]);
        sampleSet       =   int     (HO_splitColon[1]);
        addition        =   int     (HO_splitColon[2]);
        customSet       =   int     (HO_splitColon[3]);
        volume          =   int     (HO_splitColon[4]);
        hitsoundFile    =           (HO_splitColon[5]);
    } else {
        STATMSG("Failed to Convert QString.");
        cOM_HO::cOM_HO();
    }
}

void cOM_HO::setXAxis       (unsigned short  newXAxis       ){ xAxis        = newXAxis       ; return; }
void cOM_HO::setYAxis       (unsigned short  newYAxis       ){ yAxis        = newYAxis       ; return; }
void cOM_HO::setOffset      (double          newOffset      ){ offset       = newOffset      ; return; }
void cOM_HO::setNoteType    (unsigned short  newNoteType    ){ noteType     = newNoteType    ; return; }
void cOM_HO::setHitsoundType(unsigned short  newHitsoundType){ hitsoundType = newHitsoundType; return; }
void cOM_HO::setSampleSet   (unsigned short  newSampleSet   ){ sampleSet    = newSampleSet   ; return; }
void cOM_HO::setAddition    (unsigned short  newAddition    ){ addition     = newAddition    ; return; }
void cOM_HO::setCustomSet   (unsigned short  newCustomSet   ){ customSet    = newCustomSet   ; return; }
void cOM_HO::setVolume      (unsigned short  newVolume      ){ volume       = newVolume      ; return; }
void cOM_HO::setHitsoundFile(QString         newHitsoundFile){ hitsoundFile = newHitsoundFile; return; }
void cOM_HO::setLNEnd       (double          newLNEnd       ){ lnEnd        = newLNEnd       ; return; }

unsigned short cOM_HO::getColumn() const
{
    unsigned short output;

    if (keys == 0)
    {
        STATMSG("Keys not Specified, cannot get column");
        return 1;
    }

    output = round(((xAxis / 512 * keys * 2 + 1) / 2) - 1);
    // This output starts from 0

    return output;
}

void cOM_HO::setKeys(unsigned short newKeys)
{
    keys = newKeys;
}

void cOM_HO::setColumn(unsigned short newColumn)
{
    if (keys == 0)
    {
        STATMSG("Keys not Specified, cannot set column");
        return;
    }

    // This function changes xAxis according to newColumn
    xAxis = round(((newColumn + 1) * 2 - 1) / 2 * 512 / keys);
}

void cOM_HO::toString()
{
    return      QString::number(xAxis       ) + ","
            +   QString::number(yAxis       ) + ","
            +   QString::number(offset      ) + ","
            +   QString::number(noteType    ) + ","
            +   QString::number(hitsoundType) + ","
            +   (lnEnd == -1 ? "" : (QString::number(lnEnd) + ":"))
            +   QString::number(sampleSet   ) + ":"
            +   QString::number(addition    ) + ":"
            +   QString::number(customSet   ) + ":"
            +   QString::number(volume      ) + ":"
            +   hitsoundFile;
}
