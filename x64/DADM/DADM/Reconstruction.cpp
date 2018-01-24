#include "Reconstruction.h"
#include "qdebug.h"
#include <fftw3.h>
#include <Globals.h>
#include <iostream>
#include <fstream>
#include <string>




Reconstruction::Reconstruction(Data4DRaw raw_data, Data3DRaw sensitivity_maps, int L, int r)
{
	qDebug() << "Reconstruction constructor called";
	data4DRaw_input = raw_data;
	sensitivityMaps3D = sensitivity_maps;
	this->L = L;
	this->r = r;
	dtype = STRUCTURAL_DATA;
}

Reconstruction::Reconstruction(Data5DRaw data, Data3DRaw sensitivity_maps, int L, int r)
{
	qDebug() << "Reconstruction constructor called";
	data5DRaw_input = data;
	sensitivityMaps3D = sensitivity_maps;
	this->L = L;
	this->r = r;
	dtype = DIFFUSION_DATA;

}

void Reconstruction::StructuralDataAlgorithm() {

	int slices_no = data4DRaw_input.size();//slices number
	size = sensitivityMaps3D[0].rows();
	//qDebug() << "Size: " << slices_no;
	Data3DRaw data_raw;
	MatrixXd reconstructed_data;
	Data3D slices(slices_no);

	for (int i = 0; i < slices_no; i++)
	{
		//qDebug() << "Iteration: " << i;
		//Inverse Discrete Fourier Transform
		data_raw = data4DRaw_input[i];
		data_raw = FourierTransform(data_raw);
		
		//Image Reconstruction
		reconstructed_data = LSreconstruction(data_raw);
		//qDebug() << "LS reconstruction done";

		reconstructed_data = TikhonovRegularization(data_raw, reconstructed_data);
		//qDebug() << "Tikhonov regularization done";

		//Value normalization to 0-255
		double min = reconstructed_data.minCoeff();
		double max = reconstructed_data.maxCoeff();
#pragma omp parallel for shared(reconstructed_data, min, max) private(z, a)
		for (int z = 0; z < size; z++)
		{
			for (int a = 0; a < size; a++)
			{
				reconstructed_data(z,a)=((reconstructed_data(z, a)-min)*255)/(max-min);
			}
		}
		slices.at(i) = reconstructed_data;
		
	}
	//output slices
	data3D_output = slices;
	
} 

void Reconstruction::DiffusionDataAlgorithm()
{
	int slices_no = data5DRaw_input.size();
	size = sensitivityMaps3D[0].rows();
	Data4D slices(slices_no);
	Data3DRaw data_raw;

	for (int i = 0; i < slices_no; i++)
	{
		Data3DRaw data(L);

		Data4DRaw data4d_raw = data5DRaw_input[i];
		int gradients_no = data4d_raw.size();
		
		Data3D reconstructed_data_3D(gradients_no);

		for (int j = 0; j < gradients_no; j++)
		{
			data_raw = data4d_raw.at(j);
			data = FourierTransform(data_raw);
			MatrixXd reconstructed_data(size,size);
			//image reconstruction
			reconstructed_data = LSreconstruction(data);
			reconstructed_data = TikhonovRegularization(data, reconstructed_data);
			
			//Value normalization to 0-255
			double min = reconstructed_data.minCoeff();
			double max = reconstructed_data.maxCoeff();
#pragma omp parallel for shared(reconstructed_data, min, max) private(z, a)
			for (int z = 0; z < size; z++)
				{
					for (int a = 0; a < size; a++)
						{
							reconstructed_data(z, a) = ((reconstructed_data(z, a) - min) * 255) / (max - min);
						}
				}
			reconstructed_data_3D.at(j) = reconstructed_data;
			
			}

		slices.at(i) = reconstructed_data_3D;

	}

	//output slices
	data4D_output = slices;
}

Data3DRaw Reconstruction::FourierTransform(Data3DRaw raw_data)
{

	Data3DRaw data;
	data = ifft(raw_data); //call iffft function
	return data;
}

Data3DRaw Reconstruction::ifft(Data3DRaw raw_data)
{
	int sizey = raw_data.at(0).rows(); // rows number
	int sizex = raw_data.at(0).cols();// columns number
	MatrixXcd afteridftmatrix(sizey, sizex);
	Data3DRaw afteridftvector(L);

	for (int k = 0; k < L; k++)
	{
		MatrixXcd log = raw_data.at(k);

		
		std::vector<std::complex<double>> a(sizex*sizey);//input vector definition
		int count = 1;
		#pragma omp parallel for shared(log, a, count, sizey, sizex) private(i, j)
		for (int i = 0; i < sizey; i++)
		{
			for (int j = 0; j < sizex; j++)
			{
				a[i*sizex + j] = log(i, j);
				count++;
			}
		}

		std::vector<std::complex<double>> b(sizex*sizey);//output vector definition

		//IDFT plan definition
		fftw_plan plan = fftw_plan_dft_2d(sizey, sizex, reinterpret_cast<fftw_complex*>(&a[0]), reinterpret_cast<fftw_complex*>(&b[0]), FFTW_BACKWARD, FFTW_ESTIMATE);
		fftw_execute(plan);
		fftw_destroy_plan(plan);
		fftw_cleanup();
		std::complex<double> tmp;
		//return to matrix
		#pragma omp parallel for shared(b, tmp, afteridftmatrix, sizey, sizex) private(i, j)
		for (int i = 0; i < sizey; i++)
		{
			for (int j = 0; j < sizex; j++)
			{
				tmp = b.at(i*sizex + j);
				afteridftmatrix(i, j) = tmp;
			}
		}

		afteridftvector.at(k) = afteridftmatrix;

	}
	return afteridftvector;
}

MatrixXd Reconstruction::LSreconstruction(Data3DRaw data)
{
	//SENSE RECONSTRUCTION
	int rec_step = size/ r;
	MatrixXcd Sx(L, r);
	VectorXcd Dr(r, 1);
	MatrixXd Image(size, size);
	MatrixXcd Ds(L, 1);
	MatrixXcd temp(size, size);
	
	int sizex = data.at(1).rows(); // rows number
	int sizey = data.at(1).cols(); //columns number

	for (int y = 0; y <sizey; y++)
	{
		for (int x = 0; x<sizex; x++)
		{
#pragma omp parallel for shared(sensitivityMaps3D, x, y, rec_step) private(j, p)
			for (int j = 0; j<L; j++)
			{
				for (int p=0; p<r; p++)
				{ 
				Sx(j, p) = sensitivityMaps3D.at(j)(x + p*rec_step, y);
				}
			}

			for (int k = 0; k<L; k++)
			{
				Ds(k) = data.at(k)(x, y);
			}
			//evaluation according to the formula of LS reconstruction
			MatrixXcd temp = (Sx.transpose()*Sx);
			MatrixXcd temp2 = temp.inverse()*Sx.transpose();
			Dr = temp2*Ds;

			for (int q = 0; q < r; q++)
			{
				Image(x+q*rec_step, y) = abs(Dr(q));
			}

		}

	}

	return Image; //reconstructed image
}

MatrixXd Reconstruction::TikhonovRegularization(Data3DRaw data, MatrixXd image)
{
	//Tikhonov regularization
	int rec_step = size / r;
	double lambda = 0.02;
	MatrixXcd Sx(L, r);
	VectorXcd Dr(r, 1);
	MatrixXd Image(size, size);
	MatrixXcd Ds(L, 1);
	MatrixXd A=MatrixXd::Identity(r,r);
	MatrixXd LastImage = medianFilter(image, 3);
	MatrixXd ImagePoint(r, 1);

	int sizex = data.at(1).rows(); // rows number
	int sizey = data.at(1).cols(); //columns number


	for (int y = 0; y <sizey; y++)
	{
		for (int x = 0; x<sizex; x++)
		{
#pragma omp parallel for shared(sensitivityMaps3D, x, y, rec_step) private(j, p)
			for (int j = 0; j<L; j++)
			{
				for (int p = 0; p<r; p++)
				{
					Sx(j, p) = sensitivityMaps3D.at(j)(x + p*rec_step, y);
				}
			}

			for (int k = 0; k<L; k++)
			{
				Ds(k) = data.at(k)(x, y);
			}
			//evaluation according to the formula of Tikhonov Regularization
			for (int w = 0; w < r; w++) 
			{
				ImagePoint(w, 0) = LastImage(x + w*rec_step, y);
			}
			
			Dr = ImagePoint + ((Sx.transpose()*Sx + ((lambda*lambda)*A.transpose()*A)).inverse()*Sx.transpose())*(Ds - (Sx*ImagePoint));
			
			for (int q = 0; q < r; q++)
			{
				Image(x + q*rec_step, y) = abs(Dr(q));
			}

		}

	}
	return Image; //regularized image
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
	//main loop for a pixel grid, called pixel highlighted
	for (int x = 0; x < image.rows(); ++x)
	{
		for (int y = 0; y < image.cols(); ++y)
		{
			//loops responsible for operating on the filter window
			#pragma omp parallel for shared(b, a, x, y, color, pixels) private(i, j)
			for (int j = -(windowSize / 2); j < windowSize - 1; ++j)
			{
				for (int i = -(windowSize / 2); i < windowSize - 1; ++i)
				{
					a = x + i;
					b = y + j;
					if (a<0)
						a = 0;
					if (a > image.rows() -1)
						a = x;
					if (b<0)
						b = 0;
					if (b > image.cols()-1)
						b = y;
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

