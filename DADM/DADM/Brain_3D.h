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

#include "qstring.h"

typedef vtkSmartPointer<vtkRenderer> Renderer;
typedef vtkSmartPointer<vtkMarchingCubes> MarchingCubes;

class Brain_3D :
	public Segmentation
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

private:
	float threshold;
	Renderer render;
	MarchingCubes mc;
};

