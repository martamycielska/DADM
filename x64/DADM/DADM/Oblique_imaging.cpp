#include "Oblique_imaging.h"
#include "qdebug.h"


Oblique_imaging::Oblique_imaging(Data3D data, double a, double b, Profile profile)
{
	qDebug() << "Oblique imaging constructor called";
	this->inputData = data;
	this->a = a;
	this->b = b;
	this->profile = profile;
}

void Oblique_imaging::Start() {
	getObliqueImage();
}

Oblique_imaging::~Oblique_imaging()
{
}

void Oblique_imaging::getObliqueImage() {

	int size_x, size_y, size_z;
	int border = 100;

	Eigen::MatrixXd slice;

	slice = inputData.at(0);

	size_z = inputData.size();
	size_x = slice.rows();
	size_y = slice.cols();

	Eigen::Tensor<double, 3>mri_data(size_x + (2 * border), size_y + (2 * border), size_z + (2 * border));
	mri_data.setZero();

	for (int i = border; i < (size_z + border); ++i) {
		for (int j = border; j < (size_y + border); ++j) {
			for (int k = border; k < (size_x + border); ++k) {

				slice = inputData.at(i);
				mri_data(i, j, k) = slice(j, k);

			}
		}
	}

	//define vectors and point for a base plane
	RowVector3f v1, v2, point, p;
	v1 << 1, 0, 0;
	v2 << 0, 1, 0;
	point << (border + (size_x / 2)), (border + (size_y / 2)), (border + current_profile);
	p.setZero();

	//rotation
	double M_PI = 3.14;
	rot_x /= 180;
	rot_y /= 180;
	Eigen::Matrix3f rot_matrix;
	rot_matrix = AngleAxisf(rot_x*M_PI, Vector3f::UnitX())
		* AngleAxisf(rot_y*M_PI, Vector3f::UnitY());

	//v1 = rot_matrix*v1;
	//v2 = rot_matrix*v2;

	qDebug() << v1(0) << ',' << v1(1) << ',' << v1(2);
	qDebug() << v2(0) << ',' << v2(1) << ',' << v2(2);
	qDebug() << rot_matrix(0,0) << ',' << rot_matrix(0,1) << ',' << rot_matrix(0,2);
	qDebug() << rot_matrix(1, 0) << ',' << rot_matrix(1, 1) << ',' << rot_matrix(1, 2);
	qDebug() << rot_matrix(2, 0) << ',' << rot_matrix(2, 1) << ',' << rot_matrix(2, 2);
	//rotation
	//AngleAxis<float> aa(angle_in_radian, Vector3f(ax, ay, az));
	//Eigen::Transform t;
	//t = AngleAxis(angle, axis);
	//AngleAxis<float> aa(rot_x, v1);
}

/*
	Eigen::Affine3d create_rotation_matrix(double ax, double ay, double az)
	{
		Eigen::Affine3d rx =
			Eigen::Affine3d(Eigen::AngleAxisd(ax, Eigen::Vector3d(1, 0, 0)));
		Eigen::Affine3d ry =
			Eigen::Affine3d(Eigen::AngleAxisd(ay, Eigen::Vector3d(0, 1, 0)));
		Eigen::Affine3d rz =
			Eigen::Affine3d(Eigen::AngleAxisd(az, Eigen::Vector3d(0, 0, 1)));
		return rz * ry * rx;
	}
*/