#include "upsamplingimage.h"
#include "Upsampling.h"
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkNamedColors.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

UpsamplingImage::UpsamplingImage(SlicePlane plane, int width, int height, int slice, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->plane = plane;
	this->width = width;
	this->height = height;
	this->slice = slice;

	
	switch (plane) {
	case SlicePlane::XY:
	{
		UpsamplingWorker *worker = new UpsamplingWorker(Global::dataXY.at(slice), width, height);
		connect(worker, &UpsamplingWorker::finished, worker, &QObject::deleteLater);
		connect(worker, &UpsamplingWorker::processingDone, this, &UpsamplingImage::onProessingDone);
		worker->start();
		break;
	}
	case SlicePlane::XZ:
	{
		UpsamplingWorker *worker = new UpsamplingWorker(Global::dataXZ.at(slice), width, height);
		connect(worker, &UpsamplingWorker::finished, worker, &QObject::deleteLater);
		connect(worker, &UpsamplingWorker::processingDone, this, &UpsamplingImage::onProessingDone);
		worker->start();
		break;
	}
	case SlicePlane::YZ:
	{
		UpsamplingWorker *worker = new UpsamplingWorker(Global::dataYZ.at(slice), width, height);
		connect(worker, &UpsamplingWorker::finished, worker, &QObject::deleteLater);
		connect(worker, &UpsamplingWorker::processingDone, this, &UpsamplingImage::onProessingDone);
		worker->start();
		break;
	}
	}
}

void UpsamplingImage::onProessingDone(MatrixXd outputData) {
	ui.status->hide();

	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	ui.widget->SetRenderWindow(renderWnd);

	//wizualizacja
	int xspace = outputData.rows();
	int yspace = outputData.cols();

	vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
	imageData->SetDimensions(xspace, yspace, 1);
	imageData->AllocateScalars(VTK_DOUBLE, 1);
	int* dims = imageData->GetDimensions();

	for (int y = 0; y < dims[1]; y++)
		for (int x = 0; x < dims[0]; x++)
		{
			double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, 0));
			pixel[0] = outputData(x, y);
		}

	vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
	actor->SetInputData(imageData);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->ResetCamera();

	//vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	//renderWindow->AddRenderer(renderer);
	ui.widget->GetRenderWindow()->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->SetRenderWindow(ui.widget->GetRenderWindow());
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();
}

UpsamplingImage::~UpsamplingImage()
{

}

UpsamplingWorker::UpsamplingWorker(MatrixXd image, int width, int height) {
	qRegisterMetaType<MatrixXd>("MatrixXd");
	this->image = image;
	this->width = width;
	this->height = height;
}

void UpsamplingWorker::run() {
	Upsampling *upsampling = new Upsampling(image, width, height);
	upsampling->Start();
	qDebug() << "DONE";
	emit processingDone(upsampling->getData());
	delete upsampling;
	qDebug() << "EMITTED";
}