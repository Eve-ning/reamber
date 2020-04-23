#pragma once

#include "outputho.h"

class OutputEHO : public OutputHO
{
    Q_OBJECT

public:
    explicit OutputEHO(QWidget *parent = nullptr);
    ~OutputEHO() override;

    // Not implemented yet in reamber_base
    QVector<double> readOffsets(bool makeUnique = true) const override;
};

