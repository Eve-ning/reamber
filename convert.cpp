#include "convert.h"

namespace CONVERT {

//Converts
double          COLUMN_CODEtoVALUE  (QTextBrowser *tb, double columnCode, double noOfKeys)
{
    double output;
    output = round(((columnCode / 512 * noOfKeys * 2 + 1) / 2) - 1);
    STATMSG("Value: " + QString::number(output));
    return output;
}
double          COLUMN_VALUEtoCODE  (QTextBrowser *tb, double columnValue, double noOfKeys)
{
    double output;
    output = round(((columnValue + 1) * 2 - 1) / 2 * 512 / noOfKeys);
    STATMSG("Code: " + QString::number(output));
    return output;
}
double          TP_BPMCODEtoVALUE   (QTextBrowser *tb, double TPCode)
{
    double output;
    if (TPCode == 0) {
        STATMSG("Recieved division by 0, returning 100.");
        output = 100;
    }
    else
    {
        output = 60000 / TPCode;
    }
    STATMSG("Code: " + QString::number(output));
    return output;
}
double          TP_BPMVALUEtoCODE   (QTextBrowser *tb, double TPValue)
{
    double output;
    if (TPValue == 0) {
        STATMSG("Recieved division by 0, returning 100.");
        output = 100;
    }
    else
    {
        output = 60000 / TPValue;
    }
    STATMSG("Code: " + QString::number(output));
    return output;
}
double          TP_SVCODEtoVALUE    (QTextBrowser *tb, double TPCode)
{
    double output;
    if (TPCode == 0) {
        STATMSG("Recieved division by 0, returning -100.");
        output = -100;
    }
    else
    {
        output = -100 / TPCode;
    }
    STATMSG("Code: " + QString::number(output));
    return output;
}
double          TP_SVVALUEtoCODE    (QTextBrowser *tb, double TPValue)
{
    double output;
    if (TPValue == 0) {
        STATMSG("Recieved division by 0, returning -100.");
        output = -100;
    }
    else
    {
        output = -100 / TPValue;
    }
    STATMSG("Code: " + QString::number(output));

    return output;
}

QList<double>   EHOtoOFFSETLIST     (QTextBrowser *tb, QString EHO)
{
    QList<double> offsetList;
    QStringList parameterList;
    QString parameter;

    if (CHECK::EHO(tb, EHO))
    {
        parameterList = EHO.mid(EHO.indexOf("(",1) + 1,
                                            EHO.indexOf(")",1) - EHO.indexOf("(",1) - 1
                                            ).split(",", QString::SkipEmptyParts);
        foreach(parameter, parameterList)
        {
            offsetList.append(parameter.split("|")[0].toDouble());
        }
    }
    else
    {
        offsetList.append(0.0);
    }
    STATMSG("Offset List");
    STATMSG(offsetList);
    return offsetList;  
}
QList<int>      EHOtoCOLUMNLIST     (QTextBrowser *tb, QString EHO)
{
    QList<int> columnList;
    QStringList parameterList;
    QString parameter;

    if (CHECK::EHO(tb, EHO))
    {
        parameterList = EHO.mid(EHO.indexOf("(",1) + 1,
                                            EHO.indexOf(")",1) - EHO.indexOf("(",1) - 1
                                            ).split(",", QString::SkipEmptyParts);
        foreach(parameter, parameterList)
        {
            columnList.append(parameter.split("|")[1].toInt());
        }        
    }
    else
    {
        columnList.append(0);

    }
    STATMSG("Column List");
    STATMSG(columnList);
    return columnList;
}

QList<double>   HOtoOFFSETLIST      (QTextBrowser *tb, QStringList HOList)
{
    QList<double> offsetList;
    QString hitObject;

    if (CHECK::HO(tb, HOList[0]))
    {
        foreach(hitObject, HOList)
        {
            offsetList.append(hitObject.split(",")[2].toDouble());
        }
    }
    else
    {
        offsetList.append(0.0);
    }
    STATMSG("Offset List");
    STATMSG(offsetList);
    return offsetList;
}
QList<int>      HOtoCOLUMNLIST      (QTextBrowser *tb, QStringList HOList, int keyCount)
{
    QList<int> columnList;
    QString hitObject;

    if (CHECK::HO(tb, HOList[0]))
    {
        foreach(hitObject, HOList)
        {
            columnList.append(COLUMN_CODEtoVALUE(tb,
                              hitObject.split(",")[2].toInt(), (double) keyCount));
        }
    }
    else
    {
        columnList.append(0);
    }
    STATMSG("Column List");
    STATMSG(columnList);
    return columnList;
}
QStringList     HOtoEXTENSIONLIST   (QTextBrowser *tb, QStringList HOList)
{
    QStringList extensionList;
    QString extension;
    QStringList extensionSplitList;

    if (CHECK::HO(tb, HOList))
    {
        foreach(extension, extensionList)
        {
            extensionSplitList = extension.split(",", QString::SkipEmptyParts);
            extensionList.append(extensionSplitList[3] + "," +
                                 extensionSplitList[4] + "," +
                                 extensionSplitList[5]);
        }
    } else
    {
        extensionList.append("0.0");
    }
    STATMSG("Column List");
    STATMSG(extensionList);
    return extensionList;
}

QList<double>   TPtoOFFSETLIST      (QTextBrowser *tb, QStringList TPList)
{
    QList<double> offsetList;
    QString timingPoint;

    if (CHECK::TP(tb, TPList[0]))
    {
        foreach(timingPoint, TPList)
        {
            offsetList.append(timingPoint.split(",")[0].toDouble());
        }
    }
    else
    {
        offsetList.append(0.0);
    }
    STATMSG("Offset List");
    STATMSG(offsetList);
    return offsetList;
}
QList<double>   TPtoCODELIST        (QTextBrowser *tb, QStringList TPList)
{
    QList<double> codeList;
    QString timingPoint;

    if (CHECK::TP(tb, TPList[0]))
    {
        foreach(timingPoint, TPList)
        {
            codeList.append(timingPoint.split(",")[1].toDouble());
        }
    }
    else
    {
        codeList.append(0.0);
    }
    STATMSG("Code List");
    STATMSG(codeList);
    return codeList;
}

QList<double>   TPtoSVVALUELIST     (QTextBrowser *tb, QStringList TPList)
{
    QList<double> valueList;
    QString timingPoint;

    if (CHECK::TP(tb, TPList[0]))
    {
        foreach(timingPoint, TPList)
        {
            if (CHECK::TP_BPM(tb, timingPoint))
            {
                continue;
            }

             valueList.append(TP_SVCODEtoVALUE(tb, timingPoint.split(",")[1].toDouble()));
        }
    }
    else
    {
        valueList.append(0.0);
    }
    STATMSG("Value List");
    STATMSG(valueList);
    return valueList;
}
QList<double>   TPtoBPMVALUELIST    (QTextBrowser *tb, QStringList TPList)
{
    QList<double> valueList;
    QString timingPoint;

    if (CHECK::TP(tb, TPList[0]))
    {
        foreach(timingPoint, TPList)
        {
            if (CHECK::TP_SV(tb, timingPoint))
            {
                continue;
            }

             valueList.append(TP_BPMCODEtoVALUE(tb, timingPoint.split(",")[1].toDouble()));
        }
    }
    else
    {
        valueList.append(0.0);
    }
    STATMSG("Value List");
    STATMSG(valueList);
    return valueList;
}
QList<double>   TPtoSVCODELIST      (QTextBrowser *tb, QStringList TPList)
{
    QList<double> codeList;
    QString timingPoint;

    if (CHECK::TP(tb, TPList[0]))
    {
        foreach(timingPoint, TPList)
        {
            if (CHECK::TP_BPM(tb, timingPoint))
            {
                continue;
            }

             codeList.append(timingPoint.split(",")[1].toDouble());
        }
    }
    else
    {
        codeList.append(0.0);
    }
    STATMSG("Code List");
    STATMSG(codeList);
    return codeList;
}
QList<double>   TPtoBPMCODELIST     (QTextBrowser *tb, QStringList TPList)
{
    QList<double> codeList;
    QString timingPoint;

    if (CHECK::TP(tb, TPList[0]))
    {
        foreach(timingPoint, TPList)
        {
            if (CHECK::TP_SV(tb, timingPoint))
            {
                continue;
            }

             codeList.append(timingPoint.split(",")[1].toDouble());
        }
    }
    else
    {
        codeList.append(0.0);
    }
    STATMSG("Code List");
    STATMSG(codeList);
    return codeList;
}


QStringList OMtoBASIC(QTextBrowser *tb,
                      bool acceptEHO,
                      bool acceptHO,
                      bool acceptTP,
                      QStringList input,
                      int noOfKeys)
{

    bool isEHO, isHO, isTP;

    QStringList output,
            partList;
    QString partString, inputString;

    isEHO = CHECK::EHO(tb, input);
    isHO  = CHECK::HO (tb, input);
    isTP  = CHECK::TP (tb, input);

    if (!isEHO &&
        !isHO &&
        !isTP)
    {
        STATMSG("Format rejected <NO MATCH>.");
        STATMSG("Input: ");
        STATMSG(input);
        return output;
    }

    // The logic is the program will return if it DOESN'T ACCEPT the input but it RECIEVES the input
    if ((isEHO && !acceptEHO) ||
        (isHO  && !acceptHO ) ||
        (isTP  && !acceptTP ))
    {
        STATMSG("Format rejected <MISMATCH>.");
        STATMSG("Input:");
        STATMSG(input);
        STATMSG("Parameters:");
        STATMSG("isEHO: "     + isEHO     ? "TRUE" : "FALSE");
        STATMSG("acceptEHO: " + acceptEHO ? "TRUE" : "FALSE");
        STATMSG("isHO: "      + isHO      ? "TRUE" : "FALSE");
        STATMSG("acceptHO: "  + acceptHO  ? "TRUE" : "FALSE");
        STATMSG("isTP: "      + isTP      ? "TRUE" : "FALSE");
        STATMSG("acceptTP: "  + acceptTP  ? "TRUE" : "FALSE");
        return output;
    }

    if (isEHO)
    {
        // Reads each line from the input
        foreach (inputString, input) {

            if (inputString.isEmpty())
            {
                continue;
            }

            // Mid trims the current line from '(' and ')'
            // Split then splits them by ',' into different notes
            partList = inputString.mid(inputString.indexOf("(", 1) + 1,
                                       inputString.indexOf(")", 1) - inputString.indexOf("(", 1) - 1)
                                       .split(",", QString::SkipEmptyParts);

            foreach (partString, partList){
                output.append(COMPILE::BASIC_HO(tb,
                                                QString::number(noOfKeys),
                                                partString.split("|", QString::SkipEmptyParts)[0],
                                                partString.split("|", QString::SkipEmptyParts)[1]));
            }
        }
    }
    else if (isHO)
    {
        foreach (inputString, input) {

            if (inputString.isEmpty())
            {
                continue;
            }

            partList = inputString.split(",", QString::SkipEmptyParts);

            double columnKey;

            // Gets the key column through calculation and rounds to 0 D.P.
            columnKey = COLUMN_CODEtoVALUE(tb,
                                           partList[0].toDouble(), noOfKeys);

            if (CHECK::HO_NN(tb, inputString))
            {
                output.append(COMPILE::BASIC_HO(tb,
                                                QString::number(noOfKeys),
                                                partList[2],
                                                QString::number(columnKey)));

            }
            else if (CHECK::HO_LN(tb, inputString))
            {
                output.append(COMPILE::BASIC_HO(tb,
                                                QString::number(noOfKeys),
                                                partList[2],
                                                QString::number(columnKey),
                                                partList[5].mid(0,partList[5].indexOf(":",1))));
            }
        }
    }
    else if (isTP)
    {
        foreach (inputString, input)
        {
            if (inputString.isEmpty())
            {
                continue;
            }
            partList = inputString.split(",", QString::SkipEmptyParts);

            QString timingPointValue;

            if (CHECK::TP_SV(tb, inputString))
            {
                timingPointValue = QString::number(-100.0 / partList[1].toDouble());
            }
            else if (CHECK::TP_BPM(tb, inputString))
            {
                timingPointValue = QString::number(60000.0 / partList[1].toDouble());
            }

            output.append(COMPILE::BASIC_TP(tb,
                                            partList[0],
                                            timingPointValue,
                                            CHECK::TP_SV(tb, inputString) ? QString("SV") : QString("BPM")));
        }
    }
    STATMSG("Output List:");
    STATMSG(output);
    return output;
}

QStringList BASICtoOM(QTextBrowser *tb, QStringList input)
{
    bool isHitObject, isTimingPoint;

    QStringList output,
            partList;
    QString inputString;

    isHitObject   = input[0].split("|", QString::SkipEmptyParts)[0] == "HITOBJECT";
    isTimingPoint = input[0].split("|", QString::SkipEmptyParts)[0] == "TIMINGPOINT";

    // If it's neither a hitobject and timingpoint then return
    if (isHitObject && isTimingPoint)
    {
        STATMSG("Format Rejected <NO MATCH>");
        STATMSG("Input: ");
        STATMSG(input);
        return output;
    }

    if (isHitObject)
    {
        foreach (inputString, input) {

            if (inputString.isEmpty())
            {
                continue;
            }

            partList = inputString.split("|", QString::SkipEmptyParts);

            double columnCode;

            // Gets the key column through calculation and rounds to 0 D.P.
            columnCode = CONVERT::COLUMN_VALUEtoCODE(tb, partList[3].toDouble(), partList[1].toDouble());

            if (partList[4] == "-1")
            {
                output.append(COMPILE::OM_NN(tb,
                                             QString::number(columnCode),
                                             partList[2]));
            }
            else
            {
                output.append(COMPILE::OM_LN(tb,
                                             QString::number(columnCode),
                                             partList[2],
                                             partList[4]));
            }
        }
    }
    else if (isTimingPoint)
    {
        foreach (inputString, input)
        {
            if (inputString.isEmpty())
            {
                continue;
            }
            partList = inputString.split(",", QString::SkipEmptyParts);

            if (partList[3] == "BPM")
            {
                output.append(COMPILE::OM_BPM(tb, partList[1],
                              QString::number(60000.0 / partList[2].toDouble())));
            }
            else if (partList[3] == "SV")
            {
                output.append(COMPILE::OM_SV(tb, partList[1],
                              QString::number(-100 / partList[2].toDouble())));
            }
        }
    }
    STATMSG("Output List:");
    STATMSG(output);
    return output;
}


}
