#-------------------------------------------------
#
# Project created by QtCreator 2018-07-27T23:25:40
#
#-------------------------------------------------

QT       += core gui

CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SymCalculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calculator.cpp \
    ../tree.cpp \
    ../symbolTable.cpp \
    ../store.cpp \
    ../scanner.cpp \
    ../parser.cpp \
    ../hashTable.cpp \
    ../functionTable.cpp \
    ../commandParser.cpp \
    symbollistitem.cpp

HEADERS  += mainwindow.h \
    calculator.h \
    ../tree.h \
    ../symbolTable.h \
    ../strbuf.h \
    ../store.h \
    ../serialize.h \
    ../scanner.h \
    ../parser.h \
    ../Params.h \
    ../list.h \
    ../idSeq.h \
    ../hashTable.h \
    ../functionTable.h \
    ../commandParser.h \
    ../Calculator.h \
    symbollistitem.h

FORMS    += mainwindow.ui
