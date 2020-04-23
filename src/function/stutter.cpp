#include "function/stutter.h"
#include "ui_stutter.h"
#include "algorithm/algorithm.h"

Stutter::Stutter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stutter) {
    ui->setupUi(this);
    ui->input->hideKeyWidget();
    ui->input->setTitle("input");
    ui->input->setPlaceholderText("Variant Input");
    stutterLimitUpdate();
}

Stutter::~Stutter() {
    delete ui;
}

void Stutter::on_initSvSlider_valueChanged(int value) {
    ui->initSvLabel->setText(QString::number(value/VS_TO_VAL));
}
void Stutter::on_initBpmSlider_valueChanged(int value) {
    ui->initBpmLabel->setText(QString::number(value/VS_TO_VAL));
}
void Stutter::on_thresholdSlider_valueChanged(int value) {
    ui->thresholdLabel->setText(QString::number(value/VS_TO_VAL));
    stutterLimitUpdate();
}
void Stutter::on_generateButton_clicked() {
    auto offsets = readOffsets();
    // Break if empty
    if (offsets.empty()) return;

    TimingPointV tpV;

    // Depends on which radio is checked, we generateButton a different output
    if (ui->svRadio->isChecked())
        tpV = algorithm::stutterRel(offsets,
                                    ui->initSvLabel->text().toDouble(),
                                    ui->thresholdLabel->text().toDouble(),
                                    ui->aveSv->value(),
                                    false, true,
                                    ui->skipLastCheck->isChecked());
    else if (ui->bpmRadio->isChecked())
        tpV = algorithm::stutterRel(offsets,
                                    ui->initBpmLabel->text().toDouble(),
                                    ui->thresholdLabel->text().toDouble(),
                                    ui->aveBpm->value(),
                                    true, true,
                                    ui->skipLastCheck->isChecked());
    ui->output->write(tpV);
}
void Stutter::on_NormFrontTelButton_clicked() { // Normalized Front Teleport
    auto offsets = readOffsets();
    // Break if empty
    if (offsets.empty()) return;

    TimingPointV tpV = algorithm::stutterAbs(offsets,
                                             BPM_MIN,
                                             BPM_MIN,
                                             ui->aveBpm->value(),
                                             true,
                                             false,
                                             true,
                                             false);

    // We cannot directly omit since we need to stutter swap here
    tpV = algorithm::stutterSwap(tpV);

    if (ui->skipLastCheck->isChecked()) tpV.popBack();

    ui->output->write(tpV);
}
void Stutter::on_NormBackTelButton_clicked() { // Normalized Back Teleport
    auto offsets = readOffsets();

    // Break if empty
    if (offsets.empty()) return;

    TimingPointV tpV = algorithm::stutterAbs(offsets,
                                             BPM_MIN,
                                             BPM_MIN,
                                             ui->aveBpm->value(),
                                             true,
                                             false,
                                             true,
                                             ui->skipLastCheck->isChecked());

    ui->output->write(tpV);
}
void Stutter::on_MaxFronTelButton_clicked() { // Max Front Teleport
    auto offsets = readOffsets();

    // Break if empty
    if (offsets.empty()) return;

    TimingPointV tpV;
    TimingPoint tpTeleport;
    TimingPoint tpNormalized;

    tpTeleport.loadParameters(0, BPM_MAX, true);
    tpNormalized.loadParameters(1, ui->aveBpm->value(), true);

    tpV.pushBack(tpTeleport);
    tpV.pushBack(tpNormalized);

    ui->output->write(TimingPointV(algorithm::copy<TimingPoint>(
                                   QSPtr<TimingPointV>::create(tpV),
                                   offsets,
                                   true,
                                   true)));
}
void Stutter::on_MaxBackTelButton_clicked() { // Max Back Teleport
    auto offsets = readOffsets();

    // Break if empty
    if (offsets.empty()) return;

    // move back by 1ms
    for (auto& offset : offsets) offset -= 1.0;

    TimingPointV tpV;
    TimingPoint tpTeleport;
    TimingPoint tpNormalized;

    tpTeleport.loadParameters(0, BPM_MAX, true);
    tpNormalized.loadParameters(1, ui->aveBpm->value(), true);

    tpV.pushBack(tpTeleport);
    tpV.pushBack(tpNormalized);

    ui->output->write(TimingPointV(algorithm::copy<TimingPoint>(
                                   QSPtr<TimingPointV>::create(tpV),
                                   offsets,
                                   true, true)));
}
void Stutter::on_aveBpm_valueChanged(double) { stutterLimitUpdate(); }
void Stutter::on_aveSv_valueChanged(double) { stutterLimitUpdate(); }
void Stutter::stutterLimitUpdate() {
    if (ui->svRadio->isChecked()){
        // We limit the initial SV values
        QVector<double> initLim = algorithm::stutterRelInitLimits(
                    ui->thresholdLabel->text().toDouble(),
                    ui->aveSv->text().toDouble(), SV_MIN, SV_MAX);

        // If the lower limit is lower than SV_MIN we curb the setMinimum
        if (initLim[0] >= SV_MIN)
            ui->initSvSlider->setMinimum(int(initLim[0] * VS_TO_VAL));
        else
            ui->initSvSlider->setMinimum(int(SV_MIN * VS_TO_VAL));

        // If the upper limit is higher than SV_MAX we curb the setMaximum
        if (initLim[1] <= SV_MAX)
            ui->initSvSlider->setMaximum(int(initLim[1] * VS_TO_VAL));
        else
            ui->initSvSlider->setMaximum(int(SV_MAX * VS_TO_VAL));

    } else if (ui->bpmRadio->isChecked()) {
        // We limit the initial BPM values
        QVector<double> initLim = algorithm::stutterRelInitLimits(
                    ui->thresholdLabel->text().toDouble(),
                    ui->aveBpm->text().toDouble(), BPM_MIN, BPM_MAX);

        // If the lower limit is higher than BPM_MIN we curb the setMinimum
        if (initLim[0] >= BPM_MIN)
            ui->initBpmSlider->setMinimum(int(initLim[0] * VS_TO_VAL));
        else
            ui->initBpmSlider->setMinimum(int(BPM_MIN * VS_TO_VAL));


        // If the upper limit is lower than BPM_MAX we curb the setMaximum
        if (initLim[1] <= BPM_MAX)
            ui->initBpmSlider->setMaximum(int(initLim[1] * VS_TO_VAL));
        else
            ui->initBpmSlider->setMaximum(int(BPM_MAX * VS_TO_VAL));

    }
}

QString Stutter::output() const {
    return ui->output->toPlainText();
}

void Stutter::on_output_textChanged() {
    emit outputChanged();
}

QVector<double> Stutter::readOffsets() {
    return ui->input->readOffsets(true);
}
