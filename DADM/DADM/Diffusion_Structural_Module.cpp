#include "Diffusion_Structural_Module.h"

template <class InputDataType, class OutputDataType>
void Diffusion_Structural_Module<InputDataType, OutputDataType>::Start() {
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
}