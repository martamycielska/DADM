#pragma once
#include "Diffusion_Structural_Module.h"

typedef enum EstimatorType {RICE, GAUSS} EstimatorType;

template <class T, class U>
class Estimation_Module :
	protected Diffusion_Structural_Module<T, U>
{
public:
	Estimation_Module() {};
	virtual U getData(EstimatorType);
	~Estimation_Module() {};

protected:
	U RiceEstimator;
	U GaussEstimator;
};

