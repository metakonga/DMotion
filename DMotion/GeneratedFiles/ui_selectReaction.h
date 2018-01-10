/********************************************************************************
** Form generated from reading UI file 'selectReaction.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTREACTION_H
#define UI_SELECTREACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DLG_SelectReaction
{
public:
    QGroupBox *groupBox;
    QCheckBox *CH_AT_FY;
    QCheckBox *CH_AT_TR;
    QGroupBox *groupBox_2;
    QCheckBox *CH_ALR_FX;
    QCheckBox *CH_ALR_FY;
    QGroupBox *groupBox_3;
    QCheckBox *CH_LCR_FX;
    QCheckBox *CH_LCR_FY;
    QGroupBox *groupBox_4;
    QCheckBox *CH_PT_FY;
    QCheckBox *CH_PT_TR;
    QGroupBox *groupBox_5;
    QCheckBox *CH_CGR_FY;
    QCheckBox *CH_CGR_FX;
    QGroupBox *groupBox_6;
    QCheckBox *CH_PF_FY;
    QCheckBox *CH_PF_FX;
    QPushButton *PB_Close;

    void setupUi(QDialog *DLG_SelectReaction)
    {
        if (DLG_SelectReaction->objectName().isEmpty())
            DLG_SelectReaction->setObjectName(QStringLiteral("DLG_SelectReaction"));
        DLG_SelectReaction->resize(130, 346);
        groupBox = new QGroupBox(DLG_SelectReaction);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 111, 46));
        CH_AT_FY = new QCheckBox(groupBox);
        CH_AT_FY->setObjectName(QStringLiteral("CH_AT_FY"));
        CH_AT_FY->setGeometry(QRect(10, 20, 51, 16));
        CH_AT_TR = new QCheckBox(groupBox);
        CH_AT_TR->setObjectName(QStringLiteral("CH_AT_TR"));
        CH_AT_TR->setGeometry(QRect(60, 20, 51, 16));
        groupBox_2 = new QGroupBox(DLG_SelectReaction);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 60, 111, 46));
        CH_ALR_FX = new QCheckBox(groupBox_2);
        CH_ALR_FX->setObjectName(QStringLiteral("CH_ALR_FX"));
        CH_ALR_FX->setGeometry(QRect(10, 20, 51, 16));
        CH_ALR_FY = new QCheckBox(groupBox_2);
        CH_ALR_FY->setObjectName(QStringLiteral("CH_ALR_FY"));
        CH_ALR_FY->setGeometry(QRect(60, 20, 51, 16));
        groupBox_3 = new QGroupBox(DLG_SelectReaction);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 110, 111, 46));
        CH_LCR_FX = new QCheckBox(groupBox_3);
        CH_LCR_FX->setObjectName(QStringLiteral("CH_LCR_FX"));
        CH_LCR_FX->setGeometry(QRect(10, 20, 51, 16));
        CH_LCR_FY = new QCheckBox(groupBox_3);
        CH_LCR_FY->setObjectName(QStringLiteral("CH_LCR_FY"));
        CH_LCR_FY->setGeometry(QRect(60, 20, 51, 16));
        groupBox_4 = new QGroupBox(DLG_SelectReaction);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 260, 111, 46));
        CH_PT_FY = new QCheckBox(groupBox_4);
        CH_PT_FY->setObjectName(QStringLiteral("CH_PT_FY"));
        CH_PT_FY->setGeometry(QRect(10, 20, 51, 16));
        CH_PT_TR = new QCheckBox(groupBox_4);
        CH_PT_TR->setObjectName(QStringLiteral("CH_PT_TR"));
        CH_PT_TR->setGeometry(QRect(60, 20, 51, 16));
        groupBox_5 = new QGroupBox(DLG_SelectReaction);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 160, 111, 46));
        CH_CGR_FY = new QCheckBox(groupBox_5);
        CH_CGR_FY->setObjectName(QStringLiteral("CH_CGR_FY"));
        CH_CGR_FY->setGeometry(QRect(60, 20, 51, 16));
        CH_CGR_FX = new QCheckBox(groupBox_5);
        CH_CGR_FX->setObjectName(QStringLiteral("CH_CGR_FX"));
        CH_CGR_FX->setGeometry(QRect(10, 20, 51, 16));
        groupBox_6 = new QGroupBox(DLG_SelectReaction);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 210, 111, 46));
        CH_PF_FY = new QCheckBox(groupBox_6);
        CH_PF_FY->setObjectName(QStringLiteral("CH_PF_FY"));
        CH_PF_FY->setGeometry(QRect(60, 20, 51, 16));
        CH_PF_FX = new QCheckBox(groupBox_6);
        CH_PF_FX->setObjectName(QStringLiteral("CH_PF_FX"));
        CH_PF_FX->setGeometry(QRect(10, 20, 51, 16));
        PB_Close = new QPushButton(DLG_SelectReaction);
        PB_Close->setObjectName(QStringLiteral("PB_Close"));
        PB_Close->setGeometry(QRect(10, 310, 111, 31));

        retranslateUi(DLG_SelectReaction);

        QMetaObject::connectSlotsByName(DLG_SelectReaction);
    } // setupUi

    void retranslateUi(QDialog *DLG_SelectReaction)
    {
        DLG_SelectReaction->setWindowTitle(QApplication::translate("DLG_SelectReaction", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("DLG_SelectReaction", "Active trans.", 0));
        CH_AT_FY->setText(QApplication::translate("DLG_SelectReaction", "FY", 0));
        CH_AT_TR->setText(QApplication::translate("DLG_SelectReaction", "TR", 0));
        groupBox_2->setTitle(QApplication::translate("DLG_SelectReaction", "Active-Link rev.", 0));
        CH_ALR_FX->setText(QApplication::translate("DLG_SelectReaction", "FX", 0));
        CH_ALR_FY->setText(QApplication::translate("DLG_SelectReaction", "FY", 0));
        groupBox_3->setTitle(QApplication::translate("DLG_SelectReaction", "Link-Cam rev.", 0));
        CH_LCR_FX->setText(QApplication::translate("DLG_SelectReaction", "FX", 0));
        CH_LCR_FY->setText(QApplication::translate("DLG_SelectReaction", "FY", 0));
        groupBox_4->setTitle(QApplication::translate("DLG_SelectReaction", "Passive trans.", 0));
        CH_PT_FY->setText(QApplication::translate("DLG_SelectReaction", "FY", 0));
        CH_PT_TR->setText(QApplication::translate("DLG_SelectReaction", "TR", 0));
        groupBox_5->setTitle(QApplication::translate("DLG_SelectReaction", "Cam-Ground rev.", 0));
        CH_CGR_FY->setText(QApplication::translate("DLG_SelectReaction", "FY", 0));
        CH_CGR_FX->setText(QApplication::translate("DLG_SelectReaction", "FX", 0));
        groupBox_6->setTitle(QApplication::translate("DLG_SelectReaction", "Point follower", 0));
        CH_PF_FY->setText(QApplication::translate("DLG_SelectReaction", "FY", 0));
        CH_PF_FX->setText(QApplication::translate("DLG_SelectReaction", "FX", 0));
        PB_Close->setText(QApplication::translate("DLG_SelectReaction", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class DLG_SelectReaction: public Ui_DLG_SelectReaction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTREACTION_H
