#include "Brain_3D.h"
#include "qdebug.h"

Brain_3D::Brain_3D(int xspace, int yspace, int zspace, int threshold)
{
	qDebug() << "Brain 3D constructor called";
	this->mc = vtkSmartPointer<vtkMarchingCubes>::New();
	this->render = vtkSmartPointer<vtkRenderer>::New();
	this -> threshold = threshold;
	this -> xspace = xspace;
	this -> yspace = yspace;
	this -> zspace = zspace;
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
	shrink->SetShrinkFactors(2, 2, 2);

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

//void Brain_3D::cutPlane() {
//	plane = vtkSmartPointer<vtkPlane>::New();
//	plane->SetNormal(1, 0, 0);
//	clipper = vtkSmartPointer<vtkClipPolyData>::New();
//	clipper->SetClipFunction(plane);
//	clipper->InsideOutOn();
//
//	myCallback = vtkSmartPointer<MyCallback>::New();
//	myCallback->Plane = plane;
//
//	rep = vtkSmartPointer<vtkImplicitPlaneRepresentation>::New();
//	rep->SetPlaceFactor(1.0); // This must be set prior to placing the widget
//	rep->SetNormal(plane->GetNormal());
//	rep->OutlineTranslationOff();
//	rep->ScaleEnabledOff();
//	rep->GetPlaneProperty()->SetOpacity(0.0);
//	rep->GetSelectedPlaneProperty()->SetOpacity(0.2);
//
//	planeWidget = vtkSmartPointer<vtkImplicitPlaneWidget2>::New();
//	//vtkInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//	planeWidget->SetInteractor(vtkInteractor);
//	planeWidget->SetRepresentation(rep);
//	planeWidget->AddObserver(vtkCommand::InteractionEvent, myCallback);
//	//planeWidget->SetEnabled(true);
//
//	planeWidget->On();
//	clipper->SetInputConnection(confilter->GetOutputPort());
//	mapper->SetInputConnection(clipper->GetOutputPort());
//
//	plane->SetOrigin(xspace / 2., yspace / 2., zspace / 2.);
//	plane->SetNormal(0, -1, 0);
//	rep->SetNormal(plane->GetNormal());
//
//	double bounds[6];
//	bounds[0] = 0;
//	bounds[1] = xspace;
//	bounds[2] = 0;
//	bounds[3] = yspace;
//	bounds[4] = 0;
//	bounds[5] = zspace;
//
//	plane->SetNormal(1., 0., 0.);
//	rep->PlaceWidget(bounds);
//	rep->SetOrigin(plane->GetOrigin());
//	rep->SetNormal(plane->GetNormal());
//
//	qDebug() << "Jestem w cutPlane()";
//}

Renderer Brain_3D::getRenderer()
{
	return render;
}

//void Brain_3D::setVTKInteractor(vtkSmartPointer<vtkRenderWindowInteractor> interactor) 
//{
//	vtkInteractor = interactor;
//}

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
	test();
}

Mapper Brain_3D::getMapper()
{
	return mapper;
}

Confilter Brain_3D::getConfilter()
{
	return confilter;
}


