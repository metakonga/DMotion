#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include <QDockWidget>
#include <QPlainTextEdit>
#include <QString>

class commandWindow : public QDockWidget
{
public:
	commandWindow(QWidget* parent);
	~commandWindow();

	static void clear();
	static void write(QString str);
	static void printLine();

private:
	static QPlainTextEdit *e;
};

#endif