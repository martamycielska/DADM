#include "Non_stationary_noise_filtering_2.h"
#include "qdebug.h"

template <class InputDataType, class EstimatorDataType, class OutputDataType>
Non_stationary_noise_filtering_2<InputDataType, EstimatorDataType, OutputDataType>::Non_stationary_noise_filtering_2(InputDataType images, EstimatorDataType estim, DataType type)
{
	qDebug() << "Non stationary noise filtering 2 constructor called";
	this->inputData = images;
	estimator = estim;
	dtype = type;
}

template <class InputDataType, class EstimatorDataType, class OutputDataType>
void Non_stationary_noise_filtering_2<InputDataType, EstimatorDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template <class InputDataType, class EstimatorDataType, class OutputDataType>
void Non_stationary_noise_filtering_2<InputDataType, EstimatorDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template <class InputDataType, class EstimatorDataType, class OutputDataType>
Non_stationary_noise_filtering_2<InputDataType, EstimatorDataType, OutputDataType>::~Non_stationary_noise_filtering_2()
{
}
