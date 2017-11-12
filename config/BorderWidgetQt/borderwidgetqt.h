/***
 * Przykład ze strony: https://lorensen.github.io/VTKExamples/site/Cxx/Qt/BorderWidgetQt
 ***/
#ifndef BorderWidgetQt_H
#define BorderWidgetQt_H

#include <vtkSmartPointer.h>
#include <QMainWindow>

class vtkBorderWidget;

#include "ui_borderwidgetqt.h"

class BorderWidgetQt : public QMainWindow, private Ui::BorderWidgetQt
{
  Q_OBJECT
public:

  // Constructor/Destructor
  BorderWidgetQt();
  ~BorderWidgetQt() {}

private:
  vtkSmartPointer<vtkBorderWidget> BorderWidget;
};

#endif
