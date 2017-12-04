#include "Reconstruction.h"
#include "qdebug.h"

Reconstruction::Reconstruction(QString path)
{
	qDebug() << "Reconstruction constructor called";
	this->path = path;
}

void Reconstruction::start() {

}

float*** Reconstruction::getResult() {
	return image;
}



Reconstruction::~Reconstruction()
{
}
