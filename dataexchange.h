#ifndef DATAEXCHANGE_H
#define DATAEXCHANGE_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>

namespace Ui {
class DataExchange;
}

class DataExchange : public QWidget
{
    Q_OBJECT
    Ui::DataExchange *ui;
public:
    explicit DataExchange(QWidget *parent = 0);
    ~DataExchange();
    QLabel *getLabel();
    QListWidget *getListWidget();
private slots:
    void autoscroll();
};

#endif // DATAEXCHANGE_H
