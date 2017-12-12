#include "dadm.h"
#include "visualization3d.h"
#include "mri.h"
#include "classes/helpermethods.h"
#include "Globals.h"
#include <QDebug>
#include <QMessageBox>
#include "Non_stationary_noise_estimation.h"
//#include "Reconstruction.h"
#include "Intensity_inhomogenity_correction.h"
#include <Eigen\Dense>
#include <unsupported\Eigen\CXX11\Tensor>

DADM::DADM(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	vis3D = new Visualization3D();
	connect(ui.reconstructionPushButton, SIGNAL(clicked(bool)), this, SLOT(mri_reconstruct()));
	connect(ui.visualizationBtn, SIGNAL(clicked(bool)), this, SLOT(visualization3d()));

	/*
	Data3DRaw input(3,3,3);
	input.setZero();
	Reconstruction<Data3DRaw, Data3D> *reconstruction = new Reconstruction<Data3DRaw, Data3D>(input, STRUCTURAL_DATA);
	reconstruction->Start();
	Data3D out = reconstruction->getData();
	*/
}

void DADM::mri_reconstruct() {
	Data3DRaw input(3, 3, 3);
	input.setZero();

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

void DADM::onReconstructionFinished(QString str)
{
	QMessageBox msgBox;
	msgBox.setText(str);
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
	Reconstruction<Data3DRaw, Data3D> *reconstruction = new Reconstruction<Data3DRaw, Data3D>(input, STRUCTURAL_DATA);
	reconstruction->Start();
	Data3D out = reconstruction->getData();
	emit resultReady("Finished");
}