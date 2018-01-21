#pragma once
#include "MRI_Module.h"
#include "itkVTKImageToImageFilter.h"
#include <itkImageToVTKImageFilter.h>
#include "itkConnectedThresholdImageFilter.h"
#include "itkImage.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>
#include "vtkVersion.h"
#include "vtkImageViewer.h"
#include "vtkImageMapper3D.h"

typedef std::map<std::string, Data3D> SegmentationData;

class Segmentation
	//:public MRI_Module<Data3D, SegmentationData>
{
public:
	Segmentation(itk::IndexValueType seed_X, itk::IndexValueType seed_Y, int lowThreshold, int uppThreshold);
	virtual void Start();
	~Segmentation();

private:
	Data3D inputData;
	Data3D outputImg;
	itk::IndexValueType seed_X; //white matter: 60, gray matter: 107
	itk::IndexValueType seed_Y; //white matter: 116, gray matter: 69
	int lowThreshold; //white matter: 150, gray matter: 180
	int uppThreshold; //white matter : 180, gray matter : 210
	int x;
	int y;
	int z;
	vtkSmartPointer<vtkImageData> imageData;
};