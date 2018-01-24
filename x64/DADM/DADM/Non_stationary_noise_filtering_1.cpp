#include "Non_stationary_noise_filtering_1.h"
#include "qdebug.h"
#include "matio.h"
#include "qaction.h"
#include "qfiledialog.h"


Non_stationary_noise_filtering_1::Non_stationary_noise_filtering_1(Data3D images, Data3D estim)
{
	qDebug() << "Non stationary noise filtering 1 constructor called";
	this->data3D_input = images;
	estimator3D = estim;
	dtype = STRUCTURAL_DATA;
}

Non_stationary_noise_filtering_1::Non_stationary_noise_filtering_1(Data4D images, Data4D estim)
{
	qDebug() << "Non stationary noise filtering 1 constructor called";
	this->data4D_input = images;
	estimator4D = estim;
	dtype = DIFFUSION_DATA;
}

void Non_stationary_noise_filtering_1::StructuralDataAlgorithm() {
	qDebug() << "START FILTERING";
	for (int i = 0; i < data3D_input.size(); i++) {
		data3D_output.push_back(lmmse(data3D_input[i], 7, estimator3D[i]));
	}
}

void Non_stationary_noise_filtering_1::DiffusionDataAlgorithm() {
	for (int i = 0; i < data4D_input.size(); i++) {
		for (int j = 0; j < data4D_input[i].size(); j++) {
			part_out.push_back(lmmse(data4D_input[i][j], 7, estimator4D[i][j]));
		}
		data4D_output.push_back(part_out);
		part_out.clear();
	}
}

MatrixXd Non_stationary_noise_filtering_1::filter2(MatrixXd image, MatrixXd window)
{
	MatrixXd imagePlusPadding(MatrixXd::Zero(image.rows() + window.rows() - 1, image.cols() + window.cols() - 1)); // Creates padding.
	imagePlusPadding.block(window.rows() / 2, window.cols() / 2, image.rows(), image.cols()) << image; //Adds padding to image.
	MatrixXd outputPlusPadding(image.rows() + window.rows() - 1, image.cols() + window.cols() - 1); //Output of the function.
	double convolution = 0; // Convolution results for an index.
	int x, y; // Input matrix indexes.

	for (int i = 0; i < imagePlusPadding.rows(); i++) // Fills output matrix: rows and columns have i and j indexes (respectively).
	{
		for (int j = 0; j < imagePlusPadding.cols(); j++)
		{
			x = i;
			y = j;

			for (int k = 0; k < window.rows(); k++) // Window rows and columns have k and l indexes (respectively).
			{
				for (int l = 0; l < window.cols(); l++)
				{
					if (x < imagePlusPadding.rows() && y < imagePlusPadding.cols()) { // Convolution.
						convolution += window(k, l) * imagePlusPadding(x, y);
					}
					y++;
				}
				x++;
				y = j; // Restart column position.
			}
			outputPlusPadding(i, j) = convolution; // Adds result to output matrix.
			convolution = 0;
		}
	}
	return outputPlusPadding.block(0, 0, image.rows(), image.cols());
}

MatrixXd Non_stationary_noise_filtering_1::lmmse(MatrixXd image, int W, MatrixXd sigma)
{

	sigma = sigma.cwiseProduct(sigma); //Squares sigma.
	MatrixXd M2 = filter2(image.cwiseProduct(image), MatrixXd::Ones(W, W)) / (W*W); //Order 2 moment.
	MatrixXd M4 = filter2(image.cwiseProduct(image).cwiseProduct(image).cwiseProduct(image), MatrixXd::Ones(W, W)) / (W*W); //Order 4 moment.
	MatrixXd K = MatrixXd::Ones(image.rows(), image.cols()) + (4 * sigma.cwiseProduct(sigma) - 4 * sigma.cwiseProduct(M2)).cwiseQuotient(M4 - M2.cwiseProduct(M2)); //K parameter
	K = K.cwiseMax(0); //Replaces all negative K parameters by zeros.
	MatrixXd image_filtered = (M2 - 2 * sigma + K.cwiseProduct(image.cwiseProduct(image) - M2)); //Square filtered image.
	image_filtered = image_filtered.cwiseAbs();
	image_filtered = image_filtered.cwiseSqrt(); //Filtered image.

	return image_filtered;
}