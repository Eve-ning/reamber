#pragma once

#include "io.h"

class InputHO : public IO
{
public:
    Q_OBJECT

    explicit InputHO(QWidget *parent = nullptr);
    ~InputHO() override;
};

