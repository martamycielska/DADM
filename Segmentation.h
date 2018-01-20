#pragma once
#include "MRI_Module.h"
#include "itkVTKImageToImageFilter.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkImage.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

typedef std::map<std::string, Data3D> SegmentationData;

class Segmentation
	//:
	//public MRI_Module<Data3D, SegmentationData>
{
	public:
		Segmentation(itk::IndexValueType seed_X, itk::IndexValueType seed_Y, int lowThreshold, int uppThreshold);
		virtual void Start();
		~Segmentation();

	private:
		Data3D inputData; 
		Data3D outputImg; 
		itk::IndexValueType seed_X;
		itk::IndexValueType seed_Y;
		int lowThreshold; 
		int uppThreshold;
		int x;
		int y;
		int z;
		vtkSmartPointer<vtkImageData> imageData;
		itk::SmartPointer<itk::Image<float, 3U>> outImage;
};