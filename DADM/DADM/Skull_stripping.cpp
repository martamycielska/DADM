#include "Skull_stripping.h"
#include "qdebug.h"
#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
typedef Matrix<bool, Dynamic, Dynamic> MatrixXb;
const double PI = 3.14159265359;
using namespace std;

Skull_stripping::Skull_stripping(Data3D data)
{
	qDebug() << "Skull_stripping constructor called";
	this->data3D_input = data;
}

Skull_stripping::Skull_stripping(Data4D data)
{
	qDebug() << "Skull_stripping constructor called";
	this->data4D_input = data;
	dtype = DIFFUSION_DATA;
}

void Skull_stripping::StructuralDataAlgorithm() {

}

void Skull_stripping::DiffusionDataAlgorithm() {
	qDebug() << "ddd";
}

MatrixXd slice_to_fit(Data3D input) {
	Eigen::MatrixXd slice;
	//choose another more appropriate slice to fit first level set
	//serch size of this slice to find point to find elipse in the next step
	slice = input[0];
	return slice;
}


MatrixXd elipse(Data3D input) {

	



	MatrixXd slice;
	slice = slice_to_fit(input);
	int w = slice.rows();
	int k = slice.cols();
	MatrixXb slice_threshold = (slice.array() < 50);
	// serch position of frame
	//first loop for find position

	int swit = 0;
	int j = 0;
	int i = 0;
	int poz_w_a1 = 0;
	for (j = 0; j < w; j++) {
		if (swit == 1) { break; }
		for (i = 0; i < k; i++) {
			if (slice_threshold(j, i) != 1) {
				poz_w_a1 = j;
				swit = 1;
				break;
			}

		}
	}

	//////////////////////////////////////////////

	int swit = 0;
	int j = 0;
	int i = 0;
	int poz_w_a2 = 0;
	for (j = (w - 1); j <= 0; j--) {
		if (swit == 1) { break; }
		for (i = 0; i < k; i++) {
			if (slice_threshold(j, i) != 1) {
				poz_w_a2 = j;
				swit = 1;
				break;
			}

		}
	}

	int pol_sz = (poz_w_a2 - poz_w_a1) / 2 + poz_w_a1;

	//////////////////////////////////////////////////////posiotion b1
	int swit = 0;
	int j = 0;
	int i = 0;
	int poz_k_b1 = 0;
	for (j = 0; j < k j++) {
		if (swit == 1) { break; }
		for (i = 0; i < w; i++) {
			if (slice_threshold(j, i) != 1) {
				poz_k_b1 = j;
				swit = 1;
				break;
			}

		}
	}

	int swit = 0;
	int j = 0;
	int i = 0;
	int poz_k_b2 = 0;
	for (j = (k - 1); j <= 0; j--) {
		if (swit == 1) { break; }
		for (i = 0; i < w; i++) {
			if (slice_threshold(j, i) != 1) {
				poz_k_b2 = j;
				swit = 1;
				break;
			}

		}
	}


	int pol_dl = (poz_k_b2 - poz_k_b1) / 2 + poz_k_b1;

	////////////////////////now you can find 2 vectors semiaxis of elipse 

	//////////////////////first find y and x (transpose x)
	MatrixXd x;
	MatrixXd y;

	y = slice_threshold.row(pol_sz);
	x = slice_threshold.col(pol_dl);
	x = x.adjoint();


	MatrixXd diffx;
	MatrixXd diffy;
	int len_x;
	int len_y;
	////////////////you need amount of columns
	len_x = x.size();
	len_y = y.size();


	diffx = diffx.setOnes(1, (len_x - 4));
	diffy = diffy.setOnes(1, (len_y - 4));

	///Differentation x

	int i;
	for (i = 0; i < (len_x - 4); i++) {
		diffx(1, i) = ((-1)*x(1, i) - 2 * x(1, (i + 1)) + 2 * x(1, (i + 3)) + x(1, (i + 4))) / 8;
	}

	///Differentation y

	int i;
	for (i = 0; i < (len_y - 4); i++) {
		diffy(1, i) = ((-1)*y(1, i) - 2 * y(1, (i + 1)) + 2 * y(1, (i + 3)) + y(1, (i + 4))) / 8;
	}


	//seraching parameters to axis a

	i = 0;
	//from left to right side
		//serach d1
	while (s(i) == 0) {
		i = i++;
	}
	//serach d2
	while (diffx(i + 1) < diffx(i)) {
		i = i + 1;
	}


	//serach d3
	while (diffx(i + 1) > diffx(i)) {
		i = i + 1;
	}

	//serach d4
	while (diffx(i) == 0) {
		i = i + 1;
	}

	//serach d5
	while (diffx(i + 1) > diffx(i)) {
		i = i + 1;
	}


	//serach d6
	while (diffx(i + 1) < diffx(i)) {
		i = i + 1;
	}
	//serach d7
	while (diffx(i) == 0) {
		i = i + 1;
	}


	//serach d8
	while (diffx(i + 1) < diffx(i)) {
		i = i + 1;
	}
	int d8 = i;


	i = (diffx.size() - 1);

	//serach f1
	while (diffx(i) == 0) {
		i = i - 1;
	}
	//serach f2
	while (diffx(i - 1) > diffx(i)) {
		i = i - 1;
	}

	//serach f3
	while (diffx(i - 1) < diffx(i)) {
		i = i - 1;
	}

	//serach f4
	while (diffx(i) == 0) {
		i = i - 1;
	}

	//serach f5
	while (diffx(i - 1) < diffx(i)) {
		i = i - 1;
	}
	//serach f6
	while (diffx(i - 1) > diffx(i)) {
		i = i - 1;
	}

	//serach f7
	while (diffx(i) == 0) {
		i = i - 1;
	}

	//serach f8
	while (s(i - 1) > s(i)) {
		i = i - 1;
	}
	int f8 = i;


	int b1 = d8;
	int b2 = f8;

	////////////serching point for diffy
	//serach d1

	while (diffy(i) == 0) {
		i = i + 1;
	}

	//serach d2
	while (diffy(i + 1) < diffy(i)) {
		i = i + 1;
	}

	//serach d3
	while (diffy(i + 1) > diffy(i)) {
		i = i + 1;
	}

	//serach d4
	while (diffy(i) == 0) {
		i = i + 1;
	}

	//serach d5
	while (diffy(i + 1) > diffy(i)) {
		i = i + 1;
	}

	//serach d6
	while (diffy(i + 1) < diffy(i)) {
		i = i + 1;
	}

	//serach d7
	while (diffy(i) == 0) {
		i = i + 1;
	}

	//serach d8
	while (diffy(i + 1) < diffy(i)) {
		i = i + 1;
	}
	d8 = i;

	/////////////////////////////////////////////


	i = (diffy.size() - 1);
	//serach f1
	while (s(i) == 0) {
		i = i - 1;
	}

	//serach f2
	while (diffy(i - 1) > diffy(i)) {
		i = i - 1;
	}

	//serach f3
	while (diffy(i - 1) < diffy(i)) {
		i = i - 1;
	}

	//serach f4
	while (diffy(i) == 0) {
		i = i - 1;
	}

	//serach f5
	while (diffy(i - 1) < diffy(i)) {
		i = i - 1;
	}

	//serach f6
	while (diffy(i - 1) > diffy(i)) {
		i = i - 1;
	}

	//serach f7
	while (diffy(i) == 0) {
		i = i - 1;
	}

	//serach f8
	while (diffy(i - 1) > diffy(i)) {
		i = i - 1;
	}

	int f8 = i;

	int a1 = d8;
	int a2 = f8;


	/////////////////////////////draw elipse

	int a = (a2 - a1) / 2;
	b1 = b1 - 1;
	b2 = b2 + 1;
	int b = (b2 - b1) / 2;
	int x0 = a + a1;
	int y0 = b + b1;
	VectorXd t;
	int size_t = 126;
	t = t.setLinSpaced(size_t, (-PI), PI);
	MatrixXd time;
	time.col(1) = t;
	time = time.adjoint();

	ArrayXd x_e;
	ArrayXd y_e;


	x_e = time.cos();
	y_e = time.cos();

	
	x_e.array() += x0;
	y_e.array() += y0;
	
	
	x_e = round(x_e);
	y_e = round(y_e);
	int c;
	int d;


	c = slice.rows();
	d = slice.cols();
	MatrixXd EL;
	EL = MatrixXd::Zero(c, d);
	for (i = 0; i < x_e.size(); i++) {

		EL(y_e(i, 1), x_e(i, 1)) = 255;

	}
	//reshape, add 1 column to safe information about position of frame
	EL.conservativeResize(w,k+1);;
	EL(1, d) = poz_w_a1;
	EL(2, d) = poz_w_a2;
	EL(3, d) = poz_k_b1;
	EL(4,d) = poz_k_b2;
	return EL;

}
////////////////////////Sort elements to median filter
void insertionSort(int window[])
{
	int temp, i, j;
	for (i = 0; i < 9; i++) {
		temp = window[i];
		for (j = i - 1; j >= 0 && temp < window[j]; j--) {
			window[j + 1] = window[j];
		}
		window[j + 1] = temp;
	}
}

////////////////////////Use median filter
MatrixXd median_filter(MatrixXd slice) {

	int window[9];

	MatrixXd slice_smooth;
	int w = slice.rows();
	int k = slice.cols();
	slice_smooth = MatrixXd::Zero(w, k);

	for (int y = 1; y < w - 1; y++) {
		for (int x = 1; x <k - 1; x++) {

			// Pick up window element

			window[0] = slice(y - 1, x - 1);
			window[1] = slice(y, x - 1);
			window[2] = slice(y + 1, x - 1);
			window[3] = slice(y - 1, x);
			window[4] = slice(y, x);
			window[5] = slice(y + 1, x);
			window[6] = slice(y - 1, x + 1);
			window[7] = slice(y, x + 1);
			window[8] = slice(y + 1, x + 1);

			// sort the window to find median
			insertionSort(window);

			// assign the median to centered element of the matrix
			slice_smooth(y, x) = window[4];
		}
	}
	

	return slice_smooth;

}


//function to level sety

double f;


MatrixXd Dirac(MatrixXd x, double sigma) {
	MatrixXd f2,f,b;
	double f1;
	f1 = 0.5 / sigma;
	f2 = (PI / sigma)*x.array();
	f2 = f2.cos();
	f2.array() += 1;
	f = f1*f2.array();
	b = (x.array<= sigma) && (x.array() >= -sigma); %dla | x | < sigma
	f = f.array()*b.array();
	return f;
}


MatrixXd div(MatrixXd nx, MatrixXd ny) {
	//dywergencja, obliczamy gradienty
	//calculate gradient
	MatrixXd nxx, nyy, f;
	nxx = nx.rightCols(nx.cols() - 1) - nx.leftCols(nx.cols() - 1);  // Matlab: dAx = diff(A,1,2)
	nyy = ny.bottomRows(ny.rows() - 1) - ny.topRows(ny.rows() - 1);  // Matlab: dAy = diff(A)
	f = nxx + nyy;
	return f;

}


MatrixXd distReg_p2(MatrixXd phi) {
	//obliczenie R z użyciem p2
	MatrixXd phi_x, phi_y, s, a, b, ps, ar_sin, sin1, dps1, dps2, dps;
	phi_x = phi.rightCols(phi.cols() - 1) - phi.leftCols(phi.cols() - 1);  // Matlab: dAx = diff(A,1,2)
	phi_y= phi.bottomRows(phi.rows() - 1) - phi.topRows(phi.rows() - 1);  // Matlab: dAy = diff(A)
	s=phi_x.array().square() + phi_x.array().square();
	s = s.array().sqrt();
	
	a = (s.array() >= 0) && (s.array() <= 1);
	b = (s.array() > 1);
	ar_sin = 2 * PI*s.array();
	sin1 = ar_sin.sin();
	sin1 = a.array()*sin1.array() / (2 * PI);

	ps =  sin1.array()+b.array()*(s.array() - 1);
	dps1 = ((ps.array() != 0)*ps.array() + (ps.array() == 0));
	dps2=((s.array()!= 0)*s.array() + (s.array() == 0)); //wybór s do dp, obliczenie dp
	dps = dps1.array() / dps2.array();
		f = div(dps.array()*phi_x.array() - phi_x.array(), dps.array()*phi_y.array() - phi_y.array()) + 4 * del2(phi);
//PISZ LAPLASJANA
}






void algorithm(Data3D input) {

	//Skull_stripping(input);
	int poz_w_a1;
	int poz_w_a2;
	int poz_k_b1;
	int poz_k_b2;
	


	//create elipse
	MatrixXd Img;
	Img= elipse(input);
	int w = Img.rows();
	int k = Img.cols();

	Img(1,k) = poz_w_a1;
	Img(2, k)= poz_w_a2;
	Img(3, k)=poz_k_b1;
	Img(4, k) = poz_k_b2;

	//Ustawienia
		int delta_t = 5;  // delta_t
		double mi = 0.2 / delta_t;  // współczynnik mi*R(phi), gdzie R to regulowanie dystansu, występuję w równaniu na energię potencjalną Ep = mi*R + Ezew
		int iter_inner = 5;
		int iter_outer = 40;
		double lambda = 5; // współczynnik do funkcji L(phi), L(phi) = calka z(g*delta* | phi(x) | dx)
		double alfa = 0.5;  // można go śmiało modyfikować, współczynnik do A, gdzie A = całka z(g*H(-phi)dx)), H - funkcja Heaviside, A, oblicza wartosci dla SIGMA<0
		double epsilon = 1.5; //do delty diraca, deltadiraca daje informacje(z całki) o energii wzdłuż konturu zerowego

		double sigma = 1.5;     //do funkcji gaussa, odchylenie standardowe

	//
		MatrixXd slice_smooth, slice;
		slice=slice_to_fit(input);/////// future 
		///median filtration

		slice_smooth = median_filter(slice);
		MatrixXd Ix, Iy, f,g,f_help;
		//calculate gradient
		Ix = slice_smooth.rightCols(slice_smooth.cols() - 1) - slice_smooth.leftCols(slice_smooth.cols() - 1);  // Matlab: dAx = diff(A,1,2)
		Iy = slice_smooth.bottomRows(slice_smooth.rows() - 1) - slice_smooth.topRows(slice_smooth.rows() - 1);  // Matlab: dAy = diff(A)

		f=Ix.array().square() + Iy.array().square();
		f_help = f.array() + 1;
		g=f_help.array().inverse();
		int c0 = 2;
		MatrixXd initialLSF;
		int w = Img.rows();
		int k = Img.cols();
		initialLSF=MatrixXd::Ones(w, k);
		initialLSF.array() *= c0;

		//initialLSF(i, j, p, q) = -c0;
		//Block of size(p, q), starting at(i, j)
		initialLSF.block(poz_w_a1, poz_w_b1, poz_w_a2- poz_w_a1, poz_w_b2-poz_w_b1)=-c0;
		MatrixXd phi;
		phi = initialLSF;

		int potentialFunction = 2;

		for (int n = 1; n >= iter_outer; n++) {
			phi = level_set(phi, g, lambda, mi, alfa, epsilon, delta_t, iter_inner, potentialFunction);
		}
		alfa = 0;
		int iter_refine = 10;
		phi = level_set(phi, g, lambda, mi, alfa, epsilon, delta_t, iter_refine, potentialFunction);
		MatrixXd finalLSF;
		finalLSF = phi;
		//////////////////////end first fitting











}





		


