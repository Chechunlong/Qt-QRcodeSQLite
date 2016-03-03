#-------------------------------------------------
#
# Project created by QtCreator 2016-02-28T11:16:14
#
#-------------------------------------------------

QT       += core gui sql axcontainer serialport xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRcodeSql
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlui.cpp \
    duplicate.cpp \
    formaterror.cpp \
    numbererror.cpp \
    sqlsetup.cpp \
    inputpwd.cpp \
    serial.cpp \
    serialsetup.cpp \
    firstuse.cpp \
    help.cpp \
    inputarg.cpp

HEADERS  += mainwindow.h \
    sqlui.h \
    duplicate.h \
    formaterror.h \
    numbererror.h \
    sqlsetup.h \
    inputpwd.h \
    serial.h \
    serialsetup.h \
    firstuse.h \
    help.h \
    inputarg.h

FORMS    += mainwindow.ui \
    sqlui.ui \
    duplicate.ui \
    formaterror.ui \
    numbererror.ui \
    sqlsetup.ui \
    inputpwd.ui \
    serialsetup.ui \
    firstuse.ui \
    help.ui \
    inputarg.ui

RESOURCES += \
    icontopleft.qrc

DISTFILES +=

RC_FILE = myapp.rc
