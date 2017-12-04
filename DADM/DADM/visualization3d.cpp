#include "visualization3d.h"
#include "ui_visualization3d.h"
#include "classes/helpermethods.h"
#include <QThread>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFileDialog>

#pragma region VISUALIZATION3D class
Visualization3D::Visualization3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visualization3D)
{
    ui->setupUi(this);
	xspace = 180;
	yspace = 216;
	zspace = 180;
	threshold = 100;
	visualizationDone = false;
	setCutOptionEnable = true;
	brain_3D = new Brain_3D(xspace, yspace, zspace, threshold);
	planeWidget = vtkSmartPointer<vtkImplicitPlaneWidget2>::New();

    connect(ui->visualizeBtn, SIGNAL(clicked(bool)), this, SLOT(brain3D()));
	connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
	connect(ui->acceptBtn, SIGNAL(clicked(bool)), this, SLOT(acceptThreshold()));
	connect(ui->cutEnableRadioBtn, SIGNAL(toggled(bool)), this, SLOT(cutEnableChanged(bool)));
	
	ui->horizontalSlider->setValue(threshold);
	ui->thresholdTextEdit->setText(QString::number(ui->horizontalSlider->value()));
}

void Visualization3D::sliderValueChanged(int sliderValue) {
    ui->thresholdTextEdit->setText(QString::number(sliderValue));
}

void Visualization3D::cutEnableChanged(bool cutEnable) {
	if (visualizationDone) {
		if (cutEnable)
			planeWidget->On();
		else
			planeWidget->Off();

		ui->qvtkWidget->GetRenderWindow()->Render();
	}
	else
		if (cutEnable)
			setCutOptionEnable = true;
		else
			setCutOptionEnable = false;
}

void Visualization3D::acceptThreshold() {
	QString thresholdString = ui->thresholdTextEdit->toPlainText();
	float thresholdFloat = thresholdString.toFloat();
	brain_3D->setThreshold(thresholdFloat);

	if (visualizationDone == true) {

		MarchingCubes mc = brain_3D->getMarchingCubes();
		mc->SetValue(0, thresholdFloat);
		brain_3D->setMarchingCubes(mc);
		ui->qvtkWidget->GetRenderWindow()->Render();
	}
}

void Visualization3D::addRenderer() {
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	ui->qvtkWidget->SetRenderWindow(renderWnd);
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(brain_3D->getRenderer());
	//ui->processDescLabel->setText("Brain visualization done.");
	//ui->qvtkWidget->repaint();

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

	planeWidget->SetInteractor(ui->qvtkWidget->GetInteractor());
	planeWidget->SetRepresentation(rep);
	planeWidget->AddObserver(vtkCommand::InteractionEvent, myCallback);
	//planeWidget->SetEnabled(true);

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

	ui->processDescLabel->setText("Brain visualization done");
	ui->qvtkWidget->repaint();

	visualizationDone = true;
	qDebug() << "Add Renderer";
}

//void Visualization3D::showFinishedText() {
//	ui->processDescLabel->setText("Brain visualization done.");
//	ui->qvtkWidget->repaint();
//	qDebug() << "ShowFinishedText";
//}

void Visualization3D::brain3D(){
	ui->processDescLabel->setText("The model 3D initializing ....\nPlease wait");
	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Raw file (*.raw) (*raw)");
	
	if (url.isEmpty())
		return;

	QString path = url.path().remove(0, 1);

	worker = new VisualizationWorker(path, brain_3D);
	connect(worker, &VisualizationWorker::ModelCreationDone, this, &Visualization3D::addRenderer);
	//connect(worker, &VisualizationWorker::CuttingPlaneDone, this, &Visualization3D::showFinishedText);
	connect(worker, &VisualizationWorker::finished, worker, &QObject::deleteLater);
	worker->start();
}
#pragma endregion VISUALIZATION3D class


#pragma region WORKER class
VisualizationWorker::VisualizationWorker(QString path, Brain_3D *brain_3D) : path(path), brain_3D(brain_3D) {
	qRegisterMetaType<Renderer>("Renderer");
	qRegisterMetaType<MarchingCubes>("MarchingCubes");
	qRegisterMetaType<MarchingCubes>("Confilter");
	qRegisterMetaType<MarchingCubes>("Mapper");
}

void VisualizationWorker::run() {
	brain_3D->initialize(path);
	emit ModelCreationDone();
	/*brain_3D->cutPlane();
	emit CuttingPlaneDone();*/
}
#pragma endregion WORKER class