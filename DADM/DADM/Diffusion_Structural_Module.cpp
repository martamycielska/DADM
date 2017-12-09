#include "Diffusion_Structural_Module.h"

template <class T, class U>
void Diffusion_Structural_Module<T, U>::Start() {
	switch (dtype) {
	case STRUCTURAL_DATA:
		StructuralDataAlgorithm();
		break;
	case DIFFUSION_DATA:
		DiffusionDataAlgorithm();
		break;
	}
}