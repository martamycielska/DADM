#pragma once
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
#include <MRI_Module.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);

class UpsamplingVisualizator
{
public:
	UpsamplingVisualizator(Data3D upData);
	~UpsamplingVisualizator();
	void visualize();

private:
	Data3D inputData;
	vtkSmartPointer<vtkImageData> imageData;
	int xspace;
	int yspace;
	int zspace;
};