#pragma once
#include "Estimation_Module.h"
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <vector>
#include <cstdlib>
#include <cmath> 
#include "fftw3.h"
#include <boost/math/special_functions/bessel.hpp> 

using namespace std;
using namespace boost::math;
using namespace Eigen;
class Non_stationary_noise_estimation:
	public Estimation_Module
{
public:
	double e = 0.5772156649;
	double pi = 3.14159265358979323846;
	
	Non_stationary_noise_estimation(Data3D);
	Non_stationary_noise_estimation(Data4D);
	~Non_stationary_noise_estimation() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	bool Non_stationary_noise_estimation::getSum(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::getFinded(MatrixXd matrix, int conditionValue);
	void Non_stationary_noise_estimation::setValueOnSpecifiedIndexes(MatrixXd& matrixToSet, MatrixXd Indexes, double value);
	void Non_stationary_noise_estimation::setBesselValues(MatrixXd z, MatrixXd K, MatrixXd& M);
	MatrixXd Non_stationary_noise_estimation::bessel(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::getMaxValue(MatrixXd matrix, double tresh);
	MatrixXd Non_stationary_noise_estimation::filter2(MatrixXd matrix, MatrixXd window);
	MatrixXd Non_stationary_noise_estimation::getSNR(int window, MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::absoluteValue(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::logCalculate(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::expCalculate(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::noiseEstimation(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::gaussianKernel(MatrixXd K, MatrixXd image, double sig);
	MatrixXd Non_stationary_noise_estimation::dct(MatrixXd log);
	MatrixXd Non_stationary_noise_estimation::idct(MatrixXd log);
	MatrixXd Non_stationary_noise_estimation::riceCorrection(MatrixXd SNR);
	void Non_stationary_noise_estimation::writeToCSVfile(string name, MatrixXd matrix);
	void Non_stationary_noise_estimation::setEstimators(MatrixXd reconstructedImage, int i, int j = 0, bool isDiffusion = false);

	Data3D gradientEstimatorGauss;
	Data3D gradientEstimatorRice;
};

