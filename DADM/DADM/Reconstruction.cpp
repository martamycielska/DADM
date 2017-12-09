#include "Reconstruction.h"
#include "qdebug.h"

template <class In, class Out>
Reconstruction<In, Out>::Reconstruction(In data)
{
	qDebug() << "Reconstruction constructor called";
	inputData = data;
}

template <class In, class Out>
void Reconstruction<In, Out>::StructuralDataAlgorithm() {

}

template <class In, class Out>
void Reconstruction<In, Out>::DiffusionDataAlgorithm() {

}

template <class In, class Out>
Reconstruction<In, Out>::~Reconstruction()
{
}
