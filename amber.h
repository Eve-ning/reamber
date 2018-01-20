#ifndef AMBER_H
#define AMBER_H

#include <QMainWindow>
#include <QStringList>
#include <QString>
#include <QTextBrowser>
#include <QPlainTextEdit>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QVector>
#include <QRegExp>
#include <QList>
#include <QPen>
#include <QBrush>
#include <QtMath>
#include <QRadioButton>



namespace Ui {
class amber;
}

//DEFAULT ARGUMENTS
//Extern to tell the program that the variables have been defined somewhere else (amber.cpp)
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
              ,def_lnExtension
              ,def_bpmExtension
              ,def_svExtension
              ,def_timingPointType
;

class amber : public QMainWindow
{
    Q_OBJECT

public:
    explicit amber(QWidget *parent = 0);
    ~amber();
    void compileProcOutput(QTextBrowser *inputBoxObject, QTextBrowser *outputBoxObject);

    //SET DEFAULT
    void saveDefaultValues();


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
                                   QString extension = def_lnExtension);

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

    QList<double> convertEditorHitObjectToOffsetList(QString editorHitObject);
    QList<int> convertEditorHitObjectToColumnList(QString editorHitObject);
    QList<double> convertHitObjectToOffsetList(QStringList hitObjectList);
    QList<int> convertHitObjectToColumnList(QStringList hitObjectList, int keyCount);
    QList<double> convertTimingPointToOffsetList(QStringList timingPointList);
    QList<double> convertTimingPointToCodeList(QStringList timingPointList);

    QStringList convertOMtoBASIC(QLabel *messageLabel,
                                 bool acceptEditorHitObject = true,
                                 bool acceptHitObject = true,
                                 bool acceptTimingPoint = true,
                                 QStringList input = {},
                                 int noOfKeys = 4);

    QStringList convertBASICtoOM(QLabel *messageLabel,
                                 QStringList input = {});

    //CHECKS
    bool checkEditorHitObject(QString editorHitObject);
    bool checkHitObject(QString hitObject);
    bool checkTimingPoint(QString timingPoint);

    bool checkEditorHitObject(QPlainTextEdit *box);
    bool checkHitObject(QPlainTextEdit *box);
    bool checkTimingPoint(QPlainTextEdit *box);

    bool checkEditorHitObject(QStringList editorHitObjectList);
    bool checkHitObject(QStringList hitObjectList);
    bool checkTimingPoint(QStringList timingPointList);

    bool checkHitObjectNN(QString hitObjectNN);
    bool checkHitObjectLN(QString hitObjectLN);
    bool checkTimingPointSV(QString timingPointSV);
    bool checkTimingPointBPM(QString timingPointBPM);

private slots:

    void on_stutter_initSVSlider_valueChanged(int value);
    void on_stutter_initSVSpinBox_valueChanged(double arg1);
    void on_stutter_thresholdSlider_valueChanged(int value);
    void on_stutter_thresholdSpinBox_valueChanged(double arg1);
    void on_stutter_averageSVSpinBox_valueChanged(double arg1);
    void on_stutter_generateButton_clicked();
    void on_copier_generateButton_clicked();
    void on_TPF_generateButton_clicked();
    void on_TPF_initialTPSpinBox_valueChanged(double arg1);
    void on_TPF_initialTPSlider_valueChanged(int value);
    void on_TPF_endTPSpinBox_valueChanged(double arg1);
    void on_TPF_endTPSlider_valueChanged(int value);
    void on_TPF_offsetSlider_valueChanged(int value);
    void on_TPF_offsetSpinBox_valueChanged(int arg1);
    void on_TPF_frequencySpinBox_valueChanged(int arg1);
    void on_TPF_frequencySlider_valueChanged(int value);
    void on_TPF_amplitudeSlider_valueChanged(int value);
    void on_TPF_amplitudeSpinBox_valueChanged(int arg1);
    void on_TPF_defaultButton_clicked();
    void on_TPF_initialTPSlider_sliderReleased();
    void on_TPF_endTPSlider_sliderReleased();
    void on_TPF_amplitudeSlider_sliderReleased();
    void on_TPF_offsetSlider_sliderReleased();
    void on_TPF_frequencySlider_sliderReleased();
    void on_TPF_intermediateSpinBox_valueChanged(int arg1);
    void on_TPF_SVRadio_clicked();
    void on_TPF_BPMRadio_clicked();

    void on_normalizer_generateButton_clicked();
    void on_normalizer_BPMListWidget_itemPressed(QListWidgetItem *item);

    void on_basicWidgetList_itemClicked(QListWidgetItem *item);

    void on_settingsWidgetList_itemClicked(QListWidgetItem *item);

    void on_toolBox_currentChanged(int index);

    void on_advancedWidgetList_itemClicked(QListWidgetItem *item);


    void on_default_savePreferencesButton_clicked();

private:
    Ui::amber *ui;
};

#endif // AMBER_H
