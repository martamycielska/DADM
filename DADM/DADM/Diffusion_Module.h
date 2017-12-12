#pragma once
#include "MRI_Module.h"
class Diffusion_Module :
	public MRI_Module<Data4D, Data3D>
{
public:
	Diffusion_Module() {};
	virtual MatrixXd getFA() { return FA; };
	virtual MatrixXd getMD() { return MD; };
	virtual MatrixXd getRA() { return RA; };
	virtual MatrixXd getVR() { return VR; };
	virtual ~Diffusion_Module() {};

protected:
	MatrixXd FA;
	MatrixXd MD;
	MatrixXd RA;
	MatrixXd VR;
};

