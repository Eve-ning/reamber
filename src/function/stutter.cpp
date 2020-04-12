#include "function/stutter.h"
#include "ui_stutter.h"
#include "algorithm/algorithm.h"

Stutter::Stutter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stutter)
{
    ui->setupUi(this);
    stutterLimitUpdate();
}

Stutter::~Stutter()
{
    delete ui;
}


void Stutter::on_initsv_vs_valueChanged(int value) {
    ui->initsv_val->setText(QString::number(value/VS_TO_VAL));
}
void Stutter::on_initbpm_vs_valueChanged(int value) {
    ui->initbpm_val->setText(QString::number(value/VS_TO_VAL));
}
void Stutter::on_threshold_vs_valueChanged(int value) {
    ui->threshold_val->setText(QString::number(value/VS_TO_VAL));
    stutterLimitUpdate();
}
void Stutter::on_generate_clicked() {
    HitObjectV hoV;
    auto t = ui->input->toPlainText();
    // Break if fail
    if (!hoV.loadEditor(t)) return;

    // Break if empty
    if (hoV.size() == 0) return;

    TimingPointV tpV;

    // Depends on which radio is checked, we generate a different output
    if (ui->type_sv->isChecked())
        tpV = algorithm::stutterRel(
                    hoV.getOffsetV(true),
                    ui->initsv_val->text().toDouble(),
                    ui->threshold_val->text().toDouble(),
                    ui->avesv->value(),
                    false, true,
                    ui->skip_last->isChecked());
    else if (ui->type_bpm->isChecked())
        tpV = algorithm::stutterRel(
                    hoV.getOffsetV(true),
                    ui->initbpm_val->text().toDouble(),
                    ui->threshold_val->text().toDouble(),
                    ui->avebpm->value(),
                    true, true,
                    ui->skip_last->isChecked());



    ui->output->setPlainText(tpV.getStringRaw("\n"));

}
void Stutter::on_preset_nft_clicked() { // Normalized Front Teleport
    HitObjectV hoV;
    hoV.loadEditor(ui->input->toPlainText());

    // Break if empty
    if (hoV.size() == 0) return;

    TimingPointV tpV = algorithm::stutterAbs(
                hoV.getOffsetV(true),
                BPM_MIN,
                BPM_MIN,
                ui->avebpm->value(),
                true,
                false,
                true,
                false);

    // We cannot directly omit since we need to stutter swap here
    tpV = algorithm::stutterSwap(tpV);

    tpV.popBack();

    ui->output->setPlainText(tpV.getStringRaw("\n"));
}
void Stutter::on_preset_nbt_clicked() { // Normalized Back Teleport
    HitObjectV hoV;
    hoV.loadEditor(ui->input->toPlainText());

    // Break if empty
    if (hoV.size() == 0) return;

    TimingPointV tpV = algorithm::stutterAbs(
                hoV.getOffsetV(true),
                BPM_MIN,
                BPM_MIN,
                ui->avebpm->value(),
                true,
                false,
                true,
                ui->skip_last->isChecked());

    ui->output->setPlainText(tpV.getStringRaw("\n"));
}
void Stutter::on_preset_mft_clicked() { // Max Front Teleport
    HitObjectV hoV;
    hoV.loadEditor(ui->input->toPlainText());

    // Break if empty
    if (hoV.size() == 0) return;

    TimingPointV tpV;
    TimingPoint tpTeleport;
    TimingPoint tpNormalized;

    tpTeleport.setValue(BPM_MAX);
    tpNormalized.setValue(ui->avebpm->value());

    tpTeleport.setOffset(0);
    tpNormalized.setOffset(1);

    tpTeleport.setIsBpm(true);
    tpNormalized.setIsBpm(true);

    tpV.pushBack(tpTeleport);
    tpV.pushBack(tpNormalized);

    ui->output->setPlainText(
                algorithm::copy<TimingPoint>(
                    QSPtr<TimingPointV>::create(tpV),
                    hoV.getOffsetV(true),
                    true,
                    true).getStringRaw("\n"));
}
void Stutter::on_preset_mbt_clicked() { // Max Back Teleport
    HitObjectV hoV;
    hoV.loadEditor(ui->input->toPlainText());

    // Break if empty
    if (hoV.size() == 0) return;

    // move back by 1ms
    for (auto& ho : hoV) ho.setOffset(ho.getOffset()-1);

    TimingPointV tpV;
    TimingPoint tpTeleport;
    TimingPoint tpNormalized;

    tpTeleport.setValue(BPM_MAX);
    tpNormalized.setValue(ui->avebpm->value());

    tpTeleport.setOffset(0);
    tpNormalized.setOffset(1);

    tpTeleport.setIsBpm(true);
    tpNormalized.setIsBpm(true);

    tpV.pushBack(tpTeleport);
    tpV.pushBack(tpNormalized);

    ui->output->setPlainText(
                algorithm::copy<TimingPoint>(
                    QSPtr<TimingPointV>::create(tpV),
                    hoV.getOffsetV(true),
                    true, true).getStringRaw("\n"));
}
void Stutter::on_avebpm_valueChanged(double) { stutterLimitUpdate(); }
void Stutter::on_avesv_valueChanged(double) { stutterLimitUpdate(); }
void Stutter::stutterLimitUpdate() {
    if (ui->type_sv->isChecked()){
        // We limit the initial SV values
        QVector<double> initLim = algorithm::stutterRelInitLimits(
                    ui->threshold_val->text().toDouble(),
                    ui->avesv->text().toDouble(), SV_MIN, SV_MAX);

        // If the lower limit is lower than SV_MIN we curb the setMinimum
        if (initLim[0] >= SV_MIN)
            ui->initsv_vs->setMinimum(int(initLim[0] * VS_TO_VAL));
        else
            ui->initsv_vs->setMinimum(int(SV_MIN * VS_TO_VAL));


        // If the upper limit is higher than SV_MAX we curb the setMaximum
        if (initLim[1] <= SV_MAX)
            ui->initsv_vs->setMaximum(int(initLim[1] * VS_TO_VAL));
        else
            ui->initsv_vs->setMaximum(int(SV_MAX * VS_TO_VAL));

    } else if (ui->type_bpm->isChecked()) {
        // We limit the initial BPM values
        QVector<double> initLim = algorithm::stutterRelInitLimits(
                    ui->threshold_val->text().toDouble(),
                    ui->avebpm->text().toDouble(), BPM_MIN, BPM_MAX);

        // If the lower limit is higher than BPM_MIN we curb the setMinimum
        if (initLim[0] >= BPM_MIN) {
            ui->initbpm_vs->setMinimum(int(initLim[0] * VS_TO_VAL));
        } else {
            ui->initbpm_vs->setMinimum(int(BPM_MIN * VS_TO_VAL));
        }

        // If the upper limit is lower than BPM_MAX we curb the setMaximum
        if (initLim[1] <= BPM_MAX) {
            ui->initbpm_vs->setMaximum(int(initLim[1] * VS_TO_VAL));
        } else {
            ui->initbpm_vs->setMaximum(int(BPM_MAX * VS_TO_VAL));
        }
    }
}

QString Stutter::output() const
{
    return ui->output->toPlainText();
}

void Stutter::on_output_textChanged() {
    emit outputChanged();
}
