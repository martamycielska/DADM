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
#include <QtWidgets/QRadioButton>
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
    QPushButton *acceptBtn;
    QSlider *horizontalSlider;
    QTextEdit *thresholdTextEdit;
    QGroupBox *visualizationBox;
    QPushButton *visualizeBtn;
    QGroupBox *planeGroupBox;
    QRadioButton *cutEnableRadioBtn;
    QGroupBox *processGroupBox;
    QLabel *processDescLabel;
    QGroupBox *shrinkDataGroupBox;
    QSlider *shrinkSlider;
    QLabel *shrinkingLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Visualization3D)
    {
        if (Visualization3D->objectName().isEmpty())
            Visualization3D->setObjectName(QStringLiteral("Visualization3D"));
        Visualization3D->resize(1110, 750);
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
        qvtkWidget->setGeometry(QRect(370, 80, 721, 591));
        thresholdBox = new QGroupBox(widget);
        thresholdBox->setObjectName(QStringLiteral("thresholdBox"));
        thresholdBox->setGeometry(QRect(40, 210, 291, 161));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        thresholdBox->setFont(font1);
        thresholdLabel = new QLabel(thresholdBox);
        thresholdLabel->setObjectName(QStringLiteral("thresholdLabel"));
        thresholdLabel->setGeometry(QRect(10, 40, 231, 16));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        thresholdLabel->setFont(font2);
        acceptBtn = new QPushButton(thresholdBox);
        acceptBtn->setObjectName(QStringLiteral("acceptBtn"));
        acceptBtn->setGeometry(QRect(120, 100, 141, 31));
        horizontalSlider = new QSlider(thresholdBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 60, 251, 31));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(255);
        horizontalSlider->setSingleStep(10);
        horizontalSlider->setValue(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        thresholdTextEdit = new QTextEdit(thresholdBox);
        thresholdTextEdit->setObjectName(QStringLiteral("thresholdTextEdit"));
        thresholdTextEdit->setEnabled(true);
        thresholdTextEdit->setGeometry(QRect(10, 100, 101, 31));
        thresholdTextEdit->setInputMethodHints(Qt::ImhNone);
        thresholdTextEdit->setFrameShape(QFrame::WinPanel);
        thresholdTextEdit->setFrameShadow(QFrame::Sunken);
        thresholdTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        thresholdTextEdit->setReadOnly(true);
        visualizationBox = new QGroupBox(widget);
        visualizationBox->setObjectName(QStringLiteral("visualizationBox"));
        visualizationBox->setGeometry(QRect(40, 90, 291, 101));
        visualizationBox->setFont(font1);
        visualizeBtn = new QPushButton(visualizationBox);
        visualizeBtn->setObjectName(QStringLiteral("visualizeBtn"));
        visualizeBtn->setGeometry(QRect(40, 30, 201, 51));
        planeGroupBox = new QGroupBox(widget);
        planeGroupBox->setObjectName(QStringLiteral("planeGroupBox"));
        planeGroupBox->setGeometry(QRect(40, 390, 291, 61));
        planeGroupBox->setFont(font1);
        cutEnableRadioBtn = new QRadioButton(planeGroupBox);
        cutEnableRadioBtn->setObjectName(QStringLiteral("cutEnableRadioBtn"));
        cutEnableRadioBtn->setGeometry(QRect(110, 30, 61, 16));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        cutEnableRadioBtn->setFont(font3);
        cutEnableRadioBtn->setIconSize(QSize(20, 20));
        cutEnableRadioBtn->setChecked(true);
        processGroupBox = new QGroupBox(widget);
        processGroupBox->setObjectName(QStringLiteral("processGroupBox"));
        processGroupBox->setGeometry(QRect(40, 580, 291, 91));
        processGroupBox->setFont(font1);
        processDescLabel = new QLabel(processGroupBox);
        processDescLabel->setObjectName(QStringLiteral("processDescLabel"));
        processDescLabel->setGeometry(QRect(10, 30, 271, 51));
        processDescLabel->setFont(font2);
        processDescLabel->setAlignment(Qt::AlignCenter);
        shrinkDataGroupBox = new QGroupBox(widget);
        shrinkDataGroupBox->setObjectName(QStringLiteral("shrinkDataGroupBox"));
        shrinkDataGroupBox->setGeometry(QRect(40, 470, 291, 91));
        shrinkDataGroupBox->setFont(font1);
        shrinkSlider = new QSlider(shrinkDataGroupBox);
        shrinkSlider->setObjectName(QStringLiteral("shrinkSlider"));
        shrinkSlider->setGeometry(QRect(10, 30, 251, 22));
        shrinkSlider->setMinimum(1);
        shrinkSlider->setMaximum(5);
        shrinkSlider->setOrientation(Qt::Horizontal);
        shrinkingLabel = new QLabel(shrinkDataGroupBox);
        shrinkingLabel->setObjectName(QStringLiteral("shrinkingLabel"));
        shrinkingLabel->setGeometry(QRect(10, 60, 251, 16));
        shrinkingLabel->setFont(font3);
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
        thresholdLabel->setText(QApplication::translate("Visualization3D", "Change threshold and accept:", Q_NULLPTR));
        acceptBtn->setText(QApplication::translate("Visualization3D", "Accept", Q_NULLPTR));
        visualizationBox->setTitle(QApplication::translate("Visualization3D", "Visualization", Q_NULLPTR));
        visualizeBtn->setText(QApplication::translate("Visualization3D", "Visualize 3D", Q_NULLPTR));
        planeGroupBox->setTitle(QApplication::translate("Visualization3D", "Cutting plane option", Q_NULLPTR));
        cutEnableRadioBtn->setText(QApplication::translate("Visualization3D", "Enable", Q_NULLPTR));
        processGroupBox->setTitle(QApplication::translate("Visualization3D", "Process state", Q_NULLPTR));
        processDescLabel->setText(QString());
        shrinkDataGroupBox->setTitle(QApplication::translate("Visualization3D", "Shrinking data", Q_NULLPTR));
        shrinkingLabel->setText(QApplication::translate("Visualization3D", "* Shrink data to increase efficiency", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Visualization3D: public Ui_Visualization3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALIZATION3D_H
