#ifndef GRAPHWORKER_H
#define GRAPHWORKER_H

#include <QWidget>
#include <libs/qcustomplot.h>
#include <QSharedPointer>

template <class T>
struct edge
{
    T min;
    T max;
    T bias() {
        return max - min;
    }
};

template <class Key, class Value>
class GraphData
{
    QVector<Key> xScale;
    QVector<Value> yScale;
    edge<Key> xEdge;
    edge<Value> yEdge;
    Key border = 0;
    const int lastStorageTime = 3600; // sec
    const int defaultWidth = 120; // sec
    int displayWidth = defaultWidth; // sec
    int borderPos = 0; // position in data arrays
    int minPos = 0;
    int maxPos = 0;
public:
    GraphData();
    ~GraphData();
    void appendPoint(const Key &key, const Value &value);
    QVector<Key> &keys();
    QVector<Value> &values();
    edge<Key> getKeyEdge();
    edge<Value> getValueEdge();
    void scroll(int angleDelta);
    void autoScroll();
};


class GraphWorker : public QCustomPlot
{
    Q_OBJECT
    static QLabel *label;
    GraphData<double, double> data_;
    QElapsedTimer timer;
    unsigned int replotInterval = 1;
    unsigned int step = 0;
    QMenu menu;
    QSharedPointer<QCPAxisTickerDateTime> dateTicker{new QCPAxisTickerDateTime};
public:
    explicit GraphWorker(QWidget *parent = nullptr);
    ~GraphWorker();
    static void addLabel(QLabel *lbl);
    void setData(float data);
signals:

public slots:

private slots:
    void mouseMove(QMouseEvent* event);
    void scroll(QWheelEvent* event);
};

#endif // GRAPHWORKER_H
