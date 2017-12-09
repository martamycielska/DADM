#pragma once
#include "MRI_Module.h"
typedef enum DataType {STRUCTURAL_DATA, DIFFUSION_DATA} DataType;

template <class T, class U>
class Diffusion_Structural_Module:
	public MRI_Module<T, U>
{
public:
	Diffusion_Structural_Module() {};
	virtual void Start();
	~Diffusion_Structural_Module() {};

protected:
	DataType dtype;

private:
	virtual void StructuralDataAlgorithm() = 0;
	virtual void DiffusionDataAlgorithm() = 0;
};

