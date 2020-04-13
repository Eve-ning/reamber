#include "include/function/twopointbezier.h"
#include "ui_twopointbezier.h"
#include "depend/qcustomplot.h"
#include <QVector2D>
#include <QtGlobal>
#include <QMouseEvent>

TwoPointBezier::TwoPointBezier(QWidget *parent) :
    QWidget(parent),
    p(QVector<QVector2D>(2)),
    interval(1000.0),
    ui(new Ui::TwoPointBezier)
{
    ui->setupUi(this);
    ui->customplot->addGraph();
    ui->customplot->addGraph();

    connect(ui->customplot, SIGNAL(doubleClickEvent(QMouseEvent*)),
            this, SLOT(mouseEventHandler(QMouseEvent*)));
    initP();
    updatePlot();
}

TwoPointBezier::~TwoPointBezier()
{
    delete ui;
}



QVector<QVector2D> TwoPointBezier::createBezier(double start, double end) {
    int size = p.size();
    double t = start;

    auto factorial = [](int a) -> long long {
        long long sum = 1;
        for (int i = 2; i <= a; i ++) sum *= i;
        return sum;
    };

    QVector<QVector2D> out;
    QVector<QVector2D> p = QVector<QVector2D>(this->p);
    std::sort(p.begin(), p.end(), [](QVector2D a, QVector2D b){ return a.x() < b.x(); });

    // API to include ends
    for (int step = 1; t < 1.0; step++) {
        double sumX = 0.0;
        double sumY = 0.0;
        for (int n = 0; n < size; n ++) {
            long long coeff = factorial(size - 1) / (factorial(n) * factorial(size - n - 1));
            sumX += coeff * pow(1.0 - t, size - n - 1) * pow(t, n) * double(p[n].x());
            sumY += coeff * pow(1.0 - t, size - n - 1) * pow(t, n) * double(p[n].y());
        }
        out.push_back(QVector2D(float(sumX), float(sumY)));
        t = (interval * step) / (end - start);
    }
    out.push_back(QVector2D(float(end), float(p.last().y())));

    return out;
}

QVector<QVector2D> TwoPointBezier::createBezier() {
    // Automatically sets start and end
    QVector<double> x = QVector<double>();
    for (const auto & i : p) x.push_back(double(i.x()));
    return createBezier(*std::min_element(x.begin(), x.end()),
                        *std::max_element(x.begin(), x.end()));
}

void TwoPointBezier::addPoint(QMouseEvent * event) {
    if (p.size() == 15) return;
    qDebug() << float(ui->customplot->xAxis->pixelToCoord(event->pos().x()));
    qDebug() << float(ui->customplot->yAxis->pixelToCoord(event->pos().y()));
    qDebug() << p.size();
    p.push_back(QVector2D(float(ui->customplot->xAxis->pixelToCoord(event->pos().x())),
                          float(ui->customplot->yAxis->pixelToCoord(event->pos().y()))));
    updatePlot();
}

void TwoPointBezier::popPoint(){
    if (p.size() == 2) return;
    p.pop_back();
    updatePlot();
}

void TwoPointBezier::mouseEventHandler(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        addPoint(event);
    else if (event->button() == Qt::RightButton)
        popPoint();
}

bool TwoPointBezier::live() const {
    return ui->check_live->isChecked();
}

void TwoPointBezier::updatePlot() {
    if (!live()) return;
    auto customplot = ui->customplot;

    // Set Bezier
    auto vec = createBezier();
    QVector<double> x = QVector<double>();
    QVector<double> y = QVector<double>();
    for (auto i : vec){
        x.push_back(double(i.x()));
        y.push_back(double(i.y()));
    }
    customplot->graph(0)->setData(x, y, false);
    auto xMinMax = std::minmax_element(x.begin(), x.end());
    auto yMinMax = std::minmax_element(y.begin(), y.end());
    customplot->xAxis->setRange(*xMinMax.first * 0.9, *xMinMax.second * 1.1);
    customplot->yAxis->setRange(*yMinMax.first * 0.9, *yMinMax.second * 1.1);

    // Set Scatter
    QVector<double> xs = QVector<double>();
    QVector<double> ys = QVector<double>();
    for (auto i : p){
        xs.push_back(double(i.x()));
        ys.push_back(double(i.y()));
    }

    customplot->graph(1)->setData(xs, ys, false);
    customplot->graph(1)->setPen(QColor(50, 50, 50, 120));
    customplot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));


    customplot->replot();

}

void TwoPointBezier::initP()
{
    p[0] = QVector2D(0, 1);
    p[1] = QVector2D(100000, 2);
}

void TwoPointBezier::on_interval_valueChanged(int arg1){ interval = arg1; updatePlot(); }

