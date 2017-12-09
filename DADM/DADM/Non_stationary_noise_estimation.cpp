#include "Non_stationary_noise_estimation.h"
#include "qdebug.h"

template <class T>
Non_stationary_noise_estimation<T>::Non_stationary_noise_estimation(T data, DataType type)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->data = data;
	dtype = type;
}

template <class T>
void Non_stationary_noise_estimation<T>::StructuralDataAlgorithm() {

}

template <class T>
void Non_stationary_noise_estimation<T>::DiffusionDataAlgorithm() {

}

template <class T>
Non_stationary_noise_estimation<T>::~Non_stationary_noise_estimation()
{
}
