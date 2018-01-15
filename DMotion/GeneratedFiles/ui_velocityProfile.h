/********************************************************************************
** Form generated from reading UI file 'velocityProfile.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VELOCITYPROFILE_H
#define UI_VELOCITYPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VP_Dialog
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *profileWidget;
    QGridLayout *gridLayout;
    QScrollArea *SA_Profile;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *GB_ProfileDisplay;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *RB_Stroke;
    QRadioButton *RB_Velocity;
    QRadioButton *RB_Acceleration;
    QWidget *resultWidget;
    QGridLayout *gridLayout_2;
    QScrollArea *SA_Result;
    QWidget *scrollAreaWidgetContents_2;
    QGroupBox *GB_ResultDisplay;
    QRadioButton *RB_RelativeVelocity;
    QRadioButton *RB_VelocityRatio;
    QComboBox *CB_SeriesList;
    QTableWidget *TB_Table;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *PB_Import;
    QPushButton *PB_Export;

    void setupUi(QDialog *VP_Dialog)
    {
        if (VP_Dialog->objectName().isEmpty())
            VP_Dialog->setObjectName(QStringLiteral("VP_Dialog"));
        VP_Dialog->resize(650, 780);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VP_Dialog->sizePolicy().hasHeightForWidth());
        VP_Dialog->setSizePolicy(sizePolicy);
        VP_Dialog->setMinimumSize(QSize(650, 780));
        VP_Dialog->setModal(false);
        gridLayout_3 = new QGridLayout(VP_Dialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(5);
        gridLayout_3->setVerticalSpacing(0);
        gridLayout_3->setContentsMargins(5, 5, 5, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        profileWidget = new QWidget(VP_Dialog);
        profileWidget->setObjectName(QStringLiteral("profileWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(profileWidget->sizePolicy().hasHeightForWidth());
        profileWidget->setSizePolicy(sizePolicy1);
        profileWidget->setMinimumSize(QSize(400, 300));
        gridLayout = new QGridLayout(profileWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        SA_Profile = new QScrollArea(profileWidget);
        SA_Profile->setObjectName(QStringLiteral("SA_Profile"));
        SA_Profile->setMinimumSize(QSize(400, 300));
        SA_Profile->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 401, 317));
        SA_Profile->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(SA_Profile, 0, 0, 1, 1);


        verticalLayout->addWidget(profileWidget);

        GB_ProfileDisplay = new QGroupBox(VP_Dialog);
        GB_ProfileDisplay->setObjectName(QStringLiteral("GB_ProfileDisplay"));
        GB_ProfileDisplay->setMinimumSize(QSize(300, 50));
        GB_ProfileDisplay->setMaximumSize(QSize(16777215, 50));
        layoutWidget = new QWidget(GB_ProfileDisplay);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 281, 18));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        RB_Stroke = new QRadioButton(layoutWidget);
        RB_Stroke->setObjectName(QStringLiteral("RB_Stroke"));
        RB_Stroke->setChecked(false);

        horizontalLayout->addWidget(RB_Stroke);

        RB_Velocity = new QRadioButton(layoutWidget);
        RB_Velocity->setObjectName(QStringLiteral("RB_Velocity"));
        RB_Velocity->setChecked(true);

        horizontalLayout->addWidget(RB_Velocity);

        RB_Acceleration = new QRadioButton(layoutWidget);
        RB_Acceleration->setObjectName(QStringLiteral("RB_Acceleration"));

        horizontalLayout->addWidget(RB_Acceleration);


        verticalLayout->addWidget(GB_ProfileDisplay);

        resultWidget = new QWidget(VP_Dialog);
        resultWidget->setObjectName(QStringLiteral("resultWidget"));
        sizePolicy1.setHeightForWidth(resultWidget->sizePolicy().hasHeightForWidth());
        resultWidget->setSizePolicy(sizePolicy1);
        resultWidget->setMinimumSize(QSize(300, 300));
        gridLayout_2 = new QGridLayout(resultWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        SA_Result = new QScrollArea(resultWidget);
        SA_Result->setObjectName(QStringLiteral("SA_Result"));
        SA_Result->setMinimumSize(QSize(400, 300));
        SA_Result->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 401, 317));
        SA_Result->setWidget(scrollAreaWidgetContents_2);

        gridLayout_2->addWidget(SA_Result, 0, 0, 1, 1);


        verticalLayout->addWidget(resultWidget);

        GB_ResultDisplay = new QGroupBox(VP_Dialog);
        GB_ResultDisplay->setObjectName(QStringLiteral("GB_ResultDisplay"));
        GB_ResultDisplay->setMinimumSize(QSize(300, 50));
        GB_ResultDisplay->setMaximumSize(QSize(16777215, 50));
        RB_RelativeVelocity = new QRadioButton(GB_ResultDisplay);
        RB_RelativeVelocity->setObjectName(QStringLiteral("RB_RelativeVelocity"));
        RB_RelativeVelocity->setGeometry(QRect(12, 22, 114, 16));
        RB_VelocityRatio = new QRadioButton(GB_ResultDisplay);
        RB_VelocityRatio->setObjectName(QStringLiteral("RB_VelocityRatio"));
        RB_VelocityRatio->setGeometry(QRect(190, 22, 121, 16));

        verticalLayout->addWidget(GB_ResultDisplay);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 3, 1);

        CB_SeriesList = new QComboBox(VP_Dialog);
        CB_SeriesList->setObjectName(QStringLiteral("CB_SeriesList"));
        CB_SeriesList->setMinimumSize(QSize(230, 20));
        CB_SeriesList->setMaximumSize(QSize(230, 20));

        gridLayout_3->addWidget(CB_SeriesList, 0, 1, 1, 1);

        TB_Table = new QTableWidget(VP_Dialog);
        TB_Table->setObjectName(QStringLiteral("TB_Table"));
        sizePolicy1.setHeightForWidth(TB_Table->sizePolicy().hasHeightForWidth());
        TB_Table->setSizePolicy(sizePolicy1);
        TB_Table->setMinimumSize(QSize(230, 660));
        TB_Table->setMaximumSize(QSize(230, 16777215));
        TB_Table->setSizeIncrement(QSize(210, 0));
        TB_Table->setSelectionMode(QAbstractItemView::SingleSelection);

        gridLayout_3->addWidget(TB_Table, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        PB_Import = new QPushButton(VP_Dialog);
        PB_Import->setObjectName(QStringLiteral("PB_Import"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(PB_Import->sizePolicy().hasHeightForWidth());
        PB_Import->setSizePolicy(sizePolicy2);
        PB_Import->setMinimumSize(QSize(110, 35));
        PB_Import->setMaximumSize(QSize(110, 35));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(16);
        PB_Import->setFont(font);

        horizontalLayout_2->addWidget(PB_Import);

        PB_Export = new QPushButton(VP_Dialog);
        PB_Export->setObjectName(QStringLiteral("PB_Export"));
        sizePolicy2.setHeightForWidth(PB_Export->sizePolicy().hasHeightForWidth());
        PB_Export->setSizePolicy(sizePolicy2);
        PB_Export->setMinimumSize(QSize(110, 35));
        PB_Export->setMaximumSize(QSize(110, 35));
        PB_Export->setFont(font);

        horizontalLayout_2->addWidget(PB_Export);


        gridLayout_3->addLayout(horizontalLayout_2, 2, 1, 1, 1);


        retranslateUi(VP_Dialog);

        QMetaObject::connectSlotsByName(VP_Dialog);
    } // setupUi

    void retranslateUi(QDialog *VP_Dialog)
    {
        VP_Dialog->setWindowTitle(QApplication::translate("VP_Dialog", "Velocity profile", Q_NULLPTR));
        GB_ProfileDisplay->setTitle(QApplication::translate("VP_Dialog", "Profile Display", Q_NULLPTR));
        RB_Stroke->setText(QApplication::translate("VP_Dialog", "Stroke", Q_NULLPTR));
        RB_Velocity->setText(QApplication::translate("VP_Dialog", "Velocity", Q_NULLPTR));
        RB_Acceleration->setText(QApplication::translate("VP_Dialog", "Acceleration", Q_NULLPTR));
        GB_ResultDisplay->setTitle(QApplication::translate("VP_Dialog", "Result Display", Q_NULLPTR));
        RB_RelativeVelocity->setText(QApplication::translate("VP_Dialog", "Relative velocity", Q_NULLPTR));
        RB_VelocityRatio->setText(QApplication::translate("VP_Dialog", "Velocity ratio", Q_NULLPTR));
        PB_Import->setText(QApplication::translate("VP_Dialog", "Import", Q_NULLPTR));
        PB_Export->setText(QApplication::translate("VP_Dialog", "Export", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VP_Dialog: public Ui_VP_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VELOCITYPROFILE_H
