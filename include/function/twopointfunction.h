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

    void on_initSvSlider_valueChanged(int value);
    void on_endSvSlider_valueChanged(int value);
    void on_frequencySlider_valueChanged(int value);
    void on_amplitudeSlider_valueChanged(int value);
    void on_generateButton_clicked();
    void on_phaseSlider_valueChanged(int value);
    void on_powerSlider_valueChanged(int value);
    void on_resetButton_clicked();

    // Initializes and updates tpf's graph respectively
    void tpfInitCustomPlot();
    void tpfUpdateCustomPlot(QVector<double> offset_v, QVector<double> valueV, bool isBpm);

    void on_output_textChanged();

private:
    Ui::TwoPointFunction *ui;
};

#endif // TWOPOINTFUNCTION_H
