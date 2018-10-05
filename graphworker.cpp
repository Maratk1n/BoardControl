#include "graphworker.h"
#include <QDebug>

QLabel *GraphWorker::label = nullptr;

GraphWorker::GraphWorker(QWidget *parent) : QCustomPlot(parent)
{
    connect(this, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    this->addGraph();
    this->xAxis->setLabel("Время, [мин]");
    this->yAxis->setLabel("Значение");
    this->xAxis->setRange(0, 30); // 30 min

    QAction *autoscale = new QAction("autoscale", this);
    connect(autoscale, static_cast<void (QAction::*)(bool)>(&QAction::triggered), this, [this](){
        qDebug() << "autoscale";
    });
    menu.addAction(autoscale);
    connect(this, static_cast<void (QCustomPlot::*)(QMouseEvent*)>(&QCustomPlot::mousePress), this, [this](QMouseEvent* event){
        if (event->button() == Qt::RightButton){
            menu.exec(event->globalPos());
        }
    });

    QPen pen = this->graph(0)->pen();
    pen.setWidth(1);
    this->graph(0)->setPen(pen);

    timer.start();
}

GraphWorker::~GraphWorker()
{

}

void GraphWorker::addLabel(QLabel *lbl)
{
    label = lbl;
}

void GraphWorker::setData(float data)
{
    float delta_t = (float)timer.restart();
    if (delta_t > 1000.0f) {
        delta_t = 0.0f;
    }

    delta_t /= 1000 * 60; // ms to min

    if (xScale.isEmpty()) {
        xScale.append(delta_t);
        yMin = data;
        yMax = data;
    }
    else {
        xScale.append(xScale.last() + delta_t);
    }
    yScale.append(data);

    yMin = data < yMin ? data : yMin;
    yMax = data > yMax ? data : yMax;

    this->graph(0)->setData(xScale, yScale);
    step++;
    if (step > replotInterval) {
        step = 0;
        float bias = yMax - yMin;
        this->yAxis->setRange(yMin - 0.05*bias, yMax + 0.05*bias);
        this->replot();
    }
}

void GraphWorker::mouseMove(QMouseEvent *event)
{
    if (label != nullptr) {
        double x = this->xAxis->pixelToCoord(event->pos().x());
        double y = this->yAxis->pixelToCoord(event->pos().y());
        label->setText(QString("X: %1,\tY: %2").arg(QString::number(x, 'g', 2)).arg(QString::number(y, 'g', 2)));
    }
}
