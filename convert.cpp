#include "convert.h"

namespace CONVERT {

//Converts
double COLUMN_CODEtoVALUE(double columnCode, double noOfKeys)
{
    return round(((columnCode / 512 * noOfKeys * 2 + 1) / 2) - 1);
}
double COLUMN_VALUEtoCODE(double columnValue, double noOfKeys)
{
    return round(((columnValue + 1) * 2 - 1) / 2 * 512 / noOfKeys);
}

QList<double> EHOtoOFFSETLIST(QString EHO)
{
    QList<double> offsetList;
    QStringList parameterList;
    QString parameter;

    if (CHECK::EHO(EHO))
    {
        parameterList = EHO.mid(EHO.indexOf("(",1) + 1,
                                            EHO.indexOf(")",1) - EHO.indexOf("(",1) - 1
                                            ).split(",", QString::SkipEmptyParts);
        foreach(parameter, parameterList)
        {
            offsetList.append(parameter.split("|")[0].toDouble());
        }
        return offsetList;
    }
    else
    {
        offsetList.append(0.0);
        return offsetList;
    }
    return offsetList;
}
QList<int> EHOtoCOLUMNLIST(QString EHO)
{
    QList<int> columnList;
    QStringList parameterList;
    QString parameter;

    if (CHECK::EHO(EHO))
    {
        parameterList = EHO.mid(EHO.indexOf("(",1) + 1,
                                            EHO.indexOf(")",1) - EHO.indexOf("(",1) - 1
                                            ).split(",", QString::SkipEmptyParts);
        foreach(parameter, parameterList)
        {
            columnList.append(parameter.split("|")[1].toInt());
        }
        return columnList;
    }
    else
    {
        columnList.append(0);
        return columnList;
    }

}
QList<double> HOtoOFFSETLIST(QStringList HOList)
{
    QList<double> offsetList;
    QString hitObject;

    if (CHECK::HO(HOList[0]))
    {
        foreach(hitObject, HOList)
        {
            offsetList.append(hitObject.split(",")[2].toDouble());
        }
        return offsetList;
    }
    else
    {
        offsetList.append(0.0);
        return offsetList;
    }
}
QList<int> HOtoCOLUMNLIST(QStringList HOList, int keyCount)
{
    QList<int> columnList;
    QString hitObject;

    if (CHECK::HO(HOList[0]))
    {
        foreach(hitObject, HOList)
        {
            columnList.append(COLUMN_CODEtoVALUE(
                                  hitObject.split(",")[2].toInt(), (double) keyCount));
        }
        return columnList;
    }
    else
    {
        columnList.append(0);
        return columnList;
    }
}
QList<double> TPtoOFFSETLIST(QStringList TPList)
{
    QList<double> offsetList;
    QString timingPoint;

    if (CHECK::TP(TPList[0]))
    {
        foreach(timingPoint, TPList)
        {
            offsetList.append(timingPoint.split(",")[0].toDouble());
        }
        return offsetList;
    }
    else
    {
        offsetList.append(0.0);
        return offsetList;
    }
}
QList<double> TPtoCODELIST(QStringList TPList)
{
    QList<double> codeList;
    QString timingPoint;

    if (CHECK::TP(TPList[0]))
    {
        foreach(timingPoint, TPList)
        {
            codeList.append(timingPoint.split(",")[1].toDouble());
        }
        return codeList;
    }
    else
    {
        codeList.append(0.0);
        return codeList;
    }
}

QStringList OMtoBASIC(QLabel *messageLabel,
                      bool acceptEHO,
                      bool acceptHO,
                      bool acceptTP,
                      QStringList input,
                      int noOfKeys)
{

    bool isEditorHitObject, isHitObject, isTimingPoint;

    QStringList output,
            partList;
    QString partString, inputString;

    isEditorHitObject = CHECK::EHO(input);
    isHitObject = CHECK::HO(input);
    isTimingPoint = CHECK::TP(input);

    if (!isEditorHitObject &&
            !isHitObject &&
            !isTimingPoint)
    {
        messageLabel->setText("STATUS: No Valid Input Detected");
        messageLabel->setStyleSheet("QLabel { color:red; }");
        return output;
    }

    // The logic is the program will return if it DOESN'T ACCEPT the input but it RECIEVES the input
    if ((isEditorHitObject && !acceptEHO) ||
            (isHitObject && !acceptHO) ||
            (isTimingPoint && !acceptTP))
    {
        messageLabel->setText("STATUS: Input Rejected");
        messageLabel->setStyleSheet("QLabel { color:red; }");
        return output;
    }

    if (isEditorHitObject)
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
                output.append(COMPILE::BASIC_HO(QString::number(noOfKeys),
                                                                 partString.split("|", QString::SkipEmptyParts)[0],
                              partString.split("|", QString::SkipEmptyParts)[1]));
            }
        }

        messageLabel->setText("STATUS: Converted Editor Hit Object");
        messageLabel->setStyleSheet("QLabel { color:green; }");

    }
    else if (isHitObject)
    {
        foreach (inputString, input) {

            if (inputString.isEmpty())
            {
                continue;
            }

            partList = inputString.split(",", QString::SkipEmptyParts);

            double columnKey;

            // Gets the key column through calculation and rounds to 0 D.P.
            columnKey = COLUMN_CODEtoVALUE(partList[0].toDouble(), noOfKeys);

            if (CHECK::HO_NN(inputString))
            {
                output.append(COMPILE::BASIC_HO(
                                  QString::number(noOfKeys),
                                  partList[2],
                              QString::number(columnKey)));

            }
            else if (CHECK::HO_LN(inputString))
            {
                output.append(COMPILE::BASIC_HO(
                                  QString::number(noOfKeys),
                                  partList[2],
                              QString::number(columnKey),
                              partList[5].mid(0,partList[5].indexOf(":",1))));
            }
        }

        messageLabel->setText("STATUS: Converted Hit Object");
        messageLabel->setStyleSheet("QLabel { color:green; }");

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

            QString timingPointValue;

            if (CHECK::TP_SV(inputString))
            {
                timingPointValue = QString::number(-100.0 / partList[1].toDouble());
            }
            else if (CHECK::TP_BPM(inputString))
            {
                timingPointValue = QString::number(60000.0 / partList[1].toDouble());
            }

            output.append(COMPILE::BASIC_TP(
                              partList[0],
                          timingPointValue,
                          CHECK::TP_SV(inputString) ? QString("SV") : QString("BPM")));

        }

        messageLabel->setText("STATUS: Converted Timing Point");
        messageLabel->setStyleSheet("QLabel { color:green; }");

    }
    return output;
}

QStringList BASICtoOM(QLabel *messageLabel,
                      QStringList input)
{
    bool isHitObject, isTimingPoint;

    QStringList output,
            partList;
    QString inputString;

    isHitObject   = input[0].split(",", QString::SkipEmptyParts)[0] == "HITOBJECT";
    isTimingPoint = input[0].split(",", QString::SkipEmptyParts)[0] == "TIMINGPOINT";

    // The logic is the program will return if it DOESN'T ACCEPT the input but it RECIEVES the input
    if (isHitObject || isTimingPoint)
    {
        messageLabel->setText("STATUS: Input Rejected");
        messageLabel->setStyleSheet("QLabel { color:red; }");
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
            columnCode = CONVERT::COLUMN_VALUEtoCODE(partList[3].toDouble(), partList[1].toDouble());

            if (partList[4] == "-1")
            {
                output.append(COMPILE::OM_NN(QString::number(columnCode),
                                                       partList[2]));
            }
            else
            {
                output.append(COMPILE::OM_LN(QString::number(columnCode),
                                                       partList[2],
                              partList[4]));
            }
        }

        messageLabel->setText("STATUS: Hit Object");
        messageLabel->setStyleSheet("QLabel { color:green; }");

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
                output.append(COMPILE::OM_BPM(partList[1],
                              QString::number(60000.0 / partList[2].toDouble())));
            }
            else if (partList[3] == "SV")
            {
                output.append(COMPILE::OM_SV(partList[1],
                              QString::number(-100 / partList[2].toDouble())));
            }
        }

        messageLabel->setText("STATUS: Timing Point");
        messageLabel->setStyleSheet("QLabel { color:green; }");

    }
    return output;
}

QStringList HOtoEXTENSIONLIST(QStringList HOList)
{
    QStringList extensionList;
    QString extension;
    QStringList extensionSplitList;

    if (CHECK::HO(HOList))
    {
        foreach(extension, extensionList)
        {
            extensionSplitList = extension.split(",", QString::SkipEmptyParts);
            extensionList.append(extensionSplitList[3] + "," +
                                 extensionSplitList[4] + "," +
                                 extensionSplitList[5]);
        }
        return extensionList;
    } else
    {
        extensionList.append("0.0");
        return extensionList;
    }
}

QList<double> TPtoSVVALUELIST(QStringList TPList)
{

}

QList<double> TPtoBPMVALUELIST(QStringList TPList)
{

}

QList<double> TPtoSVCODELIST(QStringList TPList)
{

}

QList<double> TPtoBPMCODELIST(QStringList TPList)
{

}

double TP_CODEtoVALUE(double TPCode)
{

}

double TP_VALUEtoCODE(double TPValue)
{

}

}
