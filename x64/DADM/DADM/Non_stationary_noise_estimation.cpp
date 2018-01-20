#include "Non_stationary_noise_estimation.h"
#include "qdebug.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>
#include <cstdlib>
#include <cmath> 
#include "fftw3.h"

Non_stationary_noise_estimation::Non_stationary_noise_estimation(Data3D data)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->data3D_input = data;
	dtype = STRUCTURAL_DATA;
}

Non_stationary_noise_estimation::Non_stationary_noise_estimation(Data4D data)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->data4D_input = data;
	dtype = DIFFUSION_DATA;
}

void Non_stationary_noise_estimation::StructuralDataAlgorithm() {
	//data3D_input
}

void Non_stationary_noise_estimation::DiffusionDataAlgorithm() {
	//data4D_input
}

bool Non_stationary_noise_estimation::getSum(MatrixXd matrix)
{
	for (int j = 0; j < matrix.cols(); j++) {
		double sumInColumn = 0;
		for (int i = 0; i < matrix.rows(); i++) {
			sumInColumn += matrix(i, j);
		}
		if (sumInColumn <= 1)
		{
			return false;
		}
	}
	return true;
}

MatrixXd Non_stationary_noise_estimation::getFinded(MatrixXd matrix, int conditionValue)
{
	std::vector<double> v;
	for (int j = 0; j < matrix.cols(); j++) {
		for (int i = 0; i < matrix.rows(); i++) {
			if (matrix(i, j) == conditionValue) {
				v.push_back(i + j * matrix.rows());
			}
		}
	}
	MatrixXd Finded = MatrixXd::Zero(1, v.size());
	int iterator = 0;
	for (int n : v) {
		Finded(0, iterator) = n;
		iterator++;
	}
	return Finded;
}

MatrixXd Non_stationary_noise_estimation::setValueOnSpecifiedIndexes(MatrixXd matrixToSet, MatrixXd Indexes)
{
	MatrixXd matrixWithSetValues = MatrixXd::Zero(Indexes.cols(), 1);
	for (int i = 0; i < Indexes.cols(); i++) {

		int index = Indexes(0, i);
		int b = index / matrixToSet.rows();
		int a = index - (b*matrixToSet.rows());
		matrixWithSetValues(i, 0) = matrixToSet(a, b);
	}
	return matrixWithSetValues;
}

void Non_stationary_noise_estimation::setValueOnSpecifiedIndexes(MatrixXd& matrixToSet, MatrixXd Indexes, double value)
{
	for (int i = 0; i < Indexes.cols(); i++) {
		int index = Indexes(0, i);
		int b = index / matrixToSet.rows();
		int a = index - (b*matrixToSet.rows());
		matrixToSet(a, b) = value;
	}
}

void Non_stationary_noise_estimation::setBesselValues(MatrixXd z, MatrixXd K, MatrixXd& M)
{
	for (int i = 0; i < K.cols(); i++) {

		int index = K(0, i);
		int b = index / z.rows();
		int a = index - (b*z.rows());
		double x = cyl_bessel_i(1, z(a, b));
		double y = cyl_bessel_i(0, z(a, b));
		M(a, b) = cyl_bessel_i(1, z(a, b)) / cyl_bessel_i(0, z(a, b));
	}
}

MatrixXd Non_stationary_noise_estimation::bessel(MatrixXd matrix)
{
	MatrixXd cont = MatrixXd::Zero(256, 256);
	for (int i = 0; i < matrix.rows(); i++) {
		for (int j = 0; j < matrix.cols(); j++) {
			if (matrix(i, j) < 1.5) {
				cont(i, j) = 1;
			}
			else {
				cont(i, j) = 0;
			}
		}
	}

	MatrixXd z8 = 8 * matrix;
	MatrixXd z8Power2 = pow(z8.array(), 2);
	MatrixXd z8Power3 = pow(z8.array(), 3);
	MatrixXd Md1 = MatrixXd::Constant(256, 256, 1).array() / z8.array();
	MatrixXd Md2 = MatrixXd::Constant(256, 256, 4.5).array() / z8Power2.array();
	MatrixXd Md3 = MatrixXd::Constant(256, 256, (25 * 9) / 6).array() / z8Power3.array();
	MatrixXd Md = (MatrixXd::Constant(256, 256, 1) + Md1) + Md2 + Md3;

	MatrixXd Mn1 = MatrixXd::Constant(256, 256, 3).array() / z8.array();
	MatrixXd Mn2 = MatrixXd::Constant(256, 256, 15 / 2).array() / z8Power2.array();
	MatrixXd Mn3 = MatrixXd::Constant(256, 256, (3 * 5 * 21) / 6).array() / z8Power3.array();
	MatrixXd Mn = MatrixXd::Constant(256, 256, 1) - Mn1 - Mn2 - Mn3;

	MatrixXd M = Mn.array() / Md.array();
	for (int i = 0; i < M.rows();i++) {
		for (int j = 0; j < M.cols(); j++) {
			if (M(i, j) != M(i, j))
			{
				M(i, j) = 0;
			}
		}
	}

	if (getSum(cont)) {
		MatrixXd K = getFinded(cont, 1);
		setBesselValues(matrix, K, M);
	}
	MatrixXd K = getFinded(matrix, 0);
	setValueOnSpecifiedIndexes(M, K, 0);

	return M;
}

MatrixXd Non_stationary_noise_estimation::getMaxValue(MatrixXd matrix, double tresh) {

	for (int i = 0; i <= 255;i++) {
		for (int j = 0; j <= 255; j++) {
			if (matrix(i, j) < tresh) {
				matrix(i, j) = tresh;
			}
		}
	}
	return matrix;
}

MatrixXd Non_stationary_noise_estimation::filter2(MatrixXd matrix, MatrixXd window)
{
	int imageRows = matrix.rows();
	int imageCols = matrix.cols();
	int windowRows = window.rows();
	int windowCols = window.cols();
	MatrixXd padding(MatrixXd::Zero(imageRows + windowRows - 1, imageCols + windowCols - 1));
	padding.block(windowRows / 2, windowCols / 2, imageRows, imageCols) << matrix;
	MatrixXd outputPlusPadding(imageRows + windowRows - 1, imageCols + windowCols - 1);
	double conv = 0;
	int x, y;

	int imagePaddingRows = padding.rows();
	int imagePaddingCols = padding.cols();

	for (int i = 0; i < imagePaddingRows; i++) {
		for (int j = 0; j < imagePaddingCols; j++) {
			x = i;
			y = j;
			for (int k = 0; k < windowRows; k++) {
				for (int l = 0; l < windowCols; l++) {
					if (x < imagePaddingRows && y < imagePaddingCols) {
						conv += window(k, l) * padding(x, y);
					}
					y++;
				}
				x++;
				y = j;
			}
			outputPlusPadding(i, j) = conv;
			conv = 0;
		}
	}
	return outputPlusPadding.block(0, 0, imageRows, imageCols);
}

MatrixXd Non_stationary_noise_estimation::getSNR(int window, MatrixXd matrix) {
	MatrixXd ones = MatrixXd::Ones(window, window);
	MatrixXd matrixPow2 = pow(matrix.array(), 2);
	MatrixXd matrixPow4 = pow(matrix.array(), 4);
	MatrixXd filter = filter2(matrixPow2, ones) / (window * window);
	MatrixXd filterPow2 = pow(filter.array(), 2);
	MatrixXd A = 2 * filterPow2 - filter2(matrixPow4, ones) / (window * window);
	MatrixXd ak = sqrt(sqrt(getMaxValue(A, 0).array()));
	MatrixXd akPow2 = pow(ak.array(), 2);
	MatrixXd sigma = 0.5*getMaxValue(filter - akPow2, 0.01);

	for (int i = 0;i < 9;i++) {
		MatrixXd AM = ak.array()*matrix.array();
		MatrixXd aksigma = AM.array() / sigma.array();
		MatrixXd B = bessel(aksigma);
		ak = getMaxValue(filter2(B.array()*matrix.array(), ones) / (window * window), 0);
		MatrixXd ak2 = pow(ak.array(), 2);
		sigma = getMaxValue(0.5*filter - (ak2 / 2), 0.01);
	}
	MatrixXd sigmaSqrt = sqrt(sigma.array());
	MatrixXd SNR = ak.array() / sigmaSqrt.array();
	return SNR;
}

MatrixXd Non_stationary_noise_estimation::absoluteValue(MatrixXd matrix) {
	return matrix.cwiseAbs();
}

MatrixXd Non_stationary_noise_estimation::logCalculate(MatrixXd matrix) {

	for (int i = 0; i < matrix.rows();i++) {
		for (int j = 0; j < matrix.cols(); j++) {
			if (matrix(i, j) == 0) {
				matrix(i, j) = 0.001;
			}
		}
	}
	return matrix.array().log();
}

MatrixXd Non_stationary_noise_estimation::expCalculate(MatrixXd matrix) {
	return matrix.array().exp();
}

MatrixXd Non_stationary_noise_estimation::noiseEstimation(MatrixXd matrix) {
	return ((matrix * 2) / sqrt(2))*exp(e / 2);
}

MatrixXd Non_stationary_noise_estimation::gaussianKernel(MatrixXd K, MatrixXd image, double sig) {
	MatrixXd kernel = MatrixXd::Zero(image.rows(), image.cols());
	double sigma = 2 * sig;
	int column = 2 * image.cols();
	int row = 2 * image.rows();
	double half = row / 2;
	for (int x = 0; x < row; ++x)
		for (int y = 0; y < column; ++y) {
			K(x, y) = exp(-0.5 * (pow((x - half) / sigma, 2.0) + pow((y - half) / sigma, 2.0)))
				/ (2 * pi * sigma * sigma);
		}

	double maximum = K.maxCoeff();
	K = K / maximum;

	for (int x = image.rows(); x < row; x++)
	{
		for (int y = image.cols(); y < column; y++) {
			kernel(x - image.rows(), y - image.rows()) = K(x, y);
		}
	}

	return kernel;
}

MatrixXd Non_stationary_noise_estimation::dct(MatrixXd log) {

	int m = log.rows();
	int n = log.cols();
	std::vector<double> a(m*n);
	int count = 1;

	for (int i = 0; i<m;i++) {
		for (int j = 0; j<n;j++) {
			a[i*n + j] = log(i, j);
			count++;
		}
	}
	std::vector<double> b(m*n);
	fftw_plan plan = fftw_plan_r2r_2d(n, m, &a[0], &b[0], FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE);
	fftw_execute(plan);

	MatrixXd K = MatrixXd::Zero(m, n);
	for (int i = 0; i<m;i++)
		for (int j = 0; j<n;j++)
			K(i, j) = b[i*n + j];

	return K;
}

MatrixXd Non_stationary_noise_estimation::idct(MatrixXd log) {

	int m = log.rows();
	int n = log.cols();
	std::vector<double> a(m*n);
	int count = 1;

	for (int i = 0; i<m;i++) {
		for (int j = 0; j<n;j++) {
			a[i*n + j] = log(i, j);
			count++;
		}
	}

	std::vector<double> b(m*n);
	fftw_plan plan = fftw_plan_r2r_2d(n, m, &a[0], &b[0], FFTW_REDFT01, FFTW_REDFT01, FFTW_PATIENT);
	fftw_execute(plan);

	double f = sqrt(1 / 2 / (m*n));
	for (int i = 0, f = (m*n) << 1;i < (m*n);++i) {
		b[i] /= f * 2;
	}

	MatrixXd K = MatrixXd::Zero(m, n);
	for (int i = 0; i<m;i++)
		for (int j = 0; j<n;j++)
			K(i, j) = b[i*n + j];

	return K;
}

MatrixXd Non_stationary_noise_estimation::riceCorrection(MatrixXd SNR, MatrixXd coeff) {

	MatrixXd F = coeff(0)*pow(SNR.array(), 0) + coeff(1)*pow(SNR.array(), 1) + coeff(2)*pow(SNR.array(), 2)
		+ coeff(3)*pow(SNR.array(), 3) + coeff(4)*pow(SNR.array(), 4) + coeff(5)*pow(SNR.array(), 5)
		+ coeff(6)* pow(SNR.array(), 6) + coeff(7)*pow(SNR.array(), 7) + coeff(8)*pow(SNR.array(), 8);

	F = F.array() * (SNR.array() <= 7).cast<double>().array();

	return F;
}
