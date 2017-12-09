#include "Non_stationary_noise_estimation.h"
#include "qdebug.h"

template <class InputDataType, class OutputDataType>
Non_stationary_noise_estimation<InputDataType, OutputDataType>::Non_stationary_noise_estimation(InputDataType data, DataType type)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->inputData = data;
	dtype = type;
}

template <class InputDataType, class OutputDataType>
void Non_stationary_noise_estimation<InputDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template <class InputDataType, class OutputDataType>
void Non_stationary_noise_estimation<InputDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template <class InputDataType, class OutputDataType>
Non_stationary_noise_estimation<InputDataType, OutputDataType>::~Non_stationary_noise_estimation()
{
}
