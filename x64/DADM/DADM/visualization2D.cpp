#include "visualization2D.h"
#include "ui_visualization2D.h"
#include <QThread>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <QFileDialog>
#include <QTimer>
#include "Globals.h"
#include "helpermethods.h"
#include "qdebug.h"
#include "dadm.h"
#include <Eigen\Dense>
#include <iostream>
#include <vtkStructuredPointsReader.h>
#include <vtkRendererCollection.h>
#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkImageActor.h>
#include <stdlib.h>



Visualization2D::Visualization2D(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Visualization2D)
{
	InitValue();
	SetConnections();
	InitUI();
}

void Visualization2D::Brain2D() {
	
	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Mat file (*.mat) (*mat)");

	if (url.isEmpty())
		return;

	QString path = url.path().remove(0, 1);
	brain_2D = new Brain_2D(path);


	//c-style image test image
	const int width = 4;
	const int height = 4;
	const int depth = 4;

	unsigned char cImage[width * height * depth];
	unsigned char value = 0;
	for (unsigned int row = 0; row < height; ++row) {
		for (unsigned int col = 0; col < width; ++col) {
			for (unsigned int z = 0; z < depth; ++z) {
				cImage[row * width * depth + col * depth + z] = 100;
			}
		}
	}

	//tu dodaæ definicjê wskaŸnika cImage do macierzy danych

	vtkSmartPointer<vtkImageImport> imageImport =
		vtkSmartPointer<vtkImageImport>::New();
	imageImport->SetDataSpacing(1, 1, 1);
	imageImport->SetDataOrigin(0, 0, 0);
	imageImport->SetWholeExtent(0, width-1, 0, height-1, 0, 0);
	imageImport->SetDataExtentToWholeExtent();
	imageImport->SetDataScalarTypeToUnsignedChar();
	imageImport->SetNumberOfScalarComponents(1);
	imageImport->SetImportVoidPointer(cImage); //cImage - wskaŸnik do macierzy
	imageImport->Update();

	vtkSmartPointer<vtkImageActor> actor =
		vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
	actor->SetInput(imageImport->GetOutput());
#else
	actor->SetInputData(imageImport->GetOutput());
#endif

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->ResetCamera();

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style =
		vtkSmartPointer<vtkInteractorStyleImage>::New();

	renderWindowInteractor->SetInteractorStyle(style);

	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();

	renderWindowInteractor->Start();

	//return EXIT_SUCCESS;
}

void Visualization2D::InitValue() {
	ui->setupUi(this);
}

void Visualization2D::SetConnections() {
	connect(ui->visualizeBtn, SIGNAL(clicked(bool)), this, SLOT(Brain2D()));
}

void Visualization2D::InitUI() {
}
