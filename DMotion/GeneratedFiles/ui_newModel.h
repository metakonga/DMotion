/********************************************************************************
** Form generated from reading UI file 'newModelh37264.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef NEWMODELH37264_H
#define NEWMODELH37264_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newModelDialog
{
public:
    QGroupBox *GBNewModel;
    QPushButton *PB_Create;
    QPushButton *PB_Browse;
    QPushButton *PB_Open;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *L_ModelType;
    QLabel *LName;
    QLabel *LUnit;
    QLabel *L_Directory;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *RB_NHCM;
    QRadioButton *RB_HCM;
    QLineEdit *LE_Name;
    QComboBox *CB_Unit;
    QLineEdit *LE_Directory;

    void setupUi(QDialog *newModelDialog)
    {
        if (newModelDialog->objectName().isEmpty())
            newModelDialog->setObjectName(QStringLiteral("newModelDialog"));
        newModelDialog->setWindowModality(Qt::ApplicationModal);
        newModelDialog->resize(500, 150);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(newModelDialog->sizePolicy().hasHeightForWidth());
        newModelDialog->setSizePolicy(sizePolicy);
        newModelDialog->setMinimumSize(QSize(500, 150));
        newModelDialog->setMaximumSize(QSize(500, 150));
        newModelDialog->setModal(true);
        GBNewModel = new QGroupBox(newModelDialog);
        GBNewModel->setObjectName(QStringLiteral("GBNewModel"));
        GBNewModel->setGeometry(QRect(10, 10, 481, 131));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        GBNewModel->setFont(font);
        GBNewModel->setAutoFillBackground(false);
        PB_Create = new QPushButton(GBNewModel);
        PB_Create->setObjectName(QStringLiteral("PB_Create"));
        PB_Create->setGeometry(QRect(400, 40, 75, 23));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        PB_Create->setFont(font1);
        PB_Browse = new QPushButton(GBNewModel);
        PB_Browse->setObjectName(QStringLiteral("PB_Browse"));
        PB_Browse->setGeometry(QRect(400, 94, 75, 24));
        PB_Browse->setFont(font1);
        PB_Open = new QPushButton(GBNewModel);
        PB_Open->setObjectName(QStringLiteral("PB_Open"));
        PB_Open->setGeometry(QRect(400, 67, 75, 23));
        PB_Open->setFont(font1);
        PB_Open->setStyleSheet(QStringLiteral("border-bottom-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 0, 0, 255), stop:0.339795 rgba(255, 0, 0, 255), stop:0.339799 rgba(255, 255, 255, 255), stop:0.662444 rgba(255, 255, 255, 255), stop:0.662469 rgba(0, 0, 255, 255), stop:1 rgba(0, 0, 255, 255));"));
        PB_Open->setFlat(false);
        widget = new QWidget(GBNewModel);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(15, 20, 55, 101));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 9);
        L_ModelType = new QLabel(widget);
        L_ModelType->setObjectName(QStringLiteral("L_ModelType"));

        verticalLayout->addWidget(L_ModelType);

        LName = new QLabel(widget);
        LName->setObjectName(QStringLiteral("LName"));

        verticalLayout->addWidget(LName);

        LUnit = new QLabel(widget);
        LUnit->setObjectName(QStringLiteral("LUnit"));

        verticalLayout->addWidget(LUnit);

        L_Directory = new QLabel(widget);
        L_Directory->setObjectName(QStringLiteral("L_Directory"));

        verticalLayout->addWidget(L_Directory);

        widget1 = new QWidget(GBNewModel);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(73, 20, 321, 98));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        RB_NHCM = new QRadioButton(widget1);
        RB_NHCM->setObjectName(QStringLiteral("RB_NHCM"));
        RB_NHCM->setChecked(true);

        horizontalLayout_2->addWidget(RB_NHCM);

        RB_HCM = new QRadioButton(widget1);
        RB_HCM->setObjectName(QStringLiteral("RB_HCM"));

        horizontalLayout_2->addWidget(RB_HCM);


        verticalLayout_2->addLayout(horizontalLayout_2);

        LE_Name = new QLineEdit(widget1);
        LE_Name->setObjectName(QStringLiteral("LE_Name"));

        verticalLayout_2->addWidget(LE_Name);

        CB_Unit = new QComboBox(widget1);
        CB_Unit->setObjectName(QStringLiteral("CB_Unit"));

        verticalLayout_2->addWidget(CB_Unit);

        LE_Directory = new QLineEdit(widget1);
        LE_Directory->setObjectName(QStringLiteral("LE_Directory"));

        verticalLayout_2->addWidget(LE_Directory);


        retranslateUi(newModelDialog);

        PB_Open->setDefault(false);


        QMetaObject::connectSlotsByName(newModelDialog);
    } // setupUi

    void retranslateUi(QDialog *newModelDialog)
    {
        newModelDialog->setWindowTitle(QApplication::translate("newModelDialog", "New Model", 0));
        GBNewModel->setTitle(QApplication::translate("newModelDialog", "New Model", 0));
        PB_Create->setText(QApplication::translate("newModelDialog", "Create", 0));
        PB_Browse->setText(QApplication::translate("newModelDialog", "Browse", 0));
        PB_Open->setText(QApplication::translate("newModelDialog", "Open", 0));
        L_ModelType->setText(QApplication::translate("newModelDialog", "Model", 0));
        LName->setText(QApplication::translate("newModelDialog", "Name", 0));
        LUnit->setText(QApplication::translate("newModelDialog", "Unit", 0));
        L_Directory->setText(QApplication::translate("newModelDialog", "Directory", 0));
        RB_NHCM->setText(QApplication::translate("newModelDialog", "No Hole Cam Model", 0));
        RB_HCM->setText(QApplication::translate("newModelDialog", "Hole Cam Model", 0));
        CB_Unit->clear();
        CB_Unit->insertItems(0, QStringList()
         << QApplication::translate("newModelDialog", "MMKS(Millimeter/Kilogram/Newton/Second)", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class newModelDialog: public Ui_newModelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // NEWMODELH37264_H
