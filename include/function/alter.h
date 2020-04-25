#ifndef ALTER_H
#define ALTER_H

#include <QWidget>
#include "common.h"

namespace Ui {
class Alter;
}

class Alter : public QWidget, public Common
{
    Q_OBJECT

public:
    explicit Alter(QWidget *parent = nullptr);
    ~Alter();
    QString output() const;

signals:
    void outputChanged();

private slots:

    void on_selfMVButton_clicked();
    void on_selfAVButton_clicked();
    void on_selfMOButton_clicked();
    void on_selfAOButton_clicked();
    void on_selfDeleteButton_clicked();
    void on_convertToBpm_clicked();
    void on_convertToSv_clicked();
    void on_crossMVButton_clicked();
    void on_crossAVButton_clicked();
    void on_selfSubdByButton_clicked();
    void on_selfSubdToButton_clicked();

    void on_output_textChanged();

private:
    void initToolTips();

    Ui::Alter *ui;
};

#endif // ALTER_H
