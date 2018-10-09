#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QTimer>
#include <QThread>
#include <QObject>
#include <QElapsedTimer>
#include <QVector>
#include <QVariant>
#include <QLabel>
#include <QListWidget>
#include <QSerialPort>
#include <QMetaType>

class Connector;

struct Settings {
    QString name;
    qint32 baudRate;
    QString stringBaudRate;
    QSerialPort::DataBits dataBits;
    QString stringDataBits;
    QSerialPort::Parity parity;
    QString stringParity;
    QSerialPort::StopBits stopBits;
    QString stringStopBits;
    QSerialPort::FlowControl flowControl;
    QString stringFlowControl;
    bool localEchoEnabled;
};

enum requestType {kHEXStandart, kHEXCustom, kASCII};


//для справки
//typedef unsigned char           uint8_t;  QMetaType::UChar
//                                int8_t;   QMetaType::SChar
//typedef unsigned short          uint16_t; QMetaType::UShort
//typedef unsigned int            uint32_t; QMetaType::UInt
//                                int32_t;  QMetaType::Int
//                                int16_t;  QMetaType::Short
//typedef unsigned long int       uint64_t;

QVariant str2QVariant(const QString &type);
unsigned int bitsCount(const QString &type);

class Device : public QObject {
    Q_OBJECT

    QByteArray request;
    QByteArray response;
    QVector<QVariant> r_data;
    QVector<QBitArray> r_bitsArray;
    QVector<bool> r_inverse; // обратный порядок байт
    requestType reqType = kHEXStandart;
    Settings portSettings;
    QLabel *label = nullptr;
    QListWidget *listWidget = nullptr;
    int maxWidgetSize = 200;
    Connector *connector = nullptr;
    QThread *thread = nullptr;
    size_t totalSize = 0;
    bool anyResponse = false;
    const size_t byteSize = 8; //bits
    bool dataOk = false;
public:
    Device(QObject *parent = 0);
    ~Device();
    void setRDataType(QVariant dataType, bool inverted);
    void setRequest(const QByteArray& request);
    void setRequest(const QString& request);
    void setReqType(requestType reqType);
    void setPortSettings(const Settings &portSettings);
    void setAnyResponse(bool anyResponse);
    void putLabel(QLabel *label);
    void putListWidget(QListWidget *listWidget);
    void start(unsigned int interval = 0);
    void stop();
    QByteArray getResponse();
    QVariant getRData(unsigned int id);
    requestType getReqType();
    QBitArray getBitArray(unsigned int id);
    bool isDataOk() const;
private slots:
    void addLog(const QString &text, bool labelUpdate = false, bool timeStamp = true);
    void packageAnalysis();
signals:
    void stopAll();
    void dataReady();
};

class Connector : public QObject {
    Q_OBJECT
    unsigned int interval = 0;
    requestType reqType = kHEXStandart;
    QByteArray request;
    QByteArray response;
    bool responseOk = false;
    QTimer *timer = nullptr;
    QSerialPort *serialPort = nullptr;
    Settings portSettings;
    void setPortParams(const Settings &settings);
    bool crcCheck(const QByteArray &data);
    bool lengthCheck(const QByteArray &data);
    bool openPort();
    void closePort();
    quint64 write2Port(const QByteArray &data);
public:
    Connector(const Settings &portSettings, QObject *parent = 0);
    ~Connector();
    void setInterval(unsigned int interval);
    void setReqType(requestType reqType);
    void setRequest(QByteArray request);
    QByteArray getResponse(bool *ok = nullptr);
public slots:
    void start();
    void stop();
private slots:
    void process();
signals:
    void finished();
    void dataReady();
    void addLog(const QString &text, bool labelUpdate = false, bool timeStamp = true);
};

#endif // PROTOCOL_H
