#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22T12:01:26
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reamber
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
    src/common.cpp \
    src/function/alter.cpp \
    src/function/copier.cpp \
    src/function/stutter.cpp \
    src/function/normalizer.cpp \
    src/function/twopointfunction.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    depend/qcustomplot.cpp

HEADERS += \
    include/common.h \
    include/function/alter.h \
    include/function/copier.h \
    include/function/normalizer.h \
    include/function/stutter.h \
    include/function/twopointfunction.h \
    include/mainwindow.h \
    depend/qcustomplot.h

FORMS += \
    ui/alter.ui \
    ui/copier.ui \
    ui/normalizer.ui \
    ui/stutter.ui \
    ui/twopointfunction.ui \
    ui/mainwindow.ui \
    ui/stutter.ui

DISTFILES += \
    src/README.md \
    src/naming_conventions

RESOURCES += \
    rsc.qrc

RC_ICONS = rsc/amber.ico


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/Debug/ -lreamber_base
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/debug/ -lreamber_base
else:unix: LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/ -lreamber_base

INCLUDEPATH += \
$$PWD/../reamber_base/include \
$$PWD/include
DEPENDPATH += $$PWD/../reamber_base/include
