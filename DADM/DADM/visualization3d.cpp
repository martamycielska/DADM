#include "visualization3d.h"
#include "ui_visualization3d.h"
#include "classes/helpermethods.h"
#include <QThread>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFileDialog>

Visualization3D::Visualization3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visualization3D)
{
    ui->setupUi(this);
	threshold = 100;
	mc = vtkSmartPointer<vtkMarchingCubes>::New();

    connect(ui->visualizeBtn, SIGNAL(clicked(bool)), this, SLOT(brain3D()));
	//connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
	connect(ui->acceptBtn, SIGNAL(clicked(bool)), this, SLOT(acceptThreshold()));
}

//void Visualization3D::sliderValueChanged(int sliderValue) {
//	qRegisterMetaType<Renderer>("Renderer");
//	threshold = sliderValue;
//	mc->SetValue(0, threshold);
//	ui->qvtkWidget->GetRenderWindow()->Render();
//}

void Visualization3D::acceptThreshold() {
	ui->processDescLabel->setText("The model 3D rendering...\nPlease wait");
	QString thresholdString = ui->thresholdTextEdit->toPlainText();

	float threshold = thresholdString.toFloat();
	mc->SetValue(0, threshold);
	ui->qvtkWidget->GetRenderWindow()->Render();

	ui->processDescLabel->setText("Brain visualization done");
}

void Visualization3D::addRenderer(Renderer render) {
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	ui->qvtkWidget->SetRenderWindow(renderWnd);
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(render);
	ui->processDescLabel->setText("Brain visualization done.\nPlease tap on the render window to\n see the result.");
	ui->qvtkWidget->repaint();
}

void Visualization3D::brain3D(){

	ui->processDescLabel->setText("The model 3D initializing ....\nPlease wait");

	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Raw file (*.raw) (*raw)");
	QString path = url.path().remove(0, 1);

	worker = new VisualizationWorker(path);
	connect(worker, &VisualizationWorker::initializationDone, this, &Visualization3D::addRenderer);
	connect(worker, &VisualizationWorker::finished, worker, &QObject::deleteLater);
	worker->start();
}

VisualizationWorker::VisualizationWorker(QString path) : path(path) {
	qRegisterMetaType<Renderer>("Renderer");
}

void VisualizationWorker::run() {
	qDebug() << "START";

	QByteArray ba = path.toLatin1();
	const char* fileName = ba.data();
	float threshold = 100;
	int extractLargest = 0;

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
	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
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