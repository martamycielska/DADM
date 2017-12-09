#pragma once
#include "Diffusion_Structural_Module.h"

template <class InputDataType, class OutputDataType>
class Skull_stripping:
	public Diffusion_Structural_Module<InputDataType, OutputDataType>
{
public:
	Skull_stripping(InputDataType, DataType);
	~Skull_stripping();

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

