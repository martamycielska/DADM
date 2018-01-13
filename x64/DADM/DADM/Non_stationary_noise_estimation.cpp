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