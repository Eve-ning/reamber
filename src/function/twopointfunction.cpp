#include "function/twopointfunction.h"
#include "ui_twopointfunction.h"
#include "algorithm/algorithm.h"

TwoPointFunction::TwoPointFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoPointFunction)
{
    ui->setupUi(this);
    tpfInitCustomplot();
}

TwoPointFunction::~TwoPointFunction()
{
    delete ui;
}

QString TwoPointFunction::output() const
{
    return ui->output->toPlainText();
}

void TwoPointFunction::on_initsv_valueChanged(int value) {
    ui->initsv_val->setText(QString::number(value/VS_TO_VAL));
    if(ui->output_live->isChecked()) on_generate_clicked();
}
void TwoPointFunction::on_endsv_valueChanged(int value) {
    ui->endsv_val->setText(QString::number(value/VS_TO_VAL));
    if(ui->output_live->isChecked()) on_generate_clicked();
}
void TwoPointFunction::on_freq_valueChanged(int value) {
    ui->freq_val->setText(QString::number(value/2.0));
    if(ui->output_live->isChecked()) on_generate_clicked();
}
void TwoPointFunction::on_ampl_valueChanged(int value) {
    if (ui->type_bpm->isChecked())
        // BPM amplitude will only scale [-1 ~ 1]
        ui->ampl_val->setText(QString::number(value/(VS_TO_VAL * 10)));
    else
        ui->ampl_val->setText(QString::number(value/VS_TO_VAL));


    if (ui->output_live->isChecked()) on_generate_clicked();
}
void TwoPointFunction::on_phase_valueChanged(int value) {
    ui->phase_val->setText(QString::number(value));
    if(ui->output_live->isChecked()) on_generate_clicked();
}
void TwoPointFunction::on_power_valueChanged(int value) {
    ui->power_val->setText(QString::number(value/10.0));
    if(ui->output_live->isChecked()) on_generate_clicked();
}
void TwoPointFunction::on_generate_clicked() {
    HitObjectV hoV;

    // Break if fail
    if (!hoV.loadEditor(ui->input->text(), 0)) return;

    QVector<double> offsetV = hoV.getOffsetV(true);

    if (offsetV.size() < 2) return; // Needs to be at least 2
    if ((offsetV[1] - offsetV[0]) <= 0.0) return; // Needs to be > 0

    bool isBpm = ui->type_bpm->isChecked();

    // Extract all values from TpF
    double initTp = isBpm ? ui->initbpm->value() : ui->initsv_val->text().toDouble();
    double endTp = isBpm ? ui->endbpm->value() :ui->endsv_val->text().toDouble();
    double ampl = ui->ampl_val->text().toDouble();
    double freq = ui->freq_val->text().toDouble();
    double phase = ui->phase_val->text().toDouble();
    double power = ui->power_val->text().toDouble();
    double interpts = ui->interpts->value();

    bool curve_sine = ui->curve_type->currentText() == "sine";
    bool curve_power = ui->curve_type->currentText() == "power";

    bool curve_invert_y = ui->curve_invert_y->isChecked();

    bool output_curb = ui->output_curb->isChecked();

    // Adjust offset
    double offset_adjust = ui->offset_val->value();
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
        tp.loadParameters(offset, tpf_function(progress), ui->type_bpm->isChecked(), false, 4);
        tpV.pushBack(tp);
    }

    // Sort by offset
    tpV.sortByOffset(true);

    // Call update on the plot
    tpfUpdateCustomplot(tpV.getOffsetV(),
                        tpV.getValueV(),
                        isBpm);

    // Update Average SV
    ui->output_ave->setText(isBpm ?
                                QString::number(tpV.getAverageBpmValue()) :
                                QString::number(tpV.getAverageSvValue()));

    ui->output->setPlainText(tpV.getStringRaw());
}
void TwoPointFunction::on_reset_clicked() {
    ui->ampl->setValue(0);
    ui->freq->setValue(1);
    // freq slider on 1 sets to 0.5 for some reason, will manually set this to 0.5
    ui->freq_val->setText("1.0");

    ui->interpts->setValue(50);

    ui->phase->setValue(0);
    ui->power->setValue(10);

    ui->initsv->setValue(100);
    ui->endsv->setValue(100);

    ui->initbpm->setValue(120);
    ui->endbpm->setValue(120);

    ui->offset_val->setValue(0);

    ui->type_sv->setChecked(true);
    ui->type_bpm->setChecked(false);
    ui->curve_type->setCurrentIndex(0);
    ui->curve_invert_y->setChecked(false);
//    ui->output_curb->setChecked(true);
//    ui->output_live->setChecked(false);
}

void TwoPointFunction::tpfInitCustomplot() {
    auto customplot = ui->customplot;
    customplot->addGraph();

    customplot->xAxis->setLabel("offset");
    customplot->yAxis->setLabel("value");

    customplot->replot();
}
void TwoPointFunction::tpfUpdateCustomplot(QVector<double> offsetV, QVector<double> valueV, bool isBpm) {

    auto customplot = ui->customplot;
    customplot->graph(0)->setData(offsetV,valueV);

    // We'll have different curbing for BPM and SV
    double value_rng_min;
    double value_rng_max;

    if (isBpm) {
        value_rng_min = *std::min_element(valueV.begin(), valueV.end());
        value_rng_max = *std::max_element(valueV.begin(), valueV.end());
    } else {
        value_rng_min = SV_MIN;
        value_rng_max = SV_MAX;
    }

    customplot->xAxis->setRange(*std::min_element(offsetV.begin(), offsetV.end()),
                                *std::max_element(offsetV.begin(), offsetV.end()));
    customplot->yAxis->setRange(value_rng_min, value_rng_max);

    customplot->replot();
}

void TwoPointFunction::on_output_textChanged() {
    emit outputChanged();
}
