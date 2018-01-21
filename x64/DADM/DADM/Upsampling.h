#pragma once
#include "MRI_Module.h"
#include "Globals.h"
class Upsampling:
	public MRI_Module<MatrixXd, MatrixXd>
{
public:
	Upsampling(MatrixXd, int, int);
	virtual void Start();
	~Upsampling();
	
private:
	void Inicjalizacja(MatrixXd);
	int height;
	int width;
	


};
