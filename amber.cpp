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
 * hitObject/EHO:
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
    tb = ui->statusBox;

    setWindowIcon(QIcon(":/amberResources/icons/amberIcn.ico"));

    // Pre-RenderGraphs
    ui->adjuster_customPlot->addGraph();
    ui->adjuster_customPlot->xAxis->setLabel("Offset");
    ui->adjuster_customPlot->yAxis->setLabel("SV");

    ui->TPF_customPlot->addGraph();
    ui->TPF_customPlot->xAxis->setLabel("Offset");
    ui->TPF_customPlot->yAxis->setLabel("SV");

    // AA ComboBox
// AAObjList = {};

// ui->AA_comboBox->addItems(AAName::getNameList());

}

amber::~amber()
{
    delete ui;
}

// --------------------------------------------------------------------------------------------------------< DEBUG >
/* Error Handling Idea 4/2/2018
void amber::ERROR_MESSAGE(int ERROR_CODE)
{
// REFERENCE

// -FORMAT-

// -
// #A0000 - MESSAGE NAME
// DETAILS
// -
// -

// [SUPPORTING FUNCTIONS]
// 0___ : ALL

// [BASIC]
// 11__ : STUTTER
// 12__ : COPIER
// 13__ : TPF
// 14__ : NORMALIZER
// 15__ : ADJUSTER
// 16__ :
// 17__ :
// 18__ :
// 19__ :
// 20__ :

// [ADVANCED]
// 50__ : PACK SPLITTER
// 51__ :
// 52__ :
// 53__ :
// 54__ :
// 55__ :
// 56__ :

// [LIST OF ALL ERROR MESSAGES]
// -

// -


// [LIST OF ALL WARNING MESSAGES]




    QTextBrowser *messageBrowser;
    QMap<int, QString> messageMap;

    messageBrowser = ui->el_messageBrowser;

    messageMap[1]    = "[0001] QString amber::compileOM_NN has encountered an error.";
    messageMap[2]    = "[0002] QString amber::compileOM_LN has encountered an error.";
    messageMap[3]    = "[0003] QString COMPILE::OM_BPM has encountered an error.";
    messageMap[4]    = "[0004] QString COMPILE::OM_SV has encountered an error.";
    messageMap[5]    = "[0005] QString amber::compileBASIC_HO has encountered an error.";
    messageMap[6]    = "[0006] QString amber::compileBASIC_TP has encountered an error.";
    messageMap[7]    = "[0007] double amber::convertCOLUMN_CODEtoVALUE has encountered an error.";
    messageMap[8]    = "[0008] double amber::convertCOLUMN_VALUEtoCODE has encountered an error.";
    messageMap[9]    = "[0009] QList<double> CONVERT::EHOtoOFFSETLIST has encountered an error.";
    messageMap[10]   = "[0010] QList<int> amber::convertEHOtoCOLUMNLIST has encountered an error.";
    messageMap[11]   = "[0011] QList<double> amber::convertHOtoOFFSETLIST has encountered an error.";
    messageMap[12]   = "[0012] QList<int> amber::convertHitObjectToColumnList has encountered an error.";
    messageMap[13]   = "[0013] QList<double> amber::convertTimingPointToOffsetList has encountered an error.";
    messageMap[14]   = "[0014] QList<double> amber::convertTimingPointToCodeList has encountered an error.";
    messageMap[15]   = "[0015] void amber::compileProcOutput has encountered an error.";
    messageMap[16]   = "[0016] QStringList CONVERT::OMtoBASIC has encountered an error.";
    messageMap[17]   = "[0017] QStringList amber::convertBASICtoOM has encountered an error.";

    messageBrowser->append(messageMap[ERROR_CODE]);
}

void amber::PARAMETER_MESSAGE(QMap<QString, QVariant> PARAMETER_VALUE_LIST)
{
    QVariant VALUE;
    QTextBrowser *parameterBrowser;

    parameterBrowser = ui->el_parameterBrowser;

    QMap<QString, QVariant>::iterator iter;
    for (iter = PARAMETER_VALUE_LIST.begin(); iter != PARAMETER_VALUE_LIST.end(); ++iter)
    {
        if (iter.value().canConvert<QString>())
        {
            parameterBrowser->append(QString("%1 : %2").arg(iter.key()).arg(iter.value().toString()));
        }
        else if (iter.value().canConvert<QStringList>())
        {
            QStringList VALUE_LIST;
            VALUE_LIST = iter.value().toStringList();

            for (int i = 0; i < VALUE_LIST.length(); i ++)
            {
                parameterBrowser->append(QString("%1 : %2").arg(iter.key()).arg(VALUE_LIST[i]));
            }
        }
    }
}
*/
// --------------------------------------------------------------------------------------------------------< HOME >

void amber::on_home_githubIconLabel_clicked()
{
    HYPERLINK::REPO();
}
void amber::on_home_wikiLabel_clicked()
{
    HYPERLINK::WIKI();
}
void amber::on_home_releasesLabel_clicked()
{
    HYPERLINK::RELEASES();
}
void amber::on_home_contactLabel_clicked()
{
    HYPERLINK::CONTACT();
}

// --------------------------------------------------------------------------------------------------------< GENERAL >

// --------------------------------------------------------------------------------------------------------< SETTINGS >

// --------------------------------------------------------------------------------------------------------< QUICK ACCESS >

void amber::on_basicWidgetList_itemClicked(QListWidgetItem *item)
{
    QString itemString;
    itemString = item->text();

    if (itemString == "Home")
    {
        ui->stackedWidget->setCurrentIndex(0);
        return;
    } else {
        ui->stackedWidget->setCurrentIndex(1);
    }

    if      (itemString == "Stutter")
    {
        ui->basicStackedWidget->setCurrentIndex(0);
    }
    else if (itemString == "Copier")
    {
        ui->basicStackedWidget->setCurrentIndex(1);
    }
    else if (itemString == "2-Point Function")
    {
        ui->basicStackedWidget->setCurrentIndex(2);
    }
    else if (itemString == "Normalizer")
    {
        ui->basicStackedWidget->setCurrentIndex(3);
    }
    else if (itemString == "Adjuster")
    {
        ui->basicStackedWidget->setCurrentIndex(4);
    }

}

// --------------------------------------------------------------------------------------------------------< INPUT >

/* REMOVED 13/1/2018 */

// --------------------------------------------------------------------------------------------------------< STUTTER >

// Connect Stutter Widgets
void amber::on_stutter_initSVSlider_valueChanged(int value)
{
    ui->stutter_initSVLabel->setText(QString::number(value / 100.0, 'f', 2));
}
void amber::on_stutter_thresholdSlider_valueChanged(int value)
{
    ui->stutter_thresholdLabel->setText(QString::number(value));

    // averageSV = initSV * threshold + secondSV * (1 - threshold);
    // initSV is an abstract value, we can just set averageSV and threshold which are concrete values then use initSV calculate

    SliderVelocity maxInitSV, minInitSV, averageSV;
    double threshold;

    averageSV = ui->stutter_averageSVSpinBox->value();
    threshold = value;

    // Set Offset according to threshold
    TimingPointList stutter(QList<TimingPoint>({TimingPoint(0, 1, false),
                            TimingPoint(threshold, 1, false),
                            TimingPoint(100, 1, false)}));

    // We analyse what is the value needed to adjust to the maximum and minimum
    // So if the second SV is bound between 0.1 and 10.0, what value would it take to break the boundaries

    // Where secondSV = 0.1
    stutter[1].setValue(0.1);

    stutter.adjustToAverage(averageSV, 0);
    maxInitSV = stutter[0].getValue();

    // Where secondSV = 10.0
    stutter[1].setValue(10.0);

    stutter.adjustToAverage(averageSV, 0);
    minInitSV = stutter[0].getValue();

    // Set Maximum and Minimum
    ui->stutter_initSVSlider-> setMaximum((int) (maxInitSV.value() * 100));
    ui->stutter_initSVSlider-> setMinimum((int) (minInitSV.value() * 100));
    ui->stutter_maxSVLabel->setText(QString::number(maxInitSV.value(), 'f', 2));
    ui->stutter_minSVLabel->setText(QString::number(minInitSV.value(), 'f', 2));
}
void amber::on_stutter_averageSVSpinBox_valueChanged(double arg1)
{
    SliderVelocity maxInitSV, minInitSV, averageSV;
    double threshold;

    averageSV = arg1;
    threshold = ui->stutter_thresholdSlider->value() / 100;

    TimingPointList stutter(QList<TimingPoint>({TimingPoint(), TimingPoint(), TimingPoint()}));

    // Set Offset according to threshold
    stutter[0].setOffset(0);
    stutter[1].setOffset(threshold);
    stutter[2].setOffset(100);

    // We analyse what is the value needed to adjust to the maximum and minimum
    // So if the second SV is bound between 0.1 and 10.0, what value would it take to break the boundaries

    // Where secondSV = 0.1
    stutter[1].setValue(0.1);

    stutter.adjustToAverage(averageSV, 0);
    maxInitSV = stutter[0].getValue();

    // Where secondSV = 10.0
    stutter[1].setValue(10.0);

    stutter.adjustToAverage(averageSV, 0);
    minInitSV = stutter[0].getValue();

    // Set Maximum and Minimum
    ui->stutter_initSVSlider-> setMaximum(maxInitSV.value() * 10);
    ui->stutter_initSVSlider-> setMinimum(minInitSV.value() * 10);
    ui->stutter_maxSVLabel->setText(QString::number(maxInitSV.value(), 'f', 2));
    ui->stutter_minSVLabel->setText(QString::number(minInitSV.value(), 'f', 2));
}

// Stutter Generate Button
void amber::on_stutter_generateButton_clicked()
{
    double threshold;
    SliderVelocity initSV, secondSV, averageSV;
    Offset endOffset;

    QPlainTextEdit *inputBox;

    inputBox  = ui->stutter_inputBox;
    threshold = ui->stutter_thresholdLabel->text().toDouble() / 100;
    initSV    = SliderVelocity(ui->stutter_initSVLabel->text().toDouble());
    averageSV = SliderVelocity(ui->stutter_averageSVSpinBox->value());
    secondSV  = SliderVelocity((averageSV - (initSV * threshold)) / (1 - threshold));

    ui->stutter_outputBox->clear();

    // Set input vector
    HitObjectList noteList(inputBox, 1);

    if (noteList.getSize() == 0){
        STATMSG("Got size 0.");
        return;
    } else if (noteList.getLoadFail())
    {
        STATMSG("Load Unsuccessful.");
        return;
    }

    noteList.makeUnique();

    // Generate all SVs in basic format
    for (int i = 0; i < (noteList.getSize() - 1); ++ i)
    {
        TimingPointList stutter;
        // First SV
        stutter.append(TimingPoint(noteList[i].getOffset(), initSV, false));

        // Second SV
        stutter.append(TimingPoint(noteList[i].getOffset()
                                           + (noteList.getLength(i) * threshold), secondSV, false));

        // initSV append
        ui->stutter_outputBox->append(stutter[0].toString());

        // secondSV append
        ui->stutter_outputBox->append(stutter[1].toString());
    }

    // End SV for normalization
    endOffset = noteList[noteList.getSize() - 1].getOffset();

    TimingPoint endTP(endOffset, averageSV, false);

    // normalizeSV append
    ui->stutter_outputBox->append(endTP.toString());
}

// --------------------------------------------------------------------------------------------------------< COPIER >

// Copier Generate Button
void amber::on_copier_generateButton_clicked()
{
    QString hitObjStr,
            timingPointStr;

    hitObjStr = ui->copier_inputBox->toPlainText();
    timingPointStr = ui->copier_inputBox_2->toPlainText();

    // Invalid Cases
    if (!ValidObj::assertHitObject(hitObjStr))
    {
        STATMSG("Input Box 1 is not a HitObject.");
        return;
    }
    if (!ValidObj::assertTimingPoint(timingPointStr.split('\n')))
    {
        STATMSG("Input Box 2 is not a TimingPoint.");
        return;
    }

    TimingPointList timingPointList(timingPointStr);
    HitObjectList   hitObjectList(hitObjStr);

// // Invalid Case: Inputs same in type
// if ((boxInfo_1.getIsHO() && boxInfo_2.getIsHO()) ||
// (boxInfo_1.getIsTP() && boxInfo_2.getIsTP()))
// {
// STATMSG("Inputs should be different in type.");
// return;
// }

    // We clear only after the input is invalid to prevent accidental clearing
    ui->copier_outputBox->clear();

    // Generate Unique Offset List
    hitObjectList.makeUnique();

    // Zero the list to make use of OM_HO's initial offset
    timingPointList.zero();

    for (int tempHO = 0; tempHO < hitObjectList.getSize(); tempHO++)
    {
        for (int tempTP = 0; tempTP < timingPointList.getSize(); tempTP++)
        {
            // We take the zero-ed list and add the offset from hitObjectList
            timingPointList.addOffset(hitObjectList[tempHO].getOffset());

            // Append to output
            ui->copier_outputBox->append(timingPointList[tempTP].toString());

            // Zero it again
            timingPointList.zero();
        }
    }

    STATMSG("Convert Successful.");

}

// --------------------------------------------------------------------------------------------------------< TWO POINT FUNCTION >

void amber::on_TPF_initialTPSlider_valueChanged(int value)
{
    ui->TPF_initialTPLabel->setText(QString::number(value / 100.0, 'f', 2));
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_endTPSlider_valueChanged(int value)
{
    ui->TPF_endTPLabel->setText(QString::number(value/ 100.0, 'f', 2));
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_offsetSlider_valueChanged(int value)
{
    ui->TPF_offsetLabel->setText(QString::number(value) + "ms");
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_frequencySlider_valueChanged(int value)
{
    ui->TPF_frequencyLabel->setText(QString::number(value) + "%");
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_amplitudeSlider_valueChanged(int value)
{
    ui->TPF_amplitudeLabel->setText(QString::number(value) + "%");
    if (ui->TPF_liveUpdateCheck->checkState() == Qt::Checked){
        amber::on_TPF_generateButton_clicked();
    }
}
void amber::on_TPF_intermediateSpinBox_valueChanged(int arg1)
{
    Q_UNUSED(arg1)
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

// Reset Values to Default
void amber::on_TPF_defaultButton_clicked()
{
    if (ui->TPF_SVRadio->isChecked())
    {
        ui->TPF_initialTPSlider->setMaximum(1000);
        ui->TPF_initialTPSlider->setMinimum(10);
        ui->TPF_initialTPSlider->setValue(100);
        ui->TPF_endTPSlider->setMaximum(1000);
        ui->TPF_endTPSlider->setMinimum(10);
        ui->TPF_endTPSlider->setValue(100);

        ui->TPF_amplitudeSlider->setValue(0);
        ui->TPF_offsetSlider->setValue(0);
        ui->TPF_frequencySlider->setValue(100);
        ui->TPF_intermediateSpinBox->setValue(100);

        ui->TPF_initialTPGroup->setTitle("Initial SV:");
        ui->TPF_endTPGroup->setTitle("End SV:");
    }
    else if (ui->TPF_BPMRadio->isChecked())
    {
        ui->TPF_initialTPSlider->setMaximum(500000);
        ui->TPF_initialTPSlider->setMinimum(100);
        ui->TPF_initialTPSlider->setValue(100);
        ui->TPF_endTPSlider->setMaximum(500000);
        ui->TPF_endTPSlider->setMinimum(100);
        ui->TPF_endTPSlider->setValue(100);

        ui->TPF_amplitudeSlider->setValue(0);
        ui->TPF_offsetSlider->setValue(0);
        ui->TPF_frequencySlider->setValue(100);
        ui->TPF_intermediateSpinBox->setValue(100);

        ui->TPF_initialTPGroup->setTitle("Initial BPM:");
        ui->TPF_endTPGroup->setTitle("End BPM:");
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
     * For this function, we are going to have 2 separate graphs, linear and a sine graph (Default
     * Range: PI)
     *
     * SINE GRAPH: This will control the "curve" modification of the graph, dependant on the <layman>
     * Curve Factor (a.k.a. Amplitude).
     *             Its offset is defaulted to 0 as its start and end point (0 - PI) is 0, hence not
     * affecting the start and end points
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

    QTextBrowser* outputBox;
    QRadioButton *SVRadioButton, *BPMRadioButton;
    QCustomPlot* customPlot;

    SVRadioButton = ui->TPF_SVRadio;
    BPMRadioButton = ui->TPF_BPMRadio;
    outputBox = ui->TPF_outputBox;
    customPlot = ui->TPF_customPlot;

    HitObjectList noteInput;
    TimingPointList output;

    noteInput = ui->TPF_editorInputLine->text();

    Offset initialOffset, endOffset;
    double initialValue, endValue, averageValue = 0;
    double offset, amplitude, frequency;
    int intermediatePoints;

    bool isSV = SVRadioButton->isChecked(),
         isBPM = BPMRadioButton->isChecked();

    outputBox->clear();

    // Set startOffset and endOffset
    if (ui->TPF_editorInputLine->text().isEmpty())
    {
        STATMSG("No Input detected");
        return;
    }
    else if (noteInput.getSize() == 2)
    {
        initialOffset = noteInput[0].getOffset();
        endOffset = noteInput[1].getOffset();
    }
    else
    {
        STATMSG("Make sure you input 2 Editor Hit Objects in the Input.");
        return;
    }

    // Set other parameters
    initialValue = (double) ui->TPF_initialTPSlider->value() / 100;
    endValue =     (double) ui->TPF_endTPSlider->value() / 100;
    offset =    (double) ui->TPF_offsetSlider->value() / 100;
    amplitude = (double) ui->TPF_amplitudeSlider->value() / 100;
    frequency = (double) ui->TPF_frequencySlider->value() / 100;
    intermediatePoints = ui->TPF_intermediateSpinBox->value();

    // Generate vectors for graph
    QVector<double> xData(intermediatePoints + 1), yData(intermediatePoints + 1);
    QVector<double> yLinear(intermediatePoints + 1);
    QVector<double> ySine(intermediatePoints + 1);

    double xValue;

    for (int i = 0; i < intermediatePoints + 1; ++i)
    {
        // We find the distance between each point via xValue
        xValue = i / ((double)intermediatePoints);
        xData[i] = (xValue * (endOffset - initialOffset).value()) + initialOffset.value();

        // Graph for Respective functions
        yLinear[i] = xValue * (endValue - initialValue) + initialValue;
        ySine[i] = amplitude * qSin(frequency * (xValue + offset) * M_PI) * ((endValue + initialValue) / 2);

        // Merge together to form Y
        yData[i] = yLinear[i] + ySine[i];

        // Append to our output
        output.append(TimingPoint (xData[i], yData[i], isBPM));
    }

    // Push to output box
    ui->TPF_outputBox->append(output.toString().join('\n'));

    // Get average
    averageValue = output.getAverage(isBPM ? Info::IS_BPM : Info::IS_SV);

    customPlot->graph(0)->setData(xData, yData);
    customPlot->graph(0)->setPen(QPen(Qt::black));
    customPlot->graph(0)->setBrush(QBrush(QColor(100, 100, 100, 20)));
    customPlot->xAxis->setRange(initialOffset, endOffset);

    double minTP = *std::min_element(yData.constBegin(), yData.constEnd());
    double maxTP = *std::max_element(yData.constBegin(), yData.constEnd());

    customPlot->clearItems();
    QCPItemText* averageLabel = new QCPItemText(customPlot);
    averageLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
    averageLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    averageLabel->position->setCoords(0.5, 0);
    averageLabel->setText(QString("Average ") +
                          (isSV ? "SV: " : "BPM: ") +
                          QString::number(averageValue));
    averageLabel->setFont(QFont(font().family(), 12));

    // Set Axis
    if (isSV)
    {
        customPlot->yAxis->setLabel("SV");
        customPlot->yAxis->setRange(0.1, 10.0); // Default osu!mania SV clamps
    }
    else if (isBPM)
    {
        customPlot->yAxis->setLabel("BPM");
        customPlot->yAxis->setRange(minTP < 0 ? 0 : minTP, // We clamp on 0 BPM
                                    maxTP * 1.1); // We have some space at the top to make it look better
    }
    else
    {
        return;
    }

    customPlot->replot(QCustomPlot::rpQueuedReplot);

    /* Redacted message pushing
     *
     * if (!ui->TPF_liveUpdateCheck) // Do not push messages on live updates
    {
        STATMSG(  ("RANGE: ")
                  + (QString(initialOffset))
                  + (" ~ ")
                  + (QString(endOffset)));

        STATMSG(  "LINEAR FUNCTION: f(x) = "
                  + QString::number((endValue - initialValue) / intermediatePoints)
                  + "x + "
                  + QString::number(initialValue));

        STATMSG(  "SINE FUNCTION: f(x) = "
                  + QString::number(amplitude)
                  + " * sin[("
                  + QString::number(frequency)
                  + " * x + "
                  + QString::number(offset)
                  + ") * π]");
    }*/

}

// --------------------------------------------------------------------------------------------------------< NORMALIZER >

void amber::on_normalizer_generateButton_clicked()
{
    QPlainTextEdit *inputBox;
    QTextBrowser   *outputBox;
    QListWidget    *listWidget;
    QCheckBox      *overrideCheck;
    QDoubleSpinBox *overrideDoubleSpinBox;
    QLineEdit      *customBPMLine;

    double normalizeBPM;

    inputBox              = ui->normalizer_inputBox;
    outputBox             = ui->normalizer_outputBox;
    listWidget            = ui->normalizer_BPMListWidget;
    customBPMLine         = ui->normalizer_selectedBPMLine;
    overrideCheck         = ui->normalizer_overrideCheck;
    overrideDoubleSpinBox = ui->normalizer_overrideDoubleSpinBox;

    outputBox-> clear();
    listWidget->clear();

    TimingPointList timingPointList(inputBox);

    if (timingPointList.isEmpty()){
        STATMSG("Input is empty.");
        return;
    }

    // We reassign timingPointList to have only BPM Inputs
    timingPointList = TimingPointList(timingPointList.splitByType(Info::IS_BPM));

    if (timingPointList.isEmpty()){
        STATMSG("Input at least 1 BPM Point.");
        return;
    }

    // Add items into List widget for user to select
    for (int temp = 0; temp < timingPointList.getSize(); temp++){
        listWidget->addItem(QString("BPM: ")
                            .append(QString::number(timingPointList[temp].getValue()))
                            .append(" | Offset: ")
                            .append(QString(timingPointList[temp].getOffset())));
    }

    // Case of overriding
    if (overrideCheck->isChecked())
    {
        normalizeBPM = overrideDoubleSpinBox->value();
    }
    else if (customBPMLine->text() != "Awaiting Selection...")
    {
        normalizeBPM = customBPMLine->text().toDouble();
    }
    else
    {
        STATMSG("Select 1 BPM Timing Point or use the Manual Override");
        return;
    }

    STATMSG(("Normalizing to ")
            + (QString::number(normalizeBPM))
            + (" BPM"));

    // Append to output
    for (int temp = 0; temp < timingPointList.getSize(); temp ++)
    {
        timingPointList.convertToSV(normalizeBPM);
        outputBox->append(timingPointList[temp].toString());
    }

    return;
}
void amber::on_normalizer_BPMListWidget_itemPressed(QListWidgetItem *item)
{
    ui->normalizer_selectedBPMLine->setText(item->text()
                                            .mid(5, item->text().indexOf("|") - 5));
}

// --------------------------------------------------------------------------------------------------------< DEFAULT >

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
    QRadioButton   *SVRadio,
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
    SVRadio           = ui->adjuster_adjustSVRadio;
    graphLineRadio    = ui->adjuster_graphLineRadio;

    TimingPointList inputTPList(inputBox->toPlainText());

    Offset initialOffset,
           endOffset;
    double minTP,
           maxTP,
           averageTP = 0;

    bool isSV        = SVRadio->isChecked(),
         isGraphLine = graphLineRadio->isChecked();

    Info info(isSV ? Info::IS_SV : Info::IS_BPM);

    // We trim the timingPointList according to selection
    inputTPList = TimingPointList(inputTPList.splitByType(info));

    // Return if type is empty
    if (inputTPList.isEmpty()){
        STATMSG(QString(isSV ? "<SV>" : "<BPM>") + "Selected Type is empty");
        return;
    }

    // ZERO -
    inputTPList.subtractValue(zeroSpinBox->value());

    // INVERT
    if (invertCheck->isChecked())
    {
        inputTPList.multiplyValue(-1);
    }

    // MULTIPLY
    inputTPList.multiplyValue(multiplySpinBox->value());

    // ADD
    inputTPList.addValue(addSpinBox->value());

    // ZERO +
    inputTPList.addValue(zeroSpinBox->value());

    // OFFSET
    inputTPList.addOffset(offsetSpinBox->value());

    initialOffset  = inputTPList.getMinOffset();
    endOffset      = inputTPList.getMaxOffset();

    minTP = inputTPList.getMinValue(info);
    maxTP = inputTPList.getMaxValue(info);

    // If the values are too close together (threshold : 10), separate to at least 10
    // Update: I'm not sure why i do this
//    if (qFabs(maxTP - minTP) < 10 && !isSV)
//    {
//        minTP -= 5;
//        maxTP += 5;
//    }

    // Calculate averageSV and averageBPM
    averageTP = inputTPList.getAverage(info);

    // Auto Zero
    if (autoZeroCheck->isChecked())
    {
        zeroSpinBox->setValue(averageTP);
    }

    // Generates Graph
    customPlot->clearItems();
    QCPItemText *averageLabel = new QCPItemText(customPlot);

    QList<Offset> offsetList = inputTPList.getOffsetList(info);
    QList<double> offsetList_d;
    for (int i = 0; i < offsetList.length(); i ++){
        offsetList_d.append(offsetList[i]);
    }

    // Declare Data
    customPlot->graph(0)->setData(offsetList_d.toVector(),
                                  inputTPList.getValueList(info).toVector());
    customPlot->graph(0)->setPen(QPen(isSV ? QColor(50,200,50,255) : QColor(200,50,50,255)));
    customPlot->graph(0)->setBrush(QBrush(isSV ? QColor(50,200,50,20) : QColor(200,50,50,20)));

    customPlot->graph(0)->setLineStyle(isGraphLine ? QCPGraph::lsStepLeft : QCPGraph::lsImpulse);

    averageLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    averageLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    averageLabel->position->setCoords(0.5, 0);
    averageLabel->setText(QString("Average ")
                          + (isSV ? "SV: " : "BPM: ")
                          + QString::number(averageTP, 'f', 2));
    averageLabel->setFont(QFont(font().family(), 12));

    customPlot->xAxis->setRange(initialOffset, endOffset);
    customPlot->yAxis->setRange(isSV ? 0.0 : minTP, isSV ? 10.0 : maxTP);
    customPlot->yAxis->setLabel(isSV ? "SV" : "BPM");

    customPlot->replot(QCustomPlot::rpQueuedReplot);

    outputBox->clear();

    // Generate Output
    for (int temp = 0; temp < inputTPList.getSize(); temp++)
    {
        outputBox->append(inputTPList[temp].toString());
    }


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

//void amber::on_PS_browseButton_clicked()
//{
//    QLineEdit   *browseLine;
//    QListWidget *mapListWidget;
//    QString      filePath;

//    browseLine    = ui->PS_browseLine;
//    mapListWidget = ui->PS_mapListListWidget;

//    filePath = QFileDialog::getExistingDirectory(this, "Open osu! Song Folder", "/home",
//                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
//    browseLine->setText(filePath);
//    QDir fileDir(filePath);

//    if (filePath.right(5) == "Songs")
//    {
//        STATMSG("File Path loaded successfully");
//    } else if (!filePath.isEmpty()){
//        STATMSG("File Path might be incorrect, make sure it's the [Songs] Folder!");
//    } else {
//        STATMSG("File Path cannot be loaded");
//    }

//    mapListWidget->clear();
//    mapListWidget->addItems(fileDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs));
//}
//void amber::on_PS_mapListListWidget_itemClicked(QListWidgetItem *item)
//{
//    QString mapPath = ui->PS_browseLine->text() + "/" + item->text();
//    QDir mapDir(mapPath);

//    QListWidget *audioListWidget,
//            *difficultyListWidget;

//    QStringList audioFilter,
//            difficultyFilter;

//    audioListWidget      = ui->PS_audioFileListListWidget;
//    difficultyListWidget = ui->PS_difficultyListListWidget;

//    audioFilter     .append("*.mp3");
//    audioFilter     .append("*.ogg");
//    difficultyFilter.append("*.osu");

//    audioListWidget->clear();
//    audioListWidget->addItems(mapDir.entryList(audioFilter, QDir::NoDotAndDotDot | QDir::Files));

//    difficultyListWidget->clear();
//    difficultyListWidget->addItems(mapDir.entryList(difficultyFilter, QDir::NoDotAndDotDot | QDir::Files));
//}
//void amber::on_PS_controlSplitButton_clicked()
//{
//    QListWidget *mapListWidget,
//            *audioListWidget,
//            *difficultyListWidget;
//    QLineEdit   *browseLine;
//    QString     songsFolderPath,
//            mapName,
//            convName,
//            audioFolderName,
//            audioName,
//            difficultyName;

//    mapListWidget        = ui->PS_mapListListWidget;
//    audioListWidget      = ui->PS_audioFileListListWidget;
//    difficultyListWidget = ui->PS_difficultyListListWidget;
//    browseLine           = ui->PS_browseLine;

//    /* EXAMPLE
//     * [songsFolderPath]
//     * D:\osu!\Songs
//     *
//     * [mapName]
//     * 100000 ARTIST - SONG
//     *
//     * [convName]
//     * Converted Files
//     *
//     * [audioFolderName]
//     * audio_mp3
//     *
//     * [audioName]
//     * audio.mp3
//     *
//     * [difficultyName]
//     * difficulty.osu
//     *
//     * [difficultyBGFileName]
//     * bg.jpg
//     */


//    songsFolderPath = browseLine->text();
//    mapName         = mapListWidget->selectedItems()[0]->text();
//    convName        = "Converted Files";

//    // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files
//    QDir convDir(  songsFolderPath
//                   + "/"
//                   + mapName
//                   + "/"
//                   + convName);

//    // CREATE: CONVERTED FILES FOLDER
//    if (convDir.mkpath(".") == false) // Cannot create Convert Files Dir
//    {
//        if (convDir.exists())
//        {
//            STATMSG("Convert folder exists already.");
//            // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files
//            QDesktopServices::openUrl(QUrl::fromLocalFile(  songsFolderPath
//                                                            + mapName
//                                                            + "/"
//                                                            + convName));
//        }
//        else
//        {
//            STATMSG("Convert folder couldn't be created");
//            return;
//        }
//    }
//    else
//    {
//        STATMSG("Convert folder successfully created");

//        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files
//        QDesktopServices::openUrl(QUrl::fromLocalFile(  songsFolderPath
//                                                        + "/"
//                                                        + mapName
//                                                        + "/"
//                                                        + convName));
//    }

//    // CREATE: AUDIO FILES FOLDER
//    for (int i = 0; i < audioListWidget->count(); i ++)
//    {
//        /* We firstly create the directories for each of the maps by referring to the audio name
//         * We then copy over the audio files to each of those files
//         */
//        audioName       = audioListWidget->item(i)->text();
//        audioFolderName = audioName;
//        audioFolderName.replace(".","_");

//        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files\audio_mp3\audio.mp3
//        QDir audioFolderDir(  songsFolderPath
//                              + "/"
//                              + mapName
//                              + "/"
//                              + convName
//                              + "/"
//                              + audioFolderName);

//        // D:\osu!\Songs\100000 ARTIST - SONG\audio.mp3
//        QFile audioCopyFile(  songsFolderPath
//                              + "/"
//                              + mapName
//                              + "/"
//                              + audioName);

//        // Make audio folder for each audio file
//        if (audioFolderDir.mkpath(".") == false)
//        {
//            STATMSG("Audio folder couldn't be created");
//            return;
//        }
//        else
//        {
//            STATMSG("Audio folder successfully created");
//        }

//        // COPY: AUDIO FILES
//        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files\audio_mp3\audio.mp3
//        if (audioCopyFile.copy(  songsFolderPath
//                                 + "/"
//                                 + mapName
//                                 + "/"
//                                 + convName
//                                 + "/"
//                                 + audioFolderName
//                                 + "/"
//                                 + audioName)
//                == false )
//        {
//            STATMSG("Copying Failed or File already exists");
//        }
//        else
//        {
//            STATMSG("Copying successful");
//        }

//    }

//    // COPY: DIFFICULTY & BG OVER
//    for (int i = 0; i < difficultyListWidget->count(); i ++)
//    {
//        /* REFERENCE
//         *
//         * [General]
//         * AudioFilename: audio.mp3
//         * AudioLeadIn: 0
//         *
//         * [Events]
//         * // Background and Video events
//         * 0,0,"BG.jpg",0,0
//         */

//        QString strStream,
//                difficultyAudioFolderName,
//                difficultyBGFileName;

//        difficultyName = difficultyListWidget->item(i)->text();

//        QFile difficultyFile(  songsFolderPath
//                               + "/"
//                               + mapName
//                               + "/"
//                               + difficultyName);

//        // READ: DIFFICULTY
//        difficultyFile.open(QIODevice::ReadOnly);
//        QTextStream difficultyStream(&difficultyFile);

//        while (!difficultyFile.atEnd())
//        {
//            strStream = difficultyStream.readLine();

//            if (strStream.contains("AudioFilename:")) // CHECK FOR AUDIO FILE NAME
//            {
//                difficultyAudioFolderName = strStream.right(strStream.length() - 15).replace(".","_");
//            }
//            else if (strStream.contains(",\"") && strStream.contains("\",")) // CHECK FOR BG FILE NAME
//            {
//                difficultyBGFileName = strStream.mid(strStream.indexOf(",\"") + 2,strStream.indexOf("\",") - 5);
//                break;
//            }
//        }

//        difficultyFile.close();

//        // D:\osu!\Songs\100000 ARTIST - SONG\difficulty.osu
//        QFile difficultyCopyFile(  songsFolderPath
//                                   + "/"
//                                   + mapName
//                                   + "/"
//                                   + difficultyName);

//        // COPY: DIFFICULTY
//        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files\audio_mp3\difficulty.osu
//        difficultyCopyFile.copy(  songsFolderPath
//                                  + "/"
//                                  + mapName
//                                  + "/"
//                                  + convName
//                                  + "/"
//                                  + difficultyAudioFolderName
//                                  + "/"
//                                  + difficultyName);

//        // D:\osu!\Songs\100000 ARTIST - SONG\bg.jpg
//        QFile difficultyBGCopyFile(  songsFolderPath
//                                     + "/"
//                                     + mapName
//                                     + "/"
//                                     + difficultyBGFileName);

//        // COPY: AUDIO
//        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files\audio_mp3\bg.jpg
//        difficultyBGCopyFile.copy(  songsFolderPath
//                                    + "/"
//                                    + mapName
//                                    + "/"
//                                    + convName
//                                    + "/"
//                                    + difficultyAudioFolderName
//                                    + "/"
//                                    + difficultyBGFileName);


//    }
//}
//void amber::on_PS_controlOpenFolderButton_clicked()
//{
//    QString songsFolderPath,
//            mapName;

//    if (ui->PS_browseLine->text() != "" || ui->PS_mapListListWidget->selectedItems().size() != 0)
//    {
//        songsFolderPath = ui->PS_browseLine->text();
//        mapName = ui->PS_mapListListWidget->selectedItems()[0]->text();
//        QDesktopServices::openUrl(QUrl::fromLocalFile(songsFolderPath + "/" + mapName));

//    }
//    else
//    {
//        STATMSG("No Map Folder Specified");
//        return;
//    }
//}

// --------------------------------------------------------------------------------------------------------< ADV ADJUSTER >

