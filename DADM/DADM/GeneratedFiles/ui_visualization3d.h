/********************************************************************************
** Form generated from reading UI file 'visualization3d.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALIZATION3D_H
#define UI_VISUALIZATION3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Visualization3D
{
public:
    QWidget *widget;
    QPushButton *visualizeBtn;
    QLabel *label;
    QLabel *processDescLabel;
    QSlider *horizontalSlider;
    QVTKOpenGLWidget *qvtkWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Visualization3D)
    {
        if (Visualization3D->objectName().isEmpty())
            Visualization3D->setObjectName(QStringLiteral("Visualization3D"));
        Visualization3D->resize(988, 642);
        widget = new QWidget(Visualization3D);
        widget->setObjectName(QStringLiteral("widget"));
        visualizeBtn = new QPushButton(widget);
        visualizeBtn->setObjectName(QStringLiteral("visualizeBtn"));
        visualizeBtn->setGeometry(QRect(40, 190, 191, 51));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(330, 10, 321, 51));
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);
        processDescLabel = new QLabel(widget);
        processDescLabel->setObjectName(QStringLiteral("processDescLabel"));
        processDescLabel->setGeometry(QRect(10, 450, 251, 71));
        QFont font1;
        font1.setPointSize(12);
        processDescLabel->setFont(font1);
        processDescLabel->setAlignment(Qt::AlignCenter);
        processDescLabel->setWordWrap(true);
        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(30, 270, 211, 31));
        horizontalSlider->setOrientation(Qt::Horizontal);
        qvtkWidget = new QVTKOpenGLWidget(widget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(280, 90, 691, 501));
        Visualization3D->setCentralWidget(widget);
        menubar = new QMenuBar(Visualization3D);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 988, 22));
        Visualization3D->setMenuBar(menubar);
        statusbar = new QStatusBar(Visualization3D);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Visualization3D->setStatusBar(statusbar);

        retranslateUi(Visualization3D);

        QMetaObject::connectSlotsByName(Visualization3D);
    } // setupUi

    void retranslateUi(QMainWindow *Visualization3D)
    {
        Visualization3D->setWindowTitle(QApplication::translate("Visualization3D", "MainWindow", Q_NULLPTR));
        visualizeBtn->setText(QApplication::translate("Visualization3D", "Visualize 3D", Q_NULLPTR));
        label->setText(QApplication::translate("Visualization3D", "Brain Visualization", Q_NULLPTR));
        processDescLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Visualization3D: public Ui_Visualization3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALIZATION3D_H
