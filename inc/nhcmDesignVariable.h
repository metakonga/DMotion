#ifndef NHCM_DESIGN_VARIABLE_H
#define NHCM_DESIGN_VARIABLE_H

#include <QWidget>
#include <QTextStream>

QT_BEGIN_NAMESPACE
class QFrame;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QGridLayout;
class QLineEdit;
class QCheckBox;
QT_END_NAMESPACE

class model;

class nhcmDesignVariable : public QWidget
{
public:
	nhcmDesignVariable(QFrame *frame);
	~nhcmDesignVariable();

	void setInitValue();
	void setFromFile(QTextStream& qts);
	void saveToFile(QTextStream& qts);
	int setSystemParameters(model* md);

	void setEnableAndShow();
	void setDisableAndHide();

private:
	//QFrame *DesignTabFrame;
	QGroupBox *GB_DESIGN_VARIABLE;
	QWidget* layoutWidget;
	QHBoxLayout *horizontalLayout;
	QLabel *L_LOWER;
	QLabel *L_Step;
	QLabel *L_Upper;
	QWidget *layoutWidget_2;
	QGridLayout *gridLayout_2;
	QCheckBox *CB_HEADLINK_X;
//	QLabel *L_HEADLINK_X;
	QLineEdit *LE_HEADLINK_LOWER_X;
	QLineEdit *LE_HEADLINK_STEP_X;
	QLineEdit *LE_HEADLINK_UPPER_X;
	QCheckBox *CB_HEADLINK_Y;
//	QLabel *L_HEADLINKCAM_Y;
	QLineEdit *LE_HEADLINK_LOWER_Y;
	QLineEdit *LE_HEADLINK_STEP_Y;
	QLineEdit *LE_HEADLINK_UPPER_Y;
	QCheckBox *CB_LINKCAM_X;
//	QLabel *L_LINKCAM_X;
	QLineEdit *LE_LINKCAM_LOWER_X;
	QLineEdit *LE_LINKCAM_STEP_X;
	QLineEdit *LE_LINKCAM_UPPER_X;
	QCheckBox *CB_LINKCAM_Y;
	//QLabel *L_LINKCAM_Y;
	QLineEdit *LE_LINKCAM_LOWER_Y;
	QLineEdit *LE_LINKCAM_STEP_Y;
	QLineEdit *LE_LINKCAM_UPPER_Y;
	QCheckBox *CB_CAMRC_X;
	//QLabel *L_CAMRC_X;
	QLineEdit *LE_CAMRC_LOWER_X;
	QLineEdit *LE_CAMRC_STEP_X;
	QLineEdit *LE_CAMRC_UPPER_X;
	QCheckBox *CB_CAMRC_Y;
	//QLabel *L_CAMRC_Y;
	QLineEdit *LE_CAMRC_LOWER_Y;
	QLineEdit *LE_CAMRC_STEP_Y;
	QLineEdit *LE_CAMRC_UPPER_Y;
	QCheckBox *CB_CAMPV_X;
	//QLabel *L_CAMPV_X;
	QLineEdit *LE_CAMPV_LOWER_X;
	QLineEdit *LE_CAMPV_STEP_X;
	QLineEdit *LE_CAMPV_UPPER_X;
	QCheckBox *CB_CAMPV_Y;
	//QLabel *L_CAMPV_Y;
	QLineEdit *LE_CAMPV_LOWER_Y;
	QLineEdit *LE_CAMPV_STEP_Y;
	QLineEdit *LE_CAMPV_UPPER_Y;
	QCheckBox *CB_CAMANGLE;
	//QLabel *L_CAMANGLE;
	QLineEdit *LE_INITIAL_ANGLE_Lower;
	QLineEdit *LE_INITIAL_ANGLE_Upper;

	QCheckBox *CB_LASTANGLE;
	QLineEdit *LE_LAST_ANGLE_Lower;
	QLineEdit *LE_LAST_ANGLE_Upper;

// 	QCheckBox *CB_SPACE;
// 	QLabel *L_Space_Width;
// 	QLabel *L_Space_Height;
// 	QLineEdit *LE_Space_Width;
// 	QLineEdit *LE_Space_Height;
// 	QLabel *L_Space_Info;
};

#endif