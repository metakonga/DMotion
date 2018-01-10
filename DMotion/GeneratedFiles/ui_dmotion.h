/********************************************************************************
** Form generated from reading UI file 'dmotionf37264.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DMOTIONF37264_H
#define DMOTIONF37264_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
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
    QAction *actionResult_table;
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
    QTabWidget *TAB_MODELING;
    QWidget *DesignTab;
    QFrame *DesignTabFrame;
    QGroupBox *groupBox_5;
    QPushButton *PB_SelectParameters;
    QWidget *layoutWidget_5;
    QVBoxLayout *verticalLayout;
    QRadioButton *RB_OnlyOne;
    QRadioButton *RB_SmallerThanFirst;
    QWidget *tab_2;
    QGroupBox *GB_HardPoint;
    QLabel *label;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *L_HardPoint;
    QComboBox *CB_HardPoint;
    QLabel *L_HardPoint_X;
    QLineEdit *LE_HardPoint_X;
    QLabel *L_HardPoint_Y;
    QLineEdit *LE_HardPoint_Y;
    QGroupBox *GB_DrivingCondition;
    QPushButton *PB_ImportNozzelVelocity;
    QPushButton *PB_ImportArcVelocity;
    QFrame *Nozzle_Graph_Frame;
    QFrame *Arc_Graph_Frame;
    QGroupBox *GB_BodyInformation;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *L_Body;
    QComboBox *CB_Body;
    QLabel *L_X;
    QLineEdit *LE_X;
    QLabel *L_Y;
    QLineEdit *LE_Y;
    QLabel *L_Angle;
    QLineEdit *LE_Angle;
    QLabel *L_Mass;
    QLineEdit *LE_Mass;
    QLabel *L_Inertai;
    QLineEdit *LE_Inertia;
    QLabel *L_Shape;
    QPushButton *PB_Shape;

    void setupUi(QMainWindow *DMotionClass)
    {
        if (DMotionClass->objectName().isEmpty())
            DMotionClass->setObjectName(QStringLiteral("DMotionClass"));
        DMotionClass->resize(1318, 615);
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
        actionResult_table = new QAction(DMotionClass);
        actionResult_table->setObjectName(QStringLiteral("actionResult_table"));
        centralWidget = new QWidget(DMotionClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DMotionClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DMotionClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1318, 21));
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
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        TAB_MODELING = new QTabWidget(dockWidgetContents);
        TAB_MODELING->setObjectName(QStringLiteral("TAB_MODELING"));
        DesignTab = new QWidget();
        DesignTab->setObjectName(QStringLiteral("DesignTab"));
        DesignTabFrame = new QFrame(DesignTab);
        DesignTabFrame->setObjectName(QStringLiteral("DesignTabFrame"));
        DesignTabFrame->setGeometry(QRect(-1, 10, 489, 531));
        DesignTabFrame->setFrameShape(QFrame::NoFrame);
        DesignTabFrame->setFrameShadow(QFrame::Raised);
        DesignTabFrame->setLineWidth(0);
        groupBox_5 = new QGroupBox(DesignTabFrame);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(2, 0, 481, 71));
        PB_SelectParameters = new QPushButton(groupBox_5);
        PB_SelectParameters->setObjectName(QStringLiteral("PB_SelectParameters"));
        PB_SelectParameters->setGeometry(QRect(400, 20, 75, 41));
        layoutWidget_5 = new QWidget(groupBox_5);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 20, 384, 41));
        verticalLayout = new QVBoxLayout(layoutWidget_5);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        RB_OnlyOne = new QRadioButton(layoutWidget_5);
        RB_OnlyOne->setObjectName(QStringLiteral("RB_OnlyOne"));
        RB_OnlyOne->setChecked(true);

        verticalLayout->addWidget(RB_OnlyOne);

        RB_SmallerThanFirst = new QRadioButton(layoutWidget_5);
        RB_SmallerThanFirst->setObjectName(QStringLiteral("RB_SmallerThanFirst"));

        verticalLayout->addWidget(RB_SmallerThanFirst);

        TAB_MODELING->addTab(DesignTab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        GB_HardPoint = new QGroupBox(tab_2);
        GB_HardPoint->setObjectName(QStringLiteral("GB_HardPoint"));
        GB_HardPoint->setGeometry(QRect(280, 10, 211, 104));
        label = new QLabel(GB_HardPoint);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 56, 12));
        layoutWidget_2 = new QWidget(GB_HardPoint);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 20, 191, 74));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        L_HardPoint = new QLabel(layoutWidget_2);
        L_HardPoint->setObjectName(QStringLiteral("L_HardPoint"));

        gridLayout_4->addWidget(L_HardPoint, 0, 0, 1, 1);

        CB_HardPoint = new QComboBox(layoutWidget_2);
        CB_HardPoint->setObjectName(QStringLiteral("CB_HardPoint"));

        gridLayout_4->addWidget(CB_HardPoint, 0, 1, 1, 1);

        L_HardPoint_X = new QLabel(layoutWidget_2);
        L_HardPoint_X->setObjectName(QStringLiteral("L_HardPoint_X"));
        L_HardPoint_X->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_HardPoint_X, 1, 0, 1, 1);

        LE_HardPoint_X = new QLineEdit(layoutWidget_2);
        LE_HardPoint_X->setObjectName(QStringLiteral("LE_HardPoint_X"));

        gridLayout_4->addWidget(LE_HardPoint_X, 1, 1, 1, 1);

        L_HardPoint_Y = new QLabel(layoutWidget_2);
        L_HardPoint_Y->setObjectName(QStringLiteral("L_HardPoint_Y"));
        L_HardPoint_Y->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_HardPoint_Y, 2, 0, 1, 1);

        LE_HardPoint_Y = new QLineEdit(layoutWidget_2);
        LE_HardPoint_Y->setObjectName(QStringLiteral("LE_HardPoint_Y"));

        gridLayout_4->addWidget(LE_HardPoint_Y, 2, 1, 1, 1);

        GB_DrivingCondition = new QGroupBox(tab_2);
        GB_DrivingCondition->setObjectName(QStringLiteral("GB_DrivingCondition"));
        GB_DrivingCondition->setGeometry(QRect(280, 120, 211, 111));
        PB_ImportNozzelVelocity = new QPushButton(GB_DrivingCondition);
        PB_ImportNozzelVelocity->setObjectName(QStringLiteral("PB_ImportNozzelVelocity"));
        PB_ImportNozzelVelocity->setGeometry(QRect(140, 14, 61, 45));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        PB_ImportNozzelVelocity->setFont(font);
        PB_ImportArcVelocity = new QPushButton(GB_DrivingCondition);
        PB_ImportArcVelocity->setObjectName(QStringLiteral("PB_ImportArcVelocity"));
        PB_ImportArcVelocity->setGeometry(QRect(140, 61, 61, 45));
        PB_ImportArcVelocity->setFont(font);
        Nozzle_Graph_Frame = new QFrame(GB_DrivingCondition);
        Nozzle_Graph_Frame->setObjectName(QStringLiteral("Nozzle_Graph_Frame"));
        Nozzle_Graph_Frame->setGeometry(QRect(10, 15, 120, 45));
        Nozzle_Graph_Frame->setFrameShape(QFrame::StyledPanel);
        Nozzle_Graph_Frame->setFrameShadow(QFrame::Raised);
        Arc_Graph_Frame = new QFrame(GB_DrivingCondition);
        Arc_Graph_Frame->setObjectName(QStringLiteral("Arc_Graph_Frame"));
        Arc_Graph_Frame->setGeometry(QRect(10, 61, 120, 45));
        Arc_Graph_Frame->setFrameShape(QFrame::StyledPanel);
        Arc_Graph_Frame->setFrameShadow(QFrame::Raised);
        GB_BodyInformation = new QGroupBox(tab_2);
        GB_BodyInformation->setObjectName(QStringLiteral("GB_BodyInformation"));
        GB_BodyInformation->setGeometry(QRect(12, 10, 261, 221));
        layoutWidget = new QWidget(GB_BodyInformation);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 241, 191));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        L_Body = new QLabel(layoutWidget);
        L_Body->setObjectName(QStringLiteral("L_Body"));
        L_Body->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(L_Body, 0, 0, 1, 1);

        CB_Body = new QComboBox(layoutWidget);
        CB_Body->setObjectName(QStringLiteral("CB_Body"));

        gridLayout_3->addWidget(CB_Body, 0, 1, 1, 1);

        L_X = new QLabel(layoutWidget);
        L_X->setObjectName(QStringLiteral("L_X"));
        L_X->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(L_X, 1, 0, 1, 1);

        LE_X = new QLineEdit(layoutWidget);
        LE_X->setObjectName(QStringLiteral("LE_X"));

        gridLayout_3->addWidget(LE_X, 1, 1, 1, 1);

        L_Y = new QLabel(layoutWidget);
        L_Y->setObjectName(QStringLiteral("L_Y"));
        L_Y->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(L_Y, 2, 0, 1, 1);

        LE_Y = new QLineEdit(layoutWidget);
        LE_Y->setObjectName(QStringLiteral("LE_Y"));

        gridLayout_3->addWidget(LE_Y, 2, 1, 1, 1);

        L_Angle = new QLabel(layoutWidget);
        L_Angle->setObjectName(QStringLiteral("L_Angle"));
        L_Angle->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(L_Angle, 3, 0, 1, 1);

        LE_Angle = new QLineEdit(layoutWidget);
        LE_Angle->setObjectName(QStringLiteral("LE_Angle"));

        gridLayout_3->addWidget(LE_Angle, 3, 1, 1, 1);

        L_Mass = new QLabel(layoutWidget);
        L_Mass->setObjectName(QStringLiteral("L_Mass"));
        L_Mass->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(L_Mass, 4, 0, 1, 1);

        LE_Mass = new QLineEdit(layoutWidget);
        LE_Mass->setObjectName(QStringLiteral("LE_Mass"));

        gridLayout_3->addWidget(LE_Mass, 4, 1, 1, 1);

        L_Inertai = new QLabel(layoutWidget);
        L_Inertai->setObjectName(QStringLiteral("L_Inertai"));
        L_Inertai->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(L_Inertai, 5, 0, 1, 1);

        LE_Inertia = new QLineEdit(layoutWidget);
        LE_Inertia->setObjectName(QStringLiteral("LE_Inertia"));

        gridLayout_3->addWidget(LE_Inertia, 5, 1, 1, 1);

        L_Shape = new QLabel(layoutWidget);
        L_Shape->setObjectName(QStringLiteral("L_Shape"));
        L_Shape->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(L_Shape, 6, 0, 1, 1);

        PB_Shape = new QPushButton(layoutWidget);
        PB_Shape->setObjectName(QStringLiteral("PB_Shape"));

        gridLayout_3->addWidget(PB_Shape, 6, 1, 1, 1);

        TAB_MODELING->addTab(tab_2, QString());

        gridLayout->addWidget(TAB_MODELING, 0, 0, 1, 1);

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
        menuTool->addAction(actionResult_table);

        retranslateUi(DMotionClass);

        TAB_MODELING->setCurrentIndex(0);


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
        actionResult_table->setText(QApplication::translate("DMotionClass", "Result table", 0));
        menuHome->setTitle(QApplication::translate("DMotionClass", "Home", 0));
        menuFile->setTitle(QApplication::translate("DMotionClass", "File", 0));
        menuEdit->setTitle(QApplication::translate("DMotionClass", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("DMotionClass", "Help", 0));
        menuAnalysis->setTitle(QApplication::translate("DMotionClass", "Analysis", 0));
        menuTool->setTitle(QApplication::translate("DMotionClass", "Tool", 0));
        groupBox_5->setTitle(QApplication::translate("DMotionClass", "Optimum condition", 0));
        PB_SelectParameters->setText(QApplication::translate("DMotionClass", "Select\n"
" parameters", 0));
        RB_OnlyOne->setText(QApplication::translate("DMotionClass", "Select only one", 0));
        RB_SmallerThanFirst->setText(QApplication::translate("DMotionClass", "Select smaller case than first", 0));
        TAB_MODELING->setTabText(TAB_MODELING->indexOf(DesignTab), QApplication::translate("DMotionClass", "Design", 0));
        GB_HardPoint->setTitle(QApplication::translate("DMotionClass", "Hard point information", 0));
        label->setText(QString());
        L_HardPoint->setText(QApplication::translate("DMotionClass", "Hard point", 0));
        L_HardPoint_X->setText(QApplication::translate("DMotionClass", "X", 0));
        L_HardPoint_Y->setText(QApplication::translate("DMotionClass", "Y", 0));
        GB_DrivingCondition->setTitle(QApplication::translate("DMotionClass", "Driving condition", 0));
        PB_ImportNozzelVelocity->setText(QApplication::translate("DMotionClass", "Nozzel", 0));
        PB_ImportArcVelocity->setText(QApplication::translate("DMotionClass", "Arc", 0));
        GB_BodyInformation->setTitle(QApplication::translate("DMotionClass", "Body information", 0));
        L_Body->setText(QApplication::translate("DMotionClass", "Body", 0));
        L_X->setText(QApplication::translate("DMotionClass", "X", 0));
        L_Y->setText(QApplication::translate("DMotionClass", "Y", 0));
        L_Angle->setText(QApplication::translate("DMotionClass", "Angle", 0));
        L_Mass->setText(QApplication::translate("DMotionClass", "Mass", 0));
        L_Inertai->setText(QApplication::translate("DMotionClass", "Inertia", 0));
        L_Shape->setText(QApplication::translate("DMotionClass", "Shape", 0));
        PB_Shape->setText(QApplication::translate("DMotionClass", "Nozzle shpae", 0));
        TAB_MODELING->setTabText(TAB_MODELING->indexOf(tab_2), QApplication::translate("DMotionClass", "Modeling", 0));
    } // retranslateUi

};

namespace Ui {
    class DMotionClass: public Ui_DMotionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DMOTIONF37264_H
