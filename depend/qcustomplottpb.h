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
    void doubleClickEvent(QMouseEvent * event);
    void addAnchorEvent();
    void addBezierEvent();
    void removeEvent();

};

#endif // QCUSTOMPLOTMOUSE_H
