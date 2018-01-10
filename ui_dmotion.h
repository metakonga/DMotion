/********************************************************************************
** Form generated from reading UI file 'dmotionn34344.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DMOTIONN34344_H
#define DMOTIONN34344_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
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
    QFrame *frame;
    QGroupBox *GB_DESIGN_VARIABLE;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *L_LOWER;
    QLabel *L_Step;
    QLabel *L_Upper;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QCheckBox *CB_HEADLINK_X;
    QLabel *L_HEADLINK_X;
    QLineEdit *LE_HEADLINK_LOWER_X;
    QLineEdit *LE_HEADLINK_STEP_X;
    QLineEdit *LE_HEADLINK_UPPER_X;
    QCheckBox *CB_HEADLINK_Y;
    QLabel *L_HEADLINKCAM_Y;
    QLineEdit *LE_HEADLINK_LOWER_Y;
    QLineEdit *LE_HEADLINK_STEP_Y;
    QLineEdit *LE_HEADLINK_UPPER_Y;
    QCheckBox *CB_LINKCAM_X;
    QLabel *L_LINKCAM_X;
    QLineEdit *LE_LINKCAM_LOWER_X;
    QLineEdit *LE_LINKCAM_STEP_X;
    QLineEdit *LE_LINKCAM_UPPER_X;
    QCheckBox *CB_LINKCAM_Y;
    QLabel *L_LINKCAM_Y;
    QLineEdit *LE_LINKCAM_LOWER_Y;
    QLineEdit *LE_LINKCAM_STEP_Y;
    QLineEdit *LE_LINKCAM_UPPER_Y;
    QCheckBox *CB_CAMRC_X;
    QLabel *L_CAMRC_X;
    QLineEdit *LE_CAMRC_LOWER_X;
    QLineEdit *LE_CAMRC_STEP_X;
    QLineEdit *LE_CAMRC_UPPER_X;
    QCheckBox *CB_CAMRC_Y;
    QLabel *L_CAMRC_Y;
    QLineEdit *LE_CAMRC_LOWER_Y;
    QLineEdit *LE_CAMRC_STEP_Y;
    QLineEdit *LE_CAMRC_UPPER_Y;
    QCheckBox *CB_CAMPV_X;
    QLabel *L_CAMPV_X;
    QLineEdit *LE_CAMPV_LOWER_X;
    QLineEdit *LE_CAMPV_STEP_X;
    QLineEdit *LE_CAMPV_UPPER_X;
    QCheckBox *CB_CAMPV_Y;
    QLabel *L_CAMPV_Y;
    QLineEdit *LE_CAMPV_LOWER_Y;
    QLineEdit *LE_CAMPV_STEP_Y;
    QLineEdit *LE_CAMPV_UPPER_Y;
    QLabel *L_CAMANGLE;
    QLineEdit *LE_CAM_ANGLE;
    QGroupBox *groupBox_4;
    QPushButton *PB_SaveCase;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_6;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *LE_CI_HeadLink_X;
    QLineEdit *LE_CI_LinkCam_X;
    QLineEdit *LE_CI_CamRC_X;
    QLineEdit *LE_CI_CamPV_X;
    QLabel *label_6;
    QLineEdit *LE_CI_HeadLink_Y;
    QLineEdit *LE_CI_LinkCam_Y;
    QLineEdit *LE_CI_CamRC_Y;
    QLineEdit *LE_CI_CamPV_Y;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *L_CaseName;
    QLineEdit *LE_CaseName;
    QGroupBox *groupBox_5;
    QPushButton *PB_SelectParameters;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QRadioButton *RB_OnlyOne;
    QRadioButton *RB_SmallerThanFirst;
    QWidget *tab_2;
    QGroupBox *groupBox;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_4;
    QLabel *L_Head;
    QLabel *L_Link;
    QLabel *L_Cam;
    QLabel *L_Passive;
    QLabel *L_X;
    QLineEdit *LE_Head_X;
    QLineEdit *LE_Link_X;
    QLineEdit *LE_Cam_X;
    QLineEdit *LE_Passive_X;
    QLabel *L_Y;
    QLineEdit *LE_Head_Y;
    QLineEdit *LE_Link_Y;
    QLineEdit *LE_Cam_Y;
    QLineEdit *LE_Passive_Y;
    QLabel *L_Angle;
    QLineEdit *LE_Head_Angle;
    QLineEdit *LE_Link_Angle;
    QLineEdit *LE_Cam_Angle;
    QLineEdit *LE_Passive_Angle;
    QLabel *L_Mass;
    QLineEdit *LE_Head_Mass;
    QLineEdit *LE_Link_Mass;
    QLineEdit *LE_Cam_Mass;
    QLineEdit *LE_Passive_Mass;
    QLabel *L_Inertai;
    QLineEdit *LE_Head_Inertia;
    QLineEdit *LE_Link_Inertia;
    QLineEdit *LE_Cam_Inertia;
    QLineEdit *LE_Passive_Inertia;
    QLabel *L_Shape;
    QPushButton *PB_HeadShape;
    QPushButton *PB_LinkShape;
    QPushButton *PB_CamShape;
    QPushButton *PB_PassiveShape;
    QGroupBox *groupBox_2;
    QLabel *L_H_L_X;
    QLabel *L_C_C_X;
    QLabel *L_C_C_Y;
    QLabel *L_H_L_Y;
    QWidget *layoutWidget4;
    QGridLayout *gridLayout_3;
    QLabel *L_HeadLink;
    QLineEdit *LE_HeadLink_X;
    QLineEdit *LE_HeadLink_Y;
    QLabel *L_CamGround;
    QLineEdit *LE_CamGround_X;
    QLineEdit *LE_CamGround_Y;
    QLabel *L_LinkCam;
    QLineEdit *LE_LinkCam_X;
    QLineEdit *LE_LinkCam_Y;
    QLabel *L_Cam_Passive;
    QLineEdit *LE_CamPassive_X;
    QLineEdit *LE_CamPassive_Y;
    QGroupBox *groupBox_3;
    QPushButton *PB_ActiveVP;
    QPushButton *PB_PassivePV;

    void setupUi(QMainWindow *DMotionClass)
    {
        if (DMotionClass->objectName().isEmpty())
            DMotionClass->setObjectName(QStringLiteral("DMotionClass"));
        DMotionClass->resize(980, 660);
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
        menuBar->setGeometry(QRect(0, 0, 980, 21));
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
        TAB_MODELING = new QTabWidget(dockWidgetContents);
        TAB_MODELING->setObjectName(QStringLiteral("TAB_MODELING"));
        DesignTab = new QWidget();
        DesignTab->setObjectName(QStringLiteral("DesignTab"));
        frame = new QFrame(DesignTab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-1, 10, 489, 531));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(0);
        GB_DESIGN_VARIABLE = new QGroupBox(frame);
        GB_DESIGN_VARIABLE->setObjectName(QStringLiteral("GB_DESIGN_VARIABLE"));
        GB_DESIGN_VARIABLE->setGeometry(QRect(2, 80, 480, 281));
        layoutWidget = new QWidget(GB_DESIGN_VARIABLE);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 21, 361, 16));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        L_LOWER = new QLabel(layoutWidget);
        L_LOWER->setObjectName(QStringLiteral("L_LOWER"));
        L_LOWER->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(L_LOWER);

        L_Step = new QLabel(layoutWidget);
        L_Step->setObjectName(QStringLiteral("L_Step"));
        L_Step->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(L_Step);

        L_Upper = new QLabel(layoutWidget);
        L_Upper->setObjectName(QStringLiteral("L_Upper"));
        L_Upper->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(L_Upper);

        widget = new QWidget(GB_DESIGN_VARIABLE);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 43, 461, 230));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        CB_HEADLINK_X = new QCheckBox(widget);
        CB_HEADLINK_X->setObjectName(QStringLiteral("CB_HEADLINK_X"));
        CB_HEADLINK_X->setChecked(true);

        gridLayout_2->addWidget(CB_HEADLINK_X, 0, 0, 1, 1);

        L_HEADLINK_X = new QLabel(widget);
        L_HEADLINK_X->setObjectName(QStringLiteral("L_HEADLINK_X"));

        gridLayout_2->addWidget(L_HEADLINK_X, 0, 1, 1, 1);

        LE_HEADLINK_LOWER_X = new QLineEdit(widget);
        LE_HEADLINK_LOWER_X->setObjectName(QStringLiteral("LE_HEADLINK_LOWER_X"));

        gridLayout_2->addWidget(LE_HEADLINK_LOWER_X, 0, 2, 1, 1);

        LE_HEADLINK_STEP_X = new QLineEdit(widget);
        LE_HEADLINK_STEP_X->setObjectName(QStringLiteral("LE_HEADLINK_STEP_X"));

        gridLayout_2->addWidget(LE_HEADLINK_STEP_X, 0, 3, 1, 1);

        LE_HEADLINK_UPPER_X = new QLineEdit(widget);
        LE_HEADLINK_UPPER_X->setObjectName(QStringLiteral("LE_HEADLINK_UPPER_X"));

        gridLayout_2->addWidget(LE_HEADLINK_UPPER_X, 0, 4, 1, 1);

        CB_HEADLINK_Y = new QCheckBox(widget);
        CB_HEADLINK_Y->setObjectName(QStringLiteral("CB_HEADLINK_Y"));
        CB_HEADLINK_Y->setChecked(true);

        gridLayout_2->addWidget(CB_HEADLINK_Y, 1, 0, 1, 1);

        L_HEADLINKCAM_Y = new QLabel(widget);
        L_HEADLINKCAM_Y->setObjectName(QStringLiteral("L_HEADLINKCAM_Y"));

        gridLayout_2->addWidget(L_HEADLINKCAM_Y, 1, 1, 1, 1);

        LE_HEADLINK_LOWER_Y = new QLineEdit(widget);
        LE_HEADLINK_LOWER_Y->setObjectName(QStringLiteral("LE_HEADLINK_LOWER_Y"));

        gridLayout_2->addWidget(LE_HEADLINK_LOWER_Y, 1, 2, 1, 1);

        LE_HEADLINK_STEP_Y = new QLineEdit(widget);
        LE_HEADLINK_STEP_Y->setObjectName(QStringLiteral("LE_HEADLINK_STEP_Y"));

        gridLayout_2->addWidget(LE_HEADLINK_STEP_Y, 1, 3, 1, 1);

        LE_HEADLINK_UPPER_Y = new QLineEdit(widget);
        LE_HEADLINK_UPPER_Y->setObjectName(QStringLiteral("LE_HEADLINK_UPPER_Y"));

        gridLayout_2->addWidget(LE_HEADLINK_UPPER_Y, 1, 4, 1, 1);

        CB_LINKCAM_X = new QCheckBox(widget);
        CB_LINKCAM_X->setObjectName(QStringLiteral("CB_LINKCAM_X"));
        CB_LINKCAM_X->setChecked(true);

        gridLayout_2->addWidget(CB_LINKCAM_X, 2, 0, 1, 1);

        L_LINKCAM_X = new QLabel(widget);
        L_LINKCAM_X->setObjectName(QStringLiteral("L_LINKCAM_X"));

        gridLayout_2->addWidget(L_LINKCAM_X, 2, 1, 1, 1);

        LE_LINKCAM_LOWER_X = new QLineEdit(widget);
        LE_LINKCAM_LOWER_X->setObjectName(QStringLiteral("LE_LINKCAM_LOWER_X"));

        gridLayout_2->addWidget(LE_LINKCAM_LOWER_X, 2, 2, 1, 1);

        LE_LINKCAM_STEP_X = new QLineEdit(widget);
        LE_LINKCAM_STEP_X->setObjectName(QStringLiteral("LE_LINKCAM_STEP_X"));

        gridLayout_2->addWidget(LE_LINKCAM_STEP_X, 2, 3, 1, 1);

        LE_LINKCAM_UPPER_X = new QLineEdit(widget);
        LE_LINKCAM_UPPER_X->setObjectName(QStringLiteral("LE_LINKCAM_UPPER_X"));

        gridLayout_2->addWidget(LE_LINKCAM_UPPER_X, 2, 4, 1, 1);

        CB_LINKCAM_Y = new QCheckBox(widget);
        CB_LINKCAM_Y->setObjectName(QStringLiteral("CB_LINKCAM_Y"));
        CB_LINKCAM_Y->setChecked(true);

        gridLayout_2->addWidget(CB_LINKCAM_Y, 3, 0, 1, 1);

        L_LINKCAM_Y = new QLabel(widget);
        L_LINKCAM_Y->setObjectName(QStringLiteral("L_LINKCAM_Y"));

        gridLayout_2->addWidget(L_LINKCAM_Y, 3, 1, 1, 1);

        LE_LINKCAM_LOWER_Y = new QLineEdit(widget);
        LE_LINKCAM_LOWER_Y->setObjectName(QStringLiteral("LE_LINKCAM_LOWER_Y"));

        gridLayout_2->addWidget(LE_LINKCAM_LOWER_Y, 3, 2, 1, 1);

        LE_LINKCAM_STEP_Y = new QLineEdit(widget);
        LE_LINKCAM_STEP_Y->setObjectName(QStringLiteral("LE_LINKCAM_STEP_Y"));

        gridLayout_2->addWidget(LE_LINKCAM_STEP_Y, 3, 3, 1, 1);

        LE_LINKCAM_UPPER_Y = new QLineEdit(widget);
        LE_LINKCAM_UPPER_Y->setObjectName(QStringLiteral("LE_LINKCAM_UPPER_Y"));

        gridLayout_2->addWidget(LE_LINKCAM_UPPER_Y, 3, 4, 1, 1);

        CB_CAMRC_X = new QCheckBox(widget);
        CB_CAMRC_X->setObjectName(QStringLiteral("CB_CAMRC_X"));
        CB_CAMRC_X->setChecked(true);

        gridLayout_2->addWidget(CB_CAMRC_X, 4, 0, 1, 1);

        L_CAMRC_X = new QLabel(widget);
        L_CAMRC_X->setObjectName(QStringLiteral("L_CAMRC_X"));

        gridLayout_2->addWidget(L_CAMRC_X, 4, 1, 1, 1);

        LE_CAMRC_LOWER_X = new QLineEdit(widget);
        LE_CAMRC_LOWER_X->setObjectName(QStringLiteral("LE_CAMRC_LOWER_X"));

        gridLayout_2->addWidget(LE_CAMRC_LOWER_X, 4, 2, 1, 1);

        LE_CAMRC_STEP_X = new QLineEdit(widget);
        LE_CAMRC_STEP_X->setObjectName(QStringLiteral("LE_CAMRC_STEP_X"));

        gridLayout_2->addWidget(LE_CAMRC_STEP_X, 4, 3, 1, 1);

        LE_CAMRC_UPPER_X = new QLineEdit(widget);
        LE_CAMRC_UPPER_X->setObjectName(QStringLiteral("LE_CAMRC_UPPER_X"));

        gridLayout_2->addWidget(LE_CAMRC_UPPER_X, 4, 4, 1, 1);

        CB_CAMRC_Y = new QCheckBox(widget);
        CB_CAMRC_Y->setObjectName(QStringLiteral("CB_CAMRC_Y"));
        CB_CAMRC_Y->setChecked(true);

        gridLayout_2->addWidget(CB_CAMRC_Y, 5, 0, 1, 1);

        L_CAMRC_Y = new QLabel(widget);
        L_CAMRC_Y->setObjectName(QStringLiteral("L_CAMRC_Y"));

        gridLayout_2->addWidget(L_CAMRC_Y, 5, 1, 1, 1);

        LE_CAMRC_LOWER_Y = new QLineEdit(widget);
        LE_CAMRC_LOWER_Y->setObjectName(QStringLiteral("LE_CAMRC_LOWER_Y"));

        gridLayout_2->addWidget(LE_CAMRC_LOWER_Y, 5, 2, 1, 1);

        LE_CAMRC_STEP_Y = new QLineEdit(widget);
        LE_CAMRC_STEP_Y->setObjectName(QStringLiteral("LE_CAMRC_STEP_Y"));

        gridLayout_2->addWidget(LE_CAMRC_STEP_Y, 5, 3, 1, 1);

        LE_CAMRC_UPPER_Y = new QLineEdit(widget);
        LE_CAMRC_UPPER_Y->setObjectName(QStringLiteral("LE_CAMRC_UPPER_Y"));

        gridLayout_2->addWidget(LE_CAMRC_UPPER_Y, 5, 4, 1, 1);

        CB_CAMPV_X = new QCheckBox(widget);
        CB_CAMPV_X->setObjectName(QStringLiteral("CB_CAMPV_X"));
        CB_CAMPV_X->setChecked(true);

        gridLayout_2->addWidget(CB_CAMPV_X, 6, 0, 1, 1);

        L_CAMPV_X = new QLabel(widget);
        L_CAMPV_X->setObjectName(QStringLiteral("L_CAMPV_X"));

        gridLayout_2->addWidget(L_CAMPV_X, 6, 1, 1, 1);

        LE_CAMPV_LOWER_X = new QLineEdit(widget);
        LE_CAMPV_LOWER_X->setObjectName(QStringLiteral("LE_CAMPV_LOWER_X"));

        gridLayout_2->addWidget(LE_CAMPV_LOWER_X, 6, 2, 1, 1);

        LE_CAMPV_STEP_X = new QLineEdit(widget);
        LE_CAMPV_STEP_X->setObjectName(QStringLiteral("LE_CAMPV_STEP_X"));

        gridLayout_2->addWidget(LE_CAMPV_STEP_X, 6, 3, 1, 1);

        LE_CAMPV_UPPER_X = new QLineEdit(widget);
        LE_CAMPV_UPPER_X->setObjectName(QStringLiteral("LE_CAMPV_UPPER_X"));

        gridLayout_2->addWidget(LE_CAMPV_UPPER_X, 6, 4, 1, 1);

        CB_CAMPV_Y = new QCheckBox(widget);
        CB_CAMPV_Y->setObjectName(QStringLiteral("CB_CAMPV_Y"));
        CB_CAMPV_Y->setChecked(true);

        gridLayout_2->addWidget(CB_CAMPV_Y, 7, 0, 1, 1);

        L_CAMPV_Y = new QLabel(widget);
        L_CAMPV_Y->setObjectName(QStringLiteral("L_CAMPV_Y"));

        gridLayout_2->addWidget(L_CAMPV_Y, 7, 1, 1, 1);

        LE_CAMPV_LOWER_Y = new QLineEdit(widget);
        LE_CAMPV_LOWER_Y->setObjectName(QStringLiteral("LE_CAMPV_LOWER_Y"));

        gridLayout_2->addWidget(LE_CAMPV_LOWER_Y, 7, 2, 1, 1);

        LE_CAMPV_STEP_Y = new QLineEdit(widget);
        LE_CAMPV_STEP_Y->setObjectName(QStringLiteral("LE_CAMPV_STEP_Y"));

        gridLayout_2->addWidget(LE_CAMPV_STEP_Y, 7, 3, 1, 1);

        LE_CAMPV_UPPER_Y = new QLineEdit(widget);
        LE_CAMPV_UPPER_Y->setObjectName(QStringLiteral("LE_CAMPV_UPPER_Y"));

        gridLayout_2->addWidget(LE_CAMPV_UPPER_Y, 7, 4, 1, 1);

        L_CAMANGLE = new QLabel(widget);
        L_CAMANGLE->setObjectName(QStringLiteral("L_CAMANGLE"));

        gridLayout_2->addWidget(L_CAMANGLE, 8, 1, 1, 1);

        LE_CAM_ANGLE = new QLineEdit(widget);
        LE_CAM_ANGLE->setObjectName(QStringLiteral("LE_CAM_ANGLE"));

        gridLayout_2->addWidget(LE_CAM_ANGLE, 8, 2, 1, 1);

        groupBox_4 = new QGroupBox(frame);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(2, 370, 480, 131));
        PB_SaveCase = new QPushButton(groupBox_4);
        PB_SaveCase->setObjectName(QStringLiteral("PB_SaveCase"));
        PB_SaveCase->setGeometry(QRect(260, 20, 81, 23));
        layoutWidget1 = new QWidget(groupBox_4);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 50, 461, 66));
        gridLayout_6 = new QGridLayout(layoutWidget1);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_2, 0, 2, 1, 1);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_3, 0, 3, 1, 1);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_4, 0, 4, 1, 1);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_6->addWidget(label_5, 1, 0, 1, 1);

        LE_CI_HeadLink_X = new QLineEdit(layoutWidget1);
        LE_CI_HeadLink_X->setObjectName(QStringLiteral("LE_CI_HeadLink_X"));
        LE_CI_HeadLink_X->setReadOnly(true);

        gridLayout_6->addWidget(LE_CI_HeadLink_X, 1, 1, 1, 1);

        LE_CI_LinkCam_X = new QLineEdit(layoutWidget1);
        LE_CI_LinkCam_X->setObjectName(QStringLiteral("LE_CI_LinkCam_X"));
        LE_CI_LinkCam_X->setReadOnly(true);

        gridLayout_6->addWidget(LE_CI_LinkCam_X, 1, 2, 1, 1);

        LE_CI_CamRC_X = new QLineEdit(layoutWidget1);
        LE_CI_CamRC_X->setObjectName(QStringLiteral("LE_CI_CamRC_X"));
        LE_CI_CamRC_X->setReadOnly(true);

        gridLayout_6->addWidget(LE_CI_CamRC_X, 1, 3, 1, 1);

        LE_CI_CamPV_X = new QLineEdit(layoutWidget1);
        LE_CI_CamPV_X->setObjectName(QStringLiteral("LE_CI_CamPV_X"));
        LE_CI_CamPV_X->setReadOnly(true);

        gridLayout_6->addWidget(LE_CI_CamPV_X, 1, 4, 1, 1);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_6->addWidget(label_6, 2, 0, 1, 1);

        LE_CI_HeadLink_Y = new QLineEdit(layoutWidget1);
        LE_CI_HeadLink_Y->setObjectName(QStringLiteral("LE_CI_HeadLink_Y"));
        LE_CI_HeadLink_Y->setReadOnly(true);

        gridLayout_6->addWidget(LE_CI_HeadLink_Y, 2, 1, 1, 1);

        LE_CI_LinkCam_Y = new QLineEdit(layoutWidget1);
        LE_CI_LinkCam_Y->setObjectName(QStringLiteral("LE_CI_LinkCam_Y"));
        LE_CI_LinkCam_Y->setReadOnly(true);

        gridLayout_6->addWidget(LE_CI_LinkCam_Y, 2, 2, 1, 1);

        LE_CI_CamRC_Y = new QLineEdit(layoutWidget1);
        LE_CI_CamRC_Y->setObjectName(QStringLiteral("LE_CI_CamRC_Y"));
        LE_CI_CamRC_Y->setReadOnly(true);

        gridLayout_6->addWidget(LE_CI_CamRC_Y, 2, 3, 1, 1);

        LE_CI_CamPV_Y = new QLineEdit(layoutWidget1);
        LE_CI_CamPV_Y->setObjectName(QStringLiteral("LE_CI_CamPV_Y"));
        LE_CI_CamPV_Y->setReadOnly(true);

        gridLayout_6->addWidget(LE_CI_CamPV_Y, 2, 4, 1, 1);

        layoutWidget2 = new QWidget(groupBox_4);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 20, 241, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        L_CaseName = new QLabel(layoutWidget2);
        L_CaseName->setObjectName(QStringLiteral("L_CaseName"));

        horizontalLayout_3->addWidget(L_CaseName);

        LE_CaseName = new QLineEdit(layoutWidget2);
        LE_CaseName->setObjectName(QStringLiteral("LE_CaseName"));
        LE_CaseName->setReadOnly(true);

        horizontalLayout_3->addWidget(LE_CaseName);

        groupBox_5 = new QGroupBox(frame);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(2, 0, 481, 71));
        PB_SelectParameters = new QPushButton(groupBox_5);
        PB_SelectParameters->setObjectName(QStringLiteral("PB_SelectParameters"));
        PB_SelectParameters->setGeometry(QRect(400, 20, 75, 41));
        widget1 = new QWidget(groupBox_5);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 20, 384, 41));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        RB_OnlyOne = new QRadioButton(widget1);
        RB_OnlyOne->setObjectName(QStringLiteral("RB_OnlyOne"));
        RB_OnlyOne->setChecked(true);

        verticalLayout->addWidget(RB_OnlyOne);

        RB_SmallerThanFirst = new QRadioButton(widget1);
        RB_SmallerThanFirst->setObjectName(QStringLiteral("RB_SmallerThanFirst"));

        verticalLayout->addWidget(RB_SmallerThanFirst);

        TAB_MODELING->addTab(DesignTab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(2, 10, 480, 201));
        layoutWidget3 = new QWidget(groupBox);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 20, 461, 173));
        gridLayout_4 = new QGridLayout(layoutWidget3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        L_Head = new QLabel(layoutWidget3);
        L_Head->setObjectName(QStringLiteral("L_Head"));
        L_Head->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Head, 0, 1, 1, 1);

        L_Link = new QLabel(layoutWidget3);
        L_Link->setObjectName(QStringLiteral("L_Link"));
        L_Link->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Link, 0, 2, 1, 1);

        L_Cam = new QLabel(layoutWidget3);
        L_Cam->setObjectName(QStringLiteral("L_Cam"));
        L_Cam->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Cam, 0, 3, 1, 1);

        L_Passive = new QLabel(layoutWidget3);
        L_Passive->setObjectName(QStringLiteral("L_Passive"));
        L_Passive->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Passive, 0, 4, 1, 1);

        L_X = new QLabel(layoutWidget3);
        L_X->setObjectName(QStringLiteral("L_X"));
        L_X->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_X, 1, 0, 1, 1);

        LE_Head_X = new QLineEdit(layoutWidget3);
        LE_Head_X->setObjectName(QStringLiteral("LE_Head_X"));

        gridLayout_4->addWidget(LE_Head_X, 1, 1, 1, 1);

        LE_Link_X = new QLineEdit(layoutWidget3);
        LE_Link_X->setObjectName(QStringLiteral("LE_Link_X"));

        gridLayout_4->addWidget(LE_Link_X, 1, 2, 1, 1);

        LE_Cam_X = new QLineEdit(layoutWidget3);
        LE_Cam_X->setObjectName(QStringLiteral("LE_Cam_X"));

        gridLayout_4->addWidget(LE_Cam_X, 1, 3, 1, 1);

        LE_Passive_X = new QLineEdit(layoutWidget3);
        LE_Passive_X->setObjectName(QStringLiteral("LE_Passive_X"));

        gridLayout_4->addWidget(LE_Passive_X, 1, 4, 1, 1);

        L_Y = new QLabel(layoutWidget3);
        L_Y->setObjectName(QStringLiteral("L_Y"));
        L_Y->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Y, 2, 0, 1, 1);

        LE_Head_Y = new QLineEdit(layoutWidget3);
        LE_Head_Y->setObjectName(QStringLiteral("LE_Head_Y"));

        gridLayout_4->addWidget(LE_Head_Y, 2, 1, 1, 1);

        LE_Link_Y = new QLineEdit(layoutWidget3);
        LE_Link_Y->setObjectName(QStringLiteral("LE_Link_Y"));

        gridLayout_4->addWidget(LE_Link_Y, 2, 2, 1, 1);

        LE_Cam_Y = new QLineEdit(layoutWidget3);
        LE_Cam_Y->setObjectName(QStringLiteral("LE_Cam_Y"));

        gridLayout_4->addWidget(LE_Cam_Y, 2, 3, 1, 1);

        LE_Passive_Y = new QLineEdit(layoutWidget3);
        LE_Passive_Y->setObjectName(QStringLiteral("LE_Passive_Y"));

        gridLayout_4->addWidget(LE_Passive_Y, 2, 4, 1, 1);

        L_Angle = new QLabel(layoutWidget3);
        L_Angle->setObjectName(QStringLiteral("L_Angle"));
        L_Angle->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Angle, 3, 0, 1, 1);

        LE_Head_Angle = new QLineEdit(layoutWidget3);
        LE_Head_Angle->setObjectName(QStringLiteral("LE_Head_Angle"));

        gridLayout_4->addWidget(LE_Head_Angle, 3, 1, 1, 1);

        LE_Link_Angle = new QLineEdit(layoutWidget3);
        LE_Link_Angle->setObjectName(QStringLiteral("LE_Link_Angle"));

        gridLayout_4->addWidget(LE_Link_Angle, 3, 2, 1, 1);

        LE_Cam_Angle = new QLineEdit(layoutWidget3);
        LE_Cam_Angle->setObjectName(QStringLiteral("LE_Cam_Angle"));

        gridLayout_4->addWidget(LE_Cam_Angle, 3, 3, 1, 1);

        LE_Passive_Angle = new QLineEdit(layoutWidget3);
        LE_Passive_Angle->setObjectName(QStringLiteral("LE_Passive_Angle"));

        gridLayout_4->addWidget(LE_Passive_Angle, 3, 4, 1, 1);

        L_Mass = new QLabel(layoutWidget3);
        L_Mass->setObjectName(QStringLiteral("L_Mass"));
        L_Mass->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Mass, 4, 0, 1, 1);

        LE_Head_Mass = new QLineEdit(layoutWidget3);
        LE_Head_Mass->setObjectName(QStringLiteral("LE_Head_Mass"));

        gridLayout_4->addWidget(LE_Head_Mass, 4, 1, 1, 1);

        LE_Link_Mass = new QLineEdit(layoutWidget3);
        LE_Link_Mass->setObjectName(QStringLiteral("LE_Link_Mass"));

        gridLayout_4->addWidget(LE_Link_Mass, 4, 2, 1, 1);

        LE_Cam_Mass = new QLineEdit(layoutWidget3);
        LE_Cam_Mass->setObjectName(QStringLiteral("LE_Cam_Mass"));

        gridLayout_4->addWidget(LE_Cam_Mass, 4, 3, 1, 1);

        LE_Passive_Mass = new QLineEdit(layoutWidget3);
        LE_Passive_Mass->setObjectName(QStringLiteral("LE_Passive_Mass"));

        gridLayout_4->addWidget(LE_Passive_Mass, 4, 4, 1, 1);

        L_Inertai = new QLabel(layoutWidget3);
        L_Inertai->setObjectName(QStringLiteral("L_Inertai"));
        L_Inertai->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Inertai, 5, 0, 1, 1);

        LE_Head_Inertia = new QLineEdit(layoutWidget3);
        LE_Head_Inertia->setObjectName(QStringLiteral("LE_Head_Inertia"));

        gridLayout_4->addWidget(LE_Head_Inertia, 5, 1, 1, 1);

        LE_Link_Inertia = new QLineEdit(layoutWidget3);
        LE_Link_Inertia->setObjectName(QStringLiteral("LE_Link_Inertia"));

        gridLayout_4->addWidget(LE_Link_Inertia, 5, 2, 1, 1);

        LE_Cam_Inertia = new QLineEdit(layoutWidget3);
        LE_Cam_Inertia->setObjectName(QStringLiteral("LE_Cam_Inertia"));

        gridLayout_4->addWidget(LE_Cam_Inertia, 5, 3, 1, 1);

        LE_Passive_Inertia = new QLineEdit(layoutWidget3);
        LE_Passive_Inertia->setObjectName(QStringLiteral("LE_Passive_Inertia"));

        gridLayout_4->addWidget(LE_Passive_Inertia, 5, 4, 1, 1);

        L_Shape = new QLabel(layoutWidget3);
        L_Shape->setObjectName(QStringLiteral("L_Shape"));
        L_Shape->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(L_Shape, 6, 0, 1, 1);

        PB_HeadShape = new QPushButton(layoutWidget3);
        PB_HeadShape->setObjectName(QStringLiteral("PB_HeadShape"));

        gridLayout_4->addWidget(PB_HeadShape, 6, 1, 1, 1);

        PB_LinkShape = new QPushButton(layoutWidget3);
        PB_LinkShape->setObjectName(QStringLiteral("PB_LinkShape"));

        gridLayout_4->addWidget(PB_LinkShape, 6, 2, 1, 1);

        PB_CamShape = new QPushButton(layoutWidget3);
        PB_CamShape->setObjectName(QStringLiteral("PB_CamShape"));

        gridLayout_4->addWidget(PB_CamShape, 6, 3, 1, 1);

        PB_PassiveShape = new QPushButton(layoutWidget3);
        PB_PassiveShape->setObjectName(QStringLiteral("PB_PassiveShape"));

        gridLayout_4->addWidget(PB_PassiveShape, 6, 4, 1, 1);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(2, 219, 480, 95));
        L_H_L_X = new QLabel(groupBox_2);
        L_H_L_X->setObjectName(QStringLiteral("L_H_L_X"));
        L_H_L_X->setGeometry(QRect(107, 20, 21, 16));
        L_C_C_X = new QLabel(groupBox_2);
        L_C_C_X->setObjectName(QStringLiteral("L_C_C_X"));
        L_C_C_X->setGeometry(QRect(346, 20, 21, 16));
        L_C_C_Y = new QLabel(groupBox_2);
        L_C_C_Y->setObjectName(QStringLiteral("L_C_C_Y"));
        L_C_C_Y->setGeometry(QRect(428, 20, 21, 16));
        L_H_L_Y = new QLabel(groupBox_2);
        L_H_L_Y->setObjectName(QStringLiteral("L_H_L_Y"));
        L_H_L_Y->setGeometry(QRect(185, 20, 21, 16));
        layoutWidget4 = new QWidget(groupBox_2);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 37, 461, 48));
        gridLayout_3 = new QGridLayout(layoutWidget4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        L_HeadLink = new QLabel(layoutWidget4);
        L_HeadLink->setObjectName(QStringLiteral("L_HeadLink"));

        gridLayout_3->addWidget(L_HeadLink, 0, 0, 1, 1);

        LE_HeadLink_X = new QLineEdit(layoutWidget4);
        LE_HeadLink_X->setObjectName(QStringLiteral("LE_HeadLink_X"));

        gridLayout_3->addWidget(LE_HeadLink_X, 0, 1, 1, 1);

        LE_HeadLink_Y = new QLineEdit(layoutWidget4);
        LE_HeadLink_Y->setObjectName(QStringLiteral("LE_HeadLink_Y"));

        gridLayout_3->addWidget(LE_HeadLink_Y, 0, 2, 1, 1);

        L_CamGround = new QLabel(layoutWidget4);
        L_CamGround->setObjectName(QStringLiteral("L_CamGround"));

        gridLayout_3->addWidget(L_CamGround, 0, 3, 1, 1);

        LE_CamGround_X = new QLineEdit(layoutWidget4);
        LE_CamGround_X->setObjectName(QStringLiteral("LE_CamGround_X"));

        gridLayout_3->addWidget(LE_CamGround_X, 0, 4, 1, 1);

        LE_CamGround_Y = new QLineEdit(layoutWidget4);
        LE_CamGround_Y->setObjectName(QStringLiteral("LE_CamGround_Y"));

        gridLayout_3->addWidget(LE_CamGround_Y, 0, 5, 1, 1);

        L_LinkCam = new QLabel(layoutWidget4);
        L_LinkCam->setObjectName(QStringLiteral("L_LinkCam"));

        gridLayout_3->addWidget(L_LinkCam, 1, 0, 1, 1);

        LE_LinkCam_X = new QLineEdit(layoutWidget4);
        LE_LinkCam_X->setObjectName(QStringLiteral("LE_LinkCam_X"));

        gridLayout_3->addWidget(LE_LinkCam_X, 1, 1, 1, 1);

        LE_LinkCam_Y = new QLineEdit(layoutWidget4);
        LE_LinkCam_Y->setObjectName(QStringLiteral("LE_LinkCam_Y"));

        gridLayout_3->addWidget(LE_LinkCam_Y, 1, 2, 1, 1);

        L_Cam_Passive = new QLabel(layoutWidget4);
        L_Cam_Passive->setObjectName(QStringLiteral("L_Cam_Passive"));

        gridLayout_3->addWidget(L_Cam_Passive, 1, 3, 1, 1);

        LE_CamPassive_X = new QLineEdit(layoutWidget4);
        LE_CamPassive_X->setObjectName(QStringLiteral("LE_CamPassive_X"));

        gridLayout_3->addWidget(LE_CamPassive_X, 1, 4, 1, 1);

        LE_CamPassive_Y = new QLineEdit(layoutWidget4);
        LE_CamPassive_Y->setObjectName(QStringLiteral("LE_CamPassive_Y"));

        gridLayout_3->addWidget(LE_CamPassive_Y, 1, 5, 1, 1);

        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(2, 320, 181, 75));
        PB_ActiveVP = new QPushButton(groupBox_3);
        PB_ActiveVP->setObjectName(QStringLiteral("PB_ActiveVP"));
        PB_ActiveVP->setGeometry(QRect(10, 20, 161, 21));
        PB_PassivePV = new QPushButton(groupBox_3);
        PB_PassivePV->setObjectName(QStringLiteral("PB_PassivePV"));
        PB_PassivePV->setGeometry(QRect(10, 44, 161, 23));
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
        GB_DESIGN_VARIABLE->setTitle(QApplication::translate("DMotionClass", "Design variable", 0));
        L_LOWER->setText(QApplication::translate("DMotionClass", "Lower", 0));
        L_Step->setText(QApplication::translate("DMotionClass", "Step", 0));
        L_Upper->setText(QApplication::translate("DMotionClass", "Upper", 0));
        CB_HEADLINK_X->setText(QString());
        L_HEADLINK_X->setText(QApplication::translate("DMotionClass", "HeadLink(x)", 0));
        CB_HEADLINK_Y->setText(QString());
        L_HEADLINKCAM_Y->setText(QApplication::translate("DMotionClass", "HeadLink(y)", 0));
        CB_LINKCAM_X->setText(QString());
        L_LINKCAM_X->setText(QApplication::translate("DMotionClass", "LinkCam(x)", 0));
        CB_LINKCAM_Y->setText(QString());
        L_LINKCAM_Y->setText(QApplication::translate("DMotionClass", "LinkCam(y)", 0));
        CB_CAMRC_X->setText(QString());
        L_CAMRC_X->setText(QApplication::translate("DMotionClass", "CamRC(x)", 0));
        CB_CAMRC_Y->setText(QString());
        L_CAMRC_Y->setText(QApplication::translate("DMotionClass", "CamRC(y)", 0));
        CB_CAMPV_X->setText(QString());
        L_CAMPV_X->setText(QApplication::translate("DMotionClass", "CamPV(x)", 0));
        CB_CAMPV_Y->setText(QString());
        L_CAMPV_Y->setText(QApplication::translate("DMotionClass", "CamPV(y)", 0));
        L_CAMANGLE->setText(QApplication::translate("DMotionClass", "Cam angle", 0));
        groupBox_4->setTitle(QApplication::translate("DMotionClass", "Case information", 0));
        PB_SaveCase->setText(QApplication::translate("DMotionClass", "Save case ", 0));
        label->setText(QApplication::translate("DMotionClass", "HeadLink", 0));
        label_2->setText(QApplication::translate("DMotionClass", "LinkCam", 0));
        label_3->setText(QApplication::translate("DMotionClass", "CamRC", 0));
        label_4->setText(QApplication::translate("DMotionClass", "CamPV", 0));
        label_5->setText(QApplication::translate("DMotionClass", "X", 0));
        label_6->setText(QApplication::translate("DMotionClass", "Y", 0));
        L_CaseName->setText(QApplication::translate("DMotionClass", "Name", 0));
        groupBox_5->setTitle(QApplication::translate("DMotionClass", "Optimum condition", 0));
        PB_SelectParameters->setText(QApplication::translate("DMotionClass", "Select\n"
" parameters", 0));
        RB_OnlyOne->setText(QApplication::translate("DMotionClass", "Select only one", 0));
        RB_SmallerThanFirst->setText(QApplication::translate("DMotionClass", "Select smaller case than first", 0));
        TAB_MODELING->setTabText(TAB_MODELING->indexOf(DesignTab), QApplication::translate("DMotionClass", "Design", 0));
        groupBox->setTitle(QApplication::translate("DMotionClass", "Body information", 0));
        L_Head->setText(QApplication::translate("DMotionClass", "Head", 0));
        L_Link->setText(QApplication::translate("DMotionClass", "Link", 0));
        L_Cam->setText(QApplication::translate("DMotionClass", "Cam", 0));
        L_Passive->setText(QApplication::translate("DMotionClass", "Passive", 0));
        L_X->setText(QApplication::translate("DMotionClass", "X", 0));
        L_Y->setText(QApplication::translate("DMotionClass", "Y", 0));
        L_Angle->setText(QApplication::translate("DMotionClass", "Angle", 0));
        L_Mass->setText(QApplication::translate("DMotionClass", "Mass", 0));
        L_Inertai->setText(QApplication::translate("DMotionClass", "Inertia", 0));
        L_Shape->setText(QApplication::translate("DMotionClass", "Shape", 0));
        PB_HeadShape->setText(QApplication::translate("DMotionClass", "Head shpae", 0));
        PB_LinkShape->setText(QApplication::translate("DMotionClass", "Link shape", 0));
        PB_CamShape->setText(QApplication::translate("DMotionClass", "Cam shape", 0));
        PB_PassiveShape->setText(QApplication::translate("DMotionClass", "Passive shape", 0));
        groupBox_2->setTitle(QApplication::translate("DMotionClass", "Hard point", 0));
        L_H_L_X->setText(QApplication::translate("DMotionClass", "X", 0));
        L_C_C_X->setText(QApplication::translate("DMotionClass", "X", 0));
        L_C_C_Y->setText(QApplication::translate("DMotionClass", "Y", 0));
        L_H_L_Y->setText(QApplication::translate("DMotionClass", "Y", 0));
        L_HeadLink->setText(QApplication::translate("DMotionClass", "HeadLink", 0));
        L_CamGround->setText(QApplication::translate("DMotionClass", "CamGround", 0));
        L_LinkCam->setText(QApplication::translate("DMotionClass", "LinkCam", 0));
        L_Cam_Passive->setText(QApplication::translate("DMotionClass", "CamPassive", 0));
        groupBox_3->setTitle(QApplication::translate("DMotionClass", "Driving condition", 0));
        PB_ActiveVP->setText(QApplication::translate("DMotionClass", "Active velocity profile", 0));
        PB_PassivePV->setText(QApplication::translate("DMotionClass", "Passive velocity profile", 0));
        TAB_MODELING->setTabText(TAB_MODELING->indexOf(tab_2), QApplication::translate("DMotionClass", "Modeling", 0));
    } // retranslateUi

};

namespace Ui {
    class DMotionClass: public Ui_DMotionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DMOTIONN34344_H
