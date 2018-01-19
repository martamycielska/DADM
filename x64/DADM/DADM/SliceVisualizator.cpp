#include <SliceVisualizator.h>
#include <Globals.h>

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


SliceVisualizator::SliceVisualizator(RenderWindow renderWnd)
{
	this->renderWnd = renderWnd;
	this->inputData = Global::structuralData;
	this->x = inputData[0].rows();
	this->y = inputData[0].cols();
	this->z = inputData.size();
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
				pixel[0] = Global::structuralData[z](x, y);
			}

	imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle = vtkSmartPointer<myVtkInteractorStyleImage>::New();
	myInteractorStyle->SetImageViewer(imageViewer);
	imageViewer->SetupInteractor(renderWindowInteractor);
	renderWindowInteractor->SetInteractorStyle(myInteractorStyle);

	imageViewer->SetInputData(imageData);
	imageViewer->SetRenderWindow(renderWnd);
	imageViewer->SetSliceOrientationToXY();
	imageViewer->SetSlice(0);
	imageViewer->Render();
	renderWindowInteractor->Start();
}

Viewer SliceVisualizator::getImageViewer()
{
	return imageViewer;
}

SliceVisualizator::~SliceVisualizator()
{
	//destruktor
}