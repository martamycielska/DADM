﻿#include "Upsampling.h"
#include "qdebug.h"
#include <Eigen/Core>
#include <unsupported/Eigen/Splines>
#include <algorithm>
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


Upsampling::Upsampling(MatrixXd data, int width, int height)
{
	qDebug() << "Upsampling constructor called";
	this->inputData = data;
	this->height = height;
	this->width = width;
}


void Upsampling::Start() {

	Inicjalizacja(inputData);

}

Upsampling::~Upsampling()
{
}

void Upsampling::Inicjalizacja(MatrixXd inputData) {



	MatrixXd Image = inputData;


	int N = Image.rows();
	int M = Image.cols();

		MatrixXd Image1 = MatrixXd::Zero(N*width, M*height);

	int N1 = Image1.rows();
	int M1 = Image1.cols();
	qDebug() << "Rozmiar rozszerzonej";
	qDebug() << "ROZMIAR x" << Image1.rows();
	qDebug() << "ROZMIAR x" << Image1.cols();


	// Rozszerzenie obrazu po wierszach rows wpisanie zer

	for (int i = 0; i < Image1.rows(); i++) {
		for (int j = 0; j < Image.cols(); j++) {

			if (i % width == 0) {
				Image1(i, j) = Image(i / width, j);
				//qDebug() << "Dla i" << i << "DLa j" << j;
				//qDebug() << "INTERPOLACJA PO WIERSZACH" << Image1(i, j);
			}
			else
			{
				Image1(i, j) = 0;


			}

		}
	}

	// for (int i = 0; i < Image1.rows(); i++) {
	//  for (int j = 0; j < Image.cols(); j++) {


	//}
	//}

	// Interpolacja obrazu po wierszach (rows)


	for (int i = 0; i < Image1.rows(); i++) {

		for (int j = 0; j < Image.cols(); j++) {

			qDebug() << "dla jakiego i i j " << i << j;
			if ((Image1(i, j) == 0) && (i != (Image1.rows() - 1)) && (j != (Image.cols() - 1))) {

				Image1(i, j) = (Image1(i - 1, j) + Image1(i + 1, j) + Image1(i - 1, j + 1) + Image1(i + 1, j + 1)) / 4;

			}

			if ((Image1(i, j) == 0) && (i == (Image1.rows() - 1))) {

				Image1(i, j) = (Image1(i - 1, j) + Image1(i - 1, j + 1)) / 2;

			}

			if ((Image1(i, j) == 0) && (j == (Image.cols() - 1))) {

				Image1(i, j) = (Image1(i - 1, j) + Image1(i + 1, j)) / 2;

			}

			if ((Image1(i, j) == 0) && (i == (Image1.rows() - 1)) && (j == (Image.cols() - 1))) {

				Image1(i, j) = Image1(i - 1, j);

			}






		}
	}





	MatrixXd Image2;
	Image2 = Image1;


	// wypisane Image2


	// Rozszerzenie Obrazu  po kolumnach kolumnach wpisanie zer
	qDebug() << "Rozszerzenie obrazu";
	for (int i = 0; i < Image1.rows(); i++) {
		for (int j = 0; j < Image2.cols(); j++) {

				if (j % height != 0) {

							Image1(i, j) = 0;

					}
					else {
						Image1(i, j) = Image2(i, j / height);

					}



				}

		}




		// interpolacja macierzy po kolumnach

		qDebug() << "Interpolacja";
		for (int i = 0; i < Image1.rows(); i++) {
			for (int j = 0; j < Image1.cols(); j++) {
				qDebug() << i << j;
				if (Image1(i, j) == 0 && i == 0 && j != Image1.cols() - 1) {


					Image1(i, j) = (Image1(i, j - 1) + Image1(i, j + 1) + Image1(i + 1, j - 1) + Image1(i + 1, j + 1)) / 4;
				}

				if (Image1(i, j) == 0 && i == 0 && j == Image1.cols() - 1) {


					Image1(i, j) = (Image1(i, j - 1) + Image1(i + 1, j)) / 2;
				}

				if (Image1(i, j) == 0 && (i != Image1.rows() - 1) && (j != Image1.cols() - 1)) {



					Image1(i, j) = (Image1(i - 1, j - 1) + Image1(i, j - 1) + Image1(i - 1, j + 1) + +Image1(i, j + 1)) / 4;
				}


				if (Image1(i, j) == 0 && (i == Image1.rows() - 1) && (j != Image1.cols() - 1)) {



					Image1(i, j) = (Image1(i, j - 1) + Image1(i, j + 1) + Image1(i - 1, j - 1) + Image1(i - 1, j + 1)) / 4;
				}

				if (Image1(i, j) == 0 && (i == Image1.rows() - 1) && (j == Image1.cols() - 1)) {

					Image1(i, j) = (Image1(i, j - 1) + Image1(i - 1, j - 1)) / 2;
				}

				if (Image1(i, j) == 0 && (i != Image1.rows() - 1) && (j == Image1.cols() - 1)) {

					Image1(i, j) = (Image1(i, j - 1) + Image1(i - 1, j - 1)) / 2;
				}



			}

		}

		//////////////////////////FILTR NOWY///////////////////////////

		int h = 1;
		int punkt = 1;

		MatrixXd k(Image1.rows(), Image1.cols());

		k = Image1;

		MatrixXd Image_new(k.rows() - 4, k.cols() - 4);
		int diameter = 4;
		int i_new = 0;
		int j_new = 0;
		for (int i = 2; i < k.rows() - 2; i++) {


			for (int j = 2; j < k.cols() - 2; j++) {




				double Filtered = 0;
				double wp = 0;
				int neighbor_x = 0;
				int neighbor_y = 0;
				int half = diameter / 2;


				for (int a = 0; a < diameter; a++) {
					for (int b = 0; b < diameter; b++) {

						neighbor_x = i - (half - a);
						neighbor_y = j - (half - b);
						//qDebug() << "a" << a<<"b"<<b;
						double gi = pow((k(neighbor_x, neighbor_y) - k(i, j)), 2);
						gi = exp(-gi / h);
						//qDebug() << "gi" << gi;
						double gs = sqrt(pow(neighbor_x - i, 2) + pow(neighbor_y - j, 2)) / (pow(h, 2));
						gs = exp(gs);
						//qDebug() << "gs" << gs;
						double w = gi*gs;
						Filtered = Filtered + w*k(i + 2, j + 2);
						wp = wp + w;

					}

				}

				Filtered = Filtered / wp;
				//qDebug() << "NOEW PUNKTY OBRAZU";
				//qDebug() << "Dla i" <<i<<"Dla j" <<j;
				Image_new(i_new, j_new) = Filtered;
				//qDebug() << "punkt ";
				//qDebug() << Image_new(i_new, j_new);
				j_new = j_new + 1;
				punkt = punkt + 1;
			}
			j_new = 0;
			i_new = i_new + 1;
		}

		MatrixXd finished(k.rows(), k.cols());



		qDebug() << "RILOSC PPUNKT�W";
		qDebug() << Image_new.rows();
		qDebug() << Image_new.cols();

		double rozmiar_x = Image_new.rows();
		double rozmiar_y = Image_new.cols();


		//qDebug() << "ROZMIAR NOWEJ MACIERZY";
		//qDebug() << Image_new.size();
		qDebug() << Image_new.rows();
		qDebug() << Image_new.cols();

		//k.block<508, 508>(2,2) = Image_new;

		k.block(2, 2, rozmiar_x, rozmiar_y) = Image_new;

		outputData = k;

		qDebug() << "ROZMIAR K macierzy";

		//qDebug() << "NOWE PUNKTY";
		//for (int i = 0; i < k.rows(); i++) {
		//for (int j = 0; j < k.cols(); j++) {
		//qDebug() << "dla jakiego "<<i <<"dla jakiego j" <<j;
		//qDebug() << k(i, j);
		//}
		//}






		//// FILTR BILATERALNY ///
		qDebug() << "Filtr";


		/*      MatrixXd k(Image1.rows(), Image1.cols());
		k = Image1;

		MatrixXd outputData(k.rows(), k.cols());



		int iMin;
		int iMax;
		int jMin;
		int jMax;
		int w = 2;
		int h = 1;

		int wart = 2;
		for (int i = 0; i < k.rows(); i++) {

		for (int j = 0; j < k.cols(); j++) {
		qDebug() << i << j;



		iMin = max(i - w, 0);
		iMax = min(i + w, k.rows() - 1);
		jMin = max(j - w, 0);
		jMax = min(j + w, k.cols() - 1);

		MatrixXd I(iMax, jMax);


		if (iMax + iMin <= k.rows() && jMin + jMax <= k.cols()) {

		for (int a=0; a < iMax; a++) {
		for (int a1=0; a1 < jMax; a1++) {
		I = k.block(iMin, jMin, iMax, jMax);

		}
		}

		}
		if (iMax + iMin <= k.rows() && jMin + jMax > k.cols()) {

		int kol = k.cols() - jMin;

		for (int a=0; a < iMax; a++) {
		for (int a1=0; a1 < kol; a1++) {
		I = k.block(iMin, jMin, iMax, kol);

		}
		}

		}


		if (iMax + iMin > k.rows() && jMin + jMax <= k.cols()) {

		//int kol = k.cols() - jMin;
		int wier = k.rows() - iMin;
		for (int a = 0; a < wier; a++) {
		for (int a1 = 0; a1 < jMax; a1++) {
		I = k.block(iMin, jMin, wier, jMax);

		}
		}

		}

		if (iMax + iMin > k.rows() && jMin + jMax > k.cols()) {

		int kol = k.cols() - jMin;
		int wier = k.rows() - iMin;
		for (int a = 0; a < wier; a++) {
		for (int a1 = 0; a1 < kol; a1++) {
		I = k.block(iMin, jMin, wier, kol);

		}
		}

		}



		MatrixXd H(I.rows(), I.cols());
		MatrixXd H1(I.rows(), I.cols());
		MatrixXd F(I.rows(), I.cols());
		MatrixXd F1(I.rows(), I.cols());

		MatrixXd I1(I.rows(), I.cols());

		I1 = I;
		I1 = -( I.array() - k(i, j));
		h = pow(h, 2);
		//I1 = I1.array().square(); // tu pierwsza zmiana


		H = I1/h;
		H1 = H.array().exp();


		int O;


		for (int k = iMin; k < iMax; k++) {
		for (int m = jMin; m < jMax; m++) {

		O = sqrt(pow(k - i, 2) + pow(m - j, 2)) / (pow(h,2));
		O = exp(O);


		}

		}



		F = H1.array() * O;     // R = P .* s

		double suma =0;
		double suma1 = 0;
		double suma2 = 0;
		F1 = F.cwiseProduct(I);
		suma = F1.sum();
		suma1	=F.sum();

		suma2 = suma / suma1;

		outputData(i, j) = suma2;




		}
		}

		*/

		/*  MatrixXd inputData_matrix = k;

		int xspace = inputData_matrix.rows();
		int yspace = inputData_matrix.cols();

		vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
		imageData->SetDimensions(xspace, yspace, 1);
		imageData->AllocateScalars(VTK_DOUBLE, 1);
		int* dims = imageData->GetDimensions();

		for (int y = 0; y < dims[1]; y++)
		for (int x = 0; x < dims[0]; x++)
		{
		double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, 0));
		pixel[0] = inputData_matrix(x, y);
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
		renderWindowInteractor->Start();

		*/
	}
