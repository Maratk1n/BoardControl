#include "dataexchange.h"
#include "ui_dataexchange.h"

DataExchange::DataExchange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataExchange)
{
    ui->setupUi(this);
    connect(ui->listWidget->model(), SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(autoscroll()));
    this->setAttribute(Qt::WA_QuitOnClose, false);
}

DataExchange::~DataExchange()
{
    delete ui;
}

QLabel *DataExchange::getLabel()
{
    return ui->mainLabel;
}

QListWidget *DataExchange::getListWidget()
{
    return ui->listWidget;
}

void DataExchange::autoscroll()
{
    if (ui->autoscroll->isChecked()) {
        ui->listWidget->scrollToBottom();
    }
}
