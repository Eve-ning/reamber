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
