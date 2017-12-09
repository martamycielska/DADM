#include "Estimation_Module.h"


template <class T>
T Estimation_Module<T>::getData(EstimatorType eType)
{
	switch (eType) {
	case RICE:
		return RiceEstimator;
		break;
	case GAUSS:
		return GaussEstimator;
		break;
	}
}