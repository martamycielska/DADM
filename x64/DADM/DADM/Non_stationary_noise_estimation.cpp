#include "Non_stationary_noise_estimation.h"
#include "qdebug.h"

Non_stationary_noise_estimation::Non_stationary_noise_estimation(Data3D data)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->data3D_input = data;
	dtype = STRUCTURAL_DATA;
}

Non_stationary_noise_estimation::Non_stationary_noise_estimation(Data4D data)
{
	qDebug() << "Non stationary noise estimation constructor called";
	this->data4D_input = data;
	dtype = DIFFUSION_DATA;
}

void Non_stationary_noise_estimation::StructuralDataAlgorithm() {
	qDebug() << "START ESTIMATION";
		for (int i = 0; i < data3D_input.size(); i++) {
			setEstimators(data3D_input[i], i);
		}
}

void Non_stationary_noise_estimation::DiffusionDataAlgorithm() {
	
	for (int i = 0; i < data4D_input.size(); i++) {
		for (int j = 0; j < data4D_input[i].size(); j++) {
			setEstimators(data4D_input[i][j], i, j, true);
		}
		GaussEstimator4D.push_back(gradientEstimatorGauss);
		RiceEstimator4D.push_back(gradientEstimatorRice);
		gradientEstimatorGauss.clear();
		gradientEstimatorRice.clear();
	}
}

bool Non_stationary_noise_estimation::getSum(MatrixXd matrix)
{
	return !((matrix.colwise().sum().array() <= 1).any());
}

MatrixXd Non_stationary_noise_estimation::getFinded(MatrixXd matrix, int conditionValue)
{
	std::vector<double> v;
	for (int j = 0; j < matrix.cols(); j++) {
		for (int i = 0; i < matrix.rows(); i++) {
			if (matrix(i, j) == conditionValue) {
				v.push_back(i + j * matrix.rows());
			}
		}
	}
	MatrixXd Finded = MatrixXd::Zero(1, v.size());
	int iterator = 0;
	for (int n : v) {
		Finded(0, iterator) = n;
		iterator++;
	}
	return Finded;
}

MatrixXd Non_stationary_noise_estimation::setValueOnSpecifiedIndexes(MatrixXd matrixToSet, MatrixXd Indexes)
{
	MatrixXd matrixWithSetValues = MatrixXd::Zero(Indexes.cols(), 1);
	for (int i = 0; i < Indexes.cols(); i++) {

		int index = Indexes(0, i);
		int b = index / matrixToSet.rows();
		int a = index - (b*matrixToSet.rows());
		matrixWithSetValues(i, 0) = matrixToSet(a, b);
	}
	return matrixWithSetValues;
}

void Non_stationary_noise_estimation::setValueOnSpecifiedIndexes(MatrixXd& matrixToSet, MatrixXd Indexes, double value)
{
	for (int i = 0; i < Indexes.cols(); i++) {
		int index = Indexes(0, i);
		int b = index / matrixToSet.rows();
		int a = index - (b*matrixToSet.rows());
		matrixToSet(a, b) = value;
	}
}

void Non_stationary_noise_estimation::setBesselValues(MatrixXd z, MatrixXd K, MatrixXd& M)
{
	for (int i = 0; i < K.cols(); i++) {

		int index = K(0, i);
		int b = index / z.rows();
		int a = index - (b*z.rows());
		double x = cyl_bessel_i(1, z(a, b));
		double y = cyl_bessel_i(0, z(a, b));
		M(a, b) = cyl_bessel_i(1, z(a, b)) / cyl_bessel_i(0, z(a, b));
	}
}

MatrixXd Non_stationary_noise_estimation::bessel(MatrixXd matrix)
{
	MatrixXd cont = (matrix.array() < 1.5).cast<double>().array();
	MatrixXd z8 = 8 * matrix;
	MatrixXd z8Power2 = pow(z8.array(), 2);
	MatrixXd z8Power3 = pow(z8.array(), 3);

	MatrixXd Md = (1 + (1 / z8.array())) + (4.5 / z8Power2.array()) + (37.5 / z8Power3.array());
	MatrixXd Mn = (1 - (3 / z8.array())) - (7.5 / z8Power2.array()) - (52.5 / z8Power3.array());
	MatrixXd M = (Mn.array() / Md.array()).unaryExpr([](double v) { return std::isnan(v) ? 0.0 : v; });

	if (getSum(cont)) {
		MatrixXd K = getFinded(cont, 1);
		setBesselValues(matrix, K, M);
	}

	MatrixXd K = getFinded(matrix, 0);
	setValueOnSpecifiedIndexes(M, K, 0);

	return M;
}

MatrixXd Non_stationary_noise_estimation::getMaxValue(MatrixXd matrix, double tresh) {
	if (tresh == 0)
	{
		return matrix.unaryExpr([](double v) { return v < 0 ? 0 : v; });
	}
	else
	{
		return matrix.unaryExpr([](double v) { return v < 0.01 ? 0.01 : v; });
	}
}

MatrixXd Non_stationary_noise_estimation::filter2(MatrixXd matrix, MatrixXd window)
{
	int imageRows = matrix.rows();
	int imageCols = matrix.cols();
	int windowRows = window.rows();
	int windowCols = window.cols();
	MatrixXd padding(MatrixXd::Zero(imageRows + windowRows - 1, imageCols + windowCols - 1));
	padding.block(windowRows / 2, windowCols / 2, imageRows, imageCols) << matrix;
	MatrixXd outputPlusPadding(imageRows + windowRows - 1, imageCols + windowCols - 1);
	double conv = 0;
	int x, y;

	int imagePaddingRows = padding.rows();
	int imagePaddingCols = padding.cols();

	for (int i = 0; i < imagePaddingRows; i++) {
		for (int j = 0; j < imagePaddingCols; j++) {
			x = i;
			y = j;
			for (int k = 0; k < windowRows; k++) {
				for (int l = 0; l < windowCols; l++) {
					if (x < imagePaddingRows && y < imagePaddingCols) {
						conv += window(k, l) * padding(x, y);
					}
					y++;
				}
				x++;
				y = j;
			}
			outputPlusPadding(i, j) = conv;
			conv = 0;
		}
	}
	return outputPlusPadding.block(0, 0, imageRows, imageCols);
}

MatrixXd Non_stationary_noise_estimation::getSNR(int window, MatrixXd matrix) {
	MatrixXd ones = MatrixXd::Ones(window, window);
	MatrixXd matrixPow2 = pow(matrix.array(), 2);
	MatrixXd matrixPow4 = pow(matrix.array(), 4);
	MatrixXd filter = filter2(matrixPow2, ones) / (window * window);
	MatrixXd filterPow2 = pow(filter.array(), 2);
	MatrixXd A = 2 * filterPow2 - filter2(matrixPow4, ones) / (window * window);
	MatrixXd ak = sqrt(sqrt(getMaxValue(A, 0).array()));
	MatrixXd akPow2 = pow(ak.array(), 2);
	MatrixXd sigma = 0.5*getMaxValue(filter - akPow2, 0.01);

	for (int i = 0;i < 9;i++) {
		MatrixXd AM = ak.array()*matrix.array();
		MatrixXd aksigma = AM.array() / sigma.array();
		MatrixXd B = bessel(aksigma);
		ak = getMaxValue(filter2(B.array()*matrix.array(), ones) / (window * window), 0);
		MatrixXd ak2 = pow(ak.array(), 2);
		sigma = getMaxValue(0.5*filter - (ak2 / 2), 0.01);
	}
	MatrixXd sigmaSqrt = sqrt(sigma.array());
	MatrixXd SNR = ak.array() / sigmaSqrt.array();
	return SNR;
}

MatrixXd Non_stationary_noise_estimation::absoluteValue(MatrixXd matrix) {
	return matrix.cwiseAbs();
}

MatrixXd Non_stationary_noise_estimation::logCalculate(MatrixXd matrix) {

	for (int i = 0; i < matrix.rows();i++) {
		for (int j = 0; j < matrix.cols(); j++) {
			if (matrix(i, j) == 0) {
				matrix(i, j) = 0.001;
			}
		}
	}
	return matrix.array().log();
}

MatrixXd Non_stationary_noise_estimation::expCalculate(MatrixXd matrix) {
	return matrix.array().exp();
}

MatrixXd Non_stationary_noise_estimation::noiseEstimation(MatrixXd matrix) {
	return ((matrix * 2) / sqrt(2))*exp(e / 2);
}

MatrixXd Non_stationary_noise_estimation::gaussianKernel(MatrixXd K, MatrixXd image, double sig) {
	MatrixXd kernel = MatrixXd::Zero(image.rows(), image.cols());
	double sigma = 2 * sig;
	int column = 2 * image.cols();
	int row = 2 * image.rows();
	double half = row / 2;
	for (int x = 0; x < row; ++x)
		for (int y = 0; y < column; ++y) {
			K(x, y) = exp(-0.5 * (pow((x - half) / sigma, 2.0) + pow((y - half) / sigma, 2.0)))
				/ (2 * pi * sigma * sigma);
		}

	double maximum = K.maxCoeff();
	K = K / maximum;

	for (int x = image.rows(); x < row; x++)
	{
		for (int y = image.cols(); y < column; y++) {
			kernel(x - image.rows(), y - image.rows()) = K(x, y);
		}
	}

	return kernel;
}

MatrixXd Non_stationary_noise_estimation::dct(MatrixXd log) {

	int m = log.rows();
	int n = log.cols();
	std::vector<double> a(m*n);
	int count = 1;

	for (int i = 0; i<m;i++) {
		for (int j = 0; j<n;j++) {
			a[i*n + j] = log(i, j);
			count++;
		}
	}
	std::vector<double> b(m*n);
	fftw_plan plan = fftw_plan_r2r_2d(n, m, &a[0], &b[0], FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE);
	fftw_execute(plan);

	MatrixXd K = MatrixXd::Zero(m, n);
	for (int i = 0; i<m;i++)
		for (int j = 0; j<n;j++)
			K(i, j) = b[i*n + j];

	return K;
}

MatrixXd Non_stationary_noise_estimation::idct(MatrixXd log) {

	int m = log.rows();
	int n = log.cols();
	std::vector<double> a(m*n);
	int count = 1;

	for (int i = 0; i<m;i++) {
		for (int j = 0; j<n;j++) {
			a[i*n + j] = log(i, j);
			count++;
		}
	}

	std::vector<double> b(m*n);
	fftw_plan plan = fftw_plan_r2r_2d(n, m, &a[0], &b[0], FFTW_REDFT01, FFTW_REDFT01, FFTW_PATIENT);
	fftw_execute(plan);

	double f = sqrt(1 / 2 / (m*n));
	for (int i = 0, f = (m*n) << 1;i < (m*n);++i) {
		b[i] /= f * 2;
	}

	MatrixXd K = MatrixXd::Zero(m, n);
	for (int i = 0; i<m;i++)
		for (int j = 0; j<n;j++)
			K(i, j) = b[i*n + j];

	return K;
}

MatrixXd Non_stationary_noise_estimation::riceCorrection(MatrixXd SNR) {

	MatrixXd F = (-0.289549906258443)*pow(SNR.array(), 0) + (-0.038892257560633)*pow(SNR.array(), 1) + (0.409867108141953)*pow(SNR.array(), 2)
		+ (-0.355237628488567)*pow(SNR.array(), 3) + (0.149328280945610)*pow(SNR.array(), 4) + (-0.035786111794209)*pow(SNR.array(), 5)
		+ (0.004979528938591)* pow(SNR.array(), 6) + (-0.0003747563744775917)*pow(SNR.array(), 7) + (0.00001180202291400923)*pow(SNR.array(), 8);
	
	F = F.array() * (SNR.array() <= 7).cast<double>().array();

	return F;
}

void Non_stationary_noise_estimation::writeToCSVfile(string name, MatrixXd matrix) {
	ofstream file(name.c_str());

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

void Non_stationary_noise_estimation::setEstimators(MatrixXd reconstructedImage, int i, int j, bool isDiffusion)
{
	MatrixXd mean = filter2(reconstructedImage, MatrixXd::Ones(5, 5)) / (5 * 5);
	MatrixXd reconstructedWithoutMean = reconstructedImage - mean;
	MatrixXd abs = absoluteValue(reconstructedWithoutMean);
	MatrixXd log = logCalculate(abs);
	MatrixXd kernel = MatrixXd::Zero(2*reconstructedImage.rows(), 2 * reconstructedImage.cols());
	MatrixXd filtered = gaussianKernel(kernel, log, 3.4);
	MatrixXd dctValue = dct(log);
	MatrixXd lpfF = dctValue.array()*filtered.array();
	MatrixXd lpf = idct(lpfF);
	MatrixXd exp =expCalculate(lpf);
	MatrixXd estimator = noiseEstimation(exp);
	MatrixXd SNR = getSNR(3, reconstructedImage);
	MatrixXd correctSNR = riceCorrection(SNR);
	MatrixXd LPF1 = lpf - correctSNR;
	MatrixXd filtered2 = gaussianKernel(kernel, log, 3.4 + 2);
	MatrixXd dctValue2 = dct(LPF1);
	MatrixXd lpfF2 = dctValue2.array()*filtered2.array();
	MatrixXd lpf2 = idct(lpfF2);
	MatrixXd exp2=expCalculate(lpf2);
	MatrixXd estimator2 = noiseEstimation(exp2);
	if (isDiffusion)
	{
		gradientEstimatorGauss.push_back(estimator);
		gradientEstimatorRice.push_back(estimator2);
	}
	else
	{
		GaussEstimator3D.push_back(estimator);
		RiceEstimator3D.push_back(estimator2);
	}
}
