#include "Intensity_inhomogenity_correction.h"
#include "qdebug.h"

template <class T>
Intensity_inhomogenity_correction<T>::Intensity_inhomogenity_correction(T data)
{
	qDebug() << "Intensity inhomogenity correction constructor called";
	this->data = data;
}

template <class T>
void Intensity_inhomogenity_correction<T>::Start() {

}

template <class T>
Intensity_inhomogenity_correction<T>::~Intensity_inhomogenity_correction()
{
}
