#pragma once
#include "MRI_Module.h"
class Reconstruction :
	public MRI_Module
{
public:
	Reconstruction(QString);
	~Reconstruction();

private:
	QString path;
};

