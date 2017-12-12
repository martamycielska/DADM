#pragma once
#include "Diffusion_Structural_Module.h"

template <class InputDataType, class EstimatorDataType, class OutputDataType>
class Non_stationary_noise_filtering_1:
	public Diffusion_Structural_Module<InputDataType, OutputDataType>
{
public:
	Non_stationary_noise_filtering_1(InputDataType, EstimatorDataType, DataType);
	~Non_stationary_noise_filtering_1() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	EstimatorDataType estimator;
};

