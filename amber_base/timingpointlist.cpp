#include "timingpointlist.h"

// CONSTRUCTORS
TimingPointList::TimingPointList()
{
    timingPointList = {};
    loadFail = false;
}
TimingPointList::TimingPointList(QList<TimingPoint> newTimingPointList)
    : TimingPointList()
{
    loadTPList(newTimingPointList);
}
TimingPointList::TimingPointList(QTextBrowser* tb)
    : TimingPointList()
{
    loadTPList(tb);
}
TimingPointList::TimingPointList(QLineEdit* line)
    : TimingPointList()
{
    loadTPList(line);
}
TimingPointList::TimingPointList(QPlainTextEdit* pte)
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
    timingPointList = newTimingPointList;
}
void TimingPointList::loadTPList(QTextBrowser* tb)
{
    QString tbText;
    QStringList tbTextSplit;

    tbText = tb->toPlainText();
    tbTextSplit = tbText.split("\n", QString::SkipEmptyParts);
    loadTPList(tbTextSplit);
}
void TimingPointList::loadTPList(QLineEdit* line)
{
    QString lineText;
    lineText = line->text();

    loadTPList(lineText);
}

void TimingPointList::loadTPList(QPlainTextEdit* pte)
{
    QString pteText;
    pteText = pte->toPlainText();

    loadTPList(pteText);
}
void TimingPointList::loadTPList(QString& str)
{
    QStringList strSplit;

    strSplit = str.split("\n", QString::SkipEmptyParts);

    loadTPList(strSplit);
}
void TimingPointList::loadTPList(QStringList& strList)
{
    QString temp;

    Common::assertTP(strList);

    if (!Common::whatOM_Type(strList).getIsTP())
    {
        loadFail = true;
        AExc(AExc::TP_LOADFAIL, QString("Input:\n") + strList.join("\n"));
        return;
    }

    foreach (temp, strList)
    {
        timingPointList.append(TimingPoint(temp));
    }
}

// SETTERS
void TimingPointList::setOffsetList(QList<double> offsetList_)
{
    Common::assertLengthMatch(timingPointList.length(), offsetList_.length());

    for (int i = 0; i < offsetList_.length(); i++)
    {
        timingPointList[i].setOffset(offsetList_[i]);
    }

    return;
}
void TimingPointList::setCodeList(QList<double> codeList_)
{
    Common::assertLengthMatch(timingPointList.length(), codeList_.length());

    for (int i = 0; i < codeList_.length(); i++)
    {
        timingPointList[i].setCode(codeList_[i]);
    }

    return;
}
void TimingPointList::setValueList(QList<double> valueList_)
{
    Common::assertLengthMatch(timingPointList.length(), valueList_.length());

    for (int i = 0; i < valueList_.length(); i++)
    {
        timingPointList[i].setValue(valueList_[i]);
    }

    return;
}

Info TimingPointList::getInfo()
{
    QStringList temp = toString();
    return Common::whatTP(temp);
}

// GETTERS
QList<double> TimingPointList::getOffsetList(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    TimingPoint TimingPoint;
    QList<double> output;
    foreach (TimingPoint, timingPointList)
    {
        if (((info.getIsBPM())
                && TimingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
            || ((info.getIsSV())
                   && TimingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(TimingPoint.getOffset());
        }
    }

    return output;
}
QList<double> TimingPointList::getCodeList(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    TimingPoint TimingPoint;
    QList<double> output;
    foreach (TimingPoint, timingPointList)
    {
        if (((info.getIsBPM())
                && TimingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
            || ((info.getIsSV())
                   && TimingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(TimingPoint.getCode());
        }
    }

    return output;
}
QList<double> TimingPointList::getValueList(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    TimingPoint TimingPoint;
    QList<double> output;
    foreach (TimingPoint, timingPointList)
    {
        if (((info.getIsBPM())
                && TimingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
            || ((info.getIsSV())
                   && TimingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(TimingPoint.getValue());
        }
    }

    return output;
}
QList<double> TimingPointList::getLengthList(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    // Note: If amberCommon::TPFlag is specified, length calculation will skip some timingPoints
    QList<double> output, offsetList;

    offsetList = getOffsetList(info);

    for (int temp = 0; temp < offsetList.length() - 1; temp++)
    {
        output.append(offsetList[temp + 1] - offsetList[temp]);
    }

    return output;
}
QList<double> TimingPointList::getDistanceList(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    QList<double> lengthList, valueList, distanceList;

    lengthList = getLengthList(info);
    valueList = getValueList(info);

    for (int temp = 0; temp < lengthList.length(); temp++)
    {
        distanceList.append(lengthList[temp] * valueList[temp]);
    }

    return distanceList;
}

QList<double> TimingPointList::getUnqOffsetList(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    QList<double> offsetList, unqOffsetList;

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

TimingPointList TimingPointList::splitByType(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        AExc(AExc::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    TimingPointList output;

    if (info.getIsSV())
    {
        for (int temp = 0; temp < timingPointList.length(); temp++)
        {
            if (!timingPointList[temp].getIsSV())
            {
                output.append(timingPointList[temp]);
            }
        }
    }
    if (info.getIsBPM())
    {
        for (int temp = 0; temp < timingPointList.length(); temp++)
        {
            if (timingPointList[temp].getIsBPM())
            {
                output.append(timingPointList[temp]);
            }
        }
    }

    return output;
}

double TimingPointList::getMinOffset() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double TimingPointList::getMaxOffset() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}

double TimingPointList::getMinValue(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    if (info.getIsSV() && info.getIsBPM())
    {
        AExc(AExc::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output;
    QList<double> valueList;
    valueList = getValueList(info);

    output = *std::min_element(valueList.begin(), valueList.end());
    return output;
}
double TimingPointList::getMaxValue(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    if (info.getIsSV() && info.getIsBPM())
    {
        AExc(AExc::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output;
    QList<double> valueList;
    valueList = getValueList(info);

    output = *std::max_element(valueList.begin(), valueList.end());
    return output;
}

double TimingPointList::getLength() const
{
    Common::assertEmpty(toString(), __FUNCTION__);

    double output = 0;
    QList<double> offsetList;

    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end())
        - *std::min_element(offsetList.begin(), offsetList.end());

    return output;
}
double TimingPointList::getLength(int index)
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertIndex(index, getSize() - 1);

    sortOffset(true);

    return timingPointList[index + 1].getOffset() - timingPointList[index].getOffset();
}

int TimingPointList::getSize(const Info& info) const
{
    TimingPoint temp;
    int counter = 0;

    if (info.getIsSV() && info.getIsBPM()) // If user requests both
    {
        counter = timingPointList.count();
    }
    else if (info.getIsSV()) // SV Request
    {
        foreach (temp, timingPointList)
        {
            if (temp.getIsSV())
            {
                counter++;
            }
        }
    }
    else if (info.getIsBPM()) // BPM Request
    {
        foreach (temp, timingPointList)
        {
            if (temp.getIsBPM())
            {
                counter++;
            }
        }
    }

    return counter;
}
double TimingPointList::getAverage(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        AExc(AExc::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output = 0;
    QList<double> TPList;
    double TPeach;

    TPList = getValueList(info);

    foreach (TPeach, TPList)
    {
        output += TPeach;
    }

    output /= TPList.count();
    return output;
}
double TimingPointList::getDistance(const Info& info) const
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        AExc(AExc::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    QList<double> lengthList, valueList;
    double distance;

    lengthList = getLengthList(info);
    valueList = getValueList(info);

    for (int temp = 0; temp < lengthList.length(); temp++)
    {
        distance += lengthList[temp] * valueList[temp];
    }

    return distance;
}
double TimingPointList::getDistance(int index)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    double length, value;

    length = getLength(index);
    value = timingPointList[index].getValue();

    return length * value;
}
QStringList TimingPointList::toString() const
{
    TimingPoint temp;
    QStringList output;
    foreach (temp, timingPointList)
    {
        output.append(temp.toString());
    }

    return output;
}

// OPERS
TimingPoint& TimingPointList::operator[](int i)
{
    if (i >= getSize())
    {
        AExc(AExc::INDEX_OUT_OF_RANGE, QString("Within TimingPointList\n"
                                               "Access: %1\n"
                                               "Last i: %2")
                                           .arg(i)
                                           .arg(getSize() - 1));
        return *(new TimingPoint());
    }

    return timingPointList[i];
}
TimingPoint TimingPointList::operator[](int i) const
{
    if (i >= getSize())
    {
        AExc(AExc::INDEX_OUT_OF_RANGE, QString("Within TimingPointList\n"
                                               "Access: %1\n"
                                               "Last i: %2")
                                           .arg(i)
                                           .arg(getSize() - 1));
        return TimingPoint();
    }
    return timingPointList[i];
}

void TimingPointList::multiplyValue(const TimingPointList rhsTimingPointList, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> lhsValueList, rhsValueList, lhsOffsetList, rhsOffsetList;
    int lhsTemp, rhsTemp;

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
        while (lhsTemp < lhsValueList.length() && rhsTemp < rhsValueList.length()
            && lhsOffsetList[lhsTemp] >= rhsOffsetList[rhsTemp]
            && lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp + 1])
        {
            // qDebug() << "lhsTemp            : " << lhsTemp << "\n"
            //          << "rhsTemp            : " << rhsTemp << "\n"
            //          << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << "\n"
            //          << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << "\n"
            //          << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << "\n"
            //          << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << "\n";

            lhsValueList[lhsTemp] *= rhsValueList[rhsTemp];

            // qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << "\n"
            //          << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << "\n";

            lhsTemp++;
        }
        rhsTemp++;
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
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> lhsValueList, rhsValueList, lhsOffsetList, rhsOffsetList;
    int lhsTemp, rhsTemp;

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
        while (lhsTemp < lhsValueList.length() && rhsTemp < rhsValueList.length()
            && lhsOffsetList[lhsTemp] >= rhsOffsetList[rhsTemp]
            && lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp + 1])
        {
            // qDebug() << "lhsTemp            : " << lhsTemp << "\n"
            //          << "rhsTemp            : " << rhsTemp << "\n"
            //          << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << "\n"
            //          << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << "\n"
            //          << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << "\n"
            //          << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << "\n";

            lhsValueList[lhsTemp] /= rhsValueList[rhsTemp];

            // qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << "\n"
            //          << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << "\n";

            lhsTemp++;
        }
        rhsTemp++;
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
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> lhsValueList, rhsValueList, lhsOffsetList, rhsOffsetList;
    int lhsTemp, rhsTemp;

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
        while (lhsTemp < lhsValueList.length() && rhsTemp < rhsValueList.length()
            && lhsOffsetList[lhsTemp] >= rhsOffsetList[rhsTemp]
            && lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp + 1])
        {
            // qDebug() << "lhsTemp            : " << lhsTemp << "\n"
            //          << "rhsTemp            : " << rhsTemp << "\n"
            //          << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << "\n"
            //          << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << "\n"
            //          << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << "\n"
            //          << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << "\n";

            lhsValueList[lhsTemp] += rhsValueList[rhsTemp];

            // qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << "\n"
            //          << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << "\n";

            lhsTemp++;
        }
        rhsTemp++;
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
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> lhsValueList, rhsValueList, lhsOffsetList, rhsOffsetList;
    int lhsTemp, rhsTemp;

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
        while (lhsTemp < lhsValueList.length() && rhsTemp < rhsValueList.length()
            && lhsOffsetList[lhsTemp] >= rhsOffsetList[rhsTemp]
            && lhsOffsetList[lhsTemp] < rhsOffsetList[rhsTemp + 1])
        {
            // qDebug() << "lhsTemp            : " << lhsTemp << "\n"
            //          << "rhsTemp            : " << rhsTemp << "\n"
            //          << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << "\n"
            //          << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << "\n"
            //          << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << "\n"
            //          << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << "\n";

            lhsValueList[lhsTemp] -= rhsValueList[rhsTemp];

            // qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << "\n"
            //          << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << "\n";

            lhsTemp++;
        }
        rhsTemp++;
    }
    setValueList(lhsValueList);

    if (limitFlag)
    {
        limitValues();
    }
    return;
}

void TimingPointList::multiplyValue(const double rhsDouble, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newValueList, oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList)
    {
        newValueList.append(temp * rhsDouble);
    }

    setValueList(newValueList);
    if (limitFlag)
    {
        limitValues();
    }
}
void TimingPointList::divideValue(const double rhsDouble, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newValueList, oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList)
    {
        newValueList.append(temp / rhsDouble);
    }

    setValueList(newValueList);
    if (limitFlag)
    {
        limitValues();
    }
}
void TimingPointList::addValue(const double rhsDouble, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newValueList, oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList)
    {
        newValueList.append(temp + rhsDouble);
    }

    setValueList(newValueList);
    if (limitFlag)
    {
        limitValues();
    }
}
void TimingPointList::subtractValue(const double rhsDouble, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newValueList, oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList)
    {
        newValueList.append(temp - rhsDouble);
    }

    setValueList(newValueList);
    if (limitFlag)
    {
        limitValues();
    }
}

void TimingPointList::multiplyOffset(const double rhsDouble, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp * rhsDouble);
    }

    setOffsetList(newOffsetList);
    if (limitFlag)
    {
        limitValues();
    }
}
void TimingPointList::divideOffset(const double rhsDouble, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp / rhsDouble);
    }

    setOffsetList(newOffsetList);
    if (limitFlag)
    {
        limitValues();
    }
}
void TimingPointList::addOffset(const double rhsDouble, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp + rhsDouble);
    }

    setOffsetList(newOffsetList);
    if (limitFlag)
    {
        limitValues();
    }
}
void TimingPointList::subtractOffset(const double rhsDouble, bool limitFlag)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList)
    {
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
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> newOffsetList, oldOffsetList;

    double temp, min;

    min = getMinOffset();

    oldOffsetList = getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp - min);
    }

    setOffsetList(newOffsetList);
}

// MISC
void TimingPointList::sortOffset(bool isAscending)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    if (isAscending)
    {
        std::sort(timingPointList.begin(), timingPointList.end());
    }
    else
    {
        std::sort(timingPointList.rbegin(), timingPointList.rend());
    }
}

void TimingPointList::append(TimingPointList timingPointList_)
{
    for (int temp = 0; temp < timingPointList_.getSize(); temp++)
    {
        timingPointList.append(timingPointList_[temp]);
    }
}

bool TimingPointList::isEmpty() const
{
    return getSize() == 0;
}
void TimingPointList::limitValues(double maxSV, double minSV, double maxBPM, double minBPM)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    TimingPoint temp;

    foreach (temp, timingPointList)
    {
        temp.limitValues(maxSV, minSV, maxBPM, minBPM);
    }
}

void TimingPointList::limitOffset(double minOffset, double maxOffset)
{
    Common::assertEmpty(toString(), __FUNCTION__);

    TimingPoint temp;

    foreach (temp, timingPointList)
    {
        temp.limitOffset(minOffset, maxOffset);
    }
}
QList<int> TimingPointList::indexList(Info& info)
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(info);

    if (info.getIsSV() && info.getIsBPM())
    {
        AExc(AExc::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    QList<int> indexList;

    for (int counter = 0; counter < timingPointList.length(); counter++)
    {
        if (info.getIsSV())
        {
            if (!timingPointList[counter].getIsBPM())
            {
                indexList.append(counter);
            }
        }
        else if (info.getIsBPM())
        {
            if (timingPointList[counter].getIsBPM())
            {
                indexList.append(counter);
            }
        }
    }

    return indexList;
}
void TimingPointList::adjustToAverage(double averageSV, int adjustIndex)
{
    Common::assertEmpty(toString(), __FUNCTION__);
    Common::assertLoadFail(getInfo());

    if (getInfo().getIsSV() && getInfo().getIsBPM())
    {
        AExc(AExc::INFO_RESTRICT, "Only works with SV only or BPM only list");
    }

    // To elaborate what this function does:
    // This function changes a single TP (via adjustIndex) to achieve the specified averageSV
    // This function cannot adjust TP at the end as it doesn't contribute to the average SV

    // If adjusting the TP cannot achieve the specified average SV then it'll fail

    Common::assertIndex(adjustIndex, timingPointList.length() - 2); // Cannot adjust last index

    double oldTotalDistance, newTotalDistance, oldAdjustLength, newAdjustValue,
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

    newAdjustValue = timingPointList[adjustIndex].getValue() + (netDistance / oldAdjustLength);

    if (getInfo().getIsSV())
    {
        if (newAdjustValue > TimingPoint::MAXIMUM_SV || newAdjustValue < TimingPoint::MINIMUM_SV)
        {
            AExc(AExc::VALUE_OUT_OF_RANGE, QString("SV %1 is out of range: [%2 - %3]")
                                               .arg(newAdjustValue)
                                               .arg(TimingPoint::MINIMUM_SV)
                                               .arg(TimingPoint::MAXIMUM_SV));
            return;
        }
    }
    else if (getInfo().getIsBPM())
    {
        if (newAdjustValue < TimingPoint::MINIMUM_BPM)
        {
            AExc(AExc::VALUE_OUT_OF_RANGE, QString("SV %1 is out of range: [%2 - %3]")
                                               .arg(newAdjustValue)
                                               .arg(TimingPoint::MINIMUM_SV)
                                               .arg(TimingPoint::MAXIMUM_SV));
            return;
        }
    }

    timingPointList[adjustIndex].setValue(newAdjustValue);
    timingPointList[adjustIndex].limitValues();
}

void TimingPointList::makeUnique()
{
    Common::assertEmpty(toString(), __FUNCTION__);

    QList<double> offsetList, newOffsetList;
    QList<TimingPoint> newTimingPointList;
    double temp;

    offsetList = getOffsetList();

    foreach (temp, offsetList)
    {
        if (!newOffsetList.contains(temp))
        {
            newOffsetList.append(temp);
            newTimingPointList.append(TimingPoint(
                temp, timingPointList[temp].getValue(), timingPointList[temp].getIsBPM()));
        }
    }

    loadTPList(newTimingPointList);
}
