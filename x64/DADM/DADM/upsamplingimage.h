#ifndef UPSAMPLINGIMAGE_H
#define UPSAMPLINGIMAGE_H

#include <QWidget>
#include "ui_upsamplingimage.h"
#include "MRI_Module.h"

class UpsamplingWorker : public QThread
{
	Q_OBJECT

public:
	UpsamplingWorker(MatrixXd image, int width, int height);
	void run();

signals:
	void processingDone(MatrixXd);

private:
	MatrixXd image;
	int width;
	int height;
};

class UpsamplingImage : public QWidget
{
	Q_OBJECT

public:
	UpsamplingImage(SlicePlane, int, int, int, QWidget *parent = 0);
	~UpsamplingImage();

public slots:
	void onProessingDone(MatrixXd);

private:
	Ui::UpsamplingImage ui;
	SlicePlane plane;
	int width;
	int height;
	int slice;
};

#endif // UPSAMPLINGIMAGE_H
