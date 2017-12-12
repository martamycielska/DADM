#include "Intensity_inhomogenity_correction.h"
#include "qdebug.h"

template <class InputDataType, class OutputDataType>
Intensity_inhomogenity_correction<InputDataType, OutputDataType>::Intensity_inhomogenity_correction(InputDataType data)
{
	qDebug() << "Intensity inhomogenity correction constructor called";
	this->inputData = data;
}

template <class InputDataType, class OutputDataType>
void Intensity_inhomogenity_correction<InputDataType, OutputDataType>::Start() {

}

template <class InputDataType, class OutputDataType>
Intensity_inhomogenity_correction<InputDataType, OutputDataType>::~Intensity_inhomogenity_correction()
{
}
