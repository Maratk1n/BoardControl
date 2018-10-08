#-------------------------------------------------
#
# Project created by QtCreator 2018-09-22T17:53:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport printsupport

TARGET = BoardControl
TEMPLATE = app
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    protocol.cpp \
    libs/qcustomplot.cpp \
    dataexchange.cpp \
    settingsdialog.cpp \
    graphworker.cpp \
    bitmappings.cpp

HEADERS += \
        mainwindow.h \
    protocol.h \
    libs/qcustomplot.h \
    dataexchange.h \
    settingsdialog.h \
    graphworker.h \
    bitmappings.h \
    uint24.h \
    help.h

FORMS += \
        mainwindow.ui \
    dataexchange.ui \
    settingsdialog.ui

DISTFILES +=

RESOURCES += \
    images.qrc

CONFIG += c++11

win32:RC_ICONS += icon.ico
