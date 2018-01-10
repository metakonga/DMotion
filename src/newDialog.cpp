#include "newDialog.h"
#include "ui_newModel.h"
#include <QtWidgets>

newDialog::newDialog(QWidget* parent)
	: QDialog(parent)
	, isDialogOk(-1)
{
	setupUi(this);
	connect(PB_Create, SIGNAL(clicked()), this, SLOT(Click_ok()));
	connect(PB_Open, SIGNAL(clicked()), this, SLOT(Click_open()));
	connect(PB_Browse, SIGNAL(clicked()), this, SLOT(Click_browse()));
	_path = getenv("USERPROFILE");
	_path += "/Documents";
	_path.replace(QString("\\"), QString("/"));
	_name = "Model_1";
}

newDialog::~newDialog()
{
	disconnect(PB_Create);
	disconnect(PB_Create);
	disconnect(PB_Browse);
	//if (ui) delete ui; ui = NULL;
}

int newDialog::callDialog()
{
	LE_Name->setText(_name);
	LE_Directory->setText(_path);
	this->exec();

	return isDialogOk;
}

void newDialog::Click_ok()
{
	_name = LE_Name->text();
	_path = LE_Directory->text();
	
	 _fullPath = _path + "/" + _name;
	 if (!QDir(_fullPath).exists())
		 QDir().mkdir(_fullPath);
	//_path = ui->LEPath->text();
//	_unit = (tUnit)ui->CBUnit->currentIndex();
//	_dir_g = (tGravity)ui->CBGravity->currentIndex();
	//_path += "/";
	 if (RB_NHCM->isChecked())
		 mtype = ORIGINAL_CAM_TYPE;
	 else if (RB_HCM->isChecked())
		 mtype = HOLE_CAM_TYPE;
	this->close();
	isDialogOk = 1;
}

void newDialog::Click_open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open"), _path, tr("Model File(*.mde)"));
	if (!fileName.isEmpty())
	{
		int loc = fileName.lastIndexOf("/");
		_path = fileName.left(loc);
		loc = _path.lastIndexOf("/");
		_name = _path.mid(loc+1);
		_path = _path.left(loc);
		openFilePath = fileName;
	}
	this->close();
	isDialogOk = 0;
}

void newDialog::Click_browse()
{
	QString fileName = QFileDialog::getExistingDirectory(this, tr("browse"), _path);
		//QFileDialog::getOpenFileName(this, tr("open"), _path, tr("Model File(*.mde)"));
	if (!fileName.isEmpty()){
		_path = fileName;
		LE_Directory->setText(_path);
// 		int begin = fileName.lastIndexOf("/");
// 		int end = fileName.lastIndexOf(".");
// 		_name = fileName.mid(begin + 1, end - begin - 1);
// 		_path = fileName.mid(0, begin + 1);
// 		this->close();
	}
	//this->close();
	//isDialogOk = false;
}