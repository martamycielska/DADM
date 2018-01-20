#include "Oblique_imaging.h"
#include "qdebug.h"


Oblique_imaging::Oblique_imaging(Data3D data, double a, double b, Profile profile)
{
	qDebug() << "Oblique imaging constructor called";
	this->inputData = data;
	this->a = a;
	this->b = b;
	this->profile = profile;
}

void Oblique_imaging::Start() {

}

Oblique_imaging::~Oblique_imaging()
{
}
