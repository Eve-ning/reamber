#ifndef COPIER_H
#define COPIER_H

#include <QWidget>

namespace Ui {
class Copier;
}

class Copier : public QWidget
{
    Q_OBJECT

public:
    explicit Copier(QWidget *parent = nullptr);
    ~Copier();

private:
    Ui::Copier *ui;
};

#endif // COPIER_H
