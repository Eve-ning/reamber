#include "include/io/io.h"
#include "ui_io.h"
#include "object/multiple/timingpointv.h"
#include "object/multiple/hitobjectv.h"
#include <QGridLayout>
#include <QSpinBox>

IO::IO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IO) {
    ui->setupUi(this);

    setTitle("input/output");
    setPlaceholderText("Variant Input/Output");
    addKeyWidget();
}

IO::~IO(){
    delete ui;
}

void IO::addKeyWidget() {
    keySb = new QSpinBox(this);
    keySb->setRange(KEY_MIN, KEY_MAX);
    keySb->setValue(KEY_DEFAULT);
    keySb->setSuffix("K");
    keySb->setPrefix("Keys: ");
    layout()->addWidget(keySb, 1, 0);
}

void IO::hideKeyWidget() {
    keySb->setVisible(false);
}

uint IO::key() const {
    return uint(keySb->value());
}

QString IO::toPlainText() const {
    return ui->text->toPlainText();
}
QPlainTextEdit *IO::textWidget() const {
    return ui->text;
}
QGridLayout *IO::layout() const {
    return ui->gridLayout_2;
}

void IO::setTitle(const QString & title) {
    ui->textLO->setTitle(title);
}
void IO::setPlaceholderText(const QString & placeholder){
    ui->text->setPlaceholderText(placeholder);
}

void IO::setPlainText(const QString &s) {
    ui->text->setPlainText(s);
}

QVector<double> IO::readOffsets(bool makeUnique) const {
    // Try to load via different methods
    HitObjectV hoV;
    if (hoV.load(toPlainText())) return hoV.getOffsetV(makeUnique);
    TimingPointV tpV;
    if (tpV.loadRaw(toPlainText())) return tpV.getOffsetV(makeUnique);
    return QVector<double>();
}

QSize IO::sizeHint() const {
    return QSize(150, 100);
}

void IO::on_text_textChanged() {
    emit textChanged(toPlainText());
}


QVariant IO::read() const {
    HitObjectV hoV;
    if (hoV.load(toPlainText(), key())) return QVariant::fromValue<HitObjectV>(hoV);
    TimingPointV tpV;
    if (tpV.loadRaw(toPlainText())) return QVariant::fromValue<TimingPointV>(tpV);
    return QVariant(0);
}

void IO::write(const HitObjectV &o) {
    ui->text->setPlainText(o.getStringRaw("\n"));
}

void IO::write(const TimingPointV &o) {
    ui->text->setPlainText(o.getStringRaw("\n"));
}

