#include "Estimation_Module.h"


template <class T, class U>
U Estimation_Module<T, U>::getData(EstimatorType eType)
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