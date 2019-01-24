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
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->copier_tp->toPlainText().toStdString());
    ui->copier_output->setPlainText(QString::fromStdString(tp_v.get_string_raw("\n")));
}
