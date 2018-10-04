#ifndef GRAPHWORKER_H
#define GRAPHWORKER_H

#include <QWidget>
#include <libs/qcustomplot.h>

class GraphWorker : public QCustomPlot
{
    Q_OBJECT
    static QLabel *label;
    QVector<double> xScale;
    QVector<double> yScale;
    QElapsedTimer timer;
    unsigned int replotInterval = 1;
    unsigned int step = 0;
    QMenu menu;
    float yMax = 0.0;
    float yMin = 0.0;
public:
    explicit GraphWorker(QWidget *parent = nullptr);
    ~GraphWorker();
    static void addLabel(QLabel *lbl);
    void setData(float data);
signals:

public slots:

private slots:
    void mouseMove(QMouseEvent* event);
};

#endif // GRAPHWORKER_H
