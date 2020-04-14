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
    void addPoint(QMouseEvent *event);
    void popPoint();
    void mouseEventHandler(QMouseEvent *event);

    void on_bpmRadio_clicked();
    void on_svRadio_clicked();
    void on_interval_editingFinished();
    void on_vertzoom_valueChanged(int value);
    void on_startOffset_valueChanged(int arg1);
    void on_endOffset_valueChanged(int arg1);
    void on_startValue_valueChanged(double arg1);
    void on_endValue_valueChanged(double arg1);

    void on_updateBoundBtn_clicked();

    static long long binomCoeff(int n, int k);

private:
    bool live() const;
    void updatePlot();
    void setCustomPlot(const QVector<double>& x,
                       const QVector<double>& y);
    void setCustomPlot(const QVector<QVector2D>& p);
    void updatePlotRange(double min, double max);
    double getZoom(double min, double max);

    void useSV();
    void useBPM();

    void initP();

    QVector<QVector2D> p;
    Ui::TwoPointBezier *ui;
    const int ZOOM_DEFAULT = 50;
    const double ZOOM_LIMIT = 10.0;
    const double ZOOM_SV_BUFFER = 2.0;
    const double ZOOM_BPM_BUFFER = 100;
    const int BEZIER_MAX_PTS = 66;
    const int BEZIER_MIN_PTS = 2;
};

#endif // TWOPOINTBEZIER_H
