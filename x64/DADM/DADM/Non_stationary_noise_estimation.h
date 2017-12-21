#pragma once
#include "Estimation_Module.h"

class Non_stationary_noise_estimation:
	public Estimation_Module
{
public:
	Non_stationary_noise_estimation(Data3D);
	Non_stationary_noise_estimation(Data4D);
	~Non_stationary_noise_estimation() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

