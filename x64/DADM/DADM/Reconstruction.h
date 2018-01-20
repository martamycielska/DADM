#pragma once
#include "Diffusion_Structural_Module.h"
#include <Eigen\Eigenvalues>
#include <complex>
#include <fstream>
#include <iostream>
#include <string>
#include <fftw3.h>


//typedef Tensor<std::complex<double>, 3> Data3DRaw;
//typedef Tensor<std::complex<double>, 4> Data4DRaw;

typedef std::vector<MatrixXcd> Data3DRaw;
typedef std::vector<std::vector<MatrixXcd>> Data4DRaw;
typedef std::vector<std::vector<std::vector<MatrixXcd>>> Data5DRaw;

class Reconstruction :
	public Diffusion_Structural_Module
{
public:
	Reconstruction(Data3DRaw, Data3DRaw, int, int);
	Reconstruction(Data4DRaw, Data3DRaw, int, int);
	~Reconstruction() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	Data3DRaw FourierTransform(Data3DRaw raw_data);
	Data3DRaw ifft(Data3DRaw raw_data);
	MatrixXd LSreconstruction(Data3DRaw data);
	MatrixXd TikhonovRegularization(Data3DRaw data, MatrixXd image);
	Data3DRaw data3DRaw_input;
	Data4DRaw data4DRaw_input;
	Data3DRaw sensitivityMaps3D;
	Data3D SensMaps;
	MatrixXd medianFilter(MatrixXd image, int windowSize);
	int L;
	int r;
	Data3D xspacedata;
	void writeToCSVfile(std::string name, MatrixXd matrix);
};