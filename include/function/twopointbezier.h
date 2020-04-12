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
    QVector<QVector2D> createBezier(const QVector<double>& x,
                                    const QVector<double>& y,
                                    double start, double end, double interval);
    QVector<QVector2D> createBezier(const QVector<double>& x,
                                    const QVector<double>& y,
                                    double interval);
    QVector<QVector2D> createBezier(const QVector<QVector2D>& p,
                                    double start, double end, double interval);
    QVector<QVector2D> createBezier(const QVector<QVector2D>& p,
                                    double interval);

    void setCustomPlot(const QVector<double>& x,
                       const QVector<double>& y);
    void setCustomPlot(const QVector<QVector2D>& p);
private:
    Ui::TwoPointBezier *ui;
};

#endif // TWOPOINTBEZIER_H
