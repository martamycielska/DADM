#pragma once
#include "Diffusion_Structural_Module.h"

typedef enum EstimatorType {RICE, GAUSS} EstimatorType;

template <class InputDataType, class OutputDataType>
class Estimation_Module :
	protected Diffusion_Structural_Module<InputDataType, OutputDataType>
{
public:
	Estimation_Module() {};
	virtual OutputDataType getData(EstimatorType);
	virtual ~Estimation_Module() {};

protected:
	OutputDataType RiceEstimator;
	OutputDataType GaussEstimator;
};

