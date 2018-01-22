#include <MultipleSlicesVisualizator.h>
#include "Globals.h"

MultipleSlicesVisualizator::MultipleSlicesVisualizator(Data3D sliceData)
{
	this->inputData = sliceData;
	this->xspace = inputData[0].rows();
	this->yspace = inputData[0].cols();
	this->zspace = inputData.size();
}

void MultipleSlicesVisualizator::visualize()
{

	vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
	imageData->SetDimensions(xspace, yspace, 1);
	imageData->AllocateScalars(VTK_DOUBLE, 1);
	int* dims = imageData->GetDimensions();

	for (int y = 0; y < dims[1]; y++)
		for (int x = 0; x < dims[0]; x++)
		{
			double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, 0));
			pixel[0] = inputData[0](x, y);
		}

	vtkSmartPointer<vtkRenderWindow> renderWindow =	vtkSmartPointer<vtkRenderWindow>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =	vtkSmartPointer<vtkRenderWindowInteractor>::New();

	renderWindowInteractor->SetRenderWindow(renderWindow);

	// Define viewport ranges
	double xmins[5] = { 0, .5, 1, 1.5, 2 };
	double ymins[5] = { 0, 0, 0, 0, 0 };
	double xmaxs[5] = { .5, 1, 1.5, 2, 2.5 };
	double ymaxs[5] = { .5, .5, .5, .5, .5 };
	for (unsigned i = 0; i < 5; i++)
	{
		vtkSmartPointer<vtkRenderer> renderer =	vtkSmartPointer<vtkRenderer>::New();

		renderWindow->AddRenderer(renderer);
		renderer->SetViewport(xmins[i], ymins[i], xmaxs[i], ymaxs[i]);

		vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
		actor->SetInputData(imageData);

		vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
		renderWindowInteractor->SetInteractorStyle(style);

		renderer->AddActor(actor);
		renderer->ResetCamera();

		renderWindow->Render();
		renderWindow->SetWindowName("MultipleSlicesVisualizator");
	}

	renderWindowInteractor->Start();

	//return EXIT_SUCCESS;
}

MultipleSlicesVisualizator::~MultipleSlicesVisualizator()
{
	//destruktor
}