#//////////////////////////////////////////
# тестовая работа к занятию https://youtu.be/-adEM8bTaeo
#//////////////////////////////////////////

QT       += core gui widgets

TARGET = ogltest5
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

SOURCES += \
        eye.cpp \
        groupobjects.cpp \
        main.cpp \
        object.cpp \
        oglwidget.cpp \
        skybox.cpp \
        transformational.cpp

HEADERS += \
        eye.h \
        groupobjects.h \
        object.h \
        oglwidget.h \
        skybox.h \
        transformational.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shaders.qrc \
    textures.qrc

win32-g* {
LIBS += -lopengl32
}

win32-msvc* {
LIBS += lopengl32.lib
}
