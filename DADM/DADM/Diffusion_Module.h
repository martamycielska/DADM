#pragma once
#include "MRI_Module.h"
class Diffusion_Module :
	public MRI_Module<Data4D, Data3D>
{
public:
	Diffusion_Module();
	MatrixXd getFA() { return FA; };
	MatrixXd getMD() { return MD; };
	MatrixXd getRA() { return RA; };
	MatrixXd getVR() { return VR; };
	~Diffusion_Module();

protected:
	MatrixXd FA;
	MatrixXd MD;
	MatrixXd RA;
	MatrixXd VR;
};

