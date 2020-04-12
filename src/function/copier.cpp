#include "function/copier.h"
#include "ui_copier.h"
#include "algorithm/algorithm.h"


Copier::Copier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Copier)
{
    ui->setupUi(this);
}

Copier::~Copier()
{
    delete ui;
}

QString Copier::output() const
{
    return ui->output->toPlainText();
}

void Copier::on_generate_clicked() {
    // We need the tpV and hoV for copier
    // However, we don't actually need correct keys for hit_object
    TimingPointV tpV;

    // Break if fail
    if (!tpV.loadRaw(ui->tp->toPlainText())) return;

    // We default keys to 0
    HitObjectV hoV;
    hoV.loadEditor(ui->ho->toPlainText());

    // We only need the offsetV of hoV to copy
    ui->output->setPlainText(
                algorithm::copy<TimingPoint>(
                    QSPtr<TimingPointV>::create(tpV),
                    hoV.getOffsetV(true),
                    true,
                    true).getStringRaw("\n"));
}

void Copier::on_output_textChanged() {
    emit outputChanged();
}
