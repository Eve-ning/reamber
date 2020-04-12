#ifndef STUTTER_H
#define STUTTER_H

#include <QWidget>

namespace Ui {
class Stutter;
}

class Stutter : public QWidget
{
    Q_OBJECT

public:
    explicit Stutter(QWidget *parent = nullptr);
    ~Stutter();

private:
    Ui::Stutter *ui;
};

#endif // STUTTER_H
