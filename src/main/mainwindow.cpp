#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithm/algorithm.h"
#include "object/multiple/timingpointv.h"
#include "object/multiple/hitobjectv.h"
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    stutter_limit_update();
    tpf_init_customplot();

    // Initializes clipboard copying
    clipboard = QApplication::clipboard();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_home_repo_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber", QUrl::TolerantMode));
}
void MainWindow::on_home_wiki_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/wiki", QUrl::TolerantMode));
}
void MainWindow::on_home_report_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/issues/new", QUrl::TolerantMode));
}
void MainWindow::on_home_releases_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Eve-ning/reamber/releases", QUrl::TolerantMode));
}

// ========================= COPIER =========================
void MainWindow::on_copier_generate_clicked() {
    // We need the tpV and hoV for copier
    // However, we don't actually need correct keys for hit_object
    TimingPointV tpV;

    // Break if fail
    if (!tpV.loadRaw(ui->copier_tp->toPlainText())) return;

    // We default keys to 0
    HitObjectV hoV;
    hoV.loadEditor(ui->copier_ho->toPlainText());

    // We only need the offsetV of hoV to copy
    ui->copier_output->setPlainText(
                algorithm::copy<TimingPoint>(
                    QSPtr<TimingPointV>::create(tpV),
                    hoV.getOffsetV(true),
                    true,
                    true).getStringRaw("\n"));
}


// ========================= NORMALIZER =========================
void MainWindow::on_normalizer_generate_clicked() {
    TimingPointV tpV;

    // Break if fail
    if (!tpV.loadRaw(ui->normalizer_input->toPlainText(), '\n')) return;

    // Break if empty
    if (tpV.getBpmOnly().size() == 0) return;

    // Remove Items
    ui->normalizer_bpmlist->clear();

    // Extract BPMs out of the vector only
    auto bpmTpV = tpV.getBpmOnly();
    QStringList bpmTpVStr;

    for (const auto& bpmTp : bpmTpV) bpmTpVStr.append(QString::number(bpmTp.getValue()));

    // Add Items
    ui->normalizer_bpmlist->addItems(bpmTpVStr);

    ui->normalizer_output->setPlainText(
                algorithm::normalize(tpV,
                                     ui->normalizer_bpm->value(),
                                     false).getStringRaw());
}
void MainWindow::on_normalizer_bpmlist_itemClicked(QListWidgetItem *item) {
    ui->normalizer_bpm->setValue(item->text().toDouble());
}

// ========================= STUTTER =========================

void MainWindow::on_stutter_initsv_vs_valueChanged(int value) {
    ui->stutter_initsv_val->setText(QString::number(value/VS_TO_VAL));
}
void MainWindow::on_stutter_initbpm_vs_valueChanged(int value) {
    ui->stutter_initbpm_val->setText(QString::number(value/VS_TO_VAL));
}
void MainWindow::on_stutter_threshold_vs_valueChanged(int value) {
    ui->stutter_threshold_val->setText(QString::number(value/VS_TO_VAL));
    stutter_limit_update();
}
void MainWindow::on_stutter_generate_clicked() {
    HitObjectV hoV;
    auto t = ui->stutter_input->toPlainText();
    // Break if fail
    if (!hoV.loadEditor(t)) return;

    // Break if empty
    if (hoV.size() == 0) return;

    TimingPointV tpV;

    // Depends on which radio is checked, we generate a different output
    if (ui->stutter_type_sv->isChecked())
        tpV = algorithm::stutterRel(
                    hoV.getOffsetV(true),
                    ui->stutter_initsv_val->text().toDouble(),
                    ui->stutter_threshold_val->text().toDouble(),
                    ui->stutter_avesv->value(),
                    false, true);
    else if (ui->stutter_type_bpm->isChecked())
        tpV = algorithm::stutterRel(
                    hoV.getOffsetV(true),
                    ui->stutter_initbpm_val->text().toDouble(),
                    ui->stutter_threshold_val->text().toDouble(),
                    ui->stutter_avebpm->value(),
                    true, true);


    ui->stutter_output->setPlainText(tpV.getStringRaw("\n"));

}
void MainWindow::on_stutter_preset_nft_clicked() {
    HitObjectV hoV;
    hoV.loadEditor(ui->stutter_input->toPlainText());

    // Break if empty
    if (hoV.size() == 0) return;

    TimingPointV tpV = algorithm::stutterAbs(
                hoV.getOffsetV(true),
                BPM_MIN,
                BPM_MIN,
                ui->stutter_avebpm->value(),
                true,
                false,
                true);

    tpV = algorithm::stutterSwap(tpV);

    ui->stutter_output->setPlainText(tpV.getStringRaw("\n"));
}
void MainWindow::on_stutter_preset_nbt_clicked() {
    HitObjectV hoV;
    hoV.loadEditor(ui->stutter_input->toPlainText());

    // Break if empty
    if (hoV.size() == 0) return;

    TimingPointV tpV = algorithm::stutterAbs(
                hoV.getOffsetV(true),BPM_MIN,BPM_MIN,ui->stutter_avebpm->value(), true, false, true);

    ui->stutter_output->setPlainText(tpV.getStringRaw("\n"));
}
void MainWindow::on_stutter_preset_mft_clicked() {
    HitObjectV hoV;
    hoV.loadEditor(ui->stutter_input->toPlainText());

    // Break if empty
    if (hoV.size() == 0) return;

    TimingPointV tpV;
    TimingPoint tpTeleport;
    TimingPoint tpNormalized;

    tpTeleport.setValue(BPM_MAX);
    tpNormalized.setValue(ui->stutter_avebpm->value());

    tpTeleport.setOffset(0);
    tpNormalized.setOffset(1);

    tpTeleport.setIsBpm(true);
    tpNormalized.setIsBpm(true);

    tpV.pushBack(tpTeleport);
    tpV.pushBack(tpNormalized);

    ui->stutter_output->setPlainText(
                algorithm::copy<TimingPoint>(
                    QSPtr<TimingPointV>::create(tpV),
                    hoV.getOffsetV(true),
                    true,
                    true).getStringRaw("\n"));
}
void MainWindow::on_stutter_preset_mbt_clicked() {
    HitObjectV hoV;
    hoV.loadEditor(ui->stutter_input->toPlainText());

    // Break if empty
    if (hoV.size() == 0) return;

    // move back by 1ms
    for (auto& ho : hoV) ho.setOffset(ho.getOffset()-1);

    TimingPointV tpV;
    TimingPoint tpTeleport;
    TimingPoint tpNormalized;

    tpTeleport.setValue(BPM_MAX);
    tpNormalized.setValue(ui->stutter_avebpm->value());

    tpTeleport.setOffset(0);
    tpNormalized.setOffset(1);

    tpTeleport.setIsBpm(true);
    tpNormalized.setIsBpm(true);

    tpV.pushBack(tpTeleport);
    tpV.pushBack(tpNormalized);

    ui->stutter_output->setPlainText(
                algorithm::copy<TimingPoint>(
                    QSPtr<TimingPointV>::create(tpV),
                    hoV.getOffsetV(true),
                    true, true).getStringRaw("\n"));
}
void MainWindow::on_stutter_avebpm_valueChanged(double) { stutter_limit_update(); }
void MainWindow::on_stutter_avesv_valueChanged(double) { stutter_limit_update(); }
void MainWindow::stutter_limit_update() {
    if (ui->stutter_type_sv->isChecked()){
        // We limit the initial SV values
        QVector<double> initLim = algorithm::stutterRelInitLimits(
                    ui->stutter_threshold_val->text().toDouble(),
                    ui->stutter_avesv->text().toDouble(), SV_MIN, SV_MAX);

        // If the lower limit is lower than SV_MIN we curb the setMinimum
        if (initLim[0] >= SV_MIN)
            ui->stutter_initsv_vs->setMinimum(int(initLim[0] * VS_TO_VAL));
        else
            ui->stutter_initsv_vs->setMinimum(int(SV_MIN * VS_TO_VAL));


        // If the upper limit is higher than SV_MAX we curb the setMaximum
        if (initLim[1] <= SV_MAX)
            ui->stutter_initsv_vs->setMaximum(int(initLim[1] * VS_TO_VAL));
        else
            ui->stutter_initsv_vs->setMaximum(int(SV_MAX * VS_TO_VAL));

    } else if (ui->stutter_type_bpm->isChecked()) {
        // We limit the initial BPM values
        QVector<double> initLim = algorithm::stutterRelInitLimits(
                    ui->stutter_threshold_val->text().toDouble(),
                    ui->stutter_avebpm->text().toDouble(), BPM_MIN, BPM_MAX);

        // If the lower limit is higher than BPM_MIN we curb the setMinimum
        if (initLim[0] >= BPM_MIN) {
            ui->stutter_initbpm_vs->setMinimum(int(initLim[0] * VS_TO_VAL));
        } else {
            ui->stutter_initbpm_vs->setMinimum(int(BPM_MIN * VS_TO_VAL));
        }

        // If the upper limit is lower than BPM_MAX we curb the setMaximum
        if (initLim[1] <= BPM_MAX) {
            ui->stutter_initbpm_vs->setMaximum(int(initLim[1] * VS_TO_VAL));
        } else {
            ui->stutter_initbpm_vs->setMaximum(int(BPM_MAX * VS_TO_VAL));
        }
    }
}


// ========================= 2PF =========================
void MainWindow::on_tpf_initsv_valueChanged(int value) {
    ui->tpf_initsv_val->setText(QString::number(value/VS_TO_VAL));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_endsv_valueChanged(int value) {
    ui->tpf_endsv_val->setText(QString::number(value/VS_TO_VAL));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_freq_valueChanged(int value) {
    ui->tpf_freq_val->setText(QString::number(value/2.0));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_ampl_valueChanged(int value) {
    if (ui->tpf_type_bpm->isChecked())
        // BPM amplitude will only scale [-1 ~ 1]
        ui->tpf_ampl_val->setText(QString::number(value/(VS_TO_VAL * 10)));
    else
        ui->tpf_ampl_val->setText(QString::number(value/VS_TO_VAL));


    if (ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_phase_valueChanged(int value) {
    ui->tpf_phase_val->setText(QString::number(value));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_power_valueChanged(int value) {
    ui->tpf_power_val->setText(QString::number(value/10.0));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void MainWindow::on_tpf_generate_clicked() {
    HitObjectV hoV;

    // Break if fail
    if (!hoV.loadEditor(ui->tpf_input->text(), 0)) return;

    QVector<double> offsetV = hoV.getOffsetV(true);

    if (offsetV.size() < 2) return; // Needs to be at least 2
    if ((offsetV[1] - offsetV[0]) <= 0.0) return; // Needs to be > 0

    bool isBpm = ui->tpf_type_bpm->isChecked();

    // Extract all values from TpF
    double initTp = isBpm ? ui->tpf_initbpm->value() : ui->tpf_initsv_val->text().toDouble();
    double endTp = isBpm ? ui->tpf_endbpm->value() :ui->tpf_endsv_val->text().toDouble();
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
    offsetV[0] += offset_adjust;
    offsetV[1] += offset_adjust;

    // Calculate all offsets with interpts
    double offset_difference = offsetV[1] - offsetV[0];
    double interpts_gap = offset_difference / (interpts + 1);

    for (int x = 1; x <= interpts; x ++) {
        double offset_append;
        offset_append = x * interpts_gap + offsetV[0];
        offsetV.push_back(offset_append);
    }

    // The function should be
    // f(offset) =
    // <PRIMARY>   <LINEAR> (mx + c) + ampl *
    // <SECONDARY> <SINE>   sin[(x * 2 * PI + phs) * freq]
    // <SECONDARY> <POWER>  x^pwr
    auto tpf_function = [&](double progress) -> double {
        double primary = 0;
        double gradient = (endTp - initTp);
        primary = (progress * gradient + initTp);
        double secondary = 0;
        if (curve_sine)  secondary = ampl * sin(((progress + (phase/360.0)) * double(MATH_PI) * 2) * freq);
        else if (curve_power) secondary = pow(progress * ampl, power);

        // This is so that the curve scales relative to the average linear BPM
        if (isBpm) secondary *= ((endTp + initTp) / 2);

        // Curb values if needed
        if (output_curb)  return clipValue(curve_invert_y ? (primary - secondary) : (primary + secondary), isBpm);

        return curve_invert_y ? (primary - secondary) : (primary + secondary);
    };

    // Create all the timing points
    TimingPointV tpV;

    for (double offset : offsetV) {
        TimingPoint tp;
        double progress = (offset - offsetV[0])/offset_difference;
        tp.loadParameters(offset, tpf_function(progress), ui->tpf_type_bpm->isChecked(), false, 4);
        tpV.pushBack(tp);
    }

    // Sort by offset
    tpV.sortByOffset(true);

    // Call update on the plot
    tpf_update_customplot(tpV.getOffsetV().toStdVector(),
                          tpV.getValueV().toStdVector(),
                          isBpm);

    // Update Average SV
    ui->tpf_output_ave->setText(isBpm ?
                                QString::number(tpV.getAverageBpmValue()) :
                                QString::number(tpV.getAverageSvValue()));

    ui->tpf_output->setPlainText(tpV.getStringRaw());
}
void MainWindow::on_tpf_reset_clicked() {
    ui->tpf_ampl->setValue(0);
    ui->tpf_freq->setValue(1);
    // freq slider on 1 sets to 0.5 for some reason, will manually set this to 0.5
    ui->tpf_freq_val->setText("1.0");

    ui->tpf_interpts->setValue(50);

    ui->tpf_phase->setValue(0);
    ui->tpf_power->setValue(10);

    ui->tpf_initsv->setValue(100);
    ui->tpf_endsv->setValue(100);

    ui->tpf_initbpm->setValue(120);
    ui->tpf_endbpm->setValue(120);

    ui->tpf_offset_val->setValue(0);

    ui->tpf_type_sv->setChecked(true);
    ui->tpf_type_bpm->setChecked(false);
    ui->tpf_curve_type->setCurrentIndex(0);
    ui->tpf_curve_invert_y->setChecked(false);
//    ui->tpf_output_curb->setChecked(true);
//    ui->tpf_output_live->setChecked(false);
}

void MainWindow::tpf_init_customplot() {
    auto customplot = ui->tpf_customplot;
    customplot->addGraph();

    customplot->xAxis->setLabel("offset");
    customplot->yAxis->setLabel("value");

    customplot->replot();
}
void MainWindow::tpf_update_customplot(std::vector<double> offsetV, std::vector<double> value_v, bool is_bpm) {
    QVector<double> q_offset_v = QVector<double>::fromStdVector(offsetV);
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

    customplot->xAxis->setRange(*std::min_element(offsetV.begin(), offsetV.end()),
                                *std::max_element(offsetV.begin(), offsetV.end()));
    customplot->yAxis->setRange(value_rng_min, value_rng_max);

    customplot->replot();
}


// ========================= ALTER =========================
void MainWindow::on_alter_self_mv_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n')) return;

    tpV *= ui->alter_self_mv->value();
    ui->alter_output->setPlainText(tpV.getStringRaw("\n"));
}
void MainWindow::on_alter_self_av_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n')) return;
    tpV += ui->alter_self_av->value();
    ui->alter_output->setPlainText(tpV.getStringRaw("\n"));
}
void MainWindow::on_alter_self_mo_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n')) return;

    auto newTpV = tpV.offsetArithmetic(ui->alter_self_mo->value(), [](double offset, double parameter){
        return offset * parameter;
    });

    ui->alter_output->setPlainText(newTpV.getStringRaw("\n"));
}
void MainWindow::on_alter_self_ao_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n')) return;

    auto newTpV = tpV.offsetArithmetic(
                ui->alter_self_ao->value(),
                [](double offset, double parameter){
        return offset + parameter;
    });
    ui->alter_output->setPlainText(newTpV.getStringRaw("\n"));
}
void MainWindow::on_alter_self_del_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n')) return;

    auto delTpV = algorithm::deleteNth<TimingPoint>(QSPtr<TimingPointV>::create(tpV),
                                         static_cast<unsigned int>(ui->alter_self_del->value()),
                                         static_cast<unsigned int>(ui->alter_self_del_offset->value()));
    ui->alter_output->setPlainText(delTpV.getStringRaw("\n"));
}
void MainWindow::on_alter_self_subd_by_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n'))  return;
    auto subdTpV =
            algorithm::copySubdBy<TimingPoint>(
                QSPtr<TimingPointV>::create(tpV),
                static_cast<unsigned int>(ui->alter_self_subd_by->value()), true);
    ui->alter_output->setPlainText(subdTpV.getStringRaw("\n"));
}
void MainWindow::on_alter_self_subd_to_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n')) return;
    auto subdTpV =
            algorithm::copySubdTo<TimingPoint>(
                QSPtr<TimingPointV>::create(tpV),
                static_cast<unsigned int>(ui->alter_self_subd_to->value()), true);
    ui->alter_output->setPlainText(subdTpV.getStringRaw("\n"));
}

void MainWindow::on_alter_convert_to_bpm_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n')) return;

    TimingPointV tpVSv = tpV.getSvOnly();
    TimingPointV tpVBpm = tpV.getBpmOnly();

    double value;
    double reference = ui->alter_convert_ref->value();

    for (TimingPoint tp_sv : tpVSv){
        value = tp_sv.getValue();
        tp_sv.setValue(value * reference);
        tp_sv.setIsBpm(true);
        tpVBpm.pushBack(tp_sv);
    }

    tpVBpm.sortByOffset(true);

    ui->alter_output->setPlainText(tpVBpm.getStringRaw("\n"));
}
void MainWindow::on_alter_convert_to_sv_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n')) return;

    TimingPointV tpVSv = tpV.getSvOnly();
    TimingPointV tpVBpm = tpV.getBpmOnly();

    double value;
    double reference = ui->alter_convert_ref->value();

    for (TimingPoint tpBpm : tpVBpm){
        value = tpBpm.getValue();
        tpBpm.setValue(value / reference);
        tpBpm.setIsSv(true);
        tpVSv.pushBack(tpBpm);
    }

    tpVSv.sortByOffset(true);

    ui->alter_output->setPlainText(tpVSv.getStringRaw("\n"));
}
void MainWindow::on_alter_cross_mv_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n'))  return;

    TimingPointV tp_v_cross;
    if (!tp_v_cross.loadRaw(ui->alter_input_cross->toPlainText(), '\n'))  return;

    tpV.crossEffectMultiply(tp_v_cross);
    ui->alter_output->setPlainText(tpV.getStringRaw("\n"));
}
void MainWindow::on_alter_cross_av_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->alter_input->toPlainText(), '\n'))  return;

    TimingPointV tp_v_cross;
    if (!tp_v_cross.loadRaw(ui->alter_input_cross->toPlainText(), '\n')) return;

    tpV.crossEffectAdd(tp_v_cross);
    ui->alter_output->setPlainText(tpV.getStringRaw("\n"));
}


// ========================= GENERIC =========================
double MainWindow::clipValue(double value, bool isBpm) {
    if (isBpm) {
        value = value > BPM_MAX ? BPM_MAX : value;
        value = value < BPM_MIN ? BPM_MIN : value;
    } else {
        value = value > SV_MAX ? SV_MAX : value;
        value = value < SV_MIN ? SV_MIN : value;
    }

    return value;
}
std::vector<double> MainWindow::clipValueV(std::vector<double> valueV, bool isBpm)
{
    std::vector<double> output;
    output.reserve(valueV.size());
    for (double value : valueV) output.push_back(clipValue(value, isBpm));
    return output;
}

void MainWindow::clipboard_copy(QString str) {
    if (ui->clipboard_copy->isChecked()) clipboard->setText(str);
}

// CLIPBOARD COPY
void MainWindow::on_alter_output_textChanged() {
    clipboard_copy(ui->alter_output->toPlainText());
}
void MainWindow::on_stutter_output_textChanged() {
    clipboard_copy(ui->stutter_output->toPlainText());
}
void MainWindow::on_copier_output_textChanged() {
    clipboard_copy(ui->copier_output->toPlainText());
}
void MainWindow::on_tpf_output_textChanged() {
    clipboard_copy(ui->tpf_output->toPlainText());
}
void MainWindow::on_normalizer_output_textChanged() {
    clipboard_copy(ui->normalizer_output->toPlainText());
}

