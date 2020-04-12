#ifndef NORMALIZER_H
#define NORMALIZER_H

#include <QWidget>

namespace Ui {
class Normalizer;
}

class Normalizer : public QWidget
{
    Q_OBJECT

public:
    explicit Normalizer(QWidget *parent = nullptr);
    ~Normalizer();

private:
    Ui::Normalizer *ui;
};

#endif // NORMALIZER_H
