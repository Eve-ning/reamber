#include "function/alter.h"
#include "ui_alter.h"
#include "algorithm/algorithm.h"

Alter::Alter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Alter)
{
    ui->setupUi(this);
}

Alter::~Alter()
{
    delete ui;
}

QString Alter::output() const
{
    return ui->output->toPlainText();
}

void Alter::on_self_mv_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    tpV *= ui->self_mv->value();
    ui->output->setPlainText(tpV.getStringRaw("\n"));
}
void Alter::on_self_av_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;
    tpV += ui->self_av->value();
    ui->output->setPlainText(tpV.getStringRaw("\n"));
}
void Alter::on_self_mo_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    auto newTpV = tpV.offsetArithmetic(ui->self_mo->value(), [](double offset, double parameter){
        return offset * parameter;
    });

    ui->output->setPlainText(newTpV.getStringRaw("\n"));
}
void Alter::on_self_ao_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    auto newTpV = tpV.offsetArithmetic(
                ui->self_ao->value(),
                [](double offset, double parameter){
        return offset + parameter;
    });
    ui->output->setPlainText(newTpV.getStringRaw("\n"));
}
void Alter::on_self_del_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    auto delTpV = algorithm::deleteNth<TimingPoint>(QSPtr<TimingPointV>::create(tpV),
                                         static_cast<unsigned int>(ui->self_del->value()),
                                         static_cast<unsigned int>(ui->self_del_offset->value()));
    ui->output->setPlainText(delTpV.getStringRaw("\n"));
}
void Alter::on_self_subd_by_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n'))  return;
    auto subdTpV =
            algorithm::copySubdBy<TimingPoint>(
                QSPtr<TimingPointV>::create(tpV),
                static_cast<unsigned int>(ui->self_subd_by->value()), true);
    ui->output->setPlainText(subdTpV.getStringRaw("\n"));
}
void Alter::on_self_subd_to_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;
    auto subdTpV =
            algorithm::copySubdTo<TimingPoint>(
                QSPtr<TimingPointV>::create(tpV),
                static_cast<unsigned int>(ui->self_subd_to->value()), true);
    ui->output->setPlainText(subdTpV.getStringRaw("\n"));
}

void Alter::on_convert_to_bpm_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    TimingPointV tpVSv = tpV.getSvOnly();
    TimingPointV tpVBpm = tpV.getBpmOnly();

    double value;
    double reference = ui->convert_ref->value();

    for (TimingPoint tp_sv : tpVSv){
        value = tp_sv.getValue();
        tp_sv.setValue(value * reference);
        tp_sv.setIsBpm(true);
        tpVBpm.pushBack(tp_sv);
    }

    tpVBpm.sortByOffset(true);

    ui->output->setPlainText(tpVBpm.getStringRaw("\n"));
}
void Alter::on_convert_to_sv_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n')) return;

    TimingPointV tpVSv = tpV.getSvOnly();
    TimingPointV tpVBpm = tpV.getBpmOnly();

    double value;
    double reference = ui->convert_ref->value();

    for (TimingPoint tpBpm : tpVBpm){
        value = tpBpm.getValue();
        tpBpm.setValue(value / reference);
        tpBpm.setIsSv(true);
        tpVSv.pushBack(tpBpm);
    }

    tpVSv.sortByOffset(true);

    ui->output->setPlainText(tpVSv.getStringRaw("\n"));
}
void Alter::on_cross_mv_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n'))  return;

    TimingPointV tp_v_cross;
    if (!tp_v_cross.loadRaw(ui->input_cross->toPlainText(), '\n'))  return;

    tpV.crossEffectMultiply(tp_v_cross);
    ui->output->setPlainText(tpV.getStringRaw("\n"));
}
void Alter::on_cross_av_b_clicked() {
    TimingPointV tpV;
    // Break if fail
    if (!tpV.loadRaw(ui->input->toPlainText(), '\n'))  return;

    TimingPointV tp_v_cross;
    if (!tp_v_cross.loadRaw(ui->input_cross->toPlainText(), '\n')) return;

    tpV.crossEffectAdd(tp_v_cross);
    ui->output->setPlainText(tpV.getStringRaw("\n"));
}

void Alter::on_output_textChanged() {
    emit outputChanged();
}
