#include "function/twopointfunction.h"
#include "ui_twopointfunction.h"
#include "algorithm/algorithm.h"

TwoPointFunction::TwoPointFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoPointFunction)
{
    ui->setupUi(this);
    tpfInitCustomPlot();
}

TwoPointFunction::~TwoPointFunction()
{
    delete ui;
}

QString TwoPointFunction::output() const
{
    return ui->output->toPlainText();
}

void TwoPointFunction::on_initSvSlider_valueChanged(int value) {
    ui->initSvLabel->setText(QString::number(value/VS_TO_VAL));
    if(ui->outputLive->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_endSvSlider_valueChanged(int value) {
    ui->endSvLabel->setText(QString::number(value/VS_TO_VAL));
    if(ui->outputLive->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_frequencySlider_valueChanged(int value) {
    ui->frequencyLabel->setText(QString::number(value/2.0));
    if(ui->outputLive->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_amplitudeSlider_valueChanged(int value) {
    if (ui->bpmRadio->isChecked())
        // BPM amplitudeSlideritude will only scale [-1 ~ 1]
        ui->amplitudeLabel->setText(QString::number(value/(VS_TO_VAL * 10)));
    else
        ui->amplitudeLabel->setText(QString::number(value/VS_TO_VAL));


    if (ui->outputLive->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_phaseSlider_valueChanged(int value) {
    ui->phaseLabel->setText(QString::number(value));
    if(ui->outputLive->isChecked()) on_generateButton_clicked();
}
void TwoPointFunction::on_powerSlider_valueChanged(int value) {
    ui->powerLabel->setText(QString::number(value/10.0));
    if(ui->outputLive->isChecked()) on_generateButton_clicked();
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
    double endTp = isBpm ? ui->endBpm->value() :ui->endSvLabel->text().toDouble();
    double amplitude = ui->amplitudeLabel->text().toDouble();
    double freq = ui->frequencyLabel->text().toDouble();
    double phase = ui->phaseLabel->text().toDouble();
    double power = ui->powerLabel->text().toDouble();
    double interpts = ui->interpts->value();

    bool curveSine = ui->curveType->currentText() == "sine";
    bool curvePower = ui->curveType->currentText() == "power";

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
    auto tpfFunction = [&](double progress) -> double {
        double primary = 0;
        double gradient = (endTp - initTp);
        primary = (progress * gradient + initTp);
        double secondary = 0;
        if (curveSine)  secondary = amplitude * sin(((progress + (phase/360.0)) * double(MATH_PI) * 2) * freq);
        else if (curvePower) secondary = pow(progress * amplitude, power);

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
        tp.loadParameters(offset, tpfFunction(progress), ui->bpmRadio->isChecked(), false, 4);
        tpV.pushBack(tp);
    }

    // Sort by offset
    tpV.sortByOffset(true);

    // Call update on the plot
    tpfUpdateCustomPlot(tpV.getOffsetV(),
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

    ui->initSvSlider->setValue(100);
    ui->endSvSlider->setValue(100);

    ui->initBpm->setValue(120);
    ui->endBpm->setValue(120);

    ui->offsetVal->setValue(0);

    ui->svRadio->setChecked(true);
    ui->bpmRadio->setChecked(false);
    ui->curveType->setCurrentIndex(0);
    ui->curveInvertY->setChecked(false);
//    ui->outputTrimCheck->setChecked(true);
//    ui->outputLive->setChecked(false);
}

void TwoPointFunction::tpfInitCustomPlot() {
    auto customPlot = ui->customPlot;
    customPlot->addGraph();

    customPlot->xAxis->setLabel("offset");
    customPlot->yAxis->setLabel("value");

    customPlot->replot();
}
void TwoPointFunction::tpfUpdateCustomPlot(QVector<double> offsetV, QVector<double> valueV, bool isBpm) {

    auto customPlot = ui->customPlot;
    customPlot->graph(0)->setData(offsetV,valueV);

    // We'll have different curbing for BPM and SV
    double valueRngMin;
    double valueRngMax;

    if (isBpm) {
        valueRngMin = *std::min_element(valueV.begin(), valueV.end());
        valueRngMax = *std::max_element(valueV.begin(), valueV.end());
    } else {
        valueRngMin = SV_MIN;
        valueRngMax = SV_MAX;
    }

    customPlot->xAxis->setRange(*std::min_element(offsetV.begin(), offsetV.end()),
                                *std::max_element(offsetV.begin(), offsetV.end()));
    customPlot->yAxis->setRange(valueRngMin, valueRngMax);

    customPlot->replot();
}

void TwoPointFunction::on_output_textChanged() {
    emit outputChanged();
}
