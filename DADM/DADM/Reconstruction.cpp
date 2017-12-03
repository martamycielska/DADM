#include "Reconstruction.h"
#include "qdebug.h"

Reconstruction::Reconstruction(QString path)
{
	qDebug() << "Reconstruction constructor called";
	this->path = path;
}

void MRI_Module::process() {

}

float*** MRI_Module::getResult() {
	return 0;
}

Reconstruction::~Reconstruction()
{
}
