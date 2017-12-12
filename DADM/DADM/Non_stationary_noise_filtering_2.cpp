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

template Non_stationary_noise_filtering_2<Data3D, Data3D, Data3D>::Non_stationary_noise_filtering_2(Data3D data, Data3D estim, DataType type);
template Non_stationary_noise_filtering_2<Data4D, Data4D, Data4D>::Non_stationary_noise_filtering_2(Data4D data, Data4D estim, DataType type);
template Non_stationary_noise_filtering_2<Data4D, Data3D, Data4D>::Non_stationary_noise_filtering_2(Data4D data, Data3D estim, DataType type);

template <class InputDataType, class EstimatorDataType, class OutputDataType>
void Non_stationary_noise_filtering_2<InputDataType, EstimatorDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template void Non_stationary_noise_filtering_2<Data3D, Data3D, Data3D>::StructuralDataAlgorithm();
template void Non_stationary_noise_filtering_2<Data4D, Data4D, Data4D>::StructuralDataAlgorithm();
template void Non_stationary_noise_filtering_2<Data4D, Data3D, Data4D>::StructuralDataAlgorithm();

template <class InputDataType, class EstimatorDataType, class OutputDataType>
void Non_stationary_noise_filtering_2<InputDataType, EstimatorDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template void Non_stationary_noise_filtering_2<Data3D, Data3D, Data3D>::DiffusionDataAlgorithm();
template void Non_stationary_noise_filtering_2<Data4D, Data4D, Data4D>::DiffusionDataAlgorithm();
template void Non_stationary_noise_filtering_2<Data4D, Data3D, Data4D>::DiffusionDataAlgorithm();