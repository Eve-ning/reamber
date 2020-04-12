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
    void stutter_limit_update();
    QString output() const;

signals:
    void outputChanged();

private slots:

    void on_stutter_initsv_vs_valueChanged(int value);
    void on_stutter_threshold_vs_valueChanged(int value);
    void on_stutter_generate_clicked();
    void on_stutter_initbpm_vs_valueChanged(int value);
    void on_stutter_avebpm_valueChanged(double);
    void on_stutter_avesv_valueChanged(double);
    void on_stutter_preset_nft_clicked();
    void on_stutter_preset_mft_clicked();
    void on_stutter_preset_nbt_clicked();
    void on_stutter_preset_mbt_clicked();


    void on_stutter_output_textChanged();

private:

    Ui::Stutter *ui;
};

#endif // STUTTER_H
