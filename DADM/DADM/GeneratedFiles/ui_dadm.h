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
    QPushButton *visualizationBtn;
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
        reconstructionPushButton->setGeometry(QRect(40, 50, 171, 41));
        visualizationBtn = new QPushButton(centralWidget);
        visualizationBtn->setObjectName(QStringLiteral("visualizationBtn"));
        visualizationBtn->setGeometry(QRect(40, 120, 171, 41));
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
        visualizationBtn->setText(QApplication::translate("DADMClass", "Visualization", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DADMClass: public Ui_DADMClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DADM_H
