
#include <QDebug>
#include <QMetaType>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bitsIndicate->hide();

    QLabel *label = new QLabel(this);
    ui->statusBar->addWidget(label);
    GraphWorker::addLabel(label);

    // Формирование таблицы
    QStringList headers;
    for (int i = 0; i < dataCount; i++) {
        headers << QString("Data%1").arg(i + 1);
    }
    ui->tableWidget->setColumnCount(dataCount); // Указываем число колонок
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем заголовки колонок
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "Формат \nданных" << "Инвертированный \nпорядок байт" << "Отрисовывать \nграфик" << "Побитовое \nпредставление");   // Задает имя строк
    /* Выполняем заполнение QTableWidget записями
     * */
    QStringList dataTypes = QStringList() << "uint16_t" << "uint8_t" << "int16_t" << "float";
    for(int i = 0; i < dataCount; i++){
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        // Создаём элемент, который будет выполнять роль чекбокса
        for (int j = 1; j < rowCount; j++) {
            QWidget *checkBoxWidget = new QWidget();
            QCheckBox *checkBox = new QCheckBox();
            QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
            checkBox->setChecked(false);
            //checkBox->setEnabled(false);
            layoutCheckBox->addWidget(checkBox);
            layoutCheckBox->setAlignment(Qt::AlignCenter);
            layoutCheckBox->setContentsMargins(0,0,0,0);
            //ui->tableWidget->setCellWidget(j, i, checkBoxWidget);
            ui->tableWidget->setCellWidget(j, i, checkBox);
        }
        QComboBox* comboBox = new QComboBox();
        comboBox->setEnabled(false);
        comboBox->addItems(dataTypes);
        ui->tableWidget->setCellWidget(0, i, comboBox);
    }
    for (int i = 0; i < dataCount + 1; i++){
        ui->dataCount->addItem(QString::number(i));
    }
    for (int i = 0; i < rowCount; i++){
        ui->tableWidget->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    ui->helpLabel->setText("sdfsf\n"
                           "sdfs\n"
                           "345435\n"
                           "4363\n"
                           "fghfgh\n"
                           "retete\n"
                           "567yhjfgh\n"
                           "dsgfsg3465\n"
                           "sdgfj\n"
                           "636345\n"
                           "sdfs\n"
                           "345435\n"
                           "4363\n"
                           "fghfgh\n"
                           "retete\n"
                           "567yhjfgh\n"
                           "dsgfsg3465\n"
                           "sdgfj\n"
                           "636345\n");

    QTimer::singleShot(1, this, SLOT(on_actionSettings_triggered()));  //вывод окна ввода пользователя поверх главного окна
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dataProcessing()
{
    if (reqType == kHEXStandart) {
        for (auto it : graphPairs.keys()) {
            graphPairs.value(it)->setData(device->getRData(it).toFloat());
        }
        for (auto it : bitMapper.keys()) {
            bitMapper.value(it)->setBitArray(device->getBitArray(it));
        }
    }
}

void MainWindow::on_actionDataExchange_triggered()
{
    dataLogger.show();
}

void MainWindow::on_dataCount_currentIndexChanged(int index)
{
    for (int i = 0; i < dataCount; i++) {
        for (int j = 1; j < rowCount; j++) {
            QCheckBox *checkBox = static_cast<QCheckBox*>(ui->tableWidget->cellWidget(j, i));
            checkBox->setEnabled(false);
        }
        QComboBox *comboBox = static_cast<QComboBox*>(ui->tableWidget->cellWidget(0, i));
        comboBox->setEnabled(false);
    }
    for (int i = 0; i < index; i++) {
        for (int j = 1; j < rowCount; j++) {
            QCheckBox *checkBox = static_cast<QCheckBox*>(ui->tableWidget->cellWidget(j, i));
            checkBox->setEnabled(true);
        }
        QComboBox *comboBox = static_cast<QComboBox*>(ui->tableWidget->cellWidget(0, i));
        comboBox->setEnabled(true);
    }
}


void MainWindow::on_anyResp_chBox_toggled(bool checked)
{
    if (checked) {
        ui->responseWidget->setEnabled(false);
    }
    else {
        ui->responseWidget->setEnabled(true);
    }
}

void MainWindow::on_actionSettings_triggered()
{
    settingsDialog = new SettingsDialog();
    if (settingsDialog->exec()) {
        portSettings = settingsDialog->settings();
    }
    delete settingsDialog;
}

/*
 *
 *      START
 *
 */
void MainWindow::on_actionConnect_triggered()
{
    delete device;

    if (ui->cycleSend->isChecked()) {
        ui->actionConnect->setEnabled(false);
        ui->protocolSettings->setEnabled(false);
        ui->actionSettings->setEnabled(false);
    }

    device = new Device();
    device->setPortSettings(portSettings);

    QByteArray request = QByteArray::fromHex(ui->requestLineEdit->text().toUtf8());

    if (ui->ascii_select->isChecked()) { // ASCII selected
        reqType = kASCII;
    } else { // HEX selected
        if (ui->standartProtocol_select) { // standart IZM protocol
            connect(device, SIGNAL(dataReady()), this, SLOT(dataProcessing()));
            reqType = kHEXStandart;
            if (ui->crcCheckBox->isChecked() && request.size() > 2) {
                uint8_t crc = 0x00;
                for (int i = 1; i < request.size(); i++) {
                    crc -= request.at(i);
                }
                request.append(crc);
            }

            // заполняем входные данные
            for (int i = 0; i < ui->dataCount->currentIndex(); i++) {
                QComboBox *dataType = static_cast<QComboBox*>(ui->tableWidget->cellWidget(0, i));
                QCheckBox *inversion = static_cast<QCheckBox*>(ui->tableWidget->cellWidget(1, i));
                QCheckBox *plot = static_cast<QCheckBox*>(ui->tableWidget->cellWidget(2, i));
                QCheckBox *bitwise = static_cast<QCheckBox*>(ui->tableWidget->cellWidget(3, i));
                device->setRDataType(str2QVariant(dataType->currentText()), inversion->isChecked());
                if (plot->isChecked()) { // plot needed
                    GraphWorker *grW = new GraphWorker(this);
                    ui->graphs->addTab(grW, QString("Data %1").arg(i + 1));
                    graphPairs.insert(i, grW);
                }
                if (bitwise->isChecked()) { // bit representation needed
                    ui->bitsIndicate->show();
                    BitMappings *bM = new BitMappings(i, bitsCount(dataType->currentText()), this);
                    ui->bitsIndicate->layout()->addWidget(bM);
                    // добавляем битовую карту
                    bitMapper.insert(i, bM);
                }
            }
        } else { // custom protocol
            reqType = kHEXCustom;
        }
    }
    device->setReqType(reqType);
    device->setRequest(request);

    unsigned int interval = 0;
    if (ui->cycleSend->isChecked()) {
        if (ui->intervalSpinBox->value() < 100 || ui->intervalSpinBox->value() > 1000) {
            interval = 333;
        }
        else {
            interval = ui->intervalSpinBox->value();
        }
    }
    anyResponse = ui->anyResp_chBox->isChecked();
    device->setAnyResponse(anyResponse);
    device->putLabel(dataLogger.getLabel());
    device->putListWidget(dataLogger.getListWidget());
    device->start(interval);
}

/*
 *
 *      STOP
 *
 */
void MainWindow::on_actionDisconnect_triggered()
{
    if (device) {
        device->stop();
    }

    for (auto it : graphPairs) {
        delete it;
    }
    graphPairs.clear();
    for (auto it : bitMapper) {
        delete it;
    }
    bitMapper.clear();

    ui->actionConnect->setEnabled(true);
    ui->protocolSettings->setEnabled(true);
    ui->actionSettings->setEnabled(true);
    ui->bitsIndicate->hide();
}

void MainWindow::on_hex_select_toggled(bool checked)
{
    if (checked) { // hex
        ui->customProtocol_select->setEnabled(true);
        ui->standartProtocol_select->setEnabled(true);
        ui->standartProtocol_select->setChecked(true);
        ui->requestLineEdit->setText("AB010300");
    } // ascii
    else {
        ui->customProtocol_select->setChecked(true);
        ui->customProtocol_select->setEnabled(false);
        ui->standartProtocol_select->setEnabled(false);
        ui->customProtocol_select->setChecked(true);
        ui->requestLineEdit->setText("dsfskjfsdkjf");
    }
}

void MainWindow::on_standartProtocol_select_toggled(bool checked)
{
    if (checked) { // standart IZM
        ui->crcCheckBox->setEnabled(true);
        ui->answerBox->setEnabled(true);
    }
    else { // custom
        ui->crcCheckBox->setChecked(false);
        ui->crcCheckBox->setEnabled(false);
        ui->answerBox->setEnabled(false);
    }
}

void MainWindow::on_cycleSend_toggled(bool checked)
{
    ui->intervalSpinBox->setEnabled(checked);
}
