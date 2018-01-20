#pragma once
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkTextRenderer.h>
#include <vtkOpenGLTextMapper.h>
#include <vtkOpenGLTexture.h>
#include <vtkAutoInit.h>
#include <sstream>
#include <vtkImageData.h>
#include <MRI_Module.h>

class SliceVisualizator
{
public:
	SliceVisualizator();
	vtkSmartPointer<vtkInteractorObserver> getData();
	vtkSmartPointer<vtkImageViewer2> getImageViewer();
	void setImageViewer(vtkSmartPointer<vtkImageViewer2>);
	~SliceVisualizator();
	void visualize();	

private:
	Data3D inputData;
	vtkSmartPointer<vtkInteractorObserver> myInteractorStyleObserver;
	vtkSmartPointer<vtkImageViewer2> imageViewer;
	int x;
	int y; 
	int z;
};
