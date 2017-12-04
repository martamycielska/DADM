#include "dadm.h"
#include "visualization3d.h"
#include "mri.h"
#include "classes/helpermethods.h"
#include "Globals.h"
#include <QDebug>
#include <QMessageBox>

DADM::DADM(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	vis3D = new Visualization3D();
	connect(ui.reconstructionPushButton, SIGNAL(clicked(bool)), this, SLOT(mri_reconstruct()));
	connect(ui.visualizationBtn, SIGNAL(clicked(bool)), this, SLOT(visualization3d()));
	qDebug() << Globals::i;
	Globals::i++;
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
