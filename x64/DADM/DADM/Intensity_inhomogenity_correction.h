#pragma once
#include "Diffusion_Structural_Module.h"

class Intensity_inhomogenity_correction:
	public Diffusion_Structural_Module
{
public:
	Intensity_inhomogenity_correction(Data3D);
	Intensity_inhomogenity_correction(Data4D);
	~Intensity_inhomogenity_correction() {};

private:
	virtual void StructuralDataAlgorithm();
	virtual void DiffusionDataAlgorithm();
	Data3D inputData;			//dane w formacie data3D
	void SetDataSize();			//zwraca rozmiary danych
	void importTest3D();		//wczytanie danych testowych z pliku .mat
	void writeToCSVfile(std::string name, MatrixXd matrix);	//zapis danych do pliku csv
	Eigen::MatrixXd selectRandomPoints(Eigen::MatrixXd &image, int n);	//wybranie losowych punktów z obrazu
	void createFilter();		//tworzy macierz 5x5 parametrówfiltru Gaussa
	Eigen::MatrixXd applyFilter(Eigen::MatrixXd image, double * gKernel);	//wymna¿a filtr przez obraz
	void LMOptimization();		//oblicza wspólczynniki dopasowanej powierzchni
	int xspace, yspace, zspace;	//rozmiary danych
	Eigen::MatrixXd image,sigma;//zmienne przechowuj¹ce obraz na poszczególnych etapach
};

