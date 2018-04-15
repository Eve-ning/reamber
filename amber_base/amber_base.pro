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
    com_ho.cpp \
    com_tp.cpp \
    com_holist.cpp \
    com_tplist.cpp \
    com_mapset.cpp \
    com_map.cpp \
    com_breakp.cpp \
    com_breakplist.cpp \
    com_math.cpp \
    com_common.cpp

HEADERS += \
    com_ho.h \
    com_tp.h \
    com_holist.h \
    com_tplist.h \
    com_mapset.h \
    com_mapset.h \
    com_map.h \
    com_breakp.h \
    com_breakplist.h \
    com_math.h \
    com_common.h

DISTFILES += \
    documentation.txt
