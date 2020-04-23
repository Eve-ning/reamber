#pragma once

#include "io.h"

class HitObjectV;

class OutputHO : public IO
{
    Q_OBJECT

public:
    explicit OutputHO(QWidget *parent = nullptr);
    ~OutputHO() override;

    void write(const HitObjectV & hoV);

    QVector<double> readOffsets(bool makeUnique = true) const override;
};

