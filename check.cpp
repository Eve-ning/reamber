#include "check.h"

namespace CHECK {

bool EHO(QString EHO)
{
    bool returnFlag;
    returnFlag = EHO.contains("(") &&
                 EHO.contains(")") &&
                 EHO.contains("|") &&
                 EHO.contains("-");
    return returnFlag;
}
bool HO(QString HO)
{
    bool returnFlag;
    returnFlag = (HO.count(QRegExp(",")) == 5) &&
                !(HO.contains("(") &&
                  HO.contains(")") &&
                  HO.contains("|") &&
                  HO.contains("-"));
    return returnFlag;
}
bool TP(QString TP)
{
    bool returnFlag;
    returnFlag = (TP.count(QRegExp(",")) == 7) &&
                !(TP.contains("(") &&
                  TP.contains(")") &&
                  TP.contains("|") &&
                  TP.contains("-"));
    return returnFlag;
}

bool EHO(QPlainTextEdit *box)
{
    return EHO(box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}
bool HO(QPlainTextEdit *box)
{
    return HO(box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}
bool TP(QPlainTextEdit *box)
{
    return TP(box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}

bool EHO(QStringList EHOList)
{
    if (EHOList.length() != 0)
    {
    return EHO(EHOList[0]);
    }
    return false;
}
bool HO(QStringList HOList)
{
    if (HOList.length() != 0)
    {
    return HO(HOList[0]);
    }
    return false;
}
bool TP(QStringList TPList)
{
    if (TPList.length() != 0)
    {
    return TP(TPList[0]);
    }
    return false;
}

bool HO_NN(QString HO_NN)
{
    if (!HO_NN.contains(",")){
        return false;
    }
    return HO_NN.count(QRegExp(",")) == 4;
}
bool HO_LN(QString HO_LN)
{
    if (!HO_LN.contains(",")){
        return false;
    }
    return HO_LN.count(QRegExp(",")) == 5;
}
bool TP_SV(QString TP_SV)
{
    if (!TP_SV.contains(",")){
        return false;
    }
    return TP_SV.split(",", QString::SkipEmptyParts)[6] == "0";
}
bool TP_BPM(QString TP_BPM)
{
    if (!TP_BPM.contains(",")){
        return false;
    }
    return TP_BPM.split(",", QString::SkipEmptyParts)[6] == "1";
}

}
