#include "Brain_3D.h"
#include "qdebug.h"

Brain_3D::Brain_3D(QString path)
{
	qDebug() << "Brain 3D constructor called";
	this->path = path;
	this->mc = vtkSmartPointer<vtkMarchingCubes>::New();
	this->render = vtkSmartPointer<vtkRenderer>::New();
	threshold = 100;
}

void Brain_3D::start() {
	initialize(path);
}

float*** Brain_3D::getResult() {
	return 0;
}

void Brain_3D::initialize(QString path) {

	QByteArray ba = path.toLatin1();
	const char* fileName = ba.data();
	int extractLargest = 0;

	vtkImageReader *reader = vtkImageReader::New();
	reader->SetFileName(fileName);
	reader->SetFileDimensionality(3);
	reader->SetNumberOfScalarComponents(1);
	reader->SetDataExtent(0, 180, 0, 216, 0, 180);
	reader->SetDataSpacing(0.145, 0.145, 0.145);
	reader->SetDataScalarTypeToChar();
	reader->Update();

	vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

	// Create a 3D model using marching cubes
	this->mc = vtkSmartPointer<vtkMarchingCubes>::New();
	mc->SetInputConnection(reader->GetOutputPort());
	mc->ComputeNormalsOn();
	mc->ComputeGradientsOn();
	mc->SetValue(0, threshold);

	// To remain largest region
	vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
	confilter->SetInputConnection(mc->GetOutputPort());
	confilter->SetExtractionModeToLargestRegion();

	// Create a mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	if (extractLargest)
		mapper->SetInputConnection(confilter->GetOutputPort());
	else
		mapper->SetInputConnection(mc->GetOutputPort());

	// set utilize actor's property
	mapper->ScalarVisibilityOff();

	// Visualize
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->GetProperty()->SetColor(colors->GetColor3d("Flesh").GetData());
	actor->SetMapper(mapper);

	// VTK Renderer
	this->render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);
	render->SetBackground(colors->GetColor3d("Burlywood").GetData());
	render->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
	render->GetActiveCamera()->SetPosition(0.0, 1.0, 0.0);
	render->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
	render->ResetCamera();
	render->GetActiveCamera()->Azimuth(30.0);
	render->GetActiveCamera()->Elevation(30.0);

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

void Brain_3D::setThreshold(float t)
{
	threshold = t;
}

void Brain_3D::MarchingCubesSetValue(float t)
{
	threshold = t;
	mc->SetValue(0, t);
}

Brain_3D::~Brain_3D()
{

}
