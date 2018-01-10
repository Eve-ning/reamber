#include "svTool.h"
#include "ui_svTool.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QSplitter>
#include <QStringList>
#include <QRegExp>
#include <QList>
#include <QTextBrowser>
#include <QPen>
#include <QBrush>
#include <QtMath>

/* osu!mania FORMATTING REF
 * Normal Note: 109,192,1020,1,0,0:0:0:0:
 * Long Note: 402,192,73,128,0,388:0:0:0:0:
 * BPM Line: 517,600,4,3,0,20,1,0
 * SV Line: 517,-100,4,3,0,20,0,0
 */
/* DEFAULT EXTENSIONS
 * Normal Note: ,1,0,0:0:0:0:
 * Long Note: :0:0:0:0:
 * BPM Line: ,4,3,0,20,1,0
 * SV Line: ,4,3,0,20,0,0
 */
/* BASIC FORMATTING
 * Format to use:
 * hitObject/editorHitObject:
     * HITOBJECT|NO_OF_KEYS|OFFSET|COLUMN|LN_END_OFFSET
     * NO_OF_KEYS: 1 - 18
 * timingPoint:
     * TIMINGPOINT|OFFSET|VALUE|TYPE
     * VALUE: The processed value of BPM or SV
     * TYPE: SV/BPM
 */
svTool::svTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::svTool)
{
    ui->setupUi(this);

}

svTool::~svTool()
{
    delete ui;
}

//DEFAULT ARGUMENTS
QString def_xAxis            = "256"
       ,def_yAxis            = "192"
       ,def_offset           = "0"
       ,def_lnParameter      = "128,0"
       ,def_lnOffset         = "-1"
       ,def_bpmCode          = "600"
       ,def_svCode           = "-100"
       ,def_bpmValue         = "100"
       ,def_svValue          = "1"
       ,def_column           = "0"
       ,def_noOfKeys         = "4"
       ,def_timingPointLabel = "TIMINGPOINT"
       ,def_hitObjectLabel   = "HITOBJECT"
       ,def_nnExtension      = "1,0,0:0:0:0:"
       ,def_lnExtesion       = ":0:0:0:0:"
       ,def_bpmExtension     = "4,3,0,20,1,0"
       ,def_svExtension      = "4,3,0,20,0,0"
       ,def_timingPointType  = "SV"
;

// ------------------------------------- GENERAL -------------------------------------

//Compilers
QString svTool::compileOMFormatting_NN(QString xAxis,
                                       QString offset,
                                       QString yAxis,
                                       QString extension)
{
    QString output;
    /* Normal Note: xAxis,yAxis,offset,extension */
    output = xAxis
            .append(",")
            .append(yAxis)
            .append(",")
            .append(offset)
            .append(",")
            .append(extension);
    return output;
}
QString svTool::compileOMFormatting_LN(QString xAxis,
                                       QString offset,
                                       QString lnOffset,
                                       QString yAxis,
                                       QString lnParameter,
                                       QString extension)
{
    QString output;
    /* Long Note: xAxis,yAxis,offset,parameter,lnOffset&extension */
    output = xAxis
            .append(",")
            .append(yAxis)
            .append(",")
            .append(offset)
            .append(",")
            .append(lnParameter)
            .append(",")
            .append(lnOffset)
            .append(extension);
    return output;
}
QString svTool::compileOMFormatting_BPM(QString offset,
                                        QString bpmCode,
                                        QString extension)
{
    QString output;
    /* BPM Line: offset,code,extension */
    output = offset
            .append(",")
            .append(bpmCode)
            .append(",")
            .append(extension);
    return output;
}
QString svTool::compileOMFormatting_SV(QString offset,
                                       QString svCode,
                                       QString extension)
{
    QString output;
    /* SV Line: offset,code,extension */
    output = offset
            .append(",")
            .append(svCode)
            .append(",")
            .append(extension);
    return output;
}
QString svTool::compileBASICFormatting_hitObject(QString noOfKeys,
                                                 QString offset,
                                                 QString column,
                                                 QString lnOffset,
                                                 QString label)
{
    QString output;
    /* HITOBJECT: HITOBJECT|NO_OF_KEYS|OFFSET|COLUMN|LN_OFFSET */
    output = label
            .append("|")
            .append(noOfKeys)
            .append("|")
            .append(offset)
            .append("|")
            .append(column)
            .append("|")
            .append(lnOffset);
    return output;
}
QString svTool::compileBASICFormatting_timingPoint(QString offset,
                                                   QString value,
                                                   QString timingPointType,
                                                   QString label)
{
    QString output;
    /* TIMINGPOINT: TIMINGPOINT|OFFSET|VALUE|TYPE */
    output = label
            .append("|")
            .append(offset)
            .append("|")
            .append(value)
            .append("|")
            .append(timingPointType);
    return output;
}
//Converts
double svTool::convertColumnCodeToColumnKey(double columnCode, double noOfKeys)
{
    return round(((columnCode / 512 * noOfKeys * 2 + 1) / 2) - 1);
}
double svTool::convertColumnKeyToColumnCode(double columnKey, double noOfKeys)
{
    return round(((columnKey + 1) * 2 - 1) / 2 * 512 / noOfKeys);
}
QList<double> svTool::convertEditorHitObjectToOffsetList(QString editorHitObject)
{
    QList<double> offsetList;
    QStringList parameterList;
    QString parameter;

    if (svTool::checkEditorHitObject(editorHitObject))
    {
        parameterList = editorHitObject.mid(editorHitObject.indexOf("(",1) + 1,
                                              editorHitObject.indexOf(")",1) - editorHitObject.indexOf("(",1) - 1
                                              ).split(",", QString::SkipEmptyParts);
        foreach(parameter, parameterList)
        {
            offsetList.append(parameter.split("|").at(0).toDouble());
        }
        return offsetList;
    } else
    {
        offsetList.append(0.0);
        return offsetList;
    }
    return offsetList;
}
QList<int> svTool::convertEditorHitObjectToColumnList(QString editorHitObject)
{
    QList<int> columnList;
    QStringList parameterList;
    QString parameter;

    if (svTool::checkEditorHitObject(editorHitObject))
    {
        parameterList = editorHitObject.mid(editorHitObject.indexOf("(",1) + 1,
                                              editorHitObject.indexOf(")",1) - editorHitObject.indexOf("(",1) - 1
                                              ).split(",", QString::SkipEmptyParts);
        foreach(parameter, parameterList)
        {
            columnList.append(parameter.split("|").at(1).toInt());
        }
        return columnList;
    } else
    {
        columnList.append(0);
        return columnList;
    }

}
QList<double> svTool::convertHitObjectToOffsetList(QStringList hitObjectList)
{
    QList<double> offsetList;
    QString hitObject;

    if (svTool::checkHitObject(hitObjectList.at(0)))
    {
        foreach(hitObject, hitObjectList)
        {
            offsetList.append(hitObject.split(",").at(2).toDouble());
        }
        return offsetList;
    } else
    {
        offsetList.append(0.0);
        return offsetList;
    }
}
QList<int> svTool::convertHitObjectToColumnList(QStringList hitObjectList, int keyCount)
{
    QList<int> columnList;
    QString hitObject;

    if (svTool::checkHitObject(hitObjectList.at(0)))
    {
        foreach(hitObject, hitObjectList)
        {
            columnList.append(svTool::convertColumnCodeToColumnKey(
                              hitObject.split(",").at(2).toInt(), (double) keyCount));
        }
        return columnList;
    } else
    {
        columnList.append(0);
        return columnList;
    }
}
QList<double> svTool::convertTimingPointToOffsetList(QStringList timingPointList)
{
    QList<double> offsetList;
    QString timingPoint;

    if (svTool::checkTimingPoint(timingPointList.at(0)))
    {
        foreach(timingPoint, timingPointList)
        {
            offsetList.append(timingPoint.split(",").at(0).toDouble());
        }
        return offsetList;
    } else
    {
        offsetList.append(0.0);
        return offsetList;
    }
}
QList<double> svTool::convertTimingPointToCodeList(QStringList timingPointList)
{
    QList<double> codeList;
    QString timingPoint;

    if (svTool::checkTimingPoint(timingPointList.at(0)))
    {
        foreach(timingPoint, timingPointList)
        {
            codeList.append(timingPoint.split(",").at(1).toDouble());
        }
        return codeList;
    } else
    {
        codeList.append(0.0);
        return codeList;
    }
}

//Checks
bool svTool::checkEditorHitObject(QString editorHitObject)
{
    bool returnFlag;
    returnFlag = editorHitObject.contains("(") &&
                 editorHitObject.contains(")") &&
                 editorHitObject.contains("|") &&
                 editorHitObject.contains("-");
    return returnFlag;
}
bool svTool::checkHitObject(QString hitObject)
{
    bool returnFlag;
    returnFlag = (hitObject.count(QRegExp(",")) == 5) &&
                !(hitObject.contains("(") &&
                  hitObject.contains(")") &&
                  hitObject.contains("|") &&
                  hitObject.contains("-"));
    return returnFlag;
}
bool svTool::checkTimingPoint(QString timingPoint)
{
    bool returnFlag;
    returnFlag = (timingPoint.count(QRegExp(",")) == 7) &&
                !(timingPoint.contains("(") &&
                  timingPoint.contains(")") &&
                  timingPoint.contains("|") &&
                  timingPoint.contains("-"));
    return returnFlag;
}


//Converts data from BASIC FORMATTING to OSU!MANIA FORMATTING
void svTool::compileProcOutput(QTextBrowser *inputBoxObject, QTextBrowser *outputBoxObject)
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

         /* DEBUG
          * ui->console_consoleBox->append(QString("RAW"));
          * ui->console_consoleBox->append(QString(partVector.at(0)));
          * ui->console_consoleBox->append(QString("HITOBJECT Compare"));
          * ui->console_consoleBox->append(QString::number(QString::compare(partVector.at(0),QString("HITOBJECT"),Qt::CaseInsensitive)));
          * ui->console_consoleBox->append(QString("TIMINGPOINT Compare"));
          * ui->console_consoleBox->append(QString::number(QString::compare(partVector.at(0),QString("TIMINGPOINT"),Qt::CaseInsensitive)));
          */

        if (QString::compare(partVector.at(0),QString("HITOBJECT"),Qt::CaseInsensitive) == 0)
        {
            //hitObjectOutput
            //Calculation of ColumnCode
            columnCode = svTool::convertColumnKeyToColumnCode(partVector.at(1).toDouble(), partVector.at(3).toDouble());
            if (QString::compare(partVector.at(4),QString("-1"),Qt::CaseInsensitive) == 0)
            {
                //Normal Note Compile
                outputBoxObject->append(svTool::compileOMFormatting_NN(QString::number(columnCode),partVector.at(2)));
            } else
            {
                //Long Note Compile
                outputBoxObject->append(svTool::compileOMFormatting_LN(QString::number(columnCode),partVector.at(2),partVector.at(4)));
            }

        } else if (QString::compare(partVector.at(0),QString("TIMINGPOINT"),Qt::CaseInsensitive) == 0)
        {
            //timingPointOutput
            if (QString::compare(partVector.at(3),QString("BPM"),Qt::CaseInsensitive) == 0)
            {
                //BPM Compile
                timingPointCode = 60000 / partVector.at(2).toDouble();
                outputBoxObject->append(svTool::compileOMFormatting_BPM(QString(partVector.at(1)),QString::number(timingPointCode)));
            } else if (QString::compare(partVector.at(3),QString("SV"),Qt::CaseInsensitive) == 0)
            {
                //SV Compile
                timingPointCode = -100 / partVector.at(2).toDouble();
                outputBoxObject->append(svTool::compileOMFormatting_SV(QString(partVector.at(1)),QString::number(timingPointCode)));
            }
        } else
        {
            //nullOutput
            continue;
        }
    }
}

// -------------------------------------- INPUT --------------------------------------

// Validation Button
void svTool::on_input_validateButton_clicked()
{
    // Copy over to Debug
    ui->debug_rawInputBox->setPlainText(ui->input_rawInputBox->toPlainText());

    QStringList partVector, rawInputVector;
    QString partString, rawInputString;
    QString noOfKeys;

    // validateType indicates the input type
    enum class inputType
    {
        nullInput, // 0
        editorHitObjectInput, // 1
        hitObjectInput, // 2
        timingPointInput  // 3
    };
    inputType validateType;
    validateType = inputType::nullInput;

    // Set keys
    noOfKeys = ui->input_keysSpinBox->text();
    ui->debug_procInputBox->append(ui->input_keysSpinBox->text());

    // Splits the rawInputBox input into a Vector
    rawInputVector = ui->input_rawInputBox->toPlainText().split("\n");

    // Clears the procInputBox
    ui->debug_procInputBox->clear();

    /*
     * rawInputLine.indexOf("(",1) == -1 <TRUE: Editor Hit Object Input>
     * rawInputLine.indexOf(")",1) == -1 <TRUE: Editor Hit Object Input>
     * rawInputLine.count(QRegExp(",")) > 5) <TRUE: Timing Point Input>
     * rawInputLine.count(QRegExp(",")) <= 5) <TRUE: Hit Object Input>
     */

    // Detect Input
    if (svTool::checkEditorHitObject(rawInputVector.at(0)))
    {
        validateType = inputType::editorHitObjectInput;
        ui->input_statusLabel->setText("STATUS: Editor Hit Object Format detected.");
        ui->input_statusLabel->setStyleSheet("QLabel { color:green; }");
    } else if (svTool::checkHitObject(rawInputVector.at(0)))
    {
        validateType = inputType::hitObjectInput;
        ui->input_statusLabel->setText("STATUS: Hit Object Format detected.");
        ui->input_statusLabel->setStyleSheet("QLabel { color:green; }");
    } else if (svTool::checkTimingPoint(rawInputVector.at(0)))
    {
        validateType = inputType::timingPointInput;
        ui->input_statusLabel->setText("STATUS: Timing Point Format detected.");
        ui->input_statusLabel->setStyleSheet("QLabel { color:green; }");
    } else
    {
        validateType = inputType::nullInput;
        ui->input_statusLabel->setText("STATUS: No Format detected.");
        ui->input_statusLabel->setStyleSheet("QLabel { color:red; }");
    }

    // Switch to generate all data
    switch (validateType){

    case inputType::nullInput:
        break;

    case inputType::editorHitObjectInput:
        // Reads each line from the rawInputVector
        foreach (rawInputString, rawInputVector) {

            // Skips any blank lines
            if(rawInputString.isEmpty()){
                continue;
            }

            // Mid trims the current line from '(' and ')'
            // Split then splits them by ',' into different notes
            partVector = rawInputString.mid(rawInputString.indexOf("(",1) + 1,
                                          rawInputString.indexOf(")",1) - rawInputString.indexOf("(",1) - 1
                                          ).split(",", QString::SkipEmptyParts);

            // For each note append according to format
            foreach (partString, partVector){
                ui->debug_procInputBox->append(
                            QString("HITOBJECT|")
                            .append(QString(noOfKeys))
                            .append(QString("|"))
                            .append(partString)
                            .append(QString("|"))
                            // -1 represents Normal Note
                            .append(QString("-1")));
            }
        }
        break;
    case inputType::hitObjectInput:
        // Reads each line from the rawInputVector
        foreach (rawInputString, rawInputVector) {

            // Skips any blank lines
            if(rawInputString.isEmpty()){
                continue;
            }

            // Splits them into parameters
            partVector = rawInputString.split(",",QString::SkipEmptyParts);

            double columnKey;

            // Gets the key column through calculation and rounds to 0 D.P.
            columnKey = svTool::convertColumnCodeToColumnKey(partVector.at(0).toDouble(), noOfKeys.toDouble());

            if(rawInputString.count(QRegExp(",")) == 4){
                // Detected as Normal Note
                // For each note append according to format
                ui->debug_procInputBox->append(
                            svTool::compileBASICFormatting_hitObject(
                                noOfKeys,partVector.at(2),
                                QString::number(columnKey)));

            } else if (rawInputString.count(QRegExp(",")) == 5){
                // Detected as Long Note
                // For each note append according to format
                ui->debug_procInputBox->append(
                            svTool::compileBASICFormatting_hitObject(
                                noOfKeys,partVector.at(2),
                                QString::number(columnKey),
                                partVector.at(5).mid(0,partVector.at(5).indexOf(":",1))));
            }
        }
        break;

    case inputType::timingPointInput:
        // Reads each line from the rawInputVector
        foreach (rawInputString, rawInputVector)
        {

            // Skips any blank lines
            if(rawInputString.isEmpty())
                continue;

            // Splits them into parameters
            partVector = rawInputString.split(",",QString::SkipEmptyParts);

            QString timingPointValue;

            // Check Type and calculate timingPointValue
            if (partVector.at(6) == QString("0"))
            {
                // Detected as an SV Timing Point
                timingPointValue = QString::number(-100.0 / partVector.at(1).toDouble());
            } else if (partVector.at(6) == QString("1"))
            {
                // Detected as a BPM Timing Point
                timingPointValue = QString::number(60000.0 / partVector.at(1).toDouble());
            }

            // Detected as Normal Note
            // For each note append according to format
            ui->debug_procInputBox->append(
                        svTool::compileBASICFormatting_timingPoint(
                            partVector.at(0),
                            timingPointValue,
                            partVector.at(6) == QString("0") ? QString("SV") : QString("BPM")));

        }
        break;
    }

    // Copy over to other boxes for Input
    ui->stutter_procInputBox->setPlainText(ui->debug_procInputBox->toPlainText());
    ui->copier_procInputBox->setPlainText(ui->debug_procInputBox->toPlainText());
}

// Validation Button 2
void svTool::on_input_validateButton_2_clicked()
{
    // Copy over to Debug
    ui->debug_rawInputBox_2->setPlainText(ui->input_rawInputBox_2->toPlainText());

    QStringList partVector, rawInputVector;
    QString partString, rawInputString;
    QString noOfKeys;

    // validateType indicates the input type
    enum class inputType
    {
        nullInput, // 0
        editorHitObjectInput, // 1
        hitObjectInput, // 2
        timingPointInput  // 3
    };
    inputType validateType;
    validateType = inputType::nullInput;

    // Set keys
    noOfKeys = ui->input_keysSpinBox_2->text();
    ui->debug_procInputBox_2->append(ui->input_keysSpinBox_2->text());

    // Splits the rawInputBox input into a Vector
    rawInputVector = ui->input_rawInputBox_2->toPlainText().split("\n");

    // Clears the procInputBox
    ui->debug_procInputBox_2->clear();

    /*
     * rawInputLine.indexOf("(",1) == -1 <TRUE: Editor Hit Object Input>
     * rawInputLine.indexOf(")",1) == -1 <TRUE: Editor Hit Object Input>
     * rawInputLine.count(QRegExp(",")) > 5) <TRUE: Timing Point Input>
     * rawInputLine.count(QRegExp(",")) <= 5) <TRUE: Hit Object Input>
     */

    // Detect Input
    if ((rawInputVector.at(0)).indexOf("(", 1) != -1 &&
        (rawInputVector.at(0)).indexOf(")",1) != -1)
    {
        validateType = inputType::editorHitObjectInput;
        ui->input_statusLabel_2->setText("STATUS: Editor Hit Object Format detected.");
        ui->input_statusLabel_2->setStyleSheet("QLabel { color:green; }");

        // .count = 4: Normal Note
        // .count = 5: Long Note
    } else if (((rawInputVector.at(0)).count(QRegExp(",")) == 4 ||
                (rawInputVector.at(0)).count(QRegExp(",")) == 5) &&
                (rawInputVector.at(0)).indexOf("|",1) == -1)
    {
        validateType = inputType::hitObjectInput;
        ui->input_statusLabel_2->setText("STATUS: Hit Object Format detected.");
        ui->input_statusLabel_2->setStyleSheet("QLabel { color:green; }");

    } else if ((rawInputVector.at(0)).count(QRegExp(",")) == 7 &&
               (rawInputVector.at(0)).indexOf("|",1) == -1)
    {
        validateType = inputType::timingPointInput;
        ui->input_statusLabel_2->setText("STATUS: Timing Point Format detected.");
        ui->input_statusLabel_2->setStyleSheet("QLabel { color:green; }");

    } else
    {
        validateType = inputType::nullInput;
        ui->input_statusLabel_2->setText("STATUS: No Format detected.");
        ui->input_statusLabel_2->setStyleSheet("QLabel { color:red; }");
    }

    // Switch to generate all data
    switch (validateType){

    case inputType::nullInput:
        break;

    case inputType::editorHitObjectInput:
        // Reads each line from the rawInputVector
        foreach (rawInputString, rawInputVector) {

            // Skips any blank lines
            if(rawInputString.isEmpty()){
                continue;
            }

            // Mid trims the current line from '(' and ')'
            // Split then splits them by ',' into different notes
            partVector = rawInputString.mid(rawInputString.indexOf("(",1) + 1,
                                          rawInputString.indexOf(")",1) - rawInputString.indexOf("(",1) - 1
                                          ).split(",", QString::SkipEmptyParts);

            // For each note append according to format
            foreach (partString, partVector){
                ui->debug_procInputBox_2->append(
                            QString("HITOBJECT|")
                            .append(QString(noOfKeys))
                            .append(QString("|"))
                            .append(partString)
                            .append(QString("|"))
                            // -1 represents Normal Note
                            .append(QString("-1")));
            }
        }
        break;
    case inputType::hitObjectInput:
        // Reads each line from the rawInputVector
        foreach (rawInputString, rawInputVector) {

            // Skips any blank lines
            if(rawInputString.isEmpty()){
                continue;
            }

            // Splits them into parameters
            partVector = rawInputString.split(",",QString::SkipEmptyParts);

            double columnKey;

            // Gets the key column through calculation and rounds to 0 D.P.
            columnKey = svTool::convertColumnCodeToColumnKey(partVector.at(0).toDouble(), noOfKeys.toDouble());

            if(rawInputString.count(QRegExp(",")) == 4){
                // Detected as Normal Note
                // For each note append according to format
                ui->debug_procInputBox_2->append(
                            svTool::compileBASICFormatting_hitObject(
                                noOfKeys,partVector.at(2),
                                QString::number(columnKey)));

            } else if (rawInputString.count(QRegExp(",")) == 5){
                // Detected as Long Note
                // For each note append according to format
                ui->debug_procInputBox_2->append(
                            svTool::compileBASICFormatting_hitObject(
                                noOfKeys,partVector.at(2),
                                QString::number(columnKey),
                                partVector.at(5).mid(0,partVector.at(5).indexOf(":",1))));
            }
        }
        break;

    case inputType::timingPointInput:
        // Reads each line from the rawInputVector
        foreach (rawInputString, rawInputVector)
        {

            // Skips any blank lines
            if(rawInputString.isEmpty())
                continue;

            // Splits them into parameters
            partVector = rawInputString.split(",",QString::SkipEmptyParts);

            QString timingPointValue;

            // Check Type and calculate timingPointValue
            if (partVector.at(6) == QString("0"))
            {
                // Detected as an SV Timing Point
                timingPointValue = QString::number(-100.0 / partVector.at(1).toDouble());
            } else if (partVector.at(6) == QString("1"))
            {
                // Detected as a BPM Timing Point
                timingPointValue = QString::number(60000.0 / partVector.at(1).toDouble());
            }

            // Detected as Normal Note
            // For each note append according to format
            ui->debug_procInputBox_2->append(
                        svTool::compileBASICFormatting_timingPoint(
                            partVector.at(0),
                            timingPointValue,
                            partVector.at(6) == QString("0") ? QString("SV") : QString("BPM")));

        }
        break;
    }

    // Copy over to other boxes for Input 2
    ui->copier_procInputBox_2->setPlainText(ui->debug_procInputBox_2->toPlainText());
}

// ------------------------------------- STUTTER -------------------------------------

// Connect Stutter Widgets
void svTool::on_stutter_initSVSlider_valueChanged(int value)
{
    ui->stutter_initSVSpinBox->setValue(((double) value) / 100);
}
void svTool::on_stutter_thresholdSlider_valueChanged(int value)
{
    ui->stutter_thresholdSpinBox->setValue((double) value);
}
void svTool::on_stutter_initSVSpinBox_valueChanged(double arg1)
{
    ui->stutter_initSVSlider->setValue((int) (arg1 * 100));
}
void svTool::on_stutter_thresholdSpinBox_valueChanged(double arg1)
{
    ui->stutter_thresholdSlider->setValue((int) (arg1));

    // averageSV = initSV * threshold + secondSV * (1 - threshold);
    // initSV is an abstract value, we can just set averageSV and threshold which are concrete values then use initSV calculate

    double maxInitSV, minInitSV, secondSV;
    double currentAverageSV, currentThreshold;

    currentAverageSV = ui->stutter_averageSVSpinBox->value();
    currentThreshold = arg1 / 100;

    /* initSV CALCULATION
     * solve for mininitSV by substitution;
     *
     * find initSV in terms of secondSV and threshold
     * averageSV = initSV * threshold + (secondSV - secondSV * threshold)
     * initSV = [ averageSV - secondSV * ( 100 - threshold ) ] / threshold
     *
     * (ave) = (th) * in + (1 - th) * sec
     * (ave) = (th)(in) + (sec) - (th)(sec)
     * [(ave) - (sec) + (th)(sec)] / (th) = (in)
     */

    /* TERNARY CALCULATION
     * Assume secondSV is the minimum and maximum value possible to see the limits of initSV
     * If the calculation of initSV exceeds 0.1 - 10.0, it'll be bound in the limit
     */

    // Where secondSV = 0.1
    secondSV = 0.1;
    maxInitSV = (currentAverageSV - secondSV + currentThreshold * secondSV) / currentThreshold > 10.0
                   ? 10.0
                   : (currentAverageSV - secondSV + currentThreshold * secondSV) / currentThreshold;



    // Where secondSV = 10.0
    secondSV = 10.0;
    minInitSV = (currentAverageSV - secondSV + currentThreshold * secondSV) / currentThreshold < 0.1
                   ? 0.1
                   : (currentAverageSV - secondSV + currentThreshold * secondSV) / currentThreshold;


    // Set Maximum and Minimum
    ui->stutter_initSVSlider->setMaximum((int) (maxInitSV * 100));
    ui->stutter_initSVSpinBox->setMaximum(maxInitSV);

    ui->stutter_initSVSlider->setMinimum((int) (minInitSV * 100));
    ui->stutter_initSVSpinBox->setMinimum(minInitSV);

    /* DEBUG
    ui->stutter_procOutputBox->append(QString("maxinit ").append(QString::number((int) (maxInitSV * 100))));
    ui->stutter_procOutputBox->append(QString::number(ui->stutter_initSVSlider->singleStep()));
    ui->stutter_procOutputBox->append(QString::number(maxInitSV).append(" maxInit"));
    ui->stutter_procOutputBox->append(QString::number(minInitSV).append(" minInit"));
    */

}
void svTool::on_stutter_averageSVSpinBox_valueChanged(double arg1)
{
    // averageSV = initSV * threshold + secondSV * (1 - threshold);
    // initSV is an abstract value, we can just set averageSV and threshold which are concrete values then use initSV calculate

    double maxInitSV, minInitSV;
    double currentAverageSV, currentThreshold;

    currentAverageSV = arg1;
    currentThreshold = ui->stutter_thresholdSpinBox->value() / 100;

    /* initSV CALCULATION
     * solve for mininitSV by substitution;
     *
     * find initSV in terms of secondSV and threshold
     * averageSV = initSV * threshold + (secondSV - secondSV * threshold)
     * initSV = [ averageSV - secondSV * ( 1 - threshold ) ] / threshold
     */

    /* TERNARY CALCULATION
     * Assume secondSV is the minimum and maximum value possible to see the limits of initSV
     * If the calculation of initSV exceeds 0.1 - 10.0, it'll be bound in the limit
     */

    // Where secondSV = 0.1
    maxInitSV = (currentAverageSV - 0.1 * (1 - currentThreshold)) / currentThreshold > 10.0
                   ? 10.0
                   : (currentAverageSV - 0.1 * (1 - currentThreshold)) / currentThreshold;

    // Where secondSV = 10.0
    minInitSV = (currentAverageSV - 0.1 * (1 - currentThreshold)) / currentThreshold > 10.0
                   ? 10.0
                   : (currentAverageSV - 0.1 * (1 - currentThreshold)) / currentThreshold;

    // Set Maximum and Minimum
    ui->stutter_initSVSlider->setMaximum(maxInitSV * 10);
    ui->stutter_initSVSpinBox->setMaximum(maxInitSV);

    ui->stutter_initSVSlider->setMinimum(minInitSV * 10);
    ui->stutter_initSVSpinBox->setMinimum(minInitSV);

}

// Stutter Generate Button
void svTool::on_stutter_generateButton_clicked()
{
    try {
        QStringList partVector, rawInputVector;
        QString rawInputString;
        QList<double> uniqueOffsetList;

        double threshold, initSV, secondSV, averageSV, initOffset, secondOffset, endOffset;

        threshold = ui->stutter_thresholdSpinBox->value() / 100;
        initSV = ui->stutter_initSVSpinBox->value();
        averageSV = ui->stutter_averageSVSpinBox->value();
        secondSV = (averageSV - (initSV * threshold)) / (1 - threshold);

        ui->stutter_procOutputBox->clear();
        ui->stutter_outputBox->clear();

        // Set input vector
        rawInputVector = ui->stutter_procInputBox->toPlainText().split("\n");

        // Set up uniqueOffsetList
        foreach (rawInputString, rawInputVector)
        {
            partVector = rawInputString.split("|");
            if (!uniqueOffsetList.contains(partVector.at(2).toDouble()))
                uniqueOffsetList.append(partVector.at(2).toDouble());
        }

        // Generate all SVs in basic format
        int offsetListCounter = 0;

        while (offsetListCounter < uniqueOffsetList.length() - 1)
        {
            initOffset = uniqueOffsetList.at(offsetListCounter);
            secondOffset = (uniqueOffsetList.at(offsetListCounter + 1) - initOffset) * threshold + initOffset;

            //initSV append
            ui->stutter_procOutputBox->append(QString("TIMINGPOINT|")
                                     .append(QString::number(initOffset))
                                     .append(QString("|"))
                                     .append(QString::number(initSV))
                                     .append(QString("|SV")));
            //secondSV append
            ui->stutter_procOutputBox->append(QString("TIMINGPOINT|")
                                     .append(QString::number(secondOffset))
                                     .append(QString("|"))
                                     .append(QString::number(secondSV))
                                     .append(QString("|SV")));
            offsetListCounter += 1;
        }

        //End SV for normalization
        endOffset = uniqueOffsetList.at(uniqueOffsetList.length() - 1);

        //normalizeSV append
        ui->stutter_procOutputBox->append(QString("TIMINGPOINT|")
                                 .append(QString::number(endOffset))
                                 .append(QString("|"))
                                 .append(QString::number(averageSV))
                                 .append(QString("|SV")));

        svTool::compileProcOutput(ui->stutter_procOutputBox, ui->stutter_outputBox);
    } catch(...){
        //Generate Error Report
    }
}

// ------------------------------------- COPIER -------------------------------------

// Copier Generate Button
void svTool::on_copier_generateButton_clicked()
{
    try {
        QStringList rawInputVector_1, rawInputVector_2;
        QStringList hitObjectVector, timingPointVector, hitObjectPartVector;
        QString hitObjectString;
        QString timingPointPart;
        QList<double> uniqueHitObjectOffsetList;
        double uniqueHitObjectOffset, timingPointOffset, initialTimingPointOffset;

        enum class inputBoxType
        {
            timingPoint, // 0
            hitObject // 1
        };

        inputBoxType boxType1;
        inputBoxType boxType2;

        rawInputVector_1 = ui->copier_procInputBox->toPlainText().split("\n", QString::SkipEmptyParts);
        rawInputVector_2 = ui->copier_procInputBox_2->toPlainText().split("\n", QString::SkipEmptyParts);

        //Checks if the inputs are HITOBJECT and TIMINGPOINT, in any order
        if (QString::compare(rawInputVector_1.at(0).split("|").at(0),
                             "HITOBJECT",
                             Qt::CaseInsensitive) == 0)
        {
            boxType1 = inputBoxType::hitObject;
        } else if (QString::compare(rawInputVector_1.at(0).split("|").at(0),
                                    "TIMINGPOINT",
                                    Qt::CaseInsensitive) == 0)
        {
            boxType1 = inputBoxType::timingPoint;
        } else
        {
            ui->copier_statusLabel->setText("STATUS: Input Box 1 is neither HITOBJECT nor TIMINGPOINT.");
            ui->copier_statusLabel->setStyleSheet("QLabel { color:red; }");
            return;
        }

        if (QString::compare(rawInputVector_2.at(0).split("|").at(0),
                             "HITOBJECT",
                             Qt::CaseInsensitive) == 0)
        {
            boxType2 = inputBoxType::hitObject;
        } else if (QString::compare(rawInputVector_2.at(0).split("|").at(0),
                                    "TIMINGPOINT",
                                    Qt::CaseInsensitive) == 0)
        {
            boxType2 = inputBoxType::timingPoint;
        } else
        {
            ui->copier_statusLabel->setText("STATUS: Input Box 2 is neither HITOBJECT nor TIMINGPOINT.");
            ui->copier_statusLabel->setStyleSheet("QLabel { color:red; }");
            return;
        }

        if ((boxType1 == inputBoxType::hitObject && boxType2 == inputBoxType::hitObject) ||
                (boxType2 == inputBoxType::timingPoint && boxType1 == inputBoxType::timingPoint))
        {
            ui->copier_statusLabel->setText("STATUS: Make sure that both Inputs are different in type.");
            ui->copier_statusLabel->setStyleSheet("QLabel { color:red; }");
            return;
        }

        //Assign the Vectors
        if (boxType1 == inputBoxType::hitObject)
        {
            hitObjectVector = rawInputVector_1;
            timingPointVector = rawInputVector_2;
        } else
        {
            hitObjectVector = rawInputVector_2;
            timingPointVector = rawInputVector_1;
        }

        //Generate Unique Offset List
        foreach (hitObjectString, hitObjectVector)
        {
            hitObjectPartVector = hitObjectString.split("|");
            if (!uniqueHitObjectOffsetList.contains(hitObjectPartVector.at(2).toDouble()))
                uniqueHitObjectOffsetList.append(hitObjectPartVector.at(2).toDouble());
        }

        //Gets the offset from the First Timing Point in order to "zero" all Timing Points
        initialTimingPointOffset = timingPointVector.at(0).split("|").at(1).toDouble();

        //Generates Code
        foreach (uniqueHitObjectOffset, uniqueHitObjectOffsetList)
        {
            foreach (timingPointPart, timingPointVector)
            {
                timingPointOffset = timingPointPart.split("|", QString::SkipEmptyParts).at(1).toDouble();
                timingPointPart.replace(QString::number(timingPointOffset),
                                        QString::number(timingPointOffset - initialTimingPointOffset + uniqueHitObjectOffset));
                ui->copier_procOutputBox->append(timingPointPart);
            }
        }

        //Converts format
        svTool::compileProcOutput(ui->copier_procOutputBox, ui->copier_outputBox);
        
        ui->copier_statusLabel->setText("STATUS: Convert Successful.");
        ui->copier_statusLabel->setStyleSheet("QLabel { color:green; }");

    } catch (...){
        //Generate Error Report
    }
}

// ------------------------------ TWO POINT FUNCTION ---------------------------------

void svTool::on_TPF_initialSVSlider_valueChanged(int value)
{
    ui->TPF_initialSVSpinBox->setValue(((double) value) / 100);
}
void svTool::on_TPF_initialSVSpinBox_valueChanged(double arg1)
{
    ui->TPF_initialSVSlider->setValue((int) (arg1 * 100));
}

void svTool::on_TPF_endSVSlider_valueChanged(int value)
{
    ui->TPF_endSVSpinBox->setValue(((double) value) / 100);
}
void svTool::on_TPF_endSVSpinBox_valueChanged(double arg1)
{
    ui->TPF_endSVSlider->setValue((int) (arg1 * 100));
}

void svTool::on_TPF_offsetSlider_valueChanged(int value)
{
    ui->TPF_offsetSpinBox->setValue(value);
}
void svTool::on_TPF_offsetSpinBox_valueChanged(int arg1)
{
    ui->TPF_offsetSlider->setValue(arg1);
}

void svTool::on_TPF_frequencySlider_valueChanged(int value)
{
    ui->TPF_frequencySpinBox->setValue(value);
}
void svTool::on_TPF_frequencySpinBox_valueChanged(int arg1)
{
    ui->TPF_frequencySlider->setValue(arg1);
}

void svTool::on_TPF_amplitudeSlider_valueChanged(int value)
{
    ui->TPF_amplitudeSpinBox->setValue(value);
}
void svTool::on_TPF_amplitudeSpinBox_valueChanged(int arg1)
{
    ui->TPF_amplitudeSlider->setValue(arg1);
}

// TPF Generate Button
void svTool::on_TPF_generateButton_clicked()
{  
    /* For this function, we are going to have 2 separate graphs, linear and a sine graph (Default Range: PI)
     *
     * SINE GRAPH: This will control the "curve" modification of the graph, dependant on the <layman> Curve Factor (a.k.a. Amplitude).
     *             Its offset is defaulted to 0 as its start and end point (0 - PI) is 0, hence not affecting the start and end points
     *             of the original LINEAR GRAPH.
     *
     * LINEAR GRAPH: This controls the linear direction of the graph.
     *
     * PARAMETERS:
         * INITIAL & END OFFSET
         * INITIAL & END SV
         * AMPLITUDE (of SINE GRAPH)
         * OFFSET (of SINE GRAPH)
     */

    QTextBrowser *statusBox;
    QLabel *statusLabel;

    double initialOffset, endOffset;
    double initialSV, endSV;
    double xValue;
    double offset, amplitude, frequency;
    int intermediatePoints;
    statusLabel = ui->TPF_statusLabel;
    intermediatePoints = 100;
    statusBox = ui->TPF_statusBox;
    statusBox->clear();

    //Set startOffset and endOffset
    if (ui->TPF_editorInputLine->text().isEmpty())
    {
        statusLabel->setText("STATUS: No Input detected");
        statusLabel->setStyleSheet("QLabel { color:red; }");
        return;
    } else if (svTool::convertEditorHitObjectToOffsetList(ui->TPF_editorInputLine->text()).length() == 2)
    {
        initialOffset = svTool::convertEditorHitObjectToOffsetList(ui->TPF_editorInputLine->text()).at(0);
        endOffset = svTool::convertEditorHitObjectToOffsetList(ui->TPF_editorInputLine->text()).at(1);

        statusLabel->setText("STATUS: Detected Editor Hit Object Input");
        statusLabel->setStyleSheet("QLabel { color:green; }");
    } else {
        statusLabel->setText("STATUS: Make sure you input 2 Editor Hit Objects in the Input.");
        statusLabel->setStyleSheet("QLabel { color:red; }");
        return;
    }

    //Set other parameters
    initialSV = ui->TPF_initialSVSpinBox->value();
    endSV = ui->TPF_endSVSpinBox->value();
    offset = (double) ui->TPF_offsetSpinBox->value() / 100;
    amplitude = (double) ui->TPF_amplitudeSpinBox->value() / 100;
    frequency = (double) ui->TPF_frequencySpinBox->value() / 100;

    //Generate vectors for graph
    QVector<double> x(intermediatePoints + 1), y(intermediatePoints + 1);
    QVector<double> yLinear(intermediatePoints + 1);
    QVector<double> ySine(intermediatePoints + 1);

    for(int i=0; i<intermediatePoints + 1; ++i)
    {
        xValue = i / ((double) intermediatePoints);
        x[i] = (xValue * (endOffset - initialOffset)) + initialOffset;
        yLinear[i] = xValue * (endSV - initialSV) + initialSV;
        ySine[i] =  amplitude * qSin(frequency * (xValue + offset) * M_PI);
        y[i] = yLinear[i] + ySine[i];
    }
    statusBox->append(QString("RANGE: ")
                      .append(QString::number(initialOffset))
                      .append(" ~ ")
                      .append(QString::number(endOffset)));

    statusBox->append(QString("LINEAR FUNCTION: ")
                      .append("f(x) = ")
                      .append(QString::number((endSV - initialSV) / intermediatePoints))
                      .append("x + ")
                      .append(QString::number(initialSV)));

    statusBox->append(QString("SINE FUNCTION: ")
                      .append("f(x) = ")
                      .append(QString::number(amplitude)
                      .append(" * sin[(")
                      .append(QString::number(frequency))
                      .append(" * x + ")
                      .append(QString::number(offset))
                      .append(") * π]")));

    ui->TPF_customPlot->addGraph();
    ui->TPF_customPlot->graph(0)->setData(x,y);
    ui->TPF_customPlot->graph(0)->setPen(QPen(Qt::black));
    ui->TPF_customPlot->graph(0)->setBrush(QBrush(QColor(100,100,100,20)));
    ui->TPF_customPlot->xAxis->setLabel("Offset");
    ui->TPF_customPlot->yAxis->setLabel("SV");
    ui->TPF_customPlot->xAxis->setRange(initialOffset, endOffset);
    ui->TPF_customPlot->yAxis->setRange(0.0, 10.0);
    ui->TPF_customPlot->replot();
}

//Reset Values on Tab Change or Radio Change
void svTool::on_TPF_linearRadio_clicked()
{
    svTool::resetTPF();
}
void svTool::on_TPF_quadraticRadio_clicked()
{
    svTool::resetTPF();
}
void svTool::resetTPF()
{
    ui->TPF_initialSVSpinBox->setValue(1.0);
    ui->TPF_endSVSpinBox->setValue(1.0);
    ui->TPF_amplitudeSpinBox->setValue(0);
    ui->TPF_frequencySpinBox->setValue(0);
    ui->TPF_offsetSpinBox->setValue(0);
}


// ------------------------------ FUNCTION EDITOR ---------------------------------











