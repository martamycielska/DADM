#include "visualization3d.h"
#include "ui_visualization3d.h"
#include "classes/helpermethods.h"
#include <QThread>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFileDialog>
#include <QTimer>
#include "Globals.h"

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
	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Raw file (*.raw) (*raw)");

	if (url.isEmpty())
		return;

	QString path = url.path().remove(0, 1);
	UpdateProcessStateText("The model 3D initializing ....\nPlease wait");
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

void Visualization3D::AcceptThreshold() {
	QString thresholdString = ui -> thresholdTextEdit -> toPlainText();
	float thresholdFloat = thresholdString.toFloat();
	threshold = thresholdFloat;

	if (visualizationDone == true) {
		UpdateProcessStateText("The model 3D rendering...\nPlease wait");

		QEventLoop loop;
		QTimer::singleShot(1000, &loop, SLOT(quit()));
		loop.exec();

		MarchingCubes mc = brain_3D -> getMarchingCubes();
		mc -> SetValue(0, thresholdFloat);
		brain_3D -> setMarchingCubes(mc);
		brain_3D -> setThreshold(threshold);
		ui->qvtkWidget -> GetRenderWindow() -> Render();

		UpdateProcessStateText("Rendering done");
	}
	else {
		UpdateProcessStateText("Threshold changing done");
	}
}
#pragma endregion controls event

#pragma region private methods
void Visualization3D::InitValue() {
	ui->setupUi(this);
	xspace = 180;
	yspace = 216;
	zspace = 180;
	threshold = 84;
	shrinkingFactor = 2;
	visualizationDone = false;
}

void Visualization3D::SetConnections() {
	connect(ui->visualizeBtn, SIGNAL(clicked(bool)), this, SLOT(Brain3D()));
	connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SliderValueChanged(int)));
	connect(ui->acceptBtn, SIGNAL(clicked(bool)), this, SLOT(AcceptThreshold()));
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
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(brain_3D->getData());
	ui->qvtkWidget->repaint();
	visualizationDone = true;
	UpdateProcessStateText("Brain visualization done");

	qDebug() << "Add renderer";
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
	brain_3D->Start();
	emit ModelCreationDone();
}
#pragma endregion WORKER class