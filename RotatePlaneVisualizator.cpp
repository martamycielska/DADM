#include <RotatePlaneVisualizator.h>
#include "Globals.h"

RotatePlaneVisualizator::RotatePlaneVisualizator(Data3D sliceData)
{
	this->inputData = sliceData;
	this->xspace = inputData[0].rows();
	this->yspace = inputData[0].cols();
	this->zspace = inputData.size();
}

void RotatePlaneVisualizator::visualize()
{

	vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
	imageData->SetDimensions(xspace, yspace, 1);
	imageData->AllocateScalars(VTK_DOUBLE, 1);
	int* dims = imageData->GetDimensions();

	for (int y = 0; y < dims[1]; y++)
		for (int x = 0; x < dims[0]; x++)
		{
			double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, 0));
			pixel[0] = inputData[1](x, y);
		}

	vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
#if VTK_MAJOR_VERSION <= 5
	imageSliceMapper->SetInputConnection(imageData->GetProducerPort());
#else
	imageSliceMapper->SetInputData(imageData);
#endif
	vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
	imageSlice->SetMapper(imageSliceMapper);

	// Setup renderers
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddViewProp(imageSlice);
	renderer->ResetCamera();

	// Setup render window
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetSize(300, 300);
	renderWindow->AddRenderer(renderer);

	// Setup render window interactor
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =	vtkSmartPointer<vtkRenderWindowInteractor>::New();

	//vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	//renderWindowInteractor->SetInteractorStyle(style);

	// Render and start interaction
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();

	renderWindowInteractor->Start();

	//return EXIT_SUCCESS;
}

RotatePlaneVisualizator::~RotatePlaneVisualizator()
{
	//destruktor
}