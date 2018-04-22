#include "com_ho.h"

// CONSTRUCTORS
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
    loadFail        =   false;
}
cOM_HO::cOM_HO(double newOffset, int newColumn, int newKeys) : cOM_HO()
{
    loadHO(newOffset, newColumn, newKeys);
}
cOM_HO::cOM_HO(QLineEdit *line, int newKeys) : cOM_HO()
{
    loadHO(line, newKeys);
}
cOM_HO::cOM_HO(QString &HO, int newKeys) : cOM_HO()
{
    loadHO(HO, newKeys);
}

// LOADERS
void cOM_HO::loadHO(double &newOffset, int &newColumn, int &newKeys)
{
    offset = newOffset;
    keys   = newKeys;
    setColumn(newColumn);
}
void cOM_HO::loadHO(QLineEdit *line, int newKeys)
{
    QString newOM_HO;
    newOM_HO = line->text();

    loadHO(newOM_HO, newKeys);
}
void cOM_HO::loadHO(QString &HO, int newKeys)
{
    if (!cOM_Common::isHO(HO))
    {
        loadFail = true;
        failMsg  = QString("Input not HO: ") + HO;
        return;
    }

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
        throw loadInputFail(HO);
    }
}

// SETTERS
void cOM_HO::setOffset(double newOffset)
{
    cOM_Common::assertOffsetValid(newOffset);

    offset = newOffset;
    return;
}
bool cOM_HO::setColumn(unsigned short newColumn)
{
    assertColumnValid(newColumn);
    assertKeysValid();

    // This function changes xAxis according to newColumn
    xAxis = round(((double(newColumn) + 1.0) * 2.0 - 1.0) * 256.0 / double(keys));
    return true;
}

// GETTERS
void cOM_HO::printInfo() const
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
QString cOM_HO::getFailMsg() const
{
    return failMsg;
}
unsigned short cOM_HO::getColumn() const
{
    assertKeysValid();

    unsigned short output;
    output = round((((double(xAxis) / 256.0) * double(keys) + 1.0) / 2.0) - 1.0);
    // This output starts from 0

    return output;
}
QString cOM_HO::toString() const
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
void cOM_HO::addColumn      (const int &rhsInt)
{
    setColumn(getColumn() + rhsInt);
}
void cOM_HO::subtractColumn (const int &rhsInt)
{
    setColumn(getColumn() - rhsInt);
}
void cOM_HO::multiplyOffset (const double &rhsDouble)
{
    setOffset(getOffset() * rhsDouble);
}
void cOM_HO::divideOffset   (const double &rhsDouble)
{
    cOM_Common::assertDivByZero(rhsDouble);
    setOffset(getOffset() / rhsDouble);
}
void cOM_HO::addOffset      (const double &rhsDouble)
{
    setOffset(getOffset() + rhsDouble);
}
void cOM_HO::subtractOffset (const double &rhsDouble)
{
    setOffset(getOffset() - rhsDouble);
}

void cOM_HO::assertColumnValid()
{
    if (getColumn() < MINIMUM_COLUMN || getColumn() > keys - 1)
    {
        throw columnOutOfRange(getColumn(), MINIMUM_COLUMN, keys - 1);
    }
}
void cOM_HO::assertColumnValid(int &newColumn)
{
    if (newColumn < MINIMUM_COLUMN || newColumn > keys - 1)
    {
        throw columnOutOfRange(newColumn, MINIMUM_COLUMN, keys - 1);
    }
}

void cOM_HO::assertXAxisValid()
{
    if (xAxis < MINIMUM_XAXIS || xAxis > MAXIMUM_XAXIS)
    {
        throw offsetOutOfRange(offset, cOM_Common::MINIMUM_OFFSET, cOM_Common::MAXIMUM_OFFSET);
    }
}
void cOM_HO::assertXAxisValid(int &newXAxis)
{
    if (newXAxis < MINIMUM_XAXIS || newXAxis > MAXIMUM_XAXIS)
    {
        throw offsetOutOfRange(offset, cOM_Common::MINIMUM_OFFSET, cOM_Common::MAXIMUM_OFFSET);
    }
}
void cOM_HO::assertKeysValid()
{
    if (keys < MINIMUM_KEYS || keys > MAXIMUM_KEYS)
    {
        throw offsetOutOfRange(keys, cOM_Common::MINIMUM_KEYS, MAXIMUM_KEYS);
    }
}
void cOM_HO::assertKeysValid(int &newKeys)
{
    if (newKeys < MINIMUM_KEYS || newKeys > MAXIMUM_KEYS)
    {
        throw offsetOutOfRange(newKeys, MINIMUM_KEYS, MAXIMUM_KEYS);
    }
}

void cOM_HO::limitColumn(int &maxColumn, int &minColumn)
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
void cOM_HO::limitColumn()
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
void cOM_HO::limitOffset(double minOffset, double maxOffset)
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

void cOM_HO::setFailMsg(const QString &value)
{
    failMsg = value;
}

// MISC




