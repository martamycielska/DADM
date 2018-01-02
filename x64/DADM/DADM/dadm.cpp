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
	connect(ui.actionDiffusion_data, &QAction::triggered, this, &DADM::importDiffusionData);
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
	ImportWorker* iw = new ImportWorker(path, STRUCTURAL_DATA);
	connect(iw, &ImportWorker::importDone, this, &DADM::onImportDone);
	connect(iw, &Worker::finished, iw, &QObject::deleteLater);
	iw->start();
}

void DADM::importDiffusionData()
{

	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Mat file (*.mat) (*mat)");

	if (url.isEmpty())
		return;

	QString path = url.path().remove(0, 1);

	ImportWorker* iw = new ImportWorker(path, DIFFUSION_DATA);
	connect(iw, &ImportWorker::importDone, this, &DADM::onImportDone);
	connect(iw, &Worker::finished, iw, &QObject::deleteLater);
	iw->start();
}

void DADM::onImportDone()
{
	QMessageBox msgBox;
	msgBox.setText("Data imported");
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

ImportWorker::ImportWorker(QString path, DataType type) {
	this->path = path;
	this->dtype = type;
}

void ImportWorker::run() {
	switch (dtype)
	{
	case STRUCTURAL_DATA:
		structuralDataImport();
		break;
	case DIFFUSION_DATA:
		diffusionDataImport();
		break;
	default:
		break;
	}

}

void ImportWorker::diffusionDataImport()
{
	QByteArray ba = path.toLatin1();
	const char *fileName = ba.data();
	//const char *fileName = "T1_synthetic_normal_1mm_L8_r2.mat";
	mat_t *mat = Mat_Open(fileName, MAT_ACC_RDONLY);

	if (mat) {
		qDebug() << "Otwarto plik";

		matvar_t *g_matVar = 0;

		g_matVar = Mat_VarRead(mat, (char*)"gradients");

		if (g_matVar) {
			qDebug() << "Otwarto gradients";

			//unsigned int xSize = matVar->nbytes / matVar->data_size;
			const double *xData = static_cast<const double*>(g_matVar->data);

			qDebug() << g_matVar->dims[0];
			qDebug() << g_matVar->dims[1];

			//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
			int val_num = 0;
			MatrixXd m(g_matVar->dims[0], g_matVar->dims[1]);
			for (int i = 0; i < g_matVar->dims[1]; i++) {
				for (int j = 0; j < g_matVar->dims[0]; j++) {
					m(j, i) = xData[val_num];
					val_num++;
					if (val_num >= g_matVar->dims[0] * g_matVar->dims[1]) break;
					//qDebug() << xData[val_num];
				}
			}

			Global::gradients = m;
		}

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
			qDebug() << matVar->dims[3];

			//std::vector<MatrixXcd> raw_data;
			//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
			int val_num = 0;
			std::vector<std::vector<MatrixXcd>> raw_data;
			for (int l = 0; l < matVar->dims[3]; l++) {
				std::vector<MatrixXcd> raw_data_part;
				for (int i = 0; i < matVar->dims[2]; i++) {
					MatrixXcd m(matVar->dims[0], matVar->dims[1]);
					for (int j = 0; j < matVar->dims[1]; j++) {
						for (int k = 0; k < matVar->dims[0]; k++) {
							m(k, j) = std::complex<double>(xRe[val_num], xIm[val_num]);
							val_num++;
							if (val_num >= matVar->dims[0] * matVar->dims[1] * matVar->dims[2] * matVar->dims[3]) break;
							//qDebug() << xRe[val_num] << xIm[val_num];
						}
					}
					raw_data_part.push_back(m);
				}
				raw_data.push_back(raw_data_part);
			}

			Global::diffusionRawData = raw_data;

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
							if (val_num >= s_matVar->dims[0] * s_matVar->dims[1] * s_matVar->dims[2]) break;
							//qDebug() << xRe[val_num] << xIm[val_num];
						}
					}
					sensitivity_maps.push_back(m);
				}

				Global::structuralSensitivityMaps = sensitivity_maps;
			}
		}

		matvar_t *l_matVar = 0;
		l_matVar = Mat_VarRead(mat, (char*)"L");
		if (l_matVar) {
			qDebug() << "Otwarto L";
			const double *xData = static_cast<const double*>(l_matVar->data);
			Global::L = xData[0];
		}

		matvar_t *r_matVar = 0;
		r_matVar = Mat_VarRead(mat, (char*)"r");

		if (r_matVar) {
			qDebug() << "Otwarto r";
			const double *xData = static_cast<const double*>(r_matVar->data);
			Global::r = xData[0];
		}

		matvar_t *b_matVar = 0;
		b_matVar = Mat_VarRead(mat, (char*)"b_value");

		if (b_matVar) {
			qDebug() << "Otwarto b_value";
			const double *xData = static_cast<const double*>(b_matVar->data);
			Global::b_value = xData[0];
		}

	}
	qDebug() << Global::L;
	qDebug() << Global::r;
	Mat_Close(mat);
	emit importDone();
}

void ImportWorker::structuralDataImport()
{
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
						if (val_num >= matVar->dims[0] * matVar->dims[1] * matVar->dims[2]) break;
						//qDebug() << xRe[val_num] << xIm[val_num];
					}
				}
				raw_data.push_back(m);
			}

			Global::structuralRawData = raw_data;

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
							if (val_num >= s_matVar->dims[0] * s_matVar->dims[1] * s_matVar->dims[2]) break;
							//qDebug() << xRe[val_num] << xIm[val_num];
						}
					}
					sensitivity_maps.push_back(m);
				}

				Global::structuralSensitivityMaps = sensitivity_maps;
			}
		}

		matvar_t *l_matVar = 0;
		l_matVar = Mat_VarRead(mat, (char*)"L");
		if (l_matVar) {
			qDebug() << "Otwarto L";
			const double *xData = static_cast<const double*>(l_matVar->data);
			Global::L = xData[0];
		}

		matvar_t *r_matVar = 0;
		r_matVar = Mat_VarRead(mat, (char*)"r");

		if (r_matVar) {
			qDebug() << "Otwarto r";
			const double *xData = static_cast<const double*>(r_matVar->data);
			Global::r = xData[0];
		}

	}
	qDebug() << Global::L;
	qDebug() << Global::r;
	Mat_Close(mat);
	emit importDone();
}
