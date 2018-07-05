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

// Must be defined first
#include "amber_base_inc.h"
#include "statusbox.h"
#include "hyperlink.h"

namespace Ui {
class amber;
}

class amber : public QMainWindow
{
    Q_OBJECT

public:

    explicit amber(QWidget *parent = 0);
    ~amber();

    // SET DEFAULT
    void saveDefaultValues();

    // DEBUG MESSENGER
    void ERROR_MESSAGE(int ERROR_CODE);
    void PARAMETER_MESSAGE(QMap<QString, QVariant> PARAMETER_VALUE_LIST);

public slots:

private slots:

    // STUTTER
    void on_stutter_thresholdSlider_valueChanged(int value);
    void on_stutter_averageSVSpinBox_valueChanged(double arg1);
    void on_stutter_generateButton_clicked();
    void on_stutter_initSVSlider_valueChanged(int value);

    // COPIER
    void on_copier_generateButton_clicked();

    // TWO POINT FUNCTION
    void on_TPF_generateButton_clicked();
    void on_TPF_initialTPSlider_valueChanged(int value);
    void on_TPF_endTPSlider_valueChanged(int value);
    void on_TPF_offsetSlider_valueChanged(int value);
    void on_TPF_frequencySlider_valueChanged(int value);
    void on_TPF_amplitudeSlider_valueChanged(int value);
    void on_TPF_defaultButton_clicked();
    void on_TPF_intermediateSpinBox_valueChanged(int arg1);
    void on_TPF_SVRadio_clicked();
    void on_TPF_BPMRadio_clicked();

    // NORMALIZER
    void on_normalizer_generateButton_clicked();
    void on_normalizer_BPMListWidget_itemPressed(QListWidgetItem *item);

    // TOOLBAR
    void on_basicWidgetList_itemClicked(QListWidgetItem *item);
//    void on_settingsWidgetList_itemClicked(QListWidgetItem *item);
//    void on_advancedWidgetList_itemClicked(QListWidgetItem *item);
//    void on_default_savePreferencesButton_clicked();

    // HOME
    void on_home_githubIconLabel_clicked();
    void on_home_wikiLabel_clicked();
    void on_home_releasesLabel_clicked();
    void on_home_contactLabel_clicked();

    // ADJUSTER
    void on_adjuster_generateButton_clicked();
    void on_adjuster_multiplySpinBox_editingFinished();
    void on_adjuster_zeroSpinBox_editingFinished();
    void on_adjuster_offsetSpinBox_editingFinished();
    void on_adjuster_addSpinBox_editingFinished();
    void on_adjuster_autoZeroCheck_stateChanged(int arg1);
    void on_adjuster_adjustSVRadio_clicked();
    void on_adjuster_adjustBPMRadio_clicked();
    void on_adjuster_defaultButton_clicked();

    // PACK SPLITTER
//    void on_PS_browseButton_clicked();
//    void on_PS_mapListListWidget_itemClicked(QListWidgetItem *item);
//    void on_PS_controlSplitButton_clicked();
//    void on_PS_controlOpenFolderButton_clicked();

private:
    QTextBrowser *tb;
    Ui::amber *ui;
};



#endif // AMBER_H
