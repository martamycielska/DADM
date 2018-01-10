#ifndef VISUALIZATION2D_H
#define VISUALIZATION2D_H
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkTextRenderer.h>
#include <sstream>
#include <vtkStructuredPointsReader.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkImageReader.h>
#include <vtkNamedColors.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkBorderWidget.h>
#include <vtkPlane.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkClipPolyData.h>
#include <vtkImplicitPlaneWidget2.h>
#include <QVTKOpenGLWidget.h>
#include <QMainWindow>
#include <QThread>
#include <QVTKOpenGLWidget.h>
#include "Brain_2D.h"


namespace Ui {
	class Visualization2D;
}

class Visualization2D : public QMainWindow
{
	Q_OBJECT

public:
	explicit Visualization2D(QWidget *parent = 0);
	 
private:
	Ui::Visualization2D *ui;
	Brain_2D *brain_2D;

	void InitValue();
	void InitUI();
	void SetConnections();

	private slots:
	void Brain2D();
};

#endif VISUALIZATION2D_H
