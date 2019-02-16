#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>

#include <custom_lib_functions/lib_functions.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tpf_init_customplot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_copier_generate_clicked()
{
    // We need the tp_v and ho_v for copier
    // However, we don't actually need correct keys for hit_object

    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->copier_tp->toPlainText().toStdString());

    // We default keys to 0
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->copier_ho->toPlainText().toStdString());

    // We only need the offset_v of ho_v to copy
    ui->copier_output->setPlainText(
                QString::fromStdString(
                    lib_functions::create_copies(&tp_v, ho_v.get_offset_v(true),true,true)->get_string_raw("\n"))
                );
}

void MainWindow::on_normalizer_generate_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->normalizer_input->toPlainText().toStdString(), '\n');

    // Break if empty
    if (tp_v.size() == 0){
        return;
    }

    // Remove Items
    ui->normalizer_bpmlist->clear();

    // Extract BPMs out of the vector only
    auto bpm_tp_v = tp_v.get_bpm_only();
    QStringList bpm_tp_v_str;

    for (auto bpm_tp : bpm_tp_v) {
        bpm_tp_v_str.append(QString::number(bpm_tp.get_value()));
    }

    // Add Items
    ui->normalizer_bpmlist->addItems(bpm_tp_v_str);

    ui->normalizer_output->setPlainText(
                QString::fromStdString(
                    lib_functions::create_normalize(tp_v, ui->normalizer_bpm->value(), false).get_string_raw()
                    )
                );
}
void MainWindow::on_normalizer_bpmlist_itemClicked(QListWidgetItem *item)
{
    ui->normalizer_bpm->setValue(item->text().toDouble());
}

void MainWindow::on_stutter_initsv_vs_valueChanged(int value)
{
    ui->stutter_initsv_val->setText(QString::number(value/VS_TO_VAL));
}
void MainWindow::on_stutter_initbpm_vs_valueChanged(int value)
{
    ui->stutter_initbpm_val->setText(QString::number(value/VS_TO_VAL));
}
void MainWindow::on_stutter_threshold_vs_valueChanged(int value)
{
    ui->stutter_threshold_val->setText(QString::number(value/VS_TO_VAL));
    stutter_limit_update();
}
void MainWindow::on_stutter_generate_clicked()
{
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->stutter_input->toPlainText().toStdString());

    // Break if empty
    if (ho_v.size() == 0){
        return;
    }

    timing_point_v tp_v;

    // Depends on which radio is checked, we generate a different output
    if (ui->stutter_type_sv->isChecked()){
        tp_v = lib_functions::create_stutter_relative(
                    ho_v.get_offset_v(true),
                    ui->stutter_initsv_val->text().toDouble(),
                    ui->stutter_threshold_val->text().toDouble(),
                    ui->stutter_avesv->value(),
                    false, true);

    } else if (ui->stutter_type_bpm->isChecked()) {
        tp_v = lib_functions::create_stutter_relative(
                    ho_v.get_offset_v(true),
                    ui->stutter_initbpm_val->text().toDouble(),
                    ui->stutter_threshold_val->text().toDouble(),
                    ui->stutter_avebpm->value(),
                    true, true);
    }

    ui->stutter_output->setPlainText(
                QString::fromStdString(tp_v.get_string_raw("\n")));
}
void MainWindow::on_stutter_preset_nft_clicked()
{
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->stutter_input->toPlainText().toStdString());

    // Break if empty
    if (ho_v.size() == 0){
        return;
    }

    timing_point_v tp_v = lib_functions::create_stutter_absolute(
                ho_v.get_offset_v(true),BPM_MIN,BPM_MIN,ui->stutter_avebpm->value(), true, false, true);

    tp_v = lib_functions::stutter_swap(tp_v);

    ui->stutter_output->setPlainText(
                QString::fromStdString(tp_v.get_string_raw("\n")));
}
void MainWindow::on_stutter_preset_nbt_clicked()
{
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->stutter_input->toPlainText().toStdString());

    // Break if empty
    if (ho_v.size() == 0){
        return;
    }

    timing_point_v tp_v = lib_functions::create_stutter_absolute(
                ho_v.get_offset_v(true),BPM_MIN,BPM_MIN,ui->stutter_avebpm->value(), true, false, true);

    ui->stutter_output->setPlainText(
                QString::fromStdString(tp_v.get_string_raw("\n")));
}
void MainWindow::on_stutter_preset_mft_clicked()
{
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->stutter_input->toPlainText().toStdString());

    // Break if empty
    if (ho_v.size() == 0){
        return;
    }

    timing_point_v tp_v;
    timing_point tp_teleport;
    timing_point tp_normalized;

    tp_teleport.set_value(BPM_MAX);
    tp_normalized.set_value(ui->stutter_avebpm->value());

    tp_teleport.set_offset(0);
    tp_normalized.set_offset(1);

    tp_teleport.set_is_bpm(true);
    tp_normalized.set_is_bpm(true);

    tp_v.push_back(tp_teleport);
    tp_v.push_back(tp_normalized);

    ui->stutter_output->setPlainText(
                QString::fromStdString(lib_functions::create_copies(&tp_v, ho_v.get_offset_v(true), true, true)->get_string_raw("\n")));
}
void MainWindow::on_stutter_preset_mbt_clicked()
{
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->stutter_input->toPlainText().toStdString());

    // Break if empty
    if (ho_v.size() == 0){
        return;
    }

    // move back by 1ms
    for (auto& ho : ho_v){
        ho.set_offset(ho.get_offset()-1);
    }

    timing_point_v tp_v;
    timing_point tp_teleport;
    timing_point tp_normalized;

    tp_teleport.set_value(BPM_MAX);
    tp_normalized.set_value(ui->stutter_avebpm->value());

    tp_teleport.set_offset(0);
    tp_normalized.set_offset(1);

    tp_teleport.set_is_bpm(true);
    tp_normalized.set_is_bpm(true);

    tp_v.push_back(tp_teleport);
    tp_v.push_back(tp_normalized);

    ui->stutter_output->setPlainText(
                QString::fromStdString(lib_functions::create_copies(&tp_v, ho_v.get_offset_v(true), true, true)->get_string_raw("\n")));
}

void MainWindow::on_stutter_avebpm_valueChanged(double)
{
    stutter_limit_update();
}
void MainWindow::on_stutter_avesv_valueChanged(double)
{
    stutter_limit_update();
}
void MainWindow::stutter_limit_update()
{
    if (ui->stutter_type_sv->isChecked()){
        // We limit the initial SV values
        std::vector<double> init_lim = lib_functions::get_stutter_rel_init_limits(
                    ui->stutter_threshold_val->text().toDouble(),
                    ui->stutter_avesv->text().toDouble(), SV_MIN, SV_MAX);

        // If the lower limit is lower than SV_MIN we curb the setMinimum
        if (init_lim[0] >= SV_MIN) {
            ui->stutter_initsv_vs->setMinimum(int(init_lim[0] * VS_TO_VAL));
        } else {
            ui->stutter_initsv_vs->setMinimum(int(SV_MIN * VS_TO_VAL));
        }

        // If the upper limit is higher than SV_MAX we curb the setMaximum
        if (init_lim[1] <= SV_MAX) {
            ui->stutter_initsv_vs->setMaximum(int(init_lim[1] * VS_TO_VAL));
        } else {
            ui->stutter_initsv_vs->setMaximum(int(SV_MAX * VS_TO_VAL));
        }
    } else if (ui->stutter_type_bpm->isChecked()) {
        // We limit the initial BPM values
        std::vector<double> init_lim = lib_functions::get_stutter_rel_init_limits(
                    ui->stutter_threshold_val->text().toDouble(),
                    ui->stutter_avebpm->text().toDouble(), BPM_MIN, BPM_MAX);

        // If the lower limit is higher than BPM_MIN we curb the setMinimum
        if (init_lim[0] >= BPM_MIN) {
            ui->stutter_initbpm_vs->setMinimum(int(init_lim[0] * VS_TO_VAL));
        } else {
            ui->stutter_initbpm_vs->setMinimum(int(BPM_MIN * VS_TO_VAL));
        }

        // If the upper limit is lower than BPM_MAX we curb the setMaximum
        if (init_lim[1] <= BPM_MAX) {
            ui->stutter_initbpm_vs->setMaximum(int(init_lim[1] * VS_TO_VAL));
        } else {
            ui->stutter_initbpm_vs->setMaximum(int(BPM_MAX * VS_TO_VAL));
        }
    }
}

void MainWindow::on_tpf_initsv_valueChanged(int value)
{
    ui->tpf_initsv_val->setText(QString::number(value/VS_TO_VAL));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_endsv_valueChanged(int value)
{
    ui->tpf_endsv_val->setText(QString::number(value/VS_TO_VAL));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_freq_valueChanged(int value)
{
    ui->tpf_freq_val->setText(QString::number(value/2.0));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_ampl_valueChanged(int value)
{
    if (ui->tpf_type_bpm->isChecked()) {
        // BPM amplitude will only scale [-1 ~ 1]
        ui->tpf_ampl_val->setText(QString::number(value/(VS_TO_VAL * 10)));
    } else {
        ui->tpf_ampl_val->setText(QString::number(value/VS_TO_VAL));
    }

    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_phase_valueChanged(int value)
{
    ui->tpf_phase_val->setText(QString::number(value));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_power_valueChanged(int value)
{
    ui->tpf_power_val->setText(QString::number(value/10.0));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_generate_clicked()
{
    hit_object_v ho_v;
    ho_v.load_editor_hit_object(ui->tpf_input->text().toStdString(), 0);
    std::vector<double> offset_v = ho_v.get_offset_v(true);

    if (offset_v.size() < 2){
        return; // Needs to be at least 2
    }
    if ((offset_v[1] - offset_v[0]) <= 0.0){
        return; // Needs to be > 0
    }

    bool is_bpm = ui->tpf_type_bpm->isChecked();

    // Extract all values from TPF
    double inittp = is_bpm ? ui->tpf_initbpm->value() : ui->tpf_initsv_val->text().toDouble();
    double endtp = is_bpm ? ui->tpf_endbpm->value() :ui->tpf_endsv_val->text().toDouble();
    double ampl = ui->tpf_ampl_val->text().toDouble();
    double freq = ui->tpf_freq_val->text().toDouble();
    double phase = ui->tpf_phase_val->text().toDouble();
    double power = ui->tpf_power_val->text().toDouble();
    double interpts = ui->tpf_interpts->value();

    bool curve_sine = ui->tpf_curve_type->currentText() == "sine";
    bool curve_power = ui->tpf_curve_type->currentText() == "power";

    bool curve_invert_y = ui->tpf_curve_invert_y->isChecked();

    bool output_curb = ui->tpf_output_curb->isChecked();

    // Adjust offset
    double offset_adjust = ui->tpf_offset_val->value();
    offset_v[0] += offset_adjust;
    offset_v[1] += offset_adjust;

    // Calculate all offsets with interpts
    double offset_difference = offset_v[1] - offset_v[0];
    double interpts_gap = offset_difference / (interpts + 1);

    for (int x = 1; x <= interpts; x ++) {
        double offset_append;
        offset_append = x * interpts_gap + offset_v[0];
        offset_v.push_back(offset_append);
    }

    // The function should be
    // f(offset) =
    // <PRIMARY>   <LINEAR> (mx + c) + ampl *
    // <SECONDARY> <SINE>   sin[(x * 2 * PI + phs) * freq]
    // <SECONDARY> <POWER>  x^pwr
    auto tpf_function = [&](double progress) -> double {
        double primary = 0;
        double gradient = (endtp - inittp);
        primary = (progress * gradient + inittp);
        double secondary = 0;
        if (curve_sine) {
            secondary = ampl * sin(((progress + (phase/360.0)) * double(MATH_PI) * 2) * freq) ;
        } else if (curve_power) {
            secondary = pow(progress * ampl, power);
        }

        // This is so that the curve scales relative to the average linear BPM
        if (is_bpm) {
            secondary *= ((endtp + inittp) / 2);
        }

        // Curb values if needed
        if (output_curb) {
            return curb_value(curve_invert_y ? (primary - secondary) : (primary + secondary), is_bpm);
        } else {
            return curve_invert_y ? (primary - secondary) : (primary + secondary);
        }
    };

    // Create all the timing points
    timing_point_v tp_v;

    for (double offset : offset_v) {
        timing_point tp;
        double progress = (offset - offset_v[0])/offset_difference;
        tp.load_parameters(offset, tpf_function(progress), ui->tpf_type_bpm->isChecked(), false, 4);
        tp_v.push_back(tp);
    }

    // Sort by offset
    tp_v.sort_by_offset(true);

    // Call update on the plot
    tpf_update_customplot(tp_v.get_offset_v(), tp_v.get_value_v(), is_bpm);

    // Update Average SV
    ui->tpf_output_ave->setText(is_bpm ?
                                QString::number(tp_v.get_average_bpm_value()) :
                                QString::number(tp_v.get_average_sv_value()));

    ui->tpf_output->setPlainText(QString::fromStdString(tp_v.get_string_raw()));
}

void MainWindow::tpf_init_customplot()
{
    auto customplot = ui->tpf_customplot;
    customplot->addGraph();

    customplot->xAxis->setLabel("offset");
    customplot->yAxis->setLabel("value");

    customplot->replot();
}
void MainWindow::tpf_update_customplot(std::vector<double> offset_v, std::vector<double> value_v, bool is_bpm)
{
    QVector<double> q_offset_v = QVector<double>::fromStdVector(offset_v);
    QVector<double> q_value_v = QVector<double>::fromStdVector(value_v);

    auto customplot = ui->tpf_customplot;
    customplot->graph(0)->setData(q_offset_v,q_value_v);

    // We'll have different curbing for BPM and SV
    double value_rng_min;
    double value_rng_max;

    if (is_bpm) {
        value_rng_min = *std::min_element(value_v.begin(), value_v.end());
        value_rng_max = *std::max_element(value_v.begin(), value_v.end());
    } else {
        value_rng_min = SV_MIN;
        value_rng_max = SV_MAX;
    }

    customplot->xAxis->setRange(*std::min_element(offset_v.begin(), offset_v.end()), *std::max_element(offset_v.begin(), offset_v.end()));
    customplot->yAxis->setRange(SV_MIN, SV_MAX);

    customplot->replot();
}

void MainWindow::on_alter_self_mv_b_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    tp_v *= ui->alter_self_mv->value();
    ui->alter_output->setPlainText(QString::fromStdString(tp_v.get_string_raw("\n")));
}
void MainWindow::on_alter_self_av_b_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    tp_v += ui->alter_self_mv->value();
    ui->alter_output->setPlainText(QString::fromStdString(tp_v.get_string_raw("\n")));
}
void MainWindow::on_alter_self_mo_b_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    tp_v.offset_arithmetic(ui->alter_self_mo->value(), [](double offset, double parameter){
        return offset * parameter;
    });
    ui->alter_output->setPlainText(QString::fromStdString(tp_v.get_string_raw("\n")));
}
void MainWindow::on_alter_self_ao_b_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    tp_v.offset_arithmetic(ui->alter_self_ao->value(), [](double offset, double parameter){
        return offset + parameter;
    });
    ui->alter_output->setPlainText(QString::fromStdString(tp_v.get_string_raw("\n")));
}
void MainWindow::on_alter_self_del_b_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    lib_functions::delete_nth(&tp_v, ui->alter_self_del->value(), ui->alter_self_del_offset->value());
    ui->alter_output->setPlainText(QString::fromStdString(tp_v.get_string_raw("\n")));
}

double MainWindow::curb_value(double value, bool is_bpm)
{
    if (is_bpm) {
        value = value > BPM_MAX ? BPM_MAX : value;
        value = value < BPM_MIN ? BPM_MIN : value;
    } else {
        value = value > SV_MAX ? SV_MAX : value;
        value = value < SV_MIN ? SV_MIN : value;
    }

    return value;
}
std::vector<double> MainWindow::curb_value_v(std::vector<double> value_v, bool is_bpm)
{
    std::vector<double> output;
    for (double value : value_v) {
        output.push_back(curb_value(value, is_bpm));
    }
    return output;
}

void MainWindow::on_alter_convert_to_bpm_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    timing_point_v tp_v_sv = tp_v.get_sv_only();
    timing_point_v tp_v_bpm = tp_v.get_bpm_only();

    double value;
    double reference = ui->alter_convert_ref->value();

    for (timing_point tp_sv : tp_v_sv){
        value = tp_sv.get_value();
        tp_sv.set_value(value * reference);
        tp_sv.set_is_bpm(true);
        tp_v_bpm.push_back(tp_sv);
    }

    tp_v_bpm.sort_by_offset(true);

    ui->alter_output->setPlainText(QString::fromStdString(tp_v_bpm.get_string_raw("\n")));
}

void MainWindow::on_alter_convert_to_sv_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    timing_point_v tp_v_sv = tp_v.get_sv_only();
    timing_point_v tp_v_bpm = tp_v.get_bpm_only();

    double value;
    double reference = ui->alter_convert_ref->value();

    for (timing_point tp_bpm : tp_v_bpm){
        value = tp_bpm.get_value();
        tp_bpm.set_value(value / reference);
        tp_bpm.set_is_sv(true);
        tp_v_sv.push_back(tp_bpm);
    }

    tp_v_sv.sort_by_offset(true);

    ui->alter_output->setPlainText(QString::fromStdString(tp_v_sv.get_string_raw("\n")));
}

void MainWindow::on_alter_cross_mv_b_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    timing_point_v tp_v_cross;
    tp_v_cross.load_raw_timing_point(ui->alter_input_cross->toPlainText().toStdString(), '\n');
    tp_v.cross_effect_multiply(tp_v_cross);
    ui->alter_output->setPlainText(QString::fromStdString(tp_v.get_string_raw("\n")));
}

void MainWindow::on_alter_cross_av_b_clicked()
{
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(ui->alter_input->toPlainText().toStdString(), '\n');
    timing_point_v tp_v_cross;
    tp_v_cross.load_raw_timing_point(ui->alter_input_cross->toPlainText().toStdString(), '\n');
    tp_v.cross_effect_add(tp_v_cross);
    ui->alter_output->setPlainText(QString::fromStdString(tp_v.get_string_raw("\n")));
}
