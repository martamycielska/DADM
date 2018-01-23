#include "Brain_3D.h"

Brain_3D::Brain_3D(Data3D data, int xspace, int yspace, int zspace, int threshold, int shrinkingFactor)
{
	qDebug() << "Brain 3D constructor called";
	this->inputData = data;
	this->outputData = vtkSmartPointer<vtkRenderer>::New();
	this->threshold = threshold;
	this->xspace = xspace;
	this->yspace = yspace;
	this->zspace = zspace;
	this->shrinkingFactor = shrinkingFactor;
}

void Brain_3D::Start() {
	createModel3D(inputData);
}

void Brain_3D::createModel3D(Data3D inputData) {

	// Create a MRI image data
	imageData = vtkSmartPointer<vtkImageData>::New();
	imageData->SetDimensions(xspace, yspace, zspace);
	imageData->AllocateScalars(VTK_DOUBLE, 1);
	int* dims = imageData->GetDimensions();

	for (int z = 0; z < dims[2]; z++)
		for (int y = 0; y < dims[1]; y++)
			for (int x = 0; x < dims[0]; x++)
			{
				double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, z));
				pixel[0] = inputData[z](x, y);
			}

	// Shrink data to increase efficiency
	shrink = vtkSmartPointer<vtkImageShrink3D>::New();
	shrink->SetInputData(imageData);
	shrink->SetShrinkFactors(shrinkingFactor, shrinkingFactor, shrinkingFactor);

	// Create cortex isosurface using marching cubes
	this->mc = vtkSmartPointer<vtkMarchingCubes>::New();
	mc->SetInputConnection(shrink->GetOutputPort());
	mc->ComputeNormalsOn();
	mc->ComputeGradientsOn();
	mc->SetValue(0, threshold);

	// Reduce the number of triangles (in percentage)
	decimater = vtkSmartPointer<vtkDecimatePro>::New();
	decimater->SetInputConnection(mc->GetOutputPort());
	//decimate->SetTargetReduction(.99); //99% reduction (if there was 100 triangles, now there will be 1)
	decimater->SetTargetReduction(.6); //60% reduction (if there was 100 triangles, now there will be 40)

	// Create a mapper (mapping isosurface to graphic primitives)
	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(decimater->GetOutputPort());
	//mapper->SetInputConnection(mc->GetOutputPort());
	mapper->ScalarVisibilityOff();

	// Create object to set colors
	colors = vtkSmartPointer<vtkNamedColors>::New();
	// change colors: https://gitlab.kitware.com/vtk/vtk/blob/bc8b0a565766ab3768df6a4f5f07992bdae4afd8/Common/Color/vtkNamedColors.cxx

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

Decimate  Brain_3D::getDecimate()
{
	return decimater;
}


