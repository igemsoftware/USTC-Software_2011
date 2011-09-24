#-------------------------------------------------
#
# Project created by QtCreator 2011-06-23T16:49:44
#
#-------------------------------------------------

QT       += core gui script scripttools xml xmlpatterns webkit

#LIBS += -lgsl -lgslcblas
#LIBS += -lsbml

CONFIG(debug, debug|release) {
    TARGET = LachesisD
    config += debug
    DEFINES += DEBUG
}

CONFIG(release, debug|release) {
    TARGET = Lachesis
    config += release
}

TEMPLATE = app
DESTDIR = $$PWD/bin

include($$PWD/lib/libs.pri)
include($$PWD/src/designer/Designer.pri)

