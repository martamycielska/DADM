#ifndef VISUALIZATION3D_H
#define VISUALIZATION3D_H
#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>
#include <Eigen\Dense>

#include <vtkMarchingCubes.h>
#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPlane.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkClipPolyData.h>
#include <vtkImplicitPlaneWidget2.h>
#include <matio.h>

#include "Brain_3D.h"
#include "ui_visualization3d.h"


namespace Ui {
	class Visualization3D;
}

class VisualizationWorker : public QThread
{
	Q_OBJECT

public:
	VisualizationWorker(Brain_3D*);
	void run();

signals:
	void ModelCreationDone();
	void CuttingPlaneDone();

private:
	Brain_3D *brain_3D;
};

class Visualization3D : public QMainWindow
{
	Q_OBJECT

public:
	explicit Visualization3D(QWidget *parent = 0);

private:
	Ui::Visualization3D *ui;
	QString processDescString;
	VisualizationWorker *worker;
	Brain_3D *brain_3D;
	int threshold;
	int shrinkingFactor;
	int xspace;
	int yspace;
	int zspace;
	bool visualizationDone;
	bool setCutOptionEnable;
	Data3D inputData;
	vtkSmartPointer<vtkPlane> plane;
	vtkSmartPointer<vtkClipPolyData> clipper;
	vtkSmartPointer<MyCallback> myCallback;
	vtkSmartPointer<vtkImplicitPlaneRepresentation> rep;
	vtkSmartPointer<vtkImplicitPlaneWidget2> planeWidget;
	void InitValue();
	void InitUI();
	void SetConnections();
	void UpdateProcessStateText(QString text);
	void ReadMatFile(QString path);
	void SetDataSize();

	private slots:
	void Brain3D();
	void AcceptThreshold();
	void SliderValueChanged(int);
	void CutEnableChanged(bool);
	void AddRendererAndPlaneWidget();
};

#endif // VISUALIZATION3D_H
