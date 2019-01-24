#include "common.h"

Common::Common()
{

}

Info Common::whatHO(const QTextBrowser   *tb)
{
    QString temp = tb->toPlainText();
    return whatHO(temp);
}
Info Common::whatHO(const QLineEdit      *line)
{
    QString temp = line->text();
    return whatHO(temp);
}
Info Common::whatHO(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return whatHO(temp);
}
Info Common::whatHO(const QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    return whatHO(HOSplit);
}
Info Common::whatHO(const QStringList &HOList)
{
    // Empty Load Fail
    assertEmpty(HOList, __FUNCTION__);

    QString temp;
    Info info = Info();

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

Info Common::whatTP(const QTextBrowser   *tb)
{
    QString temp = tb->toPlainText();
    return whatTP(temp);
}
Info Common::whatTP(const QLineEdit      *line)
{
    QString temp = line->text();
    return whatTP(temp);
}
Info Common::whatTP(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return whatTP(temp);
}
Info Common::whatTP(const QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    return whatTP(TPSplit);
}
Info Common::whatTP(const QStringList &TPList)
{
    // Empty Load Fail
    assertEmpty(TPList, __FUNCTION__);

    Info info = Info();
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

Info Common::whatOM_Type(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    return whatOM_Type(temp);
}
Info Common::whatOM_Type(const QLineEdit *line)
{
    QString temp = line->text();
    return whatOM_Type(temp);
}
Info Common::whatOM_Type(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return whatOM_Type(temp);
}
Info Common::whatOM_Type(const QString &input)
{
    QStringList inputSplit;

    inputSplit = input.split("\n", QString::SkipEmptyParts);

    return whatOM_Type(inputSplit);
}
Info Common::whatOM_Type(const QStringList &input)
{
    // Empty Load Fail
    assertEmpty(input, __FUNCTION__);

    Info info;

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

bool Common::isHO(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    return isHO(temp);
}
bool Common::isHO(const QLineEdit *line)
{
    QString temp = line->text();
    return isHO(temp);
}
bool Common::isHO(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return isHO(temp);
}
bool Common::isHO(const QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    return isHO(HOSplit);
}
bool Common::isHO(const QStringList &HOList)
{
    return whatHO(HOList).getIsHO();
}
bool Common::isTP(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    return isTP(temp);
}
bool Common::isTP(const QLineEdit *line)
{
    QString temp = line->text();
    return isTP(temp);
}
bool Common::isTP(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return isTP(temp);
}
bool Common::isTP(const QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    return isTP(TPSplit);
}
bool Common::isTP(const QStringList &TPList)
{
    return whatTP(TPList).getIsTP();
}
bool Common::isEHO(const QTextBrowser   *tb)
{
    QString temp = tb->toPlainText();
    return isEHO(temp);
}
bool Common::isEHO(const QLineEdit      *line)
{
    QString temp = line->text();
    return isEHO(temp);
}
bool Common::isEHO(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    return isEHO(temp);
}
bool Common::isEHO(const QString &EHO)
{
    // Reference: 01:52:511 (112511|3) -

    QStringList EHOSplit;

    EHOSplit = EHO.split("\n", QString::SkipEmptyParts);

    return isEHO(EHOSplit);
}
bool Common::isEHO(const QStringList &EHO)
{
    return whatHO(EHO).getIsEHO();
}

void Common::assertHO(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    assertHO(temp);
}
void Common::assertHO(const QLineEdit *line)
{
    QString temp = line->text();
    assertHO(temp);
}
void Common::assertHO(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    assertHO(temp);
}
void Common::assertHO(const QString &HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    assertHO(HOSplit);
}
void Common::assertHO(const QStringList &HOList)
{
    if (!whatHO(HOList).getIsHO())
    {
        AExc(AExc::HO_LOADFAIL,
             QString("Input: ") + HOList.join("\n"));
        return;
    }
}
void Common::assertTP(const QTextBrowser *tb)
{
    QString temp = tb->toPlainText();
    assertTP(temp);
}
void Common::assertTP(const QLineEdit *line)
{
    QString temp = line->text();
    assertTP(temp);
}
void Common::assertTP(const QPlainTextEdit *pte)
{
    QString temp = pte->toPlainText();
    assertTP(temp);
}
void Common::assertTP(const QString &TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    assertTP(TPSplit);
}
void Common::assertTP(const QStringList &TPList)
{
    if (!whatTP(TPList).getIsTP())
    {
        AExc(AExc::TP_LOADFAIL,
             QString("Input: ") + TPList.join("\n"));
    }
}

void Common::assertIndex(const int &value, const int &max)
{
    if (value > max)
    {
        AExc(AExc::INDEX_OUT_OF_RANGE,
             QString("Given: %1\n"
             "(Inclusive)\n"
             "Maximum : %2")
             .arg(value)
             .arg(max));
    }
}
void Common::assertEmpty(const QList<T> &value, const QString &funcName)
{
    if (value.isEmpty())
    {
        AExc(AExc::IS_EMPTY,
             QString("Within this context:") + funcName);
        return;
    }
}
void Common::assertEmpty(const QStringList &value, const QString &funcName)
{
    if (value.isEmpty())
    {
        AExc(AExc::IS_EMPTY,
             QString("In function:") + funcName);
        return;
    }
}
void Common::assertDivByZero(const double &value)
{
    if (value == 0)
    {
        AExc(AExc::DIVIDE_BY_ZERO);
        return;
    }
}
void Common::assertOffsetValid(const int &newOffset)
{
    if (newOffset < MINIMUM_OFFSET || newOffset > MAXIMUM_OFFSET)
    {
        AExc(AExc::VALUE_OUT_OF_RANGE,
             QString("Offset %1 is out of range: [%2 - %3]")
             .arg(newOffset)
             .arg(MINIMUM_OFFSET)
             .arg(MAXIMUM_OFFSET));
        return;
    }
}
void Common::assertLengthMatch(const int &given, const int &expected)
{
    if (given != expected)
    {
        AExc(AExc::LENGTH_MISMATCH,
             QString("Length Mismatch: (Given: %1) (Expected: %2)")
             .arg(given)
             .arg(expected));
        return;
    }
}
void Common::assertLoadFail(const Info &info)
{
    if (info.getLoadFail())
    {
        AExc(AExc::LOADFAIL_RESTRICT);
        return;
    }
}

