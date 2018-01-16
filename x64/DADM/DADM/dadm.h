#ifndef DADM_H
#define DADM_H

#include <QtWidgets/QMainWindow>
#include "ui_dadm.h"
#include "visualization3d.h"
#include "Reconstruction.h"
#include "helpermethods.h"
#include "Oblique_imaging.h"

class Worker : public QThread
{
	Q_OBJECT

public:
	Worker(DataType, FilteringType);
	void run();

signals:
	void resultReady();
	void currentProcess(QString);
	void progress(int, int);

private:
	DataType dtype;
	FilteringType ftype;

};

class ObliqueImagingWorker : public QThread
{
	Q_OBJECT

public:
	ObliqueImagingWorker(Data3D, double, double, Profile);
	void run();

signals:
	void resultReadyFrontal(Data3D);
	void resultReadySggital(Data3D);
	void resultReadyHorizontal(Data3D);

private:
	Profile profile;
	Data3D data;
	double a;
	double b;
};

class UpsamplingWorker : public QThread
{
	Q_OBJECT

public:
	UpsamplingWorker(Data3D, int, int, Profile);
	void run();

signals:
	void resultReadyFrontal(Data3D);
	void resultReadySggital(Data3D);
	void resultReadyHorizontal(Data3D);

private:
	Profile profile;
	Data3D data;
	int width;
	int height;
};

class ImportWorker : public QThread
{
	Q_OBJECT

public:
	ImportWorker(QString, DataType);
	void run();
	void diffusionDataImport();
	void structuralDataImport();

signals:
	void importDone();
	void importProgress(int, int);

private:
	DataType dtype;
	QString path;
};

class DADM : public QMainWindow
{
	Q_OBJECT
		Q_SLOT

public:
	DADM(QWidget *parent = 0);
	~DADM();

private:
	Ui::DADMClass ui;
	Visualization3D *vis3D;
	Worker *worker;

protected:
	void closeEvent(QCloseEvent*);

private slots:
	void mri_reconstruct();
	void onReconstructionFinished(Data3D);
	void visualization3d();
	void importStructuralData();
	void importDiffusionData();
	void onImportDone();
	void structuralTestDataImport();
	void onPreprocessingDone();
	void onProgress(int, int);
	void onProccesing(QString);

	void resolutionValuesChanged();
	void planeValuesChanged();
	void diffusionFASet();
	void diffusionMDSet();
	void diffusionRASet();
	void diffusionVRSet();
	void LMMSEFiltrationSet();
	void UNLMFiltrationSet();

	void restoreDefault();
	void showProgramInformation();

	void onUpsamplingFrontalDone(Data3D);
	void onUpsamplingSaggitalDone(Data3D);
	void onUpsamplingHorizontalDone(Data3D);
	void onObliqueImagingFrontalDone(Data3D);
	void onObliqueImagingSaggitalDone(Data3D);
	void onObliqueImagingHorizontalDone(Data3D);
};
#endif // DADM_H
