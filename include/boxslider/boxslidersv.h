#pragma once

#include <QWidget>
#include "boxslider.h"

class BoxSliderSv : protected BoxSlider
{
    Q_OBJECT

public:
    explicit BoxSliderSv(QWidget *parent = nullptr);
    ~BoxSliderSv();

private:
};

