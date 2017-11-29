#pragma once
#include "Non_stationary_noise_filtering_1.h"
#include "Non_stationary_noise_filtering_2.h"
class Non_stationary_noise_filtering:
	public Non_stationary_noise_filtering_1,
	public Non_stationary_noise_filtering_2

{
public:
	Non_stationary_noise_filtering();
	~Non_stationary_noise_filtering();
};

