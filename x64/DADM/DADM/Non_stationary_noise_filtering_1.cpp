#include "Non_stationary_noise_filtering_1.h"
#include "qdebug.h"

Non_stationary_noise_filtering_1::Non_stationary_noise_filtering_1(Data3D images, Data3D estim)
{
	qDebug() << "Non stationary noise filtering 1 constructor called";
	this->data3D_input = images;
	estimator3D = estim;
	dtype = STRUCTURAL_DATA;
}

Non_stationary_noise_filtering_1::Non_stationary_noise_filtering_1(Data4D images, Data4D estim)
{
	qDebug() << "Non stationary noise filtering 1 constructor called";
	this->data4D_input = images;
	estimator4D = estim;
	dtype = DIFFUSION_DATA;
}

void Non_stationary_noise_filtering_1::StructuralDataAlgorithm() {

}

void Non_stationary_noise_filtering_1::DiffusionDataAlgorithm() {

}
