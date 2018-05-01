#include "common.h"

amberCommon::amberCommon()
{

}

omInfo amberCommon::whatHO(const QTextBrowser   *tb)
{
    QString temp = tb->toPlainText();
    return whatHO(temp);
}
omInfo amberCommon::whatHO(const QLineEdit      *line)
{
    QString temp = line->text();
    return whatHO(temp);
}
omInfo amberCommon::whatHO(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return whatHO(temp);
}
omInfo amberCommon::whatHO(const QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    return whatHO(HOSplit);
}
omInfo amberCommon::whatHO(const QStringList &HOList)
{
    // Empty Load Fail
    assertEmpty(HOList, __FUNCTION__);

    QString temp;
    omInfo info = omInfo();

    short colonIndex,
          openBrIndex,
          pipeIndex,
          closeBrIndex;

    // Check other indexes
    foreach (temp, HOList) {

        colonIndex   = temp.indexOf(":");
        openBrIndex  = temp.indexOf("(");
        pipeIndex    = temp.indexOf("|");
        closeBrIndex = temp.indexOf(")");

        // EHO CASE
        if (
            colonIndex   > 0 &&
            openBrIndex  > 0 &&
            pipeIndex    > 0 &&
            closeBrIndex > 0 && // If index is -1, means that the character does not exist.

            colonIndex   < openBrIndex  &&
            openBrIndex  < pipeIndex    &&
            pipeIndex    < closeBrIndex   // As the indexes should be increasing, all of these conditions should be true
           )
        {
            info.setIsEHO(true);
        }

        // HO_NN CASE
        else if (temp.split(",").count() == 6 &&  // All HO has 5 commas
                 temp.split(":").count() == 5   ) // HO_NN has 4 colons
        {
            info.setIsNN(true);
        }

        // HO_LN CASE
        else if (temp.split(",").count() == 6 &&  // All HO has 5 commas
                 temp.split(":").count() == 6   ) // HO_LN has 5 colons
        {
            info.setIsLN(true);
        }

        // INVALID CASE
        else
        {
            info.setLoadFail(true);
            info.setFailMsg(QString("Bad Input: ") + temp);
        }
    }

    return info;
}

omInfo amberCommon::whatTP(const QTextBrowser   *tb)
{
    QString temp = tb->toPlainText();
    return whatTP(temp);
}
omInfo amberCommon::whatTP(const QLineEdit      *line)
{
    QString temp = line->text();
    return whatTP(temp);
}
omInfo amberCommon::whatTP(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return whatTP(temp);
}
omInfo amberCommon::whatTP(const QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    return whatTP(TPSplit);
}
omInfo amberCommon::whatTP(const QStringList &TPList)
{
    // Empty Load Fail
    assertEmpty(TPList, __FUNCTION__);

    omInfo info = omInfo();
    QString temp;

    foreach (temp, TPList) {

        if (temp.split(",").count() != 8) // All TP must have 7 commas <Hence 8 parts>
        {
            info.setLoadFail(true);
            info.setFailMsg(QString("Bad Input: ") + temp);
            return info;
        }

        switch (temp.split(",")[6].toInt())
        {
        // All TP will have a parameter on the 7th index that indicates the type
        case 0: // 0 indicates the TP is SV
            info.setIsSV(true);
            break;

        case 1: // 1 indicates the TP is BPM
            info.setIsBPM(true);
            break;

        default: // Otherwise it doesn't make sense
            info.setLoadFail(true);
            info.setFailMsg(QString("Bad Input: ") + temp);
            break;
        }
    }

    return info;
}

omInfo amberCommon::whatOM_Type(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    return whatOM_Type(temp);
}
omInfo amberCommon::whatOM_Type(const QLineEdit *line)
{
    QString temp = line->text();
    return whatOM_Type(temp);
}
omInfo amberCommon::whatOM_Type(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return whatOM_Type(temp);
}
omInfo amberCommon::whatOM_Type(const QString &input)
{
    QStringList inputSplit;

    inputSplit = input.split("\n", QString::SkipEmptyParts);

    return whatOM_Type(inputSplit);
}
omInfo amberCommon::whatOM_Type(const QStringList &input)
{
    // Empty Load Fail
    assertEmpty(input, __FUNCTION__);

    omInfo info;

    // If it's not a HO, it will trigger loadFail
    info = whatHO(input);
    if (!info.getLoadFail())
    {
        return info; // This means it's a HO
    }

    // We reset loadFail for TP
    info.setLoadFail(false);

    // If it's not a TP, it will trigger loadFail
    info = whatTP(input);
    if (!info.getLoadFail())
    {
        return info; // This means it's a TP
    }

    // Since both failed, we return true for loadFail
    info.setLoadFail(true);
    return info;
}

bool amberCommon::isHO(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    return isHO(temp);
}
bool amberCommon::isHO(const QLineEdit *line)
{
    QString temp = line->text();
    return isHO(temp);
}
bool amberCommon::isHO(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return isHO(temp);
}
bool amberCommon::isHO(const QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    return isHO(HOSplit);
}
bool amberCommon::isHO(const QStringList &HOList)
{
    return whatHO(HOList).getIsHO();
}
bool amberCommon::isTP(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    return isTP(temp);
}
bool amberCommon::isTP(const QLineEdit *line)
{
    QString temp = line->text();
    return isTP(temp);
}
bool amberCommon::isTP(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return isTP(temp);
}
bool amberCommon::isTP(const QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    return isTP(TPSplit);
}
bool amberCommon::isTP(const QStringList &TPList)
{
    return whatTP(TPList).getIsTP();
}
bool amberCommon::isEHO(const QTextBrowser   *tb)
{
    QString temp = tb->toPlainText();
    return isEHO(temp);
}
bool amberCommon::isEHO(const QLineEdit      *line)
{
    QString temp = line->text();
    return isEHO(temp);
}
bool amberCommon::isEHO(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return isEHO(temp);
}
bool amberCommon::isEHO(const QString &EHO)
{
    // Reference: 01:52:511 (112511|3) -

    QStringList EHOSplit;

    EHOSplit = EHO.split("\n", QString::SkipEmptyParts);

    return isEHO(EHOSplit);
}
bool amberCommon::isEHO(const QStringList &EHO)
{
    return whatHO(EHO).getIsEHO();
}

void amberCommon::assertHO(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    assertHO(temp);
}
void amberCommon::assertHO(const QLineEdit *line)
{
    QString temp = line->text();
    assertHO(temp);
}
void amberCommon::assertHO(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    assertHO(temp);
}
void amberCommon::assertHO(const QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    assertHO(HOSplit);
}
void amberCommon::assertHO(const QStringList &HOList)
{
    if (!whatHO(HOList).getIsHO())
    {
        throw HOLoadFail(HOList);
    }
}
void amberCommon::assertTP(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    assertTP(temp);
}
void amberCommon::assertTP(const QLineEdit *line)
{
    QString temp = line->text();
    assertTP(temp);
}
void amberCommon::assertTP(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    assertTP(temp);
}
void amberCommon::assertTP(const QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    assertTP(TPSplit);
}
void amberCommon::assertTP(const QStringList &TPList)
{
    if (!whatTP(TPList).getIsTP())
    {
        throw TPLoadFail(TPList);
    }
}
void amberCommon::assertIndex(const int &value, const int &max)
{
    if (value < 0 || value > max)
    {
        throw indexOutOfRange(value, max);
    }
}
void amberCommon::assertEmpty(const QList<T> &value, const QString &funcName)
{
    if (value.isEmpty())
    {
        throw emptyException(funcName);
    }
}
void amberCommon::assertEmpty(const QStringList &value, const QString &funcName)
{
    if (value.isEmpty())
    {
        throw emptyException(funcName);
    }
}
void amberCommon::assertDivByZero(const double &value)
{
    if (value == 0)
    {
        throw divideByZeroException();
    }
}
void amberCommon::assertOffsetValid(const int &newOffset)
{
    if (newOffset < amberCommon::MINIMUM_OFFSET || newOffset > amberCommon::MAXIMUM_OFFSET)
    {
        throw offsetOutOfRange(newOffset, amberCommon::MINIMUM_OFFSET, amberCommon::MAXIMUM_OFFSET);
    }
}
void amberCommon::assertLengthMatch(const int &given, const int &expected)
{
    if (given != expected)
    {
        throw lengthMismatch(given, expected);
    }
}
void amberCommon::assertLoadFail(const omInfo &info)
{
    if (info.getLoadFail())
    {
        throw loadFailException(info);
    }
}

omInfo::omInfo()
{
    isHO     = false;
    isTP     = false;
    isEHO    = false;
    isSV     = false;
    isBPM    = false;
    isNN     = false;
    isLN     = false;
    loadFail = false;
}
omInfo::omInfo(const bool &allCondition)
{
    isHO     = allCondition;
    isTP     = allCondition;
    isEHO    = allCondition;
    isSV     = allCondition;
    isBPM    = allCondition;
    isNN     = allCondition;
    isLN     = allCondition;
    loadFail = false;
}

QString omInfo::toString(const bool &type) const
{
    QString output;

    if (type)
    {
        if (isHO    ){ output.append("isHO"    ); }
        if (isTP    ){ output.append("isTP"    ); }
        if (isEHO   ){ output.append("isEHO"   ); }
        if (isSV    ){ output.append("isSV"    ); }
        if (isBPM   ){ output.append("isBPM"   ); }
        if (isNN    ){ output.append("isNN"    ); }
        if (isLN    ){ output.append("isLN"    ); }
        if (loadFail){ output.append("loadFail"); }
    }
    else
    {
        if (!isHO    ){ output.append("isHO"    ); }
        if (!isTP    ){ output.append("isTP"    ); }
        if (!isEHO   ){ output.append("isEHO"   ); }
        if (!isSV    ){ output.append("isSV"    ); }
        if (!isBPM   ){ output.append("isBPM"   ); }
        if (!isNN    ){ output.append("isNN"    ); }
        if (!isLN    ){ output.append("isLN"    ); }
        if (!loadFail){ output.append("loadFail"); }
    }
    return output;
}

bool omInfo::getIsHO() const
{
    return isHO;
}
bool omInfo::getIsTP() const
{
    return isTP;
}
bool omInfo::getIsEHO() const
{
    return isEHO;
}
bool omInfo::getIsSV() const
{
    return isSV;
}
bool omInfo::getIsBPM() const
{
    return isBPM;
}
bool omInfo::getIsNN() const
{
    return isNN;
}
bool omInfo::getIsLN() const
{
    return isLN;
}
bool omInfo::getLoadFail() const
{
    return loadFail;
}

void omInfo::setIsHO(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    isNN = value; // We set NN & LN & EHO as according to the value as HO is the super
    isLN = value;
    isEHO = value;

    isHO = value;
}
void omInfo::setIsTP(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    isSV  = value; // We set SV & BPM as according to the value as TP is the super
    isBPM = value;

    isTP = value;
}
void omInfo::setIsEHO(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isHO = true; // EHO is a HO
    }

    isEHO = value;

    if (!(isEHO || isNN || isLN)) // If all of them are false we disable isHO
    {
        isHO = false;
    }
}
void omInfo::setIsSV(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isTP = true; // SV is a TP
    }

    isSV = value;

    if (!(isSV || isBPM)) // If both are false, we disable isTP
    {
        isTP = false;
    }
}
void omInfo::setIsBPM(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isTP = true; // BPM is a TP
    }

    isBPM = value;

    if (!(isSV || isBPM)) // If both are false, we disable isTP
    {
        isTP = false;
    }
}
void omInfo::setIsNN(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isHO = true; // NN is a HO
    }

    isNN = value;

    if (!(isEHO || isNN || isLN)) // If all of them are false we disable isHO
    {
        isHO = false;
    }
}
void omInfo::setIsLN(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isHO = true; // LN is a HO
    }

    isLN = value;

    if (!(isEHO || isNN || isLN)) // If all of them are false we disable isHO
    {
        isHO = false;
    }
}
void omInfo::setLoadFail(bool value)
{
    // On load fail, all other values will be set to false
    loadFail = value;
    if (loadFail)
    {
        isHO   = false;
        isTP   = false;
        isEHO  = false;
        isSV   = false;
        isBPM  = false;
        isNN   = false;
        isLN   = false;
    }
}

QStringList omInfo::getAllTrue() const
{
    QStringList output;
    if(isHO    ){ output.append("isHO\t"    ); }
    if(isTP    ){ output.append("isTP\t"    ); }
    if(isEHO   ){ output.append("isEHO\t"   ); }
    if(isSV    ){ output.append("isSV\t"    ); }
    if(isBPM   ){ output.append("isBPM\t"   ); }
    if(isNN    ){ output.append("isNN\t"    ); }
    if(isLN    ){ output.append("isLN\t"    ); }
    if(loadFail){ output.append("loadFail\t"); }

    return output;
}
QStringList omInfo::getAllFalse() const
{
    QStringList output;
    if(!isHO    ){ output.append("isHO\t"    ); }
    if(!isTP    ){ output.append("isTP\t"    ); }
    if(!isEHO   ){ output.append("isEHO\t"   ); }
    if(!isSV    ){ output.append("isSV\t"    ); }
    if(!isBPM   ){ output.append("isBPM\t"   ); }
    if(!isNN    ){ output.append("isNN\t"    ); }
    if(!isLN    ){ output.append("isLN\t"    ); }
    if(!loadFail){ output.append("loadFail\t"); }

    return output;
}

QString omInfo::getFailMsg() const
{
    return failMsg;
}
void omInfo::setFailMsg(const QString value)
{
    failMsg = value;
}

columnOutOfRange::columnOutOfRange(const double newValue, const double min, const double max)
{
    msg = QString("Attempt to use column out of range [%1 - %2]: %3")
            .arg(min).arg(max).arg(newValue);
    badValue = newValue;
}
offsetOutOfRange::offsetOutOfRange(const double newValue, const double min, const double max)
{
    msg = QString("Attempt to use offset out of range [%1 - %2]: %3")
            .arg(min).arg(max).arg(newValue);
    badValue = newValue;
}
keysOutOfRange::keysOutOfRange(const int newValue, const int min, const int max)
{
    msg = QString("Attempt to use key out of range [%1 - %2]: %3")
            .arg(min).arg(max).arg(newValue)
            + "(Did you forget to set the key?)";
    badValue = newValue;
}
xAxisOutOfRange::xAxisOutOfRange(const int newValue, const int min, const int max)
{
    msg = QString("Attempt to use x-Axis out of range [%1 - %2]: %3")
            .arg(min).arg(max).arg(newValue);
    badValue = newValue;
}
emptyException::emptyException(QString objName)
{
    msg = QString("%1 is empty, therefore most functions are not available.")
            .arg(objName);
}
TPLoadFail::TPLoadFail(const QString newValue)
{
    msg = QString("Failed to load input as TP: %1").arg(newValue);
    badValue = newValue;
}
TPLoadFail::TPLoadFail(const QStringList newValue)
{
    msg = QString("Failed to load input as TP: %1").arg(newValue.join("\n"));
    badValue = newValue.join("\n");
}
HOLoadFail::HOLoadFail(const QString newValue)
{
    msg = QString("Failed to load input as HO: %1").arg(newValue);
    badValue = newValue;
}
HOLoadFail::HOLoadFail(const QStringList newValue)
{
    msg = QString("Failed to load input as TP: %1").arg(newValue.join("\n"));
    badValue = newValue.join("\n");
}
indexOutOfRange::indexOutOfRange(const int newValue, const int max)
{
    msg = QString("Index is out of bounds (Given: %1), (Expected: %2)")
            .arg(newValue).arg(max);
    badValue = newValue;
}
lengthMismatch::lengthMismatch(const int givenLength, const int expectedLength)
{
    msg = QString("Length Mismatch (Given: %1), (Expected: %2)")
            .arg(givenLength).arg(expectedLength);
    givenValue = givenLength;
    expectedValue = expectedLength;
}
divideByZeroException::divideByZeroException()
{
    msg = "Attempted to divide by Zero";
}
loadFailException::loadFailException(const omInfo info)
{
    msg = QString("loadFail is active. loadFailMsg: ").append(info.getFailMsg());
}
