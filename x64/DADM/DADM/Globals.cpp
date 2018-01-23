#include "Globals.h"

namespace Global {
	extern int current_slice = 0;
	extern FilteringType ftype = LMMSE;
	extern DataType dtype = STRUCTURAL_DATA;
	extern double b_value = 0;
	extern MatrixXd gradients = MatrixXd(0,0);
	extern Data3D structuralData = Data3D(0);
	extern Data3D dataFrontal = Data3D(0);
	extern Data3D dataSaggital = Data3D(0);
	extern Data3D dataHorizontal = Data3D(0);
	extern Data3D temporaryDataFrontal = Data3D(0);
	extern Data3D temporaryDataSaggital = Data3D(0);
	extern Data3D temporaryDataHorizontal = Data3D(0);
	extern Data4DRaw structuralRawData = Data4DRaw(0);
	extern Data3DRaw structuralSensitivityMaps = Data3DRaw(0);
	extern double L = 0;
	extern double r = 0;
	extern Data5DRaw diffusionRawData = Data5DRaw(0);
	extern Data3DRaw diffusionSensitivityMaps = Data3DRaw(0);
	extern Data4D diffusionData4D = Data4D(0);
	extern Data3D diffusionData3D = Data3D(0);
	extern SegmentationData segmentationData = { {"white_matter", Data3D(0)}, { "gray_matter", Data3D(0) }, { "cerebrospinal_fluid", Data3D(0) } };
	extern Data4D FA = Data4D(0);
	extern Data3D MD = Data3D(0);
	extern Data3D RA = Data3D(0);
	extern Data3D VR = Data3D(0);
}