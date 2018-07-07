#include "amber_base/obj_impl/timingpointlist_impl.h"

// LOADERS
TimingPointList_impl::TimingPointList_impl()
{
}

void TimingPointList_impl::loadTPList(QList<TimingPoint> newTimingPointList_impl)
{
    timingPointList = newTimingPointList_impl;
}
void TimingPointList_impl::loadTPList(QTextBrowser* tb)
{
    QString tbText;
    QStringList tbTextSplit;

    tbText = tb->toPlainText();
    tbTextSplit = tbText.split('\n', QString::SkipEmptyParts);
    loadTPList(tbTextSplit);
}
void TimingPointList_impl::loadTPList(QLineEdit* line)
{
    QString lineText;
    lineText = line->text();

    loadTPList(lineText);
}

void TimingPointList_impl::loadTPList(QPlainTextEdit* pte)
{
    QString pteText;
    pteText = pte->toPlainText();

    loadTPList(pteText);
}
void TimingPointList_impl::loadTPList(QString& str)
{
    QStringList strSplit;
    strSplit = str.split('\n', QString::SkipEmptyParts);

    loadTPList(strSplit);
}
void TimingPointList_impl::loadTPList(QStringList& strList)
{
    if (ValidObj::assertTimingPoint(strList))
    {
        loadFail = true;
    }

    for (int temp = 0; temp < strList.length(); temp ++)
    {
        timingPointList.append(TimingPoint(strList[temp]));
    }
}

// SETTERS
void TimingPointList_impl::setOffsetList(const QList<Offset> &offsetList_)
{
    AmberException::assertLengthMatch(timingPointList.length(),
                                      offsetList_.length());

    for (int i = 0; i < offsetList_.length(); i++)
    {
        timingPointList[i].setOffset(offsetList_[i]);
    }
}
void TimingPointList_impl::setCodeList(const QList<std::shared_ptr<TimeCode>> &codeList_)
{
    AmberException::assertLengthMatch(timingPointList.length(),
                                      codeList_.length());

    for (int i = 0; i < codeList_.length(); i++)
    {
        timingPointList[i].setCode(codeList_[i]);
    }
}
void TimingPointList_impl::setValueList(const QList<double> &valueList_)
{
    AmberException::assertLengthMatch(timingPointList.length(),
                                      valueList_.length());

    for (int i = 0; i < valueList_.length(); i++)
    {
        timingPointList[i].setValue(valueList_[i]);
    }
}

void TimingPointList_impl::convertToBPM(const BPM &referenceValue)
{
    for (auto &i : timingPointList){
        if (!i.getIsBPM())
        {
            i.convertToBPM(referenceValue);
        }
    }
}

void TimingPointList_impl::convertToSV(const BPM &referenceValue)
{
    for (auto &i : timingPointList){
        if (i.getIsBPM()){
            i.convertToSV(referenceValue);
        }
    }
}

// GETTERS
QList<Offset> TimingPointList_impl::getOffsetList(const Info& info) const
{
    TimingPoint timingPoint;
    QList<Offset> output;

    foreach (timingPoint, timingPointList){
        if (((info.getIsBPM()) && timingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
            || ((info.getIsSV()) && timingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(timingPoint.getOffset());
        }
    }

    return output;
}
QList<std::shared_ptr<TimeCode>> TimingPointList_impl::getCodeList(const Info& info) const
{
    TimingPoint timingPoint;
    QList<std::shared_ptr<TimeCode>> output;
    foreach (timingPoint, timingPointList){
        if (((info.getIsBPM()) && timingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
            || ((info.getIsSV()) && timingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(timingPoint.getCode());
        }
    }

    return output;
}
QList<double> TimingPointList_impl::getValueList(const Info& info) const
{
    TimingPoint timingPoint;
    QList<double> output;
    foreach (timingPoint, timingPointList){
        if (((info.getIsBPM()) && timingPoint.getIsBPM()) // continue if foreach is BPM and we only accept SV
            || ((info.getIsSV()) && timingPoint.getIsSV())) // continue if foreach is SV  and we only accept BPM
        {
            output.append(timingPoint.getValue());
        }
    }

    return output;
}
QList<Offset> TimingPointList_impl::getLengthList(const Info& info) const
{
    // Note: If amberCommon::TPFlag is specified, length calculation will skip some timingPoints
    QList<Offset> output, offsetList;

    offsetList = getOffsetList(info);

    for (int temp = 0; temp < offsetList.length() - 1; temp++)
    {
        output.append(Offset(offsetList[temp + 1].value() - offsetList[temp].value()));
    }

    return output;
}
QList<Distance> TimingPointList_impl::getDistanceList(const Info& info) const
{
    QList<double> valueList;
    QList<Distance> distanceList;
    QList<Offset> lengthList;

    lengthList = getLengthList(info);
    valueList = getValueList(info);

    for (int temp = 0; temp < lengthList.length(); temp++)
    {
        distanceList.append(Distance(lengthList[temp], valueList[temp]));
    }

    return distanceList;
}

QList<Offset> TimingPointList_impl::getUnqOffsetList(const Info& info) const
{
    QList<Offset> offsetList, unqOffsetList;

    Offset offset;

    offsetList = getOffsetList(info);

    for (auto &i : offsetList){
        if (!unqOffsetList.contains(i)){
            unqOffsetList.append(i);
        }
    }

    return unqOffsetList;
}

TimingPointList_impl TimingPointList_impl::splitByType(const Info& info) const
{
    if (info.getIsSV() && info.getIsBPM()){
        AmberException(AmberException::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    TimingPointList_impl output;

    if (info.getIsSV()){
        for (const auto &i : timingPointList){
            if (i.getIsSV()){
                output.append(i);
            }
        }
    }
    if (info.getIsBPM()){
        for (const auto &i : timingPointList){
            if (i.getIsBPM()){
                output.append(i);
            }
        }
    }

    return output;
}

Offset TimingPointList_impl::getMinOffset() const
{
    Offset output;
    QList<Offset> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
Offset TimingPointList_impl::getMaxOffset() const
{
    Offset output;
    QList<Offset> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}

double TimingPointList_impl::getMinValue(const Info& info) const
{
    if (info.getIsSV() && info.getIsBPM())
    {
        AmberException(AmberException::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output;
    QList<double> valueList;
    valueList = getValueList(info);

    output = *std::min_element(valueList.begin(), valueList.end());
    return output;
}
double TimingPointList_impl::getMaxValue(const Info& info) const
{
    if (info.getIsSV() && info.getIsBPM())
    {
        AmberException(AmberException::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output;
    QList<double> valueList;
    valueList = getValueList(info);

    output = *std::max_element(valueList.begin(), valueList.end());
    return output;
}

Offset TimingPointList_impl::getLength() const
{
    Offset output = 0;
    QList<Offset> offsetList;

    offsetList = getOffsetList();
    output = Offset(*std::max_element(offsetList.begin(), offsetList.end())
                  - *std::min_element(offsetList.begin(), offsetList.end()));

    return output;
}
Offset TimingPointList_impl::getLength(int index)
{
    AmberException::assertIndex(index, getSize() - 1);

    sortOffset(true);

    return Offset(timingPointList[index + 1].getOffset() -
                  timingPointList[index].getOffset());
}

int TimingPointList_impl::getSize(const Info& info) const
{
    TimingPoint temp;
    int counter = 0;

    if (info.getIsSV() && info.getIsBPM()) // If user requests both
    {
        counter = timingPointList.count();
    }
    else if (info.getIsSV()) // SV Request
    {
        for (const auto& i : timingPointList)
        {
            if (i.getIsSV())
            {
                counter++;
            }
        }
    }
    else if (info.getIsBPM()) // BPM Request
    {
        for (const auto& i : timingPointList)
        {
            if (i.getIsBPM())
            {
                counter++;
            }
        }
    }

    return counter;
}
double TimingPointList_impl::getAverage(const Info& info) const
{
    if (info.getIsSV() && info.getIsBPM())
    {
        AmberException(AmberException::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    double output = 0;
    QList<Distance> TPList;

    TPList = getDistanceList(info);

    for (const auto& i : TPList)
    {
        output += i.value();
    }

    output /= getLength().value();
    return output;
}
Distance TimingPointList_impl::getDistance(const Info& info) const
{
    if (info.getIsSV() && info.getIsBPM())
    {
        AmberException(AmberException::INFO_RESTRICT,
            QString(__FUNCTION__) + "does not accept both SV & BPM input, pick only one");
    }

    QList<Offset> lengthList;
    QList<double> valueList;
    Distance distance;

    lengthList = getLengthList(info);
    valueList = getValueList(info);

    for (int temp = 0; temp < lengthList.length(); temp++)
    {
        distance += Distance(lengthList[temp], valueList[temp]);
    }

    return distance;
}
Distance TimingPointList_impl::getDistance(int index)
{
    Offset length;
    double value;

    length = getLength(index);
    value = timingPointList[index].getValue();

    return Distance(length, value);
}
QStringList TimingPointList_impl::toString() const
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
TimingPoint& TimingPointList_impl::operator[](int i)
{
    if (i >= getSize())
    {
        AmberException(AmberException::INDEX_OUT_OF_RANGE, QString("Within TimingPointList_impl\n"
                                               "Access: %1\n"
                                               "Last i: %2")
                                           .arg(i)
                                           .arg(getSize() - 1));
        return *(new TimingPoint());
    }

    return timingPointList[i];
}
TimingPoint TimingPointList_impl::operator[](int i) const
{
    if (i >= getSize())
    {
        AmberException(AmberException::INDEX_OUT_OF_RANGE, QString("Within TimingPointList_impl\n"
                                               "Access: %1\n"
                                               "Last i: %2")
                                           .arg(i)
                                           .arg(getSize() - 1));
        return TimingPoint();
    }
    return timingPointList[i];
}

void TimingPointList_impl::multiplyValue(const TimingPointList_impl rhsTimingPointList)
{
    QList<double> lhsValueList, rhsValueList;
    QList<Offset> lhsOffsetList, rhsOffsetList;
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
            // qDebug() << "lhsTemp            : " << lhsTemp << '\n'
            //          << "rhsTemp            : " << rhsTemp << '\n'
            //          << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << '\n'
            //          << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << '\n'
            //          << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << '\n'
            //          << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << '\n';

            lhsValueList[lhsTemp] *= rhsValueList[rhsTemp];

            // qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << '\n'
            //          << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << '\n';

            lhsTemp++;
        }
        rhsTemp++;
    }
    setValueList(lhsValueList);
    return;
}
void TimingPointList_impl::divideValue(const TimingPointList_impl rhsTimingPointList)
{
    QList<double> lhsValueList, rhsValueList;
    QList<Offset> lhsOffsetList, rhsOffsetList;
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
            // qDebug() << "lhsTemp            : " << lhsTemp << '\n'
            //          << "rhsTemp            : " << rhsTemp << '\n'
            //          << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << '\n'
            //          << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << '\n'
            //          << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << '\n'
            //          << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << '\n';

            lhsValueList[lhsTemp] /= rhsValueList[rhsTemp];

            // qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << '\n'
            //          << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << '\n';

            lhsTemp++;
        }
        rhsTemp++;
    }
    setValueList(lhsValueList);
    return;
}
void TimingPointList_impl::addValue(const TimingPointList_impl rhsTimingPointList)
{
    QList<double> lhsValueList, rhsValueList;
    QList<Offset> lhsOffsetList, rhsOffsetList;
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
            // qDebug() << "lhsTemp            : " << lhsTemp << '\n'
            //          << "rhsTemp            : " << rhsTemp << '\n'
            //          << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << '\n'
            //          << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << '\n'
            //          << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << '\n'
            //          << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << '\n';

            lhsValueList[lhsTemp] += rhsValueList[rhsTemp];

            // qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << '\n'
            //          << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << '\n';

            lhsTemp++;
        }
        rhsTemp++;
    }
    setValueList(lhsValueList);
    return;
}
void TimingPointList_impl::subtractValue(const TimingPointList_impl rhsTimingPointList)
{
    QList<double> lhsValueList, rhsValueList;
    QList<Offset> lhsOffsetList, rhsOffsetList;
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
            // qDebug() << "lhsTemp            : " << lhsTemp << '\n'
            //          << "rhsTemp            : " << rhsTemp << '\n'
            //          << "lhsOffsetList      :" << lhsOffsetList[lhsTemp] << '\n'
            //          << "rhsOffsetList      :" << rhsOffsetList[rhsTemp] << '\n'
            //          << "lhsValueList <OLD> :" << lhsValueList[lhsTemp] << '\n'
            //          << "rhsValueList <OLD> :" << rhsValueList[rhsTemp] << '\n';

            lhsValueList[lhsTemp] -= rhsValueList[rhsTemp];

            // qDebug() << "lhsValueList <NEW> :" << lhsValueList[lhsTemp] << '\n'
            //          << "rhsValueList <NEW> :" << rhsValueList[rhsTemp] << '\n';

            lhsTemp++;
        }
        rhsTemp++;
    }
    setValueList(lhsValueList);

    return;
}

void TimingPointList_impl::multiplyValue(const double rhsDouble)
{
    QList<double> newValueList, oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList)
    {
        newValueList.append(temp * rhsDouble);
    }

    setValueList(newValueList);
}
void TimingPointList_impl::divideValue(const double rhsDouble)
{
    QList<double> newValueList, oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList)
    {
        newValueList.append(temp / rhsDouble);
    }

    setValueList(newValueList);

}
void TimingPointList_impl::addValue(const double rhsDouble)
{
    QList<double> newValueList, oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList)
    {
        newValueList.append(temp + rhsDouble);
    }

    setValueList(newValueList);
}
void TimingPointList_impl::subtractValue(const double rhsDouble)
{
    QList<double> newValueList, oldValueList;
    double temp;

    oldValueList = getValueList();

    foreach (temp, oldValueList)
    {
        newValueList.append(temp - rhsDouble);
    }

    setValueList(newValueList);
}

void TimingPointList_impl::multiplyOffset(const double rhsDouble)
{
    QList<Offset> newOffsetList;

    for (const auto &i : timingPointList){
        newOffsetList.append(Offset(i.getOffset() * rhsDouble));
    }

    setOffsetList(newOffsetList);
}
void TimingPointList_impl::divideOffset(const double rhsDouble)
{
    QList<Offset> newOffsetList;

    for (const auto &i : timingPointList){
        newOffsetList.append(Offset(i.getOffset() / rhsDouble));
    }

    setOffsetList(newOffsetList);
}
void TimingPointList_impl::addOffset(const double rhsDouble)
{
    QList<Offset> newOffsetList;

    for (const auto &i : timingPointList){
        newOffsetList.append(Offset(i.getOffset() + rhsDouble));
    }

    setOffsetList(newOffsetList);
}
void TimingPointList_impl::subtractOffset(const double rhsDouble)
{
    QList<Offset> newOffsetList, oldOffsetList;
    oldOffsetList = getOffsetList();

    for (const auto &i : timingPointList){
        newOffsetList.append(Offset(i.getOffset() - rhsDouble));
    }

    setOffsetList(newOffsetList);
}

void TimingPointList_impl::zero()
{
    QList<Offset> newOffsetList;

    Offset min;

    min = getMinOffset();

    for (const auto &i : timingPointList){
        newOffsetList.append(Offset(i.getOffset() - min));
    }

    setOffsetList(newOffsetList);
}

// MISC
void TimingPointList_impl::sortOffset(bool isAscending)
{
    if (isAscending)
    {
        std::sort(timingPointList.begin(), timingPointList.end(), [](const TimingPoint &left, const TimingPoint &right)
        {
            return left.getOffset() < right.getOffset();
        });
    }
    else
    {
        std::sort(timingPointList.begin(), timingPointList.end(), [](const TimingPoint &left, const TimingPoint &right)
        {
            return left.getOffset() < right.getOffset();
        });
    }
}

void TimingPointList_impl::append(TimingPointList_impl timingPointList_)
{
    for (int temp = 0; temp < timingPointList_.getSize(); temp++)
    {
        timingPointList.append(timingPointList_[temp]);
    }
}

bool TimingPointList_impl::isEmpty() const
{
    return getSize() == 0;
}
QList<int> TimingPointList_impl::indexList(Info& info)
{
    if (info.getIsSV() && info.getIsBPM())
    {
        AmberException(AmberException::INFO_RESTRICT,
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
void TimingPointList_impl::adjustToAverage(SliderVelocity average, int adjustIndex)
{
    // To elaborate what this function does:
    // This function changes a single TP (via adjustIndex) to achieve the specified averageSV
    // This function cannot adjust TP at the end as it doesn't contribute to the average SV

    // If adjusting the TP cannot achieve the specified average SV then it'll fail

    AmberException::assertIndex(adjustIndex,
                                timingPointList.length() - 2); // Cannot adjust last index

    Distance oldTotalDistance,
             newTotalDistance,
             netDistance;

    Offset  oldAdjustLength;
    SliderVelocity newAdjustSV;

    oldTotalDistance = getDistance(Info(Info::IS_SV));
    newTotalDistance = Distance(getLength(), average);

    // We calculate the distance that needs to be added/subtracted
    netDistance = newTotalDistance - oldTotalDistance;
    oldAdjustLength = getLength(adjustIndex);

    newAdjustSV = timingPointList[adjustIndex].getValue() + (netDistance.value() / oldAdjustLength.value());

    // If it goes out of range, it'll automatically raise as a qDebug message

    timingPointList[adjustIndex].setValue(newAdjustSV);
}

void TimingPointList_impl::adjustToAverage(BPM average, int adjustIndex)
{
    AmberException::assertIndex(adjustIndex,
                                timingPointList.length() - 2); // Cannot adjust last index

    Distance oldTotalDistance,
             newTotalDistance,
             netDistance;

    Offset  oldAdjustLength;
    BPM newAdjustBPM;

    oldTotalDistance = getDistance(Info(Info::IS_BPM));
    newTotalDistance = Distance(getLength(), average);

    // We calculate the distance that needs to be added/subtracted
    netDistance = newTotalDistance - oldTotalDistance;
    oldAdjustLength = getLength(adjustIndex);

    newAdjustBPM = timingPointList[adjustIndex].getValue() + (netDistance.value() / oldAdjustLength.value());

    // If it goes out of range, it'll automatically raise as a qDebug message

    timingPointList[adjustIndex].setValue(newAdjustBPM);
}

void TimingPointList_impl::makeUnique()
{
    QList<Offset> offsetList, newOffsetList;
    QList<TimingPoint> newTimingPointList;
    Offset temp;

    offsetList = getOffsetList();

    foreach (temp, offsetList)
    {
        if (!newOffsetList.contains(temp))
        {
            newOffsetList.append(temp);
            newTimingPointList.append(TimingPoint(
                                          temp,
                                          timingPointList[temp].getValue(),
                                          timingPointList[temp].getIsBPM()));
        }
    }

    loadTPList(newTimingPointList);
}
