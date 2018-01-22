#include <UpsamplingVisualizator.h>

UpsamplingVisualizator::UpsamplingVisualizator(Data3D upData)
{
	this->inputData = upData;
	this->xspace = inputData[0].rows();
	this->yspace = inputData[0].cols();
	this->zspace = inputData.size();
}

void UpsamplingVisualizator::visualize()
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


	vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
	actor->SetInputData(imageData);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->ResetCamera();

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();
}

UpsamplingVisualizator::~UpsamplingVisualizator()
{
	//destruktor
}