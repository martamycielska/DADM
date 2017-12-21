#include "dadm.h"
#include "visualization3d.h"
#include "Upsampling_GUI.h"
#include "ObliqueImaging_GUI.h"
#include "helpermethods.h"
#include "Globals.h"
#include <QDebug>
#include <QMessageBox>
#include <Eigen\Dense>
#include <unsupported\Eigen\CXX11\Tensor>
#include "matio.h"
//#include "mat.h"

//using MatFileHandler;

DADM::DADM(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	vis3D = new Visualization3D();
	connect(ui.reconstructionPushButton, SIGNAL(clicked(bool)), this, SLOT(mri_reconstruct()));
	connect(ui.visualizationBtn, SIGNAL(clicked(bool)), this, SLOT(visualization3d()));
	connect(ui.UpsamplingButton, SIGNAL(clicked(bool)), this, SLOT(openNewWindowUpsampling()));
	connect(ui.ObliqueImagingButton, SIGNAL(clicked(bool)), this, SLOT(openNewWindowObliqueImaging()));


	//MATFile *pmat;
	//const char **dir;
	//const char *name;
	//int	  ndir;
	//int	  i;
	//mxArray *pa;
	//const char *file = "T1_synthetic_normal_1mm_L8_r2.mat";

	//printf("Reading file %s...\n\n", file);

	//pmat = matOpen(file, "r");

	openFile();
}

void DADM::mri_reconstruct() {
	qRegisterMetaType<Data3D>("Data3D");
	Data3DRaw input;

	worker = new Worker(input);
	connect(worker, &Worker::resultReady, this, &DADM::onReconstructionFinished);
	connect(worker, &Worker::finished, worker, &QObject::deleteLater);
	worker->start();
}

void DADM::openNewWindowUpsampling() {
	UpsamplingWindow = new Upsampling_GUI();
	UpsamplingWindow->setWindowTitle("Upsampling");
	UpsamplingWindow->show();
}

void DADM::openNewWindowObliqueImaging() {
	ObliqueImagingWindow = new ObliqueImaging_GUI();
	ObliqueImagingWindow->setWindowTitle("Oblique Imaging");
	ObliqueImagingWindow->show();
}

void DADM::openFile()
{
	/*
	const char *fileName = "T1_synthetic_normal_1mm_L8_r2.mat";
	mat_t *mat = Mat_Open(fileName, MAT_ACC_RDONLY);

	if (mat) {
		qDebug() << "Otwarto plik";

		matvar_t *matVar = 0;

		matVar = Mat_VarRead(mat, (char*)"x");
	}
*/
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
	if (vis3D)
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