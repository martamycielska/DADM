#pragma once
#include "MRI_Module.h"
class Oblique_imaging:
	public MRI_Module<Data3D, MatrixXd>
{
public:
	Oblique_imaging(Data3D, int, double, double);
	virtual void Start();
	~Oblique_imaging();

private:
	Data3D profiles;
	int current_profile;
	double a;
	double b;
};

