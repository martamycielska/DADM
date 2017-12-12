#pragma once
#include "Diffusion_Structural_Module.h"

template <class InputDataType, class OutputDataType>
class Intensity_inhomogenity_correction:
	public Diffusion_Structural_Module<InputDataType, OutputDataType>
{
public:
	Intensity_inhomogenity_correction(InputDataType);
	~Intensity_inhomogenity_correction();

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

