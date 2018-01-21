#include "Non_stationary_noise_filtering_2.h"
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
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

Non_stationary_noise_filtering_2::Non_stationary_noise_filtering_2(Data3D images, Data3D estim)
{
	qDebug() << "Non stationary noise filtering 2 constructor called";
	this->data3D_input = images;
	//estimator3D = estim;
	dtype = STRUCTURAL_DATA;
	StructuralDataAlgorithm();
}

Non_stationary_noise_filtering_2::Non_stationary_noise_filtering_2(Data4D images, Data4D estim)
{
	qDebug() << "Non stationary noise filtering 2 constructor called";
	this->data4D_input = images;
	estimator4D = estim;
	dtype = DIFFUSION_DATA;
	DiffusionDataAlgorithm();
}

void Non_stationary_noise_filtering_2::StructuralDataAlgorithm() {
	Data3D data = data3D_input;
	Data3D sigmaTab = estimator3D;
	for (int iter = 0; iter < 1; iter++) {
		MatrixXd input = data[iter];
		//Define constants
		int M = input.rows();
		int N = input.cols();
		int Rsim = 2;
		int Rsearch = 5;
		double h;
		MatrixXd sigma = sigmaTab[iter];
		//Resize initialized Matrix
		MatrixXd input1 = MatrixXd::Zero(M + 2 * Rsim, N + 2 * Rsim);
		int M1 = input1.rows();
		int N1 = input1.cols();

		for (int i = Rsim; i < M1 - Rsim; i++) {
			for (int j = Rsim; j < N1 - Rsim; j++) {
				input1(i, j) = input(i - Rsim, j - Rsim);
			}
		}

		//Generate Gaussian Kernel
		MatrixXd gauss_kernel = MatrixXd::Zero(2 * Rsim + 1, 2 * Rsim + 1);
		double kernel_sum = 0;
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
		int test = 0;
		//Count UNLM
		int i_1, j_1, k1, k2, l1, l2;
		MatrixXd output = MatrixXd::Zero(M, N);
		double w, wmax, Z, d, Yq;
		MatrixXd Np, Nq, result1, result2, result3;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				wmax = 0;
				Z = 0;
				Yq = 0;

				//Create main pixel neighbourhood
				i_1 = i + Rsim;
				j_1 = j + Rsim;
				Np = input1.block(i, j, 2 * Rsim + 1, 2 * Rsim + 1);
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
							Nq = input1.block(k - Rsim, l - Rsim, 2 * Rsim + 1, 2 * Rsim + 1);
							result1 = Np - Nq;
							result2 = result1.cwiseProduct(result1);
							result3 = gauss_kernel.cwiseProduct(result2);
							d = result3.sum();
							h = 1.22*sigma(i,j);
							w = exp(-d / (h*h));

							if (w > wmax) {
								wmax = w;
							}
						}
						Z += w;
						Yq += w*input1(k, l);
					}
				}
				Z += wmax;
				Yq += wmax*input1(i_1, j_1);
				if (Z > 0) {
					output(i, j) = sqrt(pow((Yq / Z), 2) - 2 * pow(sigma(i,j), 2));
				}
				else {
					output(i, j) = input1(i, j);
				}
				qDebug() << test++;
				qDebug() << "\n";
			}
		}
		data[iter] = output;
		/*MatrixXd inputData = output;
		int xspace = inputData.rows();
		int yspace = inputData.cols();

		vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
		imageData->SetDimensions(xspace, yspace, 1);
		imageData->AllocateScalars(VTK_DOUBLE, 1);
		int* dims = imageData->GetDimensions();

		for (int y = 0; y < dims[1]; y++)
			for (int x = 0; x < dims[0]; x++)
			{
				double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, 0));
				pixel[0] = inputData(x, y);
			}

		vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
		actor->SetInputData(imageData);

		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		renderer->AddActor(actor);
		renderer->ResetCamera();

		vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		renderWindow->AddRenderer(renderer);

		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
		renderWindowInteractor->SetInteractorStyle(style);
		renderWindowInteractor->SetRenderWindow(renderWindow);
		renderWindowInteractor->Initialize();
		renderWindowInteractor->Start();*/
	}
	Global::structuralData = data;
}

void Non_stationary_noise_filtering_2::DiffusionDataAlgorithm() {
	Data4D data = data4D_input;
	Data4D sigmaTab = estimator4D;
	for (int iter = 0; iter < data.size(); iter++) {
		Data3D data1 = data[iter];
		Data3D sigmaTab1 = sigmaTab[iter];
		for (int iter1 = 0; iter1 < data.size(); iter1++) {
			MatrixXd input = data1[iter];
			//Define constants
			int M = input.rows();
			int N = input.cols();
			int Rsim = 2;
			int Rsearch = 5;
			double h;
			MatrixXd sigma = sigmaTab1[iter];
			//Resize initialized Matrix
			MatrixXd input1 = MatrixXd::Zero(M + 2 * Rsim, N + 2 * Rsim);
			int M1 = input1.rows();
			int N1 = input1.cols();

			for (int i = Rsim; i < M1 - Rsim; i++) {
				for (int j = Rsim; j < N1 - Rsim; j++) {
					input1(i, j) = input(i - Rsim, j - Rsim);
				}
			}
			//Generate Gaussian Kernel
			MatrixXd gauss_kernel = MatrixXd::Zero(2 * Rsim + 1, 2 * Rsim + 1);
			double kernel_sum = 0;
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
			int test = 0;
			//Count UNLM
			int i_1, j_1, k1, k2, l1, l2;
			MatrixXd output = MatrixXd::Zero(M, N);
			double w, wmax, Z, d, Yq;
			MatrixXd Np, Nq, result1, result2, result3;
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					wmax = 0;
					Z = 0;
					Yq = 0;

					//Create main pixel neighbourhood
					i_1 = i + Rsim;
					j_1 = j + Rsim;
					Np = input1.block(i, j, 2 * Rsim + 1, 2 * Rsim + 1);

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
								Nq = input1.block(k - Rsim, l - Rsim, 2 * Rsim + 1, 2 * Rsim + 1);
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
							Yq += w*input1(k, l);
						}
					}
					Z += wmax;
					Yq += wmax*input1(i_1, j_1);
					if (Z > 0) {
						output(i, j) = sqrt(pow((Yq / Z), 2) - 2 * pow(sigma(i, j), 2));
					}
					else {
						output(i, j) = input1(i, j);
					}
				}
			}
			data1[iter1] = output;
		}
		data[iter] = data1;
	}
}