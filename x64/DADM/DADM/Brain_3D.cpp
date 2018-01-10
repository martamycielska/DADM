#include "Brain_3D.h"

Brain_3D::Brain_3D(QString path, int xspace, int yspace, int zspace, int threshold, int shrinkingFactor)
{
	qDebug() << "Brain 3D constructor called";
	this -> path = path;
	this -> outputData = vtkSmartPointer<vtkRenderer>::New();
	this -> threshold = threshold;
	this -> xspace = xspace;
	this -> yspace = yspace;
	this -> zspace = zspace;
	this -> shrinkingFactor = shrinkingFactor;
}

Brain_3D::Brain_3D(Data3D profiles, int threshold)
{
	this->inputData = profiles;
	this->threshold = threshold;
}

void Brain_3D::Start() {
	initialize(path);	
}

void Brain_3D::initialize(QString path) {

	QByteArray ba = path.toLatin1();
	const char* fileName = ba.data();
	int extractLargest = 0;

	//Read data from RAW file
	reader = vtkSmartPointer<vtkImageReader>::New();
	reader->SetFileName(fileName);
	reader->SetFileDimensionality(3);
	reader->SetNumberOfScalarComponents(1);
	reader->SetDataExtent(0, xspace, 0, yspace, 0, zspace);
	reader->SetDataScalarTypeToChar();
	reader->Update();

	// Shrink data to increase efficiency
	shrink = vtkSmartPointer<vtkImageShrink3D>::New();
	shrink->SetInputConnection(reader->GetOutputPort());
	shrink->SetShrinkFactors(shrinkingFactor, shrinkingFactor, shrinkingFactor);

    colors = vtkSmartPointer<vtkNamedColors>::New();

	// Create cortex isosurface using marching cubes
	this->mc = vtkSmartPointer<vtkMarchingCubes>::New();
	mc->SetInputConnection(shrink->GetOutputPort());
	mc->ComputeNormalsOn();
	mc->ComputeGradientsOn();
	mc->SetValue(0, threshold);

	// Create a mapper
	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(mc->GetOutputPort());
	mapper->ScalarVisibilityOff();

	// Create Actor and set color
	actor = vtkSmartPointer<vtkActor>::New();
	actor->GetProperty()->SetColor(colors->GetColor3d("titanium_white").GetData());
	actor->SetMapper(mapper);

	// Rendering process
	outputData = vtkSmartPointer<vtkRenderer>::New();
	outputData->AddActor(actor);
	outputData->SetBackground(colors->GetColor3d("black").GetData());
	outputData->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
	outputData->GetActiveCamera()->SetPosition(0.0, 1.0, 0.0);
	outputData->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	outputData->ResetCamera();
	outputData->GetActiveCamera()->Azimuth(30.0);
	outputData->GetActiveCamera()->Elevation(30.0);

	// change colors: https://gitlab.kitware.com/vtk/vtk/blob/bc8b0a565766ab3768df6a4f5f07992bdae4afd8/Common/Color/vtkNamedColors.cxx
}

void Brain_3D::setRenderer(Renderer renderer)
{
	outputData = renderer;
}

MarchingCubes Brain_3D::getMarchingCubes()
{
	return mc;
}

void Brain_3D::setMarchingCubes(MarchingCubes _mc)
{
	mc = _mc;
}

float Brain_3D::getThreshold()
{
	return threshold;
}

void Brain_3D::setThreshold(int t)
{
	threshold = t;
}


Brain_3D::~Brain_3D()
{

}

Mapper Brain_3D::getMapper()
{
	return mapper;
}

void Brain_3D::setShrinkFactor(int value)
{
	shrink->SetShrinkFactors(value, value, value);
}


