QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../modules/calculate.c \
    ../modules/financial_mode.c \
    ../modules/parcer.c \
    ../modules/service_funcs.c \
    ../modules/stack.c \
    finance_window.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../modules/smart_calc.h \
    finance_window.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    finance_window.ui \
    graph.ui \
    mainwindow.ui

QT += printsupport

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
