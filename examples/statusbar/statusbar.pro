QT += widgets
TARGET       = statusbar
TEMPLATE     = app
SOURCES     += main.cpp

INCLUDEPATH += ../../fire/include
LIBS        += -L${OBJECTS_DIR}../../fire -lfire




