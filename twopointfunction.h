#ifndef TWOPOINTFUNCTION_H
#define TWOPOINTFUNCTION_H

#include <QWidget>

namespace Ui {
class TwoPointFunction;
}

class TwoPointFunction : public QWidget
{
    Q_OBJECT

public:
    explicit TwoPointFunction(QWidget *parent = nullptr);
    ~TwoPointFunction();

private:
    Ui::TwoPointFunction *ui;
};

#endif // TWOPOINTFUNCTION_H
