#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

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



    void on_tpf_initsv_valueChanged(int value);

    void on_tpf_endsv_valueChanged(int value);

    void on_tpf_freq_valueChanged(int value);

    void on_tpf_ampl_valueChanged(int value);

    void on_normalizer_generate_clicked();

    void on_normalizer_bpmlist_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
