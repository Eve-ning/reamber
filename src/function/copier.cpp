#include "function/copier.h"
#include "ui_copier.h"
#include "algorithm/algorithm.h"

Copier::Copier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Copier)
{
    ui->setupUi(this);
    ui->inputCopyFrom->setTitle("input_copy_from");
    ui->inputCopyFrom->setPlaceholderText("Variant Input");
    ui->inputCopyTo->setTitle("input_copy_to");
    ui->inputCopyTo->setPlaceholderText("Variant Input");
    ui->inputCopyTo->hideKeyWidget();
    ui->output->hideKeyWidget();
    ui->output->setTitle("output");
    ui->output->setPlaceholderText("Variant Output");
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
                    QSPtr<HitObjectV>::create(hoV),
                    copyTo,
                    true,
                    true);
        ui->output->write(HitObjectV(c));
        return;
    } else if (copyFrom.canConvert<TimingPointV>()) {
        TimingPointV tpV = copyFrom.value<TimingPointV>();
        auto c = algorithm::copy<TimingPoint>(
                    QSPtr<TimingPointV>::create(tpV),
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
