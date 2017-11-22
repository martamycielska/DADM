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

QT_BEGIN_NAMESPACE

class Ui_Visualization3D
{
public:
    QWidget *centralwidget;
    QPushButton *visualizeBtn;
    QLabel *label;
    QSlider *horizontalSlider;
    QLabel *processDescLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Visualization3D)
    {
        if (Visualization3D->objectName().isEmpty())
            Visualization3D->setObjectName(QStringLiteral("Visualization3D"));
        Visualization3D->resize(520, 346);
        centralwidget = new QWidget(Visualization3D);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        visualizeBtn = new QPushButton(centralwidget);
        visualizeBtn->setObjectName(QStringLiteral("visualizeBtn"));
        visualizeBtn->setGeometry(QRect(10, 80, 151, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 10, 151, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 140, 151, 21));
        horizontalSlider->setMinimum(10);
        horizontalSlider->setMaximum(500);
        horizontalSlider->setValue(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        processDescLabel = new QLabel(centralwidget);
        processDescLabel->setObjectName(QStringLiteral("processDescLabel"));
        processDescLabel->setGeometry(QRect(170, 280, 221, 21));
        QFont font1;
        font1.setPointSize(10);
        processDescLabel->setFont(font1);
        processDescLabel->setAlignment(Qt::AlignCenter);
        Visualization3D->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Visualization3D);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 520, 21));
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
