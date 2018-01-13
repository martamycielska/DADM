#pragma once
#include "MRI_Module.h"

typedef enum Profile { FRONTAL, SAGGITAL, HORIZONTAL } Profile;

class Oblique_imaging:
	public MRI_Module<Data3D, Data3D>
{
public:
	Oblique_imaging(Data3D, double, double, Profile);
	virtual void Start();
	~Oblique_imaging();

private:
	double a;
	double b;
	Profile profile;
};

