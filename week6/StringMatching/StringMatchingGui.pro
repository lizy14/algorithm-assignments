#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T10:19:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StringMatchingGui
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    GuiMain.cpp \
    BF.cpp \
    BM.cpp \
    KMP.cpp \
    timing.cpp

HEADERS  += mainwindow.h \
    matching.h \
    timing.h

FORMS    += mainwindow.ui
