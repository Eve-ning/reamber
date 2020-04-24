#pragma once

#include <QWidget>

namespace Ui {
class BoxSlider;
}

class BoxSlider : public QWidget
{
    Q_OBJECT

public:
    explicit BoxSlider(QWidget *parent = nullptr);
    ~BoxSlider();
    double value();
    void setLimits(double min, double max);
    void setStepSize(double factor);

    void updateRange();
    void updateSpinBox();
    void updateSlider();

protected slots:
    void on_slider_sliderMoved();
    void on_spinbox_valueChanged();

private:
    Ui::BoxSlider *ui;
    double min;
    double max;
    double stepSize;
};
