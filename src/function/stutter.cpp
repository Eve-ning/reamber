#include "function/stutter.h"
#include "ui_stutter.h"
#include "algorithm/algorithm.h"
#include "common.h"

Stutter::Stutter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stutter) {
    ui->setupUi(this);
    ui->input->hideKeyWidget();
    ui->input->setTitle("input");
    ui->input->setPlaceholderText("Variant Input");

    initBoxSliders();
    stutterLimitUpdate();
}

Stutter::~Stutter() {
    delete ui;
}

void Stutter::initBoxSliders() {
    ui->threshold->setParameters(0.01, 1.0, 1000, 0.5);
    ui->threshold->setTitle("threshold");
    ui->threshold->spinBox()->setDecimals(3);

    ui->initSv->setParameters(SV_MIN, SV_MAX, 1000, SV_DEFAULT);
    ui->initSv->setTitle("init_sv");

    ui->initBpm->setParameters(BPM_MIN, BPM_MAX, 1000, BPM_DEFAULT);
    ui->initBpm->setTitle("init_bpm");
}
void Stutter::on_threshold_valueChanged() {
    stutterLimitUpdate();
}

void Stutter::on_generateButton_clicked() {
    auto offsets = readOffsets();
    // Break if empty
    if (offsets.empty()) return;

    TimingPointV tpV;

    // Depends on which radio is checked, we generateButton a different output
    if (ui->svRadio->isChecked())
        tpV = algorithm::stutterRel(offsets,       // Offsets
                                    initSv(),      // Initial
                                    threshold(),   // Relativity
                                    aveSv(),       // Average
                                    false,         // Is BPM
                                    true,          // Skip on Invalid
                                    isSkipLast()); // Skip Last
    else if (ui->bpmRadio->isChecked())
        tpV = algorithm::stutterRel(offsets,       // Offsets
                                    initBpm(),     // Initial
                                    threshold(),   // Relativity
                                    aveBpm(),      // Average
                                    true,          // Is BPM
                                    true,          // Skip on Invalid
                                    isSkipLast()); // Skip Last
    ui->output->write(tpV);
}
void Stutter::on_NormFrontTelButton_clicked() { // Normalized Front Teleport
    auto offsets = readOffsets();
    // Break if empty
    if (offsets.empty()) return;

    TimingPointV tpV = algorithm::stutterAbs(
                offsets,        // Offsets
                BPM_MIN,// Initial
                BPM_MIN,// Relativity
                aveBpm(),       // Average
                true,           // Is BPM
                false,          // Relative From Front
                true,           // Skip on Invalid
                false);         // [*] Skip Last

    // [*] We cannot directly omit since we need to stutter swap here
    tpV = algorithm::stutterSwap(tpV);

    if (isSkipLast()) tpV.popBack();

    ui->output->write(tpV);
}
void Stutter::on_NormBackTelButton_clicked() { // Normalized Back Teleport
    auto offsets = readOffsets();

    // Break if empty
    if (offsets.empty()) return;

    TimingPointV tpV = algorithm::stutterAbs(
                offsets,        // Offsets
                BPM_MIN,        // Initial
                BPM_MIN,        // Relativity
                aveBpm(),       // Average
                true,           // Is BPM
                false,          // Relative From Front
                true,           // Skip on Invalid
                isSkipLast());  // Skip Last

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
    tpNormalized.loadParameters(1, aveBpm(), true);

    tpV.pushBack(tpTeleport);
    tpV.pushBack(tpNormalized);

    ui->output->write(TimingPointV(algorithm::copy<TimingPoint>(
                                   tpV.sptr(),
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
    tpNormalized.loadParameters(1, aveBpm(), true);

    tpV.pushBack(tpTeleport);
    tpV.pushBack(tpNormalized);

    ui->output->write(TimingPointV(algorithm::copy<TimingPoint>(
                                   tpV.sptr(),
                                   offsets,
                                   true, true)));
}
void Stutter::on_aveBpm_valueChanged(double) { stutterLimitUpdate(); }
void Stutter::on_aveSv_valueChanged(double) { stutterLimitUpdate(); }
void Stutter::stutterLimitUpdate() {
    QVector<double> initLim =
            algorithm::stutterRelInitLimits(threshold(),
                                            aveSv(),
                                            SV_MIN,
                                            SV_MAX);
    ui->initSv->setRange(initLim[0] >= SV_MIN ? initLim[0] : SV_MIN,
                          initLim[1] <= SV_MAX ? initLim[1] : SV_MAX);

    initLim = algorithm::stutterRelInitLimits(threshold(),
                                              aveBpm(),
                                              BPM_MIN,
                                              BPM_MAX);

    ui->initBpm->setRange(initLim[0] >= BPM_MIN ? initLim[0] : BPM_MIN,
                           initLim[1] <= BPM_MAX ? initLim[1] : BPM_MAX);


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

bool Stutter::isSkipLast() const {
    return ui->skipLastCheck->isChecked();
}
double Stutter::aveBpm() const {
    return ui->aveBpm->value();
}
double Stutter::aveSv() const {
    return ui->aveSv->value();
}
double Stutter::initSv() const {
    return ui->initSv->value();
}
double Stutter::initBpm() const {
    return ui->initBpm->value();
}
double Stutter::threshold() const {
    return ui->threshold->value();
}
