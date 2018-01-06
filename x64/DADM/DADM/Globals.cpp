#include "Globals.h"

namespace Global {
	
	extern double b_value = 0;
	extern MatrixXd gradients = MatrixXd(0,0);
	extern Data3D structuralData = Data3D(0);
	extern Data3DRaw structuralRawData = Data3DRaw(0);
	extern Data3DRaw structuralSensitivityMaps = Data3DRaw(0);
	extern double L = 0;
	extern double r = 0;
	extern Data4DRaw diffusionRawData = Data4DRaw(0);
	extern Data4D diffusionData4D = Data4D(0);
	extern Data3D diffusionData3D = Data3D(0);
	extern SegmentationData segmentationData = { {"white_matter", Data3D(0)}, { "gray_matter", Data3D(0) }, { "cerebrospinal_fluid", Data3D(0) } };
	extern MatrixXd FA = MatrixXd(0, 0);
	extern MatrixXd MD = MatrixXd(0, 0);
	extern MatrixXd RA = MatrixXd(0, 0);
	extern MatrixXd VR = MatrixXd(0, 0);
}