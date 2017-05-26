#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T20:18:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = radna
TEMPLATE = app


SOURCES += main.cpp\
    predmet.cpp \
    vreme.cpp \
    predmetqt.cpp \
    mainwindow.cpp \
    obavezaqt.cpp \
    provjera_obavezaqt.cpp \
    provjera_sajtovaqt.cpp

HEADERS  += \
    predmet.h \
    vreme.h \
    predmetqt.h \
    mainwindow.h \
    obavezaqt.h \
    provjera_obavezaqt.h \
    provjera_sajtovaqt.h

FORMS    += \
    predmetqt.ui \
    mainwindow.ui \
    obavezaqt.ui \
    provjera_obavezaqt.ui \
    provjera_sajtovaqt.ui
