#include "Diffusion_Structural_Module.h"

template <class T>
void Diffusion_Structural_Module<T>::Start() {
	switch (dtype) {
	case STRUCTURAL_DATA:
		StructuralDataAlgorithm();
		break;
	case DIFFUSION_DATA:
		DiffusionDataAlgorithm();
		break;
	}
}