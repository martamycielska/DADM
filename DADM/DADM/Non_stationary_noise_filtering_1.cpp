#include "Non_stationary_noise_filtering_1.h"
#include "qdebug.h"

template <class T>
Non_stationary_noise_filtering_1<T>::Non_stationary_noise_filtering_1(T images, T estim, DataType type)
{
	qDebug() << "Non stationary noise filtering 1 constructor called";
	this->data = images;
	estimator = estim;
	dtype = type;
}

template <class T>
void Non_stationary_noise_filtering_1<T>::StructuralDataAlgorithm() {

}

template <class T>
void Non_stationary_noise_filtering_1<T>::DiffusionDataAlgorithm() {

}

template <class T>
Non_stationary_noise_filtering_1<T>::~Non_stationary_noise_filtering_1()
{
}
