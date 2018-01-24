#pragma once
#include <Eigen/Dense>
//#include <unsupported\Eigen\CXX11\Tensor>
#include "MRI_Module.h"
#include "Segmentation.h"
#include "Reconstruction.h"
#include "helpermethods.h"

namespace Global {
	extern Biomarker biomarker;
	extern int current_slice;
	extern FilteringType ftype;
	extern DataType dtype;
	extern double b_value;
	extern MatrixXd gradients;
	extern Data3D dataXY;
	extern Data3D dataYZ;
	extern Data3D dataXZ;
	extern Data3D structuralData;
	extern Data4DRaw structuralRawData;
	extern Data3DRaw structuralSensitivityMaps;
	extern double L;
	extern double r;
	extern Data5DRaw diffusionRawData;
	extern Data3DRaw diffusionSensitivityMaps;
	extern Data4D diffusionData4D;
	extern Data3D diffusionData3D;
	extern SegmentationData segmentationData;
	extern Data4D FA;
	extern Data3D MD;
	extern Data3D RA;
	extern Data3D VR;
}