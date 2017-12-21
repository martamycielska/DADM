#include "Non_stationary_noise_estimation.h"
#include "qdebug.h"

Non_stationary_noise_estimation::Non_stationary_noise_estimation(Data3D data)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->data3D_input = data;
	dtype = STRUCTURAL_DATA;
}

Non_stationary_noise_estimation::Non_stationary_noise_estimation(Data4D data)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->data4D_input = data;
	dtype = DIFFUSION_DATA;
}

void Non_stationary_noise_estimation::StructuralDataAlgorithm() {

}

void Non_stationary_noise_estimation::DiffusionDataAlgorithm() {

}
