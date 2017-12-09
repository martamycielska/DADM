#pragma once
#include "MRI_Module.h"
class Segmentation:
	public MRI_Module<Data3D, Data3D>
{
public:
	Segmentation(Data3D);
	virtual void Start();
	~Segmentation();
};

