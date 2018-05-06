#include "hitobject.h"

// CONSTRUCTORS
HitObject::HitObject()
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
    loadFail        =   false;
}
HitObject::HitObject(double newOffset, int newColumn, int newKeys) : HitObject()
{
    loadHO(newOffset, newColumn, newKeys);
}
HitObject::HitObject(QLineEdit *line, int newKeys) : HitObject()
{
    loadHO(line, newKeys);
}
HitObject::HitObject(QString &HO, int newKeys) : HitObject()
{
    loadHO(HO, newKeys);
}

// LOADERS
void HitObject::loadHO(double &newOffset, int &newColumn, int &newKeys)
{
    offset = newOffset;
    keys   = newKeys;
    setColumn(newColumn);
}
void HitObject::loadHO(QLineEdit *line, int newKeys)
{
    QString newOM_HO;
    newOM_HO = line->text();

    loadHO(newOM_HO, newKeys);
}
void HitObject::loadHO(QString &HO, int newKeys)
{
    if (!amberCommon::isHO(HO)) // Case: Invalid
    {
        loadFail = true;
        throw HOLoadFail(QString("Input not HO: ") + HO);
    }

    // Case: HO

    /* REFERENCE FOR .osu HO
    // NN

    // splitComma [0] [1] [2]  [3][4]
    // splitColon                     [0][1][2][3][4]
    // REFERENCE  448,192,1799,5, 6,  1: 1: 2: 70:audio.mp3

    // LN

    // splitComma [0] [1] [2]  [3][4]
    // splitColon                    [0]  [1][2][3][4][5]
    // REFERENCE  448,192,1799,5, 6, 2001:1: 1: 2: 70:audio.mp3
    */

    QStringList HO_splitComma,
                HO_splitColon;

    keys = newKeys;

    HO_splitComma = HO.split(",", QString::KeepEmptyParts);
    HO_splitColon = HO_splitComma[HO_splitComma.size() - 1]
            .split(":", QString::KeepEmptyParts);

    if (HO_splitColon.size() == 5 &&
        HO_splitComma.size() == 6) // Means it is a NN
    {
        //Assignment to Values
        xAxis           =   (HO_splitComma[0]).toInt()   ;
        yAxis           =   (HO_splitComma[1]).toInt()   ;
        offset          =   (HO_splitComma[2]).toDouble();
        noteType        =   (HO_splitComma[3]).toInt()   ;
        hitsoundType    =   (HO_splitComma[4]).toInt()   ;
        sampleSet       =   (HO_splitColon[0]).toInt()   ;
        addition        =   (HO_splitColon[1]).toInt()   ;
        customSet       =   (HO_splitColon[2]).toInt()   ;
        volume          =   (HO_splitColon[3]).toInt()   ;
        hitsoundFile    =   (HO_splitColon[4])           ;

        //Default lnEnd Value
        lnEnd           =   -1;
    }
    else if (HO_splitColon.size() == 6 &&
             HO_splitComma.size() == 6) // Means it is a LN
    {
        //Assignment to Values
        xAxis           = (HO_splitComma[0]).toInt()   ;
        yAxis           = (HO_splitComma[1]).toInt()   ;
        offset          = (HO_splitComma[2]).toDouble();
        noteType        = (HO_splitComma[3]).toInt()   ;
        hitsoundType    = (HO_splitComma[4]).toInt()   ;
        lnEnd           = (HO_splitColon[0]).toDouble();
        sampleSet       = (HO_splitColon[1]).toInt()   ;
        addition        = (HO_splitColon[2]).toInt()   ;
        customSet       = (HO_splitColon[3]).toInt()   ;
        volume          = (HO_splitColon[4]).toInt()   ;
        hitsoundFile    = (HO_splitColon[5])           ;
    } else {
        loadFail = true;
        throw amberException("An unexpected error has occured.");
    }
}

// SETTERS
void HitObject::setOffset(double newOffset)
{
    amberCommon::assertOffsetValid(newOffset);

    offset = newOffset;
    return;
}
bool HitObject::setColumn(unsigned short newColumn)
{
    assertColumnValid(newColumn);
    assertKeysValid();

    // This function changes xAxis according to newColumn
    xAxis = round(((double(newColumn) + 1.0) * 2.0 - 1.0) * 256.0 / double(keys));
    return true;
}

// GETTERS
void HitObject::printInfo() const
{
    qDebug() << ("[---- Hit Object Info ----]")            << "\n"
    << ("XAXIS        : " + QString::number(xAxis       )) << "\n"
    << ("YAXIS        : " + QString::number(yAxis       )) << "\n"
    << ("OFFSET       : " + QString::number(offset      )) << "\n"
    << ("NOTETYPE     : " + QString::number(noteType    )) << "\n"
    << ("HITSOUNDTYPE : " + QString::number(hitsoundType)) << "\n"
    << ("LNEND        : " + QString::number(lnEnd       )) << "\n"
    << ("SAMPLESET    : " + QString::number(sampleSet   )) << "\n"
    << ("ADDITION     : " + QString::number(addition    )) << "\n"
    << ("CUSTOMSET    : " + QString::number(customSet   )) << "\n"
    << ("VOLUME       : " + QString::number(volume      )) << "\n"
    << ("HITSOUNDFILE : " + hitsoundFile)                  << "\n"
    << ("KEYS         : " + QString::number(keys        )) << "\n"
    << ("COLUMN       : " + QString::number(getColumn() )) << "\n";
}
unsigned short HitObject::getColumn() const
{
    assertKeysValid();

    unsigned short output;
    output = round((((double(xAxis) / 256.0) * double(keys) + 1.0) / 2.0) - 1.0);
    // This output starts from 0

    return output;
}
QString HitObject::toString() const
{
    assertXAxisValid();

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

// OPERS
void HitObject::addColumn      (const int &rhsInt)
{
    setColumn(getColumn() + rhsInt);
}
void HitObject::subtractColumn (const int &rhsInt)
{
    setColumn(getColumn() - rhsInt);
}
void HitObject::multiplyOffset (const double &rhsDouble)
{
    setOffset(getOffset() * rhsDouble);
}
void HitObject::divideOffset   (const double &rhsDouble)
{
    amberCommon::assertDivByZero(rhsDouble);
    setOffset(getOffset() / rhsDouble);
}
void HitObject::addOffset      (const double &rhsDouble)
{
    setOffset(getOffset() + rhsDouble);
}
void HitObject::subtractOffset (const double &rhsDouble)
{
    setOffset(getOffset() - rhsDouble);
}

void HitObject::assertColumnValid() const
{
    if (getColumn() > MAXIMUM_COLUMN)
    {
        throw columnOutOfRange(getColumn(),
                               MINIMUM_COLUMN,
                               MAXIMUM_COLUMN);
    }
}
void HitObject::assertColumnValid(int newColumn)
{
    if (newColumn < MINIMUM_COLUMN || newColumn > MAXIMUM_COLUMN)
    {
        throw columnOutOfRange(newColumn,
                               MINIMUM_COLUMN,
                               MAXIMUM_COLUMN);
    }
}

void HitObject::assertXAxisValid() const
{
    if (xAxis > MAXIMUM_XAXIS)
    {
        throw xAxisOutOfRange(xAxis,
                              amberCommon::MINIMUM_OFFSET,
                              amberCommon::MAXIMUM_OFFSET);
    }
}
void HitObject::assertXAxisValid(int newXAxis)
{
    if (newXAxis < MINIMUM_XAXIS || newXAxis > MAXIMUM_XAXIS)
    {
        throw xAxisOutOfRange(newXAxis,
                              amberCommon::MINIMUM_OFFSET,
                              amberCommon::MAXIMUM_OFFSET);
    }
}
void HitObject::assertKeysValid() const
{
    if (keys < MINIMUM_KEYS || keys > MAXIMUM_KEYS)
    {
        throw keysOutOfRange(keys,
                             MINIMUM_KEYS,
                             MAXIMUM_KEYS);
    }
}
void HitObject::assertKeysValid(int newKeys)
{
    if (newKeys < MINIMUM_KEYS || newKeys > MAXIMUM_KEYS)
    {
        throw keysOutOfRange(newKeys,
                             MINIMUM_KEYS,
                             MAXIMUM_KEYS);
    }
}

void HitObject::limitColumn(int &maxColumn, int &minColumn)
{
    if (getColumn() > maxColumn)
    {
        setColumn(maxColumn);
    }
    else if (getColumn() < minColumn)
    {
        setColumn(minColumn);
    }
}
void HitObject::limitColumn()
{
    int maxColumn, minColumn;

    maxColumn = keys - 1;
    minColumn = MINIMUM_COLUMN;

    if (getColumn() > maxColumn)
    {
        setColumn(maxColumn);
    }
    else if (getColumn() < minColumn)
    {
        setColumn(minColumn);
    }
}
void HitObject::limitOffset(double minOffset, double maxOffset)
{
    if (offset > maxOffset)
    {
        setOffset(minOffset);
    }
    else if (offset < minOffset)
    {
        setOffset(minOffset);
    }
}
// MISC




