#ifndef QCUSTOMPLOTMOUSE_H
#define QCUSTOMPLOTMOUSE_H

#include "depend/qcustomplot.h"

class QCustomPlotTPB : public QCustomPlot
{
public:
    Q_OBJECT

    public:
    explicit QCustomPlotTPB(QWidget* parent = nullptr);

    ~QCustomPlotTPB() override;

    void mousePressEvent(QMouseEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;



protected:
signals:
    void addAnchorEvent(QVector2D pos);
    void addBezierEvent(QVector2D pos);
    void removeEvent   (QVector2D pos);

};

#endif // QCUSTOMPLOTMOUSE_H
