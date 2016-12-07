#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T14:09:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GitGood
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classmetrics.cpp \
    cmultilinedcomment.cpp \
    codeanalyzer.cpp \
    commentmetrics.cpp \
    cppmultilinedcomment.cpp \
    DSString.cpp \
    filefind.cpp \
    filemetrics.cpp \
    halsteadmetrics.cpp \
    linemetrics.cpp \
    variablemetrics.cpp

HEADERS  += mainwindow.h \
    AVLTree.h \
    classmetrics.h \
    cmultilinedcomment.h \
    codeanalyzer.h \
    commentmetrics.h \
    cppmultilinedcomment.h \
    DSHashtable.h \
    DSString.h \
    filefind.h \
    filemetrics.h \
    halsteadmetrics.h \
    linemetrics.h \
    variablemetrics.h \
    Vector.h

FORMS    += mainwindow.ui

DISTFILES += \
    GitGood.pro.user

QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
    resources.qrc \
    resources.qrc
