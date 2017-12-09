#pragma once
#include "Estimation_Module.h"

template <class T, class U>
class Non_stationary_noise_estimation:
	public Estimation_Module<T, U>
{
public:
	Non_stationary_noise_estimation(T, DataType);
	~Non_stationary_noise_estimation();

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
};

