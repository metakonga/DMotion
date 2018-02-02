#include "commandWindow.h"


QPlainTextEdit* commandWindow::e = NULL;

commandWindow::commandWindow(QWidget *parent)
	: QDockWidget(parent)
{
	e = new QPlainTextEdit;
	e->setReadOnly(true);
	e->setMaximumHeight(150);
	setWidget(e);
}

commandWindow::~commandWindow()
{

}

void commandWindow::clear()
{
	e->clear();
}

void commandWindow::write(QString str)
{
	e->appendPlainText(str);
}

void commandWindow::printLine()
{
	e->appendPlainText("--------------------------------------------------------------------------------------------------------------------------------------------------------------------");
}