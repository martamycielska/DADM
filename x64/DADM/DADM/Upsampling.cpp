#include "Upsampling.h"
#include "qdebug.h"


Upsampling::Upsampling(MatrixXd data)
{
	qDebug() << "Upsampling constructor called";
	this->inputData = data;
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