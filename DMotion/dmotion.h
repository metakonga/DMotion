#ifndef DMOTION_H
#define DMOTION_H

#include <QtWidgets/QMainWindow>
#include <QMap>
#include <QToolBar>
#include "ui_dmotion.h"
#include "commandWindow.h"
#include "DynaMic.h"
#include "plotWindow.h"
#include "view.h"

//#include "documentCommon.h"

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

class plotDialog;
class vp_profile;
class Translate;
class document;
class model;
class QTimer;

typedef commandWindow com;

class DMotion : public QMainWindow
{
	Q_OBJECT
	enum MENU_ACTION{ NEW, OPEN, SAVE, VELOCITY_PROFILE	};
public:
	enum { FileNewId, FilePrefUseVBOId, FileCloseId, FilePreferencesId, FileQuitId, ViewToolId, ViewStatusId, HelpAboutId };
	enum { TOOL_WIRE_FRAME, TOOL_SHADING, TOOL_TRANSPARENCY, TOOL_MATERIAL, ToolColorId, ToolDeleteId };
	enum {
		FileImportIGESId = 2, FileExportIGESId = 3,
		FileImportSTEPId = 4, FileExportSTEPId = 5
	};
	enum { ANIMATION_PREVIOUS_2X, ANIMATION_PREVIOUS_1X, ANIMATION_PLAY, ANIMATION_PAUSE, ANIMATION_FORWARD_2X, ANIMATION_FORWARD_1X };

	DMotion(QWidget *parent = 0);
	~DMotion();

	//static QMdiArea* getWorkspace();
	static DMotion* getApplication();
	static Handle(AIS_InteractiveContext) getAISContext();
	static QString                  getResourceDir();
	static Ui::DMotionClass*		getApplicationUI();
	QToolBar *getMainToolBar() { return ui.mainToolBar; }

	public slots:
	void                            onToolAction();


protected:
	virtual int                     translationFormat(QString& fileName);

	public slots:
	virtual void                    onSelectionChanged();
	virtual Translate*              createTranslator();
	void onWireframe();
	void onShading();
	void onMaterial();
	void onTransparency();
	void onPrevious2X();
	void onPrevious1X();
	void onAnimationPlay();
	void onAnimationPause();
	void onForward1X();
	void onForward2X();
	void                           onTransparency(int);
	//virtual void                    onCloseDocument(DocumentCommon* theDoc);

	private slots:
	void edit_velocity_profile();
	void file_import();
	void file_new();
	void file_open();
	void tool_plot();
	void analysis_dynamic();
	void analysisProcess(char, QString);
	void plotProcess(double, double);
	void quitThread();
	void updateAnimationFrame();
	void onSetMaterial(int);

private:
	int                             myNbDocuments;
	bool                            myIsDocuments;
	Handle(V3d_Viewer)             Viewer(const Standard_ExtString theName,
		const Standard_CString theDomain,
		const Standard_Real theViewSize,
		const V3d_TypeOfOrientation theViewProj,
		const Standard_Boolean theComputedMode,
		const Standard_Boolean theDefaultComputedMode);

	bool                            translate(const QString&, const int, const bool);
	void createCasCadeOperations();
	void createAnimationOperations();

private:
	Ui::DMotionClass ui;
	vp_profile *vp;
	QMap<MENU_ACTION, QAction*> menus;
	QList<QAction*> myToolActions;
	QList<QAction*> myAnimationActions;
	commandWindow *cw;
	DynaMic *dm;
	Handle(V3d_Viewer)             myViewer;
	Handle(AIS_InteractiveContext) myContext;
	QToolBar* myCasCadeBar;
	QToolBar* myAnimationBar;
	double tx;
	view* myView;
	model* md;
	plotDialog* graph;
	plotWindow* plot;
	QTimer *timer;
	document* doc;
};

#endif // DMOTION_H
