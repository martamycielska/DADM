#pragma once
#include "qthread.h"
#include <Eigen\Dense>
#include <unsupported\Eigen\CXX11\Tensor>

using namespace Eigen;

//typedef Tensor<double, 3> Data3D;
//typedef Tensor<double, 4> Data4D;

typedef std::vector<MatrixXd> Data3D;
typedef std::vector<std::vector<MatrixXd>> Data4D;

template <class InputDataType, class OutputDataType>
class MRI_Module
{
public:
	MRI_Module() {};
	virtual void Start() = 0;
	virtual OutputDataType getData() { return outputData; };
	virtual ~MRI_Module() {};

protected:
	InputDataType inputData;
	OutputDataType outputData;
};

