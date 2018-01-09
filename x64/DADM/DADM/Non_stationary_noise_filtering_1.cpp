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
Non_stationary_noise_filtering_1::Non_stationary_noise_filtering_1(int start)
{
	qDebug() << "Non stationary noise filtering 1 constructor called";
	importTest3D();
	int Ws = 7;
	//MatrixXd image = readCSV("image.csv", 10, 10);
	
	//MatrixXd kernel = readCSV("kernel.csv", 5, 5);
	//std::cout << kernel << std::endl;;
	MatrixXd est = lmmse(image, Ws, sigma);
	qDebug() << est(0, 0);
	//std::cout << est << std::endl;;
	
	// usage 
	// Non_stationary_noise_filtering_1 filtering = Non_stationary_noise_filtering_1(0);
	// MatrixXd output = filtering.lmmse(MatrixXd::Ones(12, 12), 5, MatrixXd::Ones(12, 12));
}

void Non_stationary_noise_filtering_1::StructuralDataAlgorithm() {

}

void Non_stationary_noise_filtering_1::DiffusionDataAlgorithm() {

}
MatrixXd Non_stationary_noise_filtering_1::filter2(MatrixXd image, MatrixXd kernel)
{
	MatrixXd output(image.rows(), image.cols());
	float convolute = 0; // This holds the convolution results for an index.
	int x, y; // Used for input matrix index

			  // Fill output matrix: rows and columns are i and j respectively
	for (int i = 0; i < image.rows(); i++)
	{
		for (int j = 0; j < image.cols(); j++)
		{
			x = i;
			y = j;

			// Kernel rows and columns are k and l respectively
			for (int k = 0; k < kernel.rows(); k++)
			{
				for (int l = 0; l < kernel.cols(); l++)
				{
					// Convolute here.
					if (x < image.rows() && y < image.cols()) {
						convolute += kernel(k, l) * image(x, y);

					}
					y++; // Move right.
				}
				x++; // Move down.
				y = j; // Restart column position
			}
			output(i, j) = convolute; // Add result to output matrix.
			convolute = 0; // Needed before we move on to the next index.
		}
	}
	return output;
}
void Non_stationary_noise_filtering_1::importTest3D()
{
	//QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Mat file (*.mat) (*mat)");

	//if (url.isEmpty())
	//	return;

	//QString path = url.path().remove(0, 1);
	QString path = "C:\Users\Klaudia\Desktop\matlab-lmmse";
	QByteArray ba = path.toLatin1();
	const char *fileName = ba.data();
	//const char *fileName = "T1_synthetic_normal_1mm_L8_r2.mat";
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
MatrixXd Non_stationary_noise_filtering_1::lmmse(MatrixXd image, int Ws, MatrixXd sigma2)
{

	MatrixXd Squ = filter2(image.cwiseProduct(image), MatrixXd::Ones(Ws, Ws) / Ws*Ws);
	MatrixXd Qua = filter2(image.cwiseProduct(image).cwiseProduct(image).cwiseProduct(image), MatrixXd::Ones(Ws, Ws) / Ws*Ws);
	MatrixXd K1 = MatrixXd::Ones(image.rows(), image.cols()) + (4 * sigma2.cwiseProduct(sigma2 - 4 * sigma2.cwiseProduct(Squ))).cwiseQuotient(Qua - Squ.cwiseProduct(Squ));
	K1 = K1.cwiseMax(0);
	MatrixXd I_est = (Squ - 2 * sigma2 + K1.cwiseProduct(image.cwiseProduct(image) - Squ));
	I_est = I_est.cwiseAbs();
	I_est = I_est.cwiseSqrt();

	return I_est;
}