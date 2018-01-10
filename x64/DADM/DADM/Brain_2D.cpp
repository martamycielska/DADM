#include "Brain_2D.h"
#include "qdebug.h"

#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

Brain_2D::Brain_2D(QString path)
{
	qDebug() << "Brain 2D constructor called";
	this->path = path;
	this->outputData = vtkSmartPointer<vtkRenderer>::New();
}

Brain_2D::Brain_2D(Data3D profiles, int param)
{
	this->inputData = profiles;
}

void Brain_2D::Start() {
	initialize(path);
}

void Brain_2D::initialize(QString path) {

	QByteArray ba = path.toLatin1();
	const char* fileName = ba.data();
	int extractLargest = 0;

	reader = vtkSmartPointer<vtkImageReader>::New();
	reader->SetFileName(fileName);
	reader->Update();

	outputData = vtkSmartPointer<vtkRenderer>::New();
	outputData->AddActor(actor);
}

void Brain_2D::setRenderer(Renderer renderer)
{
	outputData = renderer;
}


Brain_2D::~Brain_2D()
{

}

