#include "Reconstruction.h"
#include "qdebug.h"
#include <fftw3.h>
#include "Globals.h"


Reconstruction::Reconstruction(Data3DRaw raw_data, Data3DRaw sensitivity_maps, int L, int r)
{
	qDebug() << "Reconstruction constructor called";
	data3DRaw_input = raw_data;
	sensitivityMaps3D = sensitivity_maps;
	this->L = L;
	this->r = r;
	dtype = STRUCTURAL_DATA;
	StructuralDataAlgorithm();
}

Reconstruction::Reconstruction(Data4DRaw data)
{
	qDebug() << "Reconstruction constructor called";
	data4DRaw_input = data;
	dtype = DIFFUSION_DATA;
}

void Reconstruction::StructuralDataAlgorithm() {

	Data3D data;
	data=FourierTransform();
	LSreconstruction(data);
}

void Reconstruction::DiffusionDataAlgorithm() {

}

Data3D Reconstruction::FourierTransform() {

	Data3DRaw raw_data = data3DRaw_input;
	Data3D data;
	data=ifft(raw_data);
	return data;
		}

std::vector<MatrixXd> Reconstruction::ifft(Data3DRaw raw_data)
{
	
	MatrixXd afteridftmatrix(128,256);
	Data3D afteridftvector(L);

	for (int k = 0; k < L; k++)
	{ 
		MatrixXcd log = raw_data.at(k);
		
		//-----------------------
	
		int sizey =log.rows(); // liczba wierszy
		int sizex =log.cols();// liczba kolumn
		
		std::vector<std::complex<double>> a(sizex*sizey);
		int count = 1;
		for (int i = 0; i < sizey; i++)
		{
			for (int j = 0; j < sizex; j++)
			{
				a[i*sizex + j] = log(i, j);
				count++;
			}
		}

		std::vector<std::complex<double>> b(sizex*sizey);
		
	//create a IDFT plan
	fftw_plan plan = fftw_plan_dft_2d(128, 256, reinterpret_cast<fftw_complex*>(&a[0]), reinterpret_cast<fftw_complex*>(&b[0]), FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	fftw_cleanup();
	double t;
	//powrót do macierzy
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			t = abs(b.at(i*sizex + j));
			afteridftmatrix(i,j) = t;
		}
	}
	
	// allocate input arrays
		
		
		
		afteridftvector.at(k) = afteridftmatrix;

}
	int g=2;
	return afteridftvector;
}

void Reconstruction::LSreconstruction(Data3D data)
{

	//SENSE reconstruction

	int rec_step = 256/r;
	MatrixXd Sx(8,2);
	VectorXd Dr(2,1);
	MatrixXd DR(256, 256);
	MatrixXd Ds(8,1);
	std::vector<MatrixXd> I_raw = data;
	std::vector<MatrixXcd> S = Reconstruction::sensitivityMaps3D;
	std::vector<MatrixXd> Ss(L);
	MatrixXd temp(256,256);
	for (int k = 0; k < L; k++)
	{
		for (int i = 0; i < 256; i++)
		{
			for (int j = 0; j < 256; j++)
			{
				temp(i,j) = abs(S.at(k)(i, j));
				
			}
		}
		Ss.at(k) = temp;
	}
	
	MatrixXd log = I_raw.at(1);

	int sizex = log.rows(); // liczba wierszy
	int sizey = log.cols();


	for (int y = 0; y <sizey; y++)
	{
		for (int x = 0; x<sizex; x++)
		{

			for (int j = 0; j<L;j++)
			{ 
				Sx(j,0) = Ss.at(j)(x, y);
				Sx(j,1) = Ss.at(j)(x+rec_step, y);
			}

			for (int k = 0;k<L;k++)
			{ 
				Ds(k) = I_raw.at(k)(x, y);
			}
			//Ds = Ds.transpose(); //obrócenie macierzy

			MatrixXd temp = (Sx.transpose()*Sx);
			MatrixXd temp2 = temp.inverse()*Sx.transpose();

			Dr = temp2*Ds;
			//Dr(1) = 1;
			//Dr(2) = 2;

			DR(x, y) = Dr(0);
			DR(x+rec_step, y) = Dr(1);

		}

	}

}
