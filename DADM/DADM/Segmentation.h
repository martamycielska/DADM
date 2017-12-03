#pragma once
#include "MRI_Module.h"
class Segmentation:
	public MRI_Module<float***>
{
public:
	Segmentation();
	~Segmentation();
};

