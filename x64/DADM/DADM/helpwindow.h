#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>
#include "ui_helpwindow.h"

class helpwindow : public QWidget
{
	Q_OBJECT

public:
	helpwindow(QWidget *parent = 0);
	~helpwindow();

private:
	Ui::helpwindow ui;
};

#endif // HELPWINDOW_H
