#include "bitmappings.h"
#include <QHBoxLayout>
#include <QDebug>

Circle::Circle(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(24);
}

Circle::~Circle()
{

}

void Circle::setBrush(QBrush brush)
{
    this->brush = brush;
    repaint();
}

void Circle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(brush);
    painter.drawEllipse(QPoint(12, 12), 8, 8);
}



BitMappings::BitMappings(unsigned int id, unsigned int bitsCount, QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(35);
    label.setText(QString("Data %1:\t").arg(id + 1));
    label.setFixedHeight(24);
    label.setAlignment(Qt::AlignLeft);
    QHBoxLayout *layout = new QHBoxLayout(this);
    //layout->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    layout->addWidget(&label);
    layout->setContentsMargins(3, 3, 3, 3);
    bitsCount = bitsCount > 16 ? 0 : bitsCount;
    for (unsigned int i = 0; i < bitsCount; i++) {
        circles.append(new Circle(this)); // widget for circle
        layout->addWidget(circles.last());
    }
    this->setLayout(layout);
}

BitMappings::~BitMappings()
{

}

void BitMappings::setBitArray(const QBitArray &bitArray)
{
    for (int i = 0; i < bitArray.size(); i++) {
        if (circles.size() <= i) return;

        if (bitArray[i]) {
            circles[circles.size() - 1 - i]->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        }
        else {
            circles[circles.size() - 1 - i]->setBrush(QBrush(Qt::magenta, Qt::SolidPattern));
        }
    }
}
