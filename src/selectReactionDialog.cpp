#include "selectReactionDialog.h"
#include "optimumDesignDoc.h"
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>

selectReactionDialog::selectReactionDialog(optimumDesignDoc* _odd, QWidget* parent /* = NULL */)
	: QDialog(parent)
	, odd(_odd)
	, modelType(0)
{
	//setupUi(/*this*/);
}

selectReactionDialog::~selectReactionDialog()
{

}

void selectReactionDialog::setupUi(int mtype)
{
	modelType = mtype;
	setObjectName(QStringLiteral("DLG_SelectReaction"));
	//resize(130, 346);
	setWindowTitle("Comparison Reaction Selection Dialog");
	int yGeoPos = 10;
	GB_NozzleTrans = new QGroupBox(this);
	GB_NozzleTrans->setObjectName(QStringLiteral("GB_NozzleTrans"));
	GB_NozzleTrans->setTitle("Nozzle Trans.");
	GB_NozzleTrans->setGeometry(QRect(10, yGeoPos, 111, 46));
	yGeoPos += 50;
	checkMap[NOZZLE_TRANS_FY] = new QCheckBox(GB_NozzleTrans);
	checkMap[NOZZLE_TRANS_FY]->setObjectName(QStringLiteral("CH_AT_FY"));
	checkMap[NOZZLE_TRANS_FY]->setGeometry(QRect(10, 20, 51, 16));
	checkMap[NOZZLE_TRANS_FY]->setText("FY");

	checkMap[NOZZLE_TRANS_TR] = new QCheckBox(GB_NozzleTrans);
	checkMap[NOZZLE_TRANS_TR]->setObjectName(QStringLiteral("CH_AT_TR"));
	checkMap[NOZZLE_TRANS_TR]->setGeometry(QRect(60, 20, 51, 16));
	checkMap[NOZZLE_TRANS_TR]->setText("TR");

	GB_NozzleLinkRev = new QGroupBox(this);
	GB_NozzleLinkRev->setObjectName(QStringLiteral("GB_NozzleLinkRev"));
	GB_NozzleLinkRev->setGeometry(QRect(10, yGeoPos, 111, 46));
	GB_NozzleLinkRev->setTitle("Nozzle-Link Rev.");
	yGeoPos += 50;
	checkMap[NOZZLE_LINK_REV_FX] = new QCheckBox(GB_NozzleLinkRev);
	checkMap[NOZZLE_LINK_REV_FX]->setObjectName(QStringLiteral("CH_ALR_FX"));
	checkMap[NOZZLE_LINK_REV_FX]->setGeometry(QRect(10, 20, 51, 16));
	checkMap[NOZZLE_LINK_REV_FX]->setText("FX");

	checkMap[NOZZLE_LINK_REV_FY] = new QCheckBox(GB_NozzleLinkRev);
	checkMap[NOZZLE_LINK_REV_FY]->setObjectName(QStringLiteral("CH_ALR_FY"));
	checkMap[NOZZLE_LINK_REV_FY]->setGeometry(QRect(60, 20, 51, 16));
	checkMap[NOZZLE_LINK_REV_FY]->setText("FY");

	if (mtype == 1)
	{
		GB_LinkTrans = new QGroupBox(this);
		GB_LinkTrans->setObjectName(QStringLiteral("GB_LinkTrans"));
		GB_LinkTrans->setGeometry(QRect(10, yGeoPos, 111, 46));
		GB_LinkTrans->setTitle("Link_Vertical");
		yGeoPos += 50;
		checkMap[LINK_SIMPLE_FY] = new QCheckBox(GB_LinkTrans);
		checkMap[LINK_SIMPLE_FY]->setObjectName(QStringLiteral("CH_LV_FY"));
		checkMap[LINK_SIMPLE_FY]->setGeometry(QRect(10, 20, 51, 16));
		checkMap[LINK_SIMPLE_FY]->setText("FY");
	}

	GB_LinkCamOrLinkHingeRev = new QGroupBox(this);
	GB_LinkCamOrLinkHingeRev->setObjectName(QStringLiteral("GB_LinkCamOrLinkHingeRev"));
	GB_LinkCamOrLinkHingeRev->setGeometry(QRect(10, yGeoPos, 111, 46));
	if (mtype == 0)
	{
		GB_LinkCamOrLinkHingeRev->setTitle("Link-Cam Rev.");
		checkMap[LINK_CAM_REV_FX] = new QCheckBox(GB_LinkCamOrLinkHingeRev);
		checkMap[LINK_CAM_REV_FX]->setObjectName(QStringLiteral("CH_LCR_OR_LHR_FX"));
		checkMap[LINK_CAM_REV_FX]->setGeometry(QRect(10, 20, 51, 16));
		checkMap[LINK_CAM_REV_FX]->setText("FX");
		checkMap[LINK_CAM_REV_FY] = new QCheckBox(GB_LinkCamOrLinkHingeRev);
		checkMap[LINK_CAM_REV_FY]->setObjectName(QStringLiteral("CH_LCR_OR_LHR_FY"));
		checkMap[LINK_CAM_REV_FY]->setGeometry(QRect(60, 20, 51, 16));
		checkMap[LINK_CAM_REV_FY]->setText("FY");
	}
	else if (mtype == 1)
	{
		GB_LinkCamOrLinkHingeRev->setTitle("Link-Hinge Rev.");
		checkMap[LINK_HINGE_REV_FX] = new QCheckBox(GB_LinkCamOrLinkHingeRev);
		checkMap[LINK_HINGE_REV_FX]->setObjectName(QStringLiteral("CH_LCR_OR_LHR_FX"));
		checkMap[LINK_HINGE_REV_FX]->setGeometry(QRect(10, 20, 51, 16));
		checkMap[LINK_HINGE_REV_FX]->setText("FX");
		checkMap[LINK_HINGE_REV_FY] = new QCheckBox(GB_LinkCamOrLinkHingeRev);
		checkMap[LINK_HINGE_REV_FY]->setObjectName(QStringLiteral("CH_LCR_OR_LHR_FY"));
		checkMap[LINK_HINGE_REV_FY]->setGeometry(QRect(60, 20, 51, 16));
		checkMap[LINK_HINGE_REV_FY]->setText("FY");
	}		
	yGeoPos += 50;

	if (mtype == 1)
	{
		GB_MaybeHingeCamRev = new QGroupBox(this);
		GB_MaybeHingeCamRev->setObjectName(QStringLiteral("GB_MaybeHingeCamRev"));
		GB_MaybeHingeCamRev->setGeometry(QRect(10, yGeoPos, 111, 46));
		GB_MaybeHingeCamRev->setTitle("Hinge-Cam Rev.");
		yGeoPos += 50;
		checkMap[HINGE_CAM_REV_FX] = new QCheckBox(GB_MaybeHingeCamRev);
		checkMap[HINGE_CAM_REV_FX]->setObjectName(QStringLiteral("CH_HCR_FX"));
		checkMap[HINGE_CAM_REV_FX]->setGeometry(QRect(10, 20, 51, 16));
		checkMap[HINGE_CAM_REV_FX]->setText("FX");
		checkMap[HINGE_CAM_REV_FY] = new QCheckBox(GB_MaybeHingeCamRev);
		checkMap[HINGE_CAM_REV_FY]->setObjectName(QStringLiteral("CH_HCR_FY"));
		checkMap[HINGE_CAM_REV_FY]->setGeometry(QRect(60, 20, 51, 16));
		checkMap[HINGE_CAM_REV_FY]->setText("FY");
	}
	GB_CamGroundRev = new QGroupBox(this);
	GB_CamGroundRev->setObjectName(QStringLiteral("GB_CamGroundRev"));
	GB_CamGroundRev->setGeometry(QRect(10, yGeoPos, 111, 46));
	GB_CamGroundRev->setTitle("Cam-Ground Rev.");
	yGeoPos += 50;
	checkMap[CAM_GROUND_REV_FX] = new QCheckBox(GB_CamGroundRev);
	checkMap[CAM_GROUND_REV_FX]->setObjectName(QStringLiteral("CH_CGR_FX"));
	checkMap[CAM_GROUND_REV_FX]->setGeometry(QRect(10, 20, 51, 16));
	checkMap[CAM_GROUND_REV_FX]->setText("FX");
	checkMap[CAM_GROUND_REV_FY] = new QCheckBox(GB_CamGroundRev);
	checkMap[CAM_GROUND_REV_FY]->setObjectName(QStringLiteral("CH_CGR_FY"));
	checkMap[CAM_GROUND_REV_FY]->setGeometry(QRect(60, 20, 51, 16));
	checkMap[CAM_GROUND_REV_FY]->setText("FY");

// 	if (mtype == 1)
// 	{
// 		GB_ArcRollerRev = new QGroupBox(this);
// 		GB_ArcRollerRev->setObjectName(QStringLiteral("GB_CamRollerRev"));
// 		GB_ArcRollerRev->setGeometry(QRect(10, yGeoPos, 111, 46));
// 		GB_ArcRollerRev->setTitle("Arc_Roller Rev.");
// 		yGeoPos += 50;
// 		checkMap[ARC_ROLLER_REV_FX] = new QCheckBox(GB_ArcRollerRev);
// 		checkMap[ARC_ROLLER_REV_FX]->setObjectName(QStringLiteral("CH_ARR_FX"));
// 		checkMap[ARC_ROLLER_REV_FX]->setGeometry(QRect(10, 20, 51, 16));
// 		checkMap[ARC_ROLLER_REV_FX]->setText("FX");
// 		checkMap[ARC_ROLLER_REV_FY] = new QCheckBox(GB_ArcRollerRev);
// 		checkMap[ARC_ROLLER_REV_FY]->setObjectName(QStringLiteral("CH_ARR_FY"));
// 		checkMap[ARC_ROLLER_REV_FY]->setGeometry(QRect(60, 20, 51, 16));
// 		checkMap[ARC_ROLLER_REV_FY]->setText("FY");
// 	}

	GB_ArcTrans = new QGroupBox(this);
	GB_ArcTrans->setObjectName(QStringLiteral("GB_ArcTrans"));
	GB_ArcTrans->setGeometry(QRect(10, yGeoPos, 111, 46));
	GB_ArcTrans->setTitle("Arc Trans.");
	yGeoPos += 50;
	checkMap[mtype ? ARC_SIMPLE_FY : ARC_TRANS_FY] = new QCheckBox(GB_ArcTrans);
	checkMap[mtype ? ARC_SIMPLE_FY : ARC_TRANS_FY]->setObjectName(QStringLiteral("CH_PT_FY"));
	checkMap[mtype ? ARC_SIMPLE_FY : ARC_TRANS_FY]->setGeometry(QRect(10, 20, 51, 16));
	checkMap[mtype ? ARC_SIMPLE_FY : ARC_TRANS_FY]->setText("FY");
	checkMap[mtype ? ARC_SIMPLE_TR : ARC_TRANS_TR] = new QCheckBox(GB_ArcTrans);
	checkMap[mtype ? ARC_SIMPLE_TR : ARC_TRANS_TR]->setObjectName(QStringLiteral("CH_PT_TR"));
	checkMap[mtype ? ARC_SIMPLE_TR : ARC_TRANS_TR]->setGeometry(QRect(60, 20, 51, 16));
	checkMap[mtype ? ARC_SIMPLE_TR : ARC_TRANS_TR]->setText("TR");

	GB_Profile = new QGroupBox(this);
	GB_Profile->setObjectName(QStringLiteral("GB_Profile"));
	GB_Profile->setGeometry(QRect(10, yGeoPos, 111, 46));
	GB_Profile->setTitle("Arc-Cam PF");
	yGeoPos += 50;
	checkMap[PROFILE_FX] = new QCheckBox(GB_Profile);
	checkMap[PROFILE_FX]->setObjectName(QStringLiteral("CH_PF_FX"));
	checkMap[PROFILE_FX]->setGeometry(QRect(60, 20, 51, 16));
	checkMap[PROFILE_FX]->setText("FX");
	checkMap[PROFILE_FY] = new QCheckBox(GB_Profile);
	checkMap[PROFILE_FY]->setObjectName(QStringLiteral("CH_PF_FY"));
	checkMap[PROFILE_FY]->setGeometry(QRect(10, 20, 51, 16));
	checkMap[PROFILE_FY]->setText("FY");
	
	PB_Close = new QPushButton(this);
	PB_Close->setObjectName(QStringLiteral("PB_Close"));
	PB_Close->setText("Close");
	//yGeoPos += 50;
	PB_Close->setGeometry(QRect(10, yGeoPos, 111, 31));
	resize(130, yGeoPos + 35);
	connect(PB_Close, SIGNAL(clicked()), this, SLOT(pushClose()));
}

void selectReactionDialog::setCheck(reactionForceType type, int d)
{
	checkMap[type]->setChecked(d);
// 	if (type == "AT_FY")	CH_AT_FY->setChecked(d);
// 	if (type == "AT_TR")	CH_AT_TR->setChecked(d);
// 	if (type == "ALR_FX") CH_ALR_FX->setChecked(d);
// 	if (type == "ALR_FY") CH_ALR_FY->setChecked(d);
// 	if (type == "LHR_FX") CH_LCR_OR_LHR_FX->setChecked(d);
// 	if (type == "LHR_FY") CH_LCR_OR_LHR_FY->setChecked(d);
// 	if (type == "HCR_FX") CH_HCR_FX->setChecked(d);
// 	if (type == "HCR_FY") CH_HCR_FY->setChecked(d);
// 	if (type == "LCR_FX") CH_LCR_OR_LHR_FX->setChecked(d);
// 	if (type == "LCR_FY") CH_LCR_OR_LHR_FY->setChecked(d);
// 	if (type == "CGR_FX") CH_CGR_FX->setChecked(d);
// 	if (type == "CGR_FY") CH_CGR_FY->setChecked(d);
// 	if (type == "PF_FX")	CH_PF_FX->setChecked(d);
// 	if (type == "PF_FY")	CH_PF_FY->setChecked(d);
// 	if (type == "PT_FY")	CH_PT_FY->setChecked(d);
// 	if (type == "PT_TR")	CH_PT_TR->setChecked(d);
}

void selectReactionDialog::pushClose()
{
	odd->setSelectReaction(NOZZLE_TRANS_FY, checkMap[NOZZLE_TRANS_FY]->isChecked());
	odd->setSelectReaction(NOZZLE_TRANS_TR, checkMap[NOZZLE_TRANS_TR]->isChecked());

	odd->setSelectReaction(NOZZLE_LINK_REV_FX, checkMap[NOZZLE_LINK_REV_FX]->isChecked());
	odd->setSelectReaction(NOZZLE_LINK_REV_FY, checkMap[NOZZLE_LINK_REV_FY]->isChecked());

	if (modelType == 1)
	{
		odd->setSelectReaction(LINK_SIMPLE_FY, checkMap[LINK_SIMPLE_FY]->isChecked());
		odd->setSelectReaction(LINK_HINGE_REV_FX, checkMap[LINK_HINGE_REV_FX]->isChecked());
		odd->setSelectReaction(LINK_HINGE_REV_FY, checkMap[LINK_HINGE_REV_FY]->isChecked());

		odd->setSelectReaction(HINGE_CAM_REV_FX, checkMap[HINGE_CAM_REV_FX]->isChecked());
		odd->setSelectReaction(HINGE_CAM_REV_FY, checkMap[HINGE_CAM_REV_FY]->isChecked());

// 		odd->setSelectReaction(ARC_ROLLER_REV_FX, checkMap[ARC_ROLLER_REV_FX]->isChecked());
// 		odd->setSelectReaction(ARC_ROLLER_REV_FY, checkMap[ARC_ROLLER_REV_FY]->isChecked());
	}
	else if (modelType == 0)
	{
		odd->setSelectReaction(LINK_CAM_REV_FX, checkMap[LINK_CAM_REV_FX]->isChecked());
		odd->setSelectReaction(LINK_CAM_REV_FY, checkMap[LINK_CAM_REV_FY]->isChecked());
	}

	odd->setSelectReaction(CAM_GROUND_REV_FX, checkMap[CAM_GROUND_REV_FX]->isChecked());
	odd->setSelectReaction(CAM_GROUND_REV_FY, checkMap[CAM_GROUND_REV_FY]->isChecked());

	odd->setSelectReaction(!modelType ? ARC_TRANS_FY : ARC_SIMPLE_FY, checkMap[!modelType ? ARC_TRANS_FY : ARC_SIMPLE_FY]->isChecked());
	odd->setSelectReaction(!modelType ? ARC_TRANS_TR : ARC_SIMPLE_TR, checkMap[!modelType ? ARC_TRANS_FY : ARC_SIMPLE_TR]->isChecked());

	odd->setSelectReaction(PROFILE_FX, checkMap[PROFILE_FX]->isChecked());
	odd->setSelectReaction(PROFILE_FY, checkMap[PROFILE_FY]->isChecked());

	this->close();
}