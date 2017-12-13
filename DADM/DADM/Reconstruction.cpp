#include "Reconstruction.h"
#include "qdebug.h"


Reconstruction::Reconstruction(Data3DRaw data)
{
	qDebug() << "Reconstruction constructor called";
	data3DRaw_input = data;
	dtype = STRUCTURAL_DATA;
}

Reconstruction::Reconstruction(Data4DRaw data)
{
	qDebug() << "Reconstruction constructor called";
	data4DRaw_input = data;
	dtype = DIFFUSION_DATA;
}

void Reconstruction::StructuralDataAlgorithm() {

}

void Reconstruction::DiffusionDataAlgorithm() {

}
