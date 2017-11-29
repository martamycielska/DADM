#pragma once
#include "Non_stationary_noise_filtering_1.h"
#include "Non_stationary_noise_filtering_2.h"
class Skull_stripping :
	public Non_stationary_noise_filtering_1,
	public Non_stationary_noise_filtering_2
{
public:
	Skull_stripping();
	void test();
	~Skull_stripping();
};

