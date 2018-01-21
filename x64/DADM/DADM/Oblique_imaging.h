#pragma once
#include "MRI_Module.h"
#include <vtkImageData.h>
#include <vtkSmartPointer.h>

typedef enum Profile { FRONTAL, SAGGITAL, HORIZONTAL } Profile;

class Oblique_imaging:
	public MRI_Module<Data3D, Data3D>
{
public:
	Oblique_imaging(Data3D, double, double, Profile, int);
	virtual void Start();
	~Oblique_imaging();
	void getObliqueImage(Data3D inputData);

private:
	double a;
	double b;
	Profile profile;
	int profile_nr;
};

