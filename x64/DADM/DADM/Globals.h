#pragma once
#include <Eigen/Dense>
//#include <unsupported\Eigen\CXX11\Tensor>
#include "MRI_Module.h"
#include "Segmentation.h"
#include "Reconstruction.h"
#include "dadm.h"

namespace Global {
	extern int current_slice;
	extern FilteringType ftype;
	extern DataType dtype;
	extern double b_value;
	extern MatrixXd gradients;
	extern Data3D dataFrontal;
	extern Data3D dataSaggital;
	extern Data3D dataHorizontal;
	extern Data3D temporaryDataFrontal;
	extern Data3D temporaryDataSaggital;
	extern Data3D temporaryDataHorizontal;
	extern Data3D structuralData;
	extern Data3DRaw structuralRawData;
	extern Data3DRaw structuralSensitivityMaps;
	extern double L;
	extern double r;
	extern Data4DRaw diffusionRawData;
	extern Data3DRaw diffusionSensitivityMaps;
	extern Data4D diffusionData4D;
	extern Data3D diffusionData3D;
	extern SegmentationData segmentationData;
	extern Data3D FA;
	extern Data3D MD;
	extern Data3D RA;
	extern Data3D VR;
}