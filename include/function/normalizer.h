#ifndef NORMALIZER_H
#define NORMALIZER_H

#include <QWidget>
#include "common.h"

class QListWidgetItem;

namespace Ui {
class Normalizer;
}

class Normalizer : public QWidget, public Common
{
    Q_OBJECT

public:
    explicit Normalizer(QWidget *parent = nullptr);
    ~Normalizer();
    QString output() const;
signals:
    void outputChanged();

private slots:
    void on_generate_clicked();
    void on_bpmlist_itemClicked(QListWidgetItem *item);

    void on_output_textChanged();

private:
    Ui::Normalizer *ui;
};

#endif // NORMALIZER_H
