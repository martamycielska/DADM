#include "Skull_stripping.h"
#include "qdebug.h"

template <class InputDataType, class OutputDataType>
Skull_stripping<InputDataType, OutputDataType>::Skull_stripping(InputDataType data, DataType type)
{
	qDebug() << "Skull stripping constructor called";
	this->inputData = data;
	dtype = type;
}

template Skull_stripping<Data3D, Data3D>::Skull_stripping(Data3D data, DataType type);
template Skull_stripping<Data4D, Data4D>::Skull_stripping(Data4D data, DataType type);

template <class InputDataType, class OutputDataType>
void Skull_stripping<InputDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template void Skull_stripping<Data3D, Data3D>::StructuralDataAlgorithm();
template void Skull_stripping<Data4D, Data4D>::StructuralDataAlgorithm();

template <class InputDataType, class OutputDataType>
void Skull_stripping<InputDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template void Skull_stripping<Data3D, Data3D>::DiffusionDataAlgorithm();
template void Skull_stripping<Data4D, Data4D>::DiffusionDataAlgorithm();