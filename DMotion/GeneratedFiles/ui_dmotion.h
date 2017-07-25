/********************************************************************************
** Form generated from reading UI file 'dmotion.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DMOTION_H
#define UI_DMOTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DMotionClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DMotionClass)
    {
        if (DMotionClass->objectName().isEmpty())
            DMotionClass->setObjectName(QStringLiteral("DMotionClass"));
        DMotionClass->resize(600, 400);
        menuBar = new QMenuBar(DMotionClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        DMotionClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DMotionClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DMotionClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DMotionClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DMotionClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DMotionClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DMotionClass->setStatusBar(statusBar);

        retranslateUi(DMotionClass);

        QMetaObject::connectSlotsByName(DMotionClass);
    } // setupUi

    void retranslateUi(QMainWindow *DMotionClass)
    {
        DMotionClass->setWindowTitle(QApplication::translate("DMotionClass", "DMotion", 0));
    } // retranslateUi

};

namespace Ui {
    class DMotionClass: public Ui_DMotionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DMOTION_H
