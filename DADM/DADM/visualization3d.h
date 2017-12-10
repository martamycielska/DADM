#ifndef VISUALIZATION3D_H
#define VISUALIZATION3D_H
#include <QMainWindow>
#include <QThread>

#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include <vtkMarchingCubes.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageReader.h>
#include <vtkNamedColors.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkBorderWidget.h>
#include <vtkPlane.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkClipPolyData.h>
#include <vtkImplicitPlaneWidget2.h>
#include <QVTKOpenGLWidget.h>

#include "Brain_3D.h"

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
		//bool setCutOptionEnable;
		//vtkSmartPointer<vtkPlane> plane;
		//vtkSmartPointer<vtkClipPolyData> clipper;
		//vtkSmartPointer<MyCallback> myCallback;
		//vtkSmartPointer<vtkImplicitPlaneRepresentation> rep;
		//vtkSmartPointer<vtkImplicitPlaneWidget2> planeWidget;
		void InitValue();
		void InitUI();
		void SetConnections();
		void UpdateProcessStateText(QString text);

    private slots:
        void Brain3D();
		void AcceptThreshold();
		void SliderValueChanged(int);
	    void ShrinkSliderValueChanged(int);
		//void CutEnableChanged(bool);
		void AddRendererAndPlaneWidget();
};

#endif // VISUALIZATION3D_H
