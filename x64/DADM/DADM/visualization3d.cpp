#include "visualization3d.h"
#include "Globals.h"

#pragma region VISUALIZATION3D class

Visualization3D::Visualization3D(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Visualization3D)
{
	InitValue();
	SetConnections();
	InitUI();
}

#pragma region controls event
void Visualization3D::Brain3D() {

	#pragma region to delete
	// do usuniêcia, jeœli bêdzie gotowy ca³y strumieñ danych
	// nale¿y wtedy odpowiedni¹ strukturê przypisaæ do zmiennej "inputData"
	QUrl url = QFileDialog::getOpenFileUrl(this, "Open file", QUrl(""), "Mat file (*.mat) (*mat)");

	if (url.isEmpty())
		return;

	ReadMatFile(url.path());
	//inputData = Global::structuralData;
	#pragma endregion to delete

	if (inputData.size() == 0) {
		QMessageBox msgBox;
		msgBox.setText("Brak danych lub niepoprawny plik");
		msgBox.exec();
		return;
	}

	SetDataSize();
	visualizationDone = false;
	setCutOptionEnable = ui->cutEnableRadioBtn->isChecked();

	UpdateProcessStateText("The model 3D initializing ....\nPlease wait");
	brain_3D = new Brain_3D(inputData, xspace, yspace, zspace, threshold, shrinkingFactor);

	worker = new VisualizationWorker(brain_3D);
	connect(worker, &VisualizationWorker::ModelCreationDone, this, &Visualization3D::AddRendererAndPlaneWidget);
	connect(worker, &VisualizationWorker::finished, worker, &QObject::deleteLater);
	worker->start();
}

void Visualization3D::SliderValueChanged(int sliderValue) {
	ui->thresholdTextEdit->setText(QString::number(sliderValue));
}

void Visualization3D::CutEnableChanged(bool cutEnable) {
	if (visualizationDone) {
		if (cutEnable) {
			brain_3D->getMapper()->SetInputConnection(clipper->GetOutputPort());
			planeWidget->On();
		}
		else {
			brain_3D->getMapper()->SetInputConnection(brain_3D->getDecimate()->GetOutputPort());
			planeWidget->Off();
		}

		ui->qvtkWidget->GetRenderWindow()->Render();
	}
	else {
		if (cutEnable)
			setCutOptionEnable = true;
		else
			setCutOptionEnable = false;
	}
}

void Visualization3D::AcceptThreshold() {
	QString thresholdString = ui->thresholdTextEdit->toPlainText();
	float thresholdFloat = thresholdString.toFloat();
	threshold = thresholdFloat;

	if (visualizationDone == true) {
		UpdateProcessStateText("The model 3D rendering...\nPlease wait");

		QEventLoop loop;
		QTimer::singleShot(1000, &loop, SLOT(quit()));
		loop.exec();

		MarchingCubes mc = brain_3D->getMarchingCubes();
		mc->SetValue(0, thresholdFloat);
		brain_3D->setMarchingCubes(mc);
		brain_3D->setThreshold(threshold);
		ui->qvtkWidget->GetRenderWindow()->Render();

		UpdateProcessStateText("Rendering done");
	}
	else {
		UpdateProcessStateText("Threshold changing done");
	}
}
#pragma endregion controls event

#pragma region private methods
void Visualization3D::InitValue() {
	ui->setupUi(this);
	threshold = 134;
	shrinkingFactor = 1;
	visualizationDone = false;
	setCutOptionEnable = false;
}

void Visualization3D::SetDataSize() {
	xspace = inputData[0].rows();
	yspace = inputData[0].cols();
	zspace = inputData.size();
}

void Visualization3D::SetConnections() {
	connect(ui->visualizeBtn, SIGNAL(clicked(bool)), this, SLOT(Brain3D()));
	connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SliderValueChanged(int)));
	connect(ui->acceptBtn, SIGNAL(clicked(bool)), this, SLOT(AcceptThreshold()));
	connect(ui->cutEnableRadioBtn, SIGNAL(toggled(bool)), this, SLOT(CutEnableChanged(bool)));
}

void Visualization3D::InitUI() {
	ui->horizontalSlider->setValue(threshold);
	/*ui->shrinkSlider->setValue(shrinkingFactor);*/
	ui->thresholdTextEdit->setText(QString::number(ui->horizontalSlider->value()));
	ui->cutEnableRadioBtn->setChecked(false);
}

void Visualization3D::AddRendererAndPlaneWidget() {
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	ui->qvtkWidget->SetRenderWindow(renderWnd);
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(brain_3D->getData());

	//Create plane and set normal
	plane = vtkSmartPointer<vtkPlane>::New();
	plane->SetNormal(1, 0, 0);

	//Create object to clip data (set clip function)
	clipper = vtkSmartPointer<vtkClipPolyData>::New();
	clipper->SetClipFunction(plane);
	clipper->InsideOutOn();

	//Create instance of class (observer) and assign the plane
	myCallback = vtkSmartPointer<MyCallback>::New();
	myCallback->Plane = plane;

	//Create representation to vtkImplicitPlaneWidget2 widget
	rep = vtkSmartPointer<vtkImplicitPlaneRepresentation>::New();
	rep->SetPlaceFactor(1.0);
	rep->SetNormal(plane->GetNormal());
	rep->OutlineTranslationOff();
	rep->ScaleEnabledOff();
	rep->GetPlaneProperty()->SetOpacity(0.0);
	rep->GetSelectedPlaneProperty()->SetOpacity(0.2);

	//Create widget to interact with user and clip the model
	planeWidget = vtkSmartPointer<vtkImplicitPlaneWidget2>::New();
	planeWidget->SetInteractor(ui->qvtkWidget->GetInteractor());
	planeWidget->SetRepresentation(rep);
	planeWidget->AddObserver(vtkCommand::InteractionEvent, myCallback);

	if (setCutOptionEnable)
		planeWidget->On(); 

	//Set data to clip
	clipper->SetInputConnection(brain_3D->getDecimate()->GetOutputPort());

	if (setCutOptionEnable)
		brain_3D->getMapper()->SetInputConnection(clipper->GetOutputPort());
	else
		brain_3D->getMapper()->SetInputConnection(brain_3D->getDecimate()->GetOutputPort());

	plane->SetOrigin(xspace / 2., yspace / 2., zspace / 2.);
	plane->SetNormal(0, -1, 0);
	rep->SetNormal(plane->GetNormal());

	//Define bound size
	double bounds[6];
	bounds[0] = 0;
	bounds[1] = xspace;
	bounds[2] = 0;
	bounds[3] = yspace;
	bounds[4] = 0;
	bounds[5] = zspace;

	//Set properties of representation
	plane->SetNormal(1., 0., 0.);
	rep->PlaceWidget(bounds);
	rep->SetOrigin(plane->GetOrigin());
	rep->SetNormal(plane->GetNormal());

	ui->qvtkWidget->repaint();
	visualizationDone = true;
	UpdateProcessStateText("Brain visualization done");

	qDebug() << "Add renderer and plane widget";
}

void Visualization3D::UpdateProcessStateText(QString text) {
	ui->processDescLabel->setText(text);
}

void Visualization3D::ReadMatFile(QString path) {

	inputData = Data3D(0);
	QByteArray ba = path.remove(0, 1).toLatin1();
	const char *fileName = ba.data();
	mat_t *mat = Mat_Open(fileName, MAT_ACC_RDONLY);

	if (mat) {
		matvar_t *matVar = 0;
		matVar = Mat_VarRead(mat, (char*)"Brain2");
		//matVar = Mat_VarRead(mat, (char*)"imageMaskFull");      // po segmentacji
		//matVar = Mat_VarRead(mat, (char*)"d_out");                //afterSkullStripping
		//matVar = Mat_VarRead(mat, (char*)"imageMaskFull");      //segmentaction mask
		//matVar = Mat_VarRead(mat, (char*)"dataset_T2");         //T21
		//matVar = Mat_VarRead(mat, (char*)"dataset_T1_INU_20");  //T12
		//matVar = Mat_VarRead(mat, (char*)"dataset_T2_INU_20");  //T12
		//matVar = Mat_VarRead(mat, (char*)"dataset_T1");         //T11
		//matVar = Mat_VarRead(mat, (char*)"dataset_PD_INU_20");  //PD1
		//matVar = Mat_VarRead(mat, (char*)"dataset_PD");         //PD2
		

		if (matVar) {
			const double *xData = static_cast<const double*>(matVar->data);
			std::vector<MatrixXd> data;
			int val_num = 0;

			qDebug() << matVar->dims[0];
			qDebug() << matVar->dims[1];
			qDebug() << matVar->dims[2];

			for (int i = 0; i < matVar->dims[2]; i++) {
				MatrixXd m(matVar->dims[0], matVar->dims[1]);
				for (int j = 0; j < matVar->dims[1]; j++) {
					for (int k = 0; k < matVar->dims[0]; k++) {
						m(k, j) = xData[val_num];
						val_num++;
						if (val_num >= matVar->dims[0] * matVar->dims[1] * matVar->dims[2]) break;
					}
				}
				data.push_back(m);
			}

			inputData = data;
		}

		Mat_Close(mat);
	}
}
#pragma endregion private methods

#pragma endregion VISUALIZATION3D class

#pragma region WORKER class

VisualizationWorker::VisualizationWorker(Brain_3D *brain_3D) : brain_3D(brain_3D) {
	qRegisterMetaType<Renderer>("Renderer");
	qRegisterMetaType<MarchingCubes>("MarchingCubes");
	qRegisterMetaType<MarchingCubes>("Mapper");
	qRegisterMetaType<MarchingCubes>("Decimate");
}

void VisualizationWorker::run() {
	brain_3D->Start();
	emit ModelCreationDone();
}

#pragma endregion WORKER class