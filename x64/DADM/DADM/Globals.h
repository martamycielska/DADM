#pragma once
#include <Eigen/Dense>
//#include <unsupported\Eigen\CXX11\Tensor>
#include "MRI_Module.h"
#include "Segmentation.h"
#include "Reconstruction.h"

extern Data3D structuralData;
extern Data3DRaw structuralRawData;
extern Data3DRaw structuralSensitivityMaps;
extern int L;
extern int r;
extern Data4D diffusionData4D;
extern Data3D diffusionData3D;
extern SegmentationData segmentationData;
extern MatrixXd FA;
extern MatrixXd MD;
extern MatrixXd RA;
extern MatrixXd VR;

