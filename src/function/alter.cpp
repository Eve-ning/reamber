#include "function/alter.h"
#include "ui_alter.h"
#include "algorithm/algorithm.h"

Alter::Alter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Alter) {
    ui->setupUi(this);
    ui->inputCross->setTitle("input_cross");
    initToolTips();
}

Alter::~Alter() { delete ui; }

void Alter::on_selfMVButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;

    tpV *= ui->selfMV->value();
    ui->output->write(tpV);
}
void Alter::on_selfAVButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;
    tpV += ui->selfAV->value();
    ui->output->write(tpV);
}
void Alter::on_selfMOButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;

    auto newTpV = tpV.offsetArithmetic(ui->selfMO->value(), [](double offset, double parameter){
        return offset * parameter;
    });

    ui->output->write(TimingPointV(newTpV));
}
void Alter::on_selfAOButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;

    auto newTpV = tpV.offsetArithmetic(
                ui->selfAO->value(),
                [](double offset, double parameter){
        return offset + parameter;
    });
    ui->output->write(TimingPointV(newTpV));
}
void Alter::on_selfDeleteButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;

    auto delTpV = algorithm::deleteNth<TimingPoint>(tpV.sptr(),
                                         static_cast<unsigned int>(ui->selfDel->value()),
                                         static_cast<unsigned int>(ui->selfDelOffset->value()));
    ui->output->write(TimingPointV(delTpV));
}
void Alter::on_selfSubdByButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;
    auto subdTpV = algorithm::copySubdBy<TimingPoint>(tpV.sptr(),
                            static_cast<unsigned int>(ui->selfSubdBy->value()), true);
    ui->output->write(TimingPointV(subdTpV));
}
void Alter::on_selfSubdToButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;
    auto subdTpV =  algorithm::copySubdTo<TimingPoint>(tpV.sptr(),
                            static_cast<unsigned int>(ui->selfSubdTo->value()), true);
    ui->output->write(TimingPointV(subdTpV));
}

void Alter::on_convertToBpm_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;

    TimingPointV tpVSv = tpV.getSvOnly();
    TimingPointV tpVBpm = tpV.getBpmOnly();

    double value;
    double reference = ui->convertRef->value();

    for (TimingPoint tpSv : tpVSv) {
        value = tpSv.getValue();
        tpSv.setValue(value * reference);
        tpSv.setIsBpm(true);
        tpVBpm.pushBack(tpSv);
    }

    tpVBpm.sortByOffset(true);

    ui->output->write(tpVBpm);
}
void Alter::on_convertToSv_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;

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

    ui->output->write(tpVSv);
}
void Alter::on_crossMVButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;

    TimingPointV tpVCross = ui->inputCross->read();
    if (tpVCross.empty()) return;

    tpV.crossEffectMultiply(tpVCross);
    ui->output->write(tpV);
}
void Alter::on_crossAVButton_clicked() {
    TimingPointV tpV = ui->input->read();
    if (tpV.empty()) return;

    TimingPointV tpVCross = ui->inputCross->read();
    if (tpVCross.empty()) return;

    tpV.crossEffectAdd(tpVCross);
    ui->output->write(tpV);
}

void Alter::on_output_textChanged() {
    emit outputChanged();
}

void Alter::initToolTips() {
    ui->input->setToolTip("Input to be altered.");
    ui->inputCross->setToolTip("Input to be crossed with");
    ui->output->setToolTip("Altered Output goes here");
}
QString Alter::output() const {
    return ui->output->toPlainText();
}
