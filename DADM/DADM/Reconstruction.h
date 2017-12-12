#pragma once
#include "Diffusion_Structural_Module.h"
#include <Eigen\Eigenvalues>

typedef Tensor<std::complex<double>, 3> Data3DRaw;
typedef Tensor<std::complex<double>, 4> Data4DRaw;

template <class InputDataType, class OutputDataType>
class Reconstruction :
	public Diffusion_Structural_Module<InputDataType, OutputDataType>
{
public:
	Reconstruction(InputDataType);
	~Reconstruction();

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};