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
