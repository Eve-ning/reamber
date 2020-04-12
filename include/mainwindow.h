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

    void on_home_repo_clicked();
    void on_home_wiki_clicked();
    void on_home_report_clicked();
    void on_home_releases_clicked();
    void on_listWidget_currentRowChanged(int currentRow);

    // Trigger Clipboard
    void alterClipboardCopy();
    void copierClipboardCopy();
    void normalizerClipboardCopy();
    void stutterClipboardCopy();
    void tpfClipboardCopy();

private:

    QClipboard *clipboard;
    void clipboard_copy(QString str);
    Ui::MainWindow *ui;
};

// TODO: Shorten ind. class names
