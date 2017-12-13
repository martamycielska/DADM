#pragma once
#include "MRI_Module.h"
typedef enum DataType {STRUCTURAL_DATA, DIFFUSION_DATA} DataType;

class Diffusion_Structural_Module
{
public:
	Diffusion_Structural_Module() {};
	virtual void Start() {
		switch (dtype) {
		case STRUCTURAL_DATA:
			StructuralDataAlgorithm();
			break;
		case DIFFUSION_DATA:
			DiffusionDataAlgorithm();
			break;
		default:
			break;
		}
	};
	virtual ~Diffusion_Structural_Module() {};
	virtual Data3D getData3D() { return data3D_output; };
	virtual Data4D getData4D() { return data4D_output; };

protected:
	DataType dtype;
	Data3D data3D_input;
	Data4D data4D_input;
	Data3D data3D_output;
	Data4D data4D_output;

private:
	virtual void StructuralDataAlgorithm() = 0;
	virtual void DiffusionDataAlgorithm() = 0;
};

