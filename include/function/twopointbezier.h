#ifndef TWOPOINTBEZIER_H
#define TWOPOINTBEZIER_H

#include <QWidget>
#include "common.h"
#include <QVector2D>

class TimingPointV;

namespace Ui {
class TwoPointBezier;
}

class TwoPointBezier : public QWidget, public Common
{
    Q_OBJECT

public:
    explicit TwoPointBezier(QWidget *parent = nullptr);
    ~TwoPointBezier();

    // Creates a bezier vector with explicit start and ends
    static QVector<QVector2D> createBezier(QVector<QVector2D> points, double start, double end, double interval, bool includeEnd = true);
    // Creates a bezier vector with implicit start and ends calculated by min max of points
    static QVector<QVector2D> createBezier(const QVector<QVector2D> &points, int interval, bool includeEnd = true);

    QString output() const;

signals:
    void outputChanged();

private slots:
    void on_bpmRadio_clicked();
    void on_svRadio_clicked();
    void on_interval_editingFinished();
    void on_vertZoom_valueChanged(int value);
    void on_startOffset_valueChanged(int arg1);
    void on_endOffset_valueChanged(int arg1);
    void on_startValue_valueChanged(double arg1);
    void on_endValue_valueChanged(double arg1);
    void on_updateBoundBtn_clicked();
    void on_generateButton_clicked();
    void on_resetButton_clicked();
    void on_output_textChanged();

    static long long binomCoeff(int n, int k);

    void addAnchor  (QVector2D pos); // A and B will add points
    void addBezier  (QVector2D pos); // Right click removes nearest point
    void removePoint(QVector2D pos);

private:
    void initToolTips();

    TimingPointV generateCode(const QVector<double> & offsets,
                              const QVector<double> & values,
                              bool isBPM);

    QVector<QVector2D> createPlot();

    void plot();         // Plots Everything
    void plotFunction(); // Plots the Function
    void plotBezier();   // Plots the Bezier Points only
    void plotAnchor();   // Plots the Anchor Points only

    void warning(); // Warns the user if the Interval is too small for bezier generation

    void updateAverage(QVector<QVector2D> & pts); // Updates the Average Value Label

    void updatePlotRange(double min, double max); // Different from updatePlotDomain
    void updatePlotDomain(double min, double max);

    void useSV();  // Switch to SV mode
    void useBPM(); // Switch to BPM mode

    void resetSettings(); // Resets all settings

    QVector<QVector2D> bezierPts;
    QVector<QVector2D> anchorPts;
    Ui::TwoPointBezier *ui;

    const int    ZOOM_DEFAULT        = 50;
    const double ZOOM_LIMIT          = 10.0;
    const double ZOOM_SV_BUFFER      = 2.0;
    const double ZOOM_BPM_BUFFER     = 100;
    const int    BEZIER_MAX_PTS      = 66;
    const int    BEZIER_MIN_PTS      = 2;
    const double REMOVE_DISTANCE_MAX = 35;
};

#endif // TWOPOINTBEZIER_H
