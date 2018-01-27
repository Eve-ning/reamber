#include "amber.h"
#include "ui_amber.h"

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
amber::amber(QWidget *parent) : QMainWindow(parent), ui(new Ui::amber)
{
    ui->setupUi(this);

    //Pre-RenderGraphs
    ui->adjuster_customPlot->addGraph();
    ui->adjuster_customPlot->xAxis->setLabel("Offset");
    ui->adjuster_customPlot->yAxis->setLabel("SV");

    ui->TPF_customPlot->addGraph();
    ui->TPF_customPlot->xAxis->setLabel("Offset");
    ui->TPF_customPlot->yAxis->setLabel("SV");

}

amber::~amber()
{
    delete ui;
}

namespace B_INDEX {
    int HO_LABEL       = 0;
    int HO_NOOFKEYS    = 1;
    int HO_OFFSET      = 2;
    int HO_COLUMN      = 3;
    int HO_LNENDOFFSET = 4;
    int TP_LABEL       = 0;
    int TP_OFFSET      = 1;
    int TP_VALUE       = 2;
    int TP_TYPE        = 3;
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
       ,def_lnExtension       = ":0:0:0:0:"
       ,def_bpmExtension     = "4,3,0,20,1,0"
       ,def_svExtension      = "4,3,0,20,0,0"
       ,def_timingPointType  = "SV"
;

// --------------------------------------------------------------------------------------------------------< HOME >

void amber::on_home_githubIconLabel_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/amber", QUrl::TolerantMode));
}

// --------------------------------------------------------------------------------------------------------< GENERAL >

//Compilers
QString amber::compileOMFormatting_NN(QString xAxis,
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
QString amber::compileOMFormatting_LN(QString xAxis,
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
QString amber::compileOMFormatting_BPM(QString offset,
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
            .append(",")
            .append(bpmCode)
            .append(",")
            .append(extension);
    return output;
}
QString amber::compileOMFormatting_SV(QString offset,
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
            .append(",")
            .append(svCode)
            .append(",")
            .append(extension);
    return output;
}
QString amber::compileBASICFormatting_hitObject(QString noOfKeys,
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
QString amber::compileBASICFormatting_timingPoint(QString offset,
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
double amber::convertColumnCodeToColumnKey(double columnCode, double noOfKeys)
{
    return round(((columnCode / 512 * noOfKeys * 2 + 1) / 2) - 1);
}
double amber::convertColumnKeyToColumnCode(double columnKey, double noOfKeys)
{
    return round(((columnKey + 1) * 2 - 1) / 2 * 512 / noOfKeys);
}
QList<double> amber::convertEditorHitObjectToOffsetList(QString editorHitObject)
{
    QList<double> offsetList;
    QStringList parameterList;
    QString parameter;

    if (amber::checkEditorHitObject(editorHitObject))
    {
        parameterList = editorHitObject.mid(editorHitObject.indexOf("(",1) + 1,
                                              editorHitObject.indexOf(")",1) - editorHitObject.indexOf("(",1) - 1
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
QList<int> amber::convertEditorHitObjectToColumnList(QString editorHitObject)
{
    QList<int> columnList;
    QStringList parameterList;
    QString parameter;

    if (amber::checkEditorHitObject(editorHitObject))
    {
        parameterList = editorHitObject.mid(editorHitObject.indexOf("(",1) + 1,
                                              editorHitObject.indexOf(")",1) - editorHitObject.indexOf("(",1) - 1
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
QList<double> amber::convertHitObjectToOffsetList(QStringList hitObjectList)
{
    QList<double> offsetList;
    QString hitObject;

    if (amber::checkHitObject(hitObjectList[0]))
    {
        foreach(hitObject, hitObjectList)
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
QList<int> amber::convertHitObjectToColumnList(QStringList hitObjectList, int keyCount)
{
    QList<int> columnList;
    QString hitObject;

    if (amber::checkHitObject(hitObjectList[0]))
    {
        foreach(hitObject, hitObjectList)
        {
            columnList.append(amber::convertColumnCodeToColumnKey(
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
QList<double> amber::convertTimingPointToOffsetList(QStringList timingPointList)
{
    QList<double> offsetList;
    QString timingPoint;

    if (amber::checkTimingPoint(timingPointList[0]))
    {
        foreach(timingPoint, timingPointList)
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
QList<double> amber::convertTimingPointToCodeList(QStringList timingPointList)
{
    QList<double> codeList;
    QString timingPoint;

    if (amber::checkTimingPoint(timingPointList[0]))
    {
        foreach(timingPoint, timingPointList)
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

//Checks
bool amber::checkEditorHitObject(QString editorHitObject)
{
    bool returnFlag;
    returnFlag = editorHitObject.contains("(") &&
                 editorHitObject.contains(")") &&
                 editorHitObject.contains("|") &&
                 editorHitObject.contains("-");
    return returnFlag;
}
bool amber::checkHitObject(QString hitObject)
{
    bool returnFlag;
    returnFlag = (hitObject.count(QRegExp(",")) == 5) &&
                !(hitObject.contains("(") &&
                  hitObject.contains(")") &&
                  hitObject.contains("|") &&
                  hitObject.contains("-"));
    return returnFlag;
}
bool amber::checkTimingPoint(QString timingPoint)
{
    bool returnFlag;
    returnFlag = (timingPoint.count(QRegExp(",")) == 7) &&
                !(timingPoint.contains("(") &&
                  timingPoint.contains(")") &&
                  timingPoint.contains("|") &&
                  timingPoint.contains("-"));
    return returnFlag;
}

bool amber::checkEditorHitObject(QPlainTextEdit *box)
{
    return amber::checkEditorHitObject(box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}
bool amber::checkHitObject(QPlainTextEdit *box)
{
    return amber::checkHitObject(box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}
bool amber::checkTimingPoint(QPlainTextEdit *box)
{
    return amber::checkTimingPoint(box->toPlainText().split("\n", QString::SkipEmptyParts)[0]);
}

bool amber::checkEditorHitObject(QStringList editorHitObjectList)
{
    if (editorHitObjectList.length() != 0)
    {
    return amber::checkEditorHitObject(editorHitObjectList[0]);
    }
    return false;
}
bool amber::checkHitObject(QStringList hitObjectList)
{
    if (hitObjectList.length() != 0)
    {
    return amber::checkHitObject(hitObjectList[0]);
    }
    return false;
}
bool amber::checkTimingPoint(QStringList timingPointList)
{
    if (timingPointList.length() != 0)
    {
    return amber::checkTimingPoint(timingPointList[0]);
    }
    return false;
}

bool amber::checkHitObjectNN(QString hitObjectNN)
{
    if (!hitObjectNN.contains(",")){
        return false;
    }
    return hitObjectNN.count(QRegExp(",")) == 4;
}
bool amber::checkHitObjectLN(QString hitObjectLN)
{
    if (!hitObjectLN.contains(",")){
        return false;
    }
    return hitObjectLN.count(QRegExp(",")) == 5;
}
bool amber::checkTimingPointSV(QString timingPointSV)
{
    if (!timingPointSV.contains(",")){
        return false;
    }
    return timingPointSV.split(",", QString::SkipEmptyParts)[6] == "0";
}
bool amber::checkTimingPointBPM(QString timingPointBPM)
{
    if (!timingPointBPM.contains(",")){
        return false;
    }
    return timingPointBPM.split(",", QString::SkipEmptyParts)[6] == "1";
}

void amber::compileProcOutput(QTextBrowser *inputBoxObject,
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

        if (partVector[B_INDEX::HO_LABEL] == "HITOBJECT")
        {
            //hitObjectOutput
            //Calculation of ColumnCode
            columnCode = amber::convertColumnKeyToColumnCode(partVector[B_INDEX::HO_COLUMN].toDouble(),
                                                             partVector[B_INDEX::HO_NOOFKEYS].toDouble());
            if (partVector[B_INDEX::HO_LNENDOFFSET] == "-1")
            {
                //Normal Note Compile
                outputBoxObject->append(amber::compileOMFormatting_NN(QString::number(columnCode),
                                                                      partVector[B_INDEX::HO_OFFSET]));
            }
            else
            {
                //Long Note Compile
                outputBoxObject->append(amber::compileOMFormatting_LN(QString::number(columnCode),
                                                                      partVector[B_INDEX::HO_OFFSET],
                                                                      partVector[B_INDEX::HO_LNENDOFFSET]));
            }

        }
        else if (partVector[B_INDEX::TP_LABEL] == "TIMINGPOINT")
        {
            //timingPointOutput
            if (partVector[B_INDEX::TP_TYPE] == "BPM")
            {
                //BPM Compile
                timingPointCode = 60000 / partVector[B_INDEX::TP_VALUE].toDouble();
                outputBoxObject->append(amber::compileOMFormatting_BPM(partVector[B_INDEX::TP_OFFSET],
                                                                       QString::number(timingPointCode)));
            }
            else if (partVector[B_INDEX::TP_TYPE] == "BPM")
            {
                //SV Compile
                timingPointCode = -100 / partVector[B_INDEX::TP_VALUE].toDouble();
                outputBoxObject->append(amber::compileOMFormatting_SV(partVector[B_INDEX::TP_OFFSET],
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

QStringList amber::convertOMtoBASIC(QLabel *messageLabel,
                                    bool acceptEditorHitObject,
                                    bool acceptHitObject,
                                    bool acceptTimingPoint,
                                    QStringList input,
                                    int noOfKeys)
{

    bool isEditorHitObject, isHitObject, isTimingPoint;

    QStringList output,
                partList;
    QString partString, inputString;

    isEditorHitObject = amber::checkEditorHitObject(input);
    isHitObject = amber::checkHitObject(input);
    isTimingPoint = amber::checkTimingPoint(input);

    if (!isEditorHitObject &&
        !isHitObject &&
        !isTimingPoint)
    {
        messageLabel->setText("STATUS: No Valid Input Detected");
        messageLabel->setStyleSheet("QLabel { color:red; }");
        return output;
    }

    // The logic is the program will return if it DOESN'T ACCEPT the input but it RECIEVES the input
    if ((isEditorHitObject && !acceptEditorHitObject) ||
       (isHitObject && !acceptHitObject) ||
       (isTimingPoint && !acceptTimingPoint))
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
                output.append(amber::compileBASICFormatting_hitObject(QString::number(noOfKeys),
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
            columnKey = amber::convertColumnCodeToColumnKey(partList[0].toDouble(), noOfKeys);

            if (amber::checkHitObjectNN(inputString))
            {
                output.append(amber::compileBASICFormatting_hitObject(
                              QString::number(noOfKeys),
                              partList[2],
                              QString::number(columnKey)));

            }
            else if (amber::checkHitObjectLN(inputString))
            {
                output.append(amber::compileBASICFormatting_hitObject(
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

            if (checkTimingPointSV(inputString))
            {
                timingPointValue = QString::number(-100.0 / partList[1].toDouble());
            }
            else if (checkTimingPointBPM(inputString))
            {
                timingPointValue = QString::number(60000.0 / partList[1].toDouble());
            }

            output.append(amber::compileBASICFormatting_timingPoint(
                          partList[0],
                          timingPointValue,
                          checkTimingPointSV(inputString) ? QString("SV") : QString("BPM")));

        }

        messageLabel->setText("STATUS: Converted Timing Point");
        messageLabel->setStyleSheet("QLabel { color:green; }");

    }
    return output;
}

QStringList amber::convertBASICtoOM(QLabel *messageLabel,
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
            columnCode = amber::convertColumnKeyToColumnCode(partList[3].toDouble(), partList[1].toDouble());

            if (partList[4] == "-1")
            {
                output.append(amber::compileOMFormatting_NN(QString::number(columnCode),
                                                             partList[2]));
            }
            else
            {
                output.append(amber::compileOMFormatting_LN(QString::number(columnCode),
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
                output.append(amber::compileOMFormatting_BPM(partList[1],
                                                              QString::number(60000.0 / partList[2].toDouble())));
            }
            else if (partList[3] == "SV")
            {
                output.append(amber::compileOMFormatting_SV(partList[1],
                                                              QString::number(-100 / partList[2].toDouble())));
            }
        }

        messageLabel->setText("STATUS: Timing Point");
        messageLabel->setStyleSheet("QLabel { color:green; }");

    }
    return output;
}
// --------------------------------------------------------------------------------------------------------< SETTINGS >

void amber::saveDefaultValues()
{
   def_xAxis            = ui->def_xAxisLine           ->text();
   def_yAxis            = ui->def_yAxisLine           ->text();
   def_offset           = ui->def_offsetLine          ->text();
   def_lnParameter      = ui->def_lnParameterLine     ->text();
   def_lnOffset         = ui->def_lnOffsetLine        ->text();
   def_bpmCode          = ui->def_bpmCodeLine         ->text();
   def_svCode           = ui->def_svCodeLine          ->text();
   def_bpmValue         = ui->def_bpmValueLine        ->text();
   def_svValue          = ui->def_svValueLine         ->text();
   def_column           = ui->def_columnLine          ->text();
   def_noOfKeys         = ui->def_noOfKeysLine        ->text();
   def_timingPointLabel = ui->def_timingPointLabelLine->text();
   def_hitObjectLabel   = ui->def_hitObjectLabelLine  ->text();
   def_nnExtension      = ui->def_nnExtensionLine     ->text();
   def_lnExtension      = ui->def_lnExtensionLine     ->text();
   def_bpmExtension     = ui->def_bpmExtensionLine    ->text();
   def_svExtension      = ui->def_svExtensionLine     ->text();
   def_timingPointType  = ui->def_timingPointTypeLine ->text();
}

// --------------------------------------------------------------------------------------------------------< QUICK ACCESS >

void amber::on_basicWidgetList_itemClicked(QListWidgetItem *item)
{
    QString itemString;
    itemString = item->text();

    /* BASIC WIDGET LIST
     * Stutter
     * Copier
     * 2PF
     * Normalizer
     */

    ui->stackedWidget->setCurrentIndex(1);

    if      (itemString == "Stutter")
    {
        ui->basicTabWidget->setCurrentIndex(0);
    }
    else if (itemString == "Copier")
    {
        ui->basicTabWidget->setCurrentIndex(1);
    }
    else if (itemString == "2-Point Function")
    {
        ui->basicTabWidget->setCurrentIndex(2);
    }
    else if (itemString == "Normalizer")
    {
        ui->basicTabWidget->setCurrentIndex(3);
    }
    else if (itemString == "Adjuster")
    {
        ui->basicTabWidget->setCurrentIndex(4);
    }

}
void amber::on_advancedWidgetList_itemClicked(QListWidgetItem *item)
{
    QString itemString;
    itemString = item->text();

    ui->stackedWidget->setCurrentIndex(2);

    if      (itemString == "Test 1")
    {
        ui->advancedTabWidget->setCurrentIndex(0);
    }
    else if (itemString == "Test 2")
    {
        ui->advancedTabWidget->setCurrentIndex(1);
    }
}
void amber::on_settingsWidgetList_itemClicked(QListWidgetItem *item)
{
    QString itemString;
    itemString = item->text();

    ui->stackedWidget->setCurrentIndex(3);

    if      (itemString == "Default Values")
    {
        ui->settingsTabWidget->setCurrentIndex(0);
    }
}

void amber::on_toolBox_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index + 1);
}

// --------------------------------------------------------------------------------------------------------< INPUT >

/* REMOVED 13/1/2018 */

// --------------------------------------------------------------------------------------------------------< STUTTER >

// Connect Stutter Widgets
void amber::on_stutter_initSVSlider_valueChanged(int value)
{
    ui->stutter_initSVSpinBox->setValue(((double) value) / 100);
}
void amber::on_stutter_thresholdSlider_valueChanged(int value)
{
    ui->stutter_thresholdSpinBox->setValue((double) value);
}
void amber::on_stutter_initSVSpinBox_valueChanged(double arg1)
{
    ui->stutter_initSVSlider->setValue((int) (arg1 * 100));
}
void amber::on_stutter_thresholdSpinBox_valueChanged(double arg1)
{
    ui->stutter_thresholdSlider->setValue((int) (arg1));

    // averageSV = initSV * threshold + secondSV * (1 - threshold);
    // initSV is an abstract value, we can just set averageSV and threshold which are concrete values then use initSV calculate

    double maxInitSV, minInitSV, secondSV,
           currentAverageSV, currentThreshold;

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
    ui->stutter_initSVSlider-> setMaximum((int) (maxInitSV * 100));
    ui->stutter_initSVSpinBox->setMaximum(maxInitSV);

    ui->stutter_initSVSlider-> setMinimum((int) (minInitSV * 100));
    ui->stutter_initSVSpinBox->setMinimum(minInitSV);

}
void amber::on_stutter_averageSVSpinBox_valueChanged(double arg1)
{
    // averageSV = initSV * threshold + secondSV * (1 - threshold);
    // initSV is an abstract value, we can just set averageSV and threshold which are concrete values then use initSV calculate

    double maxInitSV, minInitSV,
           currentAverageSV, currentThreshold;

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
    ui->stutter_initSVSlider-> setMaximum(maxInitSV * 10);
    ui->stutter_initSVSpinBox->setMaximum(maxInitSV);

    ui->stutter_initSVSlider-> setMinimum(minInitSV * 10);
    ui->stutter_initSVSpinBox->setMinimum(minInitSV);

}

// Stutter Generate Button
void amber::on_stutter_generateButton_clicked()
{
    try {
        QStringList partList, inputList;
        QString inputString;
        QList<double> uniqueOffsetList;

        double threshold,
               initSV, secondSV, averageSV,
               initOffset, secondOffset, endOffset;

        QPlainTextEdit *inputBox;
        inputBox  = ui->stutter_inputBox;
        threshold = ui->stutter_thresholdSpinBox->value() / 100;
        initSV    = ui->stutter_initSVSpinBox->value();
        averageSV = ui->stutter_averageSVSpinBox->value();
        secondSV  = (averageSV - (initSV * threshold)) / (1 - threshold);

        ui->stutter_outputBox->clear();

        // Set input vector
        inputList = amber::convertOMtoBASIC(ui->stutter_inputStatusLabel, true, true, false, inputBox->toPlainText().split("\n", QString::SkipEmptyParts));

        if (inputList.length() == 0){
            return;
        }
        // Set up uniqueOffsetList
        foreach (inputString, inputList)
        {
            partList = inputString.split("|");
            if (!uniqueOffsetList.contains(partList[B_INDEX::HO_OFFSET].toDouble()))
                uniqueOffsetList.append(partList[B_INDEX::HO_OFFSET].toDouble());
        }

        // Generate all SVs in basic format
        for (int i = 0; i < (uniqueOffsetList.length() - 1); ++ i)
        {
            initOffset = uniqueOffsetList.at(i);
            secondOffset = (uniqueOffsetList.at(i + 1) - initOffset) * threshold + initOffset;

            //initSV append
            ui->stutter_outputBox->append(amber::compileOMFormatting_SV(QString::number(initOffset),
                                                                        QString::number(-100.0 / initSV)));

            //secondSV append
            ui->stutter_outputBox->append(amber::compileOMFormatting_SV(QString::number(secondOffset),
                                                                        QString::number(-100.0 / secondSV)));
        }

        //End SV for normalization
        endOffset = uniqueOffsetList.at(uniqueOffsetList.length() - 1);

        //normalizeSV append
        ui->stutter_outputBox->append(amber::compileOMFormatting_SV(QString::number(endOffset),
                                                                    QString::number(-100.0 / averageSV)));
    } catch(...){
        //Generate Error Report
    }
}

// --------------------------------------------------------------------------------------------------------< COPIER >

// Copier Generate Button
void amber::on_copier_generateButton_clicked()
{
    try {
        QStringList inputList_1, inputList_2,
                    hitObjectList, timingPointList, hitObjectPartList;
        QString hitObjectString,
                timingPointPart;
        QList<double> uniqueHitObjectOffsetList;
        double uniqueHitObjectOffset, timingPointOffset, initialTimingPointOffset;

        QLabel *inputStatusLabel_1,
               *inputStatusLabel_2,
               *outputStatusLabel;

        inputStatusLabel_1 = ui->copier_inputStatusLabel;
        inputStatusLabel_2 = ui->copier_inputStatusLabel_2;
        outputStatusLabel  = ui->copier_outputStatusLabel;

        enum class inputBoxType
        {
            timingPoint, // 0
            hitObject // 1
        };

        inputBoxType boxType1,
                     boxType2;

        inputList_1 = amber::convertOMtoBASIC(inputStatusLabel_1,
                                              true, true, true,
                                              ui->copier_inputBox->toPlainText().split("\n", QString::SkipEmptyParts));
        inputList_2 = amber::convertOMtoBASIC(inputStatusLabel_2,
                                              true, true, true,
                                              ui->copier_inputBox_2->toPlainText().split("\n", QString::SkipEmptyParts));

        if (inputList_1.length() == 0 || inputList_2.length() == 0){
            return;
        }

        ui->copier_outputBox->clear();

        //Checks for Type
        if (inputList_1[0].split("|")[B_INDEX::HO_LABEL] == "HITOBJECT")
        {
            boxType1 = inputBoxType::hitObject;
        }
        else if (inputList_1[0].split("|")[B_INDEX::TP_LABEL] == "TIMINGPOINT")
        {
            boxType1 = inputBoxType::timingPoint;
        }
        else
        {
            inputStatusLabel_1->setText("STATUS: Input Box 1 is neither HITOBJECT nor TIMINGPOINT.");
            inputStatusLabel_1->setStyleSheet("QLabel { color:red; }");
            outputStatusLabel ->setText("STATUS: Error has occured.");
            outputStatusLabel ->setStyleSheet("QLabel { color:red; }");
            return;
        }

        if (inputList_2[0].split("|")[B_INDEX::HO_LABEL] == "HITOBJECT")
        {
            boxType2 = inputBoxType::hitObject;
        }
        else if (inputList_2[0].split("|")[B_INDEX::TP_LABEL] == "TIMINGPOINT")
        {
            boxType2 = inputBoxType::timingPoint;
        }
        else
        {
            inputStatusLabel_2->setText("STATUS: Input Box 2 is neither HITOBJECT nor TIMINGPOINT.");
            inputStatusLabel_2->setStyleSheet("QLabel { color:red; }");
            outputStatusLabel ->setText("STATUS: Error has occured.");
            outputStatusLabel ->setStyleSheet("QLabel { color:red; }");
            return;
        }

        if ((boxType1 == inputBoxType::hitObject && boxType2 == inputBoxType::hitObject) ||
                (boxType2 == inputBoxType::timingPoint && boxType1 == inputBoxType::timingPoint))
        {
            outputStatusLabel->setText("STATUS: Make sure that both Inputs are different in type.");
            outputStatusLabel->setStyleSheet("QLabel { color:red; }");
            return;
        }

        //Assign the Vectors
        if (boxType1 == inputBoxType::hitObject)
        {
            hitObjectList = inputList_1;
            timingPointList = inputList_2;
        }
        else
        {
            hitObjectList = inputList_2;
            timingPointList = inputList_1;
        }

        //Generate Unique Offset List
        foreach (hitObjectString, hitObjectList)
        {
            hitObjectPartList = hitObjectString.split("|");
            if (!uniqueHitObjectOffsetList.contains(hitObjectPartList[B_INDEX::HO_OFFSET].toDouble()))
                uniqueHitObjectOffsetList.append(hitObjectPartList[B_INDEX::HO_OFFSET].toDouble());
        }

        //Gets the offset from the First Timing Point in order to "zero" all Timing Points
        initialTimingPointOffset = timingPointList[0].split("|")[B_INDEX::TP_OFFSET].toDouble();

        //Generates Code
        foreach (uniqueHitObjectOffset, uniqueHitObjectOffsetList)
        {
            foreach (timingPointPart, timingPointList)
            {
                timingPointOffset = timingPointPart.split("|", QString::SkipEmptyParts)[1].toDouble();

                if (timingPointPart.split("|", QString::SkipEmptyParts)[B_INDEX::TP_TYPE] == "BPM")
                {
                    ui->copier_outputBox->append(
                    amber::compileOMFormatting_BPM(QString::number(timingPointOffset - initialTimingPointOffset + uniqueHitObjectOffset),
                                                   QString::number(60000 / timingPointPart.split("|",QString::SkipEmptyParts)
                                                                   [B_INDEX::TP_VALUE].toDouble())));
                }
                else
                {
                    ui->copier_outputBox->append(
                    amber::compileOMFormatting_SV(QString::number(timingPointOffset - initialTimingPointOffset + uniqueHitObjectOffset),
                                                  QString::number(-100 / timingPointPart.split("|", QString::SkipEmptyParts)
                                                                  [B_INDEX::TP_VALUE].toDouble())));
                }
            }
        }
        
        outputStatusLabel->setText("STATUS: Convert Successful.");
        outputStatusLabel->setStyleSheet("QLabel { color:green; }");

    } catch (...){
        //Generate Error Report
    }
}

// --------------------------------------------------------------------------------------------------------< TWO POINT FUNCTION >

void amber::on_TPF_initialTPSlider_valueChanged(int value)
{
    ui->TPF_initialTPSpinBox->setValue(((double) value) / 100);
}
void amber::on_TPF_initialTPSpinBox_valueChanged(double arg1)
{
    ui->TPF_initialTPSlider->setValue((int) (arg1 * 100));
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}

void amber::on_TPF_endTPSlider_valueChanged(int value)
{
    ui->TPF_endTPSpinBox->setValue(((double) value) / 100);
}
void amber::on_TPF_endTPSpinBox_valueChanged(double arg1)
{
    ui->TPF_endTPSlider->setValue((int) (arg1 * 100));
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}

void amber::on_TPF_offsetSlider_valueChanged(int value)
{
    ui->TPF_offsetSpinBox->setValue(value);
}
void amber::on_TPF_offsetSpinBox_valueChanged(int arg1)
{
    ui->TPF_offsetSlider->setValue(arg1);
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}

void amber::on_TPF_frequencySlider_valueChanged(int value)
{
    ui->TPF_frequencySpinBox->setValue(value);
}
void amber::on_TPF_frequencySpinBox_valueChanged(int arg1)
{
    ui->TPF_frequencySlider->setValue(arg1);
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}

void amber::on_TPF_amplitudeSlider_valueChanged(int value)
{
    ui->TPF_amplitudeSpinBox->setValue(value);
}
void amber::on_TPF_amplitudeSpinBox_valueChanged(int arg1)
{
    ui->TPF_amplitudeSlider->setValue(arg1);
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}

void amber::on_TPF_initialTPSlider_sliderReleased()
{
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_endTPSlider_sliderReleased()
{
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_amplitudeSlider_sliderReleased()
{
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    };
}
void amber::on_TPF_offsetSlider_sliderReleased()
{
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_frequencySlider_sliderReleased()
{
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_intermediateSpinBox_valueChanged(int arg1)
{
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}

void amber::on_TPF_SVRadio_clicked()
{
    amber::on_TPF_defaultButton_clicked();
}
void amber::on_TPF_BPMRadio_clicked()
{
    amber::on_TPF_defaultButton_clicked();
}

//Reset Values to Default
void amber::on_TPF_defaultButton_clicked()
{
    if (ui->TPF_SVRadio->isChecked())
    {
        ui->TPF_initialTPSlider    ->setMaximum(1000);
        ui->TPF_initialTPSlider    ->setMinimum(10);
        ui->TPF_initialTPSpinBox   ->setMaximum(10.0);
        ui->TPF_initialTPSpinBox   ->setMinimum(0.1);
        ui->TPF_endTPSlider        ->setMaximum(1000);
        ui->TPF_endTPSlider        ->setMinimum(10);
        ui->TPF_endTPSpinBox       ->setMaximum(10.0);
        ui->TPF_endTPSpinBox       ->setMinimum(0.1);

        ui->TPF_initialTPGroup     ->setTitle("Initial SV:");
        ui->TPF_endTPGroup         ->setTitle("End SV:");

        ui->TPF_initialTPSpinBox   ->setValue(1.0);
        ui->TPF_endTPSpinBox       ->setValue(1.0);
        ui->TPF_amplitudeSpinBox   ->setValue(0);
        ui->TPF_frequencySpinBox   ->setValue(100);
        ui->TPF_offsetSpinBox      ->setValue(0);
        ui->TPF_intermediateSpinBox->setValue(100);
    }
    else if (ui->TPF_BPMRadio->isChecked())
    {
        ui->TPF_initialTPSlider    ->setMaximum(500000);
        ui->TPF_initialTPSlider    ->setMinimum(100);
        ui->TPF_initialTPSpinBox   ->setMaximum(5000);
        ui->TPF_initialTPSpinBox   ->setMinimum(1);
        ui->TPF_endTPSlider        ->setMaximum(500000);
        ui->TPF_endTPSlider        ->setMinimum(100);
        ui->TPF_endTPSpinBox       ->setMaximum(500);
        ui->TPF_endTPSpinBox       ->setMinimum(1);

        ui->TPF_initialTPGroup     ->setTitle("Initial BPM:");
        ui->TPF_endTPGroup         ->setTitle("End BPM:");

        ui->TPF_initialTPSpinBox   ->setValue(120);
        ui->TPF_endTPSpinBox       ->setValue(120);
        ui->TPF_amplitudeSpinBox   ->setValue(0);
        ui->TPF_frequencySpinBox   ->setValue(100);
        ui->TPF_offsetSpinBox      ->setValue(0);
        ui->TPF_intermediateSpinBox->setValue(100);
    }
    else
    {
        return;
    }
}

// TPF Generate Button
void amber::on_TPF_generateButton_clicked()
{  
    /* DESCRIPTION
     * For this function, we are going to have 2 separate graphs, linear and a sine graph (Default Range: PI)
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

    QTextBrowser *statusBox,
                 *outputBox;
    QLabel       *statusLabel;
    QRadioButton *SVRadioButton,
                 *BPMRadioButton;
    QCustomPlot  *customPlot;

    double initialOffset, endOffset,
           initialTP, endTP, averageTP,
           xValue,
           offset, amplitude, frequency;
    int    intermediatePoints;

    SVRadioButton  = ui->TPF_SVRadio;
    BPMRadioButton = ui->TPF_BPMRadio;
    statusLabel    = ui->TPF_statusLabel;
    statusBox      = ui->TPF_statusBox;
    outputBox      = ui->TPF_outputBox;
    customPlot     = ui->TPF_customPlot;

    bool isSV  = SVRadioButton ->isChecked();
    bool isBPM = BPMRadioButton->isChecked();

    statusBox->clear(); 
    outputBox->clear();

    //Set startOffset and endOffset
    if (ui->TPF_editorInputLine->text().isEmpty())
    {
        statusLabel->setText("STATUS: No Input detected");
        statusLabel->setStyleSheet("QLabel { color:red; }");
        return;
    }
    else if (amber::convertEditorHitObjectToOffsetList(ui->TPF_editorInputLine->text()).length() == 2)
    {
        initialOffset = amber::convertEditorHitObjectToOffsetList(ui->TPF_editorInputLine->text())[0];
        endOffset = amber::convertEditorHitObjectToOffsetList(ui->TPF_editorInputLine->text())[1];

        statusLabel->setText("STATUS: Detected Editor Hit Object Input");
        statusLabel->setStyleSheet("QLabel { color:green; }");
    }
    else
    {
        statusLabel->setText("STATUS: Make sure you input 2 Editor Hit Objects in the Input.");
        statusLabel->setStyleSheet("QLabel { color:red; }");
        return;
    }

    //Set other parameters
    initialTP          =          ui->TPF_initialTPSpinBox->value();
    endTP              =          ui->TPF_endTPSpinBox->value();
    offset             = (double) ui->TPF_offsetSpinBox->value() / 100;
    amplitude          = (double) ui->TPF_amplitudeSpinBox->value() / 100;
    frequency          = (double) ui->TPF_frequencySpinBox->value() / 100;
    intermediatePoints =          ui->TPF_intermediateSpinBox->value();

    //Generate vectors for graph
    QVector<double> xData(intermediatePoints + 1), yData(intermediatePoints + 1);
    QVector<double> yLinear(intermediatePoints + 1);
    QVector<double> ySine(intermediatePoints + 1);

    for(int i = 0; i < intermediatePoints + 1; ++ i)
    {
        xValue     = i / ((double) intermediatePoints);
        xData[i]   = (xValue * (endOffset - initialOffset)) + initialOffset;
        yLinear[i] = xValue * (endTP - initialTP) + initialTP;
        ySine[i]   = amplitude * qSin(frequency * (xValue + offset) * M_PI) * ((endTP + initialTP) / 2);
        yData[i]   = yLinear[i] + ySine[i];

        //LIMIT VALUES
        if (isSV)
        {
            yData[i] = yData[i] <= 0.1 ? 0.1 : yData[i];
            yData[i] = yData[i] >= 10.0 ? 10.0 : yData[i];
        }
        else
        {
            yData[i] = yData[i] = 0 ? 0.00001 : yData[i];
        }

        if (isSV)
        {
            outputBox->append(amber::compileOMFormatting_SV(QString::number(xData[i]),
                                                            QString::number(yData[i] < 0.1 ? -1000 : -100 / yData[i])));
        }
        else if (isBPM)
        {
            outputBox->append(amber::compileOMFormatting_BPM(QString::number(xData[i]),
                                                             QString::number(yData[i] == 0 ? 9999999 : 60000 / yData[i])));
        }
        else
        {
            return;
        }
    }

    for (int i = 0; i < intermediatePoints; i++)
    {
        averageTP += (yData[i] * (xData[i + 1] - xData[i])) / (endOffset - initialOffset);
    }
    statusBox->append(QString("RANGE: ")
                      .append(QString::number(initialOffset))
                      .append(" ~ ")
                      .append(QString::number(endOffset)));

    statusBox->append(QString("LINEAR FUNCTION: ")
                      .append("f(x) = ")
                      .append(QString::number((endTP - initialTP) / intermediatePoints))
                      .append("x + ")
                      .append(QString::number(initialTP)));

    statusBox->append(QString("SINE FUNCTION: ")
                      .append("f(x) = ")
                      .append(QString::number(amplitude)
                      .append(" * sin[(")
                      .append(QString::number(frequency))
                      .append(" * x + ")
                      .append(QString::number(offset))
                      .append(") * π]")));

    customPlot->graph(0)->setData(xData,yData);
    customPlot->graph(0)->setPen(QPen(Qt::black));
    customPlot->graph(0)->setBrush(QBrush(QColor(100,100,100,20)));
    customPlot->xAxis->setRange(initialOffset, endOffset);

    double minTP = *std::min_element(yData.constBegin(),yData.constEnd());
    double maxTP = *std::max_element(yData.constBegin(),yData.constEnd());

    customPlot->clearItems();
    QCPItemText *averageLabel = new QCPItemText(customPlot);
    averageLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    averageLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    averageLabel->position->setCoords(0.5, 0);
    averageLabel->setText(QString("Average ")
                          .append(isSV ? "SV: " : "BPM: ")
                          .append(QString::number(averageTP)));
    averageLabel->setFont(QFont(font().family(), 12));

    if (isSV)
    {      
        customPlot->yAxis->setLabel("SV");
        customPlot->yAxis->setRange(0.0, 10.0);
    }
    else if (isBPM)
    {
        customPlot->yAxis->setLabel("BPM");
        customPlot->yAxis->setRange(minTP, maxTP);
    }
    else
    {
        return;
    }

    customPlot->replot(QCustomPlot::rpQueuedReplot);

}

// --------------------------------------------------------------------------------------------------------< NORMALIZER >

void amber::on_normalizer_generateButton_clicked()
{
    QStringList   inputList, partList;
    QString       inputString, partOffset, partBPM;
    QList<double> BPMList, offsetList;

    QLabel         *statusLabel;
    QPlainTextEdit *inputBox;
    QTextBrowser   *outputBox;
    QListWidget    *listWidget;
    QCheckBox      *overrideCheck;
    QDoubleSpinBox *overrideDoubleSpinBox;
    QLineEdit      *selectedBPMLine;

    double normalizeBPM;
    double normalizeSV;

    statusLabel =           ui->normalizer_inputStatusLabel;
    inputBox =              ui->normalizer_inputBox;
    outputBox =             ui->normalizer_outputBox;
    listWidget =            ui->normalizer_BPMListWidget;
    selectedBPMLine =       ui->normalizer_selectedBPMLine;
    overrideCheck =         ui->normalizer_overrideCheck;
    overrideDoubleSpinBox = ui->normalizer_overrideDoubleSpinBox;

    outputBox-> clear();
    listWidget->clear();

    inputList = amber::convertOMtoBASIC(statusLabel, false, false, true,
                                        inputBox->toPlainText().split("\n", QString::SkipEmptyParts));

    if (inputList.length() == 0){
        return;
    }

    foreach (inputString, inputList){

        partList = inputString.split("|", QString::SkipEmptyParts);

        if (partList[B_INDEX::TP_TYPE] == "SV"){
            continue;
        }

        partOffset = partList[B_INDEX::TP_OFFSET];
        partBPM = partList[B_INDEX::TP_VALUE];

        BPMList.append(partBPM.toDouble());
        offsetList.append(partOffset.toDouble());
        listWidget->addItem(QString("BPM: ")
                    .append(partBPM)
                    .append(" | Offset: ")
                    .append(partOffset));
    }

    if (BPMList.length() == 0){
        statusLabel->setText("STATUS: Input at least 1 BPM Timing Point");
        statusLabel->setStyleSheet("QLabel { color:red; }");
        return;
    }

    if (overrideCheck->isChecked())
    {
        normalizeBPM = overrideDoubleSpinBox->value();
    }
    else if (selectedBPMLine->text() != "Awaiting Selection...")
    {
        normalizeBPM = selectedBPMLine->text().toDouble();
    }
    else
    {
        statusLabel->setText("STATUS: Select 1 BPM Timing Point or use the Manual Override");
        statusLabel->setStyleSheet("QLabel { color:blue; }");
        return;
    }

    statusLabel->setText(QString("STATUS: Normalizing to ")
                         .append(QString::number(normalizeBPM))
                         .append(" BPM"));
    statusLabel->setStyleSheet("QLabel { color:green; }");


    for(int cycle = 0; cycle < BPMList.length(); cycle ++)
    {
        normalizeSV = -100 / (normalizeBPM / BPMList.at(cycle));
        outputBox->append(amber::compileOMFormatting_SV(QString::number(offsetList.at(cycle)),
                                                        QString::number(normalizeSV)));
    }

    return;
}

void amber::on_normalizer_BPMListWidget_itemPressed(QListWidgetItem *item)
{
    ui->normalizer_selectedBPMLine->setText(item->text()
                                            .mid(5, item->text().indexOf("|") - 5));
}

// --------------------------------------------------------------------------------------------------------< DEFAULT >

void amber::on_default_savePreferencesButton_clicked()
{
    amber::saveDefaultValues();
}

// --------------------------------------------------------------------------------------------------------< ADJUSTER >

void amber::on_adjuster_multiplySpinBox_editingFinished()
{
    if (ui->adjuster_liveUpdateCheck->isChecked())
    {
        amber::on_adjuster_generateButton_clicked();
    }
    if (ui->adjuster_multiplySpinBox->value() != 1)
    {
        ui->adjuster_autoZeroCheck->setEnabled(false);
        ui->adjuster_autoZeroCheck->setChecked(false);

        ui->adjuster_zeroSpinBox->setEnabled(true);
    }
    else
    {
        ui->adjuster_autoZeroCheck->setEnabled(true);
    }
}
void amber::on_adjuster_zeroSpinBox_editingFinished()
{
    if (ui->adjuster_liveUpdateCheck->isChecked())
    {
        amber::on_adjuster_generateButton_clicked();
    }
}
void amber::on_adjuster_offsetSpinBox_editingFinished()
{
    if (ui->adjuster_liveUpdateCheck->isChecked())
    {
        amber::on_adjuster_generateButton_clicked();
    }
}
void amber::on_adjuster_addSpinBox_editingFinished()
{
    if (ui->adjuster_liveUpdateCheck->isChecked())
    {
        amber::on_adjuster_generateButton_clicked();
    }
}
void amber::on_adjuster_autoZeroCheck_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        ui->adjuster_zeroSpinBox->setEnabled(false);
    }
    else if (arg1 == Qt::Unchecked)
    {
        ui->adjuster_zeroSpinBox->setEnabled(true);
    }
}

void amber::on_adjuster_generateButton_clicked()
{
    QPlainTextEdit *inputBox;
    QTextBrowser   *outputBox;
    QDoubleSpinBox *multiplySpinBox,
                   *zeroSpinBox,
                   *addSpinBox;
    QSpinBox       *offsetSpinBox;
    QCheckBox      *autoZeroCheck,
                   *invertCheck;
    QCustomPlot    *customPlot;
    QLabel         *inputStatusLabel,
                   *outputStatusLabel;
    QRadioButton   *SVRadio,
                   *BPMRadio,
                   *graphScatterRadio,
                   *graphLineRadio;

    inputBox          = ui->adjuster_inputBox;
    outputBox         = ui->adjuster_outputBox;
    multiplySpinBox   = ui->adjuster_multiplySpinBox;
    zeroSpinBox       = ui->adjuster_zeroSpinBox;
    addSpinBox        = ui->adjuster_addSpinBox;
    offsetSpinBox     = ui->adjuster_offsetSpinBox;
    autoZeroCheck     = ui->adjuster_autoZeroCheck;
    invertCheck       = ui->adjuster_invertCheck;
    customPlot        = ui->adjuster_customPlot;
    inputStatusLabel  = ui->adjuster_inputStatusLabel;
    outputStatusLabel = ui->adjuster_outputStatusLabel;
    SVRadio           = ui->adjuster_adjustSVRadio;
    BPMRadio          = ui->adjuster_adjustBPMRadio;
    graphScatterRadio = ui->adjuster_graphScatterRadio;
    graphLineRadio    = ui->adjuster_graphLineRadio;

    QStringList inputList, partList;
    QString inputString;

    double initialOffset,
           endOffset,
           minTP,
           maxTP,
           averageTP;

    bool isSV           = SVRadio->isChecked(),
         isBPM          = BPMRadio->isChecked(),
         isGraphScatter = graphScatterRadio->isChecked(),
         isGraphLine    = graphLineRadio->isChecked();

    inputList = amber::convertOMtoBASIC(inputStatusLabel,
                                        false, false, true,
                                        inputBox->toPlainText().split("\n", QString::SkipEmptyParts));
    QVector<double> xData,
                    yData;

    foreach (inputString, inputList)
    {
        partList = inputString.split("|", QString::SkipEmptyParts);

        if ((partList[B_INDEX::TP_TYPE] == "SV" && isSV) ||
            (partList[B_INDEX::TP_TYPE] == "BPM" && isBPM))
        {
            xData.append(partList[B_INDEX::TP_OFFSET].toDouble());
            yData.append(partList[B_INDEX::TP_VALUE].toDouble());
        }
        else
        {
            continue;
        }
    }

    //Adjust Functions
    //ADJUST Y
    for (QVector<double>::iterator i = yData.begin(); i != yData.end(); i++)
    {
        *i -= zeroSpinBox->value(); //Zero +

        if (invertCheck->isChecked()) {*i = - *i;}

        *i *= multiplySpinBox->value();
        *i += addSpinBox->value();

        *i += zeroSpinBox->value(); //Zero -
    }

    //ADJUST X
    for (QVector<double>::iterator i = xData.begin(); i != xData.end(); i++)
    {
        *i += offsetSpinBox->value();
    }

    //LIMIT VALUES
    for (int i = 0; i < yData.length(); i ++)
    {
        if (isSV)
        {
            yData[i] = yData[i] <= 0.1 ? 0.1 : yData[i];
            yData[i] = yData[i] >= 10.0 ? 10.0 : yData[i];
        }
        else
        {
            yData[i] = yData[i] = 0 ? 0.00001 : yData[i];
        }
    }

    initialOffset  = *std::min_element(xData.constBegin(), xData.constEnd());
    endOffset      = *std::max_element(xData.constBegin(), xData.constEnd());

    minTP = *std::min_element(yData.constBegin(),yData.constEnd());
    maxTP = *std::max_element(yData.constBegin(),yData.constEnd());

    //If the values are too close together (threshold : 10), separate to at least 10
    if (qFabs(maxTP - minTP) < 10 && isBPM)
    {
        minTP -= 5;
        maxTP += 5;
    }

    //Calculate averageSV and averageBPM
    if (xData.length() <= 1)
    {
        averageTP = xData.length() == 0 ? 0 : yData[0];
    }
    else
    {
        for (int i = 0; i < (xData.length() - 1); i ++)
        {
            averageTP += (yData.at(i) * (xData.at(i + 1) - xData.at(i))) / (endOffset - initialOffset);
        }
    }

    //Auto Zero
    if (autoZeroCheck->isChecked())
    {
        zeroSpinBox->setValue(averageTP);
    }

    //Generates Graph
    customPlot->clearItems();
    QCPItemText *averageLabel = new QCPItemText(customPlot);

    customPlot->graph(0)->setData(xData,yData);
    customPlot->graph(0)->setPen(QPen(isSV ? QColor(50,200,50,255) : QColor(200,50,50,255)));
    customPlot->graph(0)->setBrush(QBrush(isSV ? QColor(50,200,50,20) : QColor(200,50,50,20)));

    customPlot->graph(0)->setLineStyle(isGraphLine ? QCPGraph::lsStepLeft : QCPGraph::lsImpulse);

    averageLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    averageLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    averageLabel->position->setCoords(0.5, 0);
    averageLabel->setText(QString("Average ")
                          .append(isSV ? "SV: " : "BPM: ")
                          .append(QString::number(averageTP)));
    averageLabel->setFont(QFont(font().family(), 12));

    customPlot->xAxis->setRange(initialOffset, endOffset);
    customPlot->yAxis->setRange(isSV ? 0.0 : minTP, isSV ? 10.0 : maxTP);
    customPlot->yAxis->setLabel(isSV ? "SV" : "BPM");

    customPlot->replot(QCustomPlot::rpQueuedReplot);

    //Generate Output
    if (isSV)
    {
        outputBox->clear();
        for(int i = 0; i < xData.length(); i++)
        {
            outputBox->append(amber::compileOMFormatting_SV(QString::number(xData[i]),
                                                            QString::number(yData[i] <= 0 ? -1000 : -100 / yData[i])));
        }
    }
    else if (isBPM)
    {
        outputBox->clear();
        for(int i = 0; i < xData.length(); i++)
        {
            outputBox->append(amber::compileOMFormatting_BPM(QString::number(xData[i]),
                                                             QString::number(yData[i] == 0 ? 9999999 : 60000 / yData[i])));
        }
    }

    outputStatusLabel->setStyleSheet("QLabel { color:green };");
    outputStatusLabel->setText("STATUS: Convert Successful.");
    return;
}

void amber::on_adjuster_adjustSVRadio_clicked()
{
    ui->adjuster_addGroup   ->setTitle  ("Add (SV)");
    ui->adjuster_zeroGroup  ->setTitle  ("Zero (SV)");
    ui->adjuster_addSpinBox ->setMinimum(-10.0);
    ui->adjuster_addSpinBox ->setMaximum(10.0);
    ui->adjuster_zeroSpinBox->setMinimum(0.0);
    ui->adjuster_zeroSpinBox->setMaximum(10.0);
}

void amber::on_adjuster_adjustBPMRadio_clicked()
{
    ui->adjuster_addGroup   ->setTitle  ("Add (BPM)");
    ui->adjuster_zeroGroup  ->setTitle  ("Zero (BPM)");
    ui->adjuster_addSpinBox ->setMinimum(-1000000.0);
    ui->adjuster_addSpinBox ->setMaximum(1000000.0);
    ui->adjuster_zeroSpinBox->setMinimum(0.0);
    ui->adjuster_zeroSpinBox->setMaximum(1000000.0);
}

void amber::on_adjuster_defaultButton_clicked()
{
    ui->adjuster_adjustSVRadio    ->setChecked(true);
    ui->adjuster_adjustBPMRadio   ->setChecked(false);
    ui->adjuster_autoZeroCheck    ->setChecked(true);
    ui->adjuster_invertCheck      ->setChecked(false);
    ui->adjuster_liveUpdateCheck  ->setChecked(false);
    ui->adjuster_multiplySpinBox  ->setValue  (1.0);
    ui->adjuster_addSpinBox       ->setValue  (0.0);
    ui->adjuster_offsetSpinBox    ->setValue  (0.0);
    ui->adjuster_zeroSpinBox      ->setValue  (0.0);
    ui->adjuster_graphLineRadio   ->setChecked(true);
    ui->adjuster_graphScatterRadio->setChecked(false);

    amber::on_adjuster_adjustSVRadio_clicked();

    ui->adjuster_customPlot ->replot(QCustomPlot::rpQueuedReplot);
    ui->adjuster_customPlot->replot(QCustomPlot::rpQueuedReplot);
}

// --------------------------------------------------------------------------------------------------------< PACK SPLITTER >

void amber::on_PS_browseButton_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this, "Open osu! Song Folder", "/home",
                                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->PS_browseLine->setText(filePath);
    QDir fileDir(filePath);

    if (filePath.right(5) == "Songs")
    {
        ui->PS_statusLabel->setText("STATUS: File Path loaded successfully");
        ui->PS_statusLabel->setStyleSheet("QLabel { color:green }");
    } else if (!filePath.isEmpty()){
        ui->PS_statusLabel->setText("STATUS: File Path might be incorrect, make sure it's the [Songs] Folder!");
        ui->PS_statusLabel->setStyleSheet("QLabel { color:orange }");
    } else {
        ui->PS_statusLabel->setText("STATUS: File Path cannot be loaded");
        ui->PS_statusLabel->setStyleSheet("QLabel { color:red }");
    }

    ui->PS_mapListListWidget->clear();
    ui->PS_mapListListWidget->addItems(fileDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs));
}

void amber::on_PS_mapListListWidget_itemClicked(QListWidgetItem *item)
{
    QString mapFilePath = ui->PS_browseLine->text().append("/").append(item->text());

    QDir mapFileDir(mapFilePath);

    QStringList audioFilter,
                difficultyFilter;

    audioFilter     .append("*.mp3");
    audioFilter     .append("*.ogg");
    difficultyFilter.append("*.osu");

    ui->PS_audioFileListListWidget->clear();
    ui->PS_audioFileListListWidget->addItems(mapFileDir.entryList(audioFilter,
                                                                  QDir::NoDotAndDotDot | QDir::Files));

    ui->PS_difficultyListListWidget->clear();
    ui->PS_difficultyListListWidget->addItems(mapFileDir.entryList(difficultyFilter,
                                                                   QDir::NoDotAndDotDot | QDir::Files));
}














