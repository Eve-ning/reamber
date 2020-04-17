#ifndef TWOPOINTFUNCTION_H
#define TWOPOINTFUNCTION_H

#include <QWidget>
#include "common.h"

namespace Ui {
class TwoPointFunction;
}

class TwoPointFunction : public QWidget, public Common
{
    Q_OBJECT

public:
    explicit TwoPointFunction(QWidget *parent = nullptr);
    ~TwoPointFunction();
    QString output() const;

signals:
    void outputChanged();

private slots:

    void on_initSvLabel_valueChanged(int value);
    void on_endSvLabel_valueChanged(int value);
    void on_frequencyLabel_valueChanged(int value);
    void on_amplitudeSlider_valueChanged(int value);
    void on_generateButton_clicked();
    void on_phaseLabel_valueChanged(int value);
    void on_powerLabel_valueChanged(int value);
    void on_resetButton_clicked();

    // Initializes and updates tpf's graph respectively
    void tpfInitCustomPlot();
    void tpfUpdateCustomPlot(QVector<double> offset_v, QVector<double> valueV, bool isBpm);

    void on_output_textChanged();

private:
    Ui::TwoPointFunction *ui;
};

#endif // TWOPOINTFUNCTION_H
