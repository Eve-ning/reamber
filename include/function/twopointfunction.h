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

    void on_initsv_valueChanged(int value);
    void on_endsv_valueChanged(int value);
    void on_freq_valueChanged(int value);
    void on_ampl_valueChanged(int value);
    void on_generate_clicked();
    void on_phase_valueChanged(int value);
    void on_power_valueChanged(int value);
    void on_reset_clicked();


    // Initializes and updates tpf's graph respectively
    void tpf_init_customplot();
    void tpf_update_customplot(std::vector<double> offset_v, std::vector<double> value_v, bool is_bpm);

    void on_output_textChanged();

private:
    Ui::TwoPointFunction *ui;
};

#endif // TWOPOINTFUNCTION_H
