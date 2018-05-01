#include "hitobjectlist.h"

// CONSTRUCTORS
HitObjectList::HitObjectList()
{
    OM_HOList = {};
    loadFail  = false;
}
HitObjectList::HitObjectList(QList<HitObject> newHOList) : HitObjectList()
{
    loadHOList(newHOList);
}
HitObjectList::HitObjectList(QString EHO, int newKeys) : HitObjectList()
{
    loadHOList(EHO, newKeys);
}
HitObjectList::HitObjectList(QTextBrowser *tb, int newKeys) : HitObjectList()
{
    loadHOList(tb, newKeys);
}
HitObjectList::HitObjectList(QLineEdit *line, int newKeys) : HitObjectList()
{
    loadHOList(line, newKeys);
}
HitObjectList::HitObjectList(QPlainTextEdit *pte, int newKeys) : HitObjectList()
{
    loadHOList(pte, newKeys);
}

// LOADERS
void HitObjectList::loadHOList(QList<HitObject> newHOList)
{
    OM_HOList = newHOList;
}
void HitObjectList::loadHOList(QTextBrowser *tb, int newKeys)
{
    QString tbText;

    tbText = tb->toPlainText();

    loadHOList(tbText, newKeys);
}
void HitObjectList::loadHOList(QLineEdit *line, int newKeys)
{
    QString lineText;

    lineText = line->text();

    loadHOList(lineText, newKeys);
}
void HitObjectList::loadHOList(QPlainTextEdit *pte, int newKeys)
{
    QString pteText;

    pteText = pte->toPlainText();

    loadHOList(pteText, newKeys);
}
void HitObjectList::loadHOList(QString &EHOorHO, int newKeys)
{
    bool boolEHO,
         boolHO;

    omInfo info;

    info = amberCommon::whatOM_Type(EHOorHO);

    boolEHO = info.getIsEHO();
    boolHO  = info.getIsHO();

    // IF NOT HO CALL EHO

    if (boolEHO) // Case: EHO
    {
        loadEHOList(EHOorHO, newKeys); // Pass to EHO Handler
        return;
    }
    else if (boolHO) // Case: HO
    {
        // Convert to StringList and pass towards QStringList Handler
        QStringList HOList;
        HOList = EHOorHO.split("\n", QString::SkipEmptyParts);

        loadHOList(HOList); // Pass to QStringList Handler
    }
    else // Case: Invalid
    {
        loadFail = true;

        throw HOLoadFail(QString("Input not HO: ") + EHOorHO);
    }
}
void HitObjectList::loadHOList(QStringList &HOList, int newKeys)
{
    QString HO;
    foreach (HO, HOList) {
        OM_HOList.append(HitObject(HO, newKeys));
    }

    return;
}
void HitObjectList::loadEHOList(QString &EHO, int newKeys)
{
    // !! DO NOT CALL THIS DIRECTLY
    // Load via loadHOList (QString, int)
    QString EHO_trim,
            EHO_eachSplitComma;
    QStringList EHO_splitComma;
    QList<double> EHO_splitPipeOffset;
    QList<int>    EHO_splitPipeColumn;
    int openBracketIndex,
        closeBracketIndex;

    openBracketIndex = EHO.indexOf("(");
    closeBracketIndex = EHO.indexOf(")");

    EHO_trim = EHO.mid(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

    EHO_splitComma = EHO_trim.split(",",QString::SkipEmptyParts);

    foreach (EHO_eachSplitComma, EHO_splitComma) {
        EHO_splitPipeOffset.append(EHO_eachSplitComma.split("|")[0].toDouble());
        EHO_splitPipeColumn.append(EHO_eachSplitComma.split("|")[1].toInt());
    }

    for (int temp = 0; temp < EHO_splitPipeColumn.size(); temp ++)
    {
        OM_HOList.append(HitObject(EHO_splitPipeOffset[temp],
                                EHO_splitPipeColumn[temp],
                                newKeys));
    }
}

// SETTERS
void HitObjectList::setOffsetList(QList<double> &newOffsetList)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLengthMatch(OM_HOList.length(), newOffsetList.length());

    for (int i = 0; i < newOffsetList.length(); i ++)
    {
        OM_HOList[i].setOffset(newOffsetList[i]);
    }

    return;
}
void HitObjectList::setXAxisList(QList<double> &newXAxisList)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLengthMatch(OM_HOList.length(), newXAxisList.length());

    for (int i = 0; i < newXAxisList.length(); i ++)
    {
        OM_HOList[i].setXAxis(newXAxisList[i]);
    }

    return;
}
void HitObjectList::setColumnList(QList<int> &newColumnList)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLengthMatch(OM_HOList.length(), newColumnList.length());

    for (int i = 0; i < newColumnList.length(); i ++)
    {
        OM_HOList[i].setColumn(newColumnList[i]);
    }

    return;
}
void HitObjectList::setKeys(unsigned short newKeys)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    for (int temp = 0; temp < OM_HOList.length(); temp ++) {
        OM_HOList[temp].setKeys(newKeys);
    }
}

// GETTERS
QList<double> HitObjectList::getOffsetList() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    HitObject OM_HO;
    QList<double> output;
    foreach (OM_HO, OM_HOList)
    {
        output.append(OM_HO.getOffset());
    }

    return output;
}
QList<double> HitObjectList::getUnqOffsetList() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<double> unqOffsetList,
                  offsetList;

    double offset;

    offsetList = getOffsetList();

    foreach (offset, offsetList) {
        if (!unqOffsetList.contains(offset))
        {
            unqOffsetList.append(offset);
        }
    }

    return offsetList;
}
QList<double> HitObjectList::getXAxisList() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    HitObject OM_HO;
    QList<double> output;
    foreach (OM_HO, OM_HOList)
    {
        output.append(OM_HO.getXAxis());
    }

    return output;
}
QList<int> HitObjectList::getColumnList() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    HitObject OM_HO;
    QList<int> output;
    foreach (OM_HO, OM_HOList)
    {
        output.append(OM_HO.getColumn());
    }

    return output;
}
double HitObjectList::getMinOffset() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double HitObjectList::getMaxOffset() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}
double HitObjectList::getLength() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end())
           - *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double HitObjectList::getLength(int index)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    sortOffset(true);

    amberCommon::assertIndex(index, getSize() - 1);

    return OM_HOList[index + 1].getOffset() - OM_HOList[index].getOffset();
}
double HitObjectList::getSize() const
{
    return OM_HOList.count();
}
QStringList HitObjectList::toString() const
{
    HitObject temp;
    QStringList output;

    foreach (temp, OM_HOList) {
        output.append(temp.toString());
    }

    return output;
}

// OPERS
HitObject &HitObjectList::operator [](int i) {
    amberCommon::assertIndex(i, getSize() - 1);
    return OM_HOList[i];
}
HitObject HitObjectList ::operator [](int i) const {
    amberCommon::assertIndex(i, getSize() - 1);
    return OM_HOList[i];
}

// MISC
void HitObjectList::addColumn      (const int rhsInt)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<int> newColumnList,
               oldColumnList;
    int temp;

    oldColumnList = this->getColumnList();

    foreach (temp, oldColumnList) {
        newColumnList.append(temp + rhsInt);
    }

    setColumnList(newColumnList);

    limitColumn();
}
void HitObjectList::subtractColumn (const int rhsInt)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<int> newColumnList,
               oldColumnList;
    int temp;

    oldColumnList = this->getColumnList();

    foreach (temp, oldColumnList) {
        newColumnList.append(temp - rhsInt);
    }

    setColumnList(newColumnList);

    limitColumn();
}

void HitObjectList::multiplyOffset (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp * rhsDouble);
    }

    setOffsetList(newOffsetList);

    if (limitFlag)
    {
        limitOffset();
    }
}
void HitObjectList::divideOffset   (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp / rhsDouble);
    }

    setOffsetList(newOffsetList);

    if (limitFlag)
    {
        limitOffset();
    }
}
void HitObjectList::addOffset      (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp + rhsDouble);
    }

    setOffsetList(newOffsetList);

    if (limitFlag)
    {
        limitOffset();
    }
}
void HitObjectList::subtractOffset (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp - rhsDouble);
    }

    setOffsetList(newOffsetList);

    if (limitFlag)
    {
        limitOffset();
    }
}

void HitObjectList::makeUnique()
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<double> offsetList,
                  newOffsetList;
    QList<HitObject> newHOList;

    offsetList = getOffsetList();

    for (int temp = 0; temp < offsetList.length(); temp++) {
        if (!newOffsetList.contains(offsetList[temp]))
        {
            newOffsetList.append(offsetList[temp]);
            newHOList.append(HitObject(offsetList[temp], OM_HOList[temp].getColumn(), OM_HOList[temp].getKeys()));
        }
    }

    loadHOList(newHOList);
}
void HitObjectList::sortOffset(bool isAscending)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    if (isAscending)
    {
        std::sort(OM_HOList.begin(), OM_HOList.end());
    } else
    {
        std::sort(OM_HOList.rbegin(), OM_HOList.rend());
    }
}
void HitObjectList::limitColumn(int &maxColumn, int &minColumn)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    HitObject temp;

    foreach (temp, OM_HOList)
    {
        temp.limitColumn(maxColumn, minColumn);
    }
}
void HitObjectList::limitColumn()
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    HitObject temp;

    foreach (temp, OM_HOList)
    {
        temp.limitColumn();
    }
}

void HitObjectList::limitOffset(double minOffset, double maxOffset)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    HitObject temp;

    foreach (temp, OM_HOList) {
        temp.limitOffset(minOffset, maxOffset);
    }
}

bool HitObjectList::isEmpty () const
{
    return (getSize() == 0);
}





