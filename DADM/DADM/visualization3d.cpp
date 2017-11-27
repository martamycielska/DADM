#include "visualization3d.h"
#include "ui_visualization3d.h"
#include "classes/helpermethods.h"
#include <QThread>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFileDialog>

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
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkBorderWidget.h>

Visualization3D::Visualization3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visualization3D)
{
	ui->setupUi(this);
	qRegisterMetaType<Renderer>("Renderer");
    connect(ui->visualizeBtn, SIGNAL(clicked(bool)), this, SLOT(brain3D()));
	connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
}

void Visualization3D::sliderValueChanged(int i) {

}

void Visualization3D::addRenderer(Renderer render) {
	qDebug() << "Add Renderer";
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	ui->qvtkWidget->SetRenderWindow(renderWnd);
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(render);
	ui->qvtkWidget->repaint();
	ui->processDescLabel->setText("Brain visualization done.\nPlease tap on the render window to see the result.");
}

void Visualization3D::brain3D(){

    ui->processDescLabel->setText("The model 3D initializing ...");
	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Raw file (*.raw) (*raw)");
	QString path = url.path().remove(0, 1);

	//vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	//ui->qvtkWidget->SetRenderWindow(renderWnd);

	worker = new VisualizationWorker(path);
	connect(worker, &VisualizationWorker::initializationDone, this, &Visualization3D::addRenderer);
	connect(worker, &VisualizationWorker::finished, worker, &QObject::deleteLater);
	worker->start();

	/*
	connect(this, &Visualization3D::initializationDone, this, &Visualization3D::addRenderer);

	
	QByteArray ba = path.toLatin1();
    const char* fileName = ba.data();
    float threshold = 100;
    int extractLargest = 0;

    //vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    //ui->qvtkWidget->SetRenderWindow(renderWnd);

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

    // VTK Renderer
    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render -> AddActor(actor);
    render -> SetBackground(colors -> GetColor3d("Burlywood").GetData());
    render -> GetActiveCamera() -> SetViewUp(0.0, 0.0, 1.0);
    render -> GetActiveCamera() -> SetPosition(0.0, 1.0, 0.0);
    render -> GetActiveCamera() -> SetFocalPoint(0.0, 0.0, 0.0);
    render -> ResetCamera();
    render -> GetActiveCamera() -> Azimuth(30.0);
    render -> GetActiveCamera() -> Elevation(30.0);

    // Connect VTK with QT
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(render);
    //vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    //renderWindow -> AddRenderer(render);

    // Add a border widget to the right renderer
    //vtkSmartPointer<vtkBorderWidget> bw = vtkSmartPointer<vtkBorderWidget>::New();
    //BorderWidget = bw;
    //BorderWidget->SetInteractor(ui->qvtkWidget->GetInteractor());
    //BorderWidget->On();

    //vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //interactor -> SetRenderWindow(renderWindow);
    //interactor -> Initialize();
    //interactor -> Start();

    ui->processDescLabel->setText("Brain visualization done.\nPlease tap on the render window to see the result.");
	*/
}

VisualizationWorker::VisualizationWorker(QString path) : path(path) {
	qRegisterMetaType<Renderer>("Renderer");
}

void VisualizationWorker::run() {
	QByteArray ba = path.toLatin1();
	const char* fileName = ba.data();
	float threshold = 100;
	int extractLargest = 0;

	qDebug() << "START";

	//vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	//ui->qvtkWidget->SetRenderWindow(renderWnd);

	vtkImageReader *reader = vtkImageReader::New();
	reader->SetFileName(fileName);
	reader->SetFileDimensionality(3);
	reader->SetNumberOfScalarComponents(1);
	reader->SetDataExtent(0, 180, 0, 216, 0, 180);
	reader->SetDataSpacing(0.145, 0.145, 0.145);
	reader->SetDataScalarTypeToChar();
	reader->Update();

	vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

	// Create a 3D model using marching cubes
	vtkSmartPointer<vtkMarchingCubes> mc = vtkSmartPointer<vtkMarchingCubes>::New();
	mc->SetInputConnection(reader->GetOutputPort());
	mc->ComputeNormalsOn();
	mc->ComputeGradientsOn();
	mc->SetValue(0, threshold);

	// To remain largest region
	vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
	confilter->SetInputConnection(mc->GetOutputPort());
	confilter->SetExtractionModeToLargestRegion();

	// Create a mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	if (extractLargest)
		mapper->SetInputConnection(confilter->GetOutputPort());
	else
		mapper->SetInputConnection(mc->GetOutputPort());

	// set utilize actor's property
	mapper->ScalarVisibilityOff();

	// Visualize
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->GetProperty()->SetColor(colors->GetColor3d("Flesh").GetData());
	actor->SetMapper(mapper);

	// VTK Renderer
	render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);
	render->SetBackground(colors->GetColor3d("Burlywood").GetData());
	render->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
	render->GetActiveCamera()->SetPosition(0.0, 1.0, 0.0);
	render->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	render->ResetCamera();
	render->GetActiveCamera()->Azimuth(30.0);
	render->GetActiveCamera()->Elevation(30.0);
	

	qDebug() << "DONE";

	emit initializationDone(render);
}