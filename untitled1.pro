#-------------------------------------------------
#
# Project created by QtCreator 2022-09-08T14:36:24
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT+=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
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
    check.cpp \
    connectsql.cpp \
    dialog.cpp \
    login.cpp \
    look.cpp \
    love.cpp \
        main.cpp \
    mainwindow.cpp \
    search.cpp \
    statusframe.cpp \
    submit.cpp \
    to_examine.cpp

HEADERS += \
    check.h \
    connectsql.h \
    dialog.h \
    login.h \
    look.h \
    love.h \
    mainwindow.h \
    search.h \
    statusframe.h \
    submit.h \
    to_examine.h

FORMS += \
    check.ui \
    dialog.ui \
    login.ui \
    look.ui \
    love.ui \
    mainwindow.ui \
    search.ui \
    statusframe.ui \
    submit.ui \
    to_examine.ui

DISTFILES += \
    README.md \
    background.png \
    untitled1.pro.user \
    untitled1.pro.user.4.8-pre1 \
    wust.png

RESOURCES += \
    es.qrc
