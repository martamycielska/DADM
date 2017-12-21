#pragma once
#include "Diffusion_Structural_Module.h"
#include <Eigen\Eigenvalues>
#include <unsupported/Eigen/FFT>

//typedef Tensor<std::complex<double>, 3> Data3DRaw;
//typedef Tensor<std::complex<double>, 4> Data4DRaw;

typedef std::vector<MatrixXcd> Data3DRaw;
typedef std::vector<std::vector<MatrixXcd>> Data4DRaw;

class Reconstruction :
	public Diffusion_Structural_Module
{
public:
	Reconstruction(Data3DRaw);
	Reconstruction(Data4DRaw);
	~Reconstruction() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	void FourierTransform();
	Data3DRaw data3DRaw_input;
	Data4DRaw data4DRaw_input;
};