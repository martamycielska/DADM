#ifndef DADM_H
#define DADM_H

#include <QtWidgets/QMainWindow>
#include "ui_dadm.h"
#include "visualization3d.h"
#include "Reconstruction.h"
#include "Upsampling_GUI.h"
#include "ObliqueImaging_GUI.h"

class Worker : public QThread
{
	Q_OBJECT

public:
	Worker(Data3DRaw);
	void run();

signals:
	void resultReady(Data3D);

private:
	Data3DRaw input;

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
	void openFile();
};
#endif // DADM_H
