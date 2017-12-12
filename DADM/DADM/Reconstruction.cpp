#include "Reconstruction.h"
#include "qdebug.h"

template <class InputDataType, class OutputDataType>
Reconstruction<InputDataType, OutputDataType>::Reconstruction(InputDataType data)
{
	qDebug() << "Reconstruction constructor called";
	inputData = data;
}

template <class InputDataType, class OutputDataType>
void Reconstruction<InputDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template <class InputDataType, class OutputDataType>
void Reconstruction<InputDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template <class InputDataType, class OutputDataType>
Reconstruction<InputDataType, OutputDataType>::~Reconstruction()
{
}
