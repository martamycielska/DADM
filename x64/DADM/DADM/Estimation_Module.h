#pragma once
#include "Diffusion_Structural_Module.h"

typedef enum EstimatorType {RICE, GAUSS} EstimatorType;

class Estimation_Module :
	public Diffusion_Structural_Module
{
public:
	Estimation_Module() {};

	virtual Data3D getData3D(EstimatorType eType) {
		switch (eType) {
		case RICE:
			return RiceEstimator3D;
			break;
		case GAUSS:
			return GaussEstimator3D;
			break;
		}
	};
	virtual Data4D getData4D(EstimatorType eType) {
		switch (eType) {
		case RICE:
			return RiceEstimator4D;
			break;
		case GAUSS:
			return GaussEstimator4D;
			break;
		}
	};
	virtual ~Estimation_Module() {};

protected:
	Data3D RiceEstimator3D;
	Data3D GaussEstimator3D;
	Data4D RiceEstimator4D;
	Data4D GaussEstimator4D;
};

