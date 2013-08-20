#-------------------------------------------------
#
# Project created by QtCreator 2013-08-16T11:42:51
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Range
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    preferencesdialog.cpp \
    editdialog.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h \
    editdialog.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    editdialog.ui

RESOURCES += \
    rc.qrc
