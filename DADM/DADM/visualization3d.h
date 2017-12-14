#ifndef VISUALIZATION3D_H
#define VISUALIZATION3D_H
#include <QMainWindow>
#include <QThread>
#include <vtkImplicitPlaneWidget2.h>

#include "Brain_3D.h"

namespace Ui {
    class Visualization3D;
}

class VisualizationWorker : public QThread
{
	Q_OBJECT

public:
	VisualizationWorker(Brain_3D*);
	void run();

signals:
	void ModelCreationDone();
	void CuttingPlaneDone();

private:
	Brain_3D *brain_3D;
};

class Visualization3D : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Visualization3D(QWidget *parent = 0);

    private:
        Ui::Visualization3D *ui;
        QString processDescString;
		VisualizationWorker *worker;
		Brain_3D *brain_3D;
		int threshold;
		int shrinkingFactor;
		int xspace;
		int yspace;
		int zspace;
		bool visualizationDone;
		void InitValue();
		void InitUI();
		void SetConnections();
		void UpdateProcessStateText(QString text);

    private slots:
        void Brain3D();
		void AcceptThreshold();
		void SliderValueChanged(int);
	    void ShrinkSliderValueChanged(int);
		void AddRendererAndPlaneWidget();
};

#endif // VISUALIZATION3D_H
