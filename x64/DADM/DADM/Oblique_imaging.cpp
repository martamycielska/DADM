#include "Oblique_imaging.h"
#include "qdebug.h"

#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>

Oblique_imaging::Oblique_imaging(Data3D data, double a, double b, Profile profile, int profile_nr)
{
	qDebug() << "Oblique imaging constructor called";
	this->inputData = data;
	this->a = a;
	this->b = b;
	this->profile = profile;
	this->profile_nr = profile_nr;
}

void Oblique_imaging::Start() {
	getObliqueImage(inputData);
}

Oblique_imaging::~Oblique_imaging()
{
}

void Oblique_imaging::getObliqueImage(Data3D inputData) {

	int size_x = 0;
	int size_y = 0;
	int size_z = 0;
	int border = 100;
	/*
	std::vector<MatrixXd> test_data;
	test_data = Global::structuralData;
	*/
	if (0 == inputData.size()) {
		qDebug() << "Oblique Imaging modue have no data in";
		return;
	}

	Eigen::MatrixXd slice;
	slice = inputData.at(90);

	size_z = inputData.size();
	size_x = slice.rows();
	size_y = slice.cols();

	//adding borders to data
	slice = Eigen::MatrixXd::Zero((2 * border + size_x), (2 * border + size_y));
	std::vector<MatrixXd> data;

	for (int slice_nr = 0; slice_nr < (2 * border + size_z); ++slice_nr) {
		data.push_back(slice);
	}

	for (int i = border; i < (size_z + border - 1); ++i) {
		for (int j = border; j < (size_y + border - 1); ++j) {
			for (int k = border; k < (size_x + border - 1); ++k) {
				data[i](j, k) = inputData[i - border](k - border, j - border);
			}
		}
	}

	//define vectors and point for a base plane
	Eigen::RowVector3f v1, v2, point, p;

	switch (profile) {
	case HORIZONTAL:
		v1 << 1, 0, 0;
		v2 << 0, 1, 0;
		break;
	case SAGGITAL:
		v1 << 1, 0, 0;
		v2 << 0, 0, 1;
		break;
	case FRONTAL:
		v1 << 0, 1, 0;
		v2 << 0, 0, 1;
		break;

	}
	point << (border + (size_x / 2)), (border + (size_y / 2)), (border + profile_nr);

	//rotation
	const double M_PI = 3.14159265358979323846;
	if (a) {
		a /= 180;
	}

	if (b) {
		b /= 180;
	}

	Eigen::Matrix3f rot_matrix;
	switch (profile) {
	case HORIZONTAL:
		rot_matrix = Eigen::AngleAxisf(a*M_PI, Eigen::Vector3f::UnitX())
			* Eigen::AngleAxisf(b*M_PI, Eigen::Vector3f::UnitY());
		break;

	case SAGGITAL:
		rot_matrix = Eigen::AngleAxisf(a*M_PI, Eigen::Vector3f::UnitX())
			* Eigen::AngleAxisf(b*M_PI, Eigen::Vector3f::UnitZ());
		break;

	case FRONTAL:
		rot_matrix = Eigen::AngleAxisf(a*M_PI, Eigen::Vector3f::UnitY())
			* Eigen::AngleAxisf(b*M_PI, Eigen::Vector3f::UnitZ());
		break;
	}

	v1 = v1*rot_matrix;
	v2 = v2 * rot_matrix;
	qDebug() << v1(0) << v1(1) << v1(2);
	qDebug() << v2(0) << v2(1) << v2(2);

	//get new plane's points and interpolate values
	Eigen::MatrixXd image_out = Eigen::MatrixXd::Zero(size_x, size_y);

	for (int s = -127; s <= 127; ++s) {
		for (int t = -127; t <= 127; ++t) {
			p = t*v1 + s*v2 + point;

			p(0) = std::round(p(0));
			p(1) = std::round(p(1));
			p(2) = std::round(p(2));

			image_out(t + 127, s + 127) = (data[p(2)](p(0), p(1)) +
				data[p(2) - 1](p(0), p(1)) + data[p(2) + 1](p(0), p(1)) +
				data[p(2)](p(0) + 1, p(1)) + data[p(2) - 1](p(0) - 1, p(1)) +
				data[p(2)](p(0), p(1) - 1) + data[p(2)](p(0), p(1) + 1)) / 7;
		}
	}
}


