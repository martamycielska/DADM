#include "Intensity_inhomogenity_correction.h"
#include "qdebug.h"

Intensity_inhomogenity_correction::Intensity_inhomogenity_correction(Data3D data)
{
	qDebug() << "Intensity inhomogenity correction constructor called";
	this->data3D_input = data;
	dtype = STRUCTURAL_DATA;
}

Intensity_inhomogenity_correction::Intensity_inhomogenity_correction(Data4D data)
{
	qDebug() << "Intensity inhomogenity correction constructor called";
	this->data4D_input = data;
	dtype = DIFFUSION_DATA;
}

void Intensity_inhomogenity_correction::StructuralDataAlgorithm() {

}

void Intensity_inhomogenity_correction::DiffusionDataAlgorithm() {

}
