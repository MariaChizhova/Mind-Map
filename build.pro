QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

SOURCES += src/*
SOURCES += include/*

# C++11
QMAKE_CXX = g++-5
QMAKE_LINK = g++-5
QMAKE_CC = gcc-5
QMAKE_CXXFLAGS += -std=c++11

# Thanks to Qt 
QMAKE_CXXFLAGS += -Wno-unused-variable
