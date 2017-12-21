/********************************************************************************
** Form generated from reading UI file 'ObliqueImaging_GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBLIQUEIMAGING_GUI_H
#define UI_OBLIQUEIMAGING_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObliqueImaging_GUI
{
public:
    QLabel *label_2;
    QSlider *horizontalSliderOI_2;
    QTextEdit *AngleTextEdit_2;
    QGroupBox *groupBox;
    QOpenGLWidget *openGLWidget;
    QTextEdit *AngleTextEdit;
    QLabel *label;
    QPushButton *OIButton;
    QSlider *horizontalSliderOI;

    void setupUi(QWidget *ObliqueImaging_GUI)
    {
        if (ObliqueImaging_GUI->objectName().isEmpty())
            ObliqueImaging_GUI->setObjectName(QStringLiteral("ObliqueImaging_GUI"));
        ObliqueImaging_GUI->resize(800, 600);
        label_2 = new QLabel(ObliqueImaging_GUI);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 40, 321, 51));
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setScaledContents(false);
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setWordWrap(false);
        horizontalSliderOI_2 = new QSlider(ObliqueImaging_GUI);
        horizontalSliderOI_2->setObjectName(QStringLiteral("horizontalSliderOI_2"));
        horizontalSliderOI_2->setGeometry(QRect(180, 260, 121, 31));
        horizontalSliderOI_2->setMinimum(1);
        horizontalSliderOI_2->setMaximum(500);
        horizontalSliderOI_2->setSingleStep(10);
        horizontalSliderOI_2->setValue(100);
        horizontalSliderOI_2->setOrientation(Qt::Horizontal);
        AngleTextEdit_2 = new QTextEdit(ObliqueImaging_GUI);
        AngleTextEdit_2->setObjectName(QStringLiteral("AngleTextEdit_2"));
        AngleTextEdit_2->setGeometry(QRect(30, 260, 101, 21));
        groupBox = new QGroupBox(ObliqueImaging_GUI);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(370, 190, 351, 311));
        openGLWidget = new QOpenGLWidget(groupBox);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(20, 20, 311, 271));
        AngleTextEdit = new QTextEdit(ObliqueImaging_GUI);
        AngleTextEdit->setObjectName(QStringLiteral("AngleTextEdit"));
        AngleTextEdit->setGeometry(QRect(30, 220, 101, 21));
        label = new QLabel(ObliqueImaging_GUI);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 190, 111, 16));
        OIButton = new QPushButton(ObliqueImaging_GUI);
        OIButton->setObjectName(QStringLiteral("OIButton"));
        OIButton->setGeometry(QRect(80, 330, 151, 31));
        horizontalSliderOI = new QSlider(ObliqueImaging_GUI);
        horizontalSliderOI->setObjectName(QStringLiteral("horizontalSliderOI"));
        horizontalSliderOI->setGeometry(QRect(180, 220, 121, 31));
        horizontalSliderOI->setMinimum(1);
        horizontalSliderOI->setMaximum(500);
        horizontalSliderOI->setSingleStep(10);
        horizontalSliderOI->setValue(100);
        horizontalSliderOI->setOrientation(Qt::Horizontal);

        retranslateUi(ObliqueImaging_GUI);

        QMetaObject::connectSlotsByName(ObliqueImaging_GUI);
    } // setupUi

    void retranslateUi(QWidget *ObliqueImaging_GUI)
    {
        ObliqueImaging_GUI->setWindowTitle(QApplication::translate("ObliqueImaging_GUI", "ObliqueImaging_GUI", Q_NULLPTR));
        label_2->setText(QApplication::translate("ObliqueImaging_GUI", "Oblique Imaging", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ObliqueImaging_GUI", "Image", Q_NULLPTR));
        label->setText(QApplication::translate("ObliqueImaging_GUI", "Enter plane angles:", Q_NULLPTR));
        OIButton->setText(QApplication::translate("ObliqueImaging_GUI", "Oblique Imaging", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ObliqueImaging_GUI: public Ui_ObliqueImaging_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBLIQUEIMAGING_GUI_H
