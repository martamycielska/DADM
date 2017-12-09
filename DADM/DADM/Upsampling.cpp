#include "Upsampling.h"
#include "qdebug.h"


Upsampling::Upsampling(Data3D data)
{
	qDebug() << "Upsampling constructor called";
	this->inputData = data;
}

void Upsampling::Start() {

}

Upsampling::~Upsampling()
{
}
