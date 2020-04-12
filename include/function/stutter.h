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

    void on_initsv_vs_valueChanged(int value);
    void on_threshold_vs_valueChanged(int value);
    void on_generate_clicked();
    void on_initbpm_vs_valueChanged(int value);
    void on_avebpm_valueChanged(double);
    void on_avesv_valueChanged(double);
    void on_preset_nft_clicked();
    void on_preset_mft_clicked();
    void on_preset_nbt_clicked();
    void on_preset_mbt_clicked();


    void on_output_textChanged();

private:

    Ui::Stutter *ui;
};

#endif // STUTTER_H
