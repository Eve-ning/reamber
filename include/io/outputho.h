#pragma once

#include "io.h"

class OutputHO : public IO
{
public:
    Q_OBJECT

    explicit OutputHO(QWidget *parent = nullptr);
    ~OutputHO() override;
};

