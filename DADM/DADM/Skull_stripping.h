#pragma once
#include "Diffusion_Structural_Module.h"

class Skull_stripping:
	public Diffusion_Structural_Module
{
public:
	Skull_stripping(Data3D);
	Skull_stripping(Data4D);
	~Skull_stripping() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

