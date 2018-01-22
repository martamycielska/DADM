#include "Diffusion_tensor_imaging.h"
#include "qdebug.h"
#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;


Diffusion_tensor_imaging::Diffusion_tensor_imaging(Data4D data, double b_value, MatrixXd gradients)
{
	qDebug() << "Diffusion tensor imaging constructor called";
	this->inputData = data;
	this->b_value = b_value;
	this->gradients = gradients;
}

void Diffusion_tensor_imaging::Start() {

}
TensorData Diffusion_tensor_imaging::EstimateTensor() {
	MatrixXd B = this->BMatrix();
	TensorData T;

	for (int k = 0; k < this->inputData.size(); k++)
	{
		for (int i = 0; i < this->inputData[k].size(); i++)
		{
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

				for (int l = 0; l < this->inputData[k][i].cols(); l++) {

					T[k][i][j][l].setZero(3, 3);
					T[k][i][j][l].row(0)(0) = X(1,0);
					T[k][i][j][l].row(0)(1) = X(2, 0);
					T[k][i][j][l].row(0)(2) = X(3, 0);
					T[k][i][j][l].row(1)(1) = X(4, 0);
					T[k][i][j][l].row(1)(2) = X(5, 0);
					T[k][i][j][l].row(2)(2) = X(6, 0);
					
					 
				}
				
			}
		}
		
	}
	return T;
}

MatrixXd Diffusion_tensor_imaging::BMatrix() {

	//normalize gradients
	MatrixXd g,g_matrix, b_matrix(7,this->gradients.rows());

	g = this->gradients.array() * this->gradients.array();
	g = g.rowwise().sum();
	g = g.array().sqrt();
	g_matrix = g.replicate( 1, 3);
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

Data3D Diffusion_tensor_imaging::FractionalAnisotropy() {
	
	return FA; };
Data3D Diffusion_tensor_imaging::MeanDiffusivity() {

	return MD; };
Data3D Diffusion_tensor_imaging::RelativeAnisotropy() {

	return RA; };
Data3D Diffusion_tensor_imaging::VolumeRatio() {

	return VR; };

Diffusion_tensor_imaging::~Diffusion_tensor_imaging() {}

