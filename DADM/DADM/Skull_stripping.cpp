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




MatrixXd Dirac(MatrixXd x, double sigma) {
	MatrixXd f2,f,b;
	double f1;
	f1 = 0.5 / sigma;
	f2 = (PI / sigma)*x.array();
	f2 = f2.cos();
	f2.array() += 1;
	f = f1*f2.array();
	b = (x.array<= sigma) && (x.array() >= -sigma); //dla | x | < sigma
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


MatrixXd del2(MatrixXd phi) {
	int c, d, i, j;
	int pixel;
	MatrixXd phi_out(phi.rows(), phi.cols());
	//Laplasian kernel
	MatrixXd kernel(3, 3);

	kernel<< 0, -1, 0;
	-1, 4, -1;
	0, -1, 0;

	int x, y;
	x = phi.rows();
	y = phi.cols();

	phi_out= MatrixXd::Zero(x, y);
	

	for (c = 1; c < x; c++) {
		for (d = 1; d < y; d++) {
			pixel = 0;

			for (i = 0; i <= 3; i++) {
				for (j = 0; j <= 3; j++) {
					pixel = kernel(i, j)*phi(c + i - 1, d + j - 1) + pixel;
				}
			}
			phi_out(c, d) = pixel;

		}
	}

	return phi_out;

}




MatrixXd distReg_p2(MatrixXd phi) {
	//obliczenie R z użyciem p2
	MatrixXd phi_x, phi_y, s, a, b, ps, ar_sin, sin1, dps1, dps2, dps, f;
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

	MatrixXd ar_div1, ar_div2, g,h ;
	ar_div1 = dps.array()*phi_x.array() - phi_x.array();
	ar_div2 = dps.array()*phi_y.array() - phi_y.array();

		f = div(ar_div1, ar_div2) - 4 * del2(phi);
		return f;
}


MatrixXd NeumannBoundCond(MatrixXd f) {
	// Reinicjalizacja metodą Neumanna->zapewnienie lepszej
		//stablizacji->lepszego dopasowania
	int ncol, nrow;
	MatrixXd g,1;
	nrow = f.rows();
	ncol = f.cols();
	g = f;
	g(0, 0) = g(2, 2);
	g(nrow-1, ncol-1)=g(nrow - 3, ncol - 3);
	g.block(0, 1, 1, ncol - 2 - 2) = g.block(2, 1, 1, ncol - 2 - 2);
	g.block(nrow-1, 1, 1, ncol - 2 - 2) = g.block(nrow-3, 1, 1, ncol - 2 - 2);
	g.block(1, 0, nrow - 2 - 2, 1) = g.block(1, 2, nrow - 2 - 2, 1);
	g.block(1, ncol-1, nrow - 2 - 2, 1) = g.block(1, ncol-3, nrow - 2 - 2, 1);
	return g;
}


MatrixXd level_set(MatrixXd phi_0, MatrixXd g, double lambda, double mi, double alfa, double epsilon, double delta_t, int iter, int potentialFunction) {
	MatrixXd phi, vx, vy, phi_x, phi_y, s, Nx, Ny, curvature;
	phi = phi_0;
	vx = g.rightCols(g.cols() - 1) - g.leftCols(g.cols() - 1);  // Matlab: dAx = diff(A,1,2)
	vy = g.bottomRows(g.rows() - 1) - g.topRows(g.rows() - 1);  // Matlab: dAy = diff(A)
	int k;
	for (k = 0; k < iter; k++) {


		phi = NeumannBoundCond(phi);
		phi_x = phi.rightCols(phi.cols() - 1) - phi.leftCols(phi.cols() - 1);  // Matlab: dAx = diff(A,1,2)
		phi_y = phi.bottomRows(phi.rows() - 1) - phi.topRows(phi.rows() - 1);  // Matlab: dAy = diff(A)
		s = phi_x.array().square() + phi_y.array().square();
		s.array() = s.array().sqrt();
		double smallNumber = 0.000000001;
		Nx = phi_x.array / (s.array() + smallNumber);
		Ny = phi_y.array / (s.array() + smallNumber);
		curvature = div(Nx, Ny);
		//Wybór funkcji do obliczania potencjału p
		MatrixXd distRegTerm;
		if (potentialFunction == 1) {
			distRegTerm = 4 * del2(phi) - curvature;;
		} //% zmiana phi po czasie, obliczan z użycie dywergencji oraz p1
		else {
			distRegTerm = distReg_p2(phi);//% zmiana phi po czasie, obliczan z użycie dywergencji oraz p2
		}
		MatrixXd diracPhi = Dirac(phi, epsilon);
		MatrixXd  areaTerm = diracPhi.array()*g.array(); // rozszerzenie balonu dzięki sile
		MatrixXd edgeTerm = diracPhi.array()*(vx.array()*Nx.array() + vy.array()*Ny.array()) + diracPhi.array()*g.array()*curvature.array();
		phi.array() = phi.array() + delta_t*(mi*distRegTerm.array() + lambda*edgeTerm.array() + alfa*areaTerm.array());
	}
}


MatrixXd levelset(int el_or_sku, double alfa, MatrixXd Img, MatrixXd earlierLSF, int poz_w_a1, int poz_w_a2, int poz_k_b1, int poz_k_b2) {
	double delta_t = 5;  // delta_t
	double mi = 0.2 / delta_t;  // współczynnik mi*R(phi), gdzie R to regulowanie dystansu, występuję w równaniu na energię potencjalną Ep = mi*R + Ezew
	int iter_inner = 5;
	int iter_outer = 40;
	double lambda = 5; // współczynnik do funkcji L(phi), L(phi) = calka z(g*delta* | phi(x) | dx)
	double alfa = 0.5;  // można go śmiało modyfikować, współczynnik do A, gdzie A = całka z(g*H(-phi)dx)), H - funkcja Heaviside, A, oblicza wartosci dla SIGMA<0
	double epsilon = 1.5; //do delty diraca, deltadiraca daje informacje(z całki) o energii wzdłuż konturu zerowego

	double sigma = 1.5;     //do funkcji gaussa, odchylenie standardowe

							//
	MatrixXd slice_smooth;
	///median filtration

	slice_smooth = median_filter(Img);
	MatrixXd Ix, Iy, f, g, f_help;
	//calculate gradient
	Ix = slice_smooth.rightCols(slice_smooth.cols() - 1) - slice_smooth.leftCols(slice_smooth.cols() - 1);  // Matlab: dAx = diff(A,1,2)
	Iy = slice_smooth.bottomRows(slice_smooth.rows() - 1) - slice_smooth.topRows(slice_smooth.rows() - 1);  // Matlab: dAy = diff(A)

	f = Ix.array().square() + Iy.array().square();
	f_help = f.array() + 1;
	g = f_help.array().inverse();
	int c0 = 2;
	MatrixXd initialLSF;
	int w = Img.rows();
	int k = Img.cols();
	initialLSF = MatrixXd::Ones(w, k);
	initialLSF.array() *= c0;

	//initialLSF(i, j, p, q) = -c0;
	//Block of size(p, q), starting at(i, j)
	MatrixXd phi;
	if (el_or_sku == 1) {
	initialLSF.block(poz_w_a1, poz_k_b1, poz_w_a2 - poz_w_a1, poz_k_b2 - poz_k_b1).array() = -c0;
	phi = initialLSF;
	}
	else {

		initialLSF = earlierLSF;
		phi = initialLSF;

	}
	int potentialFunction = 2;

	for (int n = 1; n >= iter_outer; n++) {
		phi = level_set(phi, g, lambda, mi, alfa, epsilon, delta_t, iter_inner, potentialFunction);
	}
	alfa = 0;
	int iter_refine = 10;
	phi = level_set(phi, g, lambda, mi, alfa, epsilon, delta_t, iter_refine, potentialFunction);
	MatrixXd finalLSF;
	finalLSF = phi;

	return finalLSF;


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
	//Cut data with information about elipse size
	Img = Img.block(0, 0, Img.rows(), Img.cols() - 1);
	//Ustawienia
	//
	MatrixXd help(1, 1);
	help.array() = 0;
	MatrixXd first_contour_fit, second_contour_fit;
	first_contour_fit = levelset(1, 1.5, Img, help, poz_w_a1, poz_w_a2, poz_k_b1, poz_k_b2);
	second_contour_fit = levelset(2, 1.5, Img, first_contour_fit, 0, 0, 0, 0);
	
	
	MatrixXb logic_mask = (second_contour_fit.array() < (-1));
	//to będzie na pętli second itd


}





		


