#ifndef MDIWINDOW_H
#define MDIWINDOW_H

#include <QMainWindow>
//#include "CommonSample.h"

class DocumentCommon;
class view;

class MDIWindow : public QMainWindow
{
	Q_OBJECT

public:
	MDIWindow(DocumentCommon* aDocument, QWidget* parent, Qt::WindowFlags wflags);
	MDIWindow(view* aView, DocumentCommon* aDocument, QWidget* parent, Qt::WindowFlags wflags);
	~MDIWindow();

	DocumentCommon*            getDocument();
// 	void                       fitAll();
// 	virtual QSize              sizeHint() const;

signals:
	void                       selectionChanged();
// 	void                       message(const QString&, int);
// 	void                       sendCloseView(MDIWindow* theView);
// 
// 	public slots:
// 	void                       closeEvent(QCloseEvent* e);
// 	void                       onWindowActivated();
// 	void                       dump();

// protected:
// 	void                       createViewActions();
// 	void                       createRaytraceActions();

protected:
	DocumentCommon*            myDocument;
	view*                      myView;
};

#endif