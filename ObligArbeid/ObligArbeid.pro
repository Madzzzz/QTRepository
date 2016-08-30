#If Qt 5.3 and 5.4 use this
equals(QT_MINOR_VERSION, 3): QMAKE_CXXFLAGS += -std=c++11
equals(QT_MINOR_VERSION, 4): QMAKE_CXXFLAGS += -std=c++11
#If Qt 5.5 use this:
greaterThan(QT_MINOR_VERSION, 4): CONFIG += c++11

TARGET = ObligArbeid
TEMPLATE = app

QT += opengl
QT += core gui widgets opengl

SOURCES += main.cpp \
    displayobject.cpp \
    fil.cpp \
    glwidget.cpp \
    mainwindow.cpp \
    shaderprogram.cpp \
    syntakshighlighter.cpp \
    vertex.cpp \
    sosipunkter.cpp \
    sosikurver.cpp

HEADERS += \
    displayobject.h \
    fil.h \
    glwidget.h \
    mainwindow.h \
    qopenglfunctions.h \
    shaderprogram.h \
    syntakshighlighter.h \
    vec3.h \
    vertex.h \
    sosipunkter.h \
    sosikurver.h

