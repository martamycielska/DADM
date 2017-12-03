#pragma once
#include "MRI_Module.h"
class Diffusion_tensor_imaging:
	public MRI_Module<float***>
{
public:
	Diffusion_tensor_imaging();
	~Diffusion_tensor_imaging();
};

