#pragma once
#include "Segmentation.h"

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
#include <vtkImageShrink3D.h>

#include "qstring.h"

typedef vtkSmartPointer<vtkRenderer> Renderer;
typedef vtkSmartPointer<vtkMarchingCubes> MarchingCubes;
typedef vtkSmartPointer<vtkPolyDataConnectivityFilter> Confilter;
typedef vtkSmartPointer<vtkPolyDataMapper> Mapper;

class MyCallback : public vtkCommand
{
public:
	static MyCallback * New()
	{
		return new MyCallback;
	}
	virtual void Execute(vtkObject* caller, unsigned long, void*)
	{
		vtkImplicitPlaneWidget2* planeWidget = reinterpret_cast<vtkImplicitPlaneWidget2*>(caller);
		vtkImplicitPlaneRepresentation* rep = reinterpret_cast<vtkImplicitPlaneRepresentation*>(planeWidget->GetRepresentation());
		rep->GetPlane(this->Plane);
	}

	MyCallback() : Plane(0) {}
	vtkPlane* Plane;
};

class Brain_3D :
	public MRI_Module<Data3D, Renderer>
{
public:
	Brain_3D(QString path, int xspace, int yspace, int zspace, int threshold, int shrinkingFactor);
	Brain_3D(Data3D, int threshold);
	~Brain_3D();
	MarchingCubes getMarchingCubes();
	float getThreshold();
	Mapper getMapper();
	Confilter getConfilter();
	void setRenderer(Renderer renderer);
	void setMarchingCubes(MarchingCubes _mc);
	void setThreshold(int t);
	void setShrinkFactor(int t);
	virtual void Start();
	//virtual Renderer getResult();

private:
	Data3D profiles;
	void initialize(QString path);
	//Renderer getRenderer();
	QString path;
	int shrinkingFactor;
	float threshold;
	int xspace;
	int yspace;
	int zspace;
	//Renderer render;
	MarchingCubes mc;
	vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkNamedColors> colors;
	vtkSmartPointer<vtkImageReader> reader;
	vtkSmartPointer<vtkImageShrink3D> shrink;
};

