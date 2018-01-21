#include "Segmentation.h"
#include "qdebug.h"
#include <Globals.h>
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
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

Segmentation::Segmentation(itk::IndexValueType seed_X, itk::IndexValueType seed_Y, int lowThreshold, int uppThreshold)
{
	//qDebug() << "Segmentation constructor called";
	this->inputData = Global::structuralData;
	this->x = inputData[0].rows();
	this->y = inputData[0].cols();
	this->z = inputData.size();
}

void Segmentation::Start() {

	// Create a MRI image data
	imageData = vtkSmartPointer<vtkImageData>::New();
	imageData->SetDimensions(x, y, z);
	imageData->AllocateScalars(VTK_DOUBLE, 1);
	int* dims = imageData->GetDimensions();

	for (int z = 0; z < dims[2]; z++)
		for (int y = 0; y < dims[1]; y++)
			for (int x = 0; x < dims[0]; x++)
			{
				double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, z));
				pixel[0] = inputData[z](x, y);
			}

	//konwersja do obiektu ITK
	const unsigned int Dimension = 3;
	typedef double InternalPixelType;
	typedef itk::Image<InternalPixelType, Dimension> ImageType;
	typedef itk::VTKImageToImageFilter< ImageType > FilterType;
	FilterType::Pointer filter = FilterType::New();
	filter->SetInput(imageData);

	try
	{
		filter->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
		//return EXIT_FAILURE;
	}

	ImageType::ConstPointer myitkImage = filter->GetOutput();


	//Connected Threshold Image Filter Segmentation
	typedef double InternalPixelType;
	typedef itk::Image<InternalPixelType, Dimension> InternalImageType;

	typedef unsigned char OutputPixelType;
	typedef itk::Image<OutputPixelType, Dimension> OutputImageType;
	typedef itk::CastImageFilter<InternalImageType, OutputImageType> CastingFilterType;
	CastingFilterType::Pointer caster = CastingFilterType::New();

	InternalImageType::Pointer image = InternalImageType::New();
	const InternalImageType::SizeType  size = { { x, y, z } };
	const InternalImageType::IndexType start = { { 0, 0, 0 } };
	InternalImageType::RegionType region;
	region.SetSize(size);
	region.SetIndex(start);
	image->SetRegions(region);
	image->Allocate(true);

	typedef  itk::ImageFileWriter<OutputImageType> WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName("test.png");

	typedef itk::CurvatureFlowImageFilter<InternalImageType, InternalImageType>	CurvatureFlowImageFilterType;

	CurvatureFlowImageFilterType::Pointer smoothing = CurvatureFlowImageFilterType::New();

	typedef itk::ConnectedThresholdImageFilter<InternalImageType, InternalImageType> ConnectedFilterType;

	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();

	smoothing->SetInput(myitkImage);
	connectedThreshold->SetInput(smoothing->GetOutput());
	caster->SetInput(connectedThreshold->GetOutput());
	writer->SetInput(caster->GetOutput());

	smoothing->SetNumberOfIterations(5);
	smoothing->SetTimeStep(0.125);

	const InternalPixelType lowerThreshold = lowThreshold;
	const InternalPixelType upperThreshold = uppThreshold;

	connectedThreshold->SetLower(lowerThreshold);
	connectedThreshold->SetUpper(upperThreshold);

	connectedThreshold->SetReplaceValue(255);

	InternalImageType::IndexType  index;

	index[0] = seed_X;
	index[1] = seed_Y;

	connectedThreshold->SetSeed(index);

	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject & excep)
	{
		std::cerr << "Exception caught !" << std::endl;
		std::cerr << excep << std::endl;
	}

	//return EXIT_SUCCESS;

	//konwersja z itk do vtk i testowe wyświetlenie
	typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;

	ConnectorType::Pointer connector = ConnectorType::New();

	connector->SetInput(myitkImage);

	vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
	actor->SetInput(connector->GetOutput());
#else
	connector->Update();
	actor->SetInputData(connector->GetOutput());
#endif
	vtkSmartPointer<vtkRenderer> renderer =	vtkSmartPointer<vtkRenderer>::New();
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

	//return EXIT_SUCCESS;
}

Segmentation::~Segmentation()
{
}
