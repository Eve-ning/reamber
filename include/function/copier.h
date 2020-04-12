#ifndef COPIER_H
#define COPIER_H

#include <QWidget>
#include "common.h"

namespace Ui {
class Copier;
}

class Copier : public QWidget, public Common
{
    Q_OBJECT

public:
    explicit Copier(QWidget *parent = nullptr);
    ~Copier();

    QString output() const;

signals:
    void outputChanged();

private slots:
    void on_generate_clicked();
    void on_output_textChanged();

private:
    Ui::Copier *ui;
};

#endif // COPIER_H
