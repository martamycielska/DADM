#include "Diffusion_tensor_imaging.h"
#include "qdebug.h"
#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;


Diffusion_tensor_imaging::Diffusion_tensor_imaging(Data4D data)
{
	qDebug() << "Diffusion tensor imaging constructor called";
	this->inputData = data;
}

//void diffusion_tensor_imaging::start() {
//
//}
//
//void diffusion_tensor_imaging::fa() {
//
//}
//
//void diffusion_tensor_imaging::md() {
//
//}
//
void Diffusion_tensor_imaging::b_matrix() {

}
void Diffusion_tensor_imaging::estimate_tensor() {
	
	for (int k = 0; k < this->inputData.size(); k++)
	{
		for (int i = 0; i < this->inputData[k].size(); i++)
		{
			for (int j = 0; j < this->inputData[k][i].size(); j++)
			{
				for (int l = 0; l < this->inputData[k][i][j].size(); l++)
				{
					if (this->inputData[k][i][j][l] = 0)
					{
						this->inputData[k][i][j][l] = 1;
						MatrixXd covar = 
					}
				}
			}
		}
	}
}

Diffusion_tensor_imaging::~Diffusion_tensor_imaging()
{
}
