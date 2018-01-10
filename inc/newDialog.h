#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>
#include "ui_newModel.h"
#include "dmotion_types.h"

// namespace Ui{
// 	class newModelDialog;
// }

class newDialog : public QDialog, private Ui::newModelDialog
{
	Q_OBJECT

public:
	explicit newDialog(QWidget *parent = 0);
	~newDialog();

	int callDialog();
	QString ModelName() { return _name; }
	QString Directory() { return _path; }
	QString FullPath() { return _fullPath; }
	QString OpenFilePath(){ return openFilePath; }
	modelType SelectedModelType() { return mtype; }
	//tUnit unit() { return _unit; }
	//tGravity gravityDirection() { return _dir_g; }

private:
// 	QLineEdit *LEName;
// 	QLineEdit *LEPath;
	modelType mtype;
	QString _name;
	QString _path;
	QString _fullPath;
	QString openFilePath;
	//tUnit _unit;
	//tGravity _dir_g;

	int isDialogOk;

	//Ui::newModelDialog *ui;

private slots:
	void Click_ok();
	void Click_open();
	void Click_browse();
};


#endif