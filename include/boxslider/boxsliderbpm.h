#pragma once

#include <QWidget>
#include "boxslider.h"

class BoxSliderBpm : protected BoxSlider
{
    Q_OBJECT

public:
    explicit BoxSliderBpm(QWidget *parent = nullptr);
    ~BoxSliderBpm();

private:
};
