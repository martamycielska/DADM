#pragma once
#include "MRI_Module.h"
class Upsampling:
	public MRI_Module<MatrixXd, MatrixXd>
{
public:
	Upsampling(MatrixXd);
	virtual void Start();
	~Upsampling();

private:
	int Rozmiar_uz();
};

