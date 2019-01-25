#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_copier_generate_clicked();

    void on_tpf_initsv_valueChangedD(double value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
