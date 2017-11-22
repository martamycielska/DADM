#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

#include "dadm.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>

int main(int argc, char *argv[])
{
    // needed to ensure appropriate OpenGL context is created for VTK rendering.
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
    QApplication a(argc, argv);
    DADM w;
    w.show();

    return a.exec();
}
