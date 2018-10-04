/********************************************************************************
** Form generated from reading UI file 'dataexchange.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAEXCHANGE_H
#define UI_DATAEXCHANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataExchange
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *mainLabel;
    QCheckBox *autoscroll;
    QListWidget *listWidget;

    void setupUi(QWidget *DataExchange)
    {
        if (DataExchange->objectName().isEmpty())
            DataExchange->setObjectName(QStringLiteral("DataExchange"));
        DataExchange->resize(674, 552);
        verticalLayout_2 = new QVBoxLayout(DataExchange);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(DataExchange);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        mainLabel = new QLabel(widget);
        mainLabel->setObjectName(QStringLiteral("mainLabel"));

        horizontalLayout_2->addWidget(mainLabel);

        autoscroll = new QCheckBox(widget);
        autoscroll->setObjectName(QStringLiteral("autoscroll"));
        autoscroll->setChecked(true);

        horizontalLayout_2->addWidget(autoscroll);


        verticalLayout_2->addWidget(widget);

        listWidget = new QListWidget(DataExchange);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout_2->addWidget(listWidget);


        retranslateUi(DataExchange);

        QMetaObject::connectSlotsByName(DataExchange);
    } // setupUi

    void retranslateUi(QWidget *DataExchange)
    {
        DataExchange->setWindowTitle(QApplication::translate("DataExchange", "Form", nullptr));
        mainLabel->setText(QString());
        autoscroll->setText(QApplication::translate("DataExchange", "\320\220\320\262\321\202\320\276\321\201\320\272\321\200\320\276\320\273\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataExchange: public Ui_DataExchange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAEXCHANGE_H
