#pragma once
#include <Eigen/Dense>
//#include <unsupported\Eigen\CXX11\Tensor>
#include "MRI_Module.h"
#include "Segmentation.h"

extern Data3D structuralData;
extern Data4D diffusionData4D;
extern Data3D diffusionData3D;
extern SegmentationData segmentationData;
extern MatrixXd FA;
extern MatrixXd MD;
extern MatrixXd RA;
extern MatrixXd VR;

