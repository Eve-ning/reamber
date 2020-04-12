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

    void on_alter_self_mv_b_clicked();
    void on_alter_self_av_b_clicked();
    void on_alter_self_mo_b_clicked();
    void on_alter_self_ao_b_clicked();
    void on_alter_self_del_b_clicked();
    void on_alter_convert_to_bpm_clicked();
    void on_alter_convert_to_sv_clicked();
    void on_alter_cross_mv_b_clicked();
    void on_alter_cross_av_b_clicked();
    void on_alter_self_subd_by_b_clicked();
    void on_alter_self_subd_to_b_clicked();

    void on_alter_output_textChanged();

private:
    Ui::Alter *ui;
};

#endif // ALTER_H
