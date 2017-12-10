#include "Estimation_Module.h"


template <class InputDataType, class OutputDataType>
U Estimation_Module<InputDataType, OutputDataType>::getData(EstimatorType eType)
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