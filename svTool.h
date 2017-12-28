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

    void on_home_timingPointButton_clicked();

    void on_home_validateButton_clicked();

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
