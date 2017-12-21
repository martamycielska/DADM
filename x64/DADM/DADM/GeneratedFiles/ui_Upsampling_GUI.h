/********************************************************************************
** Form generated from reading UI file 'Upsampling_GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPSAMPLING_GUI_H
#define UI_UPSAMPLING_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Upsampling_GUI
{
public:
    QLabel *label_2;
    QPushButton *pushButton_2;
    QGroupBox *groupBox;
    QOpenGLWidget *openGLWidget;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QOpenGLWidget *openGLWidget_2;

    void setupUi(QWidget *Upsampling_GUI)
    {
        if (Upsampling_GUI->objectName().isEmpty())
            Upsampling_GUI->setObjectName(QStringLiteral("Upsampling_GUI"));
        Upsampling_GUI->resize(800, 600);
        label_2 = new QLabel(Upsampling_GUI);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(240, 30, 321, 51));
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setScaledContents(false);
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setWordWrap(false);
        pushButton_2 = new QPushButton(Upsampling_GUI);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 490, 91, 31));
        groupBox = new QGroupBox(Upsampling_GUI);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 130, 371, 351));
        openGLWidget = new QOpenGLWidget(groupBox);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(20, 20, 331, 311));
        pushButton = new QPushButton(Upsampling_GUI);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(540, 490, 90, 31));
        groupBox_2 = new QGroupBox(Upsampling_GUI);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(410, 130, 361, 351));
        openGLWidget_2 = new QOpenGLWidget(groupBox_2);
        openGLWidget_2->setObjectName(QStringLiteral("openGLWidget_2"));
        openGLWidget_2->setGeometry(QRect(20, 20, 321, 311));

        retranslateUi(Upsampling_GUI);

        QMetaObject::connectSlotsByName(Upsampling_GUI);
    } // setupUi

    void retranslateUi(QWidget *Upsampling_GUI)
    {
        Upsampling_GUI->setWindowTitle(QApplication::translate("Upsampling_GUI", "Upsampling_GUI", Q_NULLPTR));
        label_2->setText(QApplication::translate("Upsampling_GUI", "Upsampling", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Upsampling_GUI", "Open LR Image", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Upsampling_GUI", "LR Image", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Upsampling_GUI", "Upsampling", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Upsampling_GUI", "Upsampled Image", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Upsampling_GUI: public Ui_Upsampling_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPSAMPLING_GUI_H
