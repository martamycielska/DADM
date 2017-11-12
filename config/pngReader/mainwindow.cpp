#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkPNGReader.h"
#include "vtkTestUtilities.h"
#include "vtkSmartPointer.h"

#include "QVTKOpenGLWidget.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//      QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
    ui->setupUi(this);

 //     QVTKOpenGLWidget widget;
 //     widget.resize(512,512);

      vtkSmartPointer<vtkGenericOpenGLRenderWindow> renWin =
              vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
 //     widget.SetRenderWindow(renWin);
      ui->qvtkWindow->SetRenderWindow(renWin);


      vtkSmartPointer<vtkPNGReader> reader =
              vtkSmartPointer<vtkPNGReader>::New();
      //char* fname = vtkTestUtilities::ExpandDataFileName(argc, argv, "Data/vtk.png");

      QString fileNameDCM = QFileDialog::getOpenFileName();
      std::string stdstrFileNameDCM = fileNameDCM.toUtf8().constData();

      reader->SetFileName(stdstrFileNameDCM.c_str());
      //delete [] fname;

      vtkSmartPointer<vtkImageViewer> image_view =
              vtkSmartPointer<vtkImageViewer>::New();
      // use our render window with image_view
      image_view->SetRenderWindow(renWin);
      image_view->SetInputConnection(reader->GetOutputPort());
      image_view->SetupInteractor(renWin->GetInteractor());
      image_view->SetColorLevel(138.5);
      image_view->SetColorWindow(233);

      ui->qvtkWindow->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
