#include "view.h"
#include "dmotion.h"
#include <QApplication>
#include <QPainter>
#include <QMenu>
#include <QColorDialog>

#include <QFileInfo>
#include <QToolBar>
#include <QFileDialog>
#include <QMouseEvent>
#include <QRubberBand>
#include <QMdiSubWindow>
#include <QStyleFactory>

#include <Graphic3d_ExportFormat.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Graphic3d_TextureEnv.hxx>

#include <OcctWindow.h>
#include <Aspect_DisplayConnection.hxx>

// the key for multi selection :
#define MULTISELECTIONKEY Qt::ShiftModifier

// the key for shortcut ( use to activate dynamic rotation, panning )
#define CASCADESHORTCUTKEY Qt::ControlModifier

// for elastic bean selection
#define ValZWMin 1

view::view(Handle(AIS_InteractiveContext) theContext, QWidget* parent)
	: QWidget(parent),
	myIsRaytracing(false),
	myIsShadowsEnabled(true),
	myIsReflectionsEnabled(false),
	myIsAntialiasingEnabled(false),
	myRaytraceActions(0),
	myBackMenu(NULL),
	defCursor(NULL),
	handCursor(NULL),
	panCursor(NULL),
	globPanCursor(NULL),
	zoomCursor(NULL),
	rotCursor(NULL),
	myViewActions(NULL),
	myViewToolBar(NULL)
{
	myContext = theContext;

	myXmin = 0;
	myYmin = 0;
	myXmax = 0;
	myYmax = 0;
	myCurZoom = 0;
	myRectBand = 0;
	//memset(keyID, 0, sizeof(bool) * 256);

	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);

	myCurrentMode = CurAction3d_Nothing;
	myHlrModeIsOn = Standard_False;
	setMouseTracking(true);

	initViewActions();
	initCursors();

	setBackgroundRole(QPalette::NoRole);
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
	init();
}

view::~view()
{
	if (defCursor) delete defCursor; defCursor = NULL;
	if (handCursor) delete handCursor; handCursor = NULL;
	if (panCursor) delete panCursor; panCursor = NULL;
	if (globPanCursor) delete globPanCursor; globPanCursor = NULL;
	if (zoomCursor) delete zoomCursor; zoomCursor = NULL;
	if (rotCursor) delete rotCursor; rotCursor = NULL;
	if (myBackMenu) delete myBackMenu; myBackMenu = NULL;
	if (myViewActions) delete myViewActions; myViewActions = NULL;
	/*if (myRectBand) delete myRectBand; myRectBand = NULL;*/
}

void view::init()
{
	if (myView.IsNull())
		myView = myContext->CurrentViewer()->CreateView();

	Handle(OcctWindow) hWnd = new OcctWindow(this);
	myView->SetWindow(hWnd);
	if (!hWnd->IsMapped())
	{
		hWnd->Map();
	}
	myView->SetBackgroundColor(Quantity_NOC_BLACK);
	myView->MustBeResized();

	if (myIsRaytracing)
		myView->ChangeRenderingParams().Method = Graphic3d_RM_RAYTRACING;
}

void view::paintEvent(QPaintEvent *)
{
	//  QApplication::syncX();
	myView->Redraw();
}

void view::resizeEvent(QResizeEvent *)
{
	//  QApplication::syncX();
	if (!myView.IsNull())
	{
		myView->MustBeResized();
		fitAll();
	}
}

void view::fitAll()
{
	myView->FitAll();
	myView->ZFitAll();
	myView->Redraw();
}

void view::fitArea()
{
	myCurrentMode = CurAction3d_WindowZooming;
}

void view::zoom()
{
	myCurrentMode = CurAction3d_DynamicZooming;
}

void view::pan()
{
	myCurrentMode = CurAction3d_DynamicPanning;
}

void view::rotation()
{
	myCurrentMode = CurAction3d_DynamicRotation;
}

void view::globalPan()
{
	// save the current zoom value
	myCurZoom = myView->Scale();
	// Do a Global Zoom
	myView->FitAll();
	// Set the mode
	//myCurrentMode = CurAction3d_GlobalPanning;
}

void view::front()
{
	/*myView->SetProj(V3d_Yneg);*/
	myView->SetProj(V3d_Zpos);
}

void view::back()
{
	myView->SetProj(V3d_Ypos);
}

void view::top()
{
	myView->SetProj(V3d_Zpos);
}

void view::bottom()
{
	myView->SetProj(V3d_Zneg);
}

void view::left()
{
	myView->SetProj(V3d_Xneg);
}

void view::right()
{
	myView->SetProj(V3d_Xpos);
}

void view::axo()
{
	myView->SetProj(V3d_XposYnegZpos);
}

void view::reset()
{
	myView->Reset();
}

void view::hlrOff()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	myHlrModeIsOn = Standard_False;
	myView->SetComputedMode(myHlrModeIsOn);
	QApplication::restoreOverrideCursor();
}

void view::hlrOn()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	myHlrModeIsOn = Standard_True;
	myView->SetComputedMode(myHlrModeIsOn);
	QApplication::restoreOverrideCursor();
}

void view::SetRaytracedShadows(bool theState)
{
	myView->ChangeRenderingParams().IsShadowEnabled = theState;

	myIsShadowsEnabled = theState;

	myContext->UpdateCurrentViewer();
}

void view::SetRaytracedReflections(bool theState)
{
	myView->ChangeRenderingParams().IsReflectionEnabled = theState;

	myIsReflectionsEnabled = theState;

	myContext->UpdateCurrentViewer();
}

void view::onRaytraceAction()
{
	QAction* aSentBy = (QAction*)sender();

	if (aSentBy == myRaytraceActions->at(ToolRaytracingId))
	{
		bool aState = myRaytraceActions->at(ToolRaytracingId)->isChecked();

		QApplication::setOverrideCursor(Qt::WaitCursor);
		if (aState)
			EnableRaytracing();
		else
			DisableRaytracing();
		QApplication::restoreOverrideCursor();
	}

	if (aSentBy == myRaytraceActions->at(ToolShadowsId))
	{
		bool aState = myRaytraceActions->at(ToolShadowsId)->isChecked();
		SetRaytracedShadows(aState);
	}

	if (aSentBy == myRaytraceActions->at(ToolReflectionsId))
	{
		bool aState = myRaytraceActions->at(ToolReflectionsId)->isChecked();
		SetRaytracedReflections(aState);
	}

	if (aSentBy == myRaytraceActions->at(ToolAntialiasingId))
	{
		bool aState = myRaytraceActions->at(ToolAntialiasingId)->isChecked();
		SetRaytracedAntialiasing(aState);
	}
}

void view::SetRaytracedAntialiasing(bool theState)
{
	myView->ChangeRenderingParams().IsAntialiasingEnabled = theState;

	myIsAntialiasingEnabled = theState;

	myContext->UpdateCurrentViewer();
}

void view::EnableRaytracing()
{
	if (!myIsRaytracing)
		myView->ChangeRenderingParams().Method = Graphic3d_RM_RAYTRACING;

	myIsRaytracing = true;

	myContext->UpdateCurrentViewer();
}

void view::DisableRaytracing()
{
	if (myIsRaytracing)
		myView->ChangeRenderingParams().Method = Graphic3d_RM_RASTERIZATION;

	myIsRaytracing = false;

	myContext->UpdateCurrentViewer();
}

void view::initViewActions()
{
	myViewActions = new QList<QAction*>();
	QAction* a;
	myViewToolBar = DMotion::getApplication()->addToolBar("View Operations");
	a = new QAction(QIcon(":/Resources/fitAll.png"), tr("&fit all"), this);
	a->setStatusTip(tr("fit all"));
	connect(a, SIGNAL(triggered()), this, SLOT(fitAll()));
	myViewActions->insert(VIEW_FIT_ALL, a);
// 
// 	a = new QAction(QIcon(":/Resources/globalPanning.png"), tr("&global pan"), this);
// 	a->setStatusTip(tr("global pan"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(globalPan()));
// 	myViewActions->insert(VIEW_GLOBAL_PAN, a);
// 
	a = new QAction(QIcon(":/Resources/frontView.png"), tr("&front view"), this);
	a->setStatusTip(tr("front view"));
	connect(a, SIGNAL(triggered()), this, SLOT(front()));
	myViewActions->insert(VIEW_FRONT, a);
// 
// 	a = new QAction(QIcon(":/Resources/backView.png"), tr("&back view"), this);
// 	a->setStatusTip(tr("back view"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(back()));
// 	myViewActions->insert(VIEW_BACK, a);
// 
// 	a = new QAction(QIcon(":/Resources/topView.png"), tr("&top view"), this);
// 	a->setStatusTip(tr("top view"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(top()));
// 	myViewActions->insert(VIEW_TOP, a);
// 
// 	a = new QAction(QIcon(":/Resources/bottomView.png"), tr("&bottom view"), this);
// 	a->setStatusTip(tr("bottom view"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(bottom()));
// 	myViewActions->insert(VIEW_BOTTOM, a);
// 
// 	a = new QAction(QIcon(":/Resources/leftView.png"), tr("&left view"), this);
// 	a->setStatusTip(tr("left view"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(left()));
// 	myViewActions->insert(VIEW_LEFT, a);
// 
// 	a = new QAction(QIcon(":/Resources/rightView.png"), tr("&right view"), this);
// 	a->setStatusTip(tr("right view"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(right()));
// 	myViewActions->insert(VIEW_RIGHT, a);
// 
// 	a = new QAction(QIcon(":/Resources/axoView.png"), tr("&axo view"), this);
// 	a->setStatusTip(tr("axo view"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(axo()));
// 	myViewActions->insert(VIEW_AXO, a);

	//QToolBar *viewToolBar = DMotion::getApplication()->getMainToolBar();
	for (int i = 0; i < myViewActions->size(); i++)
	{
		myViewToolBar->addAction(myViewActions->at(i));
	}
}

void view::initCursors()
{
	if (!defCursor)
		defCursor = new QCursor(Qt::ArrowCursor);
	if (!handCursor)
		handCursor = new QCursor(Qt::PointingHandCursor);
	if (!panCursor)
		panCursor = new QCursor(Qt::SizeAllCursor);
	if (!globPanCursor)
		globPanCursor = new QCursor(Qt::CrossCursor);
	if (!zoomCursor)
		zoomCursor = new QCursor(QPixmap(DMotion::getResourceDir() + QString("/") + QObject::tr("ICON_CURSOR_ZOOM")));
	if (!rotCursor)
		rotCursor = new QCursor(QPixmap(DMotion::getResourceDir() + QString("/") + QObject::tr("ICON_CURSOR_ROTATE")));
}

QList<QAction*>* view::getRaytraceActions()
{
	initRaytraceActions();
	return myRaytraceActions;
}

QPaintEngine* view::paintEngine() const
{
	return 0;
}

void view::initRaytraceActions()
{
	if (myRaytraceActions)
		return;

	myRaytraceActions = new QList<QAction*>();
	QString dir = DMotion::getResourceDir() + QString("/");
	QAction* a;

	a = new QAction(QPixmap(dir + QObject::tr("ICON_TOOL_RAYTRACING")), QObject::tr("MNU_TOOL_RAYTRACING"), this);
	a->setToolTip(QObject::tr("TBR_TOOL_RAYTRACING"));
	a->setStatusTip(QObject::tr("TBR_TOOL_RAYTRACING"));
	a->setCheckable(true);
	a->setChecked(false);
	connect(a, SIGNAL(triggered()), this, SLOT(onRaytraceAction()));
	myRaytraceActions->insert(ToolRaytracingId, a);

	a = new QAction(QPixmap(dir + QObject::tr("ICON_TOOL_SHADOWS")), QObject::tr("MNU_TOOL_SHADOWS"), this);
	a->setToolTip(QObject::tr("TBR_TOOL_SHADOWS"));
	a->setStatusTip(QObject::tr("TBR_TOOL_SHADOWS"));
	a->setCheckable(true);
	a->setChecked(true);
	connect(a, SIGNAL(triggered()), this, SLOT(onRaytraceAction()));
	myRaytraceActions->insert(ToolShadowsId, a);

	a = new QAction(QPixmap(dir + QObject::tr("ICON_TOOL_REFLECTIONS")), QObject::tr("MNU_TOOL_REFLECTIONS"), this);
	a->setToolTip(QObject::tr("TBR_TOOL_REFLECTIONS"));
	a->setStatusTip(QObject::tr("TBR_TOOL_REFLECTIONS"));
	a->setCheckable(true);
	a->setChecked(false);
	connect(a, SIGNAL(triggered()), this, SLOT(onRaytraceAction()));
	myRaytraceActions->insert(ToolReflectionsId, a);

	a = new QAction(QPixmap(dir + QObject::tr("ICON_TOOL_ANTIALIASING")), QObject::tr("MNU_TOOL_ANTIALIASING"), this);
	a->setToolTip(QObject::tr("TBR_TOOL_ANTIALIASING"));
	a->setStatusTip(QObject::tr("TBR_TOOL_ANTIALIASING"));
	a->setCheckable(true);
	a->setChecked(false);
	connect(a, SIGNAL(triggered()), this, SLOT(onRaytraceAction()));
	myRaytraceActions->insert(ToolAntialiasingId, a);
}

void view::setKeyState(bool b, int id)
{
	//keyID[id] = b;
}

void view::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case 82: 
		myCurrentMode = CurAction3d_DynamicRotation;
		com::write("Start dynamic rotation");
		break;
	case 84:
		myCurrentMode = CurAction3d_DynamicPanning;
		com::write("Start dynamic panning");
		break;
	case 90:
		myCurrentMode = CurAction3d_DynamicZooming;
		com::write("Start dynamic zooming");
		break;
	}
}

void view::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
		onLButtonDown((e->buttons() | e->modifiers()), e->pos());
	else if (e->button() == Qt::MidButton)
		onMButtonDown(e->buttons() | e->modifiers(), e->pos());
	else if (e->button() == Qt::RightButton)
		onRButtonDown(e->buttons() | e->modifiers(), e->pos());
}

void view::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
		onLButtonUp(e->buttons(), e->pos());
	else if (e->button() == Qt::MidButton)
		onMButtonUp(e->buttons(), e->pos());
	else if (e->button() == Qt::RightButton)
		onRButtonUp(e->buttons(), e->pos());
}

void view::mouseMoveEvent(QMouseEvent* e)
{
	onMouseMove(e->buttons(), e->pos());
}

void view::activateCursor(const CurrentAction3d mode)
{
	switch (mode)
	{
	case CurAction3d_DynamicPanning:
		setCursor(*panCursor);
		break;
	case CurAction3d_DynamicZooming:
		setCursor(*zoomCursor);
		break;
	case CurAction3d_DynamicRotation:
		setCursor(*rotCursor);
		break;
	case CurAction3d_GlobalPanning:
		setCursor(*globPanCursor);
		break;
	case CurAction3d_WindowZooming:
		setCursor(*handCursor);
		break;
	case CurAction3d_Nothing:
	default:
		setCursor(*defCursor);
		break;
	}
}

void view::onLButtonDown(const int/*Qt::MouseButtons*/ nFlags, const QPoint point)
{
	//  save the current mouse coordinate in min
	myXmin = point.x();
	myYmin = point.y();
	myXmax = point.x();
	myYmax = point.y();

	if (nFlags & CASCADESHORTCUTKEY)
	{
		myCurrentMode = CurAction3d_DynamicZooming;
	}
	else
	{
		switch (myCurrentMode)
		{
		case CurAction3d_Nothing:
			if (nFlags & MULTISELECTIONKEY)
				MultiDragEvent(myXmax, myYmax, -1);
			else
				DragEvent(myXmax, myYmax, -1);
			break;
		case CurAction3d_DynamicZooming:
			break;
		case CurAction3d_WindowZooming:
			break;
		case CurAction3d_DynamicPanning:
			break;
		case CurAction3d_GlobalPanning:
			break;
		case CurAction3d_DynamicRotation:
			if (myHlrModeIsOn)
			{
				myView->SetComputedMode(Standard_False);
			}
			myView->StartRotation(point.x(), point.y());
			break;
		default:
			Standard_Failure::Raise("incompatible Current Mode");
			break;
		}
	}
	activateCursor(myCurrentMode);
}

void view::onMButtonDown(const int/*Qt::MouseButtons*/ nFlags, const QPoint /*point*/)
{
	if (nFlags & CASCADESHORTCUTKEY)
		myCurrentMode = CurAction3d_DynamicPanning;
	activateCursor(myCurrentMode);
}

void view::onRButtonDown(const int/*Qt::MouseButtons*/ nFlags, const QPoint point)
{
	if (nFlags & CASCADESHORTCUTKEY)
	{
		if (myHlrModeIsOn)
		{
			myView->SetComputedMode(Standard_False);
		}
		myCurrentMode = CurAction3d_DynamicRotation;
		myView->StartRotation(point.x(), point.y());
	}
	else
	{
		Popup(point.x(), point.y());
	}
	activateCursor(myCurrentMode);
}

void view::onLButtonUp(Qt::MouseButtons nFlags, const QPoint point)
{
	switch (myCurrentMode)
	{
	case CurAction3d_Nothing:
		if (point.x() == myXmin && point.y() == myYmin)
		{
			// no offset between down and up --> selectEvent
			myXmax = point.x();
			myYmax = point.y();
			if (nFlags & MULTISELECTIONKEY)
				MultiInputEvent(point.x(), point.y());
			else
				InputEvent(point.x(), point.y());
		}
		else
		{
			DrawRectangle(myXmin, myYmin, myXmax, myYmax, Standard_False);
			myXmax = point.x();
			myYmax = point.y();
			if (nFlags & MULTISELECTIONKEY)
				MultiDragEvent(point.x(), point.y(), 1);
			else
				DragEvent(point.x(), point.y(), 1);
		}
		break;
	case CurAction3d_DynamicZooming:
		myCurrentMode = CurAction3d_Nothing;
		com::write("End dynamic zooming");
		//noActiveActions();
		break;
	case CurAction3d_WindowZooming:
		DrawRectangle(myXmin, myYmin, myXmax, myYmax, Standard_False);//,LongDash);
		myXmax = point.x();
		myYmax = point.y();
		if ((abs(myXmin - myXmax) > ValZWMin) ||
			(abs(myYmin - myYmax) > ValZWMin))
			myView->WindowFitAll(myXmin, myYmin, myXmax, myYmax);
		myCurrentMode = CurAction3d_Nothing;
		//noActiveActions();
		break;
	case CurAction3d_DynamicPanning:
		myCurrentMode = CurAction3d_Nothing;
		com::write("End dynamic panning");
		//noActiveActions();
		break;
	case CurAction3d_GlobalPanning:
		myView->Place(point.x(), point.y(), myCurZoom);
		myCurrentMode = CurAction3d_Nothing;
		//noActiveActions();
		break;
	case CurAction3d_DynamicRotation:
		myCurrentMode = CurAction3d_Nothing;
		com::write("End dynamic rotation");
		//noActiveActions();
		break;
	default:
		Standard_Failure::Raise(" incompatible Current Mode ");
		break;
	}
	setKeyState(false, 82);
	activateCursor(myCurrentMode);
	DMotion::getApplication()->onSelectionChanged();
}

void view::onMButtonUp(Qt::MouseButtons /*nFlags*/, const QPoint /*point*/)
{
	myCurrentMode = CurAction3d_Nothing;
	activateCursor(myCurrentMode);
}

void view::onRButtonUp(Qt::MouseButtons /*nFlags*/, const QPoint point)
{
// 	if (myCurrentMode == CurAction3d_Nothing)
// 		Popup(point.x(), point.y());
// 	else
// 	{
// 		QApplication::setOverrideCursor(Qt::WaitCursor);
// 		// reset tyhe good Degenerated mode according to the strored one
// 		//   --> dynamic rotation may have change it
// 		myView->SetComputedMode(myHlrModeIsOn);
// 		QApplication::restoreOverrideCursor();
// 		myCurrentMode = CurAction3d_Nothing;
// 	}
// 	activateCursor(myCurrentMode);
}

void view::onMouseMove(Qt::MouseButtons nFlags, const QPoint point)
{
	if (nFlags & Qt::LeftButton || nFlags & Qt::RightButton || nFlags & Qt::MidButton)
	{
		switch (myCurrentMode)
		{
		case CurAction3d_Nothing:
			myXmax = point.x();
			myYmax = point.y();
			DrawRectangle(myXmin, myYmin, myXmax, myYmax, Standard_False);
			if (nFlags & MULTISELECTIONKEY)
				MultiDragEvent(myXmax, myYmax, 0);
			else
				DragEvent(myXmax, myYmax, 0);
			DrawRectangle(myXmin, myYmin, myXmax, myYmax, Standard_True);
			break;
		case CurAction3d_DynamicZooming:
			myView->Zoom(myXmax, myYmax, point.x(), point.y());
			myXmax = point.x();
			myYmax = point.y();
			break;
		case CurAction3d_WindowZooming:
			myXmax = point.x();
			myYmax = point.y();
			DrawRectangle(myXmin, myYmin, myXmax, myYmax, Standard_False);
			DrawRectangle(myXmin, myYmin, myXmax, myYmax, Standard_True);
			break;
		case CurAction3d_DynamicPanning:
			myView->Pan(point.x() - myXmax, myYmax - point.y());
			myXmax = point.x();
			myYmax = point.y();
			break;
		case CurAction3d_GlobalPanning:
			break;
		case CurAction3d_DynamicRotation:
			myView->Rotation(point.x(), point.y());
			myView->Redraw();
			break;
		default:
			Standard_Failure::Raise("incompatible Current Mode");
			break;
		}
	}
	else
	{
		myXmax = point.x();
		myYmax = point.y();
		if (nFlags & MULTISELECTIONKEY)
			MultiMoveEvent(point.x(), point.y());
		else
			MoveEvent(point.x(), point.y());
	}
}

void view::DragEvent(const int x, const int y, const int TheState)
{
	// TheState == -1  button down
	// TheState ==  0  move
	// TheState ==  1  button up

	static Standard_Integer theButtonDownX = 0;
	static Standard_Integer theButtonDownY = 0;

	if (TheState == -1)
	{
		theButtonDownX = x;
		theButtonDownY = y;
	}

	if (TheState == 1)
	{
		myContext->Select(theButtonDownX, theButtonDownY, x, y, myView);
		emit selectionChanged();
	}
}

void view::InputEvent(const int /*x*/, const int /*y*/)
{
	myContext->Select();
	emit selectionChanged();
}

void view::MoveEvent(const int x, const int y)
{
	myContext->MoveTo(x, y, myView);
}

void view::MultiMoveEvent(const int x, const int y)
{
	myContext->MoveTo(x, y, myView);
}

void view::MultiDragEvent(const int x, const int y, const int TheState)
{
	static Standard_Integer theButtonDownX = 0;
	static Standard_Integer theButtonDownY = 0;

	if (TheState == -1)
	{
		theButtonDownX = x;
		theButtonDownY = y;
	}
	if (TheState == 0)
	{
		myContext->ShiftSelect(theButtonDownX, theButtonDownY, x, y, myView);
		emit selectionChanged();
	}
}

void view::MultiInputEvent(const int /*x*/, const int /*y*/)
{
	myContext->ShiftSelect();
	emit selectionChanged();
}

void view::Popup(const int /*x*/, const int /*y*/)
{
	DMotion* stApp = DMotion::getApplication();
	//QMdiArea* ws = DMotion::getWorkspace();
	//QMdiSubWindow* w = ws->activeSubWindow();
	if (myContext->NbSelected())
	{
// 		QList<QAction*>* aList = stApp->getToolActions();
// 		QMenu* myToolMenu = new QMenu(0);
// 		myToolMenu->addAction(aList->at(DMotion::ToolWireframeId));
// 		myToolMenu->addAction(aList->at(DMotion::ToolShadingId));
// 		myToolMenu->addAction(aList->at(DMotion::ToolColorId));
// 
// 		QMenu* myMaterMenu = new QMenu(myToolMenu);
// 
// 		QList<QAction*>* aMeterActions = DMotion::getApplication()->getMaterialActions();
// 
// 		QString dir = DMotion::getResourceDir() + QString("/");
// 		myMaterMenu = myToolMenu->addMenu(QPixmap(dir + QObject::tr("ICON_TOOL_MATER")), QObject::tr("MNU_MATER"));
// 		for (int i = 0; i < aMeterActions->size(); i++)
// 			myMaterMenu->addAction(aMeterActions->at(i));
// 
// 		myToolMenu->addAction(aList->at(DMotion::ToolTransparencyId));
// 		myToolMenu->addAction(aList->at(DMotion::ToolDeleteId));
// 		addItemInPopup(myToolMenu);
// 		myToolMenu->exec(QCursor::pos());
// 		delete myToolMenu;
	}
	else
	{
		if (!myBackMenu)
		{
			myBackMenu = new QMenu(0);

			QAction* a = new QAction(QObject::tr("MNU_CH_BACK"), this);
			a->setToolTip(QObject::tr("TBR_CH_BACK"));
			connect(a, SIGNAL(triggered()), this, SLOT(onBackground()));
			myBackMenu->addAction(a);
			addItemInPopup(myBackMenu);

			a = new QAction(QObject::tr("MNU_CH_ENV_MAP"), this);
			a->setToolTip(QObject::tr("TBR_CH_ENV_MAP"));
			connect(a, SIGNAL(triggered()), this, SLOT(onEnvironmentMap()));
			a->setCheckable(true);
			a->setChecked(false);
			myBackMenu->addAction(a);
			addItemInPopup(myBackMenu);
		}

		myBackMenu->exec(QCursor::pos());
	}
}

void view::addItemInPopup(QMenu* /*theMenu*/)
{
}

void view::DrawRectangle(const int MinX, const int MinY,
	const int MaxX, const int MaxY, const bool Draw)
{
	static Standard_Integer StoredMinX, StoredMaxX, StoredMinY, StoredMaxY;
	static Standard_Boolean m_IsVisible;

	StoredMinX = (MinX < MaxX) ? MinX : MaxX;
	StoredMinY = (MinY < MaxY) ? MinY : MaxY;
	StoredMaxX = (MinX > MaxX) ? MinX : MaxX;
	StoredMaxY = (MinY > MaxY) ? MinY : MaxY;

	QRect aRect;
	aRect.setRect(StoredMinX, StoredMinY, abs(StoredMaxX - StoredMinX), abs(StoredMaxY - StoredMinY));

	if (!myRectBand)
	{
		myRectBand = new QRubberBand(QRubberBand::Rectangle, this);
 		myRectBand->setStyle(QStyleFactory::create("windows"));
 		myRectBand->setGeometry(aRect);
 		myRectBand->show();

		/*QPalette palette;
		palette.setColor(myRectBand->foregroundRole(), Qt::white);
		myRectBand->setPalette(palette);*/
	}

	if (m_IsVisible && !Draw) // move or up  : erase at the old position
	{
		myRectBand->hide();
		delete myRectBand->style();
		delete myRectBand;
		myRectBand = 0;
		m_IsVisible = false;
	}

	if (Draw) // move : draw
	{
		//aRect.setRect( StoredMinX, StoredMinY, abs(StoredMaxX-StoredMinX), abs(StoredMaxY-StoredMinY));
 		m_IsVisible = true;
 		myRectBand->setGeometry(aRect);
		//myRectBand->show();
	}
}

void view::onBackground()
{
	QColor aColor;
	Standard_Real R1;
	Standard_Real G1;
	Standard_Real B1;
	myView->BackgroundColor(Quantity_TOC_RGB, R1, G1, B1);
	aColor.setRgb(R1 * 255, G1 * 255, B1 * 255);

	QColor aRetColor = QColorDialog::getColor(aColor);

	if (aRetColor.isValid())
	{
		R1 = aRetColor.red() / 255.;
		G1 = aRetColor.green() / 255.;
		B1 = aRetColor.blue() / 255.;
		myView->SetBackgroundColor(Quantity_TOC_RGB, R1, G1, B1);
	}
	myView->Redraw();
}

void view::onEnvironmentMap()
{
	if (myBackMenu->actions().at(1)->isChecked())
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
			tr("All Image Files (*.bmp *.gif *.jpg *.jpeg *.png *.tga)"));

		Handle(Graphic3d_TextureEnv) aTexture = new Graphic3d_TextureEnv(fileName.toLatin1().data());

		myView->SetTextureEnv(aTexture);
	}
	else
	{
		myView->SetTextureEnv(Handle(Graphic3d_TextureEnv)());
	}

	myView->Redraw();
}

bool view::dump(Standard_CString theFile)
{
	myView->Redraw();
	QString ext = QFileInfo(QString(theFile)).completeSuffix();
	if (!ext.compare("ps") || !ext.compare("eps") || !ext.compare("tex") || !ext.compare("pdf") || !ext.compare("svg") || !ext.compare("pgf"))
	{
		Graphic3d_ExportFormat exFormat;
		if (!ext.compare("ps"))
			exFormat = Graphic3d_EF_PostScript;
		if (!ext.compare("eps"))
			exFormat = Graphic3d_EF_EnhPostScript;
		if (!ext.compare("tex"))
			exFormat = Graphic3d_EF_TEX;
		if (!ext.compare("pdf"))
			exFormat = Graphic3d_EF_PDF;
		if (!ext.compare("svg"))
			exFormat = Graphic3d_EF_SVG;
		if (!ext.compare("pgf"))
			exFormat = Graphic3d_EF_PGF;
		try
		{
			myView->Export(theFile, exFormat);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	return myView->Dump(theFile);
}

Handle(V3d_View)& view::getView()
{
	return myView;
}

Handle(AIS_InteractiveContext)& view::getContext()
{
	return myContext;
}

view::CurrentAction3d view::getCurrentMode()
{
	return myCurrentMode;
}



