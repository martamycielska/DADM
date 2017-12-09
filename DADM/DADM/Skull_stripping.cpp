#include "Skull_stripping.h"
#include "qdebug.h"

template <class InputDataType, class OutputDataType>
Skull_stripping<InputDataType, OutputDataType>::Skull_stripping(InputDataType data, DataType type)
{
	qDebug() << "Skull stripping constructor called";
	this->inputData = data;
	dtype = type;
}

template <class InputDataType, class OutputDataType>
void Skull_stripping<InputDataType, OutputDataType>::StructuralDataAlgorithm() {

}

template <class InputDataType, class OutputDataType>
void Skull_stripping<InputDataType, OutputDataType>::DiffusionDataAlgorithm() {

}

template <class InputDataType, class OutputDataType>
Skull_stripping<InputDataType, OutputDataType>::~Skull_stripping()
{
}