#ifndef DADM_H
#define DADM_H

#include <QtWidgets/QMainWindow>
#include "ui_dadm.h"
#include "visualization3d.h"
#include "Reconstruction.h"
#include "Upsampling_GUI.h"
#include "ObliqueImaging_GUI.h"

typedef enum FilteringType {LMMSE, UNLM} FilteringType;

class Worker : public QThread
{
	Q_OBJECT

public:
	Worker(DataType, FilteringType);
	void run();

signals:
	void resultReady();

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
	Upsampling_GUI *UpsamplingWindow;
	ObliqueImaging_GUI *ObliqueImagingWindow;

	private slots:
	void mri_reconstruct();
	void onReconstructionFinished(Data3D);
	void visualization3d();
	void openNewWindowUpsampling();
	void openNewWindowObliqueImaging();
	void importStructuralData();
	void importDiffusionData();
	void onImportDone();
	void structuralTestDataImport();
	void onPreprocessingDone();
};
#endif // DADM_H
