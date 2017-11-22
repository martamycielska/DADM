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
#include "QVTKOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DADM
{
public:
    QWidget *centralWidget;
    QPushButton *reconstructionPushButton;
    QPushButton *visualizationBtn;
    QVTKOpenGLWidget *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DADM)
    {
        if (DADM->objectName().isEmpty())
            DADM->setObjectName(QStringLiteral("DADM"));
        DADM->resize(613, 402);
        centralWidget = new QWidget(DADM);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        reconstructionPushButton = new QPushButton(centralWidget);
        reconstructionPushButton->setObjectName(QStringLiteral("reconstructionPushButton"));
        reconstructionPushButton->setGeometry(QRect(30, 70, 181, 51));
        visualizationBtn = new QPushButton(centralWidget);
        visualizationBtn->setObjectName(QStringLiteral("visualizationBtn"));
        visualizationBtn->setGeometry(QRect(30, 150, 181, 51));
        widget = new QVTKOpenGLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(250, 30, 341, 291));
        DADM->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DADM);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 613, 22));
        DADM->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DADM);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DADM->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DADM);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DADM->setStatusBar(statusBar);

        retranslateUi(DADM);

        QMetaObject::connectSlotsByName(DADM);
    } // setupUi

    void retranslateUi(QMainWindow *DADM)
    {
        DADM->setWindowTitle(QApplication::translate("DADM", "DADM", Q_NULLPTR));
        reconstructionPushButton->setText(QApplication::translate("DADM", "MRI Reconstruction", Q_NULLPTR));
        visualizationBtn->setText(QApplication::translate("DADM", "Visualization 3D", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DADM: public Ui_DADM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DADM_H
