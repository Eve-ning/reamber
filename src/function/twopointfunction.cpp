#include "function/twopointfunction.h"
#include "ui_twopointfunction.h"
#include "algorithm/algorithm.h"

TwoPointFunction::TwoPointFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoPointFunction)
{
    ui->setupUi(this);
    tpf_init_customplot();
}

TwoPointFunction::~TwoPointFunction()
{
    delete ui;
}

QString TwoPointFunction::output() const
{
    return ui->tpf_output->toPlainText();
}

void TwoPointFunction::on_tpf_initsv_valueChanged(int value) {
    ui->tpf_initsv_val->setText(QString::number(value/VS_TO_VAL));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void TwoPointFunction::on_tpf_endsv_valueChanged(int value) {
    ui->tpf_endsv_val->setText(QString::number(value/VS_TO_VAL));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void TwoPointFunction::on_tpf_freq_valueChanged(int value) {
    ui->tpf_freq_val->setText(QString::number(value/2.0));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void TwoPointFunction::on_tpf_ampl_valueChanged(int value) {
    if (ui->tpf_type_bpm->isChecked())
        // BPM amplitude will only scale [-1 ~ 1]
        ui->tpf_ampl_val->setText(QString::number(value/(VS_TO_VAL * 10)));
    else
        ui->tpf_ampl_val->setText(QString::number(value/VS_TO_VAL));


    if (ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void TwoPointFunction::on_tpf_phase_valueChanged(int value) {
    ui->tpf_phase_val->setText(QString::number(value));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void TwoPointFunction::on_tpf_power_valueChanged(int value) {
    ui->tpf_power_val->setText(QString::number(value/10.0));
    if(ui->tpf_output_live->isChecked()) on_tpf_generate_clicked();
}
void TwoPointFunction::on_tpf_generate_clicked() {
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
void TwoPointFunction::on_tpf_reset_clicked() {
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

void TwoPointFunction::tpf_init_customplot() {
    auto customplot = ui->tpf_customplot;
    customplot->addGraph();

    customplot->xAxis->setLabel("offset");
    customplot->yAxis->setLabel("value");

    customplot->replot();
}
void TwoPointFunction::tpf_update_customplot(std::vector<double> offsetV, std::vector<double> value_v, bool is_bpm) {
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

void TwoPointFunction::on_tpf_output_textChanged() {
    emit outputChanged();
}
