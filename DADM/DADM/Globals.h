#pragma once
#include <Eigen/Dense>
#include <unsupported\Eigen\CXX11\Tensor>

using namespace Eigen;

class Globals
{
public:
	static Tensor<double, 3> structuralData;
	static Tensor<double, 4> diffusionData4D;
	static Tensor<double, 3> diffusionData3D;
	static MatrixXd FA;
	static MatrixXd MD;
	static MatrixXd RA;
	static MatrixXd VR;
};

