/********************************************************************************
** Form generated from reading UI file 'borderwidgetqt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BORDERWIDGETQT_H
#define UI_BORDERWIDGETQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_BorderWidgetQt
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionHelp;
    QAction *actionSave;
    QWidget *centralwidget;
    QVTKOpenGLWidget *qvtkWidget;

    void setupUi(QMainWindow *BorderWidgetQt)
    {
        if (BorderWidgetQt->objectName().isEmpty())
            BorderWidgetQt->setObjectName(QStringLiteral("BorderWidgetQt"));
        BorderWidgetQt->resize(572, 583);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        BorderWidgetQt->setWindowIcon(icon);
        BorderWidgetQt->setIconSize(QSize(22, 22));
        actionOpenFile = new QAction(BorderWidgetQt);
        actionOpenFile->setObjectName(QStringLiteral("actionOpenFile"));
        actionOpenFile->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon1);
        actionExit = new QAction(BorderWidgetQt);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(""), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionPrint = new QAction(BorderWidgetQt);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icons/print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon3);
        actionHelp = new QAction(BorderWidgetQt);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionHelp->setIcon(icon);
        actionSave = new QAction(BorderWidgetQt);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        centralwidget = new QWidget(BorderWidgetQt);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        qvtkWidget = new QVTKOpenGLWidget(centralwidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(10, 20, 511, 541));
        BorderWidgetQt->setCentralWidget(centralwidget);

        retranslateUi(BorderWidgetQt);

        QMetaObject::connectSlotsByName(BorderWidgetQt);
    } // setupUi

    void retranslateUi(QMainWindow *BorderWidgetQt)
    {
        BorderWidgetQt->setWindowTitle(QApplication::translate("BorderWidgetQt", "SimpleView", Q_NULLPTR));
        actionOpenFile->setText(QApplication::translate("BorderWidgetQt", "Open File...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("BorderWidgetQt", "Exit", Q_NULLPTR));
        actionPrint->setText(QApplication::translate("BorderWidgetQt", "Print", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("BorderWidgetQt", "Help", Q_NULLPTR));
        actionSave->setText(QApplication::translate("BorderWidgetQt", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BorderWidgetQt: public Ui_BorderWidgetQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BORDERWIDGETQT_H
