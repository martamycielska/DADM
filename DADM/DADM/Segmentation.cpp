#include "Segmentation.h"
#include "qdebug.h"


Segmentation::Segmentation(Data3D data)
{
	qDebug() << "Segmentation constructor called";
	this->data = data;
}

void Segmentation::Start() {

}

Segmentation::~Segmentation()
{
}
