#include "Upsampling.h"
#include "qdebug.h"


Upsampling::Upsampling(MatrixXd data, int width, int height)
{
	qDebug() << "Upsampling constructor called";
	this->inputData = data;
	this->height = height;
	this->width = width;
}

void Upsampling::Start() {

}

Upsampling::~Upsampling()
{
}

int Upsampling::Rozmiar_uz() {
	int a = 2;
	int b = 2;
	return a,b;
}