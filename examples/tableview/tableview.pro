QT += widgets
TARGET       = tableview
TEMPLATE     = app
SOURCES     += main.cpp

INCLUDEPATH += ../../fire/include
LIBS        += -L${OBJECTS_DIR}/../../../build -lfire

RESOURCES += grades.qrc


