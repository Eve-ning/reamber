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

    void on_stutter_initsv_vs_valueChanged(int value);

    void on_stutter_threshold_vs_valueChanged(int value);

    void on_stutter_generate_clicked();

    void on_stutter_initbpm_vs_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    // Define "global" variables
    double SV_MIN = 0.1;
    double SV_MAX = 10.0;
    double BPM_MIN = 0.1;
    double BPM_MAX = 1000000; // 1,000,000

    // This value is to convert vertical slider values to val
    double VS_TO_VAL = 100.0;
};

#endif // MAINWINDOW_H
