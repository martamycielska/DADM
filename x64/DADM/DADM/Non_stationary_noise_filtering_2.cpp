#include "Non_stationary_noise_filtering_2.h"
#include "qdebug.h"

Non_stationary_noise_filtering_2::Non_stationary_noise_filtering_2(Data3D images, Data3D estim)
{
	qDebug() << "Non stationary noise filtering 2 constructor called";
	this->data3D_input = images;
	estimator3D = estim;
	dtype = STRUCTURAL_DATA;
}

Non_stationary_noise_filtering_2::Non_stationary_noise_filtering_2(Data4D images, Data4D estim)
{
	qDebug() << "Non stationary noise filtering 2 constructor called";
	this->data4D_input = images;
	estimator4D = estim;
	dtype = DIFFUSION_DATA;
}

void Non_stationary_noise_filtering_2::StructuralDataAlgorithm() {

}

void Non_stationary_noise_filtering_2::DiffusionDataAlgorithm() {

}