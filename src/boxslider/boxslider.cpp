#include "include/boxslider/boxslider.h"
#include "ui_boxslider.h"
#include "common.h"
#include <QDebug>

BoxSlider::BoxSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxSlider),
    min(0.0), max(100.0), steps(100)
{
    ui->setupUi(this);
    slider()->setRange(0, int(steps));

    setSteps(steps);
    setRange(min, max);
}

BoxSlider::~BoxSlider() { delete ui; }

void BoxSlider::setParameters(double min, double max, uint steps, double value) {
    setRange(min, max);
    setSteps(steps);
    setValue(value);
}

void BoxSlider::setRange(double min, double max) {
    this->min = min;
    this->max = max;
    spinBox()->setRange(min, max);
    ui->min->setText(QString::number(min, 'g', 4));
    ui->max->setText(QString::number(max, 'g', 4));
    updateSlider(spinBox()->value());
}

void BoxSlider::setSteps(uint steps) {
    this->steps = steps;
    slider()->setRange(0, int(steps));
    updateSlider(spinBox()->value());
    spinBox()->setSingleStep((max / min) / steps);
}

void BoxSlider::setValue(double value) {
    spinBox()->setValue(value);
    updateSlider(value);
}

void BoxSlider::updateSpinBox(double sliderValue) {
    spinBox()->setValue(sliderValue / steps * (max - min) + min);
}
void BoxSlider::updateSlider(double spinBoxValue) {
    slider()->setValue(int((spinBoxValue - min) / (max - min) * steps));
}

double BoxSlider::value() {
    return spinBox()->value();
}

void BoxSlider::setTitle(const QString &str) {
    ui->lo->setTitle(str);
}

QSlider *BoxSlider::slider() {
    return ui->slider;
}
QDoubleSpinBox *BoxSlider::spinBox() {
    return ui->spinBox;
}

void BoxSlider::on_slider_valueChanged(int value) {
    //qDebug() << value;
    updateSpinBox(value);
    emit valueChanged();
}

void BoxSlider::on_spinBox_editingFinished() {
    updateSlider(ui->spinBox->value());
    emit valueChanged();
}
