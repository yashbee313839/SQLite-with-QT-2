#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T10:38:53
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLite
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
