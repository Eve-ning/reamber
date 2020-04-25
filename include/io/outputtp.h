#pragma once

#include "io.h"

class OutputTP : public IO
{
    Q_OBJECT

public:
    explicit OutputTP(QWidget *parent = nullptr);
    ~OutputTP() override;

    void write(const TimingPointV & tpV);

    QVector<double> readOffsets(bool makeUnique = true) const override;
};

