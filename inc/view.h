#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QAction>
#include <QCursor>
// #include <QList>

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>

class TopoDS_Shape;
class QRubberBand;

// //class COMMONSAMPLE_EXPORT View: public QWidget
class view : public QWidget
{
	Q_OBJECT
protected:
	enum CurrentAction3d {
		CurAction3d_Nothing, CurAction3d_DynamicZooming,
		CurAction3d_WindowZooming, CurAction3d_DynamicPanning,
		CurAction3d_GlobalPanning, CurAction3d_DynamicRotation
	};

public:
	enum ViewAction {
		VIEW_FIT_ALL, VIEW_GLOBAL_PAN, VIEW_FRONT, VIEW_BACK, VIEW_TOP, VIEW_BOTTOM, 
		VIEW_LEFT, VIEW_RIGHT, VIEW_AXO
	};
	enum RaytraceAction { ToolRaytracingId, ToolShadowsId, ToolReflectionsId, ToolAntialiasingId };
 
 	view(Handle(AIS_InteractiveContext) theContext, QWidget* parent);
 
 	~view();
 
 	virtual void                  init();
	bool                          dump(Standard_CString theFile);
	QList<QAction*>*              getRaytraceActions();
	bool                          isShadingMode();

	void                          EnableRaytracing();
	void                          DisableRaytracing();

	void                          SetRaytracedShadows(bool theState);
	void                          SetRaytracedReflections(bool theState);
	void                          SetRaytracedAntialiasing(bool theState);

	bool                          IsRaytracingMode() const { return myIsRaytracing; }
	bool                          IsShadowsEnabled() const { return myIsShadowsEnabled; }
	bool                          IsReflectionsEnabled() const { return myIsReflectionsEnabled; }
	bool                          IsAntialiasingEnabled() const { return myIsAntialiasingEnabled; }

	static QString                GetMessages(int type, TopAbs_ShapeEnum aSubShapeType,
		TopAbs_ShapeEnum aShapeType);
	static QString                GetShapeType(TopAbs_ShapeEnum aShapeType);

	Standard_EXPORT static void   OnButtonuseraction(int ExerciceSTEP,
		Handle(AIS_InteractiveContext)&);
	Standard_EXPORT static void   DoSelection(int Id,
		Handle(AIS_InteractiveContext)&);
	Standard_EXPORT static void   OnSetSelectionMode(Handle(AIS_InteractiveContext)&,
		Standard_Integer&,
		TopAbs_ShapeEnum& SelectionMode,
		Standard_Boolean&);
	virtual QPaintEngine*         paintEngine() const;
signals:
	void                          selectionChanged();

	public slots:
	void                          fitAll();
	void                          fitArea();
	void                          zoom();
	void                          pan();
	void                          globalPan();
	void                          front();
	void                          back();
	void                          top();
	void                          bottom();
	void                          left();
	void                          right();
	void                          axo();
	void                          rotation();
	void                          reset();
	void                          hlrOn();
	void                          hlrOff();
	//void                          updateToggled(bool);
	void                          onBackground();
	void                          onEnvironmentMap();
	void                          onRaytraceAction();

protected:
	virtual void                  paintEvent(QPaintEvent*);
	virtual void                  resizeEvent(QResizeEvent*);
	virtual void                  mousePressEvent(QMouseEvent*);
	virtual void                  mouseReleaseEvent(QMouseEvent*);
	virtual void                  mouseMoveEvent(QMouseEvent*);
	virtual void				  keyPressEvent(QKeyEvent *);

	virtual void                  addItemInPopup(QMenu*);

	Handle(V3d_View)&                     getView();
	Handle(AIS_InteractiveContext)&       getContext();
	void                                  activateCursor(const CurrentAction3d);
	void                                  Popup(const int x, const int y);
	CurrentAction3d                       getCurrentMode();

	virtual void                          onLButtonDown(const int nFlags, const QPoint point);
	virtual void                          onMButtonDown(const int nFlags, const QPoint point);
	virtual void                          onRButtonDown(const int nFlags, const QPoint point);
	virtual void                          onLButtonUp(Qt::MouseButtons nFlags, const QPoint point);
	virtual void                          onMButtonUp(Qt::MouseButtons nFlags, const QPoint point);
	virtual void                          onRButtonUp(Qt::MouseButtons nFlags, const QPoint point);
	virtual void                          onMouseMove(Qt::MouseButtons nFlags, const QPoint point);

private:
	void                          initCursors();
	void                          initViewActions();
	void                          initRaytraceActions();
	void                          DragEvent(const int x, const int y, const int TheState);
	void                          InputEvent(const int x, const int y);
	void                          MoveEvent(const int x, const int y);
	void                          MultiMoveEvent(const int x, const int y);
	void                          MultiDragEvent(const int x, const int y, const int TheState);
	void                          MultiInputEvent(const int x, const int y);
	void                          DrawRectangle(const int MinX, const int MinY,	const int MaxX, const int MaxY, const bool Draw);
	void						  setKeyState(bool b, int id);

private:
	bool                            myIsRaytracing;
	bool                            myIsShadowsEnabled;
	bool                            myIsReflectionsEnabled;
	bool                            myIsAntialiasingEnabled;
//	bool							keyID[256];
// 	bool                            myDrawRect;           // set when a rect is used for selection or magnify 
	Handle(V3d_View)                myView;
	Handle(AIS_InteractiveContext)  myContext;
	CurrentAction3d                 myCurrentMode;
	Standard_Integer                myXmin;
	Standard_Integer                myYmin;
	Standard_Integer                myXmax;
	Standard_Integer                myYmax;
 	Quantity_Factor                 myCurZoom;
 	Standard_Boolean                myHlrModeIsOn;
	QList<QAction*>*                myViewActions;
	QList<QAction*>*                myRaytraceActions;
	QMenu*                          myBackMenu;
 	QRubberBand*                    myRectBand; //!< selection rectangle rubber band
	QCursor* defCursor;
	QCursor* handCursor;
	QCursor* panCursor;
	QCursor* globPanCursor;
	QCursor* zoomCursor;
	QCursor* rotCursor;
};
 
 #endif
// 
// 