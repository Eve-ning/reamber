#ifndef STUTTER_H
#define STUTTER_H

#include <QWidget>
#include "common.h"

namespace Ui {
class Stutter;
}

class Stutter : public QWidget, public Common
{
    Q_OBJECT

public:
    explicit Stutter(QWidget *parent = nullptr);
    ~Stutter();
    // Updates stutter tab's threshold limit while changing parameters
    void stutterLimitUpdate();
    QString output() const;

signals:
    void outputChanged();

private slots:

    void on_initSvVs_valueChanged(int value);
    void on_thresholdSlider_valueChanged(int value);
    void on_generateButton_clicked();
    void on_initBpmSlider_valueChanged(int value);
    void on_aveBpm_valueChanged(double);
    void on_aveSv_valueChanged(double);
    void on_NormFrontTelButton_clicked();
    void on_MaxFronTelButton_clicked();
    void on_NormBackTelButton_clicked();
    void on_MaxBackTelButton_clicked();


    void on_output_textChanged();

private:

    Ui::Stutter *ui;
};

#endif // STUTTER_H
