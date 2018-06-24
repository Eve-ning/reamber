QT       += core gui printsupport

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    hitobject.cpp \
    timingpoint.cpp \
    hitobjectlist.cpp \
    timingpointlist.cpp \
    osumapset.cpp \
    osumap.cpp \
    breakpoint.cpp \
    breakpointlist.cpp \
    common.cpp \
    info_impl/info.cpp \
    parameters/glbPar_/offset.cpp \
    parameters/glbPar_/sampleset.cpp \
    parameters/glbPar_/volume.cpp \
    parameters/hoPar_/keys.cpp \
    parameters/hoPar_/yaxis.cpp \
    parameters/hoPar_/column.cpp \
    parameters/hoPar_/notetype.cpp \
    parameters/tpPar_/slidervelocity.cpp \
    parameters/tpPar_/bpm.cpp \
    parameters/tpPar_/metronome.cpp \
    parameters/tpPar_/timecode.cpp \
    parameters/tpPar_/samplesetindex.cpp \
    parameters/tpPar_/hitsoundfile.cpp \
    parameters/hoPar_/xaxis.cpp \
    parameters/parBase_/parbase.cpp \
    parameters/parBase_/parbase_n.cpp \
    parameters/parBase_/parbase_s.cpp \
    obj_impl/hitobject_impl.cpp \
    obj_impl/timingpoint_impl.cpp \
    obj_impl/osumap_impl.cpp \
    validity/validobj.cpp \
    validity/amberexception.cpp \
    parameters/mapPar_/commonfile.cpp \
    obj_impl/hitobjectlist_impl.cpp \
    obj_impl/timingpointlist_impl.cpp \
    parameters/mapPar_/gamemode.cpp \
    parameters/glbPar_/distance.cpp



HEADERS += \
    hitobject.h \
    timingpoint.h \
    hitobjectlist.h \
    timingpointlist.h \
    osumapset.h \
    osumap.h \
    breakpoint.h \
    breakpointlist.h \
    common.h \
    parameters/glbPar_/offset.h \
    parameters/glbPar_/sampleset.h \
    parameters/glbPar_/volume.h \
    parameters/hoPar_/notetype.h \
    parameters/hoPar_/column.h \
    parameters/hoPar_/keys.h \
    parameters/hoPar_/xaxis.h \
    parameters/hoPar_/yaxis.h \
    parameters/parBase_/parbase.h \
    parameters/parBase_/parbase_n.h \
    parameters/parBase_/parbase_s.h \
    parameters/tpPar_/timecode.h \
    parameters/tpPar_/samplesetindex.h \
    parameters/tpPar_/hitsoundfile.h \
    parameters/tpPar_/slidervelocity.h \
    parameters/tpPar_/bpm.h \
    parameters/tpPar_/metronome.h \
    parameters/mapPar_/commonfile.h \
    baseclass_inc.h \
    obj_impl/hitobject_impl.h \
    obj_impl/timingpoint_impl.h \
    obj_impl/osumap_impl.h \
    validity/validobj.h \
    validity/amberexception.h \
    info_impl/info.h \
    obj_impl/hitobjectlist_impl.h \
    obj_impl/timingpointlist_impl.h \
    parameters/mapPar_/gamemode.h \
    parameters/glbPar_/distance.h

DISTFILES += \
    documentation.txt
