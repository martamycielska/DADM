/********************************************************************************
** Form generated from reading UI file 'dadm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DADM_H
#define UI_DADM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DADMClass
{
public:
    QWidget *centralWidget;
    QPushButton *reconstructionPushButton;
    QPushButton *ObliqueImagingButton;
    QPushButton *visualizationBtn;
    QPushButton *UpsamplingButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DADMClass)
    {
        if (DADMClass->objectName().isEmpty())
            DADMClass->setObjectName(QStringLiteral("DADMClass"));
        DADMClass->resize(600, 400);
        centralWidget = new QWidget(DADMClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        reconstructionPushButton = new QPushButton(centralWidget);
        reconstructionPushButton->setObjectName(QStringLiteral("reconstructionPushButton"));
        reconstructionPushButton->setGeometry(QRect(200, 130, 171, 41));
        ObliqueImagingButton = new QPushButton(centralWidget);
        ObliqueImagingButton->setObjectName(QStringLiteral("ObliqueImagingButton"));
        ObliqueImagingButton->setGeometry(QRect(390, 230, 171, 41));
        visualizationBtn = new QPushButton(centralWidget);
        visualizationBtn->setObjectName(QStringLiteral("visualizationBtn"));
        visualizationBtn->setGeometry(QRect(200, 230, 171, 41));
        UpsamplingButton = new QPushButton(centralWidget);
        UpsamplingButton->setObjectName(QStringLiteral("UpsamplingButton"));
        UpsamplingButton->setGeometry(QRect(10, 230, 171, 41));
        DADMClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DADMClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        DADMClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DADMClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DADMClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DADMClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DADMClass->setStatusBar(statusBar);

        retranslateUi(DADMClass);

        QMetaObject::connectSlotsByName(DADMClass);
    } // setupUi

    void retranslateUi(QMainWindow *DADMClass)
    {
        DADMClass->setWindowTitle(QApplication::translate("DADMClass", "DADM", Q_NULLPTR));
        reconstructionPushButton->setText(QApplication::translate("DADMClass", "Reconstruction", Q_NULLPTR));
        ObliqueImagingButton->setText(QApplication::translate("DADMClass", "Oblique Imaging", Q_NULLPTR));
        visualizationBtn->setText(QApplication::translate("DADMClass", "Visualization", Q_NULLPTR));
        UpsamplingButton->setText(QApplication::translate("DADMClass", "Upsampling", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DADMClass: public Ui_DADMClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DADM_H
