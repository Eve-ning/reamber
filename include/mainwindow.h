#pragma once

#include <QMainWindow>
#include <QListWidget>
namespace Ui {
class MainWindow;
}

class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_homeRepoButton_clicked();
    void on_homeWikiButton_clicked();
    void on_homeReportButton_clicked();
    void on_homeReleasesButton_clicked();
    void on_listWidget_currentRowChanged(int currentRow);

    // Trigger Clipboard
    void alterClipboardCopy();
    void copierClipboardCopy();
    void normalizerClipboardCopy();
    void stutterClipboardCopy();
    void tpfClipboardCopy();

private:

    QClipboard *clipboard;
    void clipboardCopy(QString str);
    Ui::MainWindow *ui;
};

// TODO: Shorten ind. class names
