#include "timingpointlist.h"

// CONSTRUCTORS
TimingPointList::TimingPointList()
{
    curTimingPointList = {};
    loadFail = false;
}
TimingPointList::TimingPointList(QList<TimingPoint> newTimingPointList) : TimingPointList()
{
    loadTPList(newTimingPointList);
}
TimingPointList::TimingPointList(QTextBrowser *tb) : TimingPointList()
{
    loadTPList(tb);
}
TimingPointList::TimingPointList(QLineEdit *line) : TimingPointList()
{
    loadTPList(line);
}
TimingPointList::TimingPointList(QPlainTextEdit *pte)
{
    loadTPList(pte);
}
TimingPointList::TimingPointList(QString str)
{
    loadTPList(str);
}
TimingPointList::TimingPointList(QStringList strList)
{
    loadTPList(strList);
}

// LOADERS
void TimingPointList::loadTPList(QList<TimingPoint> newTimingPointList)
{
    curTimingPointList = newTimingPointList;
}
void TimingPointList::loadTPList(QTextBrowser *tb)
{
    QString tbText;
    QStringList tbTextSplit;

    tbText = tb->toPlainText();
    tbTextSplit = tbText.split("\n", QString::SkipEmptyParts);
    loadTPList(tbTextSplit);
}
void TimingPointList::loadTPList(QLineEdit *line)
{
    QString lineText;
    lineText = line->text();

    loadTPList(lineText);
}

void TimingPointList::loadTPList(QPlainTextEdit *pte)
{
    QString pteText;
    pteText = pte->toPlainText();

    loadTPList(pteText);
}
void TimingPointList::loadTPList(QString &str)
{
    QStringList strSplit;

    strSplit = str.split("\n", QString::SkipEmptyParts);

    loadTPList(strSplit);
}
void TimingPointList::loadTPList(QStringList &strList)
{
    QString temp;

    amberCommon::assertTP(strList);

    if (!amberCommon::whatOM_Type(strList).getIsTP())
    {
        loadFail = true;
        throw TPLoadFail(QString("Input not TP: ") + strList.join("\n"));
        return;
    }

    foreach (temp, strList) {
        curTimingPointList.append(TimingPoint(temp));
    }
}

// SETTERS
void TimingPointList::setOffsetList(QList<double> newOffsetList)
{ 
    amberCommon::assertLengthMatch(curTimingPointList.length(), newOffsetList.length());

    for (int i = 0; i < newOffsetList.length(); i ++)
    {
        curTimingPointList[i].setOffset(newOffsetList[i]);
    }

    return;
}
void TimingPointList::setCodeList(QList<double> newCodeList)
{
    amberCommon::assertLengthMatch(curTimingPointList.length(), newCodeList.length());

    for (int i = 0; i < newCodeList.length(); i ++)
    {
        curTimingPointList[i].setCode(newCodeList[i]);
    }

    return;
}
void TimingPointList::setValueList(QList<double> newValueList)
{
    amberCommon::assertLengthMatch(curTimingPointList.length(), newValueList.length());

    for (int i = 0; i < newValueList.length(); i ++)
    {
        curTimingPointList[i].setValue(newValueList[i]);
    }

    return;
}

omInfo TimingPointList::getInfo()
{
    QStringList temp = toString();
    return amberCommon::whatTP(temp);
}

// GETTERS
QList<double> TimingPointList::getOffsetList(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

    TimingPoint TimingPoint;
    QList<double> output;
    foreach (TimingPoint, curTimingPointList)
    {
        if (    ((info.getIsBPM()) && TimingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
             || ((info.getIsSV())  && TimingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(TimingPoint.getOffset());
        }        
    }

    return output;
}
QList<double> TimingPointList::getCodeList(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

    TimingPoint TimingPoint;
    QList<double> output;
    foreach (TimingPoint, curTimingPointList)
    {
        if (    ((info.getIsBPM()) && TimingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
             || ((info.getIsSV())  && TimingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(TimingPoint.getCode());
        }
    }

    return output;
}
QList<double> TimingPointList::getValueList(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

    TimingPoint TimingPoint;
    QList<double> output;
    foreach (TimingPoint, curTimingPointList)
    {
        if (    ((info.getIsBPM()) && TimingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
             || ((info.getIsSV())  && TimingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(TimingPoint.getValue());
        }
    }

    return output;
}
QList<double> TimingPointList::getLengthList(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

    // Note: If amberCommon::TPFlag is specified, length calculation will skip some timingPoints
    QList<double> output,
                  offsetList;

    offsetList = getOffsetList(info);

    for (int temp = 0; temp < offsetList.length() - 1; temp++)
    {
        output.append(offsetList[temp + 1] - offsetList[temp]);
    }

    return output;
}
QList<double> TimingPointList::getDistanceList(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

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

QList<double> TimingPointList::getUnqOffsetList(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

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

TimingPointList TimingPointList::splitByType(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        throw amberException(QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    TimingPointList output;

    if (info.getIsSV())
    {
        for (int temp = 0; temp < curTimingPointList.length(); temp++)
        {
            if (!curTimingPointList[temp].getIsSV())
            {
                output.append(curTimingPointList[temp]);
            }
        }
    }
    if (info.getIsBPM())
    {
        for (int temp = 0; temp < curTimingPointList.length(); temp++)
        {
            if (curTimingPointList[temp].getIsBPM())
            {
                output.append(curTimingPointList[temp]);
            }
        }
    }

    return output;
}

double TimingPointList::getMinOffset() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double TimingPointList::getMaxOffset() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}

double TimingPointList::getMinValue(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
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
double TimingPointList::getMaxValue(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
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

double TimingPointList::getLength() const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    double output = 0;
    QList<double> offsetList;

    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end())
           - *std::min_element(offsetList.begin(), offsetList.end());

    return output;
}
double TimingPointList::getLength(int index)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertIndex(index, getSize() - 1);

    sortOffset(true);

    return curTimingPointList[index + 1].getOffset() - curTimingPointList[index].getOffset();
}

int    TimingPointList::getSize(const omInfo &info) const
{
    TimingPoint temp;
    int counter = 0;

    if (info.getIsSV() && info.getIsBPM()) // If user requests both
    {
        counter = curTimingPointList.count();
    }
    else if (info.getIsSV()) // SV Request
    {
        foreach (temp, curTimingPointList)
        {
            if (temp.getIsSV())
            {
                counter ++;
            }
        }
    }
    else if (info.getIsBPM()) // BPM Request
    {
        foreach (temp, curTimingPointList)
        {
            if (temp.getIsBPM())
            {
                counter ++;
            }
        }
    }

    return counter;
}
double TimingPointList::getAverage(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

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
double TimingPointList::getDistance(const omInfo &info) const
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

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
double TimingPointList::getDistance(int index)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    double length,
           value;

    length = getLength(index);
    value  = curTimingPointList[index].getValue();

    return length * value;
}
QStringList TimingPointList::toString() const
{
    TimingPoint temp;
    QStringList output;
    foreach (temp, curTimingPointList) {
        output.append(temp.toString());
    }

    return output;
}

// OPERS
TimingPoint &TimingPointList::operator [](int i) {
    amberCommon::assertIndex(i, getSize() - 1);

    return curTimingPointList[i];
}
TimingPoint TimingPointList::operator [](int i) const {
    amberCommon::assertIndex(i, getSize() - 1);

    return curTimingPointList[i];
}

void TimingPointList::multiplyValue(const TimingPointList rhsTimingPointList, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
    rhsValueList = rhsTimingPointList.getValueList();
    lhsOffsetList = getOffsetList();
    rhsOffsetList = rhsTimingPointList.getOffsetList();
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
void TimingPointList::divideValue(const TimingPointList rhsTimingPointList, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
    rhsValueList = rhsTimingPointList.getValueList();
    lhsOffsetList = getOffsetList();
    rhsOffsetList = rhsTimingPointList.getOffsetList();
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
void TimingPointList::addValue(const TimingPointList rhsTimingPointList, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
    rhsValueList = rhsTimingPointList.getValueList();
    lhsOffsetList = getOffsetList();
    rhsOffsetList = rhsTimingPointList.getOffsetList();
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
void TimingPointList::subtractValue(const TimingPointList rhsTimingPointList, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
    rhsValueList = rhsTimingPointList.getValueList();
    lhsOffsetList = getOffsetList();
    rhsOffsetList = rhsTimingPointList.getOffsetList();
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

void TimingPointList::multiplyValue  (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
void TimingPointList::divideValue    (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
void TimingPointList::addValue       (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
void TimingPointList::subtractValue  (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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

void TimingPointList::multiplyOffset (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
void TimingPointList::divideOffset   (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
void TimingPointList::addOffset      (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
void TimingPointList::subtractOffset (const double rhsDouble, bool limitFlag)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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

void TimingPointList::zero()
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

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
void TimingPointList::sortOffset(bool isAscending)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    if (isAscending)
    {
        std::sort(curTimingPointList.begin(), curTimingPointList.end());
    } else
    {
        std::sort(curTimingPointList.rbegin(), curTimingPointList.rend());
    }
}

void TimingPointList::append(TimingPointList newTimingPointList)
{
    for (int temp = 0; temp < newTimingPointList.getSize(); temp++) {
        curTimingPointList.append(newTimingPointList[temp]);
    }
}

bool TimingPointList::isEmpty() const
{
    return getSize() == 0;
}
void TimingPointList::limitValues(double maxSV, double minSV, double maxBPM, double minBPM)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    TimingPoint temp;

    foreach (temp, curTimingPointList) {
        temp.limitValues(maxSV, minSV, maxBPM, minBPM);
    }
}

void TimingPointList::limitOffset(double minOffset, double maxOffset)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    TimingPoint temp;

    foreach (temp, curTimingPointList) {
        temp.limitOffset(minOffset, maxOffset);
    }
}
QList<int> TimingPointList::indexList(omInfo &info)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        throw amberException(QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    QList<int> indexList;

    for (int counter = 0; counter < curTimingPointList.length(); counter ++)
    {
        if (info.getIsSV())
        {
            if (!curTimingPointList[counter].getIsBPM())
            {
                indexList.append(counter);
            }
        }
        else if (info.getIsBPM())
        {
            if (curTimingPointList[counter].getIsBPM())
            {
                indexList.append(counter);
            }
        }

    }

    return indexList;
}
void TimingPointList::adjustToAverage(double averageSV, int adjustIndex)
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);
    amberCommon::assertLoadFail(getInfo());

    if (getInfo().getIsSV() && getInfo().getIsBPM())
    {
        throw amberException("Only works with SV only or BPM only list");
    }

    // To elaborate what this function does:
    // This function changes a single TP (via adjustIndex) to achieve the specified averageSV
    // This function cannot adjust TP at the end as it doesn't contribute to the average SV

    // If adjusting the TP cannot achieve the specified average SV then it'll fail

    amberCommon::assertIndex(adjustIndex, curTimingPointList.length() - 2); // Cannot adjust last index

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

    newAdjustValue = curTimingPointList[adjustIndex].getValue() + (netDistance / oldAdjustLength);


    if (getInfo().getIsSV())
    {
        if (newAdjustValue > 10.0 || newAdjustValue < 0.1)
        {
            throw amberException(QString(__FUNCTION__) + ": New Value exceeds limit");
        }
    }
    else if (getInfo().getIsBPM())
    {
        if (newAdjustValue < 0)
        {
            throw amberException(QString(__FUNCTION__) + "New Value exceeds limit");
        }
    }

    curTimingPointList[adjustIndex].setValue(newAdjustValue);
    curTimingPointList[adjustIndex].limitValues();
}

void TimingPointList::makeUnique()
{
    amberCommon::assertEmpty(toString(), __FUNCTION__);

    QList<double> offsetList,
                  newOffsetList;
    QList<TimingPoint> newTimingPointList;
    double temp;

    offsetList = getOffsetList();

    foreach (temp, offsetList) {
        if (!newOffsetList.contains(temp))
        {
            newOffsetList.append(temp);
            newTimingPointList.append(TimingPoint(temp,
                                                  curTimingPointList[temp].getValue(),
                                                  curTimingPointList[temp].getIsBPM()));
        }
    }

    loadTPList(newTimingPointList);
}




