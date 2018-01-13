#include "Non_stationary_noise_estimation.h"
#include "qdebug.h"

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

}

double Non_stationary_noise_estimation::localMeanCalculate(int startRowIndex, int startColumnIndex, MatrixXd matrix, MatrixXd meanMatrix)
{
	//left top window coordinates
	int leftStartRowIndex = startRowIndex;
	int leftStartColIndex = startColumnIndex;

	for (int i = 0; i < 2; i++) {
		if (leftStartRowIndex - 1 >= 0)
		{
			leftStartRowIndex = leftStartRowIndex - 1;
		}

		if (leftStartColIndex - 1 >= 0)
		{
			leftStartColIndex = leftStartColIndex - 1;
		}
	}

	int leftDiffRows = startRowIndex - leftStartRowIndex;
	int leftDiffCols = startColumnIndex - leftStartColIndex;

	//right bottom window coordinates
	int rightStartRowIndex = startRowIndex;
	int rightStartColIndex = startColumnIndex;

	for (int i = 0; i < 2; i++) {
		if (rightStartRowIndex + 1 <= matrix.rows() - 1)
		{
			rightStartRowIndex = rightStartRowIndex + 1;
		}

		if (rightStartColIndex + 1 <= matrix.cols() - 1)
		{
			rightStartColIndex = rightStartColIndex + 1;
		}
	}

	int rightDiffRows = rightStartRowIndex - startRowIndex;
	int rightDiffCol = rightStartColIndex - startColumnIndex;

	int rowsDimension = leftDiffRows + rightDiffRows + 1;
	int colsDimension = leftDiffCols + rightDiffCol + 1;

	double meanValue = 0;
	for (int i = 0; i < rowsDimension; i++) {
		for (int j = 0; j < colsDimension; j++) {
			meanValue += matrix(leftStartRowIndex + i, leftStartColIndex + j);
		}
	}
	return (meanValue / (rowsDimension * colsDimension));
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
	for (int x = 0; x < matrix.rows(); x++)
	{
		for (int y = 0; y < matrix.cols(); y++) {
			double z = matrix(x, y);
			matrix(x, y) = exp(z);
		}
	}
	return matrix;
}

MatrixXd Non_stationary_noise_estimation::noiseEstimation(MatrixXd matrix) {
	MatrixXd noiseEstimator = MatrixXd::Zero(matrix.rows(), matrix.cols());
	for (int i = 0; i < matrix.rows();i++) {
		for (int j = 0; j < matrix.cols(); j++) {
			noiseEstimator(i, j) = ((matrix(i, j) * 2) / sqrt(2))*exp(e / 2);
		}
	}
	return noiseEstimator;
}

MatrixXd Non_stationary_noise_estimation::gaussianKernel(MatrixXd K, MatrixXd image) {
	MatrixXd kernel = MatrixXd::Zero(image.rows(), image.cols());
	double sigma = 2 * 3.4;
	int column = 2 * image.cols();
	int row = 2 * image.rows();
	double half = row / 2;
	double maximum = K(0, 0);
	for (int x = 0; x < row; ++x)
		for (int y = 0; y < column; ++y) {
			K(x, y) = exp(-0.5 * (pow((x - half) / sigma, 2.0) + pow((y - half) / sigma, 2.0)))
				/ (2 * pi * sigma * sigma);
		}
	// Normalize the kernel
	for (int x = 0; x < row; ++x) {
		for (int y = 0; y < column; ++y) {
			if (K(x, y) > maximum)
				maximum = K(x, y);
		}
	}
	for (int x = 0; x < row; ++x) {
		for (int y = 0; y < column; ++y) {
			K(x, y) /= maximum;
		}
	}
	for (int x = image.rows(); x < row; x++)
	{
		for (int y = image.rows(); y < column; y++) {
			kernel(x - image.rows(), y - image.rows()) = K(x, y);
		}
	}
	return kernel;
}