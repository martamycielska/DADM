#include "dadm.h"
#include "visualization3d.h"
#include "mri.h"
#include "classes/helpermethods.h"
#include "Globals.h"
#include <QDebug>
#include <QMessageBox>
#include "Non_stationary_noise_estimation.h"

DADM::DADM(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	vis3D = new Visualization3D();
	connect(ui.reconstructionPushButton, SIGNAL(clicked(bool)), this, SLOT(mri_reconstruct()));
	connect(ui.visualizationBtn, SIGNAL(clicked(bool)), this, SLOT(visualization3d()));

	//std::vector<MatrixXd> a3d;
	//Non_stationary_noise_estimation *estimation = new Non_stationary_noise_estimation(a3d, STRUCTURAL_DATA);

	//Reconstruction *reconstruction = new Reconstruction(STRUCTURAL_DATA);
	//reconstruction->Start();
	//MatrixXd matrix = reconstruction->getData();
}

void DADM::mri_reconstruct() {

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
