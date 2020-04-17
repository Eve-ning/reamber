#include "function/twopointfunction.h"
#include "ui_twopointfunction.h"
#include "algorithm/algorithm.h"

TwoPointFunction::TwoPointFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoPointFunction)
{
    ui->setupUi(this);
    tpfInitcustomPlot();
}

TwoPointFunction::~TwoPointFunction()
{
    delete ui;
}

QString TwoPointFunction::output() const
{
    return ui->output->toPlainText();
}

void TwoPointFunction::on_initSvLabel_valueChanged(int value) {
    ui->initSvLabel->setText(QString::number(value/VS_TO_VAL));
    if(ui->output_live->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_endSvLabel_valueChanged(int value) {
    ui->endSvLabel->setText(QString::number(value/VS_TO_VAL));
    if(ui->output_live->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_frequencyLabel_valueChanged(int value) {
    ui->frequencyLabel->setText(QString::number(value/2.0));
    if(ui->output_live->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_amplitudeSlider_valueChanged(int value) {
    if (ui->bpmRadio->isChecked())
        // BPM amplitudeSlideritude will only scale [-1 ~ 1]
        ui->amplitudeLabel->setText(QString::number(value/(VS_TO_VAL * 10)));
    else
        ui->amplitudeLabel->setText(QString::number(value/VS_TO_VAL));


    if (ui->output_live->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_phaseLabelueChanged(int value) {
    ui->phaseLabel->setText(QString::number(value));
    if(ui->output_live->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_powerLabel_valueChanged(int value) {
    ui->powerLabel->setText(QString::number(value/10.0));
    if(ui->output_live->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_generateButton_clicked() {
    HitObjectV hoV;

    // Break if fail
    if (!hoV.loadEditor(ui->input->text(), 0)) return;

    QVector<double> offsetV = hoV.getOffsetV(true);

    if (offsetV.size() < 2) return; // Needs to be at least 2
    if ((offsetV[1] - offsetV[0]) <= 0.0) return; // Needs to be > 0

    bool isBpm = ui->bpmRadio->isChecked();

    // Extract all values from TpF
    double initTp = isBpm ? ui->initBpm->value() : ui->initSvLabel->text().toDouble();
    double endTp = isBpm ? ui->endbpm->value() :ui->endSvLabel->text().toDouble();
    double amplitudeSlider = ui->amplitudeLabel->text().toDouble();
    double freq = ui->frequencyLabel->text().toDouble();
    double phaseSlider = ui->phaseLabel->text().toDouble();
    double power = ui->powerLabel->text().toDouble();
    double interpts = ui->interpts->value();

    bool curve_sine = ui->curveType->currentText() == "sine";
    bool curve_power = ui->curveType->currentText() == "power";

    bool curveInvertY = ui->curveInvertY->isChecked();

    bool outputTrimCheck = ui->outputTrimCheck->isChecked();

    // Adjust offset
    double offset_adjust = ui->offsetVal->value();
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
    // <PRIMARY>   <LINEAR> (mx + c) + amplitudeSlider *
    // <SECONDARY> <SINE>   sin[(x * 2 * PI + phs) * freq]
    // <SECONDARY> <POWER>  x^pwr
    auto tpf_function = [&](double progress) -> double {
        double primary = 0;
        double gradient = (endTp - initTp);
        primary = (progress * gradient + initTp);
        double secondary = 0;
        if (curve_sine)  secondary = amplitudeSlider * sin(((progress + (phaseSlider/360.0)) * double(MATH_PI) * 2) * freq);
        else if (curve_power) secondary = pow(progress * amplitudeSlider, power);

        // This is so that the curve scales relative to the average linear BPM
        if (isBpm) secondary *= ((endTp + initTp) / 2);

        // Curb values if needed
        if (outputTrimCheck)  return clipValue(curveInvertY ? (primary - secondary) : (primary + secondary), isBpm);

        return curveInvertY ? (primary - secondary) : (primary + secondary);
    };

    // Create all the timing points
    TimingPointV tpV;

    for (double offset : offsetV) {
        TimingPoint tp;
        double progress = (offset - offsetV[0])/offset_difference;
        tp.loadParameters(offset, tpf_function(progress), ui->bpmRadio->isChecked(), false, 4);
        tpV.pushBack(tp);
    }

    // Sort by offset
    tpV.sortByOffset(true);

    // Call update on the plot
    tpfUpdatecustomPlot(tpV.getOffsetV(),
                        tpV.getValueV(),
                        isBpm);

    // Update Average SV
    ui->outputAverage->setText(isBpm ?
                                QString::number(tpV.getAverageBpmValue()) :
                                QString::number(tpV.getAverageSvValue()));

    ui->output->setPlainText(tpV.getStringRaw());
}
void TwoPointFunction::on_resetButton_clicked() {
    ui->amplitudeSlider->setValue(0);
    ui->frequencySlider->setValue(1);
    // freq slider on 1 sets to 0.5 for some reason, will manually set this to 0.5
    ui->frequencyLabel->setText("1.0");

    ui->interpts->setValue(50);

    ui->phaseSlider->setValue(0);
    ui->powerSlider->setValue(10);

    ui->initSv->setValue(100);
    ui->endSv->setValue(100);

    ui->initBpm->setValue(120);
    ui->endbpm->setValue(120);

    ui->offsetVal->setValue(0);

    ui->svRadio->setChecked(true);
    ui->bpmRadio->setChecked(false);
    ui->curveType->setCurrentIndex(0);
    ui->curveInvertY->setChecked(false);
//    ui->outputTrimCheck->setChecked(true);
//    ui->output_live->setChecked(false);
}

void TwoPointFunction::tpfInitcustomPlot() {
    auto customPlot = ui->customPlot;
    customPlot->addGraph();

    customPlot->xAxis->setLabel("offset");
    customPlot->yAxis->setLabel("value");

    customPlot->replot();
}
void TwoPointFunction::tpfUpdatecustomPlot(QVector<double> offsetV, QVector<double> valueV, bool isBpm) {

    auto customPlot = ui->customPlot;
    customPlot->graph(0)->setData(offsetV,valueV);

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

    customPlot->xAxis->setRange(*std::min_element(offsetV.begin(), offsetV.end()),
                                *std::max_element(offsetV.begin(), offsetV.end()));
    customPlot->yAxis->setRange(value_rng_min, value_rng_max);

    customPlot->replot();
}

void TwoPointFunction::on_output_textChanged() {
    emit outputChanged();
}
