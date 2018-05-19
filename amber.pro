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
        archive/check.cpp \
        archive/convert.cpp \
        archive/compile.cpp \
        archive/defargs.cpp \
        hyperlink.cpp \
        statusbox.cpp \
        amber_base/info.cpp \
        amber_base/hitobject.cpp \
        amber_base/timingpoint.cpp \
        amber_base/hitobjectlist.cpp \
        amber_base/timingpointlist.cpp \
        amber_base/osumapset.cpp \
        amber_base/osumap.cpp \
        amber_base/breakpoint.cpp \
        amber_base/breakpointlist.cpp \
        amber_base/common.cpp \
        amber_base/osuobject.cpp \
        aaobj.cpp \
        aaform.cpp


HEADERS += \
        amber.h \
        qcustomplot.h \
        archive/check.h \
        archive/convert.h \
        archive/compile.h \
        archive/defargs.h \
        hyperlink.h \
        statusbox.h \
        amber_base_inc.h \
        amber_base/info.h \
        amber_base/hitobject.h \
        amber_base/timingpoint.h \
        amber_base/hitobjectlist.h \
        amber_base/timingpointlist.h \
        amber_base/osumapset.h \
        amber_base/osumap.h \
        amber_base/breakpoint.h \
        amber_base/breakpointlist.h \
        amber_base/common.h \
        amber_base/osuobject.h \
        aaobj.h \
        aaform.h \
    qabutton.h

LIBS += \

FORMS += \
        amber.ui \
        aaform.ui

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

INCLUDEPATH += $$PWD/../amber_base
