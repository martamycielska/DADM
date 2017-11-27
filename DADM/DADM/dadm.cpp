#include "dadm.h"
#include "visualization3d.h"
#include "mri.h"
#include "classes/helpermethods.h"
#include <QMessageBox>

DADM::DADM(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	mri = new MRI;
	connect(ui.reconstructionPushButton, SIGNAL(clicked(bool)), this, SLOT(mri_reconstruct()));
	connect(ui.visualizationBtn, SIGNAL(clicked(bool)), this, SLOT(visualization3d()));
}

void DADM::mri_reconstruct() {
	Worker *worker = new Worker(mri, RECONSTRUCTION);
	connect(worker, &Worker::resultReady, this, &DADM::onReconstructionFinished);
	connect(worker, &Worker::finished, worker, &QObject::deleteLater);
	worker->start();
	//mri->start_reconstruction();
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
	delete mri;
	delete vis3D;
}

Worker::Worker(MRI *mri, process prc) : QThread(nullptr), mri(mri), prc(prc) {}

void Worker::run() {
	switch (prc) {
	case RECONSTRUCTION:
		mri->MRI_recognition();
		mri->intensity_inhomogenity_correction();
		mri->non_stationary_noise_estimation();
		mri->non_stationary_noise_filtering_1();
		mri->brain_3d();
		emit resultReady("Done");
		break;
	default:
		break;
	}
}
