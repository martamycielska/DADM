#include "Intensity_inhomogenity_correction.h"
#include "qdebug.h"

template <class InputDataType, class OutputDataType>
Intensity_inhomogenity_correction<InputDataType, OutputDataType>::Intensity_inhomogenity_correction(InputDataType data, DataType type)
{
	qDebug() << "Intensity inhomogenity correction constructor called";
	this->inputData = data;
	dtype = type;
}

template Intensity_inhomogenity_correction<Data3D, Data3D>::Intensity_inhomogenity_correction(Data3D data, DataType type);
template Intensity_inhomogenity_correction<Data4D, Data4D>::Intensity_inhomogenity_correction(Data4D data, DataType type);

template <class InputDataType, class OutputDataType>
void Intensity_inhomogenity_correction<InputDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template void Intensity_inhomogenity_correction<Data3D, Data3D>::StructuralDataAlgorithm();
template void Intensity_inhomogenity_correction<Data4D, Data4D>::StructuralDataAlgorithm();

template <class InputDataType, class OutputDataType>
void Intensity_inhomogenity_correction<InputDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template void Intensity_inhomogenity_correction<Data3D, Data3D>::DiffusionDataAlgorithm();
template void Intensity_inhomogenity_correction<Data4D, Data4D>::DiffusionDataAlgorithm();