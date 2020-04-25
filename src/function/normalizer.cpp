#include "function/normalizer.h"
#include "ui_normalizer.h"
#include "algorithm/algorithm.h"

Normalizer::Normalizer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Normalizer) {
    ui->setupUi(this);
}

Normalizer::~Normalizer() {
    delete ui;
}

QString Normalizer::output() const {
    return ui->output->toPlainText();
}

void Normalizer::on_generateButton_clicked() {
    TimingPointV tpV = ui->input->read();
    // Break if fail
    if (tpV.empty()) return;

    // Remove Items
    ui->bpmlist->clear();

    // Extract BPMs out of the vector only
    auto bpmTpV = tpV.getBpmOnly();
    QStringList bpmTpVStr;

    for (const auto& bpmTp : bpmTpV) bpmTpVStr.append(QString::number(bpmTp.getValue()));

    // Add Items
    ui->bpmlist->addItems(bpmTpVStr);

    ui->output->write(algorithm::normalize(tpV, ui->bpm->value(), false));
}
void Normalizer::on_bpmlist_itemClicked(QListWidgetItem *item) {
    ui->bpm->setValue(item->text().toDouble());
}

void Normalizer::on_output_textChanged() {
    emit outputChanged();
}
