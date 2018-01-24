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
#include "Oblique_imaging.h"
#include "Upsampling.h"
#include "helpermethods.h"
#include "Globals.h"
#include <QDebug>
#include <QMessageBox>
#include <Eigen\Dense>
#include <unsupported\Eigen\CXX11\Tensor>
#include "matio.h"
#include "qaction.h"
#include "qfiledialog.h"
#include "qmutex.h"
#include <SliceVisualizator.h>
#include "upsamplingimage.h"
//#include "mat.h"

//using MatFileHandler;
QMutex mutex;

DADM::DADM(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	vis3D = new Visualization3D();
	connect(ui.actionVisualization_3D, &QAction::triggered, this, &DADM::visualization3d);
	connect(ui.actionVisualize_2D, &QAction::triggered, this, &DADM::visualization2d);
	connect(ui.actionStructural_data, &QAction::triggered, this, &DADM::importStructuralData);
	connect(ui.actionDiffusion_data, &QAction::triggered, this, &DADM::importDiffusionData);
	connect(ui.actionRestore_default, &QAction::triggered, this, &DADM::restoreDefault);
	connect(ui.actionInformation, &QAction::triggered, this, &DADM::showProgramInformation);
	connect(ui.actionImport_test_data, &QAction::triggered, this, &DADM::structuralTestDataImport);

	connect(ui.LMMSERadioButton, &QRadioButton::toggled, this, &DADM::LMMSEFiltrationSet);
	connect(ui.UNLMRadioButton, &QRadioButton::toggled, this, &DADM::UNLMFiltrationSet);
	connect(ui.NoneFiltrationRadioButton, &QRadioButton::toggled, this, &DADM::NoneFiltrationSet);

	connect(ui.planeApplyPushButton, SIGNAL(clicked()), this, SLOT(planeValuesChanged()));
	connect(ui.resolutionApplyPushButton, SIGNAL(clicked()), this, SLOT(resolutionValuesChanged()));
	
	connect(ui.diffFARadioButton, &QRadioButton::toggled, this, &DADM::diffusionFASet);
	connect(ui.diffMDRadioButton, &QRadioButton::toggled, this, &DADM::diffusionMDSet);
	connect(ui.difRARadioButton, &QRadioButton::toggled, this, &DADM::diffusionRASet);
	connect(ui.diffVRRadioButton, &QRadioButton::toggled, this, &DADM::diffusionVRSet);
	ui.progressBar->hide();

	connect(ui.xySlider, SIGNAL(valueChanged(int)), this, SLOT(xySliderValueChanged(int)));
	connect(ui.yzSlider, SIGNAL(valueChanged(int)), this, SLOT(yzSliderValueChanged(int)));
	connect(ui.xzSlider, SIGNAL(valueChanged(int)), this, SLOT(xzSliderValueChanged(int)));

	renderWndXY = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	renderWndYZ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	renderWndXZ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	ui.xyVtkWidget->SetRenderWindow(renderWndXY);
	ui.yzVtkWidget->SetRenderWindow(renderWndYZ);
	ui.xzVtkWidget->SetRenderWindow(renderWndXZ);

	ui.xySlider->setMinimum(0);
	ui.xySlider->setMaximum(0);
	ui.xzSlider->setMinimum(0);
	ui.xzSlider->setMaximum(0);
	ui.yzSlider->setMinimum(0);
	ui.yzSlider->setMaximum(0);

	planesSetNum = 0;
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

	Global::structuralData.clear();
	Global::dataXY.clear();
	Global::dataXZ.clear();
	Global::dataYZ.clear();

	Global::structuralData = Data3D(0);
	Global::dataXY = Data3D(0);
	Global::dataXZ = Data3D(0);
	Global::dataYZ = Data3D(0);

	ui.DiffusionPage->hide();
	Global::dtype = STRUCTURAL_DATA;
	ui.statusBar->showMessage("Busy");
	ui.progressBar->show();
	QString path = url.path().remove(0, 1);
	iw = new ImportWorker(path, STRUCTURAL_DATA);
	connect(iw, &ImportWorker::importDone, this, &DADM::onImportDone);
	connect(iw, &ImportWorker::importProgress, this, &DADM::onProgress);
	connect(iw, &Worker::finished, iw, &QObject::deleteLater);
	iw->start();
}

void DADM::importDiffusionData()
{

	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Mat file (*.mat) (*mat)");

	if (url.isEmpty())
		return;

	Global::FA.clear();
	Global::MD.clear();
	Global::RA.clear();
	Global::VR.clear();
	Global::structuralData.clear();
	Global::dataXY.clear();
	Global::dataXZ.clear();
	Global::dataYZ.clear();

	ui.DiffusionPage->show();
	disconnect(ui.diffFARadioButton, &QRadioButton::toggled, this, &DADM::diffusionFASet);
	disconnect(ui.diffMDRadioButton, &QRadioButton::toggled, this, &DADM::diffusionMDSet);
	disconnect(ui.difRARadioButton, &QRadioButton::toggled, this, &DADM::diffusionRASet);
	disconnect(ui.diffVRRadioButton, &QRadioButton::toggled, this, &DADM::diffusionVRSet);

	ui.diffFARadioButton->setChecked(true);
	ui.diffMDRadioButton->setChecked(false);
	ui.diffVRRadioButton->setChecked(false);
	ui.difRARadioButton->setChecked(false);

	connect(ui.diffFARadioButton, &QRadioButton::toggled, this, &DADM::diffusionFASet);
	connect(ui.diffMDRadioButton, &QRadioButton::toggled, this, &DADM::diffusionMDSet);
	connect(ui.difRARadioButton, &QRadioButton::toggled, this, &DADM::diffusionRASet);
	connect(ui.diffVRRadioButton, &QRadioButton::toggled, this, &DADM::diffusionVRSet);

	Global::dtype = DIFFUSION_DATA;
	QString path = url.path().remove(0, 1);
	ui.statusBar->showMessage("Busy");
	ui.progressBar->show();
	iw = new ImportWorker(path, DIFFUSION_DATA);
	connect(iw, &ImportWorker::importDone, this, &DADM::onImportDone);
	connect(iw, &ImportWorker::importProgress, this, &DADM::onProgress);
	connect(iw, &ImportWorker::finished, iw, &QObject::deleteLater);
	iw->start();
}

void DADM::onImportDone()
{
	ui.statusBar->showMessage("Ready");
	ui.progressBar->hide();
	delete iw;
	worker = new Worker(Global::dtype, Global::ftype);
	connect(worker, &Worker::resultReady, this, &DADM::onPreprocessingDone);
	connect(worker, &Worker::currentProcess, this, &DADM::onProccesing);
	connect(worker, &Worker::progress, this, &DADM::onProgress);
	connect(worker, &Worker::finished, worker, &QObject::deleteLater);
	worker->start();
}

void DADM::visualization3d() {
	vis3D = new Visualization3D();
	HelperMethods::SetCenterPosition(vis3D);
	vis3D->show();
}

void DADM::visualization2d() {

	if (Global::dtype == DIFFUSION_DATA) {
		if (Global::FA.size() == 0) return;

		switch (Global::biomarker) {
		case Biomarker::FA:
		{
			//xySliceVisualizator = new SliceVisualizator(renderWndXY, SlicePlane::XY, Global::FA);
			//xySliceVisualizator->visualize();
			break;
		}
		case Biomarker::MD:
		{
			xySliceVisualizator = new SliceVisualizator(renderWndXY, SlicePlane::XY, Global::MD);
			xySliceVisualizator->visualize();
			break;
		}
		case Biomarker::RA:
		{
			xySliceVisualizator = new SliceVisualizator(renderWndXY, SlicePlane::XY, Global::RA);
			xySliceVisualizator->visualize();
			break;
		}
		case Biomarker::VR:
		{
			xySliceVisualizator = new SliceVisualizator(renderWndXY, SlicePlane::XY, Global::VR);
			xySliceVisualizator->visualize();
			break;
		}
		}
	}

	if (Global::dataXY.size() != 0) {
		xySliceVisualizator = new SliceVisualizator(renderWndXY, SlicePlane::XY, Global::dataXY);
		xySliceVisualizator->visualize();
		yzSliceVisualizator = new SliceVisualizator(renderWndYZ, SlicePlane::YZ, Global::dataYZ);
		yzSliceVisualizator->visualize();
		xzSliceVisualizator = new SliceVisualizator(renderWndXZ, SlicePlane::XZ, Global::dataXZ);
		xzSliceVisualizator->visualize();

		
		ui.xySlider->setMinimum(0);
		ui.xySlider->setMaximum(xySliceVisualizator->getImageViewerXY()->GetSliceMax());
		ui.xzSlider->setMinimum(0);
		ui.xzSlider->setMaximum(xzSliceVisualizator->getImageViewerXZ()->GetSliceMax());
		ui.yzSlider->setMinimum(0);
		ui.yzSlider->setMaximum(yzSliceVisualizator->getImageViewerYZ()->GetSliceMax());

		delete xySliceVisualizator;
		delete yzSliceVisualizator;
		delete xzSliceVisualizator;
	}
}

void DADM::xySliderValueChanged(int sliderValue) {
	qDebug() << "Zmieniam XY: " << sliderValue << " slice";
	xySliceVisualizator->getImageViewerXY()->SetSlice(sliderValue);
	xySliceVisualizator->getImageViewerXY()->Render();
}

void DADM::yzSliderValueChanged(int sliderValue) {
	qDebug() << "Zmieniam YZ: " << sliderValue << " slice";
	yzSliceVisualizator->getImageViewerYZ()->SetSlice(sliderValue);
	yzSliceVisualizator->getImageViewerYZ()->Render();
}

void DADM::xzSliderValueChanged(int sliderValue) {
	qDebug() << "Zmieniam XZ: " << sliderValue << " slice";
	xzSliceVisualizator->getImageViewerXZ()->SetSlice(sliderValue);
	xzSliceVisualizator->getImageViewerXZ()->Render();
}

void DADM::closeEvent(QCloseEvent *)
{
	qApp->quit();
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
	ui.statusBar->showMessage("Ready");
	visualization2d();
}

void DADM::onProgress(int progress, int max)
{
	ui.progressBar->setMaximum(max);
	ui.progressBar->setValue(progress);
}

void DADM::onProccesing(QString msg)
{
	ui.statusBar->showMessage(msg);
}

void DADM::resolutionValuesChanged()
{
	if (Global::dataXY.empty()) return;
	if (ui.FrontalPlaneRadioButton->isChecked()) {
		UpsamplingImage *upsamlingImageWindow = new UpsamplingImage(SlicePlane::YZ, ui.resolutionWidthSpinBox->value(), ui.resolutionHeightSpinBox->value(), ui.yzSlider->value());
		upsamlingImageWindow->show();
	}
	if (ui.SaggitalPlaneRadioButton->isChecked()) {
		UpsamplingImage *upsamlingImageWindow = new UpsamplingImage(SlicePlane::XZ, ui.resolutionWidthSpinBox->value(), ui.resolutionHeightSpinBox->value(), ui.xzSlider->value());
		upsamlingImageWindow->show();
	}
	if (ui.HorizontalPlaneRadioButton->isChecked()) {
		UpsamplingImage *upsamlingImageWindow = new UpsamplingImage(SlicePlane::XY, ui.resolutionWidthSpinBox->value(), ui.resolutionHeightSpinBox->value(), ui.xySlider->value());
		upsamlingImageWindow->show();
	}
}

void DADM::planeValuesChanged()
{
	if (Global::dataXY.empty()) return;
	ui.planeApplyPushButton->setEnabled(false);

	ui.statusBar->showMessage("Busy");
	ObliqueImagingWorker *worker_horizontal = new ObliqueImagingWorker(Global::structuralData, ui.alphaPlaneSpinBox->value(), ui.betaPlaneSpinBox->value(), HORIZONTAL, ui.xySlider->maximum());
	connect(worker_horizontal, &ObliqueImagingWorker::resultReadyHorizontal, this, &DADM::onObliqueImagingHorizontalDone);
	connect(worker_horizontal, &ObliqueImagingWorker::finished, worker_horizontal, &QObject::deleteLater);
	worker_horizontal->start();

	ObliqueImagingWorker *worker_frontal = new ObliqueImagingWorker(Global::structuralData, ui.alphaPlaneSpinBox->value(), ui.betaPlaneSpinBox->value(), FRONTAL, ui.xySlider->maximum());
	connect(worker_frontal, &ObliqueImagingWorker::resultReadyFrontal, this, &DADM::onObliqueImagingFrontalDone);
	connect(worker_frontal, &ObliqueImagingWorker::finished, worker_frontal, &QObject::deleteLater);
	worker_frontal->start();

	ObliqueImagingWorker *worker_sagittal = new ObliqueImagingWorker(Global::structuralData, ui.alphaPlaneSpinBox->value(), ui.betaPlaneSpinBox->value(), SAGGITAL, ui.xySlider->maximum());
	connect(worker_sagittal, &ObliqueImagingWorker::resultReadySggital, this, &DADM::onObliqueImagingSaggitalDone);
	connect(worker_sagittal, &ObliqueImagingWorker::finished, worker_sagittal, &QObject::deleteLater);
	worker_sagittal->start();

}

void DADM::diffusionFASet()
{
	if (!ui.diffFARadioButton->isChecked())
		return;

	Global::biomarker = Biomarker::FA;
	visualization2d();
}

void DADM::diffusionMDSet()
{
	if (!ui.diffMDRadioButton->isChecked())
		return;

	Global::biomarker = Biomarker::MD;
	visualization2d();
}

void DADM::diffusionRASet()
{
	if (!ui.difRARadioButton->isChecked())
		return;

	Global::biomarker = Biomarker::RA;
	visualization2d();
}

void DADM::diffusionVRSet()
{
	if (!ui.diffVRRadioButton->isChecked())
		return;

	Global::biomarker = Biomarker::VR;
	visualization2d();
}

void DADM::LMMSEFiltrationSet()
{
	if (!ui.LMMSERadioButton->isChecked())
		return;

	qDebug() << "LMMSE";
	Global::ftype = LMMSE;
}

void DADM::UNLMFiltrationSet()
{
	if (!ui.UNLMRadioButton->isChecked())
		return;

	qDebug() << "UNLM";
	Global::ftype = UNLM;
}

void DADM::NoneFiltrationSet()
{
	if (!ui.NoneFiltrationRadioButton->isChecked())
		return;

	qDebug() << "NONE";
	Global::ftype = NONE;
}

void DADM::restoreDefault()
{
	if (Global::structuralData.empty() || Global::FA.empty()) return;
	ui.alphaPlaneSpinBox->setValue(0);
	ui.betaPlaneSpinBox->setValue(0);
	ui.resolutionWidthSpinBox->setValue(1);
	ui.resolutionHeightSpinBox->setValue(1);

	//------------------------------------------------------------YZ
	Eigen::MatrixXd slice;
	slice = Global::structuralData.at(0);

	int size_z = Global::structuralData.size();
	int size_x = slice.rows();
	int size_y = slice.cols();

	std::vector<MatrixXd> YZ_data_out;
	Eigen::MatrixXd image_out = Eigen::MatrixXd::Zero(size_y, size_z);

	for (int YZ_slice_nr = 0; YZ_slice_nr < size_x; ++YZ_slice_nr) {
		for (int i = 0; i < size_y; ++i) {
			for (int j = 0; j < size_z; ++j) {
				image_out(i, j) = Global::structuralData[j](YZ_slice_nr, i);
			}
		}
		YZ_data_out.push_back(image_out);
	}

	//------------------------------------------------------------ XZ
	slice = Global::structuralData.at(90);

	size_z = Global::structuralData.size();
	size_x = slice.rows();
	size_y = slice.cols();

	std::vector<MatrixXd> XZ_data_out;
	image_out = Eigen::MatrixXd::Zero(size_x, size_z);

	for (int XZ_slice_nr = 0; XZ_slice_nr < size_x; ++XZ_slice_nr) {
		for (int i = 0; i < size_x; ++i) {
			for (int j = 0; j < size_z; ++j) {
				image_out(i, j) = Global::structuralData[j](i, XZ_slice_nr);
			}
		}
		XZ_data_out.push_back(image_out);
	}

	Global::dataXY.clear();
	Global::dataXZ.clear();
	Global::dataYZ.clear();

	Global::dataXY = Data3D(0);
	Global::dataXZ = Data3D(0);
	Global::dataYZ = Data3D(0);

	Global::dataXY = Global::structuralData;
	//Global::structuralData.clear();
	Global::dataYZ = YZ_data_out;
	Global::dataXZ = XZ_data_out;

	visualization2d();
}

void DADM::showProgramInformation()
{
}


void DADM::onObliqueImagingFrontalDone()
{
	qDebug() << "Done FRONTAL";
	mutex.lock();
	planesSetNum += 1;
	mutex.unlock();
	if (planesSetNum == 3) {
		visualization2d();
		ui.planeApplyPushButton->setEnabled(true);
		planesSetNum = 0;
		ui.statusBar->showMessage("Ready");
	}
}

void DADM::onObliqueImagingSaggitalDone()
{
	qDebug() << "Done SAGITTAL";
	mutex.lock();
	planesSetNum += 1;
	mutex.unlock();
	if (planesSetNum == 3) {
		visualization2d();
		ui.planeApplyPushButton->setEnabled(true);
		planesSetNum = 0;
		ui.statusBar->showMessage("Ready");
	}
}

void DADM::onObliqueImagingHorizontalDone()
{
	qDebug() << "Done HORIZONTAL";
	mutex.lock();
	planesSetNum += 1;
	mutex.unlock();
	if (planesSetNum == 3) {
		visualization2d();
		ui.planeApplyPushButton->setEnabled(true);
		planesSetNum = 0;
		ui.statusBar->showMessage("Ready");
	}
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
	Data3D images3D = Data3D(0);
	Data4D images4D = Data4D(0);
	Data3D rice3D = Data3D(0);
	Data4D rice4D = Data4D(0);
	switch (dtype)
	{
	case STRUCTURAL_DATA:
	{
		emit currentProcess("Preprocessing: Reconstruction...");
		Reconstruction *reconstruction = new Reconstruction(Global::structuralRawData, Global::structuralSensitivityMaps, Global::L, Global::r);
		Global::structuralRawData.clear();
		Global::structuralSensitivityMaps.clear();
		reconstruction->Start();
		images3D = reconstruction->getData3D();
		delete reconstruction;
		//odkomentowaæ jesli maj¹ ruszyæ inne modu³y
		if (ftype != NONE) {

			emit currentProcess("Preprocessing: Non stationary noise estimation...");
			Non_stationary_noise_estimation *estimation = new Non_stationary_noise_estimation(images3D);
			estimation->Start();
			rice3D = estimation->getData3D(RICE);
			delete estimation;
			switch (ftype)
			{
			case LMMSE:
			{
				emit currentProcess("Preprocessing: Non stationary noise filtering...");
				Non_stationary_noise_filtering_1 *lmmse = new Non_stationary_noise_filtering_1(images3D, rice3D);
				lmmse->Start();
				images3D.clear();
				images3D = lmmse->getData3D();
				delete lmmse;
				break;
			}
			case UNLM:
			{
				emit currentProcess("Preprocessing: Non stationary noise filtering...");
				Non_stationary_noise_filtering_2 *unlm = new Non_stationary_noise_filtering_2(images3D, rice3D);
				unlm->Start();
				images3D.clear();
				qDebug() << "UNLM getData()";
				images3D = unlm->getData3D();
				delete unlm;
				break;
			}
			}
		}
		/*
		emit currentProcess("Preprocessing: Intensity inhomogenity correction...");
		Intensity_inhomogenity_correction *correction = new Intensity_inhomogenity_correction(images3D);
		correction->Start();
		Global::structuralData = correction->getData3D();
		*/
		//------------------------------------------------------------YZ
		Global::structuralData = images3D;
		Eigen::MatrixXd slice;
		slice = Global::structuralData.at(0);

		int size_z = Global::structuralData.size();
		int size_x = slice.rows();
		int size_y = slice.cols();

		std::vector<MatrixXd> YZ_data_out;
		Eigen::MatrixXd image_out = Eigen::MatrixXd::Zero(size_y, size_z);

		for (int YZ_slice_nr = 0; YZ_slice_nr < size_x; ++YZ_slice_nr) {
			for (int i = 0; i < size_y; ++i) {
				for (int j = 0; j < size_z; ++j) {
					image_out(i, j) = Global::structuralData[j](YZ_slice_nr, i);
				}
			}
			YZ_data_out.push_back(image_out);
		}

		//------------------------------------------------------------ XZ
		slice = Global::structuralData.at(90);

		size_z = Global::structuralData.size();
		size_x = slice.rows();
		size_y = slice.cols();

		std::vector<MatrixXd> XZ_data_out;
		image_out = Eigen::MatrixXd::Zero(size_x, size_z);

		for (int XZ_slice_nr = 0; XZ_slice_nr < size_x; ++XZ_slice_nr) {
			for (int i = 0; i < size_x; ++i) {
				for (int j = 0; j < size_z; ++j) {
					image_out(i, j) = Global::structuralData[j](i, XZ_slice_nr);
				}
			}
			XZ_data_out.push_back(image_out);
		}

		Global::dataXY = Global::structuralData;
		//Global::structuralData.clear();
		Global::dataYZ = YZ_data_out;
		Global::dataXZ = XZ_data_out;

		qDebug() << Global::dataXY.size();
		qDebug() << Global::dataYZ.size();
		qDebug() << Global::dataXZ.size();
		
		break;
	}
	case DIFFUSION_DATA:
	{
		emit currentProcess("Preprocessing: Reconstruction...");
		Reconstruction *reconstruction = new Reconstruction(Global::diffusionRawData, Global::diffusionSensitivityMaps, Global::L, Global::r);
		reconstruction->Start();
		Global::diffusionRawData.clear();
		Global::diffusionSensitivityMaps.clear();
		images4D = reconstruction->getData4D();
		delete reconstruction;
		if (ftype != NONE) {
			emit currentProcess("Preprocessing: Non stationary noise estimation...");
			Non_stationary_noise_estimation *estimation = new Non_stationary_noise_estimation(images4D);
			estimation->Start();
			rice4D = estimation->getData4D(RICE);
			delete estimation;
			switch (ftype)
			{
			case LMMSE:
			{
				emit currentProcess("Preprocessing: Non stationary noise filtering...");
				Non_stationary_noise_filtering_1 *lmmse = new Non_stationary_noise_filtering_1(images4D, rice4D);
				lmmse->Start();
				images4D.clear();
				images4D = lmmse->getData4D();
				delete lmmse;
				break;
			}
			case UNLM:
			{
				emit currentProcess("Preprocessing: Non stationary noise filtering...");
				Non_stationary_noise_filtering_2 *unlm = new Non_stationary_noise_filtering_2(images4D, rice4D);
				unlm->Start();
				images4D.clear();
				images4D = unlm->getData4D();
				delete unlm;
				break;
			}
			}
		}
		Global::diffusionData4D = images4D;
		/*
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
		*/
		emit currentProcess("Preprocessing: Diffusion tensor imaging...");
		Diffusion_tensor_imaging *diff = new Diffusion_tensor_imaging(images4D, Global::b_value, Global::gradients);
		diff->Start();
		//Global::diffusionData4D = diff->getData();
		Global::FA = diff->getFA();
		Global::RA = diff->getRA();
		Global::MD = diff->getMD();
		Global::VR = diff->getVR();
		delete diff;
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
			max += matVar->dims[0]*matVar->dims[1]*matVar->dims[2]*matVar->dims[3] * matVar->dims[4];
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
			}
			emit importProgress(status, max);

			Global::gradients = m;
		}

		Mat_VarFree(g_matVar);

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
			qDebug() << matVar->dims[4];

			//std::vector<MatrixXcd> raw_data;
			//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
			int val_num = 0;
			std::vector<std::vector<std::vector<MatrixXcd>>> raw_data;
			for (int m = 0; m < matVar->dims[4]; m++) {
				std::vector<std::vector<MatrixXcd>> raw_data_part_one;
				for (int l = 0; l < matVar->dims[3]; l++) {
					std::vector<MatrixXcd> raw_data_part_two;
					for (int i = 0; i < matVar->dims[2]; i++) {
						MatrixXcd m(matVar->dims[0], matVar->dims[1]);
						for (int j = 0; j < matVar->dims[1]; j++) {
							for (int k = 0; k < matVar->dims[0]; k++) {
								m(k, j) = std::complex<double>(xRe[val_num], xIm[val_num]);
								status++;
								val_num++;
								if (val_num >= matVar->dims[0] * matVar->dims[1] * matVar->dims[2] * matVar->dims[3] * matVar->dims[4]) break;
								//qDebug() << xRe[val_num] << xIm[val_num];
							}
						}
						raw_data_part_two.push_back(m);
						emit importProgress(status, max);
					}
					raw_data_part_one.push_back(raw_data_part_two);
				}
				raw_data.push_back(raw_data_part_one);
			}

			//----------------------
			
			Data5DRaw RawData5D(matVar->dims[2]);
			Data4DRaw RawData(matVar->dims[3]);
			Data3DRaw data(matVar->dims[4]);
			for (int b = 0; b < matVar->dims[2]; b++) {
				for (int d = 0; d < matVar->dims[3]; d++)
				{
					for (int f = 0; f < matVar->dims[4]; f++)
					{
						data.at(f) = raw_data.at(f).at(d).at(b);

					}
					RawData.at(d) = data;
				}
				RawData5D.at(b) = RawData;
			}

			Global::diffusionRawData = RawData5D;
			RawData5D.clear();
			Mat_VarFree(matVar);
			//------------------------------------
			//Data5DRaw RawData5D(1);
			//RawData5D[0] = RawData;

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
					}
					sensitivity_maps.push_back(m);
					emit importProgress(status, max);
				}

				Global::diffusionSensitivityMaps = sensitivity_maps;
				sensitivity_maps.clear();
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

		Mat_VarFree(s_matVar);
		Mat_VarFree(r_matVar);
		Mat_VarFree(l_matVar);
		Mat_VarFree(b_matVar);
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
		int max = 0;

		matvar_t *s_matVar = 0;
		s_matVar = Mat_VarRead(mat, (char*)"sensitivity_maps");

		if (s_matVar) {
			max += s_matVar->dims[0] * s_matVar->dims[1] * s_matVar->dims[2];
		}

		Mat_VarFree(s_matVar);

		matvar_t *matVar = 0;
		matVar = Mat_VarRead(mat, (char*)"raw_data");

		if (matVar) {
			max += matVar->dims[0] * matVar->dims[1] * matVar->dims[2] * matVar->dims[3];
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
			qDebug() << matVar->dims[3];

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
					}
					raw_data_part.push_back(m);
					emit importProgress(status, max);
				}
				raw_data.push_back(raw_data_part);
			}
			//Data4DRaw DataRaw4D(1);
			//DataRaw4D[0] = raw_data;
			Data4DRaw RawData(matVar->dims[2]);
			Data3DRaw data(matVar->dims[3]);
			for (int d = 0; d<matVar->dims[2]; d++)
			{
				for (int f = 0; f < matVar->dims[3]; f++)
				{
					data.at(f) = raw_data.at(f).at(d);

				}
				RawData.at(d) = data;
			}
			Global::structuralRawData = RawData;
			RawData.clear();
			Mat_VarFree(matVar);
			//matvar_t *s_matVar = 0;
			s_matVar = 0;
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
					}
					sensitivity_maps.push_back(m);
					emit importProgress(status, max);
				}
				Global::structuralSensitivityMaps = sensitivity_maps;
				sensitivity_maps.clear();
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

		Mat_VarFree(s_matVar);
		Mat_VarFree(r_matVar);
		Mat_VarFree(l_matVar);

	}
	
	qDebug() << Global::L;
	qDebug() << Global::r;
	Mat_Close(mat);
	mat = 0;
	emit importDone();
}


ObliqueImagingWorker::ObliqueImagingWorker(Data3D data, double a, double b, Profile profile, int max) {
	qRegisterMetaType<Data3D>("Data3D");
	this->profile = profile;
	this->data = data;
	this->a = a;
	this->b = b;
	this->max_slice = max;
}

void ObliqueImagingWorker::run() {
	Oblique_imaging *imaging;
	Data3D d;
	switch (profile) {
	case SAGGITAL:
		for (int i = 0; i < Global::dataXZ.size(); i++) {
			qDebug() << "Iteration sagittal: " << i;
			imaging = new Oblique_imaging(data, a, b, SAGGITAL, i);
			imaging->Start();
			d.push_back(imaging->getData());
			delete imaging;
		}
		Global::dataXZ = d;
		break;
		break;
	case FRONTAL:
		for (int i = 0; i < Global::dataYZ.size(); i++) {
			qDebug() << "Iteration frontal: " << i;
			imaging = new Oblique_imaging(data, a, b, FRONTAL, i);
			imaging->Start();
			d.push_back(imaging->getData());
			delete imaging;
		}
		Global::dataYZ = d;
		break;
	case HORIZONTAL:
		for (int i = 0; i < Global::dataXY.size(); i++) {
			qDebug() << "Iteration horizontal: " << i;
			imaging = new Oblique_imaging(data, a, b, HORIZONTAL, i);
			imaging->Start();
			d.push_back(imaging->getData());
			delete imaging;
		}
		Global::dataXY = d;
		break;
	}
	switch (profile) {
	case FRONTAL:
		emit resultReadyFrontal();
		break;
	case SAGGITAL:
		emit resultReadySggital();
		break;
	case HORIZONTAL:
		emit resultReadyHorizontal();
		break;
	}
}


