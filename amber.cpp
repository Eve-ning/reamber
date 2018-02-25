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

    ui->toolBox->setCurrentIndex(0);

    QIcon windowIcon = QIcon(":/amberResources/icons/amberIcn.ico");

    qDebug() << windowIcon.availableSizes();


    setWindowIcon(QIcon(":/amberResources/icons/amberIcn.ico"));

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




// --------------------------------------------------------------------------------------------------------< DEBUG >
/* Error Handling Idea 4/2/2018
void amber::ERROR_MESSAGE(int ERROR_CODE)
{
//REFERENCE

//-FORMAT-

//-
//#A0000 - MESSAGE NAME
//DETAILS
//-
//-

//[SUPPORTING FUNCTIONS]
//0___ : ALL

//[BASIC]
//11__ : STUTTER
//12__ : COPIER
//13__ : TPF
//14__ : NORMALIZER
//15__ : ADJUSTER
//16__ :
//17__ :
//18__ :
//19__ :
//20__ :

//[ADVANCED]
//50__ : PACK SPLITTER
//51__ :
//52__ :
//53__ :
//54__ :
//55__ :
//56__ :

//[LIST OF ALL ERROR MESSAGES]
//-

//-


//[LIST OF ALL WARNING MESSAGES]




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

    if      (itemString == "Pack Splitter")
    {
        ui->advancedTabWidget->setCurrentIndex(0);
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
    else if (itemString == "Error Log")
    {
        ui->settingsTabWidget->setCurrentIndex(1);
    }
}

void amber::on_toolBox_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
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
        inputList = CONVERT::OMtoBASIC(ui->stutter_inputStatusLabel, true, true, false, inputBox->toPlainText().split("\n", QString::SkipEmptyParts));

        if (inputList.length() == 0){
            return;
        }
        // Set up uniqueOffsetList
        foreach (inputString, inputList)
        {
            partList = inputString.split("|");
            if (!uniqueOffsetList.contains(partList[DEFARGS::HO_OFFSET].toDouble()))
                uniqueOffsetList.append(partList[DEFARGS::HO_OFFSET].toDouble());
        }

        // Generate all SVs in basic format
        for (int i = 0; i < (uniqueOffsetList.length() - 1); ++ i)
        {
            initOffset = uniqueOffsetList.at(i);
            secondOffset = (uniqueOffsetList.at(i + 1) - initOffset) * threshold + initOffset;

            //initSV append
            ui->stutter_outputBox->append(COMPILE::OM_SV(QString::number(initOffset),
                                                                        QString::number(-100.0 / initSV)));

            //secondSV append
            ui->stutter_outputBox->append(COMPILE::OM_SV(QString::number(secondOffset),
                                                                        QString::number(-100.0 / secondSV)));
        }

        //End SV for normalization
        endOffset = uniqueOffsetList.at(uniqueOffsetList.length() - 1);

        //normalizeSV append
        ui->stutter_outputBox->append(COMPILE::OM_SV(QString::number(endOffset),
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
                    HOList, TPList, hitObjectPartList;
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

        inputList_1 = CONVERT::OMtoBASIC(inputStatusLabel_1,
                                              true, true, true,
                                              ui->copier_inputBox->toPlainText().split("\n", QString::SkipEmptyParts));
        inputList_2 = CONVERT::OMtoBASIC(inputStatusLabel_2,
                                              true, true, true,
                                              ui->copier_inputBox_2->toPlainText().split("\n", QString::SkipEmptyParts));

        if (inputList_1.length() == 0 || inputList_2.length() == 0){
            return;
        }

        ui->copier_outputBox->clear();

        //Checks for Type
        if (inputList_1[0].split("|")[DEFARGS::HO_LABEL] == "HITOBJECT")
        {
            boxType1 = inputBoxType::hitObject;
        }
        else if (inputList_1[0].split("|")[DEFARGS::TP_LABEL] == "TIMINGPOINT")
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

        if (inputList_2[0].split("|")[DEFARGS::HO_LABEL] == "HITOBJECT")
        {
            boxType2 = inputBoxType::hitObject;
        }
        else if (inputList_2[0].split("|")[DEFARGS::TP_LABEL] == "TIMINGPOINT")
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
            HOList = inputList_1;
            TPList = inputList_2;
        }
        else
        {
            HOList = inputList_2;
            TPList = inputList_1;
        }

        //Generate Unique Offset List
        foreach (hitObjectString, HOList)
        {
            hitObjectPartList = hitObjectString.split("|");
            if (!uniqueHitObjectOffsetList.contains(hitObjectPartList[DEFARGS::HO_OFFSET].toDouble()))
                uniqueHitObjectOffsetList.append(hitObjectPartList[DEFARGS::HO_OFFSET].toDouble());
        }

        //Gets the offset from the First Timing Point in order to "zero" all Timing Points
        initialTimingPointOffset = TPList[0].split("|")[DEFARGS::TP_OFFSET].toDouble();

        //Generates Code
        foreach (uniqueHitObjectOffset, uniqueHitObjectOffsetList)
        {
            foreach (timingPointPart, TPList)
            {
                timingPointOffset = timingPointPart.split("|", QString::SkipEmptyParts)[1].toDouble();

                if (timingPointPart.split("|", QString::SkipEmptyParts)[DEFARGS::TP_TYPE] == "BPM")
                {
                    ui->copier_outputBox->append(
                    COMPILE::OM_BPM(QString::number(timingPointOffset - initialTimingPointOffset + uniqueHitObjectOffset),
                                                   QString::number(60000 / timingPointPart.split("|",QString::SkipEmptyParts)
                                                                   [DEFARGS::TP_VALUE].toDouble())));
                }
                else
                {
                    ui->copier_outputBox->append(
                    COMPILE::OM_SV(QString::number(timingPointOffset - initialTimingPointOffset + uniqueHitObjectOffset),
                                                  QString::number(-100 / timingPointPart.split("|", QString::SkipEmptyParts)
                                                                  [DEFARGS::TP_VALUE].toDouble())));
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
           initialTP, endTP, averageTP = 0,
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
    else if (CONVERT::EHOtoOFFSETLIST(ui->TPF_editorInputLine->text()).length() == 2)
    {
        initialOffset = CONVERT::EHOtoOFFSETLIST(ui->TPF_editorInputLine->text())[0];
        endOffset = CONVERT::EHOtoOFFSETLIST(ui->TPF_editorInputLine->text())[1];

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
            outputBox->append(COMPILE::OM_SV(QString::number(xData[i]),
                                                            QString::number(yData[i] < 0.1 ? -1000 : -100 / yData[i])));
        }
        else if (isBPM)
        {
            outputBox->append(COMPILE::OM_BPM(QString::number(xData[i]),
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
    statusBox->append(  ("RANGE: ")
                      + (QString::number(initialOffset))
                      + (" ~ ")
                      + (QString::number(endOffset)));

    statusBox->append(  "LINEAR FUNCTION: f(x) = "
                      + QString::number((endTP - initialTP) / intermediatePoints)
                      + "x + "
                      + QString::number(initialTP));

    statusBox->append(  "SINE FUNCTION: f(x) = "
                      + QString::number(amplitude)
                      + " * sin[("
                      + QString::number(frequency)
                      + " * x + "
                      + QString::number(offset)
                      + ") * π]");

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
    averageLabel->setText(  "Average "
                          + isSV ? "SV: " : "BPM: "
                          + QString::number(averageTP));
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

    inputList = CONVERT::OMtoBASIC(statusLabel, false, false, true,
                                        inputBox->toPlainText().split("\n", QString::SkipEmptyParts));

    if (inputList.length() == 0){
        return;
    }

    foreach (inputString, inputList){

        partList = inputString.split("|", QString::SkipEmptyParts);

        if (partList[DEFARGS::TP_TYPE] == "SV"){
            continue;
        }

        partOffset = partList[DEFARGS::TP_OFFSET];
        partBPM = partList[DEFARGS::TP_VALUE];

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

    statusLabel->setText(  ("STATUS: Normalizing to ")
                         + (QString::number(normalizeBPM))
                         + (" BPM"));
    statusLabel->setStyleSheet("QLabel { color:green; }");


    for(int cycle = 0; cycle < BPMList.length(); cycle ++)
    {
        normalizeSV = -100 / (normalizeBPM / BPMList.at(cycle));
        outputBox->append(COMPILE::OM_SV(QString::number(offsetList.at(cycle)),
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
//
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
    graphLineRadio    = ui->adjuster_graphLineRadio;

    QStringList inputList, partList;
    QString inputString;

    double initialOffset,
           endOffset,
           minTP,
           maxTP,
           averageTP = 0;

    bool isSV           = SVRadio->isChecked(),
         isBPM          = BPMRadio->isChecked(),
         isGraphLine    = graphLineRadio->isChecked();

    inputList = CONVERT::OMtoBASIC(inputStatusLabel,
                                        false, false, true,
                                        inputBox->toPlainText().split("\n", QString::SkipEmptyParts));
    QVector<double> xData,
                    yData;

    foreach (inputString, inputList)
    {
        partList = inputString.split("|", QString::SkipEmptyParts);

        if ((partList[DEFARGS::TP_TYPE] == "SV" && isSV) ||
            (partList[DEFARGS::TP_TYPE] == "BPM" && isBPM))
        {
            xData.append(partList[DEFARGS::TP_OFFSET].toDouble());
            yData.append(partList[DEFARGS::TP_VALUE].toDouble());
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
    averageLabel->setText(  "Average "
                          + isSV ? "SV: " : "BPM: "
                          + QString::number(averageTP));
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
            outputBox->append(COMPILE::OM_SV(QString::number(xData[i]),
                                                            QString::number(yData[i] <= 0 ? -1000 : -100 / yData[i])));
        }
    }
    else if (isBPM)
    {
        outputBox->clear();
        for(int i = 0; i < xData.length(); i++)
        {
            outputBox->append(COMPILE::OM_BPM(QString::number(xData[i]),
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
    QLabel      *statusLabel;
    QLineEdit   *browseLine;
    QListWidget *mapListWidget;
    QString      filePath;

    statusLabel   = ui->PS_statusLabel;
    browseLine    = ui->PS_browseLine;
    mapListWidget = ui->PS_mapListListWidget;

    filePath = QFileDialog::getExistingDirectory(this, "Open osu! Song Folder", "/home",
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    browseLine->setText(filePath);
    QDir fileDir(filePath);

    if (filePath.right(5) == "Songs")
    {
        statusLabel->setText("STATUS: File Path loaded successfully");
        statusLabel->setStyleSheet("QLabel { color:green };");
    } else if (!filePath.isEmpty()){
        statusLabel->setText("STATUS: File Path might be incorrect, make sure it's the [Songs] Folder!");
        statusLabel->setStyleSheet("QLabel { color:orange };");
    } else {
        statusLabel->setText("STATUS: File Path cannot be loaded");
        statusLabel->setStyleSheet("QLabel { color:red };");
    }

    mapListWidget->clear();
    mapListWidget->addItems(fileDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs));
}

void amber::on_PS_mapListListWidget_itemClicked(QListWidgetItem *item)
{
    QString mapPath = ui->PS_browseLine->text() + "/" + item->text();
    QDir mapDir(mapPath);

    QListWidget *audioListWidget,
                *difficultyListWidget;

    QStringList audioFilter,
                difficultyFilter;

    audioListWidget      = ui->PS_audioFileListListWidget;
    difficultyListWidget = ui->PS_difficultyListListWidget;

    audioFilter     .append("*.mp3");
    audioFilter     .append("*.ogg");
    difficultyFilter.append("*.osu");

    audioListWidget->clear();
    audioListWidget->addItems(mapDir.entryList(audioFilter, QDir::NoDotAndDotDot | QDir::Files));

    difficultyListWidget->clear();
    difficultyListWidget->addItems(mapDir.entryList(difficultyFilter, QDir::NoDotAndDotDot | QDir::Files));
}

void amber::on_PS_controlSplitButton_clicked()
{
    QListWidget *mapListWidget,
                *audioListWidget,
                *difficultyListWidget;
    QLabel      *statusLabel;
    QLineEdit   *browseLine;
    QString     songsFolderPath,
                mapName,
                convName,
                audioFolderName,
                audioName,
                difficultyName;

    mapListWidget        = ui->PS_mapListListWidget;
    audioListWidget      = ui->PS_audioFileListListWidget;
    difficultyListWidget = ui->PS_difficultyListListWidget;
    statusLabel          = ui->PS_statusLabel;
    browseLine           = ui->PS_browseLine;

    /* [songsFolderPath]
     * D:\osu!\Songs
     *
     * [mapName]
     * 100000 ARTIST - SONG
     *
     * [convName]
     * Converted Files
     *
     * [audioFolderName]
     * audio_mp3
     *
     * [audioName]
     * audio.mp3
     *
     * [difficultyName]
     * difficulty.osu
     *
     * [difficultyBGFileName]
     * bg.jpg
     */

    songsFolderPath = browseLine->text();
    mapName         = mapListWidget->selectedItems()[0]->text();
    convName        = "Converted Files";

    // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files
    QDir convDir(  songsFolderPath
                 + "/"
                 + mapName
                 + "/"
                 + convName);

    // Make Converted Files Directory
    if (convDir.mkpath(".") == false)
    {
        if (convDir.exists())
        {
            statusLabel->setText("STATUS: Convert folder exists already.");
            statusLabel->setStyleSheet("QLabel { color:orange };");

            // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files
            QDesktopServices::openUrl(QUrl::fromLocalFile(  songsFolderPath
                                                          + mapName
                                                          + "/"
                                                          + convName));
        }
        else
        {
            statusLabel->setText("STATUS: Convert folder couldn't be created");
            statusLabel->setStyleSheet("QLabel { color:red };");
            return;
        }
    }
    else
    {
        statusLabel->setText("STATUS: Convert folder successfully created");
        statusLabel->setStyleSheet("QLabel { color:green };");

        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files
        QDesktopServices::openUrl(QUrl::fromLocalFile(  songsFolderPath
                                                      + "/"
                                                      + mapName
                                                      + "/"
                                                      + convName));
    }

    //Copy Audio Files over
    for (int i = 0; i < audioListWidget->count(); i ++)
    {
        /* We firstly create the directories for each of the maps by referring to the audio name
         * We then copy over the audio files to each of those files
         */
        audioName       = audioListWidget->item(i)->text();
        audioFolderName = audioName;
        audioFolderName.replace(".","_");


        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files\audio_mp3\audio.mp3
        QDir audioFolderDir(  songsFolderPath
                            + "/"
                            + mapName
                            + "/"
                            + convName
                            + "/"
                            + audioFolderName);

        // D:\osu!\Songs\100000 ARTIST - SONG\audio.mp3
        QFile audioCopyFile(  songsFolderPath
                            + "/"
                            + mapName
                            + "/"
                            + audioName);

        // Make audio folder for each audio file
        if (audioFolderDir.mkpath(".") == false)
        {
            statusLabel->setText("STATUS: Audio folder couldn't be created");
            statusLabel->setStyleSheet("QLabel { color:red };");
            return;
        }
        else
        {
            statusLabel->setText("STATUS: Audio folder successfully created");
            statusLabel->setStyleSheet("QLabel { color:green };");
        }

        // Copy audio files over
        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files\audio_mp3\audio.mp3
        if (audioCopyFile.copy(  songsFolderPath
                               + "/"
                               + mapName
                               + "/"
                               + convName
                               + "/"
                               + audioFolderName
                               + "/"
                               + audioName)
                               == false )
        {
            statusLabel->setText("STATUS: Copying Failed or File already exists");
            statusLabel->setStyleSheet("QLabel { color:orange };");
        }
        else
        {
            statusLabel->setText("STATUS: Copying successful");
            statusLabel->setStyleSheet("QLabel { color:green };");
        }

    }

    //Check Difficulty Files and copy over
    for (int i = 0; i < difficultyListWidget->count(); i ++)
    {
        /* REFERENCE
         *
         * [General]
         * AudioFilename: audio.mp3
         * AudioLeadIn: 0
         *
         * [Events]
         * //Background and Video events
         * 0,0,"BG.jpg",0,0
         */

        QString strStream,
                difficultyAudioFolderName,
                difficultyBGFileName;

        difficultyName = difficultyListWidget->item(i)->text();

        QFile difficultyFile(  songsFolderPath
                             + "/"
                             + mapName
                             + "/"
                             + difficultyName);
        difficultyFile.open(QIODevice::ReadOnly);
        QTextStream difficultyStream(&difficultyFile);

        while (!difficultyFile.atEnd())
        {
            strStream = difficultyStream.readLine();
            if (strStream.contains("AudioFilename:"))
            {
                difficultyAudioFolderName = strStream.right(strStream.length() - 15).replace(".","_");
            }
            else if (strStream.contains(",\"") && strStream.contains("\","))
            {
                difficultyBGFileName = strStream.mid(strStream.indexOf(",\"") + 2,strStream.indexOf("\",") - 5);
                break;
            }


        }

        difficultyFile.close();

        // D:\osu!\Songs\100000 ARTIST - SONG\difficulty.osu
        QFile difficultyCopyFile(  songsFolderPath
                                 + "/"
                                 + mapName
                                 + "/"
                                 + difficultyName);

        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files\audio_mp3\difficulty.osu
        difficultyCopyFile.copy(  songsFolderPath
                                + "/"
                                + mapName
                                + "/"
                                + convName
                                + "/"
                                + difficultyAudioFolderName
                                + "/"
                                + difficultyName);

        // D:\osu!\Songs\100000 ARTIST - SONG\bg.jpg
        QFile difficultyBGCopyFile(  songsFolderPath
                                   + "/"
                                   + mapName
                                   + "/"
                                   + difficultyBGFileName);

        // D:\osu!\Songs\100000 ARTIST - SONG\Converted Files\audio_mp3\bg.jpg
        difficultyBGCopyFile.copy(  songsFolderPath
                                  + "/"
                                  + mapName
                                  + "/"
                                  + convName
                                  + "/"
                                  + difficultyAudioFolderName
                                  + "/"
                                  + difficultyBGFileName);


    }
}

void amber::on_PS_controlOpenFolderButton_clicked()
{
    QString songsFolderPath,
            mapName;

    if (ui->PS_browseLine->text() != "" || ui->PS_mapListListWidget->selectedItems().size() != 0)
    {
        songsFolderPath = ui->PS_browseLine->text();
        mapName = ui->PS_mapListListWidget->selectedItems()[0]->text();
        QDesktopServices::openUrl(QUrl::fromLocalFile(songsFolderPath + "/" + mapName));

    }
    else
    {
        ui->PS_statusLabel->setText("STATUS: No Map Folder Specified");
        ui->PS_statusLabel->setStyleSheet("QLabel { color:red }");
        return;
    }
}




