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
    void on_tpf_generate_clicked();
    void on_tpf_phase_valueChanged(int value);
    void on_tpf_power_valueChanged(int value);

    void on_normalizer_generate_clicked();
    void on_normalizer_bpmlist_itemClicked(QListWidgetItem *item);

    void on_stutter_initsv_vs_valueChanged(int value);
    void on_stutter_threshold_vs_valueChanged(int value);
    void on_stutter_generate_clicked();
    void on_stutter_initbpm_vs_valueChanged(int value);
    void on_stutter_avebpm_valueChanged(double);
    void on_stutter_avesv_valueChanged(double);
    void on_stutter_1ms_front_clicked();

private:

    void stutter_limit_update();
    void tpf_init_customplot();
    void tpf_update_customplot(std::vector<double> offset_v, std::vector<double> value_v, bool is_bpm);

    // Squeezes the value to the defined MIN and MAX limits below and returns it
    double curb_value(double value, bool is_bpm);
    std::vector<double> curb_value_v(std::vector<double> value_v, bool is_bpm);

    Ui::MainWindow *ui;

    // Define "global" variables
    double SV_MIN = 0.1;
    double SV_MAX = 10.0;
    double BPM_MIN = 0.1;
    double BPM_MAX = 10000000; // 10,000,000

    long double MATH_PI = 3.14159265358979323846l;

    // This value is to convert vertical slider values to val
    double VS_TO_VAL = 100.0;
};

#endif // MAINWINDOW_H
