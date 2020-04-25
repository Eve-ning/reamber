#pragma once

#include "io.h"

class HitObjectV;
class QSpinBox;

class InputHO : public IO
{
    Q_OBJECT

public:
    explicit InputHO(QWidget *parent = nullptr);
    ~InputHO() override;

    virtual HitObjectV read() const;
    virtual QVector<double> readOffsets(bool makeUnique) const override;

    QVector<uint> getColumns() const;

};

