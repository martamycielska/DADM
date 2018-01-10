#pragma once
#include "MRI_Module.h"
class Oblique_imaging:
	public MRI_Module<Data3D, Data3D>
{
public:
	Oblique_imaging(Data3D, double, double);
	virtual void Start();
	~Oblique_imaging();

private:
	double a;
	double b;
};

