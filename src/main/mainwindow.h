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
    void on_stutter_preset_nft_clicked();
    void on_stutter_preset_mft_clicked();
    void on_stutter_preset_nbt_clicked();
    void on_stutter_preset_mbt_clicked();

    void on_alter_self_mv_b_clicked();
    void on_alter_self_av_b_clicked();
    void on_alter_self_mo_b_clicked();
    void on_alter_self_ao_b_clicked();
    void on_alter_self_del_b_clicked();
    void on_alter_convert_to_bpm_clicked();
    void on_alter_convert_to_sv_clicked();
    void on_alter_cross_mv_b_clicked();
    void on_alter_cross_av_b_clicked();

    void on_tpf_reset_clicked();

    void on_alter_self_subd_by_b_clicked();

    void on_alter_self_subd_to_b_clicked();

private:

    // Updates stutter tab's threshold limit while changing parameters
    void stutter_limit_update();

    // Initializes and updates tpf's graph respectively
    void tpf_init_customplot();
    void tpf_update_customplot(std::vector<double> offset_v, std::vector<double> value_v, bool is_bpm);

//    // Extracts alter's inputs and output. This is a separate function as it's called a lot.
//    timing_point_v alter_get_input();
//    timing_point_v alter_get_input_cross();
//    void alter_set_output(const timing_point_v *tp_v);

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
