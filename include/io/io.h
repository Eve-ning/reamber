#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>

class TimingPointV;
class HitObjectV;

namespace Ui {
class IOWidget;
}

class IO : public QWidget
{
    Q_OBJECT

public:
    explicit IO(QWidget *parent = nullptr);
    ~IO();

    QString toPlainText() const;
    QLayout* getLayout() const;

signals:
    void textChanged(QString);

private slots:
    void on_text_textChanged();

private:
    Ui::IOWidget *ui;
};

#endif // INPUTWIDGET_H
