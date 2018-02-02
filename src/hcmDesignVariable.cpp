#include "hcmDesignVariable.h"
#include "model.h"
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>

hcmDesignVariable::hcmDesignVariable(QFrame *frame)
	: QWidget(frame)
{
	GB_DESIGN_VARIABLE = new QGroupBox(frame);
	GB_DESIGN_VARIABLE->setObjectName(QStringLiteral("GB_DESIGN_VARIABLE"));
	GB_DESIGN_VARIABLE->setTitle("Design variable");
	GB_DESIGN_VARIABLE->setGeometry(QRect(2, 135, 480, 330));
	layoutWidget = new QWidget(GB_DESIGN_VARIABLE);
	layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
	layoutWidget->setGeometry(QRect(110, 21, 361, 16));
	setObjectName(QStringLiteral("NHCM_layoutWidget"));
	setGeometry(QRect(10, 110, 461, 230));
	horizontalLayout = new QHBoxLayout(layoutWidget);
	horizontalLayout->setSpacing(6);
	horizontalLayout->setContentsMargins(11, 11, 11, 11);
	horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
	horizontalLayout->setContentsMargins(0, 0, 0, 0);

	L_LOWER = new QLabel(layoutWidget);
	L_LOWER->setText("Lower");
	L_LOWER->setObjectName(QStringLiteral("L_LOWER"));
	L_LOWER->setAlignment(Qt::AlignCenter);

	horizontalLayout->addWidget(L_LOWER);

	L_Step = new QLabel(layoutWidget);
	L_Step->setText("Step");
	L_Step->setObjectName(QStringLiteral("L_Step"));
	L_Step->setAlignment(Qt::AlignCenter);

	horizontalLayout->addWidget(L_Step);

	L_Upper = new QLabel(layoutWidget);
	L_Upper->setText("Upper");
	L_Upper->setObjectName(QStringLiteral("L_Upper"));
	L_Upper->setAlignment(Qt::AlignCenter);

	horizontalLayout->addWidget(L_Upper);

	layoutWidget_2 = new QWidget(GB_DESIGN_VARIABLE);
	layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
	layoutWidget_2->setGeometry(QRect(10, 45, 461, 280));
	gridLayout_2 = new QGridLayout(layoutWidget_2);
	gridLayout_2->setSpacing(6);
	gridLayout_2->setContentsMargins(11, 6, 11, 6);
	gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
	gridLayout_2->setContentsMargins(0, 0, 0, 0);
	CB_HEADLINK_X = new QCheckBox(layoutWidget_2);
	CB_HEADLINK_X->setObjectName(QStringLiteral("CB_HEADLINK_X"));
	CB_HEADLINK_X->setText("Nozzle-Link(X)");
	CB_HEADLINK_X->setChecked(true);

	gridLayout_2->addWidget(CB_HEADLINK_X, 0, 0, 1, 1);

	LE_HEADLINK_LOWER_X = new QLineEdit(layoutWidget_2);
	LE_HEADLINK_LOWER_X->setObjectName(QStringLiteral("LE_HEADLINK_LOWER_X"));

	gridLayout_2->addWidget(LE_HEADLINK_LOWER_X, 0, 1, 1, 1);

	LE_HEADLINK_STEP_X = new QLineEdit(layoutWidget_2);
	LE_HEADLINK_STEP_X->setObjectName(QStringLiteral("LE_HEADLINK_STEP_X"));

	gridLayout_2->addWidget(LE_HEADLINK_STEP_X, 0, 2, 1, 1);

	LE_HEADLINK_UPPER_X = new QLineEdit(layoutWidget_2);
	LE_HEADLINK_UPPER_X->setObjectName(QStringLiteral("LE_HEADLINK_UPPER_X"));

	gridLayout_2->addWidget(LE_HEADLINK_UPPER_X, 0, 3, 1, 1);

	CB_HEADLINK_Y = new QCheckBox(layoutWidget_2);
	CB_HEADLINK_Y->setText("Nozzle-Link(Y)");
	CB_HEADLINK_Y->setObjectName(QStringLiteral("CB_HEADLINK_Y"));
	CB_HEADLINK_Y->setChecked(true);

	gridLayout_2->addWidget(CB_HEADLINK_Y, 1, 0, 1, 1);

	// 	L_HEADLINKCAM_Y = new QLabel(layoutWidget_2);
	// 	L_HEADLINKCAM_Y->setObjectName(QStringLiteral("L_HEADLINKCAM_Y"));
	// 
	// 	gridLayout_2->addWidget(L_HEADLINKCAM_Y, 1, 1, 1, 1);

	LE_HEADLINK_LOWER_Y = new QLineEdit(layoutWidget_2);
	LE_HEADLINK_LOWER_Y->setObjectName(QStringLiteral("LE_HEADLINK_LOWER_Y"));

	gridLayout_2->addWidget(LE_HEADLINK_LOWER_Y, 1, 1, 1, 1);

	LE_HEADLINK_STEP_Y = new QLineEdit(layoutWidget_2);
	LE_HEADLINK_STEP_Y->setObjectName(QStringLiteral("LE_HEADLINK_STEP_Y"));

	gridLayout_2->addWidget(LE_HEADLINK_STEP_Y, 1, 2, 1, 1);

	LE_HEADLINK_UPPER_Y = new QLineEdit(layoutWidget_2);
	LE_HEADLINK_UPPER_Y->setObjectName(QStringLiteral("LE_HEADLINK_UPPER_Y"));

	gridLayout_2->addWidget(LE_HEADLINK_UPPER_Y, 1, 3, 1, 1);

	CB_LINKHINGE_X = new QCheckBox(layoutWidget_2);
	CB_LINKHINGE_X->setText("Link-Hinge(X)");
	CB_LINKHINGE_X->setObjectName(QStringLiteral("CB_LINKHINGE_X"));
	CB_LINKHINGE_X->setChecked(true);

	gridLayout_2->addWidget(CB_LINKHINGE_X, 2, 0, 1, 1);

	// 	L_LINKCAM_X = new QLabel(layoutWidget_2);
	// 	L_LINKCAM_X->setObjectName(QStringLiteral("L_LINKCAM_X"));
	// 
	// 	gridLayout_2->addWidget(L_LINKCAM_X, 2, 1, 1, 1);

	LE_LINKHINGE_LOWER_X = new QLineEdit(layoutWidget_2);
	LE_LINKHINGE_LOWER_X->setObjectName(QStringLiteral("LE_LINKHINGE_LOWER_X"));

	gridLayout_2->addWidget(LE_LINKHINGE_LOWER_X, 2, 1, 1, 1);

	LE_LINKHINGE_STEP_X = new QLineEdit(layoutWidget_2);
	LE_LINKHINGE_STEP_X->setObjectName(QStringLiteral("LE_LINKHINGE_STEP_X"));

	gridLayout_2->addWidget(LE_LINKHINGE_STEP_X, 2, 2, 1, 1);

	LE_LINKHINGE_UPPER_X = new QLineEdit(layoutWidget_2);
	LE_LINKHINGE_UPPER_X->setObjectName(QStringLiteral("LE_LINKHINGE_UPPER_X"));

	gridLayout_2->addWidget(LE_LINKHINGE_UPPER_X, 2, 3, 1, 1);

	CB_LINKHINGE_Y = new QCheckBox(layoutWidget_2);
	CB_LINKHINGE_Y->setText("Link-Hinge(Y)");
	CB_LINKHINGE_Y->setObjectName(QStringLiteral("CB_LINKHINGE_Y"));
	CB_LINKHINGE_Y->setChecked(true);

	gridLayout_2->addWidget(CB_LINKHINGE_Y, 3, 0, 1, 1);

	// 	L_LINKHINGE_Y = new QLabel(layoutWidget_2);
	// 	L_LINKHINGE_Y->setObjectName(QStringLiteral("L_LINKHINGE_Y"));
	// 
	// 	gridLayout_2->addWidget(L_LINKHINGE_Y, 3, 1, 1, 1);

	LE_LINKHINGE_LOWER_Y = new QLineEdit(layoutWidget_2);
	LE_LINKHINGE_LOWER_Y->setObjectName(QStringLiteral("LE_LINKHINGE_LOWER_Y"));

	gridLayout_2->addWidget(LE_LINKHINGE_LOWER_Y, 3, 1, 1, 1);

	LE_LINKHINGE_STEP_Y = new QLineEdit(layoutWidget_2);
	LE_LINKHINGE_STEP_Y->setObjectName(QStringLiteral("LE_LINKHINGE_STEP_Y"));

	gridLayout_2->addWidget(LE_LINKHINGE_STEP_Y, 3, 2, 1, 1);

	LE_LINKHINGE_UPPER_Y = new QLineEdit(layoutWidget_2);
	LE_LINKHINGE_UPPER_Y->setObjectName(QStringLiteral("LE_LINKHINGE_UPPER_Y"));

	gridLayout_2->addWidget(LE_LINKHINGE_UPPER_Y, 3, 3, 1, 1);

	CB_HINGECAM_X = new QCheckBox(layoutWidget_2);
	CB_HINGECAM_X->setText("Hinge-Cam(X)");
	CB_HINGECAM_X->setObjectName(QStringLiteral("CB_HINGECAM_X"));
	CB_HINGECAM_X->setChecked(true);

	gridLayout_2->addWidget(CB_HINGECAM_X, 4, 0, 1, 1);

	// 	L_LINKCAM_X = new QLabel(layoutWidget_2);
	// 	L_LINKCAM_X->setObjectName(QStringLiteral("L_LINKCAM_X"));
	// 
	// 	gridLayout_2->addWidget(L_LINKCAM_X, 2, 1, 1, 1);

	LE_HINGECAM_LOWER_X = new QLineEdit(layoutWidget_2);
	LE_HINGECAM_LOWER_X->setObjectName(QStringLiteral("LE_HINGECAM_LOWER_X"));

	gridLayout_2->addWidget(LE_HINGECAM_LOWER_X, 4, 1, 1, 1);

	LE_HINGECAM_STEP_X = new QLineEdit(layoutWidget_2);
	LE_HINGECAM_STEP_X->setObjectName(QStringLiteral("LE_HINGECAM_STEP_X"));

	gridLayout_2->addWidget(LE_HINGECAM_STEP_X, 4, 2, 1, 1);

	LE_HINGECAM_UPPER_X = new QLineEdit(layoutWidget_2);
	LE_HINGECAM_UPPER_X->setObjectName(QStringLiteral("LE_HINGECAM_UPPER_X"));

	gridLayout_2->addWidget(LE_HINGECAM_UPPER_X, 4, 3, 1, 1);

	CB_HINGECAM_Y = new QCheckBox(layoutWidget_2);
	CB_HINGECAM_Y->setText("Hinge-Cam(Y)");
	CB_HINGECAM_Y->setObjectName(QStringLiteral("CB_HINGECAM_Y"));
	CB_HINGECAM_Y->setChecked(true);

	gridLayout_2->addWidget(CB_HINGECAM_Y, 5, 0, 1, 1);

	// 	L_HINGECAM_Y = new QLabel(layoutWidget_2);
	// 	L_HINGECAM_Y->setObjectName(QStringLiteral("L_HINGECAM_Y"));
	// 
	// 	gridLayout_2->addWidget(L_HINGECAM_Y, 3, 1, 1, 1);

	LE_HINGECAM_LOWER_Y = new QLineEdit(layoutWidget_2);
	LE_HINGECAM_LOWER_Y->setObjectName(QStringLiteral("LE_HINGECAM_LOWER_Y"));

	gridLayout_2->addWidget(LE_HINGECAM_LOWER_Y, 5, 1, 1, 1);

	LE_HINGECAM_STEP_Y = new QLineEdit(layoutWidget_2);
	LE_HINGECAM_STEP_Y->setObjectName(QStringLiteral("LE_HINGECAM_STEP_Y"));

	gridLayout_2->addWidget(LE_HINGECAM_STEP_Y, 5, 2, 1, 1);

	LE_HINGECAM_UPPER_Y = new QLineEdit(layoutWidget_2);
	LE_HINGECAM_UPPER_Y->setObjectName(QStringLiteral("LE_HINGECAM_UPPER_Y"));

	gridLayout_2->addWidget(LE_HINGECAM_UPPER_Y, 5, 3, 1, 1);


	CB_CAMRC_X = new QCheckBox(layoutWidget_2);
	CB_CAMRC_X->setText("Cam-Ground(X)");
	CB_CAMRC_X->setObjectName(QStringLiteral("CB_CAMRC_X"));
	CB_CAMRC_X->setChecked(true);

	gridLayout_2->addWidget(CB_CAMRC_X, 6, 0, 1, 1);

	// 	L_CAMRC_X = new QLabel(layoutWidget_2);
	// 	L_CAMRC_X->setObjectName(QStringLiteral("L_CAMRC_X"));
	// 
	// 	gridLayout_2->addWidget(L_CAMRC_X, 4, 1, 1, 1);

	LE_CAMRC_LOWER_X = new QLineEdit(layoutWidget_2);
	LE_CAMRC_LOWER_X->setObjectName(QStringLiteral("LE_CAMRC_LOWER_X"));

	gridLayout_2->addWidget(LE_CAMRC_LOWER_X, 6, 1, 1, 1);

	LE_CAMRC_STEP_X = new QLineEdit(layoutWidget_2);
	LE_CAMRC_STEP_X->setObjectName(QStringLiteral("LE_CAMRC_STEP_X"));

	gridLayout_2->addWidget(LE_CAMRC_STEP_X, 6, 2, 1, 1);

	LE_CAMRC_UPPER_X = new QLineEdit(layoutWidget_2);
	LE_CAMRC_UPPER_X->setObjectName(QStringLiteral("LE_CAMRC_UPPER_X"));

	gridLayout_2->addWidget(LE_CAMRC_UPPER_X, 6, 3, 1, 1);

	CB_CAMRC_Y = new QCheckBox(layoutWidget_2);
	CB_CAMRC_Y->setText("Cam-Ground(Y)");
	CB_CAMRC_Y->setObjectName(QStringLiteral("CB_CAMRC_Y"));
	CB_CAMRC_Y->setChecked(true);

	gridLayout_2->addWidget(CB_CAMRC_Y, 7, 0, 1, 1);

	// 	L_CAMRC_Y = new QLabel(layoutWidget_2);
	// 	L_CAMRC_Y->setObjectName(QStringLiteral("L_CAMRC_Y"));
	// 
	// 	gridLayout_2->addWidget(L_CAMRC_Y, 5, 1, 1, 1);

	LE_CAMRC_LOWER_Y = new QLineEdit(layoutWidget_2);
	LE_CAMRC_LOWER_Y->setObjectName(QStringLiteral("LE_CAMRC_LOWER_Y"));

	gridLayout_2->addWidget(LE_CAMRC_LOWER_Y, 7, 1, 1, 1);

	LE_CAMRC_STEP_Y = new QLineEdit(layoutWidget_2);
	LE_CAMRC_STEP_Y->setObjectName(QStringLiteral("LE_CAMRC_STEP_Y"));

	gridLayout_2->addWidget(LE_CAMRC_STEP_Y, 7, 2, 1, 1);

	LE_CAMRC_UPPER_Y = new QLineEdit(layoutWidget_2);
	LE_CAMRC_UPPER_Y->setObjectName(QStringLiteral("LE_CAMRC_UPPER_Y"));

	gridLayout_2->addWidget(LE_CAMRC_UPPER_Y, 7, 3, 1, 1);

	CB_CAMPV_X = new QCheckBox(layoutWidget_2);
	CB_CAMPV_X->setText("Arc-Cam(X)");
	CB_CAMPV_X->setObjectName(QStringLiteral("CB_CAMPV_X"));
	CB_CAMPV_X->setChecked(true);

	gridLayout_2->addWidget(CB_CAMPV_X, 8, 0, 1, 1);

	// 	L_CAMPV_X = new QLabel(layoutWidget_2);
	// 	L_CAMPV_X->setObjectName(QStringLiteral("L_CAMPV_X"));
	// 
	// 	gridLayout_2->addWidget(L_CAMPV_X, 6, 1, 1, 1);

	LE_CAMPV_LOWER_X = new QLineEdit(layoutWidget_2);
	LE_CAMPV_LOWER_X->setObjectName(QStringLiteral("LE_CAMPV_LOWER_X"));

	gridLayout_2->addWidget(LE_CAMPV_LOWER_X, 8, 1, 1, 1);

	LE_CAMPV_STEP_X = new QLineEdit(layoutWidget_2);
	LE_CAMPV_STEP_X->setObjectName(QStringLiteral("LE_CAMPV_STEP_X"));

	gridLayout_2->addWidget(LE_CAMPV_STEP_X, 8, 2, 1, 1);

	LE_CAMPV_UPPER_X = new QLineEdit(layoutWidget_2);
	LE_CAMPV_UPPER_X->setObjectName(QStringLiteral("LE_CAMPV_UPPER_X"));

	gridLayout_2->addWidget(LE_CAMPV_UPPER_X, 8, 3, 1, 1);

	CB_CAMPV_Y = new QCheckBox(layoutWidget_2);
	CB_CAMPV_Y->setText("Arc-Cam(Y)");
	CB_CAMPV_Y->setObjectName(QStringLiteral("CB_CAMPV_Y"));
	CB_CAMPV_Y->setChecked(true);

	gridLayout_2->addWidget(CB_CAMPV_Y, 9, 0, 1, 1);

	// 	L_CAMPV_Y = new QLabel(layoutWidget_2);
	// 	L_CAMPV_Y->setObjectName(QStringLiteral("L_CAMPV_Y"));
	// 
	// 	gridLayout_2->addWidget(L_CAMPV_Y, 7, 1, 1, 1);

	LE_CAMPV_LOWER_Y = new QLineEdit(layoutWidget_2);
	LE_CAMPV_LOWER_Y->setObjectName(QStringLiteral("LE_CAMPV_LOWER_Y"));

	gridLayout_2->addWidget(LE_CAMPV_LOWER_Y, 9, 1, 1, 1);

	LE_CAMPV_STEP_Y = new QLineEdit(layoutWidget_2);
	LE_CAMPV_STEP_Y->setObjectName(QStringLiteral("LE_CAMPV_STEP_Y"));

	gridLayout_2->addWidget(LE_CAMPV_STEP_Y, 9, 2, 1, 1);

	LE_CAMPV_UPPER_Y = new QLineEdit(layoutWidget_2);
	LE_CAMPV_UPPER_Y->setObjectName(QStringLiteral("LE_CAMPV_UPPER_Y"));

	gridLayout_2->addWidget(LE_CAMPV_UPPER_Y, 9, 3, 1, 1);

	CB_CAMANGLE = new QCheckBox(layoutWidget_2);
	CB_CAMANGLE->setText("Initial angle");
	CB_CAMANGLE->setObjectName(QStringLiteral("CB_INITANGLE"));
	CB_CAMANGLE->setChecked(true);

	gridLayout_2->addWidget(CB_CAMANGLE, 10, 0, 1, 1);

	// 	L_CAMANGLE = new QLabel(layoutWidget_2);
	// 	L_CAMANGLE->setObjectName(QStringLiteral("L_CAMANGLE"));
	// 
	// 	gridLayout_2->addWidget(L_CAMANGLE, 8, 1, 1, 1);

	LE_INITIAL_ANGLE_Lower = new QLineEdit(layoutWidget_2);
	LE_INITIAL_ANGLE_Lower->setObjectName(QStringLiteral("LE_INITIAL_ANGLE_Lower"));

	gridLayout_2->addWidget(LE_INITIAL_ANGLE_Lower, 10, 1, 1, 1);

	LE_INITIAL_ANGLE_Upper = new QLineEdit(layoutWidget_2);
	LE_INITIAL_ANGLE_Upper->setObjectName(QStringLiteral("LE_INITIAL_ANGLE_Upper"));

	gridLayout_2->addWidget(LE_INITIAL_ANGLE_Upper, 10, 3, 1, 1);

	CB_LASTANGLE = new QCheckBox(layoutWidget_2);
	CB_LASTANGLE->setText("Last angle");
	CB_LASTANGLE->setObjectName(QStringLiteral("CB_LASTANGLE"));
	CB_LASTANGLE->setChecked(true);

	gridLayout_2->addWidget(CB_LASTANGLE, 11, 0, 1, 1);

	LE_LAST_ANGLE_Lower = new QLineEdit(layoutWidget_2);
	LE_LAST_ANGLE_Lower->setObjectName(QStringLiteral("LE_LAST_ANGLE_Lower"));

	gridLayout_2->addWidget(LE_LAST_ANGLE_Lower, 11, 1, 1, 1);

	LE_LAST_ANGLE_Upper = new QLineEdit(layoutWidget_2);
	LE_LAST_ANGLE_Upper->setObjectName(QStringLiteral("LE_LAST_ANGLE_Upper"));

	gridLayout_2->addWidget(LE_LAST_ANGLE_Upper, 11, 3, 1, 1);
}

hcmDesignVariable::~hcmDesignVariable()
{

}

void hcmDesignVariable::setInitValue()
{
	LE_HEADLINK_LOWER_X->setText("-20");
	LE_HEADLINK_STEP_X->setText("1");
	LE_HEADLINK_UPPER_X->setText("20");

	LE_HEADLINK_LOWER_Y->setText("-20");
	LE_HEADLINK_STEP_Y->setText("1");
	LE_HEADLINK_UPPER_Y->setText("20");

	LE_LINKHINGE_LOWER_X->setText("-20");
	LE_LINKHINGE_STEP_X->setText("1");
	LE_LINKHINGE_UPPER_X->setText("20");

	LE_LINKHINGE_LOWER_Y->setText("-20");
	LE_LINKHINGE_STEP_Y->setText("1");
	LE_LINKHINGE_UPPER_Y->setText("20");

	LE_HINGECAM_LOWER_X->setText("-20");
	LE_HINGECAM_STEP_X->setText("1");
	LE_HINGECAM_UPPER_X->setText("20");

	LE_HINGECAM_LOWER_Y->setText("-20");
	LE_HINGECAM_STEP_Y->setText("1");
	LE_HINGECAM_UPPER_Y->setText("20");

	LE_CAMRC_LOWER_X->setText("-20");
	LE_CAMRC_STEP_X->setText("1");
	LE_CAMRC_UPPER_X->setText("20");

	LE_CAMRC_LOWER_Y->setText("-20");
	LE_CAMRC_STEP_Y->setText("1");
	LE_CAMRC_UPPER_Y->setText("20");

	LE_CAMPV_LOWER_X->setText("-20");
	LE_CAMPV_STEP_X->setText("1");
	LE_CAMPV_UPPER_X->setText("20");

	LE_CAMPV_LOWER_Y->setText("-20");
	LE_CAMPV_STEP_Y->setText("1");
	LE_CAMPV_UPPER_Y->setText("20");

	LE_INITIAL_ANGLE_Lower->setText("40.0");
	LE_INITIAL_ANGLE_Upper->setText("45.0");

	LE_LAST_ANGLE_Lower->setText("0.0");
	LE_LAST_ANGLE_Upper->setText("45.0");
}

void hcmDesignVariable::setFromFile(QTextStream& qts)
{
	QString check, target, lower, step, upper;
	qts >> check >> target >> lower >> step >> upper;
	CB_HEADLINK_X->setChecked(check.toInt());
	LE_HEADLINK_LOWER_X->setText(lower);
	LE_HEADLINK_STEP_X->setText(step);
	LE_HEADLINK_UPPER_X->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_HEADLINK_Y->setChecked(check.toInt());
	LE_HEADLINK_LOWER_Y->setText(lower);
	LE_HEADLINK_STEP_Y->setText(step);
	LE_HEADLINK_UPPER_Y->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_LINKHINGE_X->setChecked(check.toInt());
	LE_LINKHINGE_LOWER_X->setText(lower);
	LE_LINKHINGE_STEP_X->setText(step);
	LE_LINKHINGE_UPPER_X->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_LINKHINGE_Y->setChecked(check.toInt());
	LE_LINKHINGE_LOWER_Y->setText(lower);
	LE_LINKHINGE_STEP_Y->setText(step);
	LE_LINKHINGE_UPPER_Y->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_HINGECAM_X->setChecked(check.toInt());
	LE_HINGECAM_LOWER_X->setText(lower);
	LE_HINGECAM_STEP_X->setText(step);
	LE_HINGECAM_UPPER_X->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_HINGECAM_Y->setChecked(check.toInt());
	LE_HINGECAM_LOWER_Y->setText(lower);
	LE_HINGECAM_STEP_Y->setText(step);
	LE_HINGECAM_UPPER_Y->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_CAMRC_X->setChecked(check.toInt());
	LE_CAMRC_LOWER_X->setText(lower);
	LE_CAMRC_STEP_X->setText(step);
	LE_CAMRC_UPPER_X->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_CAMRC_Y->setChecked(check.toInt());
	LE_CAMRC_LOWER_Y->setText(lower);
	LE_CAMRC_STEP_Y->setText(step);
	LE_CAMRC_UPPER_Y->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_CAMPV_X->setChecked(check.toInt());
	LE_CAMPV_LOWER_X->setText(lower);
	LE_CAMPV_STEP_X->setText(step);
	LE_CAMPV_UPPER_X->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_CAMPV_Y->setChecked(check.toInt());
	LE_CAMPV_LOWER_Y->setText(lower);
	LE_CAMPV_STEP_Y->setText(step);
	LE_CAMPV_UPPER_Y->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_CAMANGLE->setChecked(check.toInt());
	LE_INITIAL_ANGLE_Lower->setText(lower);
	LE_INITIAL_ANGLE_Upper->setText(upper);

	qts >> check >> target >> lower >> step >> upper;
	CB_LASTANGLE->setChecked(check.toInt());
	LE_LAST_ANGLE_Lower->setText(lower);
	LE_LAST_ANGLE_Upper->setText(upper);
}

void hcmDesignVariable::saveToFile(QTextStream& qts)
{
	qts << CB_HEADLINK_X->isChecked() << " " << "NozzleLink(X) " << LE_HEADLINK_LOWER_X->text() << " " << LE_HEADLINK_STEP_X->text() << " " << LE_HEADLINK_UPPER_X->text() << endl
		<< CB_HEADLINK_Y->isChecked() << " " << "NozzleLink(Y) " << LE_HEADLINK_LOWER_Y->text() << " " << LE_HEADLINK_STEP_Y->text() << " " << LE_HEADLINK_UPPER_Y->text() << endl
		<< CB_LINKHINGE_X->isChecked() << " " << "LinkCam(X) " << LE_LINKHINGE_LOWER_X->text() << " " << LE_LINKHINGE_STEP_X->text() << " " << LE_LINKHINGE_UPPER_X->text() << endl
		<< CB_LINKHINGE_Y->isChecked() << " " << "LinkCam(Y) " << LE_LINKHINGE_LOWER_Y->text() << " " << LE_LINKHINGE_STEP_Y->text() << " " << LE_LINKHINGE_UPPER_Y->text() << endl
		<< CB_HINGECAM_X->isChecked() << " " << "LinkCam(X) " << LE_HINGECAM_LOWER_X->text() << " " << LE_HINGECAM_STEP_X->text() << " " << LE_HINGECAM_UPPER_X->text() << endl
		<< CB_HINGECAM_Y->isChecked() << " " << "LinkCam(Y) " << LE_HINGECAM_LOWER_Y->text() << " " << LE_HINGECAM_STEP_Y->text() << " " << LE_HINGECAM_UPPER_Y->text() << endl
		<< CB_CAMRC_X->isChecked() << " " << "CamGround(X) " << LE_CAMRC_LOWER_X->text() << " " << LE_CAMRC_STEP_X->text() << " " << LE_CAMRC_UPPER_X->text() << endl
		<< CB_CAMRC_Y->isChecked() << " " << "CamGround(Y) " << LE_CAMRC_LOWER_Y->text() << " " << LE_CAMRC_STEP_Y->text() << " " << LE_CAMRC_UPPER_Y->text() << endl
		<< CB_CAMPV_X->isChecked() << " " << "CamArc(X) " << LE_CAMPV_LOWER_X->text() << " " << LE_CAMPV_STEP_X->text() << " " << LE_CAMPV_UPPER_X->text() << endl
		<< CB_CAMPV_Y->isChecked() << " " << "CamArc(Y) " << LE_CAMPV_LOWER_Y->text() << " " << LE_CAMPV_STEP_Y->text() << " " << LE_CAMPV_UPPER_Y->text() << endl
		<< CB_CAMANGLE->isChecked() << " " << "CamAngle " << LE_INITIAL_ANGLE_Lower->text() << " - " << LE_INITIAL_ANGLE_Upper->text() << endl
		<< CB_LASTANGLE->isChecked() << " " << "CamAngle " << LE_LAST_ANGLE_Lower->text() << " - " << LE_LAST_ANGLE_Upper->text() << endl;
}

int hcmDesignVariable::setSystemParameters(model* md)
{
	int totalCase = 0;
	double mm2m = 0.001;
	double lower, step, upper;
	lower = LE_HEADLINK_LOWER_X->text().toDouble() * mm2m;
	step = LE_HEADLINK_STEP_X->text().toDouble() * mm2m;
	upper = LE_HEADLINK_UPPER_X->text().toDouble() * mm2m;

	if (CB_HEADLINK_X->isChecked())
	{
		md->DesignVariables()["nozzleLink_x"]->setCondition(lower, step, upper);
		md->DesignVariables()["nozzleLink_x"]->setEnable(true);
		int nc = static_cast<int>((upper - lower) / step) + 1;
		if (!totalCase) totalCase += nc;
		else totalCase *= nc;
	}
	else
		md->DesignVariables()["nozzleLink_x"]->setEnable(false);

	lower = LE_HEADLINK_LOWER_Y->text().toDouble() * mm2m;
	step = LE_HEADLINK_STEP_Y->text().toDouble() * mm2m;
	upper = LE_HEADLINK_UPPER_Y->text().toDouble() * mm2m;

	if (CB_HEADLINK_Y->isChecked())
	{
		md->DesignVariables()["nozzleLink_y"]->setCondition(lower, step, upper);
		md->DesignVariables()["nozzleLink_y"]->setEnable(true);
		int nc = static_cast<int>((upper - lower) / step) + 1;
		if (!totalCase) totalCase += nc;
		else totalCase *= nc;
	}
	else
		md->DesignVariables()["nozzleLink_y"]->setEnable(false);

	lower = LE_LINKHINGE_LOWER_X->text().toDouble() * mm2m;
	step = LE_LINKHINGE_STEP_X->text().toDouble() * mm2m;
	upper = LE_LINKHINGE_UPPER_X->text().toDouble() * mm2m;

	if (CB_LINKHINGE_X->isChecked())
	{
		md->DesignVariables()["linkHinge_x"]->setCondition(lower, step, upper);
		md->DesignVariables()["linkHinge_x"]->setEnable(true);
		int nc = static_cast<int>((upper - lower) / step) + 1;
		if (!totalCase) totalCase += nc;
		else totalCase *= nc;

	}
	else
		md->DesignVariables()["linkHinge_x"]->setEnable(false);

	lower = LE_LINKHINGE_LOWER_Y->text().toDouble() * mm2m;
	step = LE_LINKHINGE_STEP_Y->text().toDouble() * mm2m;
	upper = LE_LINKHINGE_UPPER_Y->text().toDouble() * mm2m;

	if (CB_LINKHINGE_Y->isChecked())
	{
		md->DesignVariables()["linkHinge_y"]->setCondition(lower, step, upper);
		md->DesignVariables()["linkHinge_y"]->setEnable(true);
		int nc = static_cast<int>((upper - lower) / step) + 1;
		if (!totalCase) totalCase += nc;
		else totalCase *= nc;
	}
	else
	{
		md->DesignVariables()["linkHinge_y"]->setEnable(false);
	}

	lower = LE_HINGECAM_LOWER_X->text().toDouble() * mm2m;
	step = LE_HINGECAM_STEP_X->text().toDouble() * mm2m;
	upper = LE_HINGECAM_UPPER_X->text().toDouble() * mm2m;

	if (CB_HINGECAM_X->isChecked())
	{
		md->DesignVariables()["hingeCam_x"]->setCondition(lower, step, upper);
		md->DesignVariables()["hingeCam_x"]->setEnable(true);
		int nc = static_cast<int>((upper - lower) / step) + 1;
		if (!totalCase) totalCase += nc;
		else totalCase *= nc;
	}
	else
	{
		md->DesignVariables()["hingeCam_x"]->setEnable(false);
	}

	lower = LE_HINGECAM_LOWER_Y->text().toDouble() * mm2m;
	step = LE_HINGECAM_STEP_Y->text().toDouble() * mm2m;
	upper = LE_HINGECAM_UPPER_Y->text().toDouble() * mm2m;

	if (CB_HINGECAM_Y->isChecked())
	{
		md->DesignVariables()["hingeCam_y"]->setCondition(lower, step, upper);
		md->DesignVariables()["hingeCam_y"]->setEnable(true);
		int nc = static_cast<int>((upper - lower) / step) + 1;
		if (!totalCase) totalCase += nc;
		else totalCase *= nc;
	}
	else
	{
		md->DesignVariables()["hingeCam_y"]->setEnable(false);
	}
	
	lower = LE_CAMRC_LOWER_X->text().toDouble() * mm2m;
	step = LE_CAMRC_STEP_X->text().toDouble() * mm2m;
	upper = LE_CAMRC_UPPER_X->text().toDouble() * mm2m;

	if (CB_CAMRC_X->isChecked())
	{
		md->DesignVariables()["camGround_x"]->setCondition(lower, step, upper);
		md->DesignVariables()["camGround_x"]->setEnable(true);
		int nc = static_cast<int>((upper - lower) / step) + 1;
		if (!totalCase) totalCase += nc;
		else totalCase *= nc;
	}
	else
		md->DesignVariables()["camGround_x"]->setEnable(false);

	lower = LE_CAMRC_LOWER_Y->text().toDouble() * mm2m;
	step = LE_CAMRC_STEP_Y->text().toDouble() * mm2m;
	upper = LE_CAMRC_UPPER_Y->text().toDouble() * mm2m;

	if (CB_CAMRC_Y->isChecked())
	{
		md->DesignVariables()["camGround_y"]->setCondition(lower, step, upper);
		md->DesignVariables()["camGround_y"]->setEnable(true);
		int nc = static_cast<int>((upper - lower) / step) + 1;
		if (!totalCase) totalCase += nc;
		else totalCase *= nc;
	}
	else
	{
		md->DesignVariables()["camGround_y"]->setEnable(false);

	}

	lower = LE_CAMPV_LOWER_X->text().toDouble() * mm2m;
	step = LE_CAMPV_STEP_X->text().toDouble() * mm2m;
	upper = LE_CAMPV_UPPER_X->text().toDouble() * mm2m;

	designVariable* m_dv = md->DesignVariables()["arcCam_x"];
	if (m_dv)
	{
		if (CB_CAMPV_X->isChecked())
		{
			md->DesignVariables()["arcCam_x"]->setCondition(lower, step, upper);
			md->DesignVariables()["arcCam_x"]->setEnable(true);
			int nc = static_cast<int>((upper - lower) / step) + 1;
			if (!totalCase) totalCase += nc;
			else totalCase *= nc;
		}
		else
			md->DesignVariables()["arcCam_x"]->setEnable(false);
	}

	lower = LE_CAMPV_LOWER_Y->text().toDouble() * mm2m;
	step = LE_CAMPV_STEP_Y->text().toDouble() * mm2m;
	upper = LE_CAMPV_UPPER_Y->text().toDouble() * mm2m;
	m_dv = md->DesignVariables()["arcCam_y"];
	if (m_dv)
	{
		if (CB_CAMPV_Y->isChecked())
		{
			md->DesignVariables()["arcCam_y"]->setCondition(lower, step, upper);
			md->DesignVariables()["arcCam_y"]->setEnable(true);
			int nc = static_cast<int>((upper - lower) / step) + 1;
			if (!totalCase) totalCase += nc;
			else totalCase *= nc;
		}
		else
			md->DesignVariables()["arcCam_y"]->setEnable(false);
	}
	
	if (CB_CAMANGLE->isChecked())
	{
		md->setCamAngleDesignVariable(LE_INITIAL_ANGLE_Lower->text().toDouble(), LE_INITIAL_ANGLE_Upper->text().toDouble());
		md->setCamAngleDesignVariableEnable(true);
	}
	else
		md->setCamAngleDesignVariableEnable(false);

	if (CB_LASTANGLE->isChecked())
	{
		md->setLastCamAngleDesignVariable(LE_LAST_ANGLE_Lower->text().toDouble(), LE_LAST_ANGLE_Upper->text().toDouble());
		md->setLastCamAngleDesignVariableEnable(true);
	}
	else
		md->setLastCamAngleDesignVariableEnable(false);

	return totalCase;
}
