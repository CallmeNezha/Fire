QT += widgets
TARGET       = tableview
TEMPLATE     = app
SOURCES     += main.cpp \
               ../../fire/src/widgets/tableview/ntableview.cpp

HEADERS     += ../../fire/include/widgets/ntableview.h

INCLUDEPATH += ../../fire/include

RESOURCES += grades.qrc


