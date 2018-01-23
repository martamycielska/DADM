#pragma once
#include "MRI_Module.h"
class Diffusion_Module :
	public MRI_Module<Data4D, Data4D>
{
public:
	Diffusion_Module() {};
	virtual Data4D getFA() { return FA; };
	virtual Data3D getMD() { return MD; };
	virtual Data3D getRA() { return RA; };
	virtual Data3D getVR() { return VR; };
	virtual ~Diffusion_Module() {};

protected:
	Data4D FA;
	Data3D MD;
	Data3D RA;
	Data3D VR;
};

