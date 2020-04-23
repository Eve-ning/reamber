#pragma once

#include "io.h"

class TimingPointV;

class InputTP : public IO
{
    Q_OBJECT

public:
    explicit InputTP(QWidget *parent = nullptr);
    ~InputTP() override;

    TimingPointV read() const;

    QVector<double> readOffsets(bool makeUnique = true) const override;
};

