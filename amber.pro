#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T19:38:21
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = amber
TEMPLATE = app

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
        main.cpp \
        amber.cpp \
    qcustomplot.cpp \
    check.cpp \
    convert.cpp \
    compile.cpp \
    defargs.cpp \
    hyperlink.cpp \
    statusbox.cpp \

HEADERS += \
        amber.h \
    qcustomplot.h \
    check.h \
    convert.h \
    compile.h \
    defargs.h \
    hyperlink.h \
    statusbox.h \

LIBS += \


FORMS += \
        amber.ui

DISTFILES += \
    documentation \
    iconResources/Untitled.png \
    amberResources/amberLogoBlackAA.png \
    amberResources/icons/githubLogo.png

SUBDIRS += \
    amber.pro

RESOURCES += \
    res.qrc

win32:RC_ICONS += amberResources/icons/amberIcn.ico

QMAKE_LFLAGS += -static



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-amberLib-Desktop_Qt_5_10_0_MinGW_32bit-Release/release/ -lamber_base
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-amberLib-Desktop_Qt_5_10_0_MinGW_32bit-Release/debug/ -lamber_base
else:unix: LIBS += -L$$PWD/../build-amberLib-Desktop_Qt_5_10_0_MinGW_32bit-Release/ -lamber_base

INCLUDEPATH += $$PWD/../amber_base
DEPENDPATH += $$PWD/../amber_base

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-amberLib-Desktop_Qt_5_10_0_MinGW_32bit-Release/release/libamber_base.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-amberLib-Desktop_Qt_5_10_0_MinGW_32bit-Release/debug/libamber_base.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-amberLib-Desktop_Qt_5_10_0_MinGW_32bit-Release/release/amber_base.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-amberLib-Desktop_Qt_5_10_0_MinGW_32bit-Release/debug/amber_base.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-amberLib-Desktop_Qt_5_10_0_MinGW_32bit-Release/libamber_base.a
