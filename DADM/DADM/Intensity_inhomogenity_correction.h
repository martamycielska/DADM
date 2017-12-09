#pragma once
#include "Diffusion_Structural_Module.h"

template <class T, class U>
class Intensity_inhomogenity_correction:
	public Diffusion_Structural_Module<T, U>
{
public:
	Intensity_inhomogenity_correction(T);
	~Intensity_inhomogenity_correction();

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

