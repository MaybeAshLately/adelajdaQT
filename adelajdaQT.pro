QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataTransfer.cpp \
    addnewlist.cpp \
    addnewword.cpp \
    learningmodea.cpp \
    learningmodeb.cpp \
    listcontent.cpp \
    listoptions.cpp \
    listsettings.cpp \
    main.cpp \
    mainwindow.cpp \
    singleword.cpp

HEADERS += \
    DataTransfer.h \
    addnewlist.h \
    addnewword.h \
    learningmodea.h \
    learningmodeb.h \
    listcontent.h \
    listoptions.h \
    listsettings.h \
    mainwindow.h \
    singleword.h

FORMS += \
    addnewlist.ui \
    addnewword.ui \
    learningmodea.ui \
    learningmodeb.ui \
    listcontent.ui \
    listoptions.ui \
    listsettings.ui \
    mainwindow.ui \
    singleword.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    README.md
