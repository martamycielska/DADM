#ifndef DADM_H
#define DADM_H

#include <QtWidgets/QMainWindow>
#include "ui_dadm.h"
#include "visualization3d.h"
#include "Reconstruction.h"

class Worker : public QThread
{
	Q_OBJECT

public:
	Worker(Data3DRaw);
	void run();

signals:
	void resultReady(QString);

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

private slots:
	void mri_reconstruct();
	void onReconstructionFinished(QString str);
	void visualization3d();
};
#endif // DADM_H
