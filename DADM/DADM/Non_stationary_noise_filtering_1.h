#pragma once
#include "Diffusion_Structural_Module.h"

template <class T, class U>
class Non_stationary_noise_filtering_1:
	public Diffusion_Structural_Module<T>
{
public:
	Non_stationary_noise_filtering_1(T, T, DataType);
	~Non_stationary_noise_filtering_1();

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	T estimator;
};

