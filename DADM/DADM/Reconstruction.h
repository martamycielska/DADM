#pragma once
#include "MRI_Module.h"

class Reconstruction :
	public MRI_Module<float***>
{
public:
	Reconstruction(QString);
	~Reconstruction();
	virtual void start();
	virtual float*** getResult();

private:
	QString path;
	float*** image;;
};