#include "commandWindow.h"


QPlainTextEdit* commandWindow::e = NULL;

commandWindow::commandWindow(QWidget *parent)
	: QDockWidget(parent)
{
	setWindowTitle("Command DockWindow");
	e = new QPlainTextEdit;
	e->setReadOnly(true);
	e->setMaximumHeight(150);
	setWidget(e);
}

commandWindow::~commandWindow()
{
	if (e) delete e; e = NULL;
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