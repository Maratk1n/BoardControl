/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionSettings;
    QAction *actionDataExchange;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *graphs;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QScrollArea *helper;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QLabel *helpLabel;
    QGroupBox *bitsIndicate;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *protocolSettings;
    QVBoxLayout *verticalLayout_3;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *hex_select;
    QRadioButton *ascii_select;
    QWidget *horizontalWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *standartProtocol_select;
    QRadioButton *customProtocol_select;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *cycleSend;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpinBox *intervalSpinBox;
    QLabel *label_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *requestLineEdit;
    QCheckBox *crcCheckBox;
    QGroupBox *answerBox;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *anyResp_chBox;
    QWidget *responseWidget;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *dataCount;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuConnect;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(852, 754);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon2);
        actionDataExchange = new QAction(MainWindow);
        actionDataExchange->setObjectName(QStringLiteral("actionDataExchange"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/data-exchange.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDataExchange->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(4, 4, 4, 4);
        graphs = new QTabWidget(centralWidget);
        graphs->setObjectName(QStringLiteral("graphs"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        helper = new QScrollArea(tab);
        helper->setObjectName(QStringLiteral("helper"));
        helper->setWidgetResizable(true);
        helper->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 818, 176));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(6, 6, 6, 6);
        helpLabel = new QLabel(scrollAreaWidgetContents);
        helpLabel->setObjectName(QStringLiteral("helpLabel"));
        helpLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        helpLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_3->addWidget(helpLabel, 0, 0, 1, 1);

        helper->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(helper, 0, 0, 1, 1);

        graphs->addTab(tab, QString());

        verticalLayout_2->addWidget(graphs);

        bitsIndicate = new QGroupBox(centralWidget);
        bitsIndicate->setObjectName(QStringLiteral("bitsIndicate"));
        verticalLayout_7 = new QVBoxLayout(bitsIndicate);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(4, 3, 4, 3);

        verticalLayout_2->addWidget(bitsIndicate);

        protocolSettings = new QGroupBox(centralWidget);
        protocolSettings->setObjectName(QStringLiteral("protocolSettings"));
        protocolSettings->setMinimumSize(QSize(0, 420));
        protocolSettings->setMaximumSize(QSize(16777215, 420));
        verticalLayout_3 = new QVBoxLayout(protocolSettings);
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
        horizontalWidget = new QWidget(protocolSettings);
        horizontalWidget->setObjectName(QStringLiteral("horizontalWidget"));
        horizontalWidget->setMinimumSize(QSize(0, 25));
        horizontalWidget->setMaximumSize(QSize(16777215, 25));
        horizontalLayout = new QHBoxLayout(horizontalWidget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, 4, 4, 4);
        hex_select = new QRadioButton(horizontalWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(hex_select);
        hex_select->setObjectName(QStringLiteral("hex_select"));
        hex_select->setChecked(true);

        horizontalLayout->addWidget(hex_select);

        ascii_select = new QRadioButton(horizontalWidget);
        buttonGroup->addButton(ascii_select);
        ascii_select->setObjectName(QStringLiteral("ascii_select"));

        horizontalLayout->addWidget(ascii_select);


        verticalLayout_3->addWidget(horizontalWidget);

        horizontalWidget_2 = new QWidget(protocolSettings);
        horizontalWidget_2->setObjectName(QStringLiteral("horizontalWidget_2"));
        horizontalWidget_2->setMinimumSize(QSize(0, 25));
        horizontalWidget_2->setMaximumSize(QSize(16777215, 25));
        horizontalLayout_2 = new QHBoxLayout(horizontalWidget_2);
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(4, 4, 4, 4);
        standartProtocol_select = new QRadioButton(horizontalWidget_2);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(standartProtocol_select);
        standartProtocol_select->setObjectName(QStringLiteral("standartProtocol_select"));
        standartProtocol_select->setChecked(true);

        horizontalLayout_2->addWidget(standartProtocol_select);

        customProtocol_select = new QRadioButton(horizontalWidget_2);
        buttonGroup_2->addButton(customProtocol_select);
        customProtocol_select->setObjectName(QStringLiteral("customProtocol_select"));

        horizontalLayout_2->addWidget(customProtocol_select);


        verticalLayout_3->addWidget(horizontalWidget_2);

        groupBox_3 = new QGroupBox(protocolSettings);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 80));
        groupBox_3->setMaximumSize(QSize(16777215, 80));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(4);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        widget = new QWidget(groupBox_3);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(4, 4, 4, 4);
        cycleSend = new QCheckBox(widget);
        cycleSend->setObjectName(QStringLiteral("cycleSend"));
        cycleSend->setChecked(true);

        horizontalLayout_4->addWidget(cycleSend);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        intervalSpinBox = new QSpinBox(widget);
        intervalSpinBox->setObjectName(QStringLiteral("intervalSpinBox"));
        intervalSpinBox->setMinimumSize(QSize(80, 0));
        intervalSpinBox->setMinimum(100);
        intervalSpinBox->setMaximum(1000);
        intervalSpinBox->setValue(333);

        horizontalLayout_4->addWidget(intervalSpinBox);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);


        verticalLayout->addWidget(widget);

        widget_3 = new QWidget(groupBox_3);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_6 = new QHBoxLayout(widget_3);
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(4, 4, 4, 4);
        requestLineEdit = new QLineEdit(widget_3);
        requestLineEdit->setObjectName(QStringLiteral("requestLineEdit"));
        requestLineEdit->setMinimumSize(QSize(0, 20));

        horizontalLayout_6->addWidget(requestLineEdit);

        crcCheckBox = new QCheckBox(widget_3);
        crcCheckBox->setObjectName(QStringLiteral("crcCheckBox"));
        crcCheckBox->setMinimumSize(QSize(0, 20));
        crcCheckBox->setChecked(true);

        horizontalLayout_6->addWidget(crcCheckBox);


        verticalLayout->addWidget(widget_3);


        verticalLayout_3->addWidget(groupBox_3);

        answerBox = new QGroupBox(protocolSettings);
        answerBox->setObjectName(QStringLiteral("answerBox"));
        answerBox->setMinimumSize(QSize(0, 260));
        answerBox->setMaximumSize(QSize(16777215, 260));
        verticalLayout_4 = new QVBoxLayout(answerBox);
        verticalLayout_4->setSpacing(4);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(4, 4, 4, 4);
        anyResp_chBox = new QCheckBox(answerBox);
        anyResp_chBox->setObjectName(QStringLiteral("anyResp_chBox"));

        verticalLayout_4->addWidget(anyResp_chBox);

        responseWidget = new QWidget(answerBox);
        responseWidget->setObjectName(QStringLiteral("responseWidget"));
        verticalLayout_5 = new QVBoxLayout(responseWidget);
        verticalLayout_5->setSpacing(4);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(4, 4, 4, 4);
        widget_2 = new QWidget(responseWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 40));
        widget_2->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_5 = new QHBoxLayout(widget_2);
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(4, 4, 4, 4);
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        dataCount = new QComboBox(widget_2);
        dataCount->setObjectName(QStringLiteral("dataCount"));

        horizontalLayout_5->addWidget(dataCount);


        verticalLayout_5->addWidget(widget_2);

        tableWidget = new QTableWidget(responseWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(0, 170));
        tableWidget->setMaximumSize(QSize(16777215, 170));

        verticalLayout_5->addWidget(tableWidget);


        verticalLayout_4->addWidget(responseWidget);


        verticalLayout_3->addWidget(answerBox);


        verticalLayout_2->addWidget(protocolSettings);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 852, 21));
        menuConnect = new QMenu(menuBar);
        menuConnect->setObjectName(QStringLiteral("menuConnect"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuConnect->menuAction());
        menuBar->addAction(menu->menuAction());
        menuConnect->addAction(actionConnect);
        menuConnect->addAction(actionDisconnect);
        menuConnect->addAction(actionSettings);
        menu->addAction(actionDataExchange);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionSettings);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionDataExchange);
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        graphs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionConnect->setText(QApplication::translate("MainWindow", "Start", nullptr));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", nullptr));
        actionDataExchange->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\274\320\265\320\275 \320\264\320\260\320\275\320\275\321\213\320\274", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDataExchange->setToolTip(QApplication::translate("MainWindow", "\320\236\320\261\320\274\320\265\320\275 \320\264\320\260\320\275\320\275\321\213\320\274\320\270", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionDataExchange->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_NO_SHORTCUT
        helpLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        graphs->setTabText(graphs->indexOf(tab), QApplication::translate("MainWindow", "Help", nullptr));
        bitsIndicate->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\261\320\270\321\202\320\276\320\262\320\260\321\217 \320\270\320\275\320\264\320\270\320\272\320\260\321\206\320\270\321\217 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        protocolSettings->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\277\321\200\320\276\321\202\320\276\320\272\320\276\320\273\320\260", nullptr));
        hex_select->setText(QApplication::translate("MainWindow", "HEX", nullptr));
        ascii_select->setText(QApplication::translate("MainWindow", "ASCII", nullptr));
        standartProtocol_select->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\321\213\320\271 (\320\230\320\267\320\274\320\265\321\200\320\270\321\202\320\265\320\273\321\214)", nullptr));
        customProtocol_select->setText(QApplication::translate("MainWindow", "\320\243\320\275\320\270\320\272\320\260\320\273\321\214\320\275\321\213\320\271", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\200\320\276\321\201", nullptr));
        cycleSend->setText(QApplication::translate("MainWindow", "\320\246\320\270\320\272\320\273\320\270\321\207\320\275\320\260\321\217 \320\276\321\202\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\200\320\262\320\260\320\273:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\274\321\201", nullptr));
        requestLineEdit->setText(QApplication::translate("MainWindow", "AB010300", nullptr));
        crcCheckBox->setText(QApplication::translate("MainWindow", "CRC", nullptr));
        answerBox->setTitle(QApplication::translate("MainWindow", "\320\236\321\202\320\262\320\265\321\202", nullptr));
        anyResp_chBox->setText(QApplication::translate("MainWindow", "\320\233\321\216\320\261\320\276\320\271 \320\276\321\202\320\262\320\265\321\202", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\264\320\260\320\275\320\275\321\213\321\205:", nullptr));
        menuConnect->setTitle(QApplication::translate("MainWindow", "COM port", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\236\320\261\320\274\320\265\320\275 \320\264\320\260\320\275\320\275\321\213\320\274\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
