#include "bitmappings.h"
#include <QHBoxLayout>
#include <QDebug>
//#include <qapplication.h>

Circle::Circle(unsigned int id, QWidget *parent) : QLabel(parent)
{
    this->id = id;
    setFixedSize(20, 20);
    setAlignment(Qt::AlignCenter);
    setText(QString("%1").arg(id));
    //qApp->processEvents();
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
    painter.drawEllipse(QPoint(10, 10), 9, 9);
}



BitMappings::BitMappings(unsigned int id, unsigned int bitsCount, QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(22);
    label.setText(QString("Data %1:\t").arg(id + 1));
    label.setFixedHeight(20);
    label.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->setAlignment(Qt::AlignVCenter);
    //layout->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    layout->addWidget(&label);
    layout->setContentsMargins(1, 1, 1, 1);
    layout->addItem(new QSpacerItem(0, 18, QSizePolicy::Expanding, QSizePolicy::Fixed));
    for (int i = bitsCount - 1; i >= 0; i--) {
        circles.append(new Circle(i, this)); // widget for circle
        layout->addWidget(circles.last());
        layout->addItem(new QSpacerItem(0, 18, QSizePolicy::Expanding, QSizePolicy::Fixed));
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
