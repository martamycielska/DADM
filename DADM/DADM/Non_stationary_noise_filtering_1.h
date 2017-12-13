#pragma once
#include "Diffusion_Structural_Module.h"

class Non_stationary_noise_filtering_1:
	public Diffusion_Structural_Module
{
public:
	Non_stationary_noise_filtering_1(Data3D, Data3D);
	Non_stationary_noise_filtering_1(Data4D, Data4D);
	~Non_stationary_noise_filtering_1() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	Data3D estimator3D;
	Data4D estimator4D;
};

