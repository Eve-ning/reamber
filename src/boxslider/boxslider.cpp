#include "include/boxslider/boxslider.h"
#include "ui_boxslider.h"
#include "common.h"

BoxSlider::BoxSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxSlider),
    min(0.0), max(100.0), stepSize(1.0)
{
    ui->setupUi(this);
    updateRange();
}

BoxSlider::~BoxSlider()
{
    delete ui;
}

void BoxSlider::setLimits(double min, double max) {
    this->min = min;
    this->max = max;
    updateRange();
}

void BoxSlider::updateRange() {
    // Note that slider operates in integers
    // So we figure out the number of steps to reach the maximum according to stepSize
    int steps = int((max - min) / stepSize);
    ui->slider->setRange(0, steps);
    ui->spinbox->setRange(min, max);

}

void BoxSlider::updateSpinBox() {
    double sliderValue = ui->slider->value();
    ui->spinbox->setValue(sliderValue * stepSize + min);
}

void BoxSlider::updateSlider() {
    double spinboxValue = ui->spinbox->value();
    ui->slider->setValue(int((spinboxValue - min) / stepSize));
}

double BoxSlider::value()
{
    return ui->spinbox->value();
}


void BoxSlider::on_slider_sliderMoved()
{
    updateSpinBox();
}

void BoxSlider::on_spinbox_valueChanged()
{
    updateSlider();
}
