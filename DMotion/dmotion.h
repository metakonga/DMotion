#ifndef DMOTION_H
#define DMOTION_H

#include <QtWidgets/QMainWindow>
#include <QMap>
#include <QToolBar>
#include <QProgressBar>
#include "ui_dmotion.h"
#include "commandWindow.h"
#include "kinematics.h"
#include "plotWindow.h"
#include "resultTable.h"
#include "optimumDesignDoc.h"
#include "view.h"
#include "drivingConditionPlot.h"
#include "nhcmDesignVariable.h"
#include "hcmDesignVariable.h"

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

class plotDialog;
class vp_profile;
class Translate;
class document;
class model;
class QTimer;
class selectReactionDialog;

typedef commandWindow com;

class DMotion : public QMainWindow
{
	Q_OBJECT
	enum MENU_ACTION{ NEW=0, OPEN, SAVE, SOLVE, SAVE_CASE, PROFILE };
public:
	enum { TOOL_WIRE_FRAME=6, TOOL_SHADING, TOOL_TRANSPARENCY, TOOL_MATERIAL };
	enum { ANIMATION_GO_BEGIN=0, ANIMATION_PREVIOUS_2X, ANIMATION_PREVIOUS_1X, ANIMATION_PLAY_BACK, ANIMATION_INIT, ANIMATION_PLAY, ANIMATION_PAUSE, ANIMATION_FORWARD_2X, ANIMATION_FORWARD_1X, ANIMATION_GO_END };
	enum { LE_X = 0, LE_Y, LE_ANGLE, LE_MASS, LE_INERTIA, LE_HARDPOINT_X, LE_HARDPOINT_Y };

	DMotion(QWidget *parent = 0);
	~DMotion();

	//static QMdiArea* getWorkspace();
	static DMotion* getApplication();
	static Handle(AIS_InteractiveContext) getAISContext();
	static QString                  getResourceDir();
	static Ui::DMotionClass*		getApplicationUI();
	static document*				getDocument();
	QToolBar *getMainToolBar() { return ui.mainToolBar; }
	void setCaseResult();

	public slots:
	void                            onToolAction();
	void							onLineEditing();


protected:
	virtual int                     translationFormat(QString& fileName);
	void initializeDesignVariable();
	void initializeBodyInformation();
	void initializeHardPoint();
	void initializeDrivingCondition();
	unsigned int setSystemParameters();
	public slots:
	virtual void                    onSelectionChanged();
	virtual Translate*              createTranslator();
	void onWireframe();
	void onShading();
	void onMaterial();
	void onTransparency();
	void onVelocityProfile();
	void onGoToBegin();
	void onPrevious2X();
	void onPrevious1X();
	void onSetPlayAnimation();
	void onAnimationPlay();
	void onAnimationPlayBack();
	void onAnimationPause();
	void onForward1X();
	void onForward2X();
	void onGoToEnd();
	void onGoFirstStep();
	void                           onTransparency(int);
//	void finishDMotion();
	//virtual void                    onCloseDocument(DocumentCommon* theDoc);

	private slots:
	void edit_velocity_profile();
	void file_import();
	void file_new();
	void file_open(QString f = "", bool isNew = false);
	void file_save(QString f = "");
	void tool_plot();
	void analysis();
	void analysis_stop();
	void analysisProcess(char, QString);
	void updateProgressBar(int);
	void quitThread();
	void updateAnimationFrame();
	void onSetMaterial(int);
	void openResultTable();
//	void onToolProfile();
	void pushActiveVelocityBotton();
	void pushPassiveVelocityBotton();
	void pushSelectParameters();
	void pushCaseSave();
	void changeComboBody(int);
	void changeComboHardPoint(int);
	void editLineEdit();
	void clickedTabBar(int);
	void clickApplyShape();

signals:
	void analysisStopSignal();

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
	void createLineEditOperations();
	void closeEvent(QCloseEvent *event);
	void changeModelingTab(int);
	void initialize(modelType mt);

private:
	bool _isNewAnalysis;
	Ui::DMotionClass ui;
	vp_profile *vp;
	
	QMap<MENU_ACTION, QAction*> menus;
	QList<QAction*> myToolActions;
	QList<QAction*> myAnimationActions;
	QList<QLineEdit*> myLineEdits;
	commandWindow *cw;
	kinematics *kin;
	Handle(V3d_Viewer)             myViewer;
	Handle(AIS_InteractiveContext) myContext;
	QToolBar* myCasCadeBar;
	QToolBar* myAnimationBar;
	//QToolBar* myFileBar;
	int current_animation;
	double tx;
	view* myView;
	model* md;
	plotDialog* graph;
	resultTable* rTable;
	plotWindow* plot;
	QTimer *timer;
	QProgressBar *pBar;
	document* doc;
	optimumDesignDoc *odd;
	selectReactionDialog *srdlg;
	nhcmDesignVariable *dv_nhcm;
	hcmDesignVariable *dv_hcm;
	drivingConditionPlot *dcPlot;
	//QMap<modelType, model*> models;
};

#endif // DMOTION_H
