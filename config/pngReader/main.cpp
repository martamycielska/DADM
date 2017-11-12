#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2) // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle)

#include "mainwindow.h"
#include <QApplication>

#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkPNGReader.h"
#include "vtkTestUtilities.h"
#include "vtkSmartPointer.h"

#include "QVTKOpenGLWidget.h"
#include <QFileDialog>

int main(int argc, char** argv)
{
  // set surface format before application initialization
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}

