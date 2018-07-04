#-------------------------------------------------
#
# Project created by QtCreator 2018-05-23T23:15:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeepComputation-Lirads
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
        mainwindow.cpp \
    beziercurve.cpp \
    imageconvertor.cpp \
    liradsdatabase.cpp \
    login.cpp \
    casemanageform.cpp \
    patientdatabase.cpp \
    caseimageform.cpp \
    doctorform.cpp \
    showtableform.cpp

HEADERS += \
        mainwindow.h \
    beziercurve.h \
    imageconvertor.h \
    liradsdatabase.h \
    login.h \
    casemanageform.h \
    patientdatabase.h \
    caseimageform.h \
    doctorform.h \
    showtableform.h

FORMS += \
        mainwindow.ui \
    login.ui \
    casemanageform.ui \
    caseimageform.ui \
    doctorform.ui \
    showtableform.ui

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so

LIBS += -lmysqlclient -lboost_filesystem

RESOURCES += \
    liradsresource.qrc
