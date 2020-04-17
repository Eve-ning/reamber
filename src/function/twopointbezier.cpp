#include "include/function/twopointbezier.h"
#include "ui_twopointbezier.h"
#include "include/common.h"
#include "depend/QCustomPlot.h"
#include "algorithm/algorithm.h"
#include <QVector2D>
#include <QtGlobal>
#include <QMouseEvent>

TwoPointBezier::TwoPointBezier(QWidget *parent) :
    QWidget(parent),
    bezierPts(QVector<QVector2D>(0)),
    anchorPts(QVector<QVector2D>(2)),
    ui(new Ui::TwoPointBezier) {
    ui->setupUi(this);
    ui->customPlot->addGraph(); // For the function
    ui->customPlot->addGraph(); // For the bezier
    ui->customPlot->addGraph(); // For the anchor

    // Connects the double click event
    connect(ui->customPlot, SIGNAL   (removeEvent(QVector2D)),
            this,           SLOT     (removePoint(QVector2D)));
    connect(ui->customPlot, SIGNAL(addAnchorEvent(QVector2D)),
            this,           SLOT       (addAnchor(QVector2D)));
    connect(ui->customPlot, SIGNAL(addBezierEvent(QVector2D)),
            this,           SLOT       (addBezier(QVector2D)));

    // Activate SV
    useSV();
    resetButtonSettings();
    plot();
}

TwoPointBezier::~TwoPointBezier() {
    delete ui;
}

QVector<QVector2D> TwoPointBezier::createPlot() {
    auto anchorPtsCopy = Common::sortByX(anchorPts);

    QVector<QVector2D> points;
    // For each anchor pair
    for (auto anchorI = anchorPtsCopy.begin();
         anchorI < (anchorPtsCopy.end() - 1); anchorI ++) {

        QVector<QVector2D> bezierPtsFilter;
        bezierPtsFilter.push_back(*anchorI);
        bezierPtsFilter.push_back(*(anchorI + 1));

        std::copy_if(bezierPts.begin(), bezierPts.end(), std::back_inserter(bezierPtsFilter),
                     [anchorI](const QVector2D & p) {
            return p.x() >= anchorI->x() &&
                   p.x() < (anchorI + 1)->x();
        });

        if (bezierPtsFilter.size() == 66) bezierPts.pop_back();

        points.append(createBezier(bezierPtsFilter, ui->interval->value(), true));
        // We remove the ends if it's not at the end
        if (anchorI + 2 != anchorPtsCopy.end()) points.pop_back();
    }

    return points;
}

void TwoPointBezier::plot() {
    plotFunction();
    plotAnchor();
    plotBezier();
}
void TwoPointBezier::plotFunction() {
    auto customPlot = ui->customPlot;

    // Set Bezier Function
    auto vec = createPlot();
    plotAverage(vec);
    QVector<double> x = QVector<double>();
    QVector<double> y = QVector<double>();

    for (auto i : vec){
        x.push_back(double(i.x()));
        y.push_back(double(i.y()));
    }

    customPlot->graph(0)->setData(x, y, false);
    // Set color based on SV or BPM
    customPlot->graph(0)->setPen(ui->svRadio->isChecked() ?
                                 Common::Color::GREEN : Common::Color::RED);

    // Update range
    auto xMinMax = std::minmax_element(x.begin(), x.end());
    auto yMinMax = std::minmax_element(y.begin(), y.end());
    // qDebug() << *xMinMax.first << "," << *xMinMax.second;
    updatePlotDomain(*xMinMax.first,*xMinMax.second);
    updatePlotRange(*yMinMax.first, *yMinMax.second);
}
void TwoPointBezier::plotBezier()
{
    auto customPlot = ui->customPlot;

    // Set Bezier Points
    QVector<double> xs = QVector<double>();
    QVector<double> ys = QVector<double>();
    for (auto i : bezierPts){
        xs.push_back(double(i.x()));
        ys.push_back(double(i.y()));
    }

    customPlot->graph(1)->setData(xs, ys, false);
    customPlot->graph(1)->setPen(Common::Color::PURPLE);
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusCircle, 5));
    customPlot->replot();
}
void TwoPointBezier::plotAnchor()
{
    auto customPlot = ui->customPlot;

    // Set Bezier Points
    QVector<double> xs = QVector<double>();
    QVector<double> ys = QVector<double>();
    for (auto i : anchorPts){
        xs.push_back(double(i.x()));
        ys.push_back(double(i.y()));
    }

    customPlot->graph(2)->setData(xs, ys, false);
    customPlot->graph(2)->setPen(Common::ColorFade::BLUE);
    customPlot->graph(2)->setLineStyle(QCPGraph::lsImpulse);
    customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangleInverted, 5));
    customPlot->replot();
}
void TwoPointBezier::plotAverage(QVector<QVector2D> & pts)
{
    double sum = 0.0;
    bool isBpm = ui->bpmRadio->isChecked();
    for (int i = 0; i < (pts.size() - 1); i ++)
        sum += Common::clipValue(double(pts[i].y()),isBpm) * (double(pts[i + 1].x()) - double(pts[i].x()));
    double average = sum / (ui->endOffset->value() - ui->startOffset->value());

    ui->averageLabel->setText(QString("Average: %1x").arg(QString::number(average, 'f', 2)));
}

void TwoPointBezier::updatePlotRange(double min, double max){
    // Zoom from 10 % to 1000 %
    double mean = (max - min) / 2 + min;

    // This calculates zoom, zoom [0.1, 10.0]
    double zoom = pow(ZOOM_LIMIT, - double(ui->vertZoom->value() - ZOOM_DEFAULT) / ZOOM_DEFAULT);
    ui->vertZoomLabel->setText(QString::number(1.0 / zoom, 'f', 2) + "x");

    // Normalizes the range and multiplies the ends respectively
    // A buffer is used to prevent too small of a range

    double minRange;
    double maxRange;
    if (ui->svRadio->isChecked()){
        minRange = (min - mean - ZOOM_SV_BUFFER) * zoom + mean;
        maxRange = (max - mean + ZOOM_SV_BUFFER) * zoom + mean;
    } else {
        minRange = (min - mean - ZOOM_BPM_BUFFER) * zoom + mean;
        maxRange = (max - mean + ZOOM_BPM_BUFFER) * zoom + mean;
    }

    // Allow negative for easier bezier bending
    //    minRange = minRange < 0 ? 0 : minRange;
    //    if (ui->svRadio->isChecked())
    //        maxRange = maxRange > Common::SV_MAX ? Common::SV_MAX : maxRange;

    ui->customPlot->yAxis->setRange(minRange, maxRange);
}
void TwoPointBezier::updatePlotDomain(double min, double max) {
    ui->customPlot->xAxis->setRange(min, max);
}

void TwoPointBezier::useSV() {
    ui->startValue->setValue(Common::SV_DEFAULT);
    ui->startValue->setRange(Common::SV_MIN, Common::SV_MAX);
    ui->startValue->setSuffix(Common::Suffix::SV);
    ui->startValue->setSingleStep(Common::SV_STEPSIZE);
    ui->endValue  ->setValue(Common::SV_DEFAULT);
    ui->endValue  ->setRange(Common::SV_MIN, Common::SV_MAX);
    ui->endValue  ->setSuffix(Common::Suffix::SV);
    ui->endValue  ->setSingleStep(Common::SV_STEPSIZE);
}
void TwoPointBezier::useBPM() {
    ui->startValue->setRange(Common::BPM_MIN, Common::BPM_MAX);
    ui->startValue->setValue(Common::BPM_DEFAULT);
    ui->startValue->setSuffix(Common::Suffix::BPM);
    ui->startValue->setSingleStep(Common::BPM_STEPSIZE);
    ui->endValue  ->setRange(Common::BPM_MIN, Common::BPM_MAX);
    ui->endValue  ->setValue(Common::BPM_DEFAULT);
    ui->endValue  ->setSuffix(Common::Suffix::BPM);
    ui->endValue  ->setSingleStep(Common::BPM_STEPSIZE);
}
void TwoPointBezier::resetButtonSettings() {
    // resetButton p
    ui->startOffset->setRange(int(Common::OFFSET_MIN), int(Common::OFFSET_MAX));
    ui->startOffset->setValue(0);
    ui->endOffset  ->setRange(int(Common::OFFSET_MIN), int(Common::OFFSET_MAX));
    ui->endOffset  ->setValue(int(Common::OFFSET_INTERVAL_DEFAULT) * 100);

    anchorPts = QVector<QVector2D>(2);
    anchorPts[0] = {float(ui->startOffset->value()),
                    float(ui->startValue->value())};
    anchorPts[1] = {float(ui->endOffset->value()),
                    float(ui->endValue->value())};
    bezierPts = QVector<QVector2D>();
}

QVector<QVector2D> TwoPointBezier::createBezier(QVector<QVector2D> points, double start, double end, double interval, bool includeEnd) {
    int size = points.size();

    QVector<QVector2D> out;
    std::sort(points.begin(), points.end(),
              [](QVector2D a, QVector2D b){ return a.x() < b.x(); });

    // API to include ends
    double t = 0;
    for (int step = 1; t < 1.0; step++) {
        double sumX = 0.0;
        double sumY = 0.0;
        for (int n = 0; n < size; n ++) {
            long long coeff = binomCoeff(size - 1, n);
            sumX += coeff * pow(1.0 - t, size - n - 1) * pow(t, n) * (double(points[n].x()) - start);
            sumY += coeff * pow(1.0 - t, size - n - 1) * pow(t, n) * double(points[n].y());
        }
        out.push_back(QVector2D(float(sumX + start), float(sumY)));
        t = (interval * step) / (end - start);
    }
    if (includeEnd) out.push_back(QVector2D(float(end), float(points.last().y())));

    return out;
}
QVector<QVector2D> TwoPointBezier::createBezier(const QVector<QVector2D>& points, int interval, bool includeEnd) {
    QVector<double> x = QVector<double>();
    for (const auto & i : points) x.push_back(double(i.x()));
    return createBezier(points,
                        *std::min_element(x.begin(), x.end()),
                        *std::max_element(x.begin(), x.end()),
                        interval,
                        includeEnd);
}

long long TwoPointBezier::binomCoeff(int n, int k) {
    // defined as n! / k! (n-k)!
    // We find if k or n-k is larger

    // e.g. 15 C 5
    //       n   k

    //    15!
    // --------  = 15 * 14 * ... * 11 / (5!) = 15 / 5 * 14 / 4 ... 11 / 1
    // 5! * 10!    We don't evaluate 15!

    int n_k = n - k;
    long double result = 1;
    int smaller = n_k < k ? n_k : k; // find the smaller number
    while (smaller >= 1) {
        result *= static_cast<long double>(double(n) / double(smaller));
        n--;
        smaller--;
    }
    return static_cast<long long>(result);
}
QString TwoPointBezier::generateButtonCode(const QVector<double> & offsets,
                                     const QVector<double> & values,
                                     bool isBPM){
    TimingPointV tpV = TimingPointV();
    if (offsets.size() != values.size()){
        qDebug() << "offsets and values must be of the same size";
        return "";
    }
    int size = offsets.size();

    TimingPoint tp = TimingPoint();
    for (int i = 0; i < size; i ++) {
        tp.loadParameters(offsets[i], values[i], isBPM);
        tpV.pushBack(tp);
    }
    return tpV.getStringRaw();
}

void TwoPointBezier::addAnchor(QVector2D pos) {
    if (pos.x() > ui->endOffset->value() || pos.x() < ui->startOffset->value()) return; // Reject x out of bounds
    anchorPts.push_back(pos);
    plot();
}
void TwoPointBezier::addBezier(QVector2D pos) {
    if (pos.x() > ui->endOffset->value() || pos.x() < ui->startOffset->value()) return; // Reject x out of bounds
    bezierPts.push_back(pos);
    plot();
}
void TwoPointBezier::removePoint(QVector2D pos) {
    auto allPts = anchorPts + bezierPts;
    allPts.removeFirst();
    allPts.removeFirst(); // Don't remove the main anchors

    if (allPts.empty()) return;

    float min = std::numeric_limits<float>::max();
    QVector2D minV = allPts[0];
    for (auto pt : allPts){
        QVector2D ptPixels;
        // Recieved pos is in pixels
        ptPixels.setX(float(ui->customPlot->xAxis->coordToPixel(double(pt.x()))));
        ptPixels.setY(float(ui->customPlot->yAxis->coordToPixel(double(pt.y()))));

        // Compare distance in pixels
        auto dist = (pos - ptPixels).length();

        // If smaller, we set
        if (dist < min) {
            min = dist;
            minV = pt;
        }
    }
    // don't remove if too far
    if (double(min) > REMOVE_DISTANCE_MAX) return;
    if (!anchorPts.removeOne(minV)) // Don't need to execute both
        bezierPts.removeOne(minV);

    plot();
}

QVector2D TwoPointBezier::getMousePos() {
    auto x = float(ui->customPlot->xAxis->pixelToCoord(ui->customPlot->cursor().pos().x()));
    auto y = float(ui->customPlot->yAxis->pixelToCoord(ui->customPlot->cursor().pos().y()));
    return QVector2D(x, y);
}

void TwoPointBezier::on_generateButton_clicked() {
    auto bez = createPlot();
    QVector<double> offsets = QVector<double>();
    QVector<double> values  = QVector<double>();
    bool isBpm = ui->bpmRadio->isChecked();
    for (const auto & bezI : bez) {
        offsets.push_back(double(bezI.x()));
        values.push_back(Common::clipValue(double(bezI.y()), isBpm));
    }
    ui->output->setPlainText(generateButtonCode(offsets, values, ui->bpmRadio->isChecked()));
}
void TwoPointBezier::on_vertZoom_valueChanged(int value){ plot(); }
void TwoPointBezier::on_bpmRadio_clicked() {
    resetButtonSettings();
    useBPM();
    plot();
}
void TwoPointBezier::on_svRadio_clicked() {
    resetButtonSettings();
    useSV();
    plot();
}
void TwoPointBezier::on_startOffset_valueChanged(int arg1) {
    if (arg1 >= ui->endOffset->value()) return;
    anchorPts[0].setX(float(arg1));
    plot();
}
void TwoPointBezier::on_endOffset_valueChanged(int arg1) {
    if (arg1 <= ui->startOffset->value()) return;
    anchorPts[1].setX(float(arg1));
    plot();
}
void TwoPointBezier::on_startValue_valueChanged(double arg1) {
    anchorPts[0].setY(float(arg1));
    plot();
}
void TwoPointBezier::on_endValue_valueChanged(double arg1) {
    anchorPts[1].setY(float(arg1));
    plot();
}
void TwoPointBezier::on_updateBoundBtn_clicked() {
    QString text = ui->updateBound->text();
    HitObjectV hoV = HitObjectV();
    if (!hoV.loadEditor(text)) return;
    resetButtonSettings();
    if (hoV[0].getOffset() > ui->startOffset->value()) {
        ui->endOffset->setValue(int(hoV[1].getOffset()));
        ui->startOffset->setValue(int(hoV[0].getOffset()));
    } else {
        ui->startOffset->setValue(int(hoV[0].getOffset()));
        ui->endOffset->setValue(int(hoV[1].getOffset()));
    }
}
void TwoPointBezier::on_interval_editingFinished() {
    plot();
}
void TwoPointBezier::on_resetButton_clicked(){
    resetButtonSettings();
}
