#ifndef AMBER_H
#define AMBER_H

#define STATMSG(text) STATUSBOX::sendMsg(tb, text, __FUNCTION__)

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
#include <QDesktopServices>
#include <QFileDialog>

//ust be defined first
#include "statusbox.h"

#include "check.h"
#include "compile.h"
#include "convert.h"
#include "hyperlink.h"

#include "amber_base_inc.h"

namespace Ui {
class amber;
}

class amber : public QMainWindow
{
    Q_OBJECT

public:

    explicit amber(QWidget *parent = 0);
    ~amber();

    //ET DEFAULT
    void saveDefaultValues();

    //EBUG MESSENGER
    void ERROR_MESSAGE(int ERROR_CODE);
    void PARAMETER_MESSAGE(QMap<QString, QVariant> PARAMETER_VALUE_LIST);

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

    void on_home_githubIconLabel_clicked();

    void on_adjuster_generateButton_clicked();
    void on_adjuster_multiplySpinBox_editingFinished();
    void on_adjuster_zeroSpinBox_editingFinished();
    void on_adjuster_offsetSpinBox_editingFinished();
    void on_adjuster_addSpinBox_editingFinished();
    void on_adjuster_autoZeroCheck_stateChanged(int arg1);
    void on_adjuster_adjustSVRadio_clicked();
    void on_adjuster_adjustBPMRadio_clicked();

    void on_adjuster_defaultButton_clicked();

    void on_PS_browseButton_clicked();
    void on_PS_mapListListWidget_itemClicked(QListWidgetItem *item);
    void on_PS_controlSplitButton_clicked();
    void on_PS_controlOpenFolderButton_clicked();

    void on_home_wikiLabel_clicked();

    void on_home_releasesLabel_clicked();

    void on_home_contactLabel_clicked();

private:
    QTextBrowser *tb;
    Ui::amber *ui;
};



#endif // AMBER_H
