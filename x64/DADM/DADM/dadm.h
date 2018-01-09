#ifndef DADM_H
#define DADM_H

#include <QtWidgets/QMainWindow>
#include "ui_dadm.h"
#include "visualization3d.h"
#include "Reconstruction.h"

typedef enum FilteringType {LMMSE, UNLM} FilteringType;

class Worker : public QThread
{
	Q_OBJECT

public:
	Worker(DataType, FilteringType);
	void run();

signals:
	void resultReady();
	void currentProcess(QString);

private:
	DataType dtype;
	FilteringType ftype;

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

	

private slots:
	void mri_reconstruct();
	void onReconstructionFinished(Data3D);
	void visualization3d();
	void importStructuralData();
	void importDiffusionData();
	void onImportDone();
	void structuralTestDataImport();
	void onPreprocessingDone();
	void onImportProgress(int, int);
	void onProccesing(QString);

	void alphaAngleValueChanged(int);
	void betaAngleValueChanged(int);
	void resolutionWidthValueChanged(int);
	void resolutionHeightValueChanged(int);
	void diffusionSlicesSet();
	void diffusionFASet();
	void diffusionMDSet();
	void diffusionRASet();
	void diffusionVRSet();
	void LMMSEFiltrationSet();
	void UNLMFiltrationSet();

	void restoreDefault();
	void showProgramInformation();
};
#endif // DADM_H
