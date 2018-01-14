#pragma once
#include "MRI_Module.h"
class Upsampling:
	public MRI_Module<Data3D, Data3D>
{
public:
	Upsampling(Data3D, int, int);
	virtual void Start();
	~Upsampling();

private:
	int height;
	int width;
	int Rozmiar_uz();
};

