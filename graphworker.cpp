#include "graphworker.h"
#include <QDebug>

QLabel *GraphWorker::label = nullptr;


template<class Key, class Value>
GraphData<Key, Value>::GraphData()
{

}

template<class Key, class Value>
QVector<Key> &GraphData<Key, Value>::keys()
{
    return xScale;
}

template<class Key, class Value>
QVector<Value> &GraphData<Key, Value>::values()
{
    return yScale;
}

template<class Key, class Value>
edge<Key> GraphData<Key, Value>::getKeyEdge()
{
    return xEdge;
}

template<class Key, class Value>
edge<Value> GraphData<Key, Value>::getValueEdge()
{
    return yEdge;
}

template<class Key, class Value>
void GraphData<Key, Value>::scroll(int angleDelta)
{
    if (xScale.isEmpty()) return;
    if (xScale.last() < defaultWidth) return;

    displayWidth += angleDelta / 6; // angleDelta = +-120
    int maxWidth = xScale.last() - xScale.first();
    displayWidth = displayWidth > maxWidth ? maxWidth : displayWidth;
    displayWidth = displayWidth < defaultWidth ? defaultWidth : displayWidth;
}

template<class Key, class Value>
void GraphData<Key, Value>::autoScroll()
{
    displayWidth = defaultWidth;
}

template<class Key, class Value>
void GraphData<Key, Value>::appendPoint(const Key &key, const Value &value)
{
    if (yScale.isEmpty()) {
        yEdge.min = value;
        yEdge.max = value;
        minPos = 0;
        maxPos = 0;
        borderPos = 0;
    }

    xScale.append(key);
    yScale.append(value);

    // calc range of Y scale
    if (value < yEdge.min) {
        yEdge.min = value;
        minPos = xScale.size() - 1;
    }
    if (value > yEdge.max) {
        yEdge.max = value;
        maxPos = xScale.size() - 1;
    }

    // calc range of X scale
    if ((xScale.last() - xScale.at(borderPos)) < displayWidth) { // если надо расширить график
        for ( ; borderPos >= 0; borderPos--) {
            if ((xScale.last() - xScale.first()) < defaultWidth) break;
            if (yScale.at(borderPos) < yEdge.min) {
                yEdge.min = yScale.at(borderPos);
                minPos = borderPos;
            }
            if (yScale.at(borderPos) > yEdge.max) {
                yEdge.max = yScale.at(borderPos);
                maxPos = borderPos;
            }
            if ((xScale.last() - xScale.at(borderPos)) >= displayWidth) break;
        }
    }
    else { // сжать график
        for ( ; borderPos < xScale.size(); borderPos++) {
            if ((xScale.last() - xScale.at(borderPos)) <= displayWidth) break;
        }
        if (borderPos > minPos) { // минимальная точка ушла в небытие
            yEdge.min = yScale.at(borderPos);
            minPos = borderPos;
            for (int i = borderPos; i < yScale.size(); i++) {
                if (yScale.at(i) <= yEdge.min) {
                    yEdge.min = yScale.at(i);
                    minPos = i;
                }
            }
        }
        if (borderPos > maxPos) { // максимальная точка ушла в небытие
            yEdge.max = yScale.at(borderPos);
            maxPos = borderPos;
            for (int i = borderPos; i < yScale.size(); i++) {
                if (yScale.at(i) >= yEdge.max) {
                    yEdge.max = yScale.at(i);
                    maxPos = i;
                }
            }
        }
    }
    xEdge.min = xScale.at(borderPos);
    xEdge.max = xScale.last();

    if ((xScale.last() - xScale.first()) > lastStorageTime) {
        xScale.pop_front();
        minPos--;
        maxPos--;
    }
}

template<class Key, class Value>
GraphData<Key, Value>::~GraphData()
{

}


GraphWorker::GraphWorker(QWidget *parent) : QCustomPlot(parent)
{
    connect(this, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(this, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(scroll(QWheelEvent*)));
    this->addGraph();
    this->xAxis->setLabel("Время, [ч:мин:с]");
    this->yAxis->setLabel("Значение");

    // настройка показа времени на шкале
    dateTicker->setDateTimeSpec(Qt::UTC);
    dateTicker->setDateTimeFormat("H:mm:ss");
    this->xAxis->setTicker(dateTicker);

    QAction *autoscale = new QAction("autoscale", this);
    connect(autoscale, static_cast<void (QAction::*)(bool)>(&QAction::triggered), this, [this](){
        data_.autoScroll();
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

    if (data_.keys().isEmpty()) {
        data_.appendPoint(delta_t, data);
    }
    else {
        data_.appendPoint(data_.keys().last() + delta_t, data);
    }

    this->graph(0)->setData(data_.keys(), data_.values());

    step++;
    if (step > replotInterval) {
        step = 0;

        // set ranges
        this->xAxis->setRange(data_.getKeyEdge().min, data_.getKeyEdge().max);
        this->yAxis->setRange(data_.getValueEdge().min - data_.getValueEdge().bias() * 0.05,
                              data_.getValueEdge().max + data_.getValueEdge().bias() * 0.05);

        this->replot();
    }
}

void GraphWorker::mouseMove(QMouseEvent *event)
{
    if (label != nullptr) {
        double x = this->xAxis->pixelToCoord(event->pos().x());
        double y = this->yAxis->pixelToCoord(event->pos().y());
        label->setText(QString("X: %1 [ч:мин:с],\tY: %2").arg(QDateTime::fromTime_t(x).toUTC().toString("H:mm:ss")).arg(QString::number(y, 'f', 2)));
    }
}

void GraphWorker::scroll(QWheelEvent *event)
{
    data_.scroll(event->angleDelta().ry());
}
