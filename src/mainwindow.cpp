#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "object/multiple/timingpointv.h"
#include "object/multiple/hitobjectv.h"
#include "algorithm/algorithm.h"
#include <QString>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Initializes clipboard copying
    clipboard = QApplication::clipboard();

    connect(ui->widget_alter,   SIGNAL(outputChanged()), this, SLOT(alterClipboardCopy()));
    connect(ui->widget_tpf,     SIGNAL(outputChanged()), this, SLOT(tpfClipboardCopy()));
    connect(ui->widget_norm,    SIGNAL(outputChanged()), this, SLOT(normalizerClipboardCopy()));
    connect(ui->widget_copier,  SIGNAL(outputChanged()), this, SLOT(copierClipboardCopy()));
    connect(ui->widget_stutter, SIGNAL(outputChanged()), this, SLOT(stutterClipboardCopy()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_home_repo_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber", QUrl::TolerantMode));
}
void MainWindow::on_home_wiki_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/wiki", QUrl::TolerantMode));
}
void MainWindow::on_home_report_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/issues/new", QUrl::TolerantMode));
}
void MainWindow::on_home_releases_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/releases", QUrl::TolerantMode));
}

void MainWindow::clipboard_copy(QString str) {
    if (ui->clipboard_copy->isChecked()) clipboard->setText(str);
}

void MainWindow::alterClipboardCopy(){
    clipboard_copy(ui->widget_alter->output());
}

void MainWindow::copierClipboardCopy(){
    clipboard_copy(ui->widget_copier->output());
}

void MainWindow::normalizerClipboardCopy(){
    clipboard_copy(ui->widget_norm->output());
}

void MainWindow::stutterClipboardCopy(){
    clipboard_copy(ui->widget_stutter->output());
}

void MainWindow::tpfClipboardCopy(){
    clipboard_copy(ui->widget_tpf->output());
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->stackedWidget->setCurrentIndex(currentRow);
}
