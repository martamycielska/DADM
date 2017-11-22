#include "visualization3d.h"
#include "ui_visualization3d.h"
#include <QThread>
#include <QDebug>

// VTK_BRAIN 3D LIBRARIES
#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageReader.h>
#include <vtkNamedColors.h>

Visualization3D::Visualization3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visualization3D){
    ui -> setupUi(this);
    connect(ui->visualizeBtn, SIGNAL(clicked(bool)), this, SLOT(brain3D()));
}

void Visualization3D::brain3D(){
    ui->processDescLabel->setText("The model 3D initializing ...");
    const char* fileName = "/home/aneta/Pulpit/DADMgit/DADM/DADM/8bit.raw";
    float threshold = 100;
    int extractLargest = 0;

    vtkImageReader *reader = vtkImageReader::New();
    reader -> SetFileName(fileName);
    reader -> SetFileDimensionality(3);
    reader -> SetNumberOfScalarComponents(1);
    reader -> SetDataExtent(0, 180, 0, 216, 0, 180);
    reader -> SetDataSpacing(0.145, 0.145, 0.145);
    reader -> SetDataScalarTypeToChar();
    reader -> Update();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    // Create a 3D model using marching cubes
    vtkSmartPointer<vtkMarchingCubes> mc = vtkSmartPointer<vtkMarchingCubes>::New();
    mc -> SetInputConnection(reader -> GetOutputPort());
    mc -> ComputeNormalsOn();
    mc -> ComputeGradientsOn();
    mc -> SetValue(0, threshold);

    // To remain largest region
    vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
    confilter -> SetInputConnection(mc -> GetOutputPort());
    confilter -> SetExtractionModeToLargestRegion();

    // Create a mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    if (extractLargest)
        mapper -> SetInputConnection(confilter -> GetOutputPort());
    else
        mapper -> SetInputConnection(mc -> GetOutputPort());

    // set utilize actor's property
    mapper -> ScalarVisibilityOff();

    // Visualize
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor -> GetProperty() -> SetColor(colors -> GetColor3d("Flesh").GetData());
    actor -> SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render -> AddActor(actor);
    render -> SetBackground(colors -> GetColor3d("Burlywood").GetData());
    render -> GetActiveCamera() -> SetViewUp(0.0, 0.0, 1.0);
    render -> GetActiveCamera() -> SetPosition(0.0, 1.0, 0.0);
    render -> GetActiveCamera() -> SetFocalPoint(0.0, 0.0, 0.0);
    render -> ResetCamera();
    render -> GetActiveCamera() -> Azimuth(30.0);
    render -> GetActiveCamera() -> Elevation(30.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow -> AddRenderer(render);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor -> SetRenderWindow(renderWindow);
    interactor -> Initialize();
    interactor -> Start();

    ui->processDescLabel->setText("");
    qDebug() << "Brain visualization 3D done";
}
