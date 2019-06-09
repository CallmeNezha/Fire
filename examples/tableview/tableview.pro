QT += widgets
TARGET       = tableview
TEMPLATE     = app
SOURCES     += main.cpp \
               ../../fire/src/widgets/tableview/ntableview.cpp \
               ../../fire/src/widgets/tableview/nfindbar.cpp

HEADERS     += ../../fire/include/widgets/ntableview.h \
               ../../fire/include/widgets/nfindbar.h


INCLUDEPATH += ../../fire/include

RESOURCES += grades.qrc


