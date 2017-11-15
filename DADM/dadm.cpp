#include "dadm.h"
#include "ui_dadm.h"
#include "mri.h"
#include <QMessageBox>

DADM::DADM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DADM)
{
    ui->setupUi(this);
    mri = new MRI();
    connect(ui->reconstructionPushButton, SIGNAL(clicked(bool)), this, SLOT(mri_reconstruct()));
}

void DADM::mri_reconstruct() {
    Worker *worker = new Worker(mri, RECONSTRUCTION);
    connect(worker, &Worker::resultReady, this, &DADM::onReconstructionFinished);
    connect(worker, &Worker::finished, worker, &QObject::deleteLater);
    worker->start();
    //mri->start_reconstruction();
}

void DADM::onReconstructionFinished(QString str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
}

DADM::~DADM()
{
    delete ui;
}

Worker::Worker(MRI *mri, process prc) : QThread(nullptr), mri(mri), prc(prc) {}

void Worker::run() {
    switch (prc) {
    case RECONSTRUCTION:
        mri->MRI_recognition();
        mri->intensity_inhomogenity_correction();
        mri->non_stationary_noise_estimation();
        mri->non_stationary_noise_filtering_1();
        mri->brain_3d();
        emit resultReady("Done");
        break;
    default:
        break;
    }
}
