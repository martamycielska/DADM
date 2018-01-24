#include "Diffusion_tensor_imaging.h"
#include "qdebug.h"
#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace Eigen;


Diffusion_tensor_imaging::Diffusion_tensor_imaging(Data4D data, double b_value, MatrixXd gradients)
{
	qDebug() << "Diffusion tensor imaging constructor called";
	this->inputData = data;
	this->b_value = b_value;
	this->gradients = gradients;
}

void Diffusion_tensor_imaging::Start() {
	this->T = EstimateTensor();
	this->EigenVector();
	this->MeanDiffusivity();

}
TensorData Diffusion_tensor_imaging::EstimateTensor() {
	MatrixXd B = this->BMatrix();
	TensorData T = TensorData(0);
	qDebug() << 1;
	for (int k = 0; k < this->inputData.size(); k++)
	{
		std::vector<std::vector<Eigen::Matrix2d>> vec1;
		T.push_back(vec1);
		for (int i = 0; i < this->inputData[k].size(); i++)
		{
			std::vector<Eigen::Matrix2d> vec2;
			T.at(k).push_back(vec2);
			for (int j = 0; j < this->inputData[k][i].size(); j++)
			{
				for (int l = 0; l < this->inputData[k][i].cols(); l++)
				{

					if (this->inputData[k][i].row(j)(l) == 0)
					{
						this->inputData[k][i].row(j)(l) = 1;
					}
				}

				this->inputData[k][i].row(j) = this->inputData[k][i].row(j).array().square();
				MatrixXd covar = this->inputData[k][i].row(j).asDiagonal();

				MatrixXd X = ((B.transpose() * covar * B).inverse()).array() * (B.transpose() * covar).array() * this->inputData[k][i].row(j).array().log();
				MatrixXd m(3,3);
				m.setZero(3,3);

				//T.at(k).at(i).push_back(X);
				
				//T[k][i][j].setZero(3, 3);
				m.row(0)(0) = X(1, 0);
				m.row(0)(1) = X(2, 0);
				m.row(0)(2) = X(3, 0);
				m.row(1)(1) = X(4, 0);
				m.row(1)(2) = X(5, 0);
				m.row(2)(2) = X(6, 0);
				qDebug() << 4;

			}
		}

	}
	return T;
}

MatrixXd Diffusion_tensor_imaging::BMatrix() {

	//normalize gradients
	MatrixXd g, g_matrix, b_matrix(7, this->gradients.rows());

	g = this->gradients.array() * this->gradients.array();
	g = g.rowwise().sum();
	g = g.array().sqrt();
	g_matrix = g.replicate(1, 3);
	g = this->gradients.array() / g_matrix.array();

	b_matrix.row(0).fill(1);
	b_matrix.row(1) = (this->b_value*((g.col(1)).array().square())).transpose();
	b_matrix.row(2) = (this->b_value * 2 * (g.col(1)).array()*(g.col(2)).array()).transpose();
	b_matrix.row(3) = (this->b_value * 2 * (g.col(1)).array()*(g.col(3)).array()).transpose();
	b_matrix.row(4) = (this->b_value * (g.col(2)).array().square()).transpose();
	b_matrix.row(5) = (this->b_value * 2 * (g.col(2)).array()*(g.col(3)).array()).transpose();
	b_matrix.row(6) = (this->b_value * (g.col(3)).array().square()).transpose();

	return b_matrix;
}

void Diffusion_tensor_imaging::EigenVector() {

	for (int k = 0; k < this->inputData.size(); k++)
	{
		for (int i = 0; i < this->inputData[k].size(); i++)
		{
			for (int j = 0; j < this->inputData[k][i].size(); j++)
			{
				for (int l = 0; l < this->inputData[k][i].cols(); l++) {

					this->eigenVector.push_back(this->T[k][i][j].row(0)(0));
					this->eigenVector.push_back(this->T[k][i][j].row(1)(1));
					this->eigenVector.push_back(this->T[k][i][j].row(2)(2));
				}
			}
		}
	}

}

void Diffusion_tensor_imaging::MeanDiffusivity() {


	for (int k = 0; k < this->inputData.size(); k++)
	{
		MatrixXd tmp(this->inputData[k].size(), this->inputData[k][0].size());

		for (int i = 0; i < this->inputData[k].size(); i++)
		{
			for (int j = 0; j < this->inputData[k][i].size(); j++)
			{
				tmp.row(i)(j) = (this->eigenVector[0] + this->eigenVector[1] + this->eigenVector[2]) / 3;
			}
		}
		this->MD.push_back(tmp);
	}
}

void Diffusion_tensor_imaging::FractionalAnisotropy() {
	double v1, v2, v3, v;

	//>> >> >> > Stashed changes

	v1 = this->eigenVector[0];
	v2 = this->eigenVector[1];
	v3 = this->eigenVector[2];

	for (int k = 0; k < this->inputData.size(); k++)
	{
		std::vector<MatrixXd> tmp2;

		for (int i = 0; i < this->inputData[k].size(); i++)
		{
			MatrixXd tmp(this->inputData[k][i].size(), 3);

			for (int j = 0; j < this->inputData[k][i].size(); j++)
			{

				v = this->getMD()[k].row(i)(j);

				double fa = sqrt(3 * ((pow((v1 - v), 2) + (pow((v2 - v), 2)) + (pow((v3 - v), 2)))) / sqrt(2 * ((pow(v1, 2) + (pow(v2, 2)) + (pow(v3, 2))))));
				int r = (int)min(30 + 1.5f*abs(255 * fa * v1), 255.0f);
				int g = (int)min(30 + 1.5f*abs(255 * fa * v2), 255.0f);
				int b = (int)min(30 + 1.5f*abs(255 * fa * v3), 255.0f);
				tmp.row(j)(0) = r;
				tmp.row(j)(1) = g;
				tmp.row(j)(2) = b;

			}
			tmp2.push_back(tmp);

		}
		this->FA.push_back(tmp2);

	}

};

void Diffusion_tensor_imaging::RelativeAnisotropy() {

	double v1, v2, v3, v;

	v1 = this->eigenVector[0];
	v2 = this->eigenVector[1];
	v3 = this->eigenVector[2];
	for (int k = 0; k < this->inputData.size(); k++)
	{
		MatrixXd tmp(this->inputData[k].size(), this->inputData[k][0].size());

		for (int i = 0; i < this->inputData[k].size(); i++)
		{

			for (int j = 0; j < this->inputData[k][i].size(); j++)
			{

				v = this->getMD()[k].row(i)(j);
				tmp.row(i)(j) = sqrt(pow((v1 - v), 2) + (pow((v2 - v), 2)) + (pow((v3 - v), 2))) / sqrt(3 * v);

			}
		}
		this->RA.push_back(tmp);
	}
};
void Diffusion_tensor_imaging::VolumeRatio() {

	double v1, v2, v3, v;
	v1 = this->eigenVector[0];
	v2 = this->eigenVector[1];
	v3 = this->eigenVector[2];
	for (int k = 0; k < this->inputData.size(); k++)
	{
		MatrixXd tmp(this->inputData[k].size(), this->inputData[k][0].size());

		for (int i = 0; i < this->inputData[k].size(); i++)
		{
			for (int j = 0; j < this->inputData[k][i].size(); j++)
			{
				v = this->getMD()[k].row(i)(j);
				tmp.row(i)(j) = (v1*v2*v3) / (pow(v, 3));
			}
		}
		this->VR.push_back(tmp);
	}
};

Diffusion_tensor_imaging::~Diffusion_tensor_imaging() {}