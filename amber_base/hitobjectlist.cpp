#include "hitobjectlist.h"

// CONSTRUCTORS
HitObjectList::HitObjectList()
{
    hitObjectList = {};
    loadFail = false;
}
HitObjectList::HitObjectList(QList<HitObject> newHOList)
    : HitObjectList()
{
    loadHOList(newHOList);
}
HitObjectList::HitObjectList(QString EHO, int newKeys)
    : HitObjectList()
{
    loadHOList(EHO, newKeys);
}
HitObjectList::HitObjectList(QTextBrowser* tb, int newKeys)
    : HitObjectList()
{
    loadHOList(tb, newKeys);
}
HitObjectList::HitObjectList(QLineEdit* line, int newKeys)
    : HitObjectList()
{
    loadHOList(line, newKeys);
}
HitObjectList::HitObjectList(QPlainTextEdit* pte, int newKeys)
    : HitObjectList()
{
    loadHOList(pte, newKeys);
}

// LOADERS
void HitObjectList::loadHOList(QList<HitObject> newHOList)
{
    hitObjectList = newHOList;
}
void HitObjectList::loadHOList(QTextBrowser* tb, int newKeys)
{
    QString tbText;

    tbText = tb->toPlainText();

    loadHOList(tbText, newKeys);
}
void HitObjectList::loadHOList(QLineEdit* line, int newKeys)
{
    QString lineText;

    lineText = line->text();

    loadHOList(lineText, newKeys);
}
void HitObjectList::loadHOList(QPlainTextEdit* pte, int newKeys)
{
    QString pteText;

    pteText = pte->toPlainText();

    loadHOList(pteText, newKeys);
}
void HitObjectList::loadHOList(QString& EHOorHO, int newKeys)
{
    bool boolEHO, boolHO;

    Info info;

    info = Common::whatOM_Type(EHOorHO);

    boolEHO = info.getIsEHO();
    boolHO = info.getIsHO();

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

        AExc(AExc::HO_LOADFAIL, QString("Input: ") + EHOorHO);
        return;
    }
}
void HitObjectList::loadHOList(QStringList& HOList, int newKeys)
{
    QString HO;
    foreach (HO, HOList)
    {
        hitObjectList.append(HitObject(HO, newKeys));
    }

    return;
}
void HitObjectList::loadEHOList(QString& EHO, int newKeys)
{
    // !! DO NOT CALL THIS DIRECTLY
    // Load via loadHOList (QString, int)
    QString EHO_trim, EHO_eachSplitComma;
    QStringList EHO_splitComma;
    QList<double> EHO_splitPipeOffset;
    QList<int> EHO_splitPipeColumn;
    int openBracketIndex, closeBracketIndex;

    openBracketIndex = EHO.indexOf("(");
    closeBracketIndex = EHO.indexOf(")");

    EHO_trim = EHO.mid(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

    EHO_splitComma = EHO_trim.split(",", QString::SkipEmptyParts);

    foreach (EHO_eachSplitComma, EHO_splitComma)
    {
        EHO_splitPipeOffset.append(EHO_eachSplitComma.split("|")[0].toDouble());
        EHO_splitPipeColumn.append(EHO_eachSplitComma.split("|")[1].toInt());
    }

    for (int temp = 0; temp < EHO_splitPipeColumn.size(); temp++)
    {
        hitObjectList.append(
            HitObject(EHO_splitPipeOffset[temp], EHO_splitPipeColumn[temp], newKeys));
    }
}

// SETTERS
void HitObjectList::setOffsetList(const QList<double>& newOffsetList)
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLengthMatch(hitObjectList.length(), newOffsetList.length());

    for (int i = 0; i < newOffsetList.length(); i++)
    {
        hitObjectList[i].setOffset(newOffsetList[i]);
    }

    return;
}
void HitObjectList::setXAxisList(const QList<double>& newXAxisList)
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLengthMatch(hitObjectList.length(), newXAxisList.length());

    for (int i = 0; i < newXAxisList.length(); i++)
    {
        hitObjectList[i].setXAxis(newXAxisList[i]);
    }

    return;
}
void HitObjectList::setColumnList(const QList<int>& newColumnList)
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLengthMatch(hitObjectList.length(), newColumnList.length());

    for (int i = 0; i < newColumnList.length(); i++)
    {
        hitObjectList[i].setColumn(newColumnList[i]);
    }

    return;
}
void HitObjectList::setKeys(const int& newKeys)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    for (int temp = 0; temp < hitObjectList.length(); temp++)
    {
        hitObjectList[temp].setKeys(newKeys);
    }
}

// GETTERS
QList<double> HitObjectList::getOffsetList() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    HitObject OM_HO;
    QList<double> output;
    foreach (OM_HO, hitObjectList)
    {
        output.append(OM_HO.getOffset());
    }

    return output;
}
QList<double> HitObjectList::getUnqOffsetList() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> unqOffsetList, offsetList;

    double offset;

    offsetList = getOffsetList();

    foreach (offset, offsetList)
    {
        if (!unqOffsetList.contains(offset))
        {
            unqOffsetList.append(offset);
        }
    }

    return offsetList;
}
QList<double> HitObjectList::getXAxisList() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    HitObject OM_HO;
    QList<double> output;
    foreach (OM_HO, hitObjectList)
    {
        output.append(OM_HO.getXAxis());
    }

    return output;
}
QList<int> HitObjectList::getColumnList() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    HitObject OM_HO;
    QList<int> output;
    foreach (OM_HO, hitObjectList)
    {
        output.append(OM_HO.getColumn());
    }

    return output;
}
double HitObjectList::getMinOffset() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double HitObjectList::getMaxOffset() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}
double HitObjectList::getLength() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end())
        - *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double HitObjectList::getLength(const int& index)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    sortOffset(true);

    Common::assertIndex(index, getSize() - 1);

    return hitObjectList[index + 1].getOffset() - hitObjectList[index].getOffset();
}
double HitObjectList::getSize() const
{
    return hitObjectList.count();
}
QStringList HitObjectList::toString() const
{
    HitObject temp;
    QStringList output;

    foreach (temp, hitObjectList)
    {
        output.append(temp.toString());
    }

    return output;
}

// OPERS
HitObject& HitObjectList::operator[](int i)
{
    if (i >= getSize())
    {
        AExc(AExc::INDEX_OUT_OF_RANGE, QString("Within HitObjectList\n"
                                               "Access: %1\n"
                                               "Last i: %2")
                                           .arg(i)
                                           .arg(getSize() - 1));
        return *(new HitObject());
    }
    return hitObjectList[i];
}
HitObject HitObjectList::operator[](int i) const
{
    if (i >= getSize())
    {
        AExc(AExc::INDEX_OUT_OF_RANGE, QString("Within HitObjectList\n"
                                               "Access: %1\n"
                                               "Last i: %2")
                                           .arg(i)
                                           .arg(getSize() - 1));
        return HitObject();
    }
    return hitObjectList[i];
}

// MISC
void HitObjectList::addColumn(const int& rhsInt)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<int> newColumnList, oldColumnList;
    int temp;

    oldColumnList = this->getColumnList();

    foreach (temp, oldColumnList)
    {
        newColumnList.append(temp + rhsInt);
    }

    setColumnList(newColumnList);

    limitColumn();
}
void HitObjectList::subtractColumn(const int& rhsInt)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<int> newColumnList, oldColumnList;
    int temp;

    oldColumnList = this->getColumnList();

    foreach (temp, oldColumnList)
    {
        newColumnList.append(temp - rhsInt);
    }

    setColumnList(newColumnList);

    limitColumn();
}

void HitObjectList::multiplyOffset(const double& rhsDouble, const bool& limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp * rhsDouble);
    }

    setOffsetList(newOffsetList);

    if (limitFlag)
    {
        limitOffset();
    }
}
void HitObjectList::divideOffset(const double& rhsDouble, const bool& limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp / rhsDouble);
    }

    setOffsetList(newOffsetList);

    if (limitFlag)
    {
        limitOffset();
    }
}
void HitObjectList::addOffset(const double& rhsDouble, const bool& limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp + rhsDouble);
    }

    setOffsetList(newOffsetList);

    if (limitFlag)
    {
        limitOffset();
    }
}
void HitObjectList::subtractOffset(const double& rhsDouble, const bool& limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList)
    {
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
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> offsetList, newOffsetList;
    QList<HitObject> newHOList;

    offsetList = getOffsetList();

    for (int temp = 0; temp < offsetList.length(); temp++)
    {
        if (!newOffsetList.contains(offsetList[temp]))
        {
            newOffsetList.append(offsetList[temp]);
            newHOList.append(HitObject(
                offsetList[temp], hitObjectList[temp].getColumn(), hitObjectList[temp].getKeys()));
        }
    }

    loadHOList(newHOList);
}
void HitObjectList::sortOffset(const bool& isAscending)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    if (isAscending)
    {
        std::sort(hitObjectList.begin(), hitObjectList.end());
    }
    else
    {
        std::sort(hitObjectList.rbegin(), hitObjectList.rend());
    }
}
void HitObjectList::limitColumn(const int& maxColumn, const int& minColumn)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    HitObject temp;

    foreach (temp, hitObjectList)
    {
        temp.limitColumn(maxColumn, minColumn);
    }
}
void HitObjectList::limitColumn()
{
    Common::assertEmpty(toString(), __FUNCTION__);

    HitObject temp;

    foreach (temp, hitObjectList)
    {
        temp.limitColumn();
    }
}

void HitObjectList::limitOffset(const double& minOffset, const double& maxOffset)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    HitObject temp;

    foreach (temp, hitObjectList)
    {
        temp.limitOffset(minOffset, maxOffset);
    }
}

bool HitObjectList::isEmpty() const
{
    return (getSize() == 0);
}
