#include "Diffusion_tensor_imaging.h"
#include "qdebug.h"


Diffusion_tensor_imaging::Diffusion_tensor_imaging(Data4D data)
{
	qDebug() << "Diffusion tensor imaging constructor called";
	this->inputData = data;
}

void Diffusion_tensor_imaging::Start() {

}

Diffusion_tensor_imaging::~Diffusion_tensor_imaging()
{
}
