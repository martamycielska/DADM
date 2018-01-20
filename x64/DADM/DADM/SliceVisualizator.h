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
#include <vtkGenericOpenGLRenderWindow.h>
#include <MRI_Module.h>
#include <qdebug.h>

typedef vtkSmartPointer<vtkGenericOpenGLRenderWindow> RenderWindow;
typedef vtkSmartPointer<vtkImageViewer2> Viewer;

class SliceVisualizator
{
public:
	SliceVisualizator(RenderWindow renderWnd, SlicePlane plane, Data3D visData);
	~SliceVisualizator();
	SlicePlane plane;
	Viewer getImageViewerXY();
	Viewer getImageViewerYZ();
	Viewer getImageViewerXZ();
	void visualize();	

private:
	Data3D inputData;
	RenderWindow renderWndXY;
	RenderWindow renderWndYZ;
	RenderWindow renderWndXZ; 
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractorXY;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractorYZ;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractorXZ;
	vtkSmartPointer<vtkImageViewer2> imageViewerXY;
	vtkSmartPointer<vtkImageViewer2> imageViewerYZ;
	vtkSmartPointer<vtkImageViewer2> imageViewerXZ;
	vtkSmartPointer<vtkImageData> imageData;
	int x;
	int y; 
	int z;
};
