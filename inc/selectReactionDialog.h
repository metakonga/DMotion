#ifndef SELECTREACTIONDIALOG_H
#define SELECTREACTIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QMap>
//#include "ui_selectReaction.h"
#include "dmotion_types.h"

QT_BEGIN_NAMESPACE
class QGroupBox;
class QCheckBox;
class QPushButton;
QT_END_NAMESPACE

class optimumDesignDoc;

class selectReactionDialog : public QDialog// , private Ui::DLG_SelectReaction
{
	Q_OBJECT

public:
	selectReactionDialog(optimumDesignDoc* _odd, QWidget* parent = NULL);
	~selectReactionDialog();

	void setCheck(reactionForceType type, int d);
	void setupUi(int mtype);

	private slots:
	void pushClose();

private:
	int modelType;
	QGroupBox *GB_NozzleTrans;
// 	QCheckBox *CH_AT_FY;
// 	QCheckBox *CH_AT_TR;
	QGroupBox *GB_NozzleLinkRev;
	QGroupBox *GB_LinkTrans;
// 	QCheckBox *CH_ALR_FX;
// 	QCheckBox *CH_ALR_FY;
	QGroupBox *GB_LinkCamOrLinkHingeRev;
// 	QCheckBox *CH_LCR_OR_LHR_FX;
// 	QCheckBox *CH_LCR_OR_LHR_FY;
	QGroupBox *GB_MaybeHingeCamRev;
// 	QCheckBox *CH_HCR_FX;
// 	QCheckBox *CH_HCR_FY;
	QGroupBox *GB_CamGroundRev;
	QGroupBox *GB_ArcRollerRev;
//	QCheckBox *CH_CGR_FX;
//	QCheckBox *CH_CGR_FY;
	QGroupBox *GB_ArcTrans;
//	QCheckBox *CH_PT_FY;
//	QCheckBox *CH_PT_TR;
	QGroupBox *GB_Profile;
// 	QCheckBox *CH_PF_FX;
// 	QCheckBox *CH_PF_FY;
	QPushButton *PB_Close;

	optimumDesignDoc *odd;

	QMap<reactionForceType, QCheckBox*> checkMap;
};


#endif