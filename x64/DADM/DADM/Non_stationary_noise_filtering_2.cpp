#include "Non_stationary_noise_filtering_2.h"
#include "qdebug.h"

Non_stationary_noise_filtering_2::Non_stationary_noise_filtering_2(Data3D images, Data3D estim)
{
	qDebug() << "Non stationary noise filtering 2 constructor called";
	this->data3D_input = images;
	estimator3D = estim;
	dtype = STRUCTURAL_DATA;
}

Non_stationary_noise_filtering_2::Non_stationary_noise_filtering_2(Data4D images, Data4D estim)
{
	qDebug() << "Non stationary noise filtering 2 constructor called";
	this->data4D_input = images;
	estimator4D = estim;
	dtype = DIFFUSION_DATA;
}

void Non_stationary_noise_filtering_2::StructuralDataAlgorithm() {
	Data3D data = data3D_input;
	Data3D sigmaTab = estimator3D;
	for (int iter = 1; iter < data.size(); iter++) {
		MatrixXd input = data[iter];
		//Define constants
		int M = input.rows();
		int N = input.cols();
		int Rsim = 5;
		int Rsearch = 2;
		//sigma -> macierz
		double h;
		MatrixXd sigma = sigmaTab[iter];

		//Resize initialized Matrix
		MatrixXd input1 = MatrixXd::Zero(100 + 2 * Rsim, 100 + 2 * Rsim);
		int M1 = input1.rows();
		int N1 = input1.cols();
		for (int i = Rsim; i <= M1 - 1 - Rsim; i++) {
			for (int j = Rsim; j <= N1 - 1 - Rsim; j++) {
				input1(i, j) = input(i - Rsim, j - Rsim);
			}
		}

		//Generate Gaussian Kernel
		MatrixXd gauss_kernel = MatrixXd::Zero(Rsim, Rsim);
		int kernel_sum = 0;
		int g_sigma = 1;
		double e;
		for (int i = -Rsim; i <= Rsim; i++) {
			for (int j = -Rsim; j <= Rsim; j++) {
				e = exp(0.5*(i*i + j*j) / (2 * g_sigma*g_sigma));
				gauss_kernel(i + Rsim, j + Rsim) = e / (2 * M_PI*g_sigma*g_sigma);
				kernel_sum += gauss_kernel(i + Rsim, j + Rsim);
			}
		}
		//Normalize Gaussian Kernel
		for (int i = -Rsim; i <= Rsim; i++) {
			for (int j = -Rsim; j <= Rsim; j++) {
				gauss_kernel(i + Rsim, j + Rsim) = gauss_kernel(i + Rsim, j + Rsim) / kernel_sum;
			}
		}
		//Count UNLM
		int i_1, j_1, k1, k2, l1, l2;
		double w, wmax, Z, d, Yq;
		MatrixXd Np, Nq, result1, result2, result3, output;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				wmax = 0;
				Z = 0;
				Yq = 0;

				//Create main pixel neighbourhood
				i_1 = i + Rsim;
				j_1 = j + Rsim;
				for (int i1 = i; i1 <= i_1 + Rsim; i1++) {
					for (int j1 = j; j1 <= j_1 + Rsim; j1++) {
						Np(i1 - i, j1 - j) = input1(i1, j1);
					}
				}
				k1 = max(i_1 - Rsearch, Rsim + 1) - 1;
				k2 = min(i_1 + Rsearch, M + Rsim) - 1;
				l1 = max(j_1 - Rsearch, Rsim + 1) - 1;
				l2 = min(j_1 + Rsearch, N + Rsim) - 1;

				for (int k = k1; k <= k2; k++) {
					for (int l = l1; l <= l2; l++) {
						if ((k == i_1) && (l == j_1)) {
							w = wmax;
						}
						else {
							//Create comparable pixel neighbourhood
							int i3 = 0;
							int j3 = 0;
							for (int i2 = k - Rsim; i2 <= k + Rsim; i2++) {
								for (int j2 = l - Rsim; j2 <= l + Rsim; j2++) {
									Nq(i3, j3) = input1(i2, j2);
									j3++;
								}
								i3++;
							}
							result1 = Np - Nq;
							result2 = result1.cwiseProduct(result1);
							result3 = gauss_kernel.cwiseProduct(result2);
							d = result3.sum();

							h = 1.22*sigma(i, j);
							w = exp(-d / (h*h));

							if (w > wmax) {
								wmax = w;
							}
						}
						Z += w;
						Yq = Yq + w*input(k, l);
					}
				}
				Z += wmax;
				Yq += wmax*input(i_1, j_1);
				if (Z > 0) {
					output(i, j) = sqrt(pow((Yq / Z), 2) - 2 * pow((sigma(i, j)), 2));
				}
				else {
					output(i, j) = input(i, j);
				}
			}
		}
		data[iter] = output;
	}
}

void Non_stationary_noise_filtering_2::DiffusionDataAlgorithm() {

}