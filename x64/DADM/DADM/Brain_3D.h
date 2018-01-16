#pragma once

#include <vtkMarchingCubes.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkImplicitPlaneWidget2.h>
#include <vtkImageShrink3D.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
#include <Segmentation.h>
#include <vtkDecimatePro.h>
#include <QDebug>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

typedef vtkSmartPointer<vtkRenderer> Renderer;
typedef vtkSmartPointer<vtkMarchingCubes> MarchingCubes;
typedef vtkSmartPointer<vtkPolyDataMapper> Mapper;
typedef vtkSmartPointer<vtkDecimatePro> Decimate;

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
	Brain_3D(Data3D data, int xspace, int yspace, int zspace, int threshold, int shrinkingFactor);
	~Brain_3D();
	MarchingCubes getMarchingCubes();
	float getThreshold();
	Mapper getMapper();
	Decimate getDecimate();
	void setRenderer(Renderer renderer);
	void setMarchingCubes(MarchingCubes _mc);
	void setThreshold(int t);
	void setShrinkFactor(int t);
	virtual void Start();

private:
	Data3D profiles;
	void createModel3D(Data3D inputData);
	int shrinkingFactor;
	float threshold;
	int xspace;
	int yspace;
	int zspace;
	MarchingCubes mc;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkDecimatePro> decimater;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkNamedColors> colors;
	vtkSmartPointer<vtkImageShrink3D> shrink;
	vtkSmartPointer<vtkImageData> imageData;
};

