//#pragma once
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
typedef vtkSmartPointer<vtkPolyDataConnectivityFilter> Confilter;
typedef vtkSmartPointer<vtkPolyDataMapper> Mapper;

class Brain_2D :
	public MRI_Module<Data3D, Renderer>
{
public:
	Brain_2D(QString path);
	Brain_2D(Data3D, int threshold);
	~Brain_2D();
	void setRenderer(Renderer renderer);
	virtual void Start();
	//Mapper getMapper();
	//Confilter getConfilter();

private:
	Data3D profiles;
	void initialize(QString path);
	QString path;
	//float threshold;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkImageReader> reader;
};

