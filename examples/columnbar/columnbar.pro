QT += widgets
TARGET       = columnbar
TEMPLATE     = app
SOURCES     += main.cpp \
               responser.cpp

INCLUDEPATH += ../../fire/include
LIBS        += -L${OBJECTS_DIR}../../fire -lfire




