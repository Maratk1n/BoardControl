#include "graphworker.h"
#include <QDebug>

QLabel *GraphWorker::label = nullptr;

GraphWorker::GraphWorker(QWidget *parent) : QCustomPlot(parent)
{
    connect(this, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(this, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(scroll(QWheelEvent*)));
    this->addGraph();
    this->xAxis->setLabel("Время, [ч:мин]");
    this->yAxis->setLabel("Значение");

    // настройка показа времени на шкале
    dateTicker->setDateTimeSpec(Qt::UTC);
    dateTicker->setDateTimeFormat("H:mm");
    this->xAxis->setTicker(dateTicker);

    QAction *autoscale = new QAction("autoscale", this);
    connect(autoscale, static_cast<void (QAction::*)(bool)>(&QAction::triggered), this, [this](){
        displayWidth = defaultWidth;
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

    delta_t /= 1000; // ms to sec
    //delta_t *= 50;

    if (xScale.isEmpty()) {
        xScale.append(delta_t);
        yMin = data;
        yMax = data;
    }
    else {
        xScale.append(xScale.last() + delta_t);
    }
    yScale.append(data);

    // save just lastStorageTime sec
    if (xScale.last() - xScale.first() > lastStorageTime) {
        xScale.pop_front();
    }

    yMin = data < yMin ? data : yMin;
    yMax = data > yMax ? data : yMax;

//    if (!showHour && xScale.last() > 3590.0) {
//        showHour = true;
//        this->xAxis->setLabel("Время, [ч:мин]");
//        dateTicker->setDateTimeFormat("hh:mm");
//    }

    this->graph(0)->setData(xScale, yScale);
    step++;
    if (step > replotInterval) {
        step = 0;

        // set yAxis range
        float bias = yMax - yMin;
        this->yAxis->setRange(yMin - 0.05*bias, yMax + 0.05*bias);

        // set xAxis range
        if (xScale.last() < defaultWidth) {
            this->xAxis->setRange(xScale.first(), xScale.last());
        }
        else {
            this->xAxis->setRange(xScale.last() - displayWidth, xScale.last());
        }
        this->replot();
    }
}

void GraphWorker::mouseMove(QMouseEvent *event)
{
    if (label != nullptr) {
        double x = this->xAxis->pixelToCoord(event->pos().x());
        double y = this->yAxis->pixelToCoord(event->pos().y());
        label->setText(QString("X: %1 [ч:мин:с],\tY: %2").arg(QDateTime::fromTime_t(x).toUTC().toString("H:mm:ss")).arg(QString::number(y, 'g', 4)));
    }
}

void GraphWorker::scroll(QWheelEvent *event)
{
    if (xScale.isEmpty()) return;
    if (xScale.last() < defaultWidth) return;

    displayWidth += event->angleDelta().ry() / 6; // event->angleDelta().rx() = +-120
    int width = xScale.last() - xScale.first();
    displayWidth = displayWidth > width ? width : displayWidth;
    displayWidth = displayWidth < defaultWidth ? defaultWidth : displayWidth;
}
