#pragma once

#include "io.h"

class OutputEHO : public IO
{
public:
    Q_OBJECT

    explicit OutputEHO(QWidget *parent = nullptr);
    ~OutputEHO() override;
};

