#pragma once
#include "MRI_Module.h"

typedef std::map<std::string, Data3D> SegmentationData;

class Segmentation:
	public MRI_Module<Data3D, SegmentationData>
{
public:
	Segmentation(Data3D);
	virtual void Start();
	~Segmentation();
};

