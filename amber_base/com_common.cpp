#include "com_common.h"

namespace cOM_Common{
cOM_Common()
{

}

void whatHO(omInfo &info, QTextBrowser   *tb)
{
    whatHO(info, tb->toPlainText());
}
void whatHO(omInfo &info, QLineEdit      *line)
{
    whatHO(info, line->text());
}
void whatHO(omInfo &info, QPlainTextEdit *pte)
{
    whatHO(info, pte->toPlainText());
}
void whatHO(omInfo &info, QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    whatHO(info, HOSplit);
}
void whatHO(omInfo &info, QStringList &HOList)
{
    // Empty Load Fail
    if (HOList.isEmpty())
    {
        info.setLoadFail(true);
        info.setfailMsg("Recieved Empty Input.");
        return;
    }


    QString temp;

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
            colonIndex   < 0 ||
            openBrIndex  < 0 ||
            pipeIndex    < 0 ||
            closeBrIndex < 0 || // If index is -1, means that the character does not exist.

            colonIndex   > openBrIndex  ||
            openBrIndex  > pipeIndex    ||
            pipeIndex    > closeBrIndex ||
            closeBrIndex < colonIndex   // As the indexes should be increasing, all of these conditions shouldn't be true
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
            info.setfailMsg(QString("Bad Input: ") + temp);
            return;
        }
    }
}

void whatTP(omInfo &info, QTextBrowser   *tb)
{
    whatTP(info, tb->toPlainText());
}
void whatTP(omInfo &info, QLineEdit      *line)
{
    whatTP(info, line->text());
}
void whatTP(omInfo &info, QPlainTextEdit *pte)
{
    whatTP(info, pte->toPlainText());
}
void whatTP(omInfo &info, QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    whatTP(info, TPSplit);
}
void whatTP(omInfo &info, QStringList &TPList)
{
    // Empty Load Fail
    if (TPList.isEmpty())
    {
        info.setLoadFail(true);
        info.setfailMsg("Recieved Empty Input.");
        return;
    }

    QString temp;

    foreach (temp, TP) {

        if (temp.split(",").count() != 8) // All TP must have 7 commas <Hence 8 parts>
        {
            info.setLoadFail(true);
            info.setfailMsg(QString("Bad Input: ") + temp);
            return;
        }

        switch (temp.split(",")[6].toInt()) {
        // All TP will have a parameter on the 7th index that indicates the type
        case 0: // 0 indicates the TP is SV
            info.setIsSV(true);
            break;

        case 1: // 1 indicates the TP is BPM
            info.setIsBPM(true);
            break;

        default: // Otherwise it doesn't make sense
            info.setLoadFail(true);
            info.setfailMsg(QString("Bad Input: ") + temp);
            break;
        }
    }
}

bool isHO(QTextBrowser *tb)
{
    return isHO(tb->toPlainText());
}
bool isHO(QLineEdit *line)
{
    return isHO(line->text());
}
bool isHO(QPlainTextEdit *pte)
{
    return isHO(pte->toPlainText());
}
bool isHO(QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    return isHO(HOSplit);
}
bool isHO(QStringList &HOList)
{
    omInfo info();
    whatHO(info, HOList);

    return info.getIsHO();
}

bool isTP(QTextBrowser *tb)
{
    return isTP(tb->toPlainText());
}
bool isTP(QLineEdit *line)
{
    return isTP(line->text());
}
bool isTP(QPlainTextEdit *pte)
{
    return isTP(pte->toPlainText());
}
bool isTP(QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    return isTP(TPSplit);
}
bool isTP(QStringList &TPList)
{
    omInfo info();
    whatTP(info, TPList);

    return info.getIsTP();
}

bool isEHO(QTextBrowser   *tb)
{
    return isEHO(tb->toPlainText());
}
bool isEHO(QLineEdit      *line)
{
    return isEHO(line->text());
}
bool isEHO(QPlainTextEdit *pte)
{
    return isEHO(pte->toPlainText());
}
bool isEHO(QString &EHO)
{
    // Reference: 01:52:511 (112511|3) -

    QStringList EHOSplit;

    EHOSplit = EHO.split("\n", QString::SkipEmptyParts);

    return isEHO(EHOSplit);
}
bool isEHO(QStringList &EHO)
{
    // Reference: 01:52:511 (112511|3) -
    QString temp;

    short colonIndex,
          openBrIndex,
          pipeIndex,
          closeBrIndex;

    foreach (temp, EHO) {

        colonIndex   = temp.indexOf(":");
        openBrIndex  = temp.indexOf("(");
        pipeIndex    = temp.indexOf("|");
        closeBrIndex = temp.indexOf(")");

        if (
            colonIndex   < 0 ||
            openBrIndex  < 0 ||
            pipeIndex    < 0 ||
            closeBrIndex < 0 || // If index is -1, means that the character does not exist.

            colonIndex   > openBrIndex  ||
            openBrIndex  > pipeIndex    ||
            pipeIndex    > closeBrIndex ||
            closeBrIndex < colonIndex   // As the indexes should be increasing, all of these conditions shouldn't be true
           )
        {
            return false;
        }
    }
    return true;
}

void whatOM_Type(omInfo &info, QTextBrowser *tb)
{
    whatOM_Type(info, tb->toPlainText());
}
void whatOM_Type(omInfo &info, QLineEdit *line)
{
    whatOM_Type(info, line->text());
}
void whatOM_Type(omInfo &info, QPlainTextEdit *pte)
{
    whatOM_Type(info, pte->toPlainText());
}
void whatOM_Type(omInfo &info, QString &input)
{
    QStringList inputSplit;

    inputSplit = input.split("\n", QString::SkipEmptyParts);

    whatOM_Type(info, inputSplit);
}
void whatOM_Type(omInfo &info, QStringList &input)
{
    // Empty Load Fail
    if (input.isEmpty())
    {
        info.setLoadFail(true);
        info.setfailMsg("Recieved Empty Input.");
        return;
    }

    // If it's not a HO, it will trigger loadFail
    whatHO(info, input);
    if (!info.getLoadFail())
    {
        return; // This means it's a HO
    }

    // We reset loadFail for TP
    info.setLoadFail(false);

    // If it's not a TP, it will trigger loadFail
    whatTP(info, input);
    if (!info.getLoadFail())
    {
        return; // This means it's a TP
    }

    // Since both failed, we return true for loadFail
    info.setLoadFail(true);
}

void assertHO(QTextBrowser *tb)
{
    assertHO(tb->toPlainText());
}
void assertHO(QLineEdit *line)
{
    assertHO(line->text());
}
void assertHO(QPlainTextEdit *pte)
{
    assertHO(pte->toPlainText());
}
void assertHO(QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    assertHO(HOSplit);
}
void assertHO(QStringList &HOList)
{
    omInfo info();
    whatHO(info, HOList);

    if (!info.getIsHO())
    {
        throw HOLoadFail(HOList);
    }
}

void assertTP(QTextBrowser *tb)
{
    assertTP(tb->toPlainText());
}
void assertTP(QLineEdit *line)
{
    assertTP(line->text());
}
void assertTP(QPlainTextEdit *pte)
{
    assertTP(pte->toPlainText());
}
void assertTP(QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    assertTP(TPSplit);
}
void assertTP(QStringList &TPList)
{
    omInfo info();
    whatTP(info, TPList);

    if (!info.getIsTP())
    {
        throw TPLoadFail(TPList);
    }
}

void assertIndex(int &value, int &max)
{
    if (value < 0 || value >= max)
    {
        throw indexOutOfRange(value, max);
    }
}
void assertEmpty(QList &value)
{
    if (value.isEmpty())
    {
        throw emptyException("cOM_HOList");
    }
}
void assertDivByZero(double &value)
{
    if (value == 0)
    {
        throw divideByZeroException();
    }
}
void assertOffsetValid(int &newOffset)
{
    if (newOffset < cOM_Common::MINIMUM_OFFSET || newOffset > cOM_Common::MAXIMUM_OFFSET)
    {
        throw offsetOutOfRange(newOffset, cOM_Common::MINIMUM_OFFSET, cOM_Common::MAXIMUM_OFFSET);
    }
}
void assertLengthMatch(int &given, int &expected)
{
    if (given != expected)
    {
        throw lengthMismatch(given, expected);
    }
}
void assertInvalidFormat(QString &value)
{
    omInfo info;
    whatOM_Type(info, value);

    if (info.getLoadFail())
    {
        throw invalidFormat(value, info.getFailMsg());
    }
}

}

namespace omInfo
{
omInfo()
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

bool getIsHO() const
{
    return isHO;
}
bool getIsTP() const
{
    return isTP;
}
bool getIsEHO() const
{
    return isEHO;
}
bool getIsSV() const
{
    return isSV;
}
bool getIsBPM() const
{
    return isBPM;
}
bool getIsNN() const
{
    return isNN;
}
bool getIsLN() const
{
    return isLN;
}
bool getLoadFail() const
{
    return loadFail;
}

void setIsHO(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    isHO = value;
}
void setIsTP(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    isTP = value;
}
void setIsEHO(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        setIsHO(true); // EHO is a HO
    }

    isEHO = value;
}
void setIsSV(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        setIsTP(true); // SV is a TP
    }

    isSV = value;
}
void setIsBPM(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        setIsTP(true); // BPM is a TP
    }

    isBPM = value;
}
void setIsNN(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        setIsHO(true); // NN is a HO
    }

    isNN = value;
}
void setIsLN(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        setIsHO(true); // LN is a HO
    }

    isLN = value;
}
void setLoadFail(bool value)
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

QString getfailMsg() const
{
    return failMsg;
}
void setfailMsg(const QString value)
{
    failMsg = value;
}
}

columnOutOfRange::columnOutOfRange(double newValue, double min, double max)
{
    msg = QString("Attempt to use column out of range [%1 - %2]: %3")
            .arg(min).arg(max).arg(newValue);
    badValue = newValue;
}
offsetOutOfRange::offsetOutOfRange(double newValue, double min, double max)
{
    msg = QString("Attempt to use offset out of range [%1 - %2]: %3")
            .arg(min).arg(max).arg(newValue);
    badValue = newValue;
}
keysOutOfRange::keysOutOfRange(int newValue, int min, int max)
{
    msg = QString("Attempt to use key out of range [%1 - %2]: %3")
            .arg(min).arg(max).arg(newValue)
            << "(Did you forget to set the key?)";
    badValue = newValue;
}
xAxisOutOfRange::xAxisOutOfRange(int newValue, int min, int max)
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
TPLoadFail::TPLoadFail(QString newValue)
{
    msg = QString("Failed to load input as TP: %1").arg(newValue);
    badValue = newValue;
}
TPLoadFail::TPLoadFail(QStringList newValue)
{
    msg = QString("Failed to load input as TP: %1").arg(newValue.join("\n"));
    badValue = newValue;
}
HOLoadFail::HOLoadFail(QString newValue)
{
    msg = QString("Failed to load input as HO: %1").arg(newValue);
    badValue = newValue;
}
HOLoadFail::HOLoadFail(QStringList newValue)
{
    msg = QString("Failed to load input as TP: %1").arg(newValue.join("\n"));
    badValue = newValue;
}
indexOutOfRange::indexOutOfRange(int newValue, int max)
{
    msg = QString("Index is out of bounds (Given: %1), (Expected: %2)")
            .arg(newValue).arg(max);
    badValue = newValue;
}
lengthMismatch::lengthMismatch(int givenLength, int expectedLength)
{
    msg = QString("Length Mismatch (Given: %1), (Expected: %2)")
            .arg(givenLength).arg(expectedLength);
    givenValue = givenLength;
    expectedValue = expectedLength;
}
invalidFormat::invalidFormat(QString &newValue, QString &newFailMsg)
{
    msg = QString("Invalid input: %1").arg(newValue)
            << "\n" << newFailMsg;
                                                        ;
    badValue = newValue;
    failMsg = newFailMsg;
}
