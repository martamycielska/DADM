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

class Ui_DADM
{
public:
    QWidget *centralWidget;
    QPushButton *reconstructionPushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DADM)
    {
        if (DADM->objectName().isEmpty())
            DADM->setObjectName(QStringLiteral("DADM"));
        DADM->resize(400, 300);
        centralWidget = new QWidget(DADM);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        reconstructionPushButton = new QPushButton(centralWidget);
        reconstructionPushButton->setObjectName(QStringLiteral("reconstructionPushButton"));
        reconstructionPushButton->setGeometry(QRect(20, 30, 111, 23));
        DADM->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DADM);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
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
    } // retranslateUi

};

namespace Ui {
    class DADM: public Ui_DADM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DADM_H
