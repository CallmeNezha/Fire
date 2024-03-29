#-------------------------------------------------
#
# Project created by QtCreator 2019-06-07T16:53:25
#
#-------------------------------------------------

QT      += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets
TARGET   = fire
TEMPLATE = lib
CONFIG  += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/widgets/columnbar/ncolbar.cpp \
        src/widgets/statusbar/nstatusbar.cpp \
        src/widgets/tableview/ntableview.cpp \
        src/widgets/tableview/nfindbar.cpp

HEADERS += \
        include/widgets/ncolbar.h \
        include/widgets/nstatusbar.h \
        include/widgets/ntableview.h \
        include/widgets/nfindbar.h

INCLUDEPATH += \
        include

unix {
    target.path = ../build
    INSTALLS += target
}

DESTDIR = ../build
