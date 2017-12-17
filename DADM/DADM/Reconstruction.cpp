#include "Reconstruction.h"
#include "qdebug.h"


Reconstruction::Reconstruction(Data3DRaw data)
{
	qDebug() << "Reconstruction constructor called";
	data3DRaw_input = data;
	dtype = STRUCTURAL_DATA;
}

Reconstruction::Reconstruction(Data4DRaw data)
{
	qDebug() << "Reconstruction constructor called";
	data4DRaw_input = data;
	dtype = DIFFUSION_DATA;
}

void Reconstruction::StructuralDataAlgorithm() {


}

void Reconstruction::DiffusionDataAlgorithm() {

}

void Reconstruction::FourierTransform() {
	
	Data3DRaw raw_data = data3DRaw_input;
	Eigen::FFT_REVERSE;
	size_t dim_x = 28, dim_y = 126;
	Eigen::FFT<float> fft;
	Eigen::MatrixXf in = Eigen::MatrixXf::Random(dim_x, dim_y);
	Eigen::MatrixXcf out;
	out.setZero(dim_x, dim_y);

	for (int k = 0; k < in.rows(); k++) {
		Eigen::VectorXcf tmpOut(dim_x);
		fft.fwd(tmpOut, in.row(k));
		out.row(k) = tmpOut;
	}

	for (int k = 0; k < in.cols(); k++) {
		Eigen::VectorXcf tmpOut(dim_y);
		fft.fwd(tmpOut, out.col(k));
		out.col(k) = tmpOut;
	}



}