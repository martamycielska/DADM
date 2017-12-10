#pragma once
#include "qthread.h"
#include <Eigen\Dense>
#include <unsupported\Eigen\CXX11\Tensor>

using namespace Eigen;

typedef Tensor<double, 3> Data3D;
typedef Tensor<double, 4> Data4D;

template <class T, class U>
class MRI_Module
{
public:
	MRI_Module() {};
	virtual void Start() = 0;
	virtual U getData() { return outputData; };
	virtual ~MRI_Module() {};

protected:
	T inputData;
	U outputData;
};

