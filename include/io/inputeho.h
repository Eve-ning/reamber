#pragma once

#include "io.h"

class HitObjectV;

class InputEHO : public IO
{
public:
    Q_OBJECT

    explicit InputEHO(QWidget *parent = nullptr);
    ~InputEHO() override;
};

