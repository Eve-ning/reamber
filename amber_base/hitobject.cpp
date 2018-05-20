#include "hitobject.h"

// CONSTRUCTORS
HitObject::HitObject()
{
    xAxis = 256;
    yAxis = 192;
    noteType = 1;
    hitsoundType = 0;
    lnEnd = -1;
    sampleSet = 0;
    addition = 0;
    customSet = 0;
    volume = 0;
    hitsoundFile = "";
    keys = 0;
    loadFail = false;
}
HitObject::HitObject(const double newOffset, const int newColumn, const int newKeys)
    : HitObject()
{
    loadHO(newOffset, newColumn, newKeys);
}
HitObject::HitObject(const QLineEdit* line, const int newKeys)
    : HitObject()
{
    loadHO(line, newKeys);
}
HitObject::HitObject(const QString& HO, const int newKeys)
    : HitObject()
{
    loadHO(HO, newKeys);
}

// LOADERS
void HitObject::loadHO(const double& newOffset, const int& newColumn, const int& newKeys)
{
    offset = newOffset;
    keys = newKeys;
    setColumn(newColumn);
}
void HitObject::loadHO(const QLineEdit* line, const int& newKeys)
{
    QString newOM_HO;
    newOM_HO = line->text();

    loadHO(newOM_HO, newKeys);
}
void HitObject::loadHO(const QString& HO, const int& newKeys)
{
    if (!Common::isHO(HO)) // Case: Invalid
    {
        loadFail = true;
        AExc(AExc::HO_LOADFAIL, QString("Input: ") + HO);
        return;
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

    QStringList HO_splitComma, HO_splitColon;

    keys = newKeys;

    HO_splitComma = HO.split(",", QString::KeepEmptyParts);
    HO_splitColon = HO_splitComma[HO_splitComma.size() - 1].split(":", QString::KeepEmptyParts);

    if (HO_splitColon.size() == 5 && HO_splitComma.size() == 6) // Means it is a NN
    {
        // Assignment to Values
        xAxis = (HO_splitComma[0]).toInt();
        yAxis = (HO_splitComma[1]).toInt();
        offset = (HO_splitComma[2]).toDouble();
        noteType = (HO_splitComma[3]).toInt();
        hitsoundType = (HO_splitComma[4]).toInt();
        sampleSet = (HO_splitColon[0]).toInt();
        addition = (HO_splitColon[1]).toInt();
        customSet = (HO_splitColon[2]).toInt();
        volume = (HO_splitColon[3]).toInt();
        hitsoundFile = (HO_splitColon[4]);

        // Default lnEnd Value
        lnEnd = -1;
    }
    else if (HO_splitColon.size() == 6 && HO_splitComma.size() == 6) // Means it is a LN
    {
        // Assignment to Values
        xAxis = (HO_splitComma[0]).toInt();
        yAxis = (HO_splitComma[1]).toInt();
        offset = (HO_splitComma[2]).toDouble();
        noteType = (HO_splitComma[3]).toInt();
        hitsoundType = (HO_splitComma[4]).toInt();
        lnEnd = (HO_splitColon[0]).toDouble();
        sampleSet = (HO_splitColon[1]).toInt();
        addition = (HO_splitColon[2]).toInt();
        customSet = (HO_splitColon[3]).toInt();
        volume = (HO_splitColon[4]).toInt();
        hitsoundFile = (HO_splitColon[5]);
    }
    else
    {
        loadFail = true;
        AExc(AExc::UNEXPECTED_ERROR, QString("Within this context ") + __FUNCTION__);
        return;
    }
}

// SETTERS
bool HitObject::setColumn(const int& newColumn)
{
    isColumnValid(newColumn);
    isKeysValid();

    // This function changes xAxis according to newColumn
    xAxis = round(((double(newColumn) + 1.0) * 2.0 - 1.0) * 256.0 / double(keys));
    return true;
}

// GETTERS
void HitObject::printInfo() const
{
    qDebug() << ("[---- Hit Object Info ----]") << "\n"
             << ("XAXIS        : " + QString::number(xAxis)) << "\n"
             << ("YAXIS        : " + QString::number(yAxis)) << "\n"
             << ("OFFSET       : " + QString::number(offset)) << "\n"
             << ("NOTETYPE     : " + QString::number(noteType)) << "\n"
             << ("HITSOUNDTYPE : " + QString::number(hitsoundType)) << "\n"
             << ("LNEND        : " + QString::number(lnEnd)) << "\n"
             << ("SAMPLESET    : " + QString::number(sampleSet)) << "\n"
             << ("ADDITION     : " + QString::number(addition)) << "\n"
             << ("CUSTOMSET    : " + QString::number(customSet)) << "\n"
             << ("VOLUME       : " + QString::number(volume)) << "\n"
             << ("HITSOUNDFILE : " + hitsoundFile) << "\n"
             << ("KEYS         : " + QString::number(keys)) << "\n"
             << ("COLUMN       : " + QString::number(getColumn())) << "\n";
}
int HitObject::getColumn() const
{
    isKeysValid();

    int output;
    output = round((((double(xAxis) / 256.0) * double(keys) + 1.0) / 2.0) - 1.0);
    // This output starts from 0

    return output;
}
QString HitObject::toString() const
{
    if(!isXAxisValid()){
        AExc(AExc::VALUE_OUT_OF_RANGE, QString("xAxis is invalid: ") + xAxis);
    }

    return QString::number(xAxis) + "," +
           QString::number(yAxis) + "," +
           QString::number(offset) + "," +
           QString::number(noteType) + "," +
           QString::number(hitsoundType) + "," +
           (lnEnd == -1 ? "" : (QString::number(lnEnd) + ":")) +
           QString::number(sampleSet) + ":" + QString::number(addition) + ":" +
           QString::number(customSet) + ":" +
           QString::number(volume) + ":" + hitsoundFile;
}

// OPERS
void HitObject::addColumn(const int& rhsInt)
{
    setColumn(getColumn() + rhsInt);
}
void HitObject::subtractColumn(const int& rhsInt)
{
    setColumn(getColumn() - rhsInt);
}
void HitObject::multiplyOffset(const double& rhsDouble)
{
    setOffset(getOffset() * rhsDouble);
}
void HitObject::divideOffset(const double& rhsDouble)
{

    setOffset(getOffset() / rhsDouble);
}
void HitObject::addOffset(const double& rhsDouble)
{
    setOffset(getOffset() + rhsDouble);
}
void HitObject::subtractOffset(const double& rhsDouble)
{
    setOffset(getOffset() - rhsDouble);
}

bool HitObject::isColumnValid() const
{
    return (getColumn() < MINIMUM_COLUMN || getColumn() > MAXIMUM_COLUMN);
}
bool HitObject::isColumnValid(const int& newColumn)
{
    return (newColumn < MINIMUM_COLUMN || newColumn > MAXIMUM_COLUMN);
}
bool HitObject::isXAxisValid() const
{
    return (xAxis < MINIMUM_XAXIS || xAxis > MAXIMUM_XAXIS);
}
bool HitObject::isXAxisValid(const int& newXAxis)
{
    return (newXAxis < MINIMUM_XAXIS || newXAxis > MAXIMUM_XAXIS);
}
bool HitObject::isKeysValid() const
{
    return (keys < MINIMUM_KEYS || keys > MAXIMUM_KEYS);
}
bool HitObject::isKeysValid(const int& newKeys)
{
    return (newKeys < MINIMUM_KEYS || newKeys > MAXIMUM_KEYS);
}

void HitObject::assertColumnValid() const
{
    if (isColumnValid())
    {
        AExc(AExc::VALUE_OUT_OF_RANGE, QString("Column %1 is out of range: [%2 - %3]")
                                           .arg(getColumn())
                                           .arg(MINIMUM_COLUMN)
                                           .arg(MAXIMUM_COLUMN));
        return;
    }
}
void HitObject::assertColumnValid(const int& newColumn)
{
    if (isColumnValid(newColumn))
    {
        AExc(AExc::VALUE_OUT_OF_RANGE, QString("Column %1 is out of range: [%2 - %3]")
                                           .arg(newColumn)
                                           .arg(MINIMUM_COLUMN)
                                           .arg(MAXIMUM_COLUMN));
        return;
    }
}
void HitObject::assertXAxisValid() const
{
    if (isXAxisValid())
    {
        AExc(AExc::VALUE_OUT_OF_RANGE, QString("x-Axis %1 is out of range: [%2 - %3]")
                                           .arg(xAxis)
                                           .arg(MINIMUM_XAXIS)
                                           .arg(MAXIMUM_XAXIS));
        return;
    }
}
void HitObject::assertXAxisValid(const int& newXAxis)
{
    if (isXAxisValid(newXAxis))
    {
        AExc(AExc::VALUE_OUT_OF_RANGE, QString("x-Axis %1 is out of range: [%2 - %3]")
                                           .arg(newXAxis)
                                           .arg(MINIMUM_XAXIS)
                                           .arg(MAXIMUM_XAXIS));
        return;
    }
}
void HitObject::assertKeysValid() const
{
    if (isKeysValid())
    {
        AExc(AExc::VALUE_OUT_OF_RANGE, QString("Keys %1 is out of range: [%2 - %3]")
                                           .arg(keys)
                                           .arg(MINIMUM_KEYS)
                                           .arg(MAXIMUM_KEYS));
        return;
    }
}
void HitObject::assertKeysValid(const int& newKeys)
{
    if (isKeysValid(newKeys))
    {
        AExc(AExc::VALUE_OUT_OF_RANGE, QString("Keys %1 is out of range: [%2 - %3]")
                                           .arg(newKeys)
                                           .arg(MINIMUM_KEYS)
                                           .arg(MAXIMUM_KEYS));
        return;
    }
}

void HitObject::limitColumn(const int& maxColumn, const int& minColumn)
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
// MISC
