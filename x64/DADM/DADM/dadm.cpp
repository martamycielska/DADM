#include "dadm.h"
#include "visualization3d.h"
#include "Reconstruction.h"
#include "Non_stationary_noise_estimation.h"
#include "Non_stationary_noise_filtering_1.h"
#include "Non_stationary_noise_filtering_2.h"
#include "Intensity_inhomogenity_correction.h"
#include "Intensity_inhomogenity_correction.h"
#include "Skull_stripping.h"
#include "Diffusion_tensor_imaging.h"
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
	connect(ui.actionVisualization_3D, &QAction::triggered, this, &DADM::visualization3d);
	connect(ui.actionStructural_data, &QAction::triggered, this, &DADM::importStructuralData);
	connect(ui.actionDiffusion_data, &QAction::triggered, this, &DADM::importDiffusionData);
	connect(ui.actionRestore_default, &QAction::triggered, this, &DADM::restoreDefault);
	connect(ui.actionInformation, &QAction::triggered, this, &DADM::showProgramInformation);
	connect(ui.actionImport_test_data, &QAction::triggered, this, &DADM::structuralTestDataImport);

	connect(ui.LMMSERadioButton, &QRadioButton::isChecked, this, &DADM::LMMSEFiltrationSet);
	connect(ui.UNLMRadioButton, &QRadioButton::isChecked, this, &DADM::UNLMFiltrationSet);
	connect(ui.alphaPlaneSpinBox, SIGNAL(valueChanged(int)), this, SLOT(alphaAngleValueChanged(int)));
	connect(ui.betaPlaneSpinBox, SIGNAL(valueChanged(int)), this, SLOT(betaAngleValueChanged(int)));
	connect(ui.resolutionWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(resolutionWidthValueChanged(int)));
	connect(ui.resolutionHeightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(resolutionHeightValueChanged(int)));
	connect(ui.diffSlicesRadioButton, &QRadioButton::isChecked, this, &DADM::diffusionSlicesSet);
	connect(ui.diffFARadioButton, &QRadioButton::isChecked, this, &DADM::diffusionFASet);
	connect(ui.diffMDRadioButton, &QRadioButton::isChecked, this, &DADM::diffusionMDSet);
	connect(ui.difRARadioButton, &QRadioButton::isChecked, this, &DADM::diffusionRASet);
	connect(ui.diffVRRadioButton, &QRadioButton::isChecked, this, &DADM::diffusionVRSet);
	ui.progressBar->hide();
}

void DADM::mri_reconstruct() {
	/*
	qRegisterMetaType<Data3D>("Data3D");
	Data3DRaw input;

	worker = new Worker(input);
	connect(worker, &Worker::resultReady, this, &DADM::onReconstructionFinished);
	connect(worker, &Worker::finished, worker, &QObject::deleteLater);
	worker->start();
	*/
}

void DADM::importStructuralData()
{

	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Mat file (*.mat) (*mat)");

	if (url.isEmpty())
		return;

	Global::dtype = STRUCTURAL_DATA;
	ui.statusBar->showMessage("Busy");
	ui.progressBar->show();
	QString path = url.path().remove(0, 1);
	ImportWorker* iw = new ImportWorker(path, STRUCTURAL_DATA);
	connect(iw, &ImportWorker::importDone, this, &DADM::onImportDone);
	connect(iw, &ImportWorker::importProgress, this, &DADM::onImportProgress);
	connect(iw, &Worker::finished, iw, &QObject::deleteLater);
	iw->start();
}

void DADM::importDiffusionData()
{

	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Mat file (*.mat) (*mat)");

	if (url.isEmpty())
		return;

	Global::dtype = DIFFUSION_DATA;
	QString path = url.path().remove(0, 1);
	ui.statusBar->showMessage("Busy");
	ui.progressBar->show();
	ImportWorker* iw = new ImportWorker(path, DIFFUSION_DATA);
	connect(iw, &ImportWorker::importDone, this, &DADM::onImportDone);
	connect(iw, &ImportWorker::importProgress, this, &DADM::onImportProgress);
	connect(iw, &ImportWorker::finished, iw, &QObject::deleteLater);
	iw->start();
}

void DADM::onImportDone()
{
	QMessageBox msgBox;
	msgBox.setText("Data imported");
	msgBox.exec();
	ui.statusBar->showMessage("Ready");

	Worker* worker = new Worker(Global::dtype, Global::ftype);
	connect(worker, &Worker::resultReady, this, &DADM::onPreprocessingDone);
	connect(worker, &Worker::currentProcess, this, &DADM::onProccesing);
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

void DADM::structuralTestDataImport()
{
	qDebug() << "Slot called";
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

		matVar = Mat_VarRead(mat, (char*)"dataset_T1");

		if (matVar) {
			qDebug() << "Otwarto strukturê";

			//unsigned int xSize = matVar->nbytes / matVar->data_size;
			const double *xData = static_cast<const double*>(matVar->data);

			qDebug() << matVar->dims[0];
			qDebug() << matVar->dims[1];
			qDebug() << matVar->dims[2];

			std::vector<MatrixXd> data;
			//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
			int val_num = 0;
			for (int i = 0; i < matVar->dims[2]; i++) {
				MatrixXd m(matVar->dims[0], matVar->dims[1]);
				for (int j = 0; j < matVar->dims[1]; j++) {
					for (int k = 0; k < matVar->dims[0]; k++) {
						m(k, j) = xData[val_num];
						val_num++;
						if (val_num >= matVar->dims[0] * matVar->dims[1] * matVar->dims[2]) break;
						//qDebug() << xData[val_num];
					}
				}
				data.push_back(m);
			}
			Global::structuralData = data;
		}

		Mat_Close(mat);
		QMessageBox msgBox;
		msgBox.setText("Finished");
		msgBox.exec();
	}
}

void DADM::onPreprocessingDone()
{
	ui.progressBar->hide();
	ui.statusBar->showMessage("Ready");
	QMessageBox msgBox;
	msgBox.setText("Preprocessing Done");
	msgBox.exec();
}

void DADM::onImportProgress(int progress, int max)
{
	ui.progressBar->setMaximum(max);
	ui.progressBar->setValue(progress);
}

void DADM::onProccesing(QString msg)
{
	ui.statusBar->showMessage(msg);
}

void DADM::alphaAngleValueChanged(int)
{
}

void DADM::betaAngleValueChanged(int)
{
}

void DADM::resolutionWidthValueChanged(int)
{
}

void DADM::resolutionHeightValueChanged(int)
{
}

void DADM::diffusionSlicesSet()
{
}

void DADM::diffusionFASet()
{
}

void DADM::diffusionMDSet()
{
}

void DADM::diffusionRASet()
{
}

void DADM::diffusionVRSet()
{
}

void DADM::LMMSEFiltrationSet()
{
	Global::ftype = LMMSE;
}

void DADM::UNLMFiltrationSet()
{
	Global::ftype = UNLM;
}

void DADM::restoreDefault()
{
}

void DADM::showProgramInformation()
{
}

DADM::~DADM()
{
	if (vis3D)
		delete vis3D;
}

Worker::Worker(DataType dtype, FilteringType ftype)
{
	this->dtype = dtype;
	this->ftype = ftype;
}

void Worker::run()
{
	Data3D images3D;
	Data4D images4D;
	Data3D rice3D;
	Data4D rice4D;
	switch (dtype)
	{
	case STRUCTURAL_DATA:
	{
		emit currentProcess("Preprocessing: Reconstruction...");
		Reconstruction *reconstruction = new Reconstruction(Global::structuralRawData, Global::structuralSensitivityMaps, Global::L, Global::r);
		reconstruction->Start();
		images3D = reconstruction->getData3D();
		emit currentProcess("Preprocessing: Non stationary noise estimation...");
		Non_stationary_noise_estimation *estimation = new Non_stationary_noise_estimation(images3D);
		estimation->Start();
		rice3D = estimation->getData3D(RICE);
		switch (ftype)
		{
		case LMMSE:
		{
			emit currentProcess("Preprocessing: Non stationary noise filtering...");
			Non_stationary_noise_filtering_1 *lmmse = new Non_stationary_noise_filtering_1(images3D, rice3D);
			lmmse->Start();
			images3D.clear();
			images3D = lmmse->getData3D();
			break;
		}
		case UNLM:
		{
			emit currentProcess("Preprocessing: Non stationary noise filtering...");
			Non_stationary_noise_filtering_2 *unlm = new Non_stationary_noise_filtering_2(images3D, rice3D);
			unlm->Start();
			images3D.clear();
			images3D = unlm->getData3D();
			break;
		}
		}
		emit currentProcess("Preprocessing: Intensity inhomogenity correction...");
		Intensity_inhomogenity_correction *correction = new Intensity_inhomogenity_correction(images3D);
		correction->Start();
		Global::structuralData = correction->getData3D();
		break;
	}
	case DIFFUSION_DATA:
	{
		emit currentProcess("Preprocessing: Reconstruction...");
		Reconstruction *reconstruction = new Reconstruction(Global::diffusionRawData, Global::diffusionSensitivityMaps, Global::L, Global::r);
		reconstruction->Start();
		images4D = reconstruction->getData4D();
		emit currentProcess("Preprocessing: Non stationary noise estimation...");
		Non_stationary_noise_estimation *estimation = new Non_stationary_noise_estimation(images4D);
		estimation->Start();
		rice4D = estimation->getData4D(RICE);
		switch (ftype)
		{
		case LMMSE:
		{
			emit currentProcess("Preprocessing: Non stationary noise filtering...");
			Non_stationary_noise_filtering_1 *lmmse = new Non_stationary_noise_filtering_1(images4D, rice4D);
			lmmse->Start();
			images4D.clear();
			images4D = lmmse->getData4D();
			break;
		}
		case UNLM:
		{
			emit currentProcess("Preprocessing: Non stationary noise filtering...");
			Non_stationary_noise_filtering_2 *unlm = new Non_stationary_noise_filtering_2(images4D, rice4D);
			unlm->Start();
			images4D.clear();
			images4D = unlm->getData4D();
			break;
		}
		}
		emit currentProcess("Preprocessing: Intensity inhomogenity correction...");
		Intensity_inhomogenity_correction *correction = new Intensity_inhomogenity_correction(images4D);
		correction->Start();
		images4D.clear();
		images4D = correction->getData4D();
		emit currentProcess("Preprocessing: Skull stripping...");
		Skull_stripping *skull_stripping = new Skull_stripping(images4D);
		skull_stripping->Start();
		images4D.clear();
		images4D = skull_stripping->getData4D();
		emit currentProcess("Preprocessing: Diffusion tensor imaging...");
		Diffusion_tensor_imaging *diff = new Diffusion_tensor_imaging(images4D);
		diff->Start();
		Global::diffusionData3D = diff->getData();
		Global::FA = diff->getFA();
		Global::RA = diff->getRA();
		Global::MD = diff->getMD();
		Global::VR = diff->getVR();
		break;
	}
	}
	emit resultReady();
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
		matvar_t *matVar = 0;
		matvar_t *s_matVar = 0;

		g_matVar = Mat_VarRead(mat, (char*)"gradients");
		matVar = Mat_VarRead(mat, (char*)"raw_data");
		s_matVar = Mat_VarRead(mat, (char*)"sensitivity_maps");

		int max = 0;
		if (matVar) {
			max += matVar->dims[0]*matVar->dims[1]*matVar->dims[2]*matVar->dims[3];
		}

		if (s_matVar) {
			max += s_matVar->dims[0]*s_matVar->dims[1]*s_matVar->dims[2];
		}

		int status = 0;

		if (g_matVar) {
			qDebug() << "Otwarto gradients";

			//unsigned int xSize = matVar->nbytes / matVar->data_size;
			const double *xData = static_cast<const double*>(g_matVar->data);

			qDebug() << g_matVar->dims[0];
			qDebug() << g_matVar->dims[1];
			max += g_matVar->dims[0]*g_matVar->dims[1];

			//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
			int val_num = 0;
			MatrixXd m(g_matVar->dims[0], g_matVar->dims[1]);
			for (int i = 0; i < g_matVar->dims[1]; i++) {
				for (int j = 0; j < g_matVar->dims[0]; j++) {
					m(j, i) = xData[val_num];
					status++;
					val_num++;
					if (val_num >= g_matVar->dims[0] * g_matVar->dims[1]) break;
					//qDebug() << xData[val_num];
				}
				emit importProgress(status, max);
			}

			Global::gradients = m;
		}

		//matvar_t *matVar = 0;

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
							status++;
							val_num++;
							if (val_num >= matVar->dims[0] * matVar->dims[1] * matVar->dims[2] * matVar->dims[3]) break;
							//qDebug() << xRe[val_num] << xIm[val_num];
						}
						emit importProgress(status, max);
					}
					raw_data_part.push_back(m);
				}
				raw_data.push_back(raw_data_part);
			}

			Global::diffusionRawData = raw_data;

			//matvar_t *s_matVar = 0;
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
							status++;
							val_num++;
							if (val_num >= s_matVar->dims[0] * s_matVar->dims[1] * s_matVar->dims[2]) break;
							//qDebug() << xRe[val_num] << xIm[val_num];
						}
						emit importProgress(status, max);
					}
					sensitivity_maps.push_back(m);
				}

				Global::diffusionSensitivityMaps = sensitivity_maps;
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
		matvar_t *s_matVar = 0;
		s_matVar = Mat_VarRead(mat, (char*)"sensitivity_maps");

		int max = 0;
		if (matVar) {
			max += matVar->dims[0] * matVar->dims[1] * matVar->dims[2];
		}

		if (s_matVar) {
			max += s_matVar->dims[0] * s_matVar->dims[1] * s_matVar->dims[2];
		}

		int status = 0;

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
						status++;
						val_num++;
						if (val_num >= matVar->dims[0] * matVar->dims[1] * matVar->dims[2]) break;
						//qDebug() << xRe[val_num] << xIm[val_num];
					}
					emit importProgress(status, max);
				}
				raw_data.push_back(m);
			}

			Global::structuralRawData = raw_data;

			//matvar_t *s_matVar = 0;
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
							status++;
							val_num++;
							if (val_num >= s_matVar->dims[0] * s_matVar->dims[1] * s_matVar->dims[2]) break;
							//qDebug() << xRe[val_num] << xIm[val_num];
						}
						emit importProgress(status, max);
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

