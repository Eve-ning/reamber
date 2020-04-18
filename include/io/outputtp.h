#pragma once

#include "io.h"

class OutputTP : public IO
{
public:
    Q_OBJECT

    explicit OutputTP(QWidget *parent = nullptr);
    ~OutputTP() override;
};

