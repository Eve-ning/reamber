#pragma once

#include "io.h"

class InputTP : public IO
{
public:
    Q_OBJECT

    explicit InputTP(QWidget *parent = nullptr);
    ~InputTP() override;
};

