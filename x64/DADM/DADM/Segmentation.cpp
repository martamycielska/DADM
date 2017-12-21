#include "Segmentation.h"
#include "qdebug.h"


Segmentation::Segmentation(Data3D data)
{
	qDebug() << "Segmentation constructor called";
	this->inputData = data;
}

void Segmentation::Start() {

}

Segmentation::~Segmentation()
{
}
