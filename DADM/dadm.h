#ifndef DADM_H
#define DADM_H

#include <QMainWindow>
#include "mri.h"

namespace Ui {
class DADM;
}



class DADM : public QMainWindow
{
    Q_OBJECT

public:
    explicit DADM(QWidget *parent = 0);
    ~DADM();

private:
    Ui::DADM *ui;
    MRI *mri;

private slots:
    void mri_reconstruct();
    void onReconstructionFinished(QString str);
};



class Worker : public QThread
{
    Q_OBJECT

public:
    Worker(MRI *mri, process prc);
    void run();

signals:
    void resultReady(QString str);

private:
    MRI *mri;
    process prc;
};

#endif // DADM_H
