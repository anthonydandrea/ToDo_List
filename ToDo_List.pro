#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T18:54:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToDo_List
TEMPLATE = app


SOURCES += main.cpp \
    todolist.cpp \
    item.cpp

HEADERS  += \
    todolist.h \
    item.h

FORMS    += mainwindow.ui
