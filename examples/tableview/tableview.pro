QT += widgets
TARGET       = tableview
TEMPLATE     = app
SOURCES     += main.cpp \
               ../../fire/src/widgets/tableview/ntableview.cpp \
               ../../fire/src/widgets/tableview/nfindbar.cpp \
               ../../fire/src/widgets/tableview/nfilterbar.cpp \
               ../../fire/src/widgets/tableview/nsortfilterproxymodel.cpp \
               ../../fire/src/widgets/tableview/window.cpp

HEADERS     += ../../fire/include/widgets/ntableview.h \
               ../../fire/include/widgets/nfindbar.h \
               ../../fire/include/widgets/nfilterbar.h \
               ../../fire/include/widgets/nsortfilterproxymodel.h \
               ../../fire/include/widgets/window.h


INCLUDEPATH += ../../fire/include

RESOURCES += grades.qrc


