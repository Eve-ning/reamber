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

    void on_homeRepo_clicked();
    void on_homeWiki_clicked();
    void on_homeReport_clicked();
    void on_homeReleases_clicked();
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
