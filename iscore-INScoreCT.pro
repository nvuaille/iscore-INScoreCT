#-------------------------------------------------
#
# Project created by QtCreator 2014-05-02T11:27:14
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iscore-INScoreCT
TEMPLATE = app
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -Wno-deprecated-register

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/inscoreobject.cpp \
    src/variable.cpp \
    src/parameter.cpp \
    src/inscoreline.cpp \
    src/maininterface.cpp \
    src/xmldata.cpp \
    src/advancedoptions.cpp \
    src/inscoredata.cpp

HEADERS  += headers/mainwindow.h \
    headers/inscoreobject.h \
    headers/variable.h \
    headers/parameter.h \
    headers/inscoreline.h \
    headers/maininterface.h \
    headers/xmldata.h \
    headers/advancedoptions.h \
    headers/inscoredata.h

FORMS    += forms/mainwindow.ui \
    forms/inscoreline.ui \
    forms/maininterface.ui \
    forms/advancedoptions.ui
