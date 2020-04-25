#pragma once

#include "inputho.h"

class HitObjectV;

class InputEHO : public InputHO
{
    Q_OBJECT

public:
    explicit InputEHO(QWidget *parent = nullptr);
    ~InputEHO() override;

    virtual HitObjectV read() const override;
};

