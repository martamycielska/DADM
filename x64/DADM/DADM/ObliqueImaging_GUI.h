#ifndef OBLIQUEIMAGING_GUI_H
#define OBLIQUEIMAGING_GUI_H

#include <QWidget>
#include "ui_ObliqueImaging_GUI.h"

class ObliqueImaging_GUI : public QWidget
{
	Q_OBJECT

public:
	ObliqueImaging_GUI(QWidget *parent = 0);
	~ObliqueImaging_GUI();

private:
	Ui::ObliqueImaging_GUI ui;
};

#endif // OBLIQUEIMAGING_GUI_H
