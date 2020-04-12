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

    void on_tpf_initsv_valueChanged(int value);
    void on_tpf_endsv_valueChanged(int value);
    void on_tpf_freq_valueChanged(int value);
    void on_tpf_ampl_valueChanged(int value);
    void on_tpf_generate_clicked();
    void on_tpf_phase_valueChanged(int value);
    void on_tpf_power_valueChanged(int value);
    void on_tpf_reset_clicked();


    // Initializes and updates tpf's graph respectively
    void tpf_init_customplot();
    void tpf_update_customplot(std::vector<double> offset_v, std::vector<double> value_v, bool is_bpm);

    void on_tpf_output_textChanged();

private:
    Ui::TwoPointFunction *ui;
};

#endif // TWOPOINTFUNCTION_H
