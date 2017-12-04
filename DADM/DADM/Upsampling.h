#pragma once
#include "MRI_Module.h"
class Upsampling:
	public MRI_Module<float***>
{
public:
	Upsampling();
	~Upsampling();
};

