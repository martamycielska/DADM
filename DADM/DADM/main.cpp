#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

#include "dadm.h"
#include "classes/helpermethods.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	// needed to ensure appropriate OpenGL context is created for VTK rendering.
	//QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
	QApplication a(argc, argv);
	DADM w;
	HelperMethods::SetCenterPosition(&w); //set the main window in the center of screen
	w.show();
	return a.exec();
}
