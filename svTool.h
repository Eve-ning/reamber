#ifndef SVTOOL_H
#define SVTOOL_H

#include <QMainWindow>
#include <QStringList>
#include <QString>
#include <QTextBrowser>


namespace Ui {
class svTool;
}

//DEFAULT ARGUMENTS
//Extern to tell the program that the variables have been defined somewhere else (svTool.cpp)
extern QString def_xAxis
              ,def_yAxis
              ,def_offset
              ,def_lnParameter
              ,def_lnOffset
              ,def_bpmCode
              ,def_svCode
              ,def_bpmValue
              ,def_svValue
              ,def_column
              ,def_noOfKeys
              ,def_timingPointLabel
              ,def_hitObjectLabel
              ,def_nnExtension
              ,def_lnExtesion
              ,def_bpmExtension
              ,def_svExtension
              ,def_timingPointType
;

class svTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit svTool(QWidget *parent = 0);
    ~svTool();
    void compileProcOutput(QTextBrowser *inputBoxObject, QTextBrowser *outputBoxObject);

    //COMPILERS
    QString compileOMFormatting_NN(QString xAxis = def_xAxis,
                                   QString offset = def_offset,
                                   QString yAxis = def_yAxis,
                                   QString extension = def_nnExtension);

    QString compileOMFormatting_LN(QString xAxis = def_xAxis,
                                   QString offset = def_offset,
                                   QString lnOffset = def_lnOffset,
                                   QString yAxis = def_yAxis,
                                   QString lnParameter = def_lnParameter,
                                   QString extension = def_lnExtesion);

    QString compileOMFormatting_BPM(QString offset = def_offset,
                                    QString bpmCode = def_bpmCode,
                                    QString extension = def_bpmExtension);

    QString compileOMFormatting_SV(QString offset = def_offset,
                                   QString svCode = def_svCode,
                                   QString extension = def_svExtension);

    QString compileBASICFormatting_hitObject(QString noOfKeys = def_noOfKeys,
                                      QString offset = def_offset,
                                      QString column = def_column,
                                      QString lnOffset = def_lnOffset,
                                      QString label = def_hitObjectLabel);

    QString compileBASICFormatting_timingPoint(QString offset = def_offset,
                                       QString value = def_bpmValue,
                                       QString timingPointType = def_timingPointType,
                                       QString label = def_timingPointLabel);
    //CONVERTERS
    double convertColumnCodeToColumnKey(double columnCode,
                                        double noOfKeys);
    double convertColumnKeyToColumnCode(double columnKey,
                                        double noOfKeys);


private slots:

    void on_home_validateButton_clicked();

    void on_stutter_initSVSlider_valueChanged(int value);

    void on_stutter_initSVSpinBox_valueChanged(double arg1);

    void on_stutter_thresholdSlider_valueChanged(int value);

    void on_stutter_thresholdSpinBox_valueChanged(double arg1);

    void on_stutter_averageSVSpinBox_valueChanged(double arg1);

    void on_stutter_generateButton_clicked();

    void on_home_validateButton_2_clicked();

    void on_copier_generateButton_clicked();

private:
    Ui::svTool *ui;
};

/* class hitObjectEditorClass
{
    QStringList hitObjectEditorList_offset;
    QStringList hitObjectEditorList_position;
public:
    explicit hitObjectEditorClass(QStringList, QStringList);
};

hitObjectEditorClass::hitObjectEditorClass (QStringList a, QStringList b){
    hitObjectEditorList_offset = a;
    hitObjectEditorList_position = b;
} */

#endif // SVTOOL_H
