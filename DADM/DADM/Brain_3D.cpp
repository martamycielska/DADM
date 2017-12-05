#include "Brain_3D.h"
#include "qdebug.h"

Brain_3D::Brain_3D(QString path, int xspace, int yspace, int zspace, int threshold, int shrinkingFactor)
{
	qDebug() << "Brain 3D constructor called";
	this -> path = path;
	this -> mc = vtkSmartPointer<vtkMarchingCubes>::New();
	this -> render = vtkSmartPointer<vtkRenderer>::New();
	this -> threshold = threshold;
	this -> xspace = xspace;
	this -> yspace = yspace;
	this -> zspace = zspace;
	this -> shrinkingFactor = shrinkingFactor;
}

void Brain_3D::start() {
	initialize(path);	
}

Renderer Brain_3D::getResult() {
	return this->getRenderer();	
}

void Brain_3D::initialize(QString path) {

	QByteArray ba = path.toLatin1();
	const char* fileName = ba.data();
	int extractLargest = 0;
	//DO ODCZYTANIA Z WYMIARÓW MACIERZY

	reader = vtkSmartPointer<vtkImageReader>::New();
	reader->SetFileName(fileName);
	reader->SetFileDimensionality(3);
	reader->SetNumberOfScalarComponents(1);
	reader->SetDataExtent(0, xspace, 0, yspace, 0, zspace);
	//reader->SetDataSpacing(0.145, 0.145, 0.145); usuniête na potrzeby wyœwietlania danego przekroju
	reader->SetDataScalarTypeToChar();
	reader->Update();

	shrink = vtkSmartPointer<vtkImageShrink3D>::New();
	shrink->SetInputConnection(reader->GetOutputPort());
	shrink->SetShrinkFactors(shrinkingFactor, shrinkingFactor, shrinkingFactor);

    colors = vtkSmartPointer<vtkNamedColors>::New();

	// Create a 3D model using marching cubes
	this->mc = vtkSmartPointer<vtkMarchingCubes>::New();
	mc->SetInputConnection(shrink->GetOutputPort());
	mc->ComputeNormalsOn();
	mc->ComputeGradientsOn();
	mc->SetValue(0, threshold);

	// To remain largest region
	confilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
	confilter->SetInputConnection(mc->GetOutputPort());
	confilter->SetExtractionModeToLargestRegion();

	// Create a mapper
	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	if (extractLargest)
		mapper->SetInputConnection(confilter->GetOutputPort());
	else
		mapper->SetInputConnection(mc->GetOutputPort());

	// set utilize actor's property
	mapper->ScalarVisibilityOff();

	// Visualize
	actor = vtkSmartPointer<vtkActor>::New();
	actor->GetProperty()->SetColor(colors->GetColor3d("titanium_white").GetData());
	actor->SetMapper(mapper);

	// VTK Renderer
	this->render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);
	render->SetBackground(colors->GetColor3d("black").GetData());
	render->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
	render->GetActiveCamera()->SetPosition(0.0, 1.0, 0.0);
	render->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	render->ResetCamera();
	render->GetActiveCamera()->Azimuth(30.0);
	render->GetActiveCamera()->Elevation(30.0);

	// change colors: https://gitlab.kitware.com/vtk/vtk/blob/bc8b0a565766ab3768df6a4f5f07992bdae4afd8/Common/Color/vtkNamedColors.cxx
}

Renderer Brain_3D::getRenderer()
{
	return render;
}

void Brain_3D::setRenderer(Renderer renderer)
{
	render = renderer;
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

Confilter Brain_3D::getConfilter()
{
	return confilter;
}

void Brain_3D::setShrinkFactor(int value)
{
	shrink->SetShrinkFactors(value, value, value);
}


