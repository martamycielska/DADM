#include "Oblique_imaging.h"
#include "qdebug.h"


Oblique_imaging::Oblique_imaging(Data3D data, int profile_idx, double rot_x, double rot_y)
{
	qDebug() << "Oblique imaging constructor called";
	this->inputData = data;
	current_profile = profile_idx;
	this->rot_x = rot_x;
	this->rot_y = rot_y;
}

void Oblique_imaging::Start() {

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
	
	Eigen::Tensor<double, 3>mri_data(size_x+(2*border), size_y+(2*border), size_z+(2*border));
	mri_data.setZero();

	for (int i = border; i < (size_z + border); ++i) {
		for (int j = border; j < (size_y + border); ++j) {
			for (int k = border; k < (size_x + border); ++k) {

				slice = inputData.at(i);
				mri_data(i, j, k) = slice(j,k);
				
			}
		}
	}

	//define vectors and point for a base plane
	RowVector3f v1, v2, point, p;
	v1 << 1, 0, 0;
	v2 << 0, 1, 0;
	point << (border+(size_x/2)), (border+(size_y/2)), (border+current_profile);
	p.setZero();
	
	//rotation
	//AngleAxis<float> aa(angle_in_radian, Vector3f(ax, ay, az));



}