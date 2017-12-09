#pragma once
#include "Diffusion_Structural_Module.h"
#include <Eigen\Eigenvalues>

typedef Tensor<std::complex<double>, 3> Data3DRaw;
typedef Tensor<std::complex<double>, 4> Data4DRaw;

template <class T, class U>
class Reconstruction :
	public Diffusion_Structural_Module<T, U>
{
public:
	Reconstruction(T);
	~Reconstruction();

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};