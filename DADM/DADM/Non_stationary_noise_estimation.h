#pragma once
#include "Estimation_Module.h"

template <class InputDataType, class OutputDataType>
class Non_stationary_noise_estimation:
	public Estimation_Module<InputDataType, OutputDataType>
{
public:
	Non_stationary_noise_estimation(InputDataType, DataType);
	~Non_stationary_noise_estimation() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

