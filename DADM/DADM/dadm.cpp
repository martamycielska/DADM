#include "dadm.h"
#include "visualization3d.h"
#include "mri.h"
#include "classes/helpermethods.h"
#include "Globals.h"
#include <QDebug>
#include <QMessageBox>
#include <Eigen\Dense>
#include <unsupported\Eigen\CXX11\Tensor>

DADM::DADM(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	vis3D = new Visualization3D();
	connect(ui.reconstructionPushButton, SIGNAL(clicked(bool)), this, SLOT(mri_reconstruct()));
	connect(ui.visualizationBtn, SIGNAL(clicked(bool)), this, SLOT(visualization3d()));
}

void DADM::mri_reconstruct() {
	qRegisterMetaType<Data3D>("Data3D");
	Data3DRaw input;

	worker = new Worker(input);
	connect(worker, &Worker::resultReady, this, &DADM::onReconstructionFinished);
	connect(worker, &Worker::finished, worker, &QObject::deleteLater);
	worker->start();
}

void DADM::visualization3d() {
	vis3D = new Visualization3D();
	HelperMethods::SetCenterPosition(vis3D);
	vis3D->show();
}

void DADM::onReconstructionFinished(Data3D data)
{
	Data3D structuralData = data;
	QMessageBox msgBox;
	msgBox.setText("Finished");
	msgBox.exec();
}

DADM::~DADM()
{
	if(vis3D)
		delete vis3D;
}

Worker::Worker(Data3DRaw input)
{
	this->input = input;
}

void Worker::run()
{
	Reconstruction *reconstruction = new Reconstruction(input);
	reconstruction->Start();
	Data3D out = reconstruction->getData3D();
	emit resultReady(out);
}