#include "protocol.h"
#include <QDebug>
#define REQATTEMPTS     4
#define WAITFORREADY    100

#include <QSize>
#include <QMetaType>
#include <QTextCodec>
#include <QScrollBar>
#include <QDateTime>

QVariant str2QVariant(const QString &type)
{
    if (QString("uint8_t") == type) {
        return QVariant(QMetaType::UChar, nullptr);
    }
    else if (QString("uint16_t") == type) {
        return QVariant(QMetaType::UShort, nullptr);
    }
    else if (QString("int16_t") == type) {
        return QVariant(QMetaType::Short, nullptr);
    }
    else if (QString("float") == type) {
        return QVariant(QMetaType::Float, nullptr);
    }
    return QVariant(QMetaType::UChar, nullptr);
}

Device::Device(QObject *parent) : QObject(parent)
{

}

Device::~Device()
{
    stop();
}

void Device::setRDataType(QVariant dataType, bool inverted)
{
    if (reqType == kHEXStandart) {
        switch (static_cast<QMetaType::Type>(dataType.type())) {
        case QMetaType::UChar: { //uint8_t
            totalSize += sizeof(uint8_t);
            break;
        }
        case QMetaType::UShort: { //uint16_t
            totalSize += sizeof(uint16_t);
            break;
        }
        case QMetaType::Short: { //int16_t
            totalSize += sizeof(int16_t);
            break;
        }
        case QMetaType::Float:{ //float
            totalSize += sizeof(float);
            break;
        }
        default:
            break;
        }
    }
    r_data.append(dataType);
    r_inverse.append(inverted);
}

void Device::setRequest(const QByteArray &request)
{
    this->request = request;
}

void Device::setRequest(const QString &request)
{
    reqType = kASCII;
    this->request = request.toUtf8();
}

void Device::setReqType(requestType reqType)
{
    this->reqType = reqType;
}

void Device::setPortSettings(const Settings &portSettings)
{
    this->portSettings = portSettings;
}

void Device::setAnyResponse(bool anyResponse)
{
    this->anyResponse = anyResponse;
}

void Device::putLabel(QLabel *label)
{
    this->label = label;
}

void Device::putListWidget(QListWidget *listWidget)
{
    this->listWidget = listWidget;
}

void Device::start(unsigned int interval)
{
    interval = interval > 1000 ? 1000 : interval;
    connector = new Connector(portSettings);
    connector->setInterval(interval);
    connector->setReqType(reqType);
    connector->setRequest(request);
    thread = new QThread();
    connector->moveToThread(thread);

    connect(thread, SIGNAL(started()), connector, SLOT(start()));
    connect(connector, SIGNAL(finished()), thread, SLOT(quit()));
    connect(this, SIGNAL(stopAll()), connector, SLOT(stop()));
    connect(connector, SIGNAL(finished()), connector, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(connector, SIGNAL(addLog(QString,bool,bool)), this, SLOT(addLog(QString,bool,bool)));
    connect(connector, SIGNAL(dataReady()), this, SLOT(packageAnalysis()));

    thread->start();
}

void Device::stop()
{
    emit stopAll();
}

QByteArray Device::getResponse()
{
    return response;
}

QVariant Device::getRData(unsigned int id)
{
    if ((unsigned int)r_data.size() > id){
        return r_data[id];
    }
    return QVariant();
}

requestType Device::getReqType()
{
    return reqType;
}

void Device::addLog(const QString &text, bool labelUpdate, bool timeStamp)
{
    QString log;
    if (timeStamp) {
        log = QDateTime::currentDateTime().toString("hh:mm:ss.z");
        log += ":\t";
        log += text;
    }
    else {
        log = text;
    }


    if (labelUpdate && label != nullptr) {
        label->setText(text);
    }
    if (listWidget != nullptr) {
        if (listWidget->count() > maxWidgetSize){
            delete listWidget->takeItem(0);
        }
        listWidget->addItem(log);
    }
}

void Device::packageAnalysis()
{
    if (connector == nullptr) return;
    bool ok = false;
    response = connector->getResponse(&ok);

    if (reqType == kHEXStandart && ok && !anyResponse) {
        if ((totalSize + 5) != static_cast<unsigned int>(response.size())) {
            addLog("\tНеверно настроен ответ платы", false, false);
            return;
        }
        QString dataText = "\t";
        int currentPos = 4; //текущая позиция в посылке
        for (int i = 0; i < r_data.size(); i++){    // проход по всем ожидаемым входным данным
            // создаем массив байтов для текущего типа
            uint8_t array[QMetaType::sizeOf(r_data[i].type())];
            if (r_inverse[i]) { // если инверсный порядок байт
                for (int k = sizeof(array) - 1; k >= 0; k--){
                    array[k] = response[currentPos++];
                }
            }
            else { // прямой порядок байт
                for (unsigned int k = 0; k < sizeof(array); k++){
                    array[k] = response[currentPos++];
                }
            }

            switch (static_cast<QMetaType::Type>(r_data[i].type())) {
            case QMetaType::UChar: { //uint8_t
                uint8_t data;
                memcpy(&data, array, sizeof(array));
                r_data[i] = QVariant::fromValue(data);
                dataText += QString("Data%1: %2; ").arg(i+1).arg(r_data[i].toUInt());
                break;
            }
            case QMetaType::UShort: { //uint16_t
                uint16_t data;
                memcpy(&data, array, sizeof(array));
                r_data[i] = QVariant::fromValue(data);
                dataText += QString("Data%1: %2; ").arg(i+1).arg(r_data[i].toUInt());
                break;
            }
            case QMetaType::Short: { //int16_t
                int16_t data;
                memcpy(&data, array, sizeof(array));
                r_data[i] = QVariant::fromValue(data);
                dataText += QString("Data%1: %2; ").arg(i+1).arg(r_data[i].toInt());
                break;
            }
            case QMetaType::Float:{ //float
                float data;
                memcpy(&data, array, sizeof(array));
                r_data[i] = QVariant::fromValue(data);
                dataText += QString("Data%1: %2; ").arg(i+1).arg(QString::number(r_data[i].toFloat(), 'g', 2));
                break;
            }
            default:{
                break;
            }
            }
        }
        addLog(dataText, false, false);
    }

    emit dataReady();
}

/* ****************************************
 *          Класс для работы с COM портом
 * ************************************* */
Connector::Connector(const Settings &portSettings, QObject *parent) : QObject(parent), portSettings(portSettings)
{

}

Connector::~Connector()
{
    delete timer;
    delete serialPort;
}

void Connector::setPortParams(const Settings &settings)
{
    if (serialPort == nullptr) return;
    serialPort->setPortName(settings.name);
    serialPort->setBaudRate(settings.baudRate);
    serialPort->setDataBits(settings.dataBits);
    serialPort->setParity(settings.parity);
    serialPort->setStopBits(settings.stopBits);
    serialPort->setFlowControl(settings.flowControl);
}

bool Connector::crcCheck(const QByteArray &data)
{
    if (data.isEmpty() || !lengthCheck(data))
        return false;
    quint8 crcResult = 0x00;
    quint8 crcData = data[data.size() - 1];
    for(int i = 1; i < data.size() - 1; i++)
    {
        crcResult -= data[i];
    }
    return ((crcData == crcResult) && !data.isEmpty());
}

bool Connector::lengthCheck(const QByteArray &data)
{
    if ((data.size() > 3) && (data.size() == (data[3]+5))){
        return true;
    }
    return false;
}

bool Connector::openPort()
{
    if (serialPort != nullptr) {
        bool open = serialPort->open(QIODevice::ReadWrite);
        if (open) {
            emit addLog(QString("Порт '%1' открыт").arg(serialPort->portName()), true);
            emit addLog("", false, false);
            return true;
        }
        else {
            emit addLog(QString("Не удалось открыть порт '%1'").arg(serialPort->portName()), true);
            emit addLog("", false, false);
            return false;
        }
    }
    return false;
}

void Connector::closePort()
{
    if (serialPort != nullptr) {
        serialPort->close();
        emit addLog(QString("Порт '%1' закрыт").arg(serialPort->portName()), true);
        emit addLog("", false, false);
    }
}

quint64 Connector::write2Port(const QByteArray &data)
{
    if (serialPort != nullptr) {
        if (serialPort->isOpen()) {
            quint64 bytes = serialPort->write(data);
            QByteArray req = data.mid(0, bytes);
            QString text;
            for (int i = 0; i < req.size(); i++) {
                text += req.mid(i, 1).toHex().toUpper();
                text += " ";
            }
            text.chop(1);
            emit addLog(QString("Запрос: '%1'").arg(text));
            return bytes;
        }
        else {
            emit addLog(QString("Запрос: порт '%1' не открыт").arg(serialPort->portName()));
            return quint64(0);
        }
    }
    else {
        emit addLog(QString("Запрос: Объект порта не создался"));
        return quint64(0);
    }
}

void Connector::setInterval(unsigned int interval)
{
    this->interval = interval;
}

void Connector::setReqType(requestType reqType)
{
    this->reqType = reqType;
}

void Connector::setRequest(QByteArray request)
{
    this->request = request;
}

QByteArray Connector::getResponse(bool *ok)
{
    *ok = responseOk;
    return response;
}

void Connector::start()
{
    if (serialPort == nullptr) {
        serialPort = new QSerialPort;
    }
    setPortParams(portSettings);
    serialPort->moveToThread(this->thread());
    openPort();
    if (timer == nullptr) {
        timer = new QTimer;
    }
    timer->moveToThread(this->thread());
    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    connect(this, SIGNAL(finished()), serialPort, SLOT(deleteLater()));
    connect(this, SIGNAL(finished()), timer, SLOT(deleteLater()));
    timer->start(interval);
}

void Connector::process()
{
    write2Port(request);
    response.clear();
    while (serialPort->isOpen() && serialPort->waitForReadyRead(WAITFORREADY)) {
        response += serialPort->readAll();
        if ((reqType == kHEXStandart) && crcCheck(response)) { // нашли посылку IZM
            break;
        }
    }

    if (serialPort->isOpen()) {
        if (response.isEmpty()) {
            emit addLog(QString("TIMEOUT"));
            responseOk = false;
            emit dataReady();
        }
        else {
            if (reqType == kASCII) {
                emit addLog(QString("Ответ: '%1'").arg(QString::fromStdString(std::string(response.constData(), response.length()))));
                responseOk = true;
                emit dataReady();
            }
            else {
                QString text;
                for (int i = 0; i < response.size(); i++) {
                    text += response.mid(i, 1).toHex().toUpper();
                    text += " ";
                }
                text.chop(1);
                if (reqType == kHEXStandart && !crcCheck(response)) {
                    emit addLog(QString("Ответ: '%1' (Неполный ответ)").arg(text));
                    responseOk = false;
                }
                else {
                    emit addLog(QString("Ответ: '%1'").arg(text));
                    responseOk = true;
                }
                emit dataReady();
            }
        }
    }
    emit addLog("", false, false);

    if (timer->interval() == 0) {
        stop();
    }
}

void Connector::stop()
{
    closePort();
    emit finished();
}
