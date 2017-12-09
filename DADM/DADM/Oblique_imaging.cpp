#include "Oblique_imaging.h"
#include "qdebug.h"


Oblique_imaging::Oblique_imaging(Data3D data, int profile_idx, double a, double b)
{
	qDebug() << "Oblique imaging constructor called";
	this->inputData = data;
	current_profile = profile_idx;
	this->a = a;
	this->b = b;
}

void Oblique_imaging::Start() {

}

Oblique_imaging::~Oblique_imaging()
{
}
