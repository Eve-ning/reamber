#include "svTool.h"
#include "ui_svTool.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QSplitter>
#include <QStringList>
#include <QRegExp>

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

void svTool::on_home_validateButton_clicked()
{
    //Copy over to Debug
    ui->debug_rawInputBox->setPlainText(ui->home_rawInputBox->toPlainText());

    QStringList partVector, rawInputVector;
    QString rawInputLine, partLine;
    QString noOfKeys;

    //validateType indicates the input type
    enum class inputType {
        nullInput, //0
        editorHitObjectInput, //1
        hitObjectInput, //2
        timingPointInput  //3
    };
    inputType validateType;
    validateType = inputType::nullInput;

    //Set keys
    noOfKeys = ui->home_keysSpinBox->text();
    ui->debug_procInputBox->append(ui->home_keysSpinBox->text());

    //Splits the rawInputBox input into a Vector
    rawInputVector = ui->home_rawInputBox->toPlainText().split("\n");

    //Clears the procInputBox
    ui->debug_procInputBox->clear();

    /*
     * rawInputLine.indexOf("(",1) == -1 <TRUE: Editor Hit Object Input>
     * rawInputLine.indexOf(")",1) == -1 <TRUE: Editor Hit Object Input>
     * rawInputLine.count(QRegExp(",")) > 5) <TRUE: Timing Point Input>
     * rawInputLine.count(QRegExp(",")) <= 5) <TRUE: Hit Object Input>
     */

    //Detect Input
    if ((rawInputVector.at(0)).indexOf("(", 1) != -1 &&
        (rawInputVector.at(0)).indexOf(")",1) != -1){
        validateType = inputType::editorHitObjectInput;
        ui->home_statusLabel->setText("STATUS: Editor Hit Object Format detected.");
        ui->home_statusLabel->setStyleSheet("QLabel { color:green; }");

        //.count = 4: Normal Note
        //.count = 5: Long Note
    } else if (((rawInputVector.at(0)).count(QRegExp(",")) == 4 ||
                (rawInputVector.at(0)).count(QRegExp(",")) == 5) &&
                (rawInputVector.at(0)).indexOf("|",1) == -1){
        validateType = inputType::hitObjectInput;
        ui->home_statusLabel->setText("STATUS: Hit Object Format detected.");
        ui->home_statusLabel->setStyleSheet("QLabel { color:green; }");

    } else if ((rawInputVector.at(0)).count(QRegExp(",")) == 7 &&
               (rawInputVector.at(0)).indexOf("|",1) == -1){
        validateType = inputType::timingPointInput;
        ui->home_statusLabel->setText("STATUS: Timing Point Format detected.");
        ui->home_statusLabel->setStyleSheet("QLabel { color:green; }");

    } else {
        validateType = inputType::nullInput;
        ui->home_statusLabel->setText("STATUS: No Format detected.");
        ui->home_statusLabel->setStyleSheet("QLabel { color:red; }");
    }

    //Switch case for each validation type
    /*
     * Format to use:
     *
     * hitObject/editorHitObject:
         * HITOBJECT|NO_OF_KEYS|OFFSET|KEY|LN_END_OFFSET
         * NO_OF_KEYS: 1 - 18

     * timingPoint:
         * TIMINGPOINT|OFFSET|VALUE|TYPE
         * VALUE: The processed value of BPM or SV
         * TYPE: SV/BPM
     *
     */
    switch (validateType){

    case inputType::nullInput:
        break;

    case inputType::editorHitObjectInput:
        //Reads each line from the rawInputVector
        foreach (rawInputLine, rawInputVector) {

            //Skips any blank lines
            if(rawInputLine.isEmpty()){
                continue;
            }

            //Mid trims the current line from '(' and ')'
            //Split then splits them by ',' into different notes
            partVector = rawInputLine.mid(rawInputLine.indexOf("(",1) + 1,
                                          rawInputLine.indexOf(")",1) - rawInputLine.indexOf("(",1) - 1
                                          ).split(",", QString::SkipEmptyParts);

            //For each note append according to format
            foreach (partLine, partVector){
                ui->debug_procInputBox->append(
                            QString("HITOBJECT|")
                            .append(QString(noOfKeys))
                            .append(QString("|"))
                            .append(partLine)
                            .append(QString("|"))
                            // -1 represents Normal Note
                            .append(QString("-1")));
            }
        }
        break;
    case inputType::hitObjectInput:
        //Reads each line from the rawInputVector
        foreach (rawInputLine, rawInputVector) {

            //Skips any blank lines
            if(rawInputLine.isEmpty()){
                continue;
            }

            //Splits them into parameters
            partVector = rawInputLine.split(",",QString::SkipEmptyParts);

            double keyColumn;

            //Gets the key column through calculation and rounds to 0 D.P.
            keyColumn = round((partVector.at(0).toDouble() / 512 * noOfKeys.toDouble() * 2 + 1) / 2) - 1;

            if(rawInputLine.count(QRegExp(",")) == 4){

                //Detected as Normal Note
                //For each note append according to format
                ui->debug_procInputBox->append(
                            QString("HITOBJECT|")
                            .append(QString(noOfKeys))
                            .append(QString("|"))
                            .append(partVector.at(2))
                            .append(QString("|"))
                            .append(QString::number(keyColumn))
                            .append(QString("|"))
                            // -1 represents Normal Note
                            .append(QString("-1")));

            } else if (rawInputLine.count(QRegExp(",")) == 5){

                //Detected as Long Note
                //For each note append according to format
                ui->debug_procInputBox->append(
                            QString("HITOBJECT|")
                            .append(QString(noOfKeys))
                            .append(QString("|"))
                            .append(partVector.at(2))
                            .append(QString("|"))
                            .append(QString::number(keyColumn))
                            .append(QString("|"))
                            .append(partVector.at(5)
                                    .mid(0,partVector.at(5).indexOf(":",1))));
            }
        }
        break;

    case inputType::timingPointInput:
        //Reads each line from the rawInputVector
        foreach (rawInputLine, rawInputVector) {

            //Skips any blank lines
            if(rawInputLine.isEmpty()){
                continue;
            }

            //Splits them into parameters
            partVector = rawInputLine.split(",",QString::SkipEmptyParts);

            QString timingPointValue;

            //Check Type and calculate timingPointValue
            if (partVector.at(6) == QString("0")){
                //Detected as an SV Timing Point
                timingPointValue = QString::number(-100.0 / partVector.at(1).toDouble());
            } else if (partVector.at(6) == QString("1")){
                //Detected as a BPM Timing Point
                timingPointValue = QString::number(60000.0 / partVector.at(1).toDouble());
            }

            //Detected as Normal Note
            //For each note append according to format
            ui->debug_procInputBox->append(
                        QString("TIMINGPOINT|")
                        .append(partVector.at(0))
                        .append(QString("|"))
                        .append(timingPointValue)
                        .append(QString("|"))
                        .append(partVector.at(6) == QString("0") ? QString("SV") : QString("BPM")));
        }
        break;
    }
}
