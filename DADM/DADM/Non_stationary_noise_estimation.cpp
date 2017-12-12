#include "Non_stationary_noise_estimation.h"
#include "qdebug.h"

template <class InputDataType, class OutputDataType>
Non_stationary_noise_estimation<InputDataType, OutputDataType>::Non_stationary_noise_estimation(InputDataType data, DataType type)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->inputData = data;
	dtype = type;
}

template Non_stationary_noise_estimation<Data3D, Data3D>::Non_stationary_noise_estimation(Data3D data, DataType type);
template Non_stationary_noise_estimation<Data4D, Data4D>::Non_stationary_noise_estimation(Data4D data, DataType type);
template Non_stationary_noise_estimation<Data4D, Data3D>::Non_stationary_noise_estimation(Data4D data, DataType type);

template <class InputDataType, class OutputDataType>
void Non_stationary_noise_estimation<InputDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template void Non_stationary_noise_estimation<Data3D, Data3D>::StructuralDataAlgorithm();
template void Non_stationary_noise_estimation<Data4D, Data4D>::StructuralDataAlgorithm();
template void Non_stationary_noise_estimation<Data4D, Data3D>::StructuralDataAlgorithm();

template <class InputDataType, class OutputDataType>
void Non_stationary_noise_estimation<InputDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template void Non_stationary_noise_estimation<Data3D, Data3D>::DiffusionDataAlgorithm();
template void Non_stationary_noise_estimation<Data4D, Data4D>::DiffusionDataAlgorithm();
template void Non_stationary_noise_estimation<Data4D, Data3D>::DiffusionDataAlgorithm();