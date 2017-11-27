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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Visualization3D
{
public:
    QWidget *widget;
    QLabel *label;
    QVTKOpenGLWidget *qvtkWidget;
    QGroupBox *thresholdBox;
    QLabel *thresholdLabel;
    QTextEdit *thresholdTextEdit;
    QPushButton *acceptBtn;
    QSlider *horizontalSlider;
    QGroupBox *visualizationBox;
    QPushButton *visualizeBtn;
    QLabel *processDescLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Visualization3D)
    {
        if (Visualization3D->objectName().isEmpty())
            Visualization3D->setObjectName(QStringLiteral("Visualization3D"));
        Visualization3D->resize(1110, 664);
        widget = new QWidget(Visualization3D);
        widget->setObjectName(QStringLiteral("widget"));
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
        qvtkWidget = new QVTKOpenGLWidget(widget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(370, 110, 721, 501));
        thresholdBox = new QGroupBox(widget);
        thresholdBox->setObjectName(QStringLiteral("thresholdBox"));
        thresholdBox->setGeometry(QRect(40, 230, 291, 161));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        thresholdBox->setFont(font1);
        thresholdLabel = new QLabel(thresholdBox);
        thresholdLabel->setObjectName(QStringLiteral("thresholdLabel"));
        thresholdLabel->setGeometry(QRect(10, 40, 81, 16));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        thresholdLabel->setFont(font2);
        thresholdTextEdit = new QTextEdit(thresholdBox);
        thresholdTextEdit->setObjectName(QStringLiteral("thresholdTextEdit"));
        thresholdTextEdit->setGeometry(QRect(10, 60, 101, 31));
        acceptBtn = new QPushButton(thresholdBox);
        acceptBtn->setObjectName(QStringLiteral("acceptBtn"));
        acceptBtn->setGeometry(QRect(130, 60, 131, 31));
        horizontalSlider = new QSlider(thresholdBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 110, 251, 31));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(500);
        horizontalSlider->setSingleStep(10);
        horizontalSlider->setValue(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        visualizationBox = new QGroupBox(widget);
        visualizationBox->setObjectName(QStringLiteral("visualizationBox"));
        visualizationBox->setGeometry(QRect(40, 110, 291, 101));
        visualizationBox->setFont(font1);
        visualizeBtn = new QPushButton(visualizationBox);
        visualizeBtn->setObjectName(QStringLiteral("visualizeBtn"));
        visualizeBtn->setGeometry(QRect(50, 30, 171, 41));
        processDescLabel = new QLabel(widget);
        processDescLabel->setObjectName(QStringLiteral("processDescLabel"));
        processDescLabel->setGeometry(QRect(40, 450, 271, 91));
        QFont font3;
        font3.setPointSize(11);
        processDescLabel->setFont(font3);
        processDescLabel->setAlignment(Qt::AlignCenter);
        Visualization3D->setCentralWidget(widget);
        menubar = new QMenuBar(Visualization3D);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1110, 21));
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
        label->setText(QApplication::translate("Visualization3D", "Brain Visualization", Q_NULLPTR));
        thresholdBox->setTitle(QApplication::translate("Visualization3D", "Threshold", Q_NULLPTR));
        thresholdLabel->setText(QApplication::translate("Visualization3D", "Enter value:", Q_NULLPTR));
        acceptBtn->setText(QApplication::translate("Visualization3D", "Accept", Q_NULLPTR));
        visualizationBox->setTitle(QApplication::translate("Visualization3D", "Visualization", Q_NULLPTR));
        visualizeBtn->setText(QApplication::translate("Visualization3D", "Visualize 3D", Q_NULLPTR));
        processDescLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Visualization3D: public Ui_Visualization3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALIZATION3D_H
