#include "Non_stationary_noise_filtering_2.h"
#include "qdebug.h"

template <class T>
Non_stationary_noise_filtering_2<T>::Non_stationary_noise_filtering_2(T images, T estim, DataType type)
{
	qDebug() << "Non stationary noise filtering 2 constructor called";
	this->data = images;
	estimator = estim;
	dtype = type;
}

template <class T>
void Non_stationary_noise_filtering_2<T>::StructuralDataAlgorithm() {

}

template <class T>
void Non_stationary_noise_filtering_2<T>::DiffusionDataAlgorithm() {

}

template <class T>
Non_stationary_noise_filtering_2<T>::~Non_stationary_noise_filtering_2()
{
}
