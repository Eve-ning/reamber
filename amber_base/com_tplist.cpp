#include "com_tplist.h"

// CONSTRUCTORS
cOM_TPList::cOM_TPList()
{
    OM_TPList = {};
    loadFail = false;
}
cOM_TPList::cOM_TPList(QList<cOM_TP> newOM_TPList) : cOM_TPList()
{
    loadTPList(newOM_TPList);
}
cOM_TPList::cOM_TPList(QTextBrowser *tb) : cOM_TPList()
{
    loadTPList(tb);
}
cOM_TPList::cOM_TPList(QLineEdit *line) : cOM_TPList()
{
    loadTPList(line);
}
cOM_TPList::cOM_TPList(QPlainTextEdit *pte)
{
    loadTPList(pte);
}
cOM_TPList::cOM_TPList(QString str)
{
    loadTPList(str);
}
cOM_TPList::cOM_TPList(QStringList strList)
{
    loadTPList(strList);
}

// LOADERS
void cOM_TPList::loadTPList(QList<cOM_TP> newOM_TPList)
{
    OM_TPList = newOM_TPList;
}
void cOM_TPList::loadTPList(QTextBrowser *tb)
{
    QString tbText;
    QStringList tbTextSplit;

    tbText = tb->toPlainText();
    tbTextSplit = tbText.split("\n", QString::SkipEmptyParts);
    loadTPList(tbTextSplit);
}
void cOM_TPList::loadTPList(QLineEdit *line)
{
    QString lineText;
    lineText = line->text();

    loadTPList(lineText);
}

void cOM_TPList::loadTPList(QPlainTextEdit *pte)
{
    QString pteText;
    pteText = pte->toPlainText();

    loadTPList(pteText);
}
void cOM_TPList::loadTPList(QString &str)
{
    QStringList strSplit;

    strSplit = str.split("\n", QString::SkipEmptyParts);

    loadTPList(strSplit);
}
void cOM_TPList::loadTPList(QStringList &strList)
{
    QString temp;

    cOM_Common::assertTP(strList);

    if (!cOM_Common::whatOM_Type(strList).getIsTP())
    {
        loadFail = true;
        throw TPLoadFail(QString("Input not TP: ") + strList.join("\n"));
        return;
    }

    foreach (temp, strList) {
        OM_TPList.append(cOM_TP(temp));
    }
}

// SETTERS
void cOM_TPList::setOffsetList(QList<double> newOffsetList)
{ 
    cOM_Common::assertLengthMatch(OM_TPList.length(), newOffsetList.length());

    for (int i = 0; i < newOffsetList.length(); i ++)
    {
        OM_TPList[i].setOffset(newOffsetList[i]);
    }

    return;
}
void cOM_TPList::setCodeList(QList<double> newCodeList)
{
    cOM_Common::assertLengthMatch(OM_TPList.length(), newCodeList.length());

    for (int i = 0; i < newCodeList.length(); i ++)
    {
        OM_TPList[i].setCode(newCodeList[i]);
    }

    return;
}
void cOM_TPList::setValueList(QList<double> newValueList)
{
    cOM_Common::assertLengthMatch(OM_TPList.length(), newValueList.length());

    for (int i = 0; i < newValueList.length(); i ++)
    {
        OM_TPList[i].setValue(newValueList[i]);
    }

    return;
}

omInfo cOM_TPList::getInfo()
{
    QStringList temp = toString();
    return cOM_Common::whatTP(temp);
}

// GETTERS
QList<double> cOM_TPList::getOffsetList(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    cOM_TP OM_TP;
    QList<double> output;
    foreach (OM_TP, OM_TPList)
    {
        if (    ((info.getIsBPM()) && OM_TP.getIsBPM()) // continue if foreach is BPM and we only accept SV
             || ((info.getIsSV())  && OM_TP.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(OM_TP.getOffset());
        }        
    }

    return output;
}
QList<double> cOM_TPList::getCodeList(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    cOM_TP OM_TP;
    QList<double> output;
    foreach (OM_TP, OM_TPList)
    {
        if (    ((info.getIsBPM()) && OM_TP.getIsBPM()) // continue if foreach is BPM and we only accept SV
             || ((info.getIsSV())  && OM_TP.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(OM_TP.getCode());
        }
    }

    return output;
}
QList<double> cOM_TPList::getValueList(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    cOM_TP OM_TP;
    QList<double> output;
    foreach (OM_TP, OM_TPList)
    {
        if (    ((info.getIsBPM()) && OM_TP.getIsBPM()) // continue if foreach is BPM and we only accept SV
             || ((info.getIsSV())  && OM_TP.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(OM_TP.getValue());
        }
    }

    return output;
}
QList<double> cOM_TPList::getLengthList(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    // Note: If cOM_Common::TPFlag is specified, length calculation will skip some timingPoints
    QList<double> output,
                  offsetList;

    offsetList = getOffsetList(info);

    for (int temp = 0; temp < offsetList.length() - 1; temp++)
    {
        output.append(offsetList[temp + 1] - offsetList[temp]);
    }

    return output;
}
QList<double> cOM_TPList::getDistanceList(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    QList<double> lengthList,
                  valueList,
                  distanceList;

    lengthList = getLengthList(info);
    valueList  = getValueList (info);

    for (int temp = 0; temp < lengthList.length(); temp++)
    {
        distanceList.append(lengthList[temp] * valueList[temp]);
    }

    return distanceList;
}

QList<double> cOM_TPList::getUnqOffsetList(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    QList<double> offsetList,
                  unqOffsetList;

    double offset;

    offsetList = getOffsetList(info);

    foreach (offset, offsetList)
    {
        if (!unqOffsetList.contains(offset))
        {
            unqOffsetList.append(offset);
        }
    }

    return unqOffsetList;
}

cOM_TPList cOM_TPList::splitByType(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        throw amberException(QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    cOM_TPList output;

    if (info.getIsSV())
    {
        for (int temp = 0; temp < OM_TPList.length(); temp++)
        {
            if (!OM_TPList[temp].getIsSV())
            {
                output.append(OM_TPList[temp]);
            }
        }
    }
    if (info.getIsBPM())
    {
        for (int temp = 0; temp < OM_TPList.length(); temp++)
        {
            if (OM_TPList[temp].getIsBPM())
            {
                output.append(OM_TPList[temp]);
            }
        }
    }

    return output;
}

double cOM_TPList::getMinOffset() const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double cOM_TPList::getMaxOffset() const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}

double cOM_TPList::getMinValue(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    if (info.getIsSV() && info.getIsBPM())
    {
        throw amberException(QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output;
    QList<double> valueList;
    valueList = getValueList(info);

    output = *std::min_element(valueList.begin(), valueList.end());
    return output;
}
double cOM_TPList::getMaxValue(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    if (info.getIsSV() && info.getIsBPM())
    {
        throw amberException(QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output;
    QList<double> valueList;
    valueList = getValueList(info);

    output = *std::max_element(valueList.begin(), valueList.end());
    return output;
}

double cOM_TPList::getLength() const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    double output = 0;
    QList<double> offsetList;

    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end())
           - *std::min_element(offsetList.begin(), offsetList.end());

    return output;
}
double cOM_TPList::getLength(int index)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertIndex(index, getSize() - 1);

    sortOffset(true);

    return OM_TPList[index + 1].getOffset() - OM_TPList[index].getOffset();
}

int    cOM_TPList::getSize(const omInfo &info) const
{
    cOM_TP temp;
    int counter = 0;

    if (info.getIsSV() && info.getIsBPM()) // If user requests both
    {
        counter = OM_TPList.count();
    }
    else if (info.getIsSV()) // SV Request
    {
        foreach (temp, OM_TPList)
        {
            if (temp.getIsSV())
            {
                counter ++;
            }
        }
    }
    else if (info.getIsBPM()) // BPM Request
    {
        foreach (temp, OM_TPList)
        {
            if (temp.getIsBPM())
            {
                counter ++;
            }
        }
    }

    return counter;
}
double cOM_TPList::getAverage(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        throw amberException(QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output = 0;
    QList<double> TPList;
    double TPeach;

    TPList = getValueList(info);

    foreach (TPeach, TPList) {
        output += TPeach;
    }

    output /= TPList.count();
    return output;
}
double cOM_TPList::getDistance(const omInfo &info) const
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        throw amberException(QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    QList<double> lengthList,
                  valueList;
    double        distance;

    lengthList = getLengthList(info);
    valueList  = getValueList (info);

    for (int temp = 0; temp < lengthList.length(); temp++)
    {
        distance += lengthList[temp] * valueList[temp];
    }

    return distance;
}
double cOM_TPList::getDistance(int index)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    double length,
           value;

    length = getLength(index);
    value  = OM_TPList[index].getValue();

    return length * value;
}
QStringList cOM_TPList::toString() const
{
    cOM_TP temp;
    QStringList output;
    foreach (temp, OM_TPList) {
        output.append(temp.toString());
    }

    return output;
}

// OPERS
cOM_TP &cOM_TPList::operator [](int i) {
    cOM_Common::assertIndex(i, getSize() - 1);

    return OM_TPList[i];
}
cOM_TP cOM_TPList::operator [](int i) const {
    cOM_Common::assertIndex(i, getSize() - 1);

    return OM_TPList[i];
}

void cOM_TPList::multiplyValue(const cOM_TPList rhsOM_TPList, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> lhsValueList,
                  rhsValueList,
                  lhsOffsetList,
                  rhsOffsetList;
    int lhsTemp,
        rhsTemp;

    /* Visualization
     *
     * Input
     * LHS | |1| |2|1| |
     * RHS |2| |1| |2|1|
     *
     * Result
     * LHS | |2| |2|2| |
     *
     */

    lhsTemp = rhsTemp = 0;

    lhsValueList = getValueList();
    rhsValueList = rhsOM_TPList.getValueList();
    lhsOffsetList = getOffsetList();
    rhsOffsetList = rhsOM_TPList.getOffsetList();
    rhsOffsetList.append(9999999); // Append to prevent out of index

    /* CONDITION 1 <LHS FIRST>
     * LHS |A| |
     * RHS | |B|
     */
    while (lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp])
    {
        lhsTemp++;
    }

    while (rhsTemp < rhsValueList.length())
    {
        /* CONDITION 2 <RHS FIRST / EQUAL>
         * LHS | |A|
         * RHS |B| |
         *
         * LHS |A| |
         * RHS |B| |
         */
        while (lhsTemp < lhsValueList.length() &&
               rhsTemp < rhsValueList.length() &&
               lhsOffsetList[lhsTemp] >= rhsOffsetList[rhsTemp] &&
               lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp + 1])
        {
            qDebug() << "lhsTemp            : " << lhsTemp << "\n"
                     << "rhsTemp            : " << rhsTemp << "\n"
                     << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << "\n"
                     << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << "\n"
                     << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << "\n"
                     << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << "\n";

            lhsValueList[lhsTemp] *= rhsValueList[rhsTemp];

            qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << "\n"
                     << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << "\n";

            lhsTemp ++;
        }
        rhsTemp ++;
    }
    setValueList(lhsValueList);

    if (limitFlag)
    {
        limitValues();
    }
    return;
}
void cOM_TPList::divideValue(const cOM_TPList rhsOM_TPList, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> lhsValueList,
                  rhsValueList,
                  lhsOffsetList,
                  rhsOffsetList;
    int lhsTemp,
        rhsTemp;

    /* Visualization
     *
     * Input
     * LHS | |1| |2|1| |
     * RHS |2| |1| |2|1|
     *
     * Result
     * LHS | |2| |2|2| |
     *
     */

    lhsTemp = rhsTemp = 0;

    lhsValueList = getValueList();
    rhsValueList = rhsOM_TPList.getValueList();
    lhsOffsetList = getOffsetList();
    rhsOffsetList = rhsOM_TPList.getOffsetList();
    rhsOffsetList.append(9999999); // Append to prevent out of index

    /* CONDITION 1 <LHS FIRST>
     * LHS |A| |
     * RHS | |B|
     */
    while (lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp])
    {
        lhsTemp++;
    }

    while (rhsTemp < rhsValueList.length())
    {
        /* CONDITION 2 <RHS FIRST / EQUAL>
         * LHS | |A|
         * RHS |B| |
         *
         * LHS |A| |
         * RHS |B| |
         */
        while (lhsTemp < lhsValueList.length() &&
               rhsTemp < rhsValueList.length() &&
               lhsOffsetList[lhsTemp] >= rhsOffsetList[rhsTemp] &&
               lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp + 1])
        {
//            qDebug() << "lhsTemp            : " << lhsTemp << "\n"
//                     << "rhsTemp            : " << rhsTemp << "\n"
//                     << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << "\n"
//                     << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << "\n"
//                     << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << "\n"
//                     << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << "\n";

            lhsValueList[lhsTemp] /= rhsValueList[rhsTemp];

//            qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << "\n"
//                     << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << "\n";

            lhsTemp ++;
        }
        rhsTemp ++;
    }
    setValueList(lhsValueList);

    if (limitFlag)
    {
        limitValues();
    }
    return;
}
void cOM_TPList::addValue(const cOM_TPList rhsOM_TPList, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> lhsValueList,
                  rhsValueList,
                  lhsOffsetList,
                  rhsOffsetList;
    int lhsTemp,
        rhsTemp;

    /* Visualization
     *
     * Input
     * LHS | |1| |2|1| |
     * RHS |3| |1| |2|1|
     *
     * Result
     * LHS | |4| |3|3| |
     *
     */

    lhsTemp = rhsTemp = 0;

    lhsValueList = getValueList();
    rhsValueList = rhsOM_TPList.getValueList();
    lhsOffsetList = getOffsetList();
    rhsOffsetList = rhsOM_TPList.getOffsetList();
    rhsOffsetList.append(9999999); // Append to prevent out of index

    /* CONDITION 1 <LHS FIRST>
     * LHS |A| |
     * RHS | |B|
     */
    while (lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp])
    {
        lhsTemp++;
    }

    while (rhsTemp < rhsValueList.length())
    {
        /* CONDITION 2 <RHS FIRST / EQUAL>
         * LHS | |A|
         * RHS |B| |
         *
         * LHS |A| |
         * RHS |B| |
         */
        while (lhsTemp < lhsValueList.length() &&
               rhsTemp < rhsValueList.length() &&
               lhsOffsetList[lhsTemp] >= rhsOffsetList[rhsTemp] &&
               lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp + 1])
        {
//            qDebug() << "lhsTemp            : " << lhsTemp << "\n"
//                     << "rhsTemp            : " << rhsTemp << "\n"
//                     << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << "\n"
//                     << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << "\n"
//                     << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << "\n"
//                     << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << "\n";

            lhsValueList[lhsTemp] += rhsValueList[rhsTemp];

//            qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << "\n"
//                     << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << "\n";

            lhsTemp ++;
        }
        rhsTemp ++;
    }
    setValueList(lhsValueList);

    if (limitFlag)
    {
        limitValues();
    }
    return;
}
void cOM_TPList::subtractValue(const cOM_TPList rhsOM_TPList, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> lhsValueList,
                  rhsValueList,
                  lhsOffsetList,
                  rhsOffsetList;
    int lhsTemp,
        rhsTemp;

    /* Visualization
     *
     * Input
     * LHS | |1| |2|1| |
     * RHS |3| |1| |2|1|
     *
     * Result
     * LHS | |4| |3|3| |
     *
     */

    lhsTemp = rhsTemp = 0;

    lhsValueList = getValueList();
    rhsValueList = rhsOM_TPList.getValueList();
    lhsOffsetList = getOffsetList();
    rhsOffsetList = rhsOM_TPList.getOffsetList();
    rhsOffsetList.append(9999999); // Append to prevent out of index

    /* CONDITION 1 <LHS FIRST>
     * LHS |A| |
     * RHS | |B|
     */
    while (lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp])
    {
        lhsTemp++;
    }

    while (rhsTemp < rhsValueList.length())
    {
        /* CONDITION 2 <RHS FIRST / EQUAL>
         * LHS | |A|
         * RHS |B| |
         *
         * LHS |A| |
         * RHS |B| |
         */
        while (lhsTemp < lhsValueList.length() &&
               rhsTemp < rhsValueList.length() &&
               lhsOffsetList[lhsTemp] >= rhsOffsetList[rhsTemp] &&
               lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp + 1])
        {
//            qDebug() << "lhsTemp            : " << lhsTemp << "\n"
//                     << "rhsTemp            : " << rhsTemp << "\n"
//                     << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << "\n"
//                     << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << "\n"
//                     << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << "\n"
//                     << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << "\n";

            lhsValueList[lhsTemp] -= rhsValueList[rhsTemp];

//            qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << "\n"
//                     << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << "\n";

            lhsTemp ++;
        }
        rhsTemp ++;
    }
    setValueList(lhsValueList);

    if (limitFlag)
    {
        limitValues();
    }
    return;
}

void cOM_TPList::multiplyValue  (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newValueList,
                  oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList) {
        newValueList.append(temp * rhsDouble);
    }

    setValueList(newValueList);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TPList::divideValue    (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newValueList,
                  oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList) {
        newValueList.append(temp / rhsDouble);
    }

    setValueList(newValueList);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TPList::addValue       (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newValueList,
                  oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList) {
        newValueList.append(temp + rhsDouble);
    }

    setValueList(newValueList);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TPList::subtractValue  (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newValueList,
                  oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList) {
        newValueList.append(temp - rhsDouble);
    }

    setValueList(newValueList);
    if (limitFlag)
    {
        limitValues();
    }
}

void cOM_TPList::multiplyOffset (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp * rhsDouble);
    }

    setOffsetList(newOffsetList);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TPList::divideOffset   (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp / rhsDouble);
    }

    setOffsetList(newOffsetList);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TPList::addOffset      (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp + rhsDouble);
    }

    setOffsetList(newOffsetList);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TPList::subtractOffset (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp - rhsDouble);
    }

    setOffsetList(newOffsetList);
    if (limitFlag)
    {
        limitValues();
    }
}

void cOM_TPList::zero()
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList,
                  oldOffsetList;

    double temp,
           min;

    min = getMinOffset();

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList) {
        newOffsetList.append(temp - min);
    }

    setOffsetList(newOffsetList);
}

// MISC
void cOM_TPList::sortOffset(bool isAscending)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    if (isAscending)
    {
        std::sort(OM_TPList.begin(), OM_TPList.end());
    } else
    {
        std::sort(OM_TPList.rbegin(), OM_TPList.rend());
    }
}

void cOM_TPList::append(cOM_TPList newOM_TPList)
{
    for (int temp = 0; temp < newOM_TPList.getSize(); temp++) {
        OM_TPList.append(newOM_TPList[temp]);
    }
}

bool cOM_TPList::isEmpty() const
{
    return getSize() == 0;
}
void cOM_TPList::limitValues(double maxSV, double minSV, double maxBPM, double minBPM)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    cOM_TP temp;

    foreach (temp, OM_TPList) {
        temp.limitValues(maxSV, minSV, maxBPM, minBPM);
    }
}

void cOM_TPList::limitOffset(double minOffset, double maxOffset)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    cOM_TP temp;

    foreach (temp, OM_TPList) {
        temp.limitOffset(minOffset, maxOffset);
    }
}
QList<int> cOM_TPList::indexList(omInfo &info)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        throw amberException(QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    QList<int> indexList;

    for (int counter = 0; counter < OM_TPList.length(); counter ++)
    {
        if (info.getIsSV())
        {
            if (!OM_TPList[counter].getIsBPM())
            {
                indexList.append(counter);
            }
        }
        else if (info.getIsBPM())
        {
            if (OM_TPList[counter].getIsBPM())
            {
                indexList.append(counter);
            }
        }

    }

    return indexList;
}
void cOM_TPList::adjustToAverage(double averageSV, int adjustIndex)
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);
    cOM_Common::assertLoadFail(getInfo());

    if (getInfo().getIsSV() && getInfo().getIsBPM())
    {
        throw amberException("Only works with SV only or BPM only list");
    }

    // To elaborate what this function does:
    // This function changes a single TP (via adjustIndex) to achieve the specified averageSV
    // This function cannot adjust TP at the end as it doesn't contribute to the average SV

    // If adjusting the TP cannot achieve the specified average SV then it'll fail

    cOM_Common::assertIndex(adjustIndex, OM_TPList.length() - 2); // Cannot adjust last index

    double oldTotalDistance,
           newTotalDistance,
           oldAdjustLength,
           newAdjustValue,
           netDistance; // otherDistance as in the distance covered by other TP(s)
                        // I can't find a better wording for this

    // TOTAL LENGTH = 70000
    // NEW AVE = 1.0
    // OLD AVE = 1.075

    oldTotalDistance = getDistance(getInfo());
    newTotalDistance = averageSV * getLength();

    // We calculate the distance that needs to be added/subtracted
    netDistance = newTotalDistance - oldTotalDistance;
    oldAdjustLength = getLength(adjustIndex);

    newAdjustValue = OM_TPList[adjustIndex].getValue() + (netDistance / oldAdjustLength);


    if (getInfo().getIsSV())
    {
        if (newAdjustValue > 10.0 || newAdjustValue < 0.1)
        {
            throw amberException(QString(__FUNCTION__) + ": New Value exceeds limit");
        }
    }
    else if (getInfo().getIsSV())
    {
        if (newAdjustValue < 0)
        {
            throw amberException(QString(__FUNCTION__) + "New Value exceeds limit");
        }
    }

    OM_TPList[adjustIndex].setValue(newAdjustValue);
    OM_TPList[adjustIndex].limitValues();
}

void cOM_TPList::makeUnique()
{
    cOM_Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> offsetList,
                  newOffsetList;
    QList<cOM_TP> newOM_TPList;
    double temp;

    offsetList = getOffsetList();

    foreach (temp, offsetList) {
        if (!newOffsetList.contains(temp))
        {
            newOffsetList.append(temp);
            newOM_TPList.append(cOM_TP(temp, OM_TPList[temp].getValue()));
        }
    }

    loadTPList(newOM_TPList);
}




