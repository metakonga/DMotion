#include "dmotion.h"
#include "vp_profile.h"
#include "plotDialog.h"
#include "document.h"
#include "translate.h"
#include "transparency.h"
#include "slider_crank.hpp"
#include "dual_motion.hpp"
#include "animation_controller.h"
#include "materialDialog.h"
#include <QDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QComboBox>

#include <Aspect_DisplayConnection.hxx>
#include <AIS_InteractiveObject.hxx>
#include <Graphic3d_NameOfMaterial.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <TCollection_AsciiString.hxx>
#include <V3d_DirectionalLight.hxx>
#include <V3d_AmbientLight.hxx>
//#include "MCHSpline.h"
// #include <QChartView>
// #include <QLineSeries>
//#include <QDialog>

Handle(V3d_Viewer) DMotion::Viewer(const Standard_ExtString,
	const Standard_CString,
	const Standard_Real theViewSize,
	const V3d_TypeOfOrientation theViewProj,
	const Standard_Boolean theComputedMode,
	const Standard_Boolean theDefaultComputedMode)
{
	static Handle(OpenGl_GraphicDriver) aGraphicDriver;

	if (aGraphicDriver.IsNull())
	{
		Handle(Aspect_DisplayConnection) aDisplayConnection;
#if !defined(_WIN32) && !defined(__WIN32__) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX))
		aDisplayConnection = new Aspect_DisplayConnection(qgetenv("DISPLAY").constData());
#endif
		aGraphicDriver = new OpenGl_GraphicDriver(aDisplayConnection);
	}

	Handle(V3d_Viewer) aViewer = new V3d_Viewer(aGraphicDriver);
	aViewer->SetDefaultViewSize(theViewSize);
	aViewer->SetDefaultViewProj(theViewProj);
	aViewer->SetComputedMode(theComputedMode);
	aViewer->SetDefaultComputedMode(theDefaultComputedMode);
	return aViewer;
}

static DMotion* stApp = 0;
static Handle(AIS_InteractiveContext) ctx = 0;
static Ui::DMotionClass* userInterface = 0;
//static QMdiArea* stWs = 0;

DMotion::DMotion(QWidget *parent)
	: QMainWindow(parent, 0)
	, vp(NULL)
	, cw(NULL)
	, dm(NULL)
	, doc(NULL)
	, graph(NULL)
	, plot(NULL)
	, timer(NULL)
	, tx(0)
{
	ui.setupUi(this);
	userInterface = &ui;
	myNbDocuments = 0;
	stApp = this;
	myIsDocuments = false;
	cw = new commandWindow(this);
	graph = new plotDialog(this);
	plot = new plotWindow(this);
	doc = new document(this);
	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimationFrame()));
	connect(ui.File_New, SIGNAL(triggered()), this, SLOT(file_new()));
	connect(ui.File_Open, SIGNAL(triggered()), this, SLOT(file_open()));
	connect(ui.Tool_Graph, SIGNAL(triggered()), this, SLOT(tool_plot()));
	connect(ui.Analysis_dynamic, SIGNAL(triggered()), this, SLOT(analysis_dynamic()));
 	TCollection_ExtendedString a3DName("Visu3D");
 	myViewer = Viewer(a3DName.ToExtString(), "", 1000.0, V3d_XposYnegZpos, Standard_True, Standard_True);
// 	static Handle(V3d_Light) aLight1 = new V3d_DirectionalLight(myViewer, V3d_XnegYposZneg);
// 	static Handle(V3d_Light) aLight2 = new V3d_DirectionalLight(myViewer, V3d_XnegYnegZpos);
// 	static Handle(V3d_Light) aLight3 = new V3d_DirectionalLight(myViewer, V3d_XposYnegZpos);
// 	static Handle(V3d_Light) aLight4 = new V3d_DirectionalLight(myViewer, V3d_XnegYnegZneg);
// 	static Handle(V3d_Light) aLight5 = new V3d_DirectionalLight(myViewer, V3d_XnegYposZpos);
// 	static Handle(V3d_Light) aLight6 = new V3d_DirectionalLight(myViewer, V3d_XposYposZpos);

	//myViewer->SetDefaultBackgroundColor(Quantity_NOC_AQUAMARINE1);
 	myViewer->SetDefaultLights();
 	myViewer->SetLightOn();
//  	myViewer->SetLightOn(aLight2);

//  	myViewer->SetLightOn(aLight3);

// 	myViewer->SetLightOn(aLight4);
// 	myViewer->SetLightOn(aLight5);
// 	myViewer->SetLightOn(aLight6
	//md = new slider_crank();
	md = new dual_motion();
	//md->init();
   	myContext = new AIS_InteractiveContext(myViewer);
	ctx = myContext;
  	QFrame *vb = new QFrame(this);
  	QVBoxLayout* layout = new QVBoxLayout(vb);
  	layout->setMargin(0);
  	vb->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  	setCentralWidget(vb);
  	myView = new view(myContext, vb);

  	layout->addWidget(myView);
// // 	//setLayout(layout);
 	addDockWidget(Qt::BottomDockWidgetArea, cw);
	addDockWidget(Qt::LeftDockWidgetArea, plot);
//	userInterface->GP_DOCK->setWidget(vcht);
	plot->resize(400, 400);
	//ui.DW_Modeling->setFloating(true);
  	resize(1200, 700);
  	setFocusPolicy(Qt::StrongFocus);
	createCasCadeOperations();
	createAnimationOperations();
	ui.DW_Modeling->setMinimumWidth(400);
	ui.DW_Modeling->setMaximumWidth(400);
	connect(ui.Edit_VelocityProfile, SIGNAL(triggered()), this, SLOT(edit_velocity_profile()));
	connect(ui.File_Import, SIGNAL(triggered()), this, SLOT(file_import()));
	connect(myView, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
	
	doc->setDisplayDynamicModel(md->RigidBodies(), md->HardPoints());
	myView->front();
/*	myView->fitAll();*/
	//ui.DW_Modeling->setWidget(doc->getHPTable());
	//myView->globalPan();
}

DMotion::~DMotion()
{
	if (vp) delete vp; vp = NULL;
	if (cw) delete cw; cw = NULL;
	if (dm) delete dm; dm = NULL;
	if (md) delete md; md = NULL;
	if (myView) delete myView; myView = NULL;
	if (graph) delete graph; graph = NULL;
	if (timer) delete timer; timer = NULL;
}

Handle(AIS_InteractiveContext) DMotion::getAISContext()
{
	return ctx;
}

Ui::DMotionClass* DMotion::getApplicationUI()
{
	return userInterface;
}

void DMotion::analysisProcess(char c, QString str)
{
	//QString mode;
	switch (c)
	{
	case '@': cw->write("" + str); break;
	case 'L': cw->printLine(); break;
	}
	
}

void DMotion::createCasCadeOperations()
{
	myCasCadeBar = addToolBar(tr("Shape Operations"));
	QAction* a;
	a = new QAction(QIcon(":/Resources/wireFrame.png"), tr("&wireFrame"), this);
	a->setStatusTip(tr("wireFrame"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(TOOL_WIRE_FRAME, a);

	a = new QAction(QIcon(":/Resources/shading.png"), tr("&shading"), this);
	a->setStatusTip(tr("shading"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(TOOL_SHADING, a);

	a = new QAction(QIcon(":/Resources/material.png"), tr("&material"), this);
	a->setStatusTip(tr("material"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(TOOL_MATERIAL, a);

	a = new QAction(QIcon(":/Resources/transparency.png"), tr("&transparency"), this);
	a->setStatusTip(tr("transparency"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(TOOL_TRANSPARENCY, a);

	for (int i = 0; i < myToolActions.size(); i++)
	{
		myCasCadeBar->addAction(myToolActions.at(i));
	}
	myCasCadeBar->show();
}

void DMotion::createAnimationOperations()
{
	myAnimationBar = addToolBar(tr("Animation Operations"));
	QAction *a;
	a = new QAction(QIcon(":/Resources/ani_moreprevious.png"), tr("&previous2X"), this);
	a->setStatusTip(tr("previous 2X"));
	connect(a, SIGNAL(triggered()), this, SLOT(onPrevious2X()));
	myAnimationActions.insert(ANIMATION_PREVIOUS_2X, a);

	a = new QAction(QIcon(":/Resources/ani_previous.png"), tr("&previous1X"), this);
	a->setStatusTip(tr("previous 1X"));
	connect(a, SIGNAL(triggered()), this, SLOT(onPrevious1X()));
	myAnimationActions.insert(ANIMATION_PREVIOUS_1X, a);

	a = new QAction(QIcon(":/Resources/ani_play.png"), tr("&animation play"), this);
	a->setStatusTip(tr("animation play"));
	connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPlay()));
	myAnimationActions.insert(ANIMATION_PLAY, a);

// 	a = new QAction(QIcon(":/Resources/ani_pause.png"), tr("&animation pause"), this);
// 	a->setStatusTip(tr("animation pause"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPause()));
// 	myAnimationActions.insert(ANIMATION_PAUSE, a);

	a = new QAction(QIcon(":/Resources/ani_fast.png"), tr("&forward1X"), this);
	a->setStatusTip(tr("forward 1X"));
	connect(a, SIGNAL(triggered()), this, SLOT(onForward1X()));
	myAnimationActions.insert(ANIMATION_FORWARD_1X, a);

	a = new QAction(QIcon(":/Resources/ani_morefast.png"), tr("&forward2X"), this);
	a->setStatusTip(tr("forward 2X"));
	connect(a, SIGNAL(triggered()), this, SLOT(onForward2X()));
	myAnimationActions.insert(ANIMATION_FORWARD_2X, a);

	for (int i = 0; i < myAnimationActions.size(); i++)
	{
		myAnimationBar->addAction(myAnimationActions.at(i));
	}
	myAnimationBar->hide();
}

void DMotion::onToolAction()
{
 	QAction* sentBy = (QAction*)sender();
// 	QMdiArea* ws = ApplicationCommonWindow::getWorkspace();
// 	DocumentCommon* doc = qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget())->getDocument();

	if (sentBy == myToolActions.at(TOOL_WIRE_FRAME))
		onWireframe();

	if (sentBy == myToolActions.at(TOOL_SHADING))
		onShading();

// 	if (sentBy == myToolActions.at(ToolColorId))
// 		doc->onColor();
// 
	if (sentBy == myToolActions.at(TOOL_MATERIAL))
		onMaterial();

	if (sentBy == myToolActions.at(TOOL_TRANSPARENCY))
		onTransparency();
// 
// 	if (sentBy == myToolActions.at(ToolDeleteId))
// 		doc->onDelete();

}

void DMotion::onSetMaterial(int theMaterial)
{
	for (myContext->InitCurrent(); myContext->MoreCurrent(); myContext->NextCurrent())
		myContext->SetMaterial(myContext->Current(), (Graphic3d_NameOfMaterial)theMaterial);
}

void DMotion::onMaterial()
{
	materialDialog *m = new materialDialog(this);
	connect(m, SIGNAL(sendMaterialChanged(int)), this, SLOT(onSetMaterial(int)));
	m->exec();
}

void DMotion::onWireframe()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	for (myContext->InitCurrent(); myContext->MoreCurrent(); myContext->NextCurrent())
	{
		myContext->SetDisplayMode(myContext->Current(), 0, false);
	//	myContext->SetLocation(myContext->Current(), t);
		//Handle(AIS_Shape) s1 = dynamic_cast<Handle(AIS_Shape)>(myContext->Current());
		//Handle(AIS_Shape) s = new AIS_Shape(myContext->Current());
	}
		
	myContext->UpdateCurrentViewer();
	//getApplication()->onSelectionChanged();
	QApplication::restoreOverrideCursor();
}

void DMotion::onShading()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	for (myContext->InitCurrent(); myContext->MoreCurrent(); myContext->NextCurrent())
		myContext->SetDisplayMode(myContext->Current(), 1, false);
	myContext->UpdateCurrentViewer();
	//	getApplication()->onSelectionChanged();
	QApplication::restoreOverrideCursor();
}

void DMotion::onTransparency(int theTrans)
{
	for (myContext->InitCurrent(); myContext->MoreCurrent(); myContext->NextSelected())
		myContext->SetTransparency(myContext->Current(), ((Standard_Real)theTrans) / 10.0);
}

void DMotion::onTransparency()
{
	DialogTransparency* aDialog = new DialogTransparency();
	connect(aDialog, SIGNAL(sendTransparencyChanged(int)), this, SLOT(onTransparency(int)));
	aDialog->exec();
	delete aDialog;
}

void DMotion::edit_velocity_profile()
{
	cw->write("Editing dialog of velocity profile is opened.");
	vp->exec();
}

Translate* DMotion::createTranslator()
{
	Translate* anTrans = new Translate(this/*, "Translator"*/);
	return anTrans;
}

void DMotion::file_import()
{
	QString dir = "C:/DMotion";
	QString fileName = QFileDialog::getOpenFileName(this, tr("open"), dir, tr("IGES file (*.iges *.igs);;STEP file (*.stp *.step);;All files (*.*)"));
	if (fileName.isEmpty())
		return;
	int type = translationFormat(fileName);
	bool stat = translate(fileName, type, true);
	if (stat)
	{
		myView->fitAll();
		myCasCadeBar->show();
		onSelectionChanged();
		com::write("Success import process ..... " + fileName);
	}
}

int DMotion::translationFormat(QString& fileName)
{
	int type = -1;
	int begin = fileName.lastIndexOf(".");
	QString ext = fileName.mid(begin);
	if (ext == ".igs" || ext == ".iges")
	{
		type = Translate::FormatIGES;
	}
	else if (ext == ".step" || ext == ".stp")
	{
		type = Translate::FormatSTEP;
	}
	return type;
// 	int _type = 0;
// 	switch (type)
// 	{
// 	case 2:
// 	case 3:
// 		_type = Translate::FormatIGES;
// 		break;
// 	case 4:
// 	case 5:
// 		_type = Translate::FormatSTEP;
// 		break;
// 	}
// 	return _type;
}

bool DMotion::translate(const QString& file, const int format, const bool import)
{
	static Translate* anTrans = createTranslator();
// 	DocumentCommon* doc = qobject_cast<MDIWindow*>(getWorkspace()->activeSubWindow()->widget())->getDocument();
// 	Handle(AIS_InteractiveContext) context = doc->getContext();
	bool status;
	if (import)
		status = anTrans->importModel(file, format, myContext);
//	else
//		status = anTrans->exportModel(file, format, myContext);

	if (!status)
	{
		QString msg = QObject::tr("Translation error");
		if (!anTrans->info().isEmpty())
			msg += QString("\n") + anTrans->info();
		QMessageBox::critical(this, QObject::tr("Error"), msg, QObject::tr("Ok"), QString::null, QString::null, 0, 0);
	}

	return status;
}

QString DMotion::getResourceDir()
{
	static QString aResourceDir =
		QString::fromUtf8(qgetenv("CSF_ResourcesDefaults").constData());

	return aResourceDir;
}

// QMdiArea* DMotion::getWorkspace()
// {
// 	return stWs;
// }

DMotion* DMotion::getApplication()
{
	return stApp;
}


void DMotion::file_new()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	foreach(Handle(AIS_Shape) value, doc->getHardPoints())
	{
		//Handle(AIS_Shape) s = new AIS_Shape(*value);
		
		myContext->Display(value, false);
		myContext->SetDisplayMode(value, 1, false);
	}
	//myCasCadeBar->show();
	myContext->UpdateCurrentViewer();
	QApplication::restoreOverrideCursor();
	myView->front();
	myView->fitAll();
// 	tx += 0.1;
// 	QApplication::setOverrideCursor(Qt::WaitCursor);
// 	for (myContext->InitCurrent(); myContext->MoreCurrent(); myContext->NextCurrent())
// 	{
// 		myContext->SetDisplayMode(myContext->Current(), 0, false);
// 		gp_Trsf t;
// 		gp_Ax1 Ax1(gp_Pnt(0, 0, 0), gp_Vec(0, 1, 0));
// 		t.SetRotation(Ax1, M_PI * tx);
// 		myContext->SetLocation(myContext->Current(), t);
// 		//Handle(AIS_Shape) s1 = dynamic_cast<Handle(AIS_Shape)>(myContext->Current());
// 		//Handle(AIS_Shape) s = new AIS_Shape(myContext->Current());
// 	}
// 
// 	myContext->UpdateCurrentViewer();

// 	QApplication::restoreOverrideCursor();

// 	DocumentCommon* aDoc = createNewDocument();
// 	aDoc->onCreateNewView();
// 	onSelectionChanged();
// 
// 	connect(aDoc, SIGNAL(sendCloseDocument(DocumentCommon*)),
// 		this, SLOT(onCloseDocument(DocumentCommon*)));
// 	connect(stWs, SIGNAL(windowActivated(QWidget*)),
// 		this, SLOT(onWindowActivated(QWidget*)));
// 	connect(aDoc, SIGNAL(selectionChanged()),
// 		this, SLOT(onSelectionChanged()));
// 
// 	myDocuments.append(aDoc);
// 	//myStdActions.at(FileCloseId)->setEnabled(myDocuments.count() > 0);
// 
// 	return aDoc;

}

void DMotion::file_open()
{
	//connect(dm, SIGNAL(finished()), dm, SLOT(oneStepAnalysis()));
//	dm->start();
	QApplication::setOverrideCursor(Qt::WaitCursor);
	for (myContext->InitCurrent(); myContext->MoreCurrent(); myContext->NextCurrent())
	{
		myContext->SetDisplayMode(myContext->Current(), 0, false);
		gp_Trsf t;
		//gp_Ax1 Ax1(gp_Pnt(0, 0, 0), gp_Vec(0, 1, 0));
		t.SetTranslation(gp_Vec(0, 0, 100));
		
		//t.SetRotation(Ax1, M_PI * tx);
		myContext->SetLocation(myContext->Current(), t);
		//Handle(AIS_Shape) s1 = dynamic_cast<Handle(AIS_Shape)>(myContext->Current());
		//Handle(AIS_Shape) s = new AIS_Shape(myContext->Current());
	}

	myContext->UpdateCurrentViewer();

	QApplication::restoreOverrideCursor();
}

void DMotion::tool_plot()
{
	if (graph->isVisible())
		return;
	graph->setModel(md);
	graph->show();
}

void DMotion::quitThread()
{
	dm->quit();
	dm->wait();
	disconnect(dm);
	if (dm) delete dm; dm = NULL;
	myAnimationBar->show();
}

void DMotion::plotProcess(double xv, double yv)
{
	plot->appendData("link", xv, yv);
}

void DMotion::analysis_dynamic()
{
	dm = new DynaMic(md);
	dm->setPlotWindow(plot);
	plot->createSeries("active");
	connect(dm, SIGNAL(sendProcess(char, QString)), this, SLOT(analysisProcess(char, QString)));
	connect(dm, SIGNAL(sendPlotData(double, double)), this, SLOT(plotProcess(double, double)));
	connect(dm, SIGNAL(finishedThread()), this, SLOT(quitThread()));
	dm->setSimulationCondition(0.00001, 0.035);
	dm->init();
	dm->start();
}

void DMotion::onSelectionChanged()
{
	 bool OneOrMoreInShading = false;
	 bool OneOrMoreInWireframe = false;
	 int numSel = myContext->NbSelected();
	 if (numSel)
	 {
		 for (myContext->InitCurrent(); myContext->MoreCurrent(); myContext->NextCurrent())
		 {
			 if (myContext->IsDisplayed(myContext->Current(), 1))
				 OneOrMoreInShading = true;
			 if (myContext->IsDisplayed(myContext->Current(), 0))
				 OneOrMoreInWireframe = true;
		 }
		 myToolActions.at(TOOL_WIRE_FRAME)->setEnabled(OneOrMoreInShading);
		 myToolActions.at(TOOL_SHADING)->setEnabled(OneOrMoreInWireframe);
// 		 myToolActions.at(ToolColorId)->setEnabled(true);
// 		 myToolActions.at(ToolMaterialId)->setEnabled(true);
		 myToolActions.at(TOOL_TRANSPARENCY)->setEnabled(OneOrMoreInShading);
// 		 myToolActions.at(ToolDeleteId)->setEnabled(true);
	 }
	 else
	 {
		 myToolActions.at(TOOL_WIRE_FRAME)->setEnabled(false);
		 myToolActions.at(TOOL_SHADING)->setEnabled(false);
// 		 myToolActions.at(ToolColorId)->setEnabled(false);
// 		 myToolActions.at(ToolMaterialId)->setEnabled(false);
		 myToolActions.at(TOOL_TRANSPARENCY)->setEnabled(false);
// 		 myToolActions.at(ToolDeleteId)->setEnabled(false);
	 }
}

void DMotion::onPrevious2X()
{
	onAnimationPause();
	animation_controller::previous2x();
	updateAnimationFrame();
}

void DMotion::onPrevious1X()
{
	onAnimationPause();
	animation_controller::previous();
	updateAnimationFrame();
}

void DMotion::updateAnimationFrame()
{
	unsigned int i = animation_controller::CurrentFrame();
	QVectorIterator<rigidBody*> r(md->RigidBodies());
	QMap<QString, Handle(AIS_Shape)> r_objs = doc->getRigidBodies();
	while (r.hasNext())
	{
		rigidBody* rb = r.next();
		if (rb->IsGround())
			continue;
		resultDataType rdt = rb->ResultData()->at(i);
		Handle(AIS_Shape) ais = r_objs[rb->Name()];
		gp_Trsf t;
		
		//gp_Trsf a;
		vecd3 pos = 1000.0 * rdt.pos;
		gp_Ax1 ax(gp_Pnt(0,0,0), gp_Vec(0, 0, 1));
		//gp_Ax3 base(pos, gp_Vec(0, 0, 1), gp_Vec(1, 0, 0));
		double ang = rdt.ang;
		//t.SetTransformation(base/*.Rotated(gp_Ax1(pos, gp_Dir(0, 0, 1)), ang)*/);
 		//t.SetRotation(ax, ang);
		t.SetValues(
			cos(ang), -sin(ang), 0, pos.X(),
			sin(ang), cos(ang), 0, pos.Y(),
			0, 0, 1, pos.Z());
 		//t.SetTranslation(gp_Vec(pos.X(), pos.Y(), 0.0));
		//gp_TrsfForm f = t.Form();
		ais->SetLocalTransformation(t);
		//ais->SetLocalTransformation(a);
		//
		
	}

	QVectorIterator<constraint*> c(md->Constraints());
	QMap<QString, Handle(AIS_Shape)> objs = doc->getHardPoints();
	while (c.hasNext())
	{
		constraint* cs = c.next();
		if (cs->JointType() == DRIVING)
			continue;
		jointResultDataType jrdt = cs->ResultData()->at(i);
		hardPoint* hp = cs->BindedHardPoint();
		if (!hp) continue;
		Handle(AIS_Shape) ais = objs[hp->name];
		gp_Trsf t;
		vecd3 pos = 1000.0 * jrdt.loc;
		t.SetTranslation(gp_Vec(pos.X(), pos.Y(), 0.0));
		ais->SetLocalTransformation(t);		
	}
	myContext->UpdateCurrentViewer();
	if(animation_controller::IsPlay())
		animation_controller::next();
}

void DMotion::onAnimationPlay()
{
	animation_controller::setPlayEnable(true);
	QAction *a = myAnimationActions[ANIMATION_PLAY];
	disconnect(a);
	a->setIcon(QIcon(":/Resources/ani_pause.png"));
	a->setStatusTip(tr("Restart the animation."));
	connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPause()));
	timer->start(2);
}

void DMotion::onAnimationPause()
{
	animation_controller::setPlayEnable(false);
	QAction *a = myAnimationActions[ANIMATION_PLAY];
	disconnect(a);
	a->setIcon(QIcon(":/Resources/ani_play.png"));
	a->setStatusTip(tr("Pause the animation."));
	connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPlay()));
	timer->stop();
}

void DMotion::onForward1X()
{
	onAnimationPause();
	animation_controller::next();
	updateAnimationFrame();
}

void DMotion::onForward2X()
{
	onAnimationPause();
	animation_controller::next2x();
	updateAnimationFrame();
}

