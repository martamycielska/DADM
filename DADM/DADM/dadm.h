#ifndef DADM_H
#define DADM_H

#include <QtWidgets/QMainWindow>
#include "ui_dadm.h"
#include "visualization3d.h"

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

private slots:
	void mri_reconstruct();
	void onReconstructionFinished(QString str);
	void visualization3d();
};

#endif // DADM_H
