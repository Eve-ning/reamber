#include "com_tplist.h"
#define CHECK_EMPTY(returnValue) if (isEmpty()) \
                                 { \
                                     qDebug() << __FUNCTION__ << ": OM_TP List is empty"; \
                                     return returnValue; \
                                 }

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

    bool boolTP;
    boolTP = (int(cOM_Common::isTP(str)) != int(cOM_Common::TPFlag::INVALID));

    if (!boolTP)
    {
        loadFail = true;
        return;
    }

    strSplit = str.split("\n", QString::SkipEmptyParts);

    loadTPList(strSplit);
}
void cOM_TPList::loadTPList(QStringList &strList)
{
    bool boolTP;
    QString     temp;

    boolTP = (int(cOM_Common::isTP(strList)) != int(cOM_Common::TPFlag::INVALID));

    if (!boolTP)
    {
        loadFail = true;
        return;
    }

    foreach (temp, strList) {
        OM_TPList.append(cOM_TP(temp));
    }
}

// SETTERS
void cOM_TPList::setOffsetList(QList<double> newOffsetList)
{
    if (OM_TPList.length() != newOffsetList.length())
    {
        qDebug() << __FUNCTION__ << ": Length Mismatch";
        return;
    }

    for (int i = 0; i < newOffsetList.length(); i ++)
    {
        OM_TPList[i].setOffset(newOffsetList[i]);
    }

    return;
}
void cOM_TPList::setCodeList(QList<double> newCodeList)
{
    if (OM_TPList.length() != newCodeList.length())
    {
        qDebug() << __FUNCTION__ << ": Length Mismatch";
        return;
    }

    for (int i = 0; i < newCodeList.length(); i ++)
    {
        OM_TPList[i].setCode(newCodeList[i]);
    }

    return;
}
void cOM_TPList::setValueList(QList<double> newValueList)
{
    if (OM_TPList.length() != newValueList.length())
    {
        qDebug() << __FUNCTION__ << ": Length Mismatch";
        return;
    }

    for (int i = 0; i < newValueList.length(); i ++)
    {
        OM_TPList[i].setValue(newValueList[i]);
    }

    return;
}

// GETTERS
QList<double> cOM_TPList::getOffsetList(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(QList<double>({}));

    cOM_TP OM_TP;
    QList<double> output;
    foreach (OM_TP, OM_TPList)
    {
        if (    ((onlyFlag == cOM_Common::TPFlag::SV_ONLY ) && OM_TP.getIsBPM ()) // continue if foreach is BPM and we only accept SV
             || ((onlyFlag == cOM_Common::TPFlag::BPM_ONLY) && OM_TP.getIsKiai())) // continue if foreach is SV  and we only accept BPM
        {
            continue;
        }
        output.append(OM_TP.getOffset());
    }

    return output;
}
QList<double> cOM_TPList::getCodeList(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(QList<double>({}));

    cOM_TP OM_TP;
    QList<double> output;
    foreach (OM_TP, OM_TPList)
    {
        if (    ((onlyFlag == cOM_Common::TPFlag::SV_ONLY ) && OM_TP.getIsBPM ()) // continue if foreach is BPM and we only accept SV
             || ((onlyFlag == cOM_Common::TPFlag::BPM_ONLY) && OM_TP.getIsKiai())) // continue if foreach is SV  and we only accept BPM
        {
            continue;
        }
        output.append(OM_TP.getCode());
    }

    return output;
}
QList<double> cOM_TPList::getValueList(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(QList<double>({}));

    cOM_TP OM_TP;
    QList<double> output;
    foreach (OM_TP, OM_TPList)
    {
        if (    ((onlyFlag == cOM_Common::TPFlag::SV_ONLY ) && (OM_TP.getIsBPM ())) // continue if foreach is BPM and we only accept SV
             || ((onlyFlag == cOM_Common::TPFlag::BPM_ONLY) && (OM_TP.getIsKiai()))) // continue if foreach is SV  and we only accept BPM
        {
            continue;
        }
        output.append(OM_TP.getValue());
    }

    return output;
}
QList<double> cOM_TPList::getLengthList(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(QList<double>({}));

    // Note: If cOM_Common::TPFlag is specified, length calculation will skip some timingPoints
    QList<double> output,
                  offsetList;

    offsetList = getOffsetList(onlyFlag);

    for (int temp = 0; temp < offsetList.length() - 1; temp++)
    {
        output.append(offsetList[temp + 1] - offsetList[temp]);
    }

    return output;
}
QList<double> cOM_TPList::getDistanceList(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(QList<double>({}));

    QList<double> lengthList,
                  valueList,
                  distanceList;

    lengthList = getLengthList(onlyFlag);
    valueList  = getValueList (onlyFlag);

    for (int temp = 0; temp < lengthList.length(); temp++)
    {
        distanceList.append(lengthList[temp] * valueList[temp]);
    }

    return distanceList;
}

QList<double> cOM_TPList::getUnqOffsetList(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(QList<double>({}));

    QList<double> offsetList,
                  unqOffsetList;

    double offset;

    offsetList = getOffsetList(onlyFlag);

    foreach (offset, offsetList)
    {
        if (!unqOffsetList.contains(offset))
        {
            unqOffsetList.append(offset);
        }
    }

    return unqOffsetList;
}

cOM_TPList cOM_TPList::splitByType(cOM_Common::TPFlag onlyFlag) const
{
    if (onlyFlag == cOM_Common::TPFlag::SV_BPM_ONLY ||
        onlyFlag == cOM_Common::TPFlag::INVALID )
    {
        qDebug() << __FUNCTION__ << "does not support SV_BPM_ONLY and INVALID";
        return cOM_TPList();
    }

    cOM_TPList output;

    switch (onlyFlag) {
    case cOM_Common::TPFlag::SV_ONLY:
        for (int temp = 0; temp < OM_TPList.length(); temp++)
        {
            if (!OM_TPList[temp].getIsBPM())
            {
                output.append(OM_TPList[temp]);
            }
        }
        break;

    case cOM_Common::TPFlag::BPM_ONLY:
        for (int temp = 0; temp < OM_TPList.length(); temp++)
        {
            if (OM_TPList[temp].getIsBPM())
            {
                output.append(OM_TPList[temp]);
            }
        }
        break;

    default:
        break;
    }

    return output;
}

double cOM_TPList::getMinOffset() const
{
    CHECK_EMPTY(0);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
double cOM_TPList::getMaxOffset() const
{
    CHECK_EMPTY(0);

    double output;
    QList<double> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}
double cOM_TPList::getMinValue(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(0);

    if (onlyFlag == cOM_Common::TPFlag::SV_BPM_ONLY ||
        onlyFlag == cOM_Common::TPFlag::INVALID)
    {
        qDebug() << __FUNCTION__ << "does not support SV_BPM_ONLY and INVALID";
        return 0;
    }

    double output;
    QList<double> valueList;
    valueList = getValueList(onlyFlag);

    if (valueList.length() == 0)
    {
        qDebug() << __FUNCTION__ << "selected flagtype is empty";
        return 0;
    }

    output = *std::min_element(valueList.begin(), valueList.end());
    return output;
}
double cOM_TPList::getMaxValue(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(0);

    if (onlyFlag == cOM_Common::TPFlag::SV_BPM_ONLY ||
        onlyFlag == cOM_Common::TPFlag::INVALID)
    {
        qDebug() << __FUNCTION__ << "does not support SV_BPM_ONLY and INVALID";
        return 0;
    }

    double output;
    QList<double> valueList;
    valueList = getValueList(onlyFlag);

    if (valueList.length() == 0)
    {
        qDebug() << __FUNCTION__ << "selected flagtype is empty";
        return 0;
    }

    output = *std::max_element(valueList.begin(), valueList.end());
    return output;
}

double cOM_TPList::getLength() const
{
    CHECK_EMPTY(0);

    double output = 0;
    QList<double> offsetList;

    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end())
           - *std::min_element(offsetList.begin(), offsetList.end());

    return output;
}
double cOM_TPList::getLength(int index)
{
    CHECK_EMPTY(0);

    sortOffset(true);

    if (!(index < (getSize() - 1)))
    {
        qDebug() << __FUNCTION__ << "Index is out of bounds, cannot get length" << "\n"
                 << "Returning 0;";
        return 0;
    }

    return OM_TPList[index + 1].getOffset() - OM_TPList[index].getOffset();
}
int    cOM_TPList::getSize(cOM_Common::TPFlag onlyFlag) const
{
    cOM_TP temp;
    int counter = 0;
    switch (onlyFlag) {
    case cOM_Common::TPFlag::SV_BPM_ONLY:
        return OM_TPList.count();
        break;

    case cOM_Common::TPFlag::SV_ONLY:
        foreach (temp, OM_TPList) {
            if (!temp.getIsBPM())
            {
                counter ++;
            }
        }
        return counter;
        break;

    case cOM_Common::TPFlag::BPM_ONLY:
        foreach (temp, OM_TPList) {
            if (temp.getIsBPM())
            {
                counter ++;
            }
        }
        return counter;
        break;

    default:
        return 0;
        break;
    }

    return counter;
}
double cOM_TPList::getAverage(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(0);

    if (onlyFlag == cOM_Common::TPFlag::SV_BPM_ONLY ||
        onlyFlag == cOM_Common::TPFlag::INVALID )
    {
        qDebug() << __FUNCTION__ << "does not support SV_BPM_ONLY and INVALID";
        return 0;
    }

    double output = 0;
    QList<double> TPList;
    double TPeach;

    TPList = getValueList(onlyFlag);

    foreach (TPeach, TPList) {
        output += TPeach;
    }

    output /= TPList.count();
    return output;
}
double cOM_TPList::getDistance(cOM_Common::TPFlag onlyFlag) const
{
    CHECK_EMPTY(0);

    if (onlyFlag == cOM_Common::TPFlag::SV_BPM_ONLY ||
        onlyFlag == cOM_Common::TPFlag::INVALID    )
    {
        qDebug() << __FUNCTION__ << "does not support SV_BPM_ONLY and INVALID";
        return 0;
    }

    QList<double> lengthList,
                  valueList;
    double        distance;

    lengthList = getLengthList(onlyFlag);
    valueList  = getValueList (onlyFlag);

    for (int temp = 0; temp < lengthList.length(); temp++)
    {
        distance += lengthList[temp] * valueList[temp];
    }

    return distance;
}
double cOM_TPList::getDistance(int index)
{
    CHECK_EMPTY(0);

    double length,
           value;

    length = getLength(index);
    value  = OM_TPList[index].getValue();

    return length * value;
}
QStringList cOM_TPList::toString() const
{
    CHECK_EMPTY(QStringList({}));

    cOM_TP temp;
    QStringList output;
    foreach (temp, OM_TPList) {
        output.append(temp.toString());
    }

    return output;
}

// OPERS
cOM_TP &cOM_TPList::operator [](int i) {    
    if (i < OM_TPList.count()){
        return OM_TPList[i];
    } else {
        qDebug() << "cOM_TP Index Does not Exist, returning first index." << "\r\n";
        return OM_TPList[0];
    }
}
cOM_TP cOM_TPList::operator [](int i) const {
    if (i < OM_TPList.count()){
        return OM_TPList[i];
    } else {
        qDebug() << "cOM_TP Index Does not Exist, returning default." << "\r\n";
        return cOM_TP();
    }
}

void cOM_TPList::multiplyValue(const cOM_TPList rhsOM_TPList, bool limitFlag)
{
    CHECK_EMPTY();

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

    lhsValueList = getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);
    rhsValueList = rhsOM_TPList.getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);
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

            lhsValueList[lhsTemp] *= rhsValueList[rhsTemp];

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
void cOM_TPList::divideValue(const cOM_TPList rhsOM_TPList, bool limitFlag)
{
    CHECK_EMPTY();

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

    lhsValueList = getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);
    rhsValueList = rhsOM_TPList.getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);
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
    CHECK_EMPTY();

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

    lhsValueList = getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);
    rhsValueList = rhsOM_TPList.getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);
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
    CHECK_EMPTY();

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

    lhsValueList = getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);
    rhsValueList = rhsOM_TPList.getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);
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
    CHECK_EMPTY();

    QList<double> newValueList,
                  oldValueList;
    double temp;

    oldValueList = this->getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);

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
    CHECK_EMPTY();

    QList<double> newValueList,
                  oldValueList;
    double temp;

    oldValueList = getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);

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
    CHECK_EMPTY();

    QList<double> newValueList,
                  oldValueList;
    double temp;

    oldValueList = getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);

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
    CHECK_EMPTY();

    QList<double> newValueList,
                  oldValueList;
    double temp;

    oldValueList = getValueList(cOM_Common::TPFlag::SV_BPM_ONLY);

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
    CHECK_EMPTY();

    QList<double> newOffsetList,
                  oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList(cOM_Common::TPFlag::SV_BPM_ONLY);

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
    CHECK_EMPTY();

    QList<double> newOffsetList,
                  oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList(cOM_Common::TPFlag::SV_BPM_ONLY);

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
    CHECK_EMPTY();

    QList<double> newOffsetList,
                  oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList(cOM_Common::TPFlag::SV_BPM_ONLY);

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
    CHECK_EMPTY();

    QList<double> newOffsetList,
                  oldOffsetList;
    double temp;

    oldOffsetList = getOffsetList(cOM_Common::TPFlag::SV_BPM_ONLY);

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
    CHECK_EMPTY();

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
    CHECK_EMPTY();

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

cOM_Common::TPFlag cOM_TPList::isUniform()
{
    CHECK_EMPTY(cOM_Common::TPFlag::INVALID);

    cOM_TP temp;

    cOM_Common::TPFlag output = OM_TPList[0].getIsBPM() ? cOM_Common::TPFlag::BPM_ONLY : cOM_Common::TPFlag::SV_ONLY;

    foreach (temp, OM_TPList)
    {
        if (output != (temp.getIsBPM() ? cOM_Common::TPFlag::BPM_ONLY : cOM_Common::TPFlag::SV_ONLY))
        {
            return cOM_Common::TPFlag::SV_BPM_ONLY; // If it isn't uniform then return this
        }
    }

    return output;
}
bool cOM_TPList::isEmpty() const
{
    return getSize() == 0;
}
void cOM_TPList::limitValues(double maxSV, double minSV, double maxBPM, double minBPM)
{
    CHECK_EMPTY();

    cOM_TP temp;

    foreach (temp, OM_TPList) {
        temp.limitValues(maxSV, minSV, maxBPM, minBPM);
    }
}
QList<int> cOM_TPList::indexList(cOM_Common::TPFlag onlyFlag)
{
    CHECK_EMPTY(QList<int>({}));

    if (onlyFlag == cOM_Common::TPFlag::SV_BPM_ONLY ||
        onlyFlag == cOM_Common::TPFlag::INVALID)
    {
        qDebug() << __FUNCTION__ << "does not support SV_BPM_ONLY and INVALID";
        return QList<int>({});
    }

    QList<int> indexList;

    for (int counter = 0; counter < OM_TPList.length(); counter ++)
    {
        switch (onlyFlag) {
        case cOM_Common::TPFlag::SV_ONLY:
            if (!OM_TPList[counter].getIsBPM())
            {
                indexList.append(counter);
            }
            break;
        case cOM_Common::TPFlag::BPM_ONLY:
            if (OM_TPList[counter].getIsBPM())
            {
                indexList.append(counter);
            }
            break;

        default:
            break;
        }

    }

    return indexList;
}
void cOM_TPList::adjustToAverage(double averageSV, int adjustIndex)
{
    CHECK_EMPTY();

    if (isUniform() == cOM_Common::TPFlag::SV_BPM_ONLY ||
        isUniform() == cOM_Common::TPFlag::INVALID)
    {
        qDebug() << __FUNCTION__ << "only works with uniform lists.";
        return;
    }

    // To elaborate what this function does:
    // This function changes a single TP (via adjustIndex) to achieve the specified averageSV
    // This function cannot adjust TP at the end as it doesn't contribute to the average SV

    // If adjusting the TP cannot achieve the specified average SV then it'll fail

    if (adjustIndex > OM_TPList.length())
    {
        qDebug() << "Adjust Index cannot be longer than OM_TPList Length.";
        return;
    } else if (adjustIndex == (OM_TPList.length() - 1))
    {
        qDebug() << "Cannot adjust last index.";
        return;
    }

    double oldTotalDistance,
           newTotalDistance,
           oldAdjustLength,
           newAdjustValue,
           netDistance; // otherDistance as in the distance covered by other TP(s)
                          // I can't find a better wording for this

    // TOTAL LENGTH = 70000
    // NEW AVE = 1.0
    // OLD AVE = 1.075

    oldTotalDistance = getDistance(isUniform());
    newTotalDistance = averageSV * getLength();

    // We calculate the distance that needs to be added/subtracted
    netDistance = newTotalDistance - oldTotalDistance;
    oldAdjustLength = getLength(adjustIndex);

    newAdjustValue = OM_TPList[adjustIndex].getValue() + (netDistance / oldAdjustLength);

    switch (isUniform()) {
    case cOM_Common::TPFlag::SV_ONLY:
        if (newAdjustValue > 10.0 || newAdjustValue < 0.1)
        {
            qDebug() << __FUNCTION__ << "New Value exceeds limit";
        }
        break;

    case cOM_Common::TPFlag::BPM_ONLY:
        if (newAdjustValue < 0)
        {
            qDebug() << __FUNCTION__ << "New Value exceeds limit";
        }
        break;

    default:
        qDebug() << __FUNCTION__ << "an unexpected error has occured";
        break;
    }

    OM_TPList[adjustIndex].setValue(newAdjustValue);
    OM_TPList[adjustIndex].limitValues();

}

void cOM_TPList::makeUnique()
{
    CHECK_EMPTY();

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




