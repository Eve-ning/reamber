#ifndef ALTER_H
#define ALTER_H

#include <QWidget>

namespace Ui {
class Alter;
}

class Alter : public QWidget
{
    Q_OBJECT

public:
    explicit Alter(QWidget *parent = nullptr);
    ~Alter();

private:
    Ui::Alter *ui;
};

#endif // ALTER_H
