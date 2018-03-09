#include "compile.h"

namespace COMPILE {

//Compilers
QString OM_NN(QTextBrowser *tb,
              QString xAxis,
              QString offset,
              QString yAxis,
              QString extension)
{
    QString output;
    /* Normal Note: xAxis,yAxis,offset,extension */
    output = xAxis
            + (",")
            + (yAxis)
            + (",")
            + (offset)
            + (",")
            + (extension);
    STATMSG("Output: " + output)
    return output;
}

QString OM_LN(QTextBrowser *tb,
              QString xAxis,
              QString offset,
              QString lnOffset,
              QString yAxis,
              QString lnParameter,
              QString extension)
{
    QString output;
    /* Long Note: xAxis,yAxis,offset,parameter,lnOffset&extension */
    output = xAxis
            + (",")
            + (yAxis)
            + (",")
            + (offset)
            + (",")
            + (lnParameter)
            + (",")
            + (lnOffset)
            + (extension);
    STATMSG("Output: " + output)
    return output;
}

QString OM_BPM(QTextBrowser *tb,
               QString offset,
               QString bpmCode,
               QString extension)
{
    if (bpmCode.toDouble() < 0)
    {
        bpmCode = QString::number(99999999);
    }

    QString output;
    /* BPM Line: offset,code,extension */
    output = offset
            + (",")
            + (bpmCode)
            + (",")
            + (extension);
    STATMSG("Output: " + output)
    return output;
}

QString OM_SV(QTextBrowser *tb,
              QString offset,
              QString svCode,
              QString extension)
{
    if (svCode.toDouble() > -10.0)
    {
        svCode = QString::number(-10.0);
    }
    else if (svCode.toDouble() < -1000.0)
    {
        svCode = QString::number(-1000.0);
    }

    QString output;
    /* SV Line: offset,code,extension */
    output = offset
            + (",")
            + (svCode)
            + (",")
            + (extension);
    STATMSG("Output: " + output)
    return output;
}

QString BASIC_HO(QTextBrowser *tb,
                 QString noOfKeys,
                 QString offset,
                 QString column,
                 QString lnOffset,
                 QString label)
{
    QString output;
    /* HITOBJECT: HITOBJECT|NO_OF_KEYS|OFFSET|COLUMN|LN_OFFSET */
    output = label
            + ("|")
            + (noOfKeys)
            + ("|")
            + (offset)
            + ("|")
            + (column)
            + ("|")
            + (lnOffset);
    STATMSG("Output: " + output)
    return output;
}

QString BASIC_TP(QTextBrowser *tb,
                 QString offset,
                 QString value,
                 QString timingPointType,
                 QString label)
{
    QString output;
    /* TIMINGPOINT: TIMINGPOINT|OFFSET|VALUE|TYPE */
    output = label
            + ("|")
            + (offset)
            + ("|")
            + (value)
            + ("|")
            + (timingPointType);
    STATMSG("Output: " + output)
    return output;
}

/* ProcOutput
void ProcOutput(QTextBrowser *inputBoxObject,
                QTextBrowser *outputBoxObject)
{
    QStringList partVector, rawOutputVector;
    QString rawOutputString;
    double columnCode, timingPointCode;

    //Clear outputBox
    outputBoxObject->clear();

    //Load procOutput into Vector
    rawOutputVector = inputBoxObject->toPlainText().split("\n");

    foreach(rawOutputString, rawOutputVector){
        partVector = rawOutputString.split("|",QString::SkipEmptyParts);

        if (partVector[DEFARGS::HO_LABEL] == "HITOBJECT")
        {
            //hitObjectOutput
            //Calculation of ColumnCode
            columnCode = CONVERT::COLUMN_VALUEtoCODE(partVector[DEFARGS::HO_COLUMN].toDouble(),
                                                             partVector[DEFARGS::HO_NOOFKEYS].toDouble());
            if (partVector[DEFARGS::HO_LNENDOFFSET] == "-1")
            {
                //Normal Note Compile
                outputBoxObject->append(OM_NN(QString::number(columnCode),
                                                                      partVector[DEFARGS::HO_OFFSET]));
            }
            else
            {
                //Long Note Compile
                outputBoxObject->append(OM_LN(QString::number(columnCode),
                                                                      partVector[DEFARGS::HO_OFFSET],
                                                                      partVector[DEFARGS::HO_LNENDOFFSET]));
            }

        }
        else if (partVector[DEFARGS::TP_LABEL] == "TIMINGPOINT")
        {
            //timingPointOutput
            if (partVector[DEFARGS::TP_TYPE] == "BPM")
            {
                //BPM Compile
                timingPointCode = 60000 / partVector[DEFARGS::TP_VALUE].toDouble();
                outputBoxObject->append(OM_BPM(partVector[DEFARGS::TP_OFFSET],
                                                                       QString::number(timingPointCode)));
            }
            else if (partVector[DEFARGS::TP_TYPE] == "BPM")
            {
                //SV Compile
                timingPointCode = -100 / partVector[DEFARGS::TP_VALUE].toDouble();
                outputBoxObject->append(OM_SV(partVector[DEFARGS::TP_OFFSET],
                                                                      QString::number(timingPointCode)));
            }
        }
        else
        {
            //nullOutput
            continue;
        }
    }
}
*/
}
