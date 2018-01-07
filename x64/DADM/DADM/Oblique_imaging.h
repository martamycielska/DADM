#pragma once
#include "MRI_Module.h"
#include <unsupported/Eigen/CXX11/Tensor>

class Oblique_imaging:
	public MRI_Module<Data3D, MatrixXd>
{
public:
	Oblique_imaging(Data3D, int, double, double);
	virtual void Start();
	~Oblique_imaging();
	void getObliqueImage();

private:
	int current_profile;
	double rot_x;
	double rot_y;
};

