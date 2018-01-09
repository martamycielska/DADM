#pragma once
#include "Diffusion_Structural_Module.h"
#include <Eigen\Eigenvalues>
#include <complex>

#include <fftw3.h>

//typedef Tensor<std::complex<double>, 3> Data3DRaw;
//typedef Tensor<std::complex<double>, 4> Data4DRaw;

typedef std::vector<MatrixXcd> Data3DRaw;
typedef std::vector<std::vector<MatrixXcd>> Data4DRaw;

class Reconstruction :
	public Diffusion_Structural_Module
{
public:
	Reconstruction(Data3DRaw, Data3DRaw, int, int);
	Reconstruction(Data4DRaw);
	~Reconstruction() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	Data3D FourierTransform();
	std::vector<MatrixXd> ifft(Data3DRaw raw_data);
	void LSreconstruction(Data3D data);
	Data3DRaw data3DRaw_input;
	Data4DRaw data4DRaw_input;
	Data3DRaw sensitivityMaps3D;
	int L;
	int r;
	Data3D xspacedata;
};