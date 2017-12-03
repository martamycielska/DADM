#pragma once
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

#include "qstring.h"

#include "MRI_Module.h"

typedef vtkSmartPointer<vtkRenderer> Renderer;
typedef vtkSmartPointer<vtkMarchingCubes> MarchingCubes;

class Brain_3D:
	public MRI_Module
{
public:
	Brain_3D();
	~Brain_3D();
	void initialize(QString path);
	Renderer getRenderer();
	void setRenderer(Renderer renderer);
	MarchingCubes getMarchingCubes();
	void setMarchingCubes(MarchingCubes _mc);
	float getThreshold();
	void setThreshold(float t);
	void MarchingCubesSetValue(float t);

private:
	float threshold;
	Renderer render;
	MarchingCubes mc;
};

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

