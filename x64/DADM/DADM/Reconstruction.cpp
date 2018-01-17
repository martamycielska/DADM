#include "Reconstruction.h"
#include "qdebug.h"
#include <fftw3.h>
#include "Globals.h"
#include <iostream>
#include <fstream>
#include <string>


Reconstruction::Reconstruction(Data3DRaw raw_data, Data3DRaw sensitivity_maps, int L, int r)
{
	qDebug() << "Reconstruction constructor called";
	data3DRaw_input = raw_data;
	sensitivityMaps3D = sensitivity_maps;
	this->L = L;
	this->r = r;
	dtype = STRUCTURAL_DATA;
}

Reconstruction::Reconstruction(Data4DRaw data, Data3DRaw sensitivity_maps, int L, int r)
{
	qDebug() << "Reconstruction constructor called";
	data4DRaw_input = data;
	sensitivityMaps3D = sensitivity_maps;
	this->L = L;
	this->r = r;
	dtype = DIFFUSION_DATA;
}

void Reconstruction::StructuralDataAlgorithm() {

	int slices_no = 1;
	Data3D slices(slices_no);
	for (int i = 0; i < slices_no; i++)
	{
		Data3D data;
		//przeprowadzenie Odwrotnej Transformaty Fouriera
		Data3DRaw data_raw = data3DRaw_input;
		data = FourierTransform(data_raw);
		MatrixXd reconstructed_data;
		//Rekonstrukcja obrazu
		reconstructed_data = LSreconstruction(data);
		qDebug() << "LS reconstruction done";
		reconstructed_data = TikhonovRegularization(data, reconstructed_data);

		slices.at(i) = reconstructed_data;

	}
	//zwracana wartoœæ
	data3D_output = slices;
}

void Reconstruction::DiffusionDataAlgorithm()
{
	int slices_no = 1;
	Data4D slices(slices_no);
	for (int i = 0; i < slices_no; i++)
	{
		Data3D data;
		
		Data4DRaw data4d_raw = data4DRaw_input;
		int gradients_no = data4d_raw.size();
		Data3D reconstructed_data_3D(gradients_no);

		for (int j = 0; j < gradients_no; j++)
		{
			Data3DRaw data_raw = data4d_raw.at(j);
			data = FourierTransform(data_raw);
			MatrixXd reconstructed_data;
			//Rekonstrukcja obrazu
			reconstructed_data = LSreconstruction(data);
			reconstructed_data_3D.at(j) = reconstructed_data;
			//tymczasowy zapis do pliku

		}

		slices.at(i) = reconstructed_data_3D;

	}

	//zwracana wartoœæ
	data4D_output = slices;
}

Data3D Reconstruction::FourierTransform(Data3DRaw raw_data)
{

	Data3D data;
	data = ifft(raw_data); //wywo³anie funkcji do odwrotnej transformaty Fouriera
	return data;
}

Data3D Reconstruction::ifft(Data3DRaw raw_data)
{
	int sizey = raw_data.at(0).rows(); // liczba wierszy
	int sizex = raw_data.at(0).cols();// liczba kolumn
	MatrixXd afteridftmatrix(sizey, sizex);
	Data3D afteridftvector(L);

	for (int k = 0; k < L; k++)
	{
		MatrixXcd log = raw_data.at(k);

		//-----------------------

		std::vector<std::complex<double>> a(sizex*sizey);//zdefiniowanie wektora wejœciowego
		int count = 1;
		//#pragma omp parallel for shared(log, a, count, sizey, sizex) private(i, j)
		for (int i = 0; i < sizey; i++)
		{
			for (int j = 0; j < sizex; j++)
			{
				a[i*sizex + j] = log(i, j);
				count++;
			}
		}

		std::vector<std::complex<double>> b(sizex*sizey);//zdefiniowanie wektora wyjœciowego

														 //zdefiniowanie IDFT plan
		fftw_plan plan = fftw_plan_dft_2d(sizey, sizex, reinterpret_cast<fftw_complex*>(&a[0]), reinterpret_cast<fftw_complex*>(&b[0]), FFTW_BACKWARD, FFTW_ESTIMATE);
		fftw_execute(plan);
		fftw_destroy_plan(plan);
		fftw_cleanup();
		double tmp;
		//powrót do macierzy
		//#pragma omp parallel for shared(b, tmp, afteridftmatrix, sizey, sizex) private(i, j)
		for (int i = 0; i < sizey; i++)
		{
			for (int j = 0; j < sizex; j++)
			{
				tmp = abs(b.at(i*sizex + j));
				afteridftmatrix(i, j) = tmp;
			}
		}

		afteridftvector.at(k) = afteridftmatrix;

	}
	return afteridftvector;
}

MatrixXd Reconstruction::LSreconstruction(Data3D data)
{
	//rekonstrukcja SENSE
	int rec_step = 256 / r;
	MatrixXd Sx(L, r);
	VectorXd Dr(r, 1);
	MatrixXd Image(256, 256);
	MatrixXd Ds(L, 1);
	std::vector<MatrixXd> I_raw = data;
	std::vector<MatrixXcd> S = Reconstruction::sensitivityMaps3D;
	std::vector<MatrixXd> Sd(L);
	MatrixXd temp(256, 256);
	for (int k = 0; k < L; k++)
	{
		//#pragma omp parallel for shared(S, k, temp) private(i, j)
		for (int i = 0; i < 256; i++)
		{
			for (int j = 0; j < 256; j++)
			{
				temp(i, j) = abs(S.at(k)(i, j));

			}
		}

		Sd.at(k) = temp; //zamiana wartoœci na double
	}
	Reconstruction::SensMaps = Sd;
	MatrixXd log = I_raw.at(1);

	int sizex = log.rows(); // liczba wierszy
	int sizey = log.cols(); //liczba kolumn


	for (int y = 0; y <sizey; y++)
	{
		for (int x = 0; x<sizex; x++)
		{

			for (int j = 0; j<L; j++)
			{
				Sx(j, 0) = Sd.at(j)(x, y);
				Sx(j, 1) = Sd.at(j)(x + rec_step, y);
			}

			for (int k = 0; k<L; k++)
			{
				Ds(k) = I_raw.at(k)(x, y);
			}
			//wyliczenie zgodnie ze wzorem
			MatrixXd temp = (Sx.transpose()*Sx);
			MatrixXd temp2 = temp.inverse()*Sx.transpose();
			Dr = temp2*Ds;

			Image(x, y) = Dr(0);
			Image(x + rec_step, y) = Dr(1);

		}

	}

	return Image; //zrekonstruowany obraz
}

MatrixXd Reconstruction::TikhonovRegularization(Data3D data, MatrixXd image)
{
	//regularyzacja Tichonova
	int rec_step = 256 / r;
	double lambda = 0.2;
	MatrixXd Sx(L, r);
	VectorXd Dr(r, 1);
	MatrixXd maj;
	MatrixXd Image(256, 256);
	MatrixXd Ds(L, 1);
	Matrix2d A;
	A(0, 0) = 1;
	A(1, 0) = 0;
	A(0, 1) = 0;
	A(1, 1) = 1;
	std::vector<MatrixXd> I_raw = data;
	std::vector<MatrixXd> Sd = Reconstruction::SensMaps;
	MatrixXd LastImage = medianFilter(image, 3);
	MatrixXd ImagePoint(2, 1);
	MatrixXd temp(256, 256);
	MatrixXd log = I_raw.at(1);

	int sizex = log.rows(); // liczba wierszy
	int sizey = log.cols(); //liczba kolumn


	for (int y = 0; y <sizey; y++)
	{
		for (int x = 0; x<sizex; x++)
		{

			for (int j = 0; j<L; j++)
			{
				Sx(j, 0) = Sd.at(j)(x, y);
				Sx(j, 1) = Sd.at(j)(x + rec_step, y);
			}

			for (int k = 0; k<L; k++)
			{
				Ds(k) = I_raw.at(k)(x, y);
			}
			//wyliczenie zgodnie ze wzorem
			ImagePoint(0, 0) = LastImage(x, y);
			ImagePoint(1, 0) = LastImage(x + rec_step, y);
			//temp = (Sx.transpose()*Sx+((lambda*lambda)*A.transpose()*A));
			Dr = ImagePoint + ((Sx.transpose()*Sx + ((lambda*lambda)*A.transpose()*A)).inverse()*Sx.transpose())*(Ds - (Sx*ImagePoint));
			//Dr = ImagePoint+r*r1;

			Image(x, y) = Dr(0);
			Image(x + rec_step, y) = Dr(1);

		}

	}
	return Image; //zrekonstruowany obraz
}

void Reconstruction::writeToCSVfile(std::string name, MatrixXd matrix)
{
	std::ofstream file(name.c_str());

	for (int i = 0; i < matrix.rows(); i++) {
		for (int j = 0; j < matrix.cols(); j++) {

			if (j + 1 == matrix.cols()) {
				file << (matrix(i, j));
			}
			else {
				file << (matrix(i, j)) << ',';
			}
		}
		file << '\n';
	}
	file.close();
}

MatrixXd Reconstruction::medianFilter(MatrixXd image, int windowSize)
{

	std::vector<double> pixels;
	double color;
	int a;
	int b;

	MatrixXd newimage(image.rows(), image.cols());
	//glowny loop dla siatki pixeli wyznaczajacy tzw pixel wyrozniony
	for (int x = 0; x < image.rows(); ++x)
	{
		for (int y = 0; y < image.cols(); ++y)
		{
			//loopy odpowiedzialne za operowanie na oknie filtrujacym
			// #pragma omp parallel for shared(b, a, x, y, color, pixels) private(i, j)
			for (int j = -(windowSize / 2); j < windowSize - 1; ++j)
			{
				for (int i = -(windowSize / 2); i < windowSize - 1; ++i)
				{
					a = x + i;
					b = y + j;
					if (a<0)
						a = 0;
					if (a > 255)
						a = 255;
					if (b<0)
						b = 0;
					if (b > 255)
						b = 255;
					color = image(a, b);
					pixels.push_back(color);
				}
			}

			sort(pixels.begin(), pixels.end());
			newimage(x, y) = pixels[pixels.size() / 2];
			pixels.clear();
		}
	}
	return newimage;
}

