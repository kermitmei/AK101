######################################################################
# Automatically generated by qmake (2.01a) Sun Oct 2 22:10:29 2011
######################################################################

TEMPLATE = app
TARGET = test
DEPENDPATH += . pics
INCLUDEPATH += .

QT += xml network


# Input
FORMS += MainWindow.ui
RESOURCES += pics/pixmaps.qrc

HEADERS += MainWindow.h    \
           MemberArray.h   \  
           MemberModel.h   \
           SubmitManager.h

SOURCES += main.cpp        \
           MainWindow.cpp  \
           MemberArray.cpp \
           MemberModel.cpp \
           SubmitManager.cpp
