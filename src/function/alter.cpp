#include "function/alter.h"
#include "ui_alter.h"
#include "algorithm/algorithm.h"

Alter::Alter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Alter) {
    ui->setupUi(this);
}

Alter::~Alter() { delete ui; }


void Alter::on_selfMVButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    tpV *= ui->selfMV->value();
    ui->output->setPlainText(tpV.getStringRaw("\n"));
}
void Alter::on_selfAVButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;
    tpV += ui->selfAV->value();
    ui->output->setPlainText(tpV.getStringRaw("\n"));
}
void Alter::on_selfMOButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    auto newTpV = tpV.offsetArithmetic(ui->selfMO->value(), [](double offset, double parameter){
        return offset * parameter;
    });

    ui->output->setPlainText(newTpV.getStringRaw("\n"));
}
void Alter::on_selfAOButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    auto newTpV = tpV.offsetArithmetic(
                ui->selfAO->value(),
                [](double offset, double parameter){
        return offset + parameter;
    });
    ui->output->setPlainText(newTpV.getStringRaw("\n"));
}
void Alter::on_selfDeleteButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    auto delTpV = algorithm::deleteNth<TimingPoint>(QSPtr<TimingPointV>::create(tpV),
                                         static_cast<unsigned int>(ui->selfDel->value()),
                                         static_cast<unsigned int>(ui->selfDelOffset->value()));
    ui->output->setPlainText(delTpV.getStringRaw("\n"));
}
void Alter::on_selfSubdByButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;
    auto subdTpV =
            algorithm::copySubdBy<TimingPoint>(
                QSPtr<TimingPointV>::create(tpV),
                static_cast<unsigned int>(ui->selfSubdBy->value()), true);
    ui->output->setPlainText(subdTpV.getStringRaw("\n"));
}
void Alter::on_selfSubdToButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;
    auto subdTpV =
            algorithm::copySubdTo<TimingPoint>(
                QSPtr<TimingPointV>::create(tpV),
                static_cast<unsigned int>(ui->selfSubdTo->value()), true);
    ui->output->setPlainText(subdTpV.getStringRaw("\n"));
}

void Alter::on_convertToBpm_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    TimingPointV tpVSv = tpV.getSvOnly();
    TimingPointV tpVBpm = tpV.getBpmOnly();

    double value;
    double reference = ui->convertRef->value();

    for (TimingPoint tpSv : tpVSv){
        value = tpSv.getValue();
        tpSv.setValue(value * reference);
        tpSv.setIsBpm(true);
        tpVBpm.pushBack(tpSv);
    }

    tpVBpm.sortByOffset(true);

    ui->output->setPlainText(tpVBpm.getStringRaw("\n"));
}
void Alter::on_convertToSv_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    TimingPointV tpVSv = tpV.getSvOnly();
    TimingPointV tpVBpm = tpV.getBpmOnly();

    double value;
    double reference = ui->convertRef->value();

    for (TimingPoint tpBpm : tpVBpm){
        value = tpBpm.getValue();
        tpBpm.setValue(value / reference);
        tpBpm.setIsSv(true);
        tpVSv.pushBack(tpBpm);
    }

    tpVSv.sortByOffset(true);

    ui->output->setPlainText(tpVSv.getStringRaw("\n"));
}
void Alter::on_crossMVButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n'))  return;

    TimingPointV tpVCross;
    if (!tpVCross.loadRaw(ui->inputCross->toPlainText(), '\n'))  return;

    tpV.crossEffectMultiply(tpVCross);
    ui->output->setPlainText(tpV.getStringRaw("\n"));
}
void Alter::on_crossAVButton_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n'))  return;

    TimingPointV tpVCross;
    if (!tpVCross.loadRaw(ui->inputCross->toPlainText(), '\n')) return;

    tpV.crossEffectAdd(tpVCross);
    ui->output->setPlainText(tpV.getStringRaw("\n"));
}

void Alter::on_output_textChanged() {
    emit outputChanged();
}
QString Alter::output() const {
    return ui->output->toPlainText();
}
