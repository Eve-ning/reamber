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
        amber_base/com_ho.cpp \
        amber_base/com_tp.cpp \
        amber_base/com_holist.cpp \
        amber_base/com_tplist.cpp \
        amber_base/com_mapset.cpp \
        amber_base/com_map.cpp \
        amber_base/com_breakp.cpp \
        amber_base/com_breakplist.cpp \
        amber_base/com_math.cpp \
        amber_base/com_common.cpp \
        aaobj.cpp \
        aaform.cpp \
    qabutton.cpp


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
        amber_base/com_ho.h \
        amber_base/com_tp.h \
        amber_base/com_holist.h \
        amber_base/com_tplist.h \
        amber_base/com_mapset.h \
        amber_base/com_map.h \
        amber_base/com_breakp.h \
        amber_base/com_breakplist.h \
        amber_base/com_math.h \
        amber_base/com_common.h \
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
