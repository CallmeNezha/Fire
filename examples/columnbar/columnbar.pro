QT += widgets
TARGET       = columnbar
TEMPLATE     = app
SOURCES     += main.cpp \
               responser.cpp

HEADERS     += responser.h

INCLUDEPATH += ../../fire/include
LIBS        += -L${OBJECTS_DIR}/../../../build -lfire


