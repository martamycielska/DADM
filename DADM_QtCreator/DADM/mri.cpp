
#include "mri.h"
#include <QThread>
#include <QDebug>

MRI::MRI()
{
}

void MRI::MRI_recognition() {
    QThread::msleep(500);
    qDebug() << "MRI recognition done";
}

void MRI::intensity_inhomogenity_correction() {
    QThread::msleep(500);
    qDebug() << "Intensity nhomogenity correction done";
}

void MRI::non_stationary_noise_estimation() {
    QThread::msleep(500);
    qDebug() << "Non stationary noise estimation done";
}

void MRI::non_stationary_noise_filtering_1() {
    QThread::msleep(500);
    qDebug() << "Non stationary noise filtering #1 done";
}

void MRI::non_stationary_noise_filtering_2() {

}

void MRI::streamline_tractography() {

}

void MRI::skull_stripping() {

}

void MRI::segmentation() {

}

void MRI::upsampling() {

}

void MRI::brain_3d() {

}

void MRI::oblique_imaging() {

}
