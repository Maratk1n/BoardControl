#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataexchange.h"
#include "protocol.h"
#include "settingsdialog.h"
#include "graphworker.h"
#include "bitmappings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void dataProcessing();

    void on_actionDataExchange_triggered();

    void on_dataCount_currentIndexChanged(int index);

    void on_anyResp_chBox_toggled(bool checked);

    void on_actionSettings_triggered();

    void on_actionConnect_triggered();

    void on_actionDisconnect_triggered();

    void on_hex_select_toggled(bool checked);

    void on_standartProtocol_select_toggled(bool checked);

    void on_cycleSend_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    DataExchange dataLogger;
    const int dataCount = 8;
    const int rowCount = 4;

    Device *device = nullptr;
    SettingsDialog *settingsDialog;
    Settings portSettings;
    bool anyResponse = false;
    requestType reqType = kHEXStandart;

    QMap<int, GraphWorker*> graphPairs;
    QMap<int, BitMappings*> bitMapper;
};

#endif // MAINWINDOW_H