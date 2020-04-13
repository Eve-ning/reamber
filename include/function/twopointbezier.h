#ifndef TWOPOINTBEZIER_H
#define TWOPOINTBEZIER_H

#include <QWidget>

namespace Ui {
class TwoPointBezier;
}

class TwoPointBezier : public QWidget
{
    Q_OBJECT

public:
    explicit TwoPointBezier(QWidget *parent = nullptr);
    ~TwoPointBezier();

protected:
    QVector<QVector2D> createBezier(double start, double end);
    QVector<QVector2D> createBezier();

private slots:
    void on_y1ms_valueChanged(double arg1);
    void on_x2ms_valueChanged(double arg1);
    void on_y2ms_valueChanged(double arg1);
    void on_x3ms_valueChanged(double arg1);
    void on_y3ms_valueChanged(double arg1);
    void on_y4ms_valueChanged(double arg1);
    void on_x4ms_valueChanged(double arg1);
    void on_x2p_valueChanged(double arg1);
    void on_x3p_valueChanged(double arg1);
    void on_interval_valueChanged(int arg1);

private:
    bool live() const;
    void updatePlot();
    void setCustomPlot(const QVector<double>& x,
                       const QVector<double>& y);
    void setCustomPlot(const QVector<QVector2D>& p);

    void initP();
    QVector<QVector2D> p;
    int interval;
    Ui::TwoPointBezier *ui;

};

#endif // TWOPOINTBEZIER_H
