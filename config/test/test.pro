#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T17:12:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
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

INCLUDEPATH += /home/michal/includes

#LIBS += /home/michal/VTK-Release-build/lib/*.so

#INCLUDEPATH += /home/michal/VTK/GUISupport/Qt \
#                /home/michal/VTK-Release-build/GUISupport/Qt \
#                /home/michal/VTK-Release-build/Rendering/Core \
#                /home/michal/VTK-Release-build/Filters/Core \
#                /home/michal/VTK-Release-build/Rendering/OpenGL2 \
#                /home/michal/VTK/Common/Core \
#                /home/michal/VTK-Release-build/Common/Core \
#                /home/michal/VTK-Release-build/Utilities/KWIML \
#                /home/michal/VTK/Utilities/KWIML \
#                /home/michal/VTK/Rendering/Core

SOURCES += \
        main.cpp \
        mainwindow.cpp

LIBS += -L"/home/michal/VTK-Release-build/lib/" -libQVTKWidgetPlugin -libvtkGUISupportQt-9.0

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
