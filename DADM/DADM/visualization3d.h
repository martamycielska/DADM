#ifndef VISUALIZATION3D_H
#define VISUALIZATION3D_H
#include <QMainWindow>
#include <QThread>

#include "vtkSmartPointer.h"
#include "vtkRenderer.h"

typedef vtkSmartPointer<vtkRenderer> Renderer;

namespace Ui {
    class Visualization3D;
}

class VisualizationWorker : public QThread
{
	Q_OBJECT

public:
	VisualizationWorker(QString);
	void run();

signals:
	void initializationDone(Renderer);

private:
	QString path;
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

    private slots:
        void brain3D();
		void sliderValueChanged(int);
		void addRenderer(Renderer);
};

#endif // VISUALIZATION3D_H
