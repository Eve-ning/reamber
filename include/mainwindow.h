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

    // Links
    void on_homeRepoButton_clicked();
    void on_homeWikiButton_clicked();
    void on_homeReportButton_clicked();
    void on_homeReleasesButton_clicked();

    // Trigger Clipboard
    void alterClipboardCopy();
    void copierClipboardCopy();
    void normalizerClipboardCopy();
    void stutterClipboardCopy();
    void tpbClipboardCopy();

    // Action Buttons
    void on_actionHome_triggered();
    void on_actionAlter_triggered();
    void on_actionNormalizer_triggered();
    void on_actionTPB_triggered();
    void on_actionCopier_triggered();
    void on_actionStutter_triggered();

private:

    QClipboard *clipboard;
    void clipboardCopy(QString str);
    Ui::MainWindow *ui;
};

// TODO: Shorten ind. class names
