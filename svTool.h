#ifndef SVTOOL_H
#define SVTOOL_H

#include <QMainWindow>
#include <QStringList>
#include <QString>


namespace Ui {
class svTool;
}

class svTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit svTool(QWidget *parent = 0);
    ~svTool();

private slots:

    void on_home_validateButton_clicked();

    void on_stutter_initSVSlider_valueChanged(int value);

    void on_stutter_initSVSpinBox_valueChanged(double arg1);

    void on_stutter_thresholdSlider_valueChanged(int value);

    void on_stutter_thresholdSpinBox_valueChanged(double arg1);

    void on_stutter_averageSVSpinBox_valueChanged(double arg1);

    void on_stutter_generateButton_clicked();

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
