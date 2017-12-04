#include "visualization3d.h"
#include "ui_visualization3d.h"
#include "classes/helpermethods.h"
#include <QThread>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFileDialog>
#include <QTimer>

#pragma region VISUALIZATION3D class
Visualization3D::Visualization3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visualization3D)
{
	InitValue();
	SetConnections();
	InitUI();
}

#pragma region controls event

void Visualization3D::Brain3D() {
	UpdateProcessStateText("The model 3D initializing ....\nPlease wait");
	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Raw file (*.raw) (*raw)");

	if (url.isEmpty())
		return;

	QString path = url.path().remove(0, 1);
	brain_3D = new Brain_3D(path, xspace, yspace, zspace, threshold, shrinkingFactor);

	worker = new VisualizationWorker(brain_3D);
	connect(worker, &VisualizationWorker::ModelCreationDone, this, &Visualization3D::AddRendererAndPlaneWidget);
	connect(worker, &VisualizationWorker::finished, worker, &QObject::deleteLater);
	worker->start();
}

void Visualization3D::SliderValueChanged(int sliderValue) {
    ui -> thresholdTextEdit -> setText(QString::number(sliderValue));
}

void Visualization3D::ShrinkSliderValueChanged(int sliderValue) {
	shrinkingFactor = sliderValue;
	
	if (visualizationDone) {
		UpdateProcessStateText("The mri data shrinking...\nPlease wait");
		QEventLoop loop;
		QTimer::singleShot(1000, &loop, SLOT(quit()));
		loop.exec();
		brain_3D -> setShrinkFactor(shrinkingFactor);
		ui -> qvtkWidget -> GetRenderWindow() -> Render();
		UpdateProcessStateText("Shrinking done");
	}
}

void Visualization3D::CutEnableChanged(bool cutEnable) {
	if (visualizationDone) {
		if (cutEnable)
			planeWidget -> On();
		else
			planeWidget -> Off();

		ui -> qvtkWidget -> GetRenderWindow() -> Render();
	}
	else {
		if (cutEnable)
			setCutOptionEnable = true;
		else
			setCutOptionEnable = false;
	}
}

void Visualization3D::AcceptThreshold() {
	UpdateProcessStateText("The model 3D rendering...\nPlease wait");

	QEventLoop loop;
	QTimer::singleShot(1000, &loop, SLOT(quit()));
	loop.exec();

	QString thresholdString = ui -> thresholdTextEdit -> toPlainText();
	float thresholdFloat = thresholdString.toFloat();
	threshold = thresholdFloat;

	if (visualizationDone == true) {
		MarchingCubes mc = brain_3D -> getMarchingCubes();
		mc -> SetValue(0, thresholdFloat);
		brain_3D -> setMarchingCubes(mc);
		brain_3D -> setThreshold(threshold);
		ui->qvtkWidget -> GetRenderWindow() -> Render();
	}

	UpdateProcessStateText("Rendering done");
}
#pragma endregion controls event

#pragma region private methods
void Visualization3D::InitValue() {
	ui->setupUi(this);
	xspace = 180;
	yspace = 216;
	zspace = 180;
	threshold = 100;
	shrinkingFactor = 2;
	visualizationDone = false;
	setCutOptionEnable = true;
}

void Visualization3D::SetConnections() {
	connect(ui->visualizeBtn, SIGNAL(clicked(bool)), this, SLOT(Brain3D()));
	connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SliderValueChanged(int)));
	connect(ui->acceptBtn, SIGNAL(clicked(bool)), this, SLOT(AcceptThreshold()));
	connect(ui->cutEnableRadioBtn, SIGNAL(toggled(bool)), this, SLOT(CutEnableChanged(bool)));
	connect(ui->shrinkSlider, SIGNAL(valueChanged(int)), this, SLOT(ShrinkSliderValueChanged(int)));
}

void Visualization3D::InitUI() {
	ui->horizontalSlider->setValue(threshold);
	ui->shrinkSlider->setValue(shrinkingFactor);
	ui->thresholdTextEdit->setText(QString::number(ui->horizontalSlider->value()));
}

void Visualization3D::AddRendererAndPlaneWidget() {
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	ui->qvtkWidget->SetRenderWindow(renderWnd);
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(brain_3D->getRenderer());

	plane = vtkSmartPointer<vtkPlane>::New();
	plane->SetNormal(1, 0, 0);
	clipper = vtkSmartPointer<vtkClipPolyData>::New();
	clipper->SetClipFunction(plane);
	clipper->InsideOutOn();

	myCallback = vtkSmartPointer<MyCallback>::New();
	myCallback->Plane = plane;

	rep = vtkSmartPointer<vtkImplicitPlaneRepresentation>::New();
	rep->SetPlaceFactor(1.0); // This must be set prior to placing the widget
	rep->SetNormal(plane->GetNormal());
	rep->OutlineTranslationOff();
	rep->ScaleEnabledOff();
	rep->GetPlaneProperty()->SetOpacity(0.0);
	rep->GetSelectedPlaneProperty()->SetOpacity(0.2);

	planeWidget = vtkSmartPointer<vtkImplicitPlaneWidget2>::New();
	planeWidget->SetInteractor(ui->qvtkWidget->GetInteractor());
	planeWidget->SetRepresentation(rep);
	planeWidget->AddObserver(vtkCommand::InteractionEvent, myCallback);

	if (setCutOptionEnable)
		planeWidget->On();

	clipper->SetInputConnection(brain_3D->getConfilter()->GetOutputPort());
	brain_3D->getMapper()->SetInputConnection(clipper->GetOutputPort());

	plane->SetOrigin(xspace / 2., yspace / 2., zspace / 2.);
	plane->SetNormal(0, -1, 0);
	rep->SetNormal(plane->GetNormal());

	double bounds[6];
	bounds[0] = 0;
	bounds[1] = xspace;
	bounds[2] = 0;
	bounds[3] = yspace;
	bounds[4] = 0;
	bounds[5] = zspace;

	plane->SetNormal(1., 0., 0.);
	rep->PlaceWidget(bounds);
	rep->SetOrigin(plane->GetOrigin());
	rep->SetNormal(plane->GetNormal());

	ui->qvtkWidget->repaint();
	visualizationDone = true;
	UpdateProcessStateText("Brain visualization done");

	qDebug() << "Add Renderer";
}

void Visualization3D::UpdateProcessStateText(QString text) {
	ui->processDescLabel->setText(text);
}
#pragma endregion private methods

#pragma endregion VISUALIZATION3D class


#pragma region WORKER class
VisualizationWorker::VisualizationWorker(Brain_3D *brain_3D) : brain_3D(brain_3D) {
	qRegisterMetaType<Renderer>("Renderer");
	qRegisterMetaType<MarchingCubes>("MarchingCubes");
	qRegisterMetaType<MarchingCubes>("Confilter");
	qRegisterMetaType<MarchingCubes>("Mapper");
}

void VisualizationWorker::run() {
	brain_3D->start();
	emit ModelCreationDone();
}
#pragma endregion WORKER class