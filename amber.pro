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
        hyperlink.cpp \
        statusbox.cpp \
        amber_base/info_impl/info.cpp \
        amber_base/obj_impl/hitobject_impl.cpp \
        amber_base/obj_impl/hitobjectlist_impl.cpp \
        amber_base/obj_impl/osumap_impl.cpp \
        amber_base/obj_impl/timingpoint_impl.cpp \
        amber_base/obj_impl/timingpointlist_impl.cpp \
        amber_base/parameters/glbPar_/distance.cpp \
        amber_base/parameters/glbPar_/offset.cpp \
        amber_base/parameters/glbPar_/sampleset.cpp \
        amber_base/parameters/glbPar_/volume.cpp \
        amber_base/parameters/hoPar_/column.cpp \
        amber_base/parameters/hoPar_/keys.cpp \
        amber_base/parameters/hoPar_/notetype.cpp \
        amber_base/parameters/hoPar_/xaxis.cpp \
        amber_base/parameters/hoPar_/yaxis.cpp \
        amber_base/parameters/mapPar_/commonfile.cpp \
        amber_base/parameters/mapPar_/gamemode.cpp \
        amber_base/parameters/tpPar_/hitsoundfile.cpp \
        amber_base/parameters/tpPar_/metronome.cpp \
        amber_base/parameters/tpPar_/samplesetindex.cpp \
        amber_base/parameters/tpPar_/timecode.cpp \
        amber_base/validity/amberexception.cpp \
        amber_base/validity/validobj.cpp \
        amber_base/breakpoint.cpp \
        amber_base/breakpointlist.cpp \
        amber_base/common.cpp \
        amber_base/hitobject.cpp \
        amber_base/hitobjectlist.cpp \
        amber_base/osumap.cpp \
        amber_base/osumapset.cpp \
        amber_base/timingpoint.cpp \
        amber_base/timingpointlist.cpp \
        amber_base/parameters/base_/ambernumber.cpp \
        amber_base/parameters/base_/amberstring.cpp \
    amber_base/parameters/tpPar_/bpm.cpp \
    amber_base/parameters/tpPar_/slidervelocity.cpp


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
        amber_base/info_impl/info.h \
        amber_base/obj_impl/hitobject_impl.h \
        amber_base/obj_impl/hitobjectlist_impl.h \
        amber_base/obj_impl/osumap_impl.h \
        amber_base/obj_impl/timingpoint_impl.h \
        amber_base/obj_impl/timingpointlist_impl.h \
        amber_base/parameters/glbPar_/distance.h \
        amber_base/parameters/glbPar_/offset.h \
        amber_base/parameters/glbPar_/sampleset.h \
        amber_base/parameters/glbPar_/volume.h \
        amber_base/parameters/hoPar_/column.h \
        amber_base/parameters/hoPar_/keys.h \
        amber_base/parameters/hoPar_/notetype.h \
        amber_base/parameters/hoPar_/xaxis.h \
        amber_base/parameters/hoPar_/yaxis.h \
        amber_base/parameters/mapPar_/commonfile.h \
        amber_base/parameters/mapPar_/gamemode.h \
        amber_base/parameters/tpPar_/hitsoundfile.h \
        amber_base/parameters/tpPar_/metronome.h \
        amber_base/parameters/tpPar_/samplesetindex.h \
        amber_base/parameters/tpPar_/timecode.h \
        amber_base/validity/amberexception.h \
        amber_base/validity/validobj.h \
        amber_base/baseclass_inc.h \
        amber_base/breakpoint.h \
        amber_base/breakpointlist.h \
        amber_base/common.h \
        amber_base/hitobject.h \
        amber_base/hitobjectlist.h \
        amber_base/osumap.h \
        amber_base/osumapset.h \
        amber_base/timingpoint.h \
        amber_base/timingpointlist.h \
        amber_base/parameters/base_/ambernumber.h \
        amber_base/parameters/base_/amberstring.h \
    amber_base/parameters/tpPar_/bpm.h \
    amber_base/parameters/tpPar_/slidervelocity.h \
    amber_base/parameters/tpPar_/bpm.h \
    amber_base/parameters/tpPar_/slidervelocity.h


LIBS += \

FORMS += \
        amber.ui

DISTFILES += \
    documentation \
    iconResources/Untitled.png \
    amberResources/amberLogoBlackAA.png \
    amberResources/icons/githubLogo.png \
    debug_copypaste

SUBDIRS += \
    amber.pro

RESOURCES += \
    res.qrc

win32:RC_ICONS += amberResources/icons/amberIcn.ico

QMAKE_LFLAGS += -static

INCLUDEPATH += $$PWD/../amber_base
