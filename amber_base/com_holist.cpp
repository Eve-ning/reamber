#include "com_holist.h"

// CONSTRUCTORS
cOM_HOList::cOM_HOList()
{
    OM_HOList = {};
    loadFail  = false;
}
cOM_HOList::cOM_HOList(QList<cOM_HO> newOM_HOList) : cOM_HOList()
{
    loadHOList(newOM_HOList);
}
cOM_HOList::cOM_HOList(QString EHO, int newKeys) : cOM_HOList()
{
    loadHOList(EHO, newKeys);
}
cOM_HOList::cOM_HOList(QTextBrowser *tb, int newKeys) : cOM_HOList()
{
    loadHOList(tb, newKeys);
}
cOM_HOList::cOM_HOList(QLineEdit *line, int newKeys) : cOM_HOList()
{
    loadHOList(line, newKeys);
}
cOM_HOList::cOM_HOList(QPlainTextEdit *pte, int newKeys) : cOM_HOList()
{
    loadHOList(pte, newKeys);
}

// LOADERS
void cOM_HOList::loadHOList(QList<cOM_HO> newOM_HOList)
{
    OM_HOList = newOM_HOList;
}
void cOM_HOList::loadHOList(QTextBrowser *tb, int newKeys)
{
    QString tbText;

    tbText = tb->toPlainText();

    loadHOList(tbText, newKeys);
}
void cOM_HOList::loadHOList(QLineEdit *line, int newKeys)
{
    QString lineText;

    lineText = line->text();

    loadHOList(lineText, newKeys);
}
void cOM_HOList::loadHOList(QPlainTextEdit *pte, int newKeys)
{
    QString pteText;

    pteText = pte->toPlainText();

    loadHOList(pteText, newKeys);
}
void cOM_HOList::loadHOList(QString &EHOorHO, int newKeys)
{
    bool boolEHO,
         boolHO;

    omInfo info();

    cOM_Common::whatOM_Type(info, EHOorHO);

    boolEHO = info.getIsEHO();
    boolHO  = info.getIsHO();

    // IF NOT HO CALL EHO
    if (boolEHO)
    {
        loadEHOList(EHOorHO, newKeys); // Pass to EHO Handler
        return;
    }
    else if (boolHO)
    {
        // Convert to StringList and pass towards QStringList Handler
        QStringList HOList;
        HOList = EHOorHO.split("\n", QString::SkipEmptyParts);

        loadHOList(HOList); // Pass to QStringList Handler
    }
    else
    {
        cOM_Common::assertInvalidFormat(EHOorHO);
        loadFail = true;
        return;
    }
}
void cOM_HOList::loadHOList(QStringList &HOList, int newKeys)
{
    QString HO;
    foreach (HO, HOList) {
        OM_HOList.append(cOM_HO(HO, newKeys));
    }

    return;
}
void cOM_HOList::loadEHOList(QString &EHO, int newKeys)
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
        OM_HOList.append(cOM_HO(EHO_splitPipeOffset[temp],
                                EHO_splitPipeColumn[temp],
                                newKeys));
    }
}

// SETTERS
void cOM_HOList::setOffsetList(QList<double> &newOffsetList)
{
    cOM_Common::assertEmpty(OM_HOList);
    cOM_Common::assertLengthMatch(OM_HOList.length(), newOffsetList.length());

    for (int i = 0; i < newOffsetList.length(); i ++)
    {
        OM_HOList[i].setOffset(newOffsetList[i]);
    }

    return;
}
void cOM_HOList::setXAxisList(QList<double> &newXAxisList)
{
    cOM_Common::assertEmpty(OM_HOList);
    cOM_Common::assertLengthMatch(OM_HOList.length(), newXAxisList.length());

    for (int i = 0; i < newXAxisList.length(); i ++)
    {
        OM_HOList[i].setXAxis(newXAxisList[i]);
    }

    return;
}
void cOM_HOList::setColumnList(QList<int> &newColumnList)
{
    cOM_Common::assertEmpty(OM_HOList);
    cOM_Common::assertLengthMatch(OM_HOList.length(), newColumnList.length());

    for (int i = 0; i < newColumnList.length(); i ++)
    {
        OM_HOList[i].setColumn(newColumnList[i]);
    }

    return;
}
void cOM_HOList::setKeys(unsigned short newKeys)
{
    cOM_Common::assertEmpty(OM_HOList);

    for (int temp = 0; temp < OM_HOList.length(); temp ++) {
        OM_HOList[temp].setKeys(newKeys);
    }
}

// GETTERS
QList<double> cOM_HOList::getOffsetList() const
{
    cOM_Common::assertEmpty(OM_HOList);

    cOM_HO OM_HO;
    QList<double> output;
    foreach (OM_HO, OM_HOList)
    {
        output.append(OM_HO.getOffset());
    }

    return output;
}
QList<double> cOM_HOList::getUnqOffsetList() const
{
    cOM_Common::assertEmpty(OM_HOList);

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
QList<double> cOM_HOList::getXAxisList() const
{
    cOM_Common::assertEmpty(OM_HOList);

    cOM_HO OM_HO;
    QList<double> output;
    foreach (OM_HO, OM_HOList)
    {
        output.append(OM_HO.getXAxis());
    }

    return output;
}
QList<int> cOM_HOList::getColumnList() const
{
    cOM_Common::assertEmpty(OM_HOList);

    cOM_HO OM_HO;
    QList<int> output;
    foreach (OM_HO, OM_HOList)
    {
        output.append(OM_HO.getColumn());
    }

    return output;
}
double cOM_HOList::getMinOffset() const
{
    cOM_Common::assertEmpty(OM_HOList);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double cOM_HOList::getMaxOffset() const
{
    cOM_Common::assertEmpty(OM_HOList);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}
double cOM_HOList::getLength() const
{
    cOM_Common::assertEmpty(OM_HOList);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end())
           - *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double cOM_HOList::getLength(int index)
{
    cOM_Common::assertEmpty(OM_HOList);

    sortOffset(true);

    cOM_Common::assertIndex(index, getSize());

    return OM_HOList[index + 1].getOffset() - OM_HOList[index].getOffset();
}
double cOM_HOList::getSize() const
{
    return OM_HOList.count();
}
QStringList cOM_HOList::toString() const
{
    cOM_Common::assertEmpty(OM_HOList);

    cOM_HO temp;
    QStringList output;

    foreach (temp, OM_HOList) {
        output.append(temp.toString());
    }

    return output;
}

// OPERS
cOM_HO &cOM_HOList::operator [](int i) {
    if (i < OM_HOList.count()){
        return OM_HOList[i];
    } else {
        cOM_Common::assertIndex(i, getSize());
        return OM_HOList[0];
    }
}
cOM_HO cOM_HOList ::operator [](int i) const {
    if (i < OM_HOList.count()){
        return OM_HOList[i];
    } else {
        cOM_Common::assertIndex(i, getSize());
        return cOM_HO();
    }
}

// MISC
void cOM_HOList::addColumn      (const int rhsInt)
{
    cOM_Common::assertEmpty(OM_HOList);

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
void cOM_HOList::subtractColumn (const int rhsInt)
{
    cOM_Common::assertEmpty(OM_HOList);

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

void cOM_HOList::multiplyOffset (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(OM_HOList);

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
void cOM_HOList::divideOffset   (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(OM_HOList);

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
void cOM_HOList::addOffset      (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(OM_HOList);

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
void cOM_HOList::subtractOffset (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(OM_HOList);

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

void cOM_HOList::makeUnique()
{
    cOM_Common::assertEmpty(OM_HOList);

    QList<double> offsetList,
                  newOffsetList;
    QList<cOM_HO> newOM_HOList;

    offsetList = getOffsetList();

    for (int temp = 0; temp < offsetList.length(); temp++) {
        if (!newOffsetList.contains(offsetList[temp]))
        {
            newOffsetList.append(offsetList[temp]);
            newOM_HOList.append(cOM_HO(offsetList[temp], OM_HOList[temp].getColumn(), OM_HOList[temp].getKeys()));
        }
    }

    loadHOList(newOM_HOList);
}
void cOM_HOList::sortOffset(bool isAscending)
{
    cOM_Common::assertEmpty(OM_HOList);

    if (isAscending)
    {
        std::sort(OM_HOList.begin(), OM_HOList.end());
    } else
    {
        std::sort(OM_HOList.rbegin(), OM_HOList.rend());
    }
}
void cOM_HOList::limitColumn(int &maxColumn, int &minColumn)
{
    cOM_Common::assertEmpty(OM_HOList);

    cOM_HO temp;

    foreach (temp, OM_HOList)
    {
        temp.limitColumn(maxColumn, minColumn);
    }
}
void cOM_HOList::limitColumn()
{
    cOM_Common::assertEmpty(OM_HOList);

    cOM_HO temp;

    foreach (temp, OM_HOList)
    {
        temp.limitColumn();
    }
}

void cOM_HOList::limitOffset(double minOffset, double maxOffset)
{
    cOM_Common::assertEmpty(OM_HOList);

    cOM_HO temp;

    foreach (temp, OM_HOList) {
        temp.limitOffset(minOffset, maxOffset);
    }
}



bool cOM_HOList::isEmpty () const
{
    return (getSize() == 0);
}





