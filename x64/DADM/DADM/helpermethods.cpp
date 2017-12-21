#include "helpermethods.h"
#include <QDesktopWidget>
#include <QApplication>

HelperMethods::HelperMethods(){
}

//Method to set main window in the center of screen
void HelperMethods::SetCenterPosition(QMainWindow *window){
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-window->width()) / 2;
    int y = (screenGeometry.height()-window->height()) / 2;
    window->move(x, y);
}
