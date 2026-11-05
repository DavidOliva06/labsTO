QT       += core
QT       -= gui

CONFIG   += console c++17
CONFIG   -= app_bundle

TARGET   = DistanciasHilos
TEMPLATE = app

SOURCES  += main.cpp

RESOURCES += recursos.qrc

DISTFILES += distancias_manhattan_euclides.csv
