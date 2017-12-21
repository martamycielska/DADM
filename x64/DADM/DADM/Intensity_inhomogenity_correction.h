#pragma once
#include "Diffusion_Structural_Module.h"

class Intensity_inhomogenity_correction:
	public Diffusion_Structural_Module
{
public:
	Intensity_inhomogenity_correction(Data3D);
	Intensity_inhomogenity_correction(Data4D);
	~Intensity_inhomogenity_correction() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

