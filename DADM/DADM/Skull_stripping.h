#pragma once
#include "Diffusion_Structural_Module.h"

template <class T, class U>
class Skull_stripping:
	public Diffusion_Structural_Module<T, U>
{
public:
	Skull_stripping(T, DataType);
	~Skull_stripping();

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

