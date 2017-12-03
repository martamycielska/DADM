#pragma once
#include "MRI_Module.h"
class Non_stationary_noise_estimation:
	public MRI_Module<float***>
{
public:
	Non_stationary_noise_estimation();
	~Non_stationary_noise_estimation();
};

