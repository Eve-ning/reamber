#include "check.h"

namespace CHECK {

bool    EHO (QTextBrowser *tb,
            QString EHO)
{
    bool returnFlag;
    returnFlag = EHO.contains("(") &&
            EHO.contains(")") &&
            EHO.contains("|") &&
            EHO.contains("-");
    if (!returnFlag) {
        STATMSG("False");
    }
    else
    {
        STATMSG("True");
    }
    return returnFlag;
}
bool    HO  (QTextBrowser *tb,
            QString HO)
{
    bool returnFlag;
    returnFlag = (HO.count(QRegExp(",")) == 5) &&
            !(HO.contains("(") &&
              HO.contains(")") &&
              HO.contains("|") &&
              HO.contains("-"));
    if (!returnFlag) {
        STATMSG("False");
    }
    else
    {
        STATMSG("True");
    }
    return returnFlag;
}
bool    TP  (QTextBrowser *tb,
            QString TP)
{
    bool returnFlag;
    returnFlag = (TP.count(QRegExp(",")) == 7) &&
                !(TP.contains("(") &&
                  TP.contains(")") &&
                  TP.contains("|") &&
                  TP.contains("-"));
    if (!returnFlag) {
        STATMSG("False");
    }
    else
    {
        STATMSG("True");
    }
    return returnFlag;
}

bool    EHO (QTextBrowser *tb,
            QPlainTextEdit *box)
{
    return EHO(tb, box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}
bool    HO  (QTextBrowser *tb,
            QPlainTextEdit *box)
{
    return HO(tb, box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}
bool    TP  (QTextBrowser *tb,
            QPlainTextEdit *box)
{
    return TP(tb, box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}

bool    EHO (QTextBrowser *tb,
            QStringList EHOList)
{
    if (EHOList.length() != 0)
    {
    return EHO(tb, EHOList[0]);
    }
    return false;
}
bool    HO  (QTextBrowser *tb,
            QStringList HOList)
{
    if (HOList.length() != 0)
    {
    return HO(tb, HOList[0]);
    }
    return false;
}
bool    TP  (QTextBrowser *tb,
            QStringList TPList)
{
    if (TPList.length() != 0)
    {
    return TP(tb, TPList[0]);
    }
    return false;
}

bool    HO_NN   (QTextBrowser *tb,
                QString HO_NN)
{
    bool returnFlag;
    returnFlag = HO_NN.count(QRegExp(",")) == 4;
    if (!returnFlag) {
        STATMSG("False");
    }
    else
    {
        STATMSG("True");
    }
    return returnFlag;
}
bool    HO_LN   (QTextBrowser *tb,
                QString HO_LN)
{
    bool returnFlag;
    returnFlag = HO_LN.count(QRegExp(",")) == 5;
    if (!returnFlag) {
        STATMSG("False");
    }
    else
    {
        STATMSG("True");
    }
    return returnFlag;
}
bool    TP_SV   (QTextBrowser *tb,
                QString TP_SV)
{
    bool returnFlag;
    returnFlag = TP_SV.split(",", QString::SkipEmptyParts)[6] == "0";
    if (!returnFlag) {
        STATMSG("False");
    }
    else
    {
        STATMSG("True");
    }
    return returnFlag;
}
bool    TP_BPM  (QTextBrowser *tb,
                QString TP_BPM)
{
    bool returnFlag;
    returnFlag = TP_BPM.split(",", QString::SkipEmptyParts)[6] == "1";
    if (!returnFlag) {
        STATMSG("False");
    }
    else
    {
        STATMSG("True");
    }
    return returnFlag;
}

QString INPUT_ALL(QTextBrowser *tb,
                  QString input)
{   
    if (EHO(tb, input))
    {
        return "EHO";
    }
    else if (HO(tb, input))
    {
        return "HO";
    }
    else if (TP(tb, input))
    {
        return "TP";
    }
    else
    {
        return "INVALID";
    }
}
QString INPUT_ALL(QTextBrowser *tb,
                  QStringList input)
{
    QString inputEach;
    QString inputType;

    inputType = INPUT_ALL(tb, input[0]);

    foreach (inputEach, input)
    {
        if (INPUT_ALL(tb, inputEach) != inputType)
        {
            inputType = "MIXED";
            break;
        }
    }

    return inputType;
}

}
