#pragma once
#include "MRI_Module.h"
class Upsampling:
	public MRI_Module<MatrixXd, MatrixXd>
{
public:
	Upsampling(MatrixXd, int, int);
	virtual void Start();
	~Upsampling();

private:
	int height;
	int width;
	int Rozmiar_uz();
};

