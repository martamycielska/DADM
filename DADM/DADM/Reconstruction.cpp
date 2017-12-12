#include "Reconstruction.h"
#include "qdebug.h"


template <class InputDataType, class OutputDataType>
Reconstruction<InputDataType, OutputDataType>::Reconstruction(InputDataType data, DataType type)
{
	qDebug() << "Reconstruction constructor called";
	inputData = data;
	dtype = type;
}

template Reconstruction<Data3DRaw, Data3D>::Reconstruction(Data3DRaw data, DataType type);
template Reconstruction<Data4DRaw, Data4D>::Reconstruction(Data4DRaw data, DataType type);

template <class InputDataType, class OutputDataType>
void Reconstruction<InputDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template void Reconstruction<Data3DRaw, Data3D>::StructuralDataAlgorithm();
template void Reconstruction<Data4DRaw, Data4D>::StructuralDataAlgorithm();

template <class InputDataType, class OutputDataType>
void Reconstruction<InputDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template void Reconstruction<Data3DRaw, Data3D>::DiffusionDataAlgorithm();
template void Reconstruction<Data4DRaw, Data4D>::DiffusionDataAlgorithm();