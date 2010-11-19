#-------------------------------------------------
#
# Project created by QtCreator 2010-11-18T02:32:04
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = zmqirclog
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    zmqirclog.cpp

HEADERS += \
    zmqirclog.h

target.path = $$(HOME)/bin

INCLUDEPATH += $$(HOME)/include

LIBS += -L/$$(HOME)/lib -ltravlrsutils

OTHER_FILES += \
    rst/source/conf.py \
    rst/source/index.rst
