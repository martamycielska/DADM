#include "Skull_stripping.h"
#include "qdebug.h"

Skull_stripping::Skull_stripping(Data3D data)
{
	qDebug() << "Skull_stripping constructor called";
	this->data3D_input = data;
	dtype = STRUCTURAL_DATA;
}

Skull_stripping::Skull_stripping(Data4D data)
{
	qDebug() << "Skull_stripping constructor called";
	this->data4D_input = data;
	dtype = DIFFUSION_DATA;
}

void Skull_stripping::StructuralDataAlgorithm() {

}

void Skull_stripping::DiffusionDataAlgorithm() {

}