#include <SliceVisualizator.h>
#include <vtkImageCast.h>

class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
	static myVtkInteractorStyleImage* New();
	vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);

protected:
	vtkImageViewer2* _ImageViewer;
	vtkTextMapper* _StatusMapper;
	int _Slice;
	int _MinSlice;
	int _MaxSlice;

public:
	void SetImageViewer(vtkImageViewer2* imageViewer) {
		_ImageViewer = imageViewer;
		_MinSlice = imageViewer->GetSliceMin();
		_MaxSlice = imageViewer->GetSliceMax();
		_Slice = _MinSlice;
	}

protected:
	void MoveSliceForward() {
		if (_Slice < _MaxSlice) {
			_Slice += 1;
			_ImageViewer->SetSlice(_Slice);
			_ImageViewer->Render();
		}
	}

	void MoveSliceBackward() {
		if (_Slice > _MinSlice) {
			_Slice -= 1;
			_ImageViewer->SetSlice(_Slice);
			_ImageViewer->Render();
		}
	}

	virtual void OnKeyDown() {
		std::string key = this->GetInteractor()->GetKeySym();
		if (key.compare("Up") == 0) {
			MoveSliceForward();
		}
		else if (key.compare("Down") == 0) {
			MoveSliceBackward();
		}
		vtkInteractorStyleImage::OnKeyDown();
	}

	virtual void OnMouseWheelForward() {
		MoveSliceForward();
	}

	virtual void OnMouseWheelBackward() {
		if (_Slice > _MinSlice) {
			MoveSliceBackward();
		}
	}
};

vtkStandardNewMacro(myVtkInteractorStyleImage);

SliceVisualizator::SliceVisualizator(RenderWindow renderWnd, SlicePlane plane, Data3D visData)
{
	this->plane = plane;
	this->inputData = visData;
	this->x = inputData[0].rows();
	this->y = inputData[0].cols();
	this->z = inputData.size();

	if (plane == SlicePlane::XY)
		this->renderWndXY = renderWnd;
	if (plane == SlicePlane::YZ)
		this->renderWndYZ = renderWnd;
	if (plane == SlicePlane::XZ)
		this->renderWndXZ = renderWnd;
}

void SliceVisualizator::visualize()
{
	imageData = vtkSmartPointer<vtkImageData>::New();
	imageData->SetDimensions(x, y, z);
	imageData->AllocateScalars(VTK_DOUBLE, 1);
	int* dims = imageData->GetDimensions();

	for (int z = 0; z < dims[2]; z++)
		for (int y = 0; y < dims[1]; y++)
			for (int x = 0; x < dims[0]; x++)
			{
				double* pixel = static_cast<double*>(imageData->GetScalarPointer(x, y, z));
				pixel[0] = inputData[z](x, y);
			}

	if (plane == SlicePlane::XY) 
	{
		imageViewerXY = vtkSmartPointer<vtkImageViewer2>::New();
		renderWindowInteractorXY = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyleXY = vtkSmartPointer<myVtkInteractorStyleImage>::New();
		myInteractorStyleXY->SetImageViewer(imageViewerXY);
		imageViewerXY->SetupInteractor(renderWindowInteractorXY);
		renderWindowInteractorXY->SetInteractorStyle(myInteractorStyleXY);

		imageViewerXY->SetInputData(imageData);
		imageViewerXY->SetRenderWindow(renderWndXY);
		imageViewerXY->SetSliceOrientationToXY();
		imageViewerXY->SetSlice((int)(imageViewerXY->GetSliceMax()/2));
		imageViewerXY->Render();
		qDebug() << "Skonczona wizualizacja XY";
	}

	if (plane == SlicePlane::YZ)
	{
		imageViewerYZ= vtkSmartPointer<vtkImageViewer2>::New();
		renderWindowInteractorYZ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyleYZ = vtkSmartPointer<myVtkInteractorStyleImage>::New();
		myInteractorStyleYZ->SetImageViewer(imageViewerYZ);
		imageViewerYZ->SetupInteractor(renderWindowInteractorYZ);
		renderWindowInteractorYZ->SetInteractorStyle(myInteractorStyleYZ);

		imageViewerYZ->SetInputData(imageData);
		imageViewerYZ->SetRenderWindow(renderWndYZ);
		//imageViewerYZ->SetSliceOrientationToYZ();
		imageViewerYZ->SetSlice((int)(imageViewerYZ->GetSliceMax() / 2));
		imageViewerYZ->Render();

		qDebug() << "Skonczona wizualizacja YZ";
	}

	if (plane == SlicePlane::XZ)
	{
		imageViewerXZ = vtkSmartPointer<vtkImageViewer2>::New();
		renderWindowInteractorXZ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyleXZ = vtkSmartPointer<myVtkInteractorStyleImage>::New();
		myInteractorStyleXZ->SetImageViewer(imageViewerXZ);
		imageViewerXZ->SetupInteractor(renderWindowInteractorXZ);
		renderWindowInteractorXZ->SetInteractorStyle(myInteractorStyleXZ);

		imageViewerXZ->SetInputData(imageData);
		imageViewerXZ->SetRenderWindow(renderWndXZ);
		//imageViewerXZ->SetSliceOrientationToXZ();
		imageViewerXZ->SetSlice((int)(imageViewerXZ->GetSliceMax() / 2));
		imageViewerXZ->Render();

		qDebug() << "Skonczona wizualizacja XZ";
	}
}

Viewer SliceVisualizator::getImageViewerXY()
{
	return imageViewerXY;
}

Viewer SliceVisualizator::getImageViewerYZ()
{
	return imageViewerYZ;
}

Viewer SliceVisualizator::getImageViewerXZ()
{
	return imageViewerXZ;
}

SliceVisualizator::~SliceVisualizator()
{
	//destruktor
}