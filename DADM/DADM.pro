#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T17:36:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DADM
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
           dadm.cpp \
           mri.cpp \
           visualization3d.cpp

HEADERS += \
           dadm.h \
           mri.h \
           visualization3d.h

FORMS += \
        dadm.ui \
        visualization3d.ui

LIBS += -L"/usr/local/lib/" -lvtkalglib-9.0 \
        -lvtkChartsCore-9.0 \
        -lvtkCommonColor-9.0 \
        -lvtkCommonComputationalGeometry-9.0 \
        -lvtkCommonCore-9.0 \
        -lvtkCommonDataModel-9.0 \
        -lvtkCommonExecutionModel-9.0 \
        -lvtkCommonMath-9.0 \
        -lvtkCommonMisc-9.0 \
        -lvtkCommonSystem-9.0 \
        -lvtkCommonTransforms-9.0 \
        -lvtkDICOMParser-9.0 \
        -lvtkDomainsChemistry-9.0 \
        -lvtkDomainsChemistryOpenGL2-9.0 \
        -lvtkexoIIc-9.0 \
        -lvtkexpat-9.0 \
        -lvtkFiltersAMR-9.0 \
        -lvtkFiltersCore-9.0 \
        -lvtkFiltersExtraction-9.0 \
        -lvtkFiltersFlowPaths-9.0 \
        -lvtkFiltersGeneral-9.0 \
        -lvtkFiltersGeneric-9.0 \
        -lvtkFiltersGeometry-9.0 \
        -lvtkFiltersHybrid-9.0 \
        -lvtkFiltersHyperTree-9.0 \
        -lvtkFiltersImaging-9.0 \
        -lvtkFiltersModeling-9.0 \
        -lvtkFiltersParallel-9.0 \
        -lvtkFiltersParallelImaging-9.0 \
        -lvtkFiltersPoints-9.0 \
        -lvtkFiltersProgrammable-9.0 \
        -lvtkFiltersSelection-9.0 \
        -lvtkFiltersSMP-9.0 \
        -lvtkFiltersSources-9.0 \
        -lvtkFiltersStatistics-9.0 \
        -lvtkFiltersTexture-9.0 \
        -lvtkFiltersTopology-9.0 \
        -lvtkFiltersVerdict-9.0 \
        -lvtkfreetype-9.0 \
        -lvtkGeovisCore-9.0 \
        -lvtkgl2ps-9.0 \
        -lvtkglew-9.0 \
        -lvtkGUISupportQt-9.0 \
        -lvtkhdf5-9.0 \
        -lvtkhdf5_hl-9.0 \
        -lvtkImagingColor-9.0 \
        -lvtkImagingCore-9.0 \
        -lvtkImagingGeneral-9.0 \
        -lvtkImagingMath-9.0 \
        -lvtkImagingMorphological-9.0 \
        -lvtkImagingSources-9.0 \
        -lvtkImagingStatistics-9.0 \
        -lvtkInfovisCore-9.0 \
        -lvtkInteractionImage-9.0 \
        -lvtkInteractionStyle-9.0 \
        -lvtkInteractionWidgets-9.0 \
        -lvtkIOCore-9.0 \
        -lvtkIOImage-9.0 \
        -lvtkIOImport-9.0 \
        -lvtkjpeg-9.0 \
        -lvtkmetaio-9.0 \
        -lvtkNetCDF-9.0 \
        -lvtknetcdfcpp-9.0 \
        -lvtkoggtheora-9.0 \
        -lvtkParallelCore-9.0 \
        -lvtkpng-9.0 \
        -lvtkproj4-9.0 \
        -lvtkRenderingContext2D-9.0 \
        -lvtkRenderingContextOpenGL2-9.0 \
        -lvtkRenderingCore-9.0 \
        -lvtkRenderingFreeType-9.0 \
        -lvtkRenderingImage-9.0 \
        -lvtkRenderingLabel-9.0 \
        -lvtkRenderingOpenGL2-9.0 \
        -lvtkRenderingQt-9.0 \
        -lvtksys-9.0 \
        -lvtkTestingGenericBridge-9.0 \
        -lvtkTestingRendering-9.0 \
        -lvtktiff-9.0 \
        -lvtkverdict-9.0 \
        -lvtkViewsContext2D-9.0 \
        -lvtkViewsCore-9.0 \
        -lvtkViewsInfovis-9.0 \
        -lvtkViewsQt-9.0 \

INCLUDEPATH += /usr/local/include/vtk-9.0
