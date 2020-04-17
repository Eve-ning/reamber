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

    connect(ui->widgetAlter,   SIGNAL(outputChanged()), this, SLOT(alterClipboardCopy()));
    connect(ui->widgetTpf,     SIGNAL(outputChanged()), this, SLOT(tpfClipboardCopy()));
    connect(ui->widgetNorm,    SIGNAL(outputChanged()), this, SLOT(normalizerClipboardCopy()));
    connect(ui->widgetCopier,  SIGNAL(outputChanged()), this, SLOT(copierClipboardCopy()));
    connect(ui->widgetStutter, SIGNAL(outputChanged()), this, SLOT(stutterClipboardCopy()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_homeRepo_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber", QUrl::TolerantMode));
}
void MainWindow::on_homeWiki_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/wiki", QUrl::TolerantMode));
}
void MainWindow::on_homeReport_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/issues/new", QUrl::TolerantMode));
}
void MainWindow::on_homeReleases_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/releases", QUrl::TolerantMode));
}

void MainWindow::clipboardCopy(QString str) {
    if (ui->clipboardCopy->isChecked()) clipboard->setText(str);
}

void MainWindow::alterClipboardCopy(){
    clipboardCopy(ui->widgetAlter->output());
}
void MainWindow::copierClipboardCopy(){
    clipboardCopy(ui->widgetCopier->output());
}
void MainWindow::normalizerClipboardCopy(){
    clipboardCopy(ui->widgetNorm->output());
}
void MainWindow::stutterClipboardCopy(){
    clipboardCopy(ui->widgetStutter->output());
}
void MainWindow::tpfClipboardCopy(){
    clipboardCopy(ui->widgetTpf->output());
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow) {
    ui->stackedWidget->setCurrentIndex(currentRow);
}
