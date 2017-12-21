#ifndef UPSAMPLING_GUI_H
#define UPSAMPLING_GUI_H

#include <QWidget>
#include "ui_Upsampling_GUI.h"

class Upsampling_GUI : public QWidget
{
	Q_OBJECT

public:
	Upsampling_GUI(QWidget *parent = 0);
	~Upsampling_GUI();

private:
	Ui::Upsampling_GUI ui;
};

#endif // UPSAMPLING_GUI_H
