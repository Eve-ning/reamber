#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <custom_lib_functions/lib_functions.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_copier_generate_clicked()
{
    // We need the tp_v and ho_v for copier
    // However, we don't actually need correct keys for hit_object

    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->copier_tp->toPlainText().toStdString());

    // We default keys to 0
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->copier_ho->toPlainText().toStdString());

    // We only need the offset_v of ho_v to copy
    ui->copier_output->setPlainText(
                QString::fromStdString(
                    lib_functions::create_copies(&tp_v, ho_v.get_offset_v(true),true,true)->get_string_raw("\n"))
                );
}

void MainWindow::on_tpf_initsv_valueChanged(int value)
{
    ui->tpf_initsv_val->setText(QString::number(value/100.0));
}

void MainWindow::on_tpf_endsv_valueChanged(int value)
{
    ui->tpf_endsv_val->setText(QString::number(value/100.0));
}

void MainWindow::on_tpf_freq_valueChanged(int value)
{
    ui->tpf_freq_val->setText(QString::number(value/100.0));
}

void MainWindow::on_tpf_ampl_valueChanged(int value)
{
    ui->tpf_ampl_val->setText(QString::number(value/100.0));
}

void MainWindow::on_normalizer_generate_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->normalizer_input->toPlainText().toStdString(), '\n');

    // Break if empty
    if (tp_v.size() == 0){
        return;
    }

    // Remove Items
    ui->normalizer_bpmlist->clear();

    // Extract BPMs out of the vector only
    auto bpm_tp_v = tp_v.get_bpm_only();
    QStringList bpm_tp_v_str;

    for (auto bpm_tp : bpm_tp_v) {
        bpm_tp_v_str.append(QString::number(bpm_tp.get_value()));
    }

    // Add Items
    ui->normalizer_bpmlist->addItems(bpm_tp_v_str);

    ui->normalizer_output->setPlainText(
                QString::fromStdString(
                    lib_functions::create_normalize(tp_v, ui->normalizer_bpm->value(), false).get_string_raw()
                    )
                );
}

// Automatically set the BPM value after selecting
void MainWindow::on_normalizer_bpmlist_itemClicked(QListWidgetItem *item)
{
    ui->normalizer_bpm->setValue(item->text().toDouble());
}

void MainWindow::on_stutter_initsv_vs_valueChanged(int value)
{
    ui->stutter_initsv_val->setText(QString::number(value/100.0));
}

void MainWindow::on_stutter_threshold_vs_valueChanged(int value)
{
    ui->stutter_threshold_val->setText(QString::number(value/100.0));

    // We would also like to limit the initial SV values
    std::vector<double> init_lim = lib_functions::create_basic_stutter_initial_sv_limits(
                value/100.0, ui->stutter_avesv->text().toDouble(), 0.1, 10.0);

    qDebug() << init_lim[0] << "<->" << init_lim[1];

    if (init_lim[0] >= 0.1) {
        ui->stutter_initsv_vs->setMinimum(int(init_lim[0] * 100.0));
    } else {
        ui->stutter_initsv_vs->setMinimum(10);
    }
    if (init_lim[1] <= 10.0) {
        ui->stutter_initsv_vs->setMaximum(int(init_lim[1] * 100.0));
    } else {
        ui->stutter_initsv_vs->setMaximum(1000);
    }
}

void MainWindow::on_stutter_generate_clicked()
{
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->stutter_input->toPlainText().toStdString());

    ui->stutter_output->setPlainText(
                QString::fromStdString(
                    lib_functions::create_basic_stutter(
                        ho_v.get_offset_v(true),
                        ui->stutter_initsv_val->text().toDouble(),
                        ui->stutter_threshold_val->text().toDouble(),
                        ui->stutter_avesv->value(),
                        false
                    ).get_string_raw("\n")
                    )
                );
}
