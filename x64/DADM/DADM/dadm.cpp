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
#include "qaction.h"
#include "qfiledialog.h"
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
	connect(ui.actionStructural_data, &QAction::triggered, this, &DADM::importStructuralData);
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

void DADM::importStructuralData()
{

	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Mat file (*.mat) (*mat)");

	if (url.isEmpty())
		return;

	QString path = url.path().remove(0, 1);
	QByteArray ba = path.toLatin1();
	const char *fileName = ba.data();
	//const char *fileName = "T1_synthetic_normal_1mm_L8_r2.mat";
	mat_t *mat = Mat_Open(fileName, MAT_ACC_RDONLY);

	if (mat) {
		qDebug() << "Otwarto plik";

		matvar_t *matVar = 0;

		matVar = Mat_VarRead(mat, (char*)"raw_data");

		if (matVar) {
			qDebug() << "Otwarto raw_data";

			//unsigned int xSize = matVar->nbytes / matVar->data_size;
			const mat_complex_split_t *xData = static_cast<const mat_complex_split_t*>(matVar->data);
			const double *xRe = static_cast<const double*>(xData->Re);
			const double *xIm = static_cast<const double*>(xData->Im);

			qDebug() << matVar->dims[0];
			qDebug() << matVar->dims[1];
			qDebug() << matVar->dims[2];

			std::vector<MatrixXcd> raw_data;
			//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
			int val_num = 0;
			for (int i = 0; i < matVar->dims[2]; i++) {
				MatrixXcd m(matVar->dims[0], matVar->dims[1]);
				for (int j = 0; j < matVar->dims[1]; j++) {
					for (int k = 0; k < matVar->dims[0]; k++) {
						m(k, j) = std::complex<double>(xRe[val_num], xIm[val_num]);
						val_num++;
						//qDebug() << xRe[val_num] << xIm[val_num];
					}
				}
				raw_data.push_back(m);
			}

			Data3DRaw structuralRawData = raw_data;

			matvar_t *s_matVar = 0;
			s_matVar = Mat_VarRead(mat, (char*)"sensitivity_maps");

			if (s_matVar) {
				qDebug() << "Otwarto sensitivity_maps";

				//unsigned int xSize = matVar->nbytes / matVar->data_size;
				const mat_complex_split_t *xData = static_cast<const mat_complex_split_t*>(s_matVar->data);
				const double *xRe = static_cast<const double*>(xData->Re);
				const double *xIm = static_cast<const double*>(xData->Im);

				qDebug() << s_matVar->dims[0];
				qDebug() << s_matVar->dims[1];
				qDebug() << s_matVar->dims[2];

				std::vector<MatrixXcd> sensitivity_maps;
				//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
				int val_num = 0;
				for (int i = 0; i < s_matVar->dims[2]; i++) {
					MatrixXcd m(s_matVar->dims[0], s_matVar->dims[1]);
					for (int j = 0; j < s_matVar->dims[1]; j++) {
						for (int k = 0; k < s_matVar->dims[0]; k++) {
							m(k, j) = std::complex<double>(xRe[val_num], xIm[val_num]);
							val_num++;
							//qDebug() << xRe[val_num] << xIm[val_num];
						}
					}
					sensitivity_maps.push_back(m);
				}

				Data3DRaw structuralSensitivityMaps = sensitivity_maps;
			}
		}

		matvar_t *l_matVar = 0;
		l_matVar = Mat_VarRead(mat, (char*)"L");

		if (l_matVar) {
			qDebug() << "Otwarto L";
			const int *xData = static_cast<const int*>(l_matVar->data);
			int L = xData[0];
		}

		matvar_t *r_matVar = 0;
		r_matVar = Mat_VarRead(mat, (char*)"r");

		if (r_matVar) {
			qDebug() << "Otwarto r";
			const int *xData = static_cast<const int*>(r_matVar->data);
			int r = xData[0];
		}

	}

	Mat_Close(mat);

	QMessageBox msgBox;
	msgBox.setText("File imported");
	msgBox.exec();
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
	/*
	Reconstruction *reconstruction = new Reconstruction(input);
	reconstruction->Start();
	Data3D out = reconstruction->getData3D();
	emit resultReady(out);
	*/
}