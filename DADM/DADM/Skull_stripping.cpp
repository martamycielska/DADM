#include "Skull_stripping.h"
#include "qdebug.h"

template <class T>
Skull_stripping<T>::Skull_stripping(T data, DataType type)
{
	qDebug() << "Skull stripping constructor called";
	this->data = data;
	dtype = type;
}

template <class T>
void Skull_stripping<T>::StructuralDataAlgorithm() {

}

template <class T>
void Skull_stripping<T>::DiffusionDataAlgorithm() {

}

template <class T>
Skull_stripping<T>::~Skull_stripping()
{
}