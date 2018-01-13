#pragma once
#include "Estimation_Module.h"

class Non_stationary_noise_estimation:
	public Estimation_Module
{
public:
	Non_stationary_noise_estimation(Data3D);
	Non_stationary_noise_estimation(Data4D);
	~Non_stationary_noise_estimation() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	double Non_stationary_noise_estimation::localMeanCalculate(int startRowIndex, int startColumnIndex, MatrixXd matrix, MatrixXd meanMatrix);
	MatrixXd Non_stationary_noise_estimation::absoluteValue(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::logCalculate(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::expCalculate(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::noiseEstimation(MatrixXd matrix);
	MatrixXd Non_stationary_noise_estimation::gaussianKernel(MatrixXd K, MatrixXd image)
};

