#include "Intensity_inhomogenity_correction.h"
#include "Globals.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "qdebug.h"
#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>
#include "matio.h"
#include "qaction.h"
#include "qfiledialog.h"
#define _USE_MATH_DEFINES
#include "qmath.h"
#include <cmath>


Intensity_inhomogenity_correction::Intensity_inhomogenity_correction(Data3D data)
{
	qDebug() << "Intensity inhomogenity correction constructor called";
	this->data3D_input = data;
	dtype = STRUCTURAL_DATA;
}

Intensity_inhomogenity_correction::Intensity_inhomogenity_correction(Data4D data)
{
	qDebug() << "Intensity inhomogenity correction constructor called";
	this->data4D_input = data;
	dtype = DIFFUSION_DATA;
}

void Intensity_inhomogenity_correction::writeToCSVfile(std::string name, MatrixXd matrix)
{
	std::ofstream file(name.c_str());

	for (int i = 0; i < matrix.rows(); i++) {
		for (int j = 0; j < matrix.cols(); j++) {

			if (j + 1 == matrix.cols()) {
				file << (matrix(i, j));
			}
			else {
				file << (matrix(i, j)) << ',';
			}
		}
		file << '\n';
	}
	file.close();
}

void Intensity_inhomogenity_correction::SetDataSize() {
	xspace = inputData[0].rows();
	yspace = inputData[0].cols();
	zspace = inputData.size();
}
Eigen::MatrixXd Intensity_inhomogenity_correction::selectRandomPoints(Eigen::MatrixXd &image, int n) {
	
	Eigen::MatrixXd values = MatrixXd::Zero();
	
	for (int i = 0; i < n; i++) {
		int coordx = ceil(rand() * 256);
		int coordy = ceil(rand() * 256);
		values(coordx,coordy) = image(coordx, coordy);
	}
	return values;
}
void Intensity_inhomogenity_correction::createFilter()
{
	// set standard deviation to 1.0
	double sigma = 1.0;
	double r, s = 2.0 * sigma * sigma;
	double gKernel[5][5];

	// sum is for normalization
	double sum = 0.0;
	// generate 256x256 kernel
	for (int x = -2; x <= 2; x++)
	{
		for (int y = -2; y <= 2; y++)
		{
			r = sqrt(x*x + y*y);
			gKernel[x + 2][y + 2] = (exp(-(r*r) / s)) / (M_PI * s);
			sum += gKernel[x + 2][y + 2];
		}
	}

	// normalize the Kernel
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			gKernel[i][j] /= sum;
}

Eigen::MatrixXd Intensity_inhomogenity_correction::applyFilter(Eigen::MatrixXd image, double * gKernel) {
	
	//assert(image.size() == 3 && filter.size() != 0);

	int height = image.rows();
	int width = image.cols();
	int filterHeight = sizeof(gKernel[0]);
	int filterWidth = sizeof(gKernel);
	int newImageHeight = height - filterHeight + 1;
	int newImageWidth = width - filterWidth + 1;
	int d, i, j, h, w;

	Eigen::MatrixXd newImage;

	
		for (i = 0; i<newImageHeight; i++) {
			for (j = 0; j<newImageWidth; j++) {
				for (h = i; h<i + filterHeight; h++) {
					for (w = j; w<j + filterWidth; w++) {
						newImage(i,j) += gKernel[h - i][w - j] * image(h,w);
					}
				}
			}
		}
	

	return newImage;
};

void Intensity_inhomogenity_correction::importTest3D()
{
	
	QString path = "C:/Users/Maurycy/Desktop/studia/projektDADM/DADM/DADM/x64/DADM/DADM";
	QByteArray ba = path.toLatin1();
	//const char *fileName = ba.data();
	const char *fileName = "T1_synthetic_normal_1mm_L8_r2.mat";
	mat_t *mat = Mat_Open(fileName, MAT_ACC_RDONLY);

	if (mat) {
		qDebug() << "Otwarto plik";

		matvar_t *matVar = 0;

		matVar = Mat_VarRead(mat, (char*)"In");

		if (matVar) {
			qDebug() << "Otwarto zmienn¹";

			//unsigned int xSize = matVar->nbytes / matVar->data_size;
			const double *xData = static_cast<const double*>(matVar->data);

			qDebug() << matVar->dims[0];
			qDebug() << matVar->dims[1];

			//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
			int val_num = 0;
			MatrixXd m(matVar->dims[0], matVar->dims[1]);
			for (int i = 0; i < matVar->dims[1]; i++) {
				for (int j = 0; j < matVar->dims[0]; j++) {
					m(j, i) = xData[val_num];
					val_num++;
					if (val_num >= matVar->dims[0] * matVar->dims[1]) break;
					qDebug() << xData[val_num];
				}
			}
			image = m;
		}
	}
	if (mat) {
		qDebug() << "Otwarto plik";

		matvar_t *matVar = 0;

		matVar = Mat_VarRead(mat, (char*)"MapaR2");

		if (matVar) {
			qDebug() << "Otwarto zmienn¹";

			//unsigned int xSize = matVar->nbytes / matVar->data_size;
			const double *xData = static_cast<const double*>(matVar->data);

			qDebug() << matVar->dims[0];
			qDebug() << matVar->dims[1];

			//MatrixXcd m(matVar->dims[0], matVar->dims[1]);
			int val_num = 0;
			MatrixXd m(matVar->dims[0], matVar->dims[1]);
			for (int i = 0; i < matVar->dims[1]; i++) {
				for (int j = 0; j < matVar->dims[0]; j++) {
					m(j, i) = xData[val_num];
					val_num++;
					if (val_num >= matVar->dims[0] * matVar->dims[1]) break;
					qDebug() << xData[val_num];
				}
			}
			sigma = m.cwiseProduct(m);
		}
	}

}
struct LMFunctor
{
	// image
	Eigen::MatrixXd measuredValues;

	int operator()(const Eigen::MatrixXd &x, Eigen::MatrixXd &fvec) const
	{
		float aParam = x(0);
		float bParam = x(1);
		float cParam = x(2);

		for (int i = 0; i < values(); i++) {
			for (int j = 0; j < values(); j++) {
				float xValue = x(i, j);
				float yValue = measuredValues(i, j);

				fvec(i,j) = yValue - (aParam * xValue * xValue + bParam * xValue + cParam);
			}
		}
		return 0;
	}

	// Compute the jacobian of the errors
	int df(const Eigen::MatrixXd &x, Eigen::MatrixXd &fjac) const
	{
		float epsilon;
		epsilon = 1e-5f;

		for (int i = 0; i < x.size(); i++) {
			Eigen::VectorXf xPlus(x);
			xPlus(i) += epsilon;
			Eigen::VectorXf xMinus(x);
			xMinus(i) -= epsilon;

			Eigen::MatrixXd  fvecPlus(values());
			operator()(xPlus, fvecPlus);

			Eigen::MatrixXd  fvecMinus(values());
			operator()(xMinus, fvecMinus);

			Eigen::MatrixXd  fvecDiff(values());
			fvecDiff = (fvecPlus - fvecMinus) / (2.0f * epsilon);

			fjac.block(0, i, values(), 1) = fvecDiff;
		}

		return 0;
	}

	// Number of data points, i.e. values.
	int m;

	// Returns 'm', the number of values.
	int values() const { return m; }

	// The number of parameters, i.e. inputs.
	int n;

	// Returns 'n', the number of inputs.
	int inputs() const { return n; }

};

void Intensity_inhomogenity_correction::LMOptimization(){

	importTest3D();
	Eigen::MatrixXd measuredValues = sigma;
	//inputData = Global::structuralData;
	int m = 256;
	int k = 256;


	// 'n' is the number of parameters in the function.
	// f(x) = a(x^2) + b(x) + c has 3 parameters: a, b, c
	int n = 3;

	// 'x' is vector of length 'n' containing the initial values for the parameters.
	// The parameters 'x' are also referred to as the 'inputs' in the context of LM optimization.
	// The LM optimization inputs should not be confused with the x input values.
	Eigen::VectorXf x(n);
	x(0) = 0.0;             // initial value for 'a'
	x(1) = 0.0;             // initial value for 'b'
	x(2) = 0.0;             // initial value for 'c'

							//
							// Run the LM optimization
							// Create a LevenbergMarquardt object and pass it the functor.
							//

	LMFunctor functor;
	functor.measuredValues = measuredValues;
	functor.m = m;
	functor.n = n;


	Eigen::LevenbergMarquardt<LMFunctor, float> lm(functor);
	int status = lm.minimize(x);
	std::cout << "LM optimization status: " << status << std::endl;

	//
	// Results
	// The 'x' vector also contains the results of the optimization.
	//
	std::cout << "Optimization results" << std::endl;
	std::cout << "\ta: " << x(0) << std::endl;
	std::cout << "\tb: " << x(1) << std::endl;
	std::cout << "\tc: " << x(2) << std::endl;
}

void Intensity_inhomogenity_correction::StructuralDataAlgorithm() {
	
}

void Intensity_inhomogenity_correction::DiffusionDataAlgorithm() {

}
