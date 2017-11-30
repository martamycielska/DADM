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
    ui->setupUi(this);
	brain_3D = new Brain_3D();

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
	QEventLoop loop;
	QTimer::singleShot(1000, &loop, SLOT(quit()));
	loop.exec();
	QString thresholdString = ui->thresholdTextEdit->toPlainText();
	brain_3D->setThreshold(thresholdString.toFloat());
	MarchingCubes mc = brain_3D->getMarchingCubes();
	mc->SetValue(0, thresholdString.toFloat());
	brain_3D->setMarchingCubes(mc);
	ui->qvtkWidget->GetRenderWindow()->Render();

	ui->processDescLabel->setText("Rendering done");
}

void Visualization3D::addRenderer() {
	qDebug() << "Add Renderer";
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	ui->qvtkWidget->SetRenderWindow(renderWnd);
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(brain_3D->getRenderer());
	ui->processDescLabel->setText("Brain visualization done.");
	ui->qvtkWidget->repaint();
}

void Visualization3D::brain3D(){
	ui->processDescLabel->setText("The model 3D initializing ....\nPlease wait");
	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Raw file (*.raw) (*raw)");
	QString path = url.path().remove(0, 1);

	worker = new VisualizationWorker(path, brain_3D);
	connect(worker, &VisualizationWorker::initializationDone, this, &Visualization3D::addRenderer);
	connect(worker, &VisualizationWorker::finished, worker, &QObject::deleteLater);
	worker->start();
}
#pragma endregion VISUALIZATION3D class


#pragma region WORKER class
VisualizationWorker::VisualizationWorker(QString path, Brain_3D *brain_3D) : path(path), brain_3D(brain_3D) {
	qRegisterMetaType<Renderer>("Renderer");
	qRegisterMetaType<MarchingCubes>("MarchingCubes");
}

void VisualizationWorker::run() {
	brain_3D->initialize(path);
	emit initializationDone();
}
#pragma endregion WORKER class