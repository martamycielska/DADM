#include "Intensity_inhomogenity_correction.h"
#include "qdebug.h"

template <class T, class U>
Intensity_inhomogenity_correction<T, U>::Intensity_inhomogenity_correction(T data)
{
	qDebug() << "Intensity inhomogenity correction constructor called";
	this->inputData = data;
}

template <class T, class U>
void Intensity_inhomogenity_correction<T, U>::Start() {

}

template <class T, class U>
Intensity_inhomogenity_correction<T, U>::~Intensity_inhomogenity_correction()
{
}
