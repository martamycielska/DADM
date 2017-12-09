#pragma once
#include "Diffusion_Module.h"
class Diffusion_tensor_imaging:
	public Diffusion_Module
{
public:
	Diffusion_tensor_imaging(Data4D);
	virtual void Start();
	~Diffusion_tensor_imaging();
};

