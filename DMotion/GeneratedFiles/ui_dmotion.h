/********************************************************************************
** Form generated from reading UI file 'dmotionh39336.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DMOTIONH39336_H
#define DMOTIONH39336_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DMotionClass
{
public:
    QAction *Edit_VelocityProfile;
    QAction *File_New;
    QAction *File_Open;
    QAction *File_Save;
    QAction *actionAbout_DMotion;
    QAction *actionExit;
    QAction *File_Import_STEP;
    QAction *File_Import_IGES;
    QAction *File_Import_2;
    QAction *File_Import;
    QAction *Analysis_dynamic;
    QAction *Tool_Graph;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuHome;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuAnalysis;
    QMenu *menuTool;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *DW_Modeling;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;

    void setupUi(QMainWindow *DMotionClass)
    {
        if (DMotionClass->objectName().isEmpty())
            DMotionClass->setObjectName(QStringLiteral("DMotionClass"));
        DMotionClass->resize(728, 400);
        Edit_VelocityProfile = new QAction(DMotionClass);
        Edit_VelocityProfile->setObjectName(QStringLiteral("Edit_VelocityProfile"));
        File_New = new QAction(DMotionClass);
        File_New->setObjectName(QStringLiteral("File_New"));
        File_Open = new QAction(DMotionClass);
        File_Open->setObjectName(QStringLiteral("File_Open"));
        File_Save = new QAction(DMotionClass);
        File_Save->setObjectName(QStringLiteral("File_Save"));
        actionAbout_DMotion = new QAction(DMotionClass);
        actionAbout_DMotion->setObjectName(QStringLiteral("actionAbout_DMotion"));
        actionExit = new QAction(DMotionClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        File_Import_STEP = new QAction(DMotionClass);
        File_Import_STEP->setObjectName(QStringLiteral("File_Import_STEP"));
        File_Import_IGES = new QAction(DMotionClass);
        File_Import_IGES->setObjectName(QStringLiteral("File_Import_IGES"));
        File_Import_2 = new QAction(DMotionClass);
        File_Import_2->setObjectName(QStringLiteral("File_Import_2"));
        File_Import = new QAction(DMotionClass);
        File_Import->setObjectName(QStringLiteral("File_Import"));
        Analysis_dynamic = new QAction(DMotionClass);
        Analysis_dynamic->setObjectName(QStringLiteral("Analysis_dynamic"));
        Tool_Graph = new QAction(DMotionClass);
        Tool_Graph->setObjectName(QStringLiteral("Tool_Graph"));
        centralWidget = new QWidget(DMotionClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DMotionClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DMotionClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 728, 21));
        menuHome = new QMenu(menuBar);
        menuHome->setObjectName(QStringLiteral("menuHome"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuAnalysis = new QMenu(menuBar);
        menuAnalysis->setObjectName(QStringLiteral("menuAnalysis"));
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QStringLiteral("menuTool"));
        DMotionClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DMotionClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DMotionClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DMotionClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DMotionClass->setStatusBar(statusBar);
        DW_Modeling = new QDockWidget(DMotionClass);
        DW_Modeling->setObjectName(QStringLiteral("DW_Modeling"));
        DW_Modeling->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        DW_Modeling->setWidget(dockWidgetContents);
        DMotionClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), DW_Modeling);

        menuBar->addAction(menuHome->menuAction());
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuBar->addAction(menuAnalysis->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHome->addAction(actionAbout_DMotion);
        menuHome->addAction(actionExit);
        menuFile->addAction(File_New);
        menuFile->addAction(File_Open);
        menuFile->addAction(File_Save);
        menuFile->addSeparator();
        menuFile->addAction(File_Import);
        menuEdit->addAction(Edit_VelocityProfile);
        menuAnalysis->addAction(Analysis_dynamic);
        menuTool->addAction(Tool_Graph);

        retranslateUi(DMotionClass);

        QMetaObject::connectSlotsByName(DMotionClass);
    } // setupUi

    void retranslateUi(QMainWindow *DMotionClass)
    {
        DMotionClass->setWindowTitle(QApplication::translate("DMotionClass", "DMotion", 0));
        Edit_VelocityProfile->setText(QApplication::translate("DMotionClass", "Velocity profile", 0));
        File_New->setText(QApplication::translate("DMotionClass", "New", 0));
        File_Open->setText(QApplication::translate("DMotionClass", "Open", 0));
        File_Save->setText(QApplication::translate("DMotionClass", "Save", 0));
        actionAbout_DMotion->setText(QApplication::translate("DMotionClass", "About DMotion", 0));
        actionExit->setText(QApplication::translate("DMotionClass", "Exit", 0));
        File_Import_STEP->setText(QApplication::translate("DMotionClass", "STEP", 0));
        File_Import_IGES->setText(QApplication::translate("DMotionClass", "IGES", 0));
        File_Import_2->setText(QApplication::translate("DMotionClass", "Import", 0));
        File_Import->setText(QApplication::translate("DMotionClass", "Import", 0));
        Analysis_dynamic->setText(QApplication::translate("DMotionClass", "Dynamic", 0));
        Tool_Graph->setText(QApplication::translate("DMotionClass", "Graph", 0));
        menuHome->setTitle(QApplication::translate("DMotionClass", "Home", 0));
        menuFile->setTitle(QApplication::translate("DMotionClass", "File", 0));
        menuEdit->setTitle(QApplication::translate("DMotionClass", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("DMotionClass", "Help", 0));
        menuAnalysis->setTitle(QApplication::translate("DMotionClass", "Analysis", 0));
        menuTool->setTitle(QApplication::translate("DMotionClass", "Tool", 0));
    } // retranslateUi

};

namespace Ui {
    class DMotionClass: public Ui_DMotionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DMOTIONH39336_H
