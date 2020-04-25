#include "function/copier.h"
#include "ui_copier.h"
#include "algorithm/algorithm.h"

Copier::Copier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Copier)
{
    ui->setupUi(this);
    ui->inputCopyFrom->setTitle("Input to Copy From");
    ui->inputCopyFrom->setPlaceholderText("Variant Input");
    ui->inputCopyTo->setTitle("Input to Copy To");
    ui->inputCopyTo->setPlaceholderText("Variant Input");
    ui->inputCopyTo->hideKeyWidget();
    ui->output->hideKeyWidget();
    ui->output->setTitle("Output");
    ui->output->setPlaceholderText("Variant Output");

    initToolTips();
}

Copier::~Copier() {
    delete ui;
}

QString Copier::output() const {
    return ui->output->toPlainText();
}

void Copier::on_generateButton_clicked() {
    auto copyTo = ui->inputCopyTo->readOffsets(true);
    QVariant copyFrom = ui->inputCopyFrom->read();
    if (copyFrom.canConvert<HitObjectV>()) {
        HitObjectV hoV = copyFrom.value<HitObjectV>();
        auto c = algorithm::copy<HitObject>(
                    hoV.sptr(),
                    copyTo,
                    true,
                    true);
        ui->output->write(HitObjectV(c));
        return;
    } else if (copyFrom.canConvert<TimingPointV>()) {
        TimingPointV tpV = copyFrom.value<TimingPointV>();
        auto c = algorithm::copy<TimingPoint>(
                    tpV.sptr(),
                    copyTo,
                    true,
                    true);
        ui->output->write(TimingPointV(c));
        return;
    }
    // else it doesn't convert correctly
}

void Copier::on_output_textChanged() {
    emit outputChanged();
}

void Copier::initToolTips() {
    ui->inputCopyTo->setToolTip("Input offsets to be copied to, can be any osu type with offsets.");
    ui->inputCopyFrom->setToolTip("Input objects to copy, keys MUST be specified in the case of HitObjects for correct conversion.");
    ui->output->setToolTip("Copied Output Objects goes here");
}
