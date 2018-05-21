#ifndef AAFORM_H
#define AAFORM_H

#include <QDialog>
#include <QDebug>
#include "amber.h"

namespace Ui {
class AAForm;
}

class AAForm : public QDialog
{
    Q_OBJECT

public:
    explicit AAForm(QWidget* parent = 0);
    ~AAForm();

    bool disableAll();
    bool enableAll();
    bool disableChkbx(int index = -1);
    bool enableChkbx(int index = -1);
    bool disableLine(int index = -1);
    bool enableLine(int index = -1);
    bool disablePTE(int index = -1);
    bool enablePTE(int index = -1);
    bool disableRadio(int index = -1);
    bool enableRadio(int index = -1);

    void setChkbxTitle(QString newTitle);
    bool setChkbxText(QString newText, int index);
    bool setLineTitle(QString newTitle, int index, QString hintText = "");
    bool setPTETitle(QString newTitle, int index, QString hintText = "");
    void setRadioTitle(QString newTitle);
    bool setRadioText(QString newText, int index);

    bool getChkbxState(int index);
    QString getLineText(int index); // Note that it returns a QString
    QString getPTEText(int index); // Note that it returns a QString
    bool getRadioState(int index);

    AAData getData();
    void setData(AAData &data);

    bool checkChkbx(int index = -1, bool check = true);
    bool checkRadio(int index, bool check = true);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AAForm *ui;
};

#endif // AAFORM_H
