#pragma once

#include <QWidget>

class QSlider;
class QDoubleSpinBox;

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
    virtual void setTitle(const QString & str);

    void setParameters(double min, double max, uint steps, double value);
    virtual void setRange(double min, double max);
    virtual void setSteps(uint steps);
    virtual void setValue(double value);
    virtual void setDecimals(uint decimals);

    virtual void updateSpinBox(double sliderValue);
    virtual void updateSlider(double spinBoxValue);

    QSlider * slider();
    QDoubleSpinBox * spinBox();

signals:
    void valueChanged();

protected slots:
    void on_slider_valueChanged(int value);
    void on_spinBox_editingFinished();

protected:
    Ui::BoxSlider *ui;
    double min;
    double max;
    uint steps;
};
