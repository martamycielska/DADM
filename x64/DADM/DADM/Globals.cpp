#include "Globals.h"

namespace Global {
	extern int current_slice = 0;
	extern FilteringType ftype = LMMSE;
	extern DataType dtype = STRUCTURAL_DATA;
	extern double b_value = 0;
	extern MatrixXd gradients = MatrixXd(0,0);
	extern Data3D structuralData = Data3D(0);
	extern Data3D dataXY = Data3D(0);
	extern Data3D dataYZ = Data3D(0);
	extern Data3D dataXZ = Data3D(0);
	extern Data3D temporaryDataXY = Data3D(0);
	extern Data3D temporaryDataYZ = Data3D(0);
	extern Data3D temporaryDataXZ = Data3D(0);
	extern Data4DRaw structuralRawData = Data4DRaw(0);
	extern Data3DRaw structuralSensitivityMaps = Data3DRaw(0);
	extern double L = 0;
	extern double r = 0;
	extern Data5DRaw diffusionRawData = Data5DRaw(0);
	extern Data3DRaw diffusionSensitivityMaps = Data3DRaw(0);
	extern Data4D diffusionData4D = Data4D(0);
	extern Data3D diffusionData3D = Data3D(0);
	extern SegmentationData segmentationData = { {"white_matter", Data3D(0)}, { "gray_matter", Data3D(0) }, { "cerebrospinal_fluid", Data3D(0) } };
	extern Data3D FA = Data3D(0);
	extern Data3D MD = Data3D(0);
	extern Data3D RA = Data3D(0);
	extern Data3D VR = Data3D(0);
}