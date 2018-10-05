#ifndef BITMAPPINGS_H
#define BITMAPPINGS_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QBitArray>


class Circle : public QWidget
{
    Q_OBJECT
    QBrush brush;
public:
    explicit Circle(QWidget *parent = nullptr);
    ~Circle();
    void setBrush(QBrush brush);
protected:
    void paintEvent(QPaintEvent *event);
};

class BitMappings : public QWidget
{
    Q_OBJECT

    QLabel label;
    QVector<Circle*> circles;
public:
    explicit BitMappings(unsigned int id, unsigned int bitsCount, QWidget *parent = nullptr);
    ~BitMappings();
    void setBitArray(const QBitArray &bitArray);

};

#endif // BITMAPPINGS_H
