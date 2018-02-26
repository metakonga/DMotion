#include "dmotion.h"
#include "messageBox.h"
#include "vp_profile.h"
#include "plotDialog.h"
#include "document.h"
#include "translate.h"
#include "transparency.h"
#include "slider_crank.hpp"
#include "dual_motion.hpp"
#include "dual_motion_hole.hpp"
#include "animation_controller.h"
#include "materialDialog.h"
#include "selectReactionDialog.h"
#include "errors.h"
#include "newDialog.h"

//#include "resultTable.h"
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QComboBox>
#include <QTextStream>

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
static document* docu = 0;
static Ui::DMotionClass* userInterface = 0;
//static QMdiArea* stWs = 0;

DMotion::DMotion(QWidget *parent)
	: QMainWindow(parent, 0)
	, pBar(NULL)
	, vp(NULL)
	, cw(NULL)
	, kin(NULL)
	, doc(NULL)
	, graph(NULL)
	, plot(NULL)
	, odd(NULL)
	, srdlg(NULL)
	, timer(NULL)
	, rTable(NULL)
	, dv_nhcm(NULL)
	, dv_hcm(NULL)
	, md(NULL)
	, dcPlot(NULL)
	//, myFileBar(NULL)
	, myCasCadeBar(NULL)
	, myAnimationBar(NULL)
	, current_animation(-1)
	, tx(0)
	, _isNewAnalysis(false)
{
 	ui.setupUi(this);
	ui.DW_Modeling->setWindowTitle("Design and Modeling DockWindow");
	userInterface = &ui;

	myNbDocuments = 0;
	stApp = this;
	myIsDocuments = false;
	
	timer = new QTimer(this);
	
	connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimationFrame()));
	connect(ui.File_New, SIGNAL(triggered()), this, SLOT(file_new()));
	connect(ui.File_Open, SIGNAL(triggered()), this, SLOT(file_open()));
	connect(ui.File_Save, SIGNAL(triggered()), this, SLOT(file_save()));
	connect(ui.Tool_Graph, SIGNAL(triggered()), this, SLOT(tool_plot()));
	createCasCadeOperations();
	createAnimationOperations();
	createLineEditOperations();

	pBar = new QProgressBar;
	ui.statusBar->addWidget(pBar);
	pBar->hide();
 	TCollection_ExtendedString a3DName("Visu3D");
 	myViewer = Viewer(a3DName.ToExtString(), "", 1000.0, V3d_XposYnegZpos, Standard_True, Standard_True);
 	myViewer->SetDefaultLights();
 	myViewer->SetLightOn();
    myContext = new AIS_InteractiveContext(myViewer);
 	ctx = myContext;
	
   	QFrame *vb = new QFrame(this);
//	QFrame *plotFrame = new QFrame(this);
	QVBoxLayout* layout = new QVBoxLayout(vb);
   	layout->setMargin(0);
   	vb->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
   	setCentralWidget(vb);
   	
	ui.DW_Modeling->setMinimumWidth(500);
 	ui.DW_Modeling->setMaximumWidth(500);

	myView = new view(myContext, vb);
	
	//setPlotComboBox();
	layout->addWidget(myView);
	// // 	//setLayout(layout)
	connect(ui.Edit_VelocityProfile, SIGNAL(triggered()), this, SLOT(edit_velocity_profile()));
	connect(ui.File_Import, SIGNAL(triggered()), this, SLOT(file_import()));
	connect(myView, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
	connect(ui.actionResult_table, SIGNAL(triggered()), this, SLOT(openResultTable()));
	connect(ui.PB_ImportNozzelVelocity, SIGNAL(clicked()), this, SLOT(pushActiveVelocityBotton()));
	connect(ui.PB_ImportArcVelocity, SIGNAL(clicked()), this, SLOT(pushPassiveVelocityBotton()));
	connect(ui.PB_SelectParameters, SIGNAL(clicked()), this, SLOT(pushSelectParameters()));
	//connect(ui.TAB_MODELING, SIGNAL(currentChanged(int)), this, SLOT(changeModelingTab(int)));
	connect(ui.TAB_MODELING, SIGNAL(tabBarClicked(int)), this, SLOT(clickedTabBar(int)));
	
	connect(ui.PB_Shape, SIGNAL(clicked()), this, SLOT(clickApplyShape()));
	dv_hcm = new hcmDesignVariable(ui.DesignTabFrame);
	dv_nhcm = new nhcmDesignVariable(ui.DesignTabFrame);
	dv_hcm->setInitValue();
	dv_nhcm->setInitValue();
	file_new();
}

DMotion::~DMotion()
{
	if (doc) delete doc; doc = NULL;
  	if (vp) delete vp; vp = NULL;
  	if (cw) delete cw; cw = NULL;
  	if (kin) delete kin; kin = NULL;
  	if (myView) delete myView; myView = NULL;
// // 	if (graph) delete graph; graph = NULL;
  	if (timer) delete timer; timer = NULL;
  	if (plot) delete plot; plot = NULL;
  	
 	if (odd) delete odd; odd = NULL;
	if (rTable) delete rTable; rTable = NULL;
	if (srdlg) delete srdlg; srdlg = NULL;	
	if (pBar) delete pBar; pBar = NULL;
	if (md) delete md; md = NULL;
	if (dv_nhcm) delete dv_nhcm; dv_nhcm = NULL;
	if (dv_hcm) delete dv_hcm; dv_hcm = NULL;
	if (dcPlot) delete dcPlot; dcPlot = NULL;
	//qDeleteAll(models);
}

void DMotion::initialize(modelType mt)
{
	if (plot) delete plot; plot = NULL;
	if (doc) delete doc; doc = NULL;
	if (md) delete md; md = NULL;
	if (odd) delete odd; odd = NULL;
	if (cw) delete cw; cw = NULL;
	//if (dv_nhcm) delete dv_nhcm; dv_nhcm = NULL;
	//if (dv_hcm) delete dv_hcm; dv_hcm = NULL;
	if (dcPlot) delete dcPlot; dcPlot = NULL;
	if (srdlg) delete srdlg; srdlg = NULL;
	
	switch (mt)
	{
	case ORIGINAL_CAM_TYPE:
		md = new dual_motion;
		break;
	case HOLE_CAM_TYPE:
		md = new dual_motion_hole;
		break;
	default:
		break;
	}
// 	disconnect(ui.CB_Body, SLOT(changeComboBody(int)));
// 	disconnect(ui.CB_HardPoint, SLOT(changeComboBody(int)));
	ui.CB_Body->clear();
	ui.CB_HardPoint->clear();
	ui.CB_Body->insertItems(0, md->BodyList());
	ui.CB_HardPoint->insertItems(0, md->HardPointList());
	connect(ui.CB_Body, SIGNAL(currentIndexChanged(int)), this, SLOT(changeComboBody(int)));
	connect(ui.CB_HardPoint, SIGNAL(currentIndexChanged(int)), this, SLOT(changeComboHardPoint(int)));
	doc = new document(this);
	docu = doc;
	doc->setDisplayDynamicModel(md->RigidBodies(), md->HardPoints());
	plot = new plotWindow(md, this);
	cw = new commandWindow(this);
	if (!odd)
		odd = new optimumDesignDoc(md, plot);
	initializeDesignVariable();
	initializeBodyInformation();
	initializeHardPoint();
	initializeDrivingCondition();

	addDockWidget(Qt::BottomDockWidgetArea, cw);
	addDockWidget(Qt::LeftDockWidgetArea, plot);
	plot->resize(400, 400);
	resize(1200, 800);
	setFocusPolicy(Qt::StrongFocus);

	if (rTable) delete rTable; rTable = NULL;
	ui.TAB_MODELING->removeTab(2);
	myAnimationBar->hide();

	myView->front();
	myView->fitAll();
}

void DMotion::file_new()
{
	newDialog *nd = new newDialog;
	int ret = nd->callDialog();
	if (ret == 1)
	{
		initialize(nd->SelectedModelType());
		md->setModelName(nd->ModelName());
		md->setModelPath(nd->Directory() + "/" + nd->ModelName() + "/");
	}
	else if (ret == 0)
	{
		this->file_open(nd->OpenFilePath(), true);
	}
	else
	{
		dv_hcm->setDisableAndHide();
		dv_nhcm->setDisableAndHide();
		//addDockWidget(Qt::BottomDockWidgetArea, cw);
		//addDockWidget(Qt::LeftDockWidgetArea, plot);
	}
	current_animation = -1;
	delete nd;
}

void DMotion::file_open(QString f, bool isNew)
{
	QString fileName;
	if (!md && !isNew)
	{
		QString dir = "C:/";
		fileName = QFileDialog::getOpenFileName(this, tr("open"), dir, tr("Model file(*.mde)"));
	}
	else if (f.isEmpty())
	{
		QString dir = md->ModelPath() + md->ModelName() + ".mde";
		fileName = QFileDialog::getOpenFileName(this, tr("open"), dir, tr("Model file(*.mde)"));
	}
	else
	{
		fileName = f;
	}
	if (fileName.isEmpty())
		return;
	QFile qf(fileName);
	qf.open(QIODevice::ReadOnly);
	QTextStream qts(&qf);
	int mtype;
	QString str;
	qts >> str >> mtype >> str;
	initialize(modelType(mtype));
	int begin = fileName.lastIndexOf("/");
	QString m_path = fileName.left(begin+1);
	int mid = fileName.lastIndexOf(".");
	QString m_name = fileName.mid(begin + 1, mid - begin - 1);
	//md->setModelPath()
	md->setModelName(m_name);
	md->setModelPath(m_path);
// 	if (!f.isEmpty())
// 	{
// 		int begin = f.lastIndexOf("/");
// 		md->setModelPath(f.left(begin));
// 		int begin2 = f.lastIndexOf(".");
// 		md->setModelName(f.mid(begin+1, begin2 - begin - 1));
// 	}
	
	if (str == "Body_information")
	{
		QString x, y, angle, mass, inertia, shapePath;
		qts >> str >> str >> str >> str >> str >> str >> str;
		qts >> str;
		while (str != "end")
		{
			qts >> x >> y >> angle >> mass >> inertia >> shapePath;
			rigidBody* rb = md->RigidBodies()[str];
			rb->setPosition(x.toDouble() * 0.001, y.toDouble() * 0.001, 0.0);
			rb->setAngle(angle.toDouble() * (M_PI / 180.0));
			rb->setMass(mass.toDouble());
			rb->setInertia(inertia.toDouble() * 0.000001);
			rb->setShapePath(shapePath);
			com::write("Success : Body information of " + str);
			qts >> str;
		}
	}
	qts >> str;
	if (str == "HardPoint_information")
	{
		QString x, y;
		qts >> str >> str >> str;
		qts >> str;
		while (str != "end")
		{
			qts >> x >> y;
			hardPoint *hp = md->HardPoints()[str];
			hp->loc = vecd3(x.toDouble() * 0.001, y.toDouble() * 0.001, 0.0);
			hp->loc0 = hp->loc;
			com::write("Success : Information of " + str);
			qts >> str;
		}
	}
	qts >> str;
	if (str == "Driving_information")
	{
		QString path;
		qts >> str >> str;
		qts >> str;
		if (str == "Nozzle")
		{
			qts >> path;
			drivingConstraint* dc = md->DrivingConstraints()["Nozzle_driving"];
			if (dc->setVelocityProfile(path))
			{
				QVector<QPointF> nozzleV;
				for (int i = 0; i < dc->VelocityProfile().size(); i++)
				{
					if (!(i % 10))
						nozzleV.append(dc->TimeVelocity(i));
				}
				if (dcPlot)
					dcPlot->setArcPlot(nozzleV);
				com::write("Success : Loading of driving condition(Nozzle)");
			}
				
			else
				com::write("Fail : Loading of driving condition(Nozzle)");

		}
		qts >> str;
		if (str == "Arc")
		{
			qts >> path;
			drivingConstraint* dc = md->DrivingConstraints()["Arc_driving"];
			if (dc->setVelocityProfile(path))
			{
				QVector<QPointF> arcV;
				for (int i = 0; i < dc->VelocityProfile().size(); i++)
				{
					if (!(i % 10))
						arcV.append(dc->TimeVelocity(i));
				}
				if (dcPlot)
					dcPlot->setArcPlot(arcV);
				com::write("Success : Loading of driving condition(Arc)");
			}				
			else
				com::write("Fail : Loading of driving condition(Arc)");
		}
	}
	qts >> str;
	if (str == "Optimum_condition")
	{
		QString target, check;
		qts >> str;
		if (str == "0")
			ui.RB_OnlyOne->setChecked(true);
		else if (str == "1")
			ui.RB_SmallerThanFirst->setChecked(true);
		qts >> str >> str;
		qts >> target;
		while (target != "end")
		{
			qts >> check;
			srdlg->setCheck((reactionForceType)target.toInt(), check.toInt());
			qts >> target;
		}
	}
	qts >> str;
	if (str == "Design_variable")
	{
		qts >> str >> str >> str >> str >> str;
		if (md->ModelType() == ORIGINAL_CAM_TYPE)
			dv_nhcm->setFromFile(qts);
		else if (md->ModelType() == HOLE_CAM_TYPE)
			dv_hcm->setFromFile(qts);
	}
	qts >> str;
	if (str == "Space_constraint")
	{
		qts >> str >> str >> str;
		int check;
		QString sw, sh;
		qts >> check >> sw >> sh;
		ui.CB_SPACE->setChecked(check);
		ui.LE_Space_Width->setText(sw);
		ui.LE_Space_Height->setText(sh);
	}
	qf.close();
	//updateModelingLineEdit();
}

void DMotion::changeModelingTab(int idx)
{
	if (idx == 1)
	{

	}
}

void DMotion::file_save(QString f)
{
	QString fileName;
	if (f.isEmpty())
	{
		QString dir = md->ModelPath() + md->ModelName() + ".mde";
		fileName = QFileDialog::getSaveFileName(this, tr("save"), dir, tr("Model file(*.mde)"));
	}
	else
	{
		fileName = f;
	}
	
	if (fileName.isEmpty())
		return;
	//int loc = fileName.lastIndexOf("/");

	QFile qf(fileName);
	qf.open(QIODevice::WriteOnly);
	QTextStream qts(&qf);
	qts << "Model_type " << (int)md->ModelType() << endl;
	qts << "Body_information" << endl;
	qts << "Body PosX PosY Angle Mass Inertia ShapePath" << endl;
	foreach(QString rb_list, md->BodyList())
	{
		rigidBody *rb = md->RigidBodies()[rb_list];
		qts << rb_list << " " << rb->Position().X() * 1000.0 << " " << rb->Position().Y() * 1000.0 << " " << rb->Angle() * (180.0 / M_PI) << " " << rb->Mass() << " " << rb->Inertia() * 1000000.0 << " " << rb->ShapePath() << endl;
	}
	qts << "end" << endl;

	qts << "HardPoint_information" << endl;
	qts << "HardPoint X Y" << endl;
	foreach(QString hp_list, md->HardPointList())
	{
		hardPoint* hp = md->HardPoints()[hp_list];
		qts << hp_list << " " << hp->loc.X() * 1000.0 << " " << hp->loc.Y() * 1000.0 << endl;
	}
	qts << "end" << endl;

	qts << "Driving_information" << endl;
	qts << "Target File" << endl;
	if (md->DrivingConstraints()["Nozzle_driving"])
		qts << "Nozzle " << md->DrivingConstraints()["Nozzle_driving"]->FilePath() << endl;
	if (md->DrivingConstraints()["Arc_driving"])
		qts << "Arc " << md->DrivingConstraints()["Arc_driving"]->FilePath() << endl;
// 	qts << "Nozzle " << md->DrivingConstraints()["Nozzle_driving"]->FilePath() << endl
// 		<< "Arc " << md->DrivingConstraints()["Arc_driving"]->FilePath() << endl;

	qts << "Optimum_condition ";
	if (ui.RB_OnlyOne->isChecked())
		qts << "0 ";
	else if (ui.RB_SmallerThanFirst->isChecked())
		qts << "1";
	qts << endl;
	qts << "Target Check" << endl;
	QMapIterator<reactionForceType, bool> rList(odd->SelectList());
	while (rList.hasNext())
	{
		rList.next();
		qts << rList.key() << " " << rList.value() << endl;
	}
	qts << "end" << endl;

	qts << "Design_variable" << endl;
	qts << "Check Target Lower Step Upper" << endl;
	if (md->ModelType() == ORIGINAL_CAM_TYPE)
		dv_nhcm->saveToFile(qts);
	else if (md->ModelType() == HOLE_CAM_TYPE)
		dv_hcm->saveToFile(qts);
	qts << "Space_constraint" << endl;
	qts << "Check Width Height" << endl;
	qts << ui.CB_SPACE->isChecked() << " " << ui.LE_Space_Width->text() << " " << ui.LE_Space_Height->text() << endl;
	qf.close();
	com::write("Save model file : " + fileName);
}

void DMotion::closeEvent(QCloseEvent *event)
{
// 	if (rTable)
// 		if (rTable->isEnabled())
// 			rTable->close();
}

void DMotion::openResultTable()
{
	if (!odd->OptimumCases().size())
		return;
	if (!rTable)
		rTable = new resultTable(odd);
	else
		rTable->reset();
	rTable->ResultTable()->setSortingEnabled(false);
	foreach(optimumCase* oc, odd->OptimumCases())
	{
		QString cName = oc->Name();
		QList<double> dataList;
		foreach(reactionForceType rft, md->ReactionMap())
		{
			dataList.push_back(oc->MaximumReactions()[rft].maximum);
		}
		rTable->appendTable(cName, dataList);
	}
	ui.TAB_MODELING->addTab(rTable, "Results");
	/*connect(ui.TAB_MODELING, SIGNAL(tabBarClicked(int)), this, SLOT(clickedTabBar(int)));*/
	rTable->ResultTable()->sortByColumn(0, Qt::SortOrder::AscendingOrder);
	rTable->ResultTable()->setSortingEnabled(true);
	//rTable->setWindowModality(Qt::NonModal);
	ui.TAB_MODELING->setCurrentIndex(2);
	_isNewAnalysis = false;
}

void DMotion::pushActiveVelocityBotton()
{
	QString dir = "../data";// md->ModelPath();
	QString fileName = QFileDialog::getOpenFileName(this, tr("open"), dir, tr("Profile text file(*.txt)"));
	if (!fileName.isEmpty())
	{
		drivingConstraint* ad = md->DrivingConstraints()["Nozzle_driving"];
		ad->setVelocityProfile(fileName);
		QVector<QPointF> nozzleV;
		for (int i = 0; i < ad->VelocityProfile().size(); i++)
		{
			if (!(i % 10))
				nozzleV.append(ad->TimeVelocity(i));
		}
		if (dcPlot)
			dcPlot->setNozzlePlot(nozzleV);
	}

}

void DMotion::pushPassiveVelocityBotton()
{
	QString dir = "../data";
	QString fileName = QFileDialog::getOpenFileName(this, tr("open"), dir, tr("Profile text file(*.txt)"));
	if (!fileName.isEmpty())
	{
		drivingConstraint* pd = md->DrivingConstraints()["Arc_driving"];
		pd->setVelocityProfile(fileName);
		QVector<QPointF> arcV;
		for (int i = 0; i < pd->VelocityProfile().size(); i++)
		{
			if (!(i % 10))
				arcV.append(pd->TimeVelocity(i));
		}
		if (dcPlot)
			dcPlot->setArcPlot(arcV);		
	}
}

void DMotion::pushSelectParameters()
{
	if (!srdlg)
		srdlg = new selectReactionDialog(odd);
	srdlg->exec();
}

void DMotion::pushCaseSave()
{
	if (!odd)
		return;
	QString dir = md->ModelPath() + md->ModelName();
	QString path = md->ModelPath();// QFileDialog::getSaveFileName(this, tr("Save case"), dir);

	if (!path.isEmpty())
	{
		optimumCase* oc = odd->SelectedCase();
		QString directory = path + oc->Name() + "/";
		QDir qdir(directory);
		if (!qdir.exists())
			qdir.mkdir(directory);
		if (!oc)
			return;
		QVector<QPointF> profile = oc->CamProfileResults();
		QString fname = directory + "CamProfile.txt";
		QFile qf(fname);
		qf.open(QIODevice::WriteOnly);
		QTextStream qts(&qf);
		qts << /*"distance(mm)  " << "angle(degree) " <<*/ "x_pos(mm) " << "y_pos(mm)" << endl;
		foreach(QPointF p, profile)
		{
			double x = /*p.y() * cos(p.x())*/p.x() * 1000.0;
			double y = /*p.y() * sin(p.x())*/p.y() * 1000.0;
			qts << qSetRealNumberPrecision(10) << x << " " << y << endl;
		}
		qf.close();
		QMapIterator<QString, QVector<resultDataType>> rbody(oc->BodyResults());
	//	int loc = fileName.lastIndexOf("/");
		while (rbody.hasNext())
		{
			rbody.next();
			QString fname = directory + rbody.key() + ".txt";
			qf.setFileName(fname);
			qf.open(QIODevice::WriteOnly);
			qts << "time " << "pos_x " << "pos_y " << "angle " << "vel_x " << "vel_y " << "ang_vel " << "acc_x " << "acc_y " << "ang_acc" << endl;
			for (int i = 0; i < rbody.value().size(); i++)
			{
				resultDataType rdt = rbody.value().at(i);
				qts << rdt.time << " " << rdt.pos.X() << " " << rdt.pos.Y() << " " << rdt.ang << " " << rdt.vel.X() << " " << rdt.vel.Y() << " " << rdt.angv << " " << rdt.acc.X() << " " << rdt.acc.Y() << " " << rdt.anga << endl;
			}
			qf.close();
		}
		QMapIterator<QString, QVector<jointResultDataType>> rreact(oc->ReactionResults());
		while (rreact.hasNext())
		{
			rreact.next();
			QString fname = directory + rreact.key() + ".txt";
			qf.setFileName(fname);
			qf.open(QIODevice::WriteOnly);
			constraint *cons = md->Constraints()[rreact.key()];
			jointType jt;
			if (!cons)
				jt = POINTFOLLOWER;
			else
				jt = cons->JointType();
			switch (jt)
			{
			case TRANSLATION: qts << "time " << "FY " << "TR" << endl; break;
			case POINTFOLLOWER:
			case REVOLUTE: qts << "time " << "FX " << "FY" << endl; break;
			}
			for (int i = 0; i < rreact.value().size(); i++)
			{
				jointResultDataType jrdt = rreact.value().at(i);
				qts << jrdt.time << " " << jrdt.fx << " " << jrdt.fy << endl;
			}
			qf.close();
		}
		com::write("The selected case have been saved to " + directory);
	}
	
}

void DMotion::changeComboBody(int idx)
{
	if (idx < 0)
		return;
	double radian2degree = 180.0 / M_PI;
	double m2mm = 1000.0;
	double kgm2kgmm = 1000000.0;
	QString str = ui.CB_Body->itemText(idx);
	rigidBody* rb = md->RigidBodies()[str];
	ui.LE_X->setText(QString("%1").arg(rb->Position().X() * m2mm, 6, 'f', 6));
	ui.LE_Y->setText(QString("%1").arg(rb->Position().Y() * m2mm, 6, 'f', 6));
	ui.LE_Angle->setText(QString("%1").arg(rb->Angle() * radian2degree, 6, 'f', 6));
	ui.LE_Mass->setText(QString("%1").arg(rb->Mass(), 6, 'f', 6));
	ui.LE_Inertia->setText(QString("%1").arg(rb->Inertia() * kgm2kgmm, 6, 'f', 6));
	QString buttonName = rb->Name() + " Shape";
	ui.PB_Shape->setText(buttonName);
}

void DMotion::changeComboHardPoint(int idx)
{
	if (idx < 0)
		return;
	double m2mm = 1000.0;
	QString str = ui.CB_HardPoint->itemText(idx);
	hardPoint* hp = md->HardPoints()[str];
	ui.LE_HardPoint_X->setText(QString("%1").arg(hp->loc.X() * m2mm, 6, 'f', 6));
	ui.LE_HardPoint_Y->setText(QString("%1").arg(hp->loc.Y() * m2mm, 6, 'f', 6));
}

void DMotion::editLineEdit()
{
	QLineEdit* sendBy = (QLineEdit*)sender();
	QString str;
	if (sendBy == myLineEdits.at(LE_X))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double x = sendBy->text().toDouble() * 0.001;
		rb->setPosition(x, rb->Position().Y(), 0, true);

	}
	
	if (sendBy == myLineEdits.at(LE_Y))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double y = sendBy->text().toDouble() * 0.001;
		rb->setPosition(rb->Position().X(), y, 0, true);
	}

	if (sendBy == myLineEdits.at(LE_ANGLE))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double angle = sendBy->text().toDouble();
		rb->setAngle(angle * ((double)M_PI / 180.0), true);
	}

	if (sendBy == myLineEdits.at(LE_MASS))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double mass = sendBy->text().toDouble();
		rb->setMass(mass, true);
	}

	if (sendBy == myLineEdits.at(LE_INERTIA))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double inertia = sendBy->text().toDouble();
		rb->setInertia(inertia * 0.000001, true);
	}
// 	optimumCase* oc = odd->SelectedCase();
// 	QMap<QString, Handle(AIS_Shape)> hps = DMotion::getDocument()->getHardPoints();
// 	QMapIterator<QString, Handle(AIS_Shape)> ais(hps);
// 	while (ais.hasNext())
// 	{
// 		ais.next();
// 		QString hpName = ais.key();
// 		Handle(AIS_Shape) shape = ais.value();
// 		vecd3 loc0 = oc->HardPointsResults()[hpName].at(i);
// 		gp_Trsf t;
// 		t.SetTranslation(1000.0 * gp_Vec(loc0.X(), loc0.Y(), 0.0));
// 		shape->SetLocalTransformation(t);
// 	}
	if (sendBy == myLineEdits.at(LE_HARDPOINT_X))
	{
		str = ui.CB_HardPoint->currentText();
		hardPoint* hp = md->HardPoints()[str];
		double x = sendBy->text().toDouble() * 0.001;
		hp->loc.SetX(x);
		hp->loc0 = hp->loc;
		Handle(AIS_Shape) shape = doc->getHardPoints()[hp->name];
		gp_Trsf t;
		t.SetTranslation(gp_Vec(x, hp->loc.Y(), 0.0));
		shape->SetLocalTransformation(t);
		myContext->UpdateCurrentViewer();
	}

	if (sendBy == myLineEdits.at(LE_HARDPOINT_Y))
	{
		str = ui.CB_HardPoint->currentText();
		hardPoint* hp = md->HardPoints()[str];
		double y = sendBy->text().toDouble() * 0.001;
		hp->loc.SetY(y);
		hp->loc0 = hp->loc;
		Handle(AIS_Shape) shape = doc->getHardPoints()[hp->name];
		gp_Trsf t;
		t.SetTranslation(gp_Vec(hp->loc.X(), y , 0.0));
		shape->SetLocalTransformation(t);
		myContext->UpdateCurrentViewer();
	}
}

void DMotion::clickedTabBar(int idx)
{
	QString txt = ui.TAB_MODELING->tabText(idx);
	if (txt == "Results")
		ui.DW_Modeling->setMaximumWidth(524287);
	else
		ui.DW_Modeling->setMaximumWidth(500);
	if (txt == "Modeling")
	{
		changeComboBody(0);
		changeComboHardPoint(0);
	}
}

void DMotion::clickApplyShape()
{
	QString dir = "../data";
	QString shapePath = QFileDialog::getOpenFileName(this, tr("open"), dir, tr("IGES file (*.iges *.igs);;STEP file (*.stp *.step);;All files (*.*)"));
	if (shapePath.isEmpty())
		return;
	QString cur = ui.CB_Body->currentText();
	rigidBody *rb = md->RigidBodies()[cur];
	doc->DisplayShape(rb, shapePath);
	com::write("Success importing the " + cur + "shape.");
}

Handle(AIS_InteractiveContext) DMotion::getAISContext()
{
	return ctx;
}

Ui::DMotionClass* DMotion::getApplicationUI()
{
	return userInterface;
}

document* DMotion::getDocument()
{
	return docu;
}

void DMotion::setCaseResult()
{
	optimumCase *oc = odd->SelectedCase();
	com::printLine();
	QString info;
	QTextStream srm(&info);
	//srm.setFieldWidth(30);
	srm.setFieldAlignment(QTextStream::AlignCenter);
	srm << qSetFieldWidth(30) << "Name";
	//QMapIterator<QString, QVector<vecd3>> hprs(oc->HardPointsResults());
	foreach(QString str, md->HardPointList())
	{
		//QVector<vecd3> hprs = oc->HardPointsResults()[str];
		srm << qSetFieldWidth(22 + str.size()) << /*qSetFieldWidth(20) << center <<*/ str;
	}
	srm << qSetFieldWidth(0) << endl;
	//hprs.toFront();
	srm.setFieldAlignment(QTextStream::AlignCenter);
	srm << qSetFieldWidth(30) << oc->Name();
	foreach(QString str, md->HardPointList())
	{
		QVector<vecd3> hprs = oc->HardPointsResults()[str];
		vecd3 pos = hprs.at(0);
		srm << qSetFieldWidth(30) << "[" + QString("%1").arg(pos.X() * 1000, 2, 'f', 2) + ", " + QString("%1").arg(pos.Y() * 1000, 2, 'f', 2) + "]";
	}
	com::write(info);
	com::printLine();
	// qDebug() << "maxConstraintCamDistance : " << oc->profileMaxDistance();
}

void DMotion::createCasCadeOperations()
{
	QAction* a;
	a = new QAction(QIcon(":/Resources/new.png"), tr("&New"), this);
	a->setStatusTip(tr("New"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(NEW, a);

	a = new QAction(QIcon(":/Resources/open.png"), tr("&Open"), this);
	a->setStatusTip(tr("Open"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(OPEN, a);

	a = new QAction(QIcon(":/Resources/save.png"), tr("&Save"), this);
	a->setStatusTip(tr("Save"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(SAVE, a);

	a = new QAction(QIcon(":/Resources/solve.png"), tr("&analysis"), this);
	a->setStatusTip(tr("analysis"));
	connect(a, SIGNAL(triggered()), this, SLOT(analysis()));
	myToolActions.insert(SOLVE, a);

// 	a = new QAction(QIcon(":/Resources/stop.png"), tr("&analysis stop"), this);
// 	a->setStatusTip(tr("analysis stop"));
// 	connect(a, SIGNAL(triggered()), this, SLOT(analysis_stop()));
// 	myToolActions.insert(SOLVE_STOP, a);

	a = new QAction(QIcon(":/Resources/caseSave.png"), tr("&SaveCase"), this);
	a->setStatusTip(tr("Save the selected case information"));
	connect(a, SIGNAL(triggered()), this, SLOT(pushCaseSave()));
	myToolActions.insert(SAVE_CASE, a);

	a = new QAction(QIcon(":/Resources/plot.png"), tr("&velocity profile"), this);
	a->setStatusTip(tr("velocity profile"));
	connect(a, SIGNAL(triggered()), this, SLOT(onVelocityProfile()));
	myToolActions.insert(PROFILE, a);

	ui.mainToolBar->setWindowTitle("Tool Operations");
	int i = 0;
	for (; i < myToolActions.size(); i++)
	{
		ui.mainToolBar->addAction(myToolActions.at(i));
	}

	myCasCadeBar = addToolBar(tr("Shape Operations"));

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

	

	for (; i < myToolActions.size(); i++)
	{
		myCasCadeBar->addAction(myToolActions.at(i));
	}
	myCasCadeBar->show();
}

void DMotion::createAnimationOperations()
{
	myAnimationBar = addToolBar(tr("Animation Operations"));
	QAction *a;

	a = new QAction(QIcon(":/Resources/ani_tobegin.png"), tr("&toBegin"), this);
	a->setStatusTip(tr("Go to begin"));
	connect(a, SIGNAL(triggered()), this, SLOT(onGoToBegin()));
	myAnimationActions.insert(ANIMATION_GO_BEGIN, a);

	a = new QAction(QIcon(":/Resources/ani_moreprevious.png"), tr("&previous2X"), this);
	a->setStatusTip(tr("previous 2X"));
	connect(a, SIGNAL(triggered()), this, SLOT(onPrevious2X()));
	myAnimationActions.insert(ANIMATION_PREVIOUS_2X, a);

	a = new QAction(QIcon(":/Resources/ani_previous.png"), tr("&previous1X"), this);
	a->setStatusTip(tr("previous 1X"));
	connect(a, SIGNAL(triggered()), this, SLOT(onPrevious1X()));
	myAnimationActions.insert(ANIMATION_PREVIOUS_1X, a);

	a = new QAction(QIcon(":/Resources/ani_playback.png"), tr("&animation back play"), this);
	a->setStatusTip(tr("animation back play"));
	connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPlayBack()));
	myAnimationActions.insert(ANIMATION_PLAY_BACK, a);

	a = new QAction(QIcon(":/Resources/ani_init.png"), tr("&animation initialize"), this);
	a->setStatusTip(tr("animation initialize"));
	connect(a, SIGNAL(triggered()), this, SLOT(onGoFirstStep()));
	myAnimationActions.insert(ANIMATION_INIT, a);

	a = new QAction(QIcon(":/Resources/ani_play.png"), tr("&animation play"), this);
	a->setStatusTip(tr("animation play"));
	connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPlay()));
	myAnimationActions.insert(ANIMATION_PLAY, a);

	a = new QAction(QIcon(":/Resources/ani_fast.png"), tr("&forward1X"), this);
	a->setStatusTip(tr("forward 1X"));
	connect(a, SIGNAL(triggered()), this, SLOT(onForward1X()));
	myAnimationActions.insert(ANIMATION_FORWARD_1X, a);

	a = new QAction(QIcon(":/Resources/ani_morefast.png"), tr("&forward2X"), this);
	a->setStatusTip(tr("forward 2X"));
	connect(a, SIGNAL(triggered()), this, SLOT(onForward2X()));
	myAnimationActions.insert(ANIMATION_FORWARD_2X, a);

	a = new QAction(QIcon(":/Resources/ani_toEnd.png"), tr("&toEnd"), this);
	a->setStatusTip(tr("Go to end"));
	connect(a, SIGNAL(triggered()), this, SLOT(onGoToEnd()));
	myAnimationActions.insert(ANIMATION_GO_END, a);

	for (int i = 0; i < myAnimationActions.size(); i++)
	{
		myAnimationBar->addAction(myAnimationActions.at(i));
	}
	myAnimationBar->hide();
}

void DMotion::createLineEditOperations()
{
	myLineEdits.insert(LE_X, ui.LE_X);
	myLineEdits.insert(LE_Y, ui.LE_Y);
	myLineEdits.insert(LE_ANGLE, ui.LE_Angle);
	myLineEdits.insert(LE_MASS, ui.LE_Mass);
	myLineEdits.insert(LE_INERTIA, ui.LE_Inertia);
	myLineEdits.insert(LE_HARDPOINT_X, ui.LE_HardPoint_X);
	myLineEdits.insert(LE_HARDPOINT_Y, ui.LE_HardPoint_Y);

	for (int i = 0; i < myLineEdits.size(); i++)
	{
		connect(myLineEdits.at(i), SIGNAL(editingFinished()), this, SLOT(editLineEdit()));
	}
}

void DMotion::onToolAction()
{
 	QAction* sentBy = (QAction*)sender();
// 	QMdiArea* ws = ApplicationCommonWindow::getWorkspace();
// 	DocumentCommon* doc = qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget())->getDocument();

	if (sentBy == myToolActions.at(NEW))
		file_new();

	if (sentBy == myToolActions.at(OPEN))
		file_open();

	if (sentBy == myToolActions.at(SAVE))
		file_save();

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

// 	if (sentBy == myToolActions.at(TOOL_SOLVE))
// 		analysis();
// 
// 	if (sentBy == myToolActions.at(ToolDeleteId))
// 		doc->onDelete();

}

void DMotion::onVelocityProfile()
{
	edit_velocity_profile();
// 	double stroke = ui.DCLE_Stroke->text().toDouble();
// 	double ratio = ui.DCLE_Ratio->text().toDouble();
// 	double maxRelativeVelocity = ui.DCLE_MRV->text().toDouble();
// 	double maxRelativeVelocityTime = ui.DCLE_MRVT->text().toDouble();
// 	drivingConstraint* nozzle = md->DrivingConstraints()["nozzle_driving"];
// 	QVector<double> nozzleMotion = nozzle->VelocityProfile();
// 	double* arcVel = new double[nozzleMotion.size()];
// 	QVectorIterator<double> nziter(nozzleMotion);
// 	nziter.toBack();
// 
// 	while (nziter.hasPrevious())
// 	{
// 		double nz = nziter.previous();
// 		double ac = nz * 0.5;
// 	}
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
	}
		
	myContext->UpdateCurrentViewer();
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
	if (!vp)
		vp = new vp_profile(md->ModelPath(), this);
	vp->setActiveProfile(md->DrivingConstraints()["Nozzle_driving"]->VelocityProfile());
	vp->exec();
	delete vp;
	vp = NULL;
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
}

void DMotion::initializeDesignVariable()
{
	if (md->ModelType() == ORIGINAL_CAM_TYPE)
	{
		dv_hcm->setDisableAndHide();
		dv_nhcm->setEnableAndShow();
		dv_nhcm->setInitValue();
// 		dv_nhcm = new nhcmDesignVariable(ui.DesignTabFrame);
// 		//bool bb = ui.DesignTabFrame->layout()->isEmpty();
// 		dv_nhcm->setInitValue();
	}
	else if (md->ModelType() == HOLE_CAM_TYPE)
	{		
		dv_nhcm->setDisableAndHide();
		dv_hcm->setEnableAndShow();
		dv_hcm->setInitValue();
		//ui.DesignTabFrame->raise();
	//	bool bb = ui.DesignTabFrame->layout()->isEmpty();
		
// 		dv_hcm = new hcmDesignVariable(ui.DesignTabFrame);
// 		//bool bb = ui.DesignTabFrame->layout()->isEmpty();
// 		//dv_hcm->show();
// 		dv_hcm->setInitValue();
	}
// 	dv_hcm = new hcmDesignVariable(ui.DesignTabFrame);
// 	//bool bb = ui.DesignTabFrame->layout()->isEmpty();
// 	//dv_hcm->show();
// 	dv_hcm->setInitValue();
// 	dv_hcm->setEnabled(false);
// 	dv_hcm->hide();
	if (!srdlg)
	{
		srdlg = new selectReactionDialog(odd);
		srdlg->setupUi(md->ModelType());
	}
	ui.LE_Space_Width->setText("618");
	ui.LE_Space_Height->setText("140");
	ui.RB_OnlyOne->setChecked(true);
}

void DMotion::initializeBodyInformation()
{
	double radian2degree = 180.0 / M_PI;
	double m2mm = 1000.0;
	double kgm2kgmm = 1000000.0;
	foreach(QString str, md->BodyList())
	{
		rigidBody* rb = md->RigidBodies()[str];
		rb->setBody0();
	}
	changeComboBody(0);
}

void DMotion::initializeHardPoint()
{
	changeComboHardPoint(0);
}

void DMotion::onLineEditing()
{

}

void DMotion::initializeDrivingCondition()
{
	if (!dcPlot)
		dcPlot = new drivingConditionPlot(this, ui.Nozzle_Graph_Frame, ui.Arc_Graph_Frame);
	drivingConstraint* nozzleDC = md->DrivingConstraints()["Nozzle_driving"];
	drivingConstraint* arcDC = md->DrivingConstraints()["Arc_driving"];
	QVector<QPointF> nozzleV;
	QVector<QPointF> arcV;
	int sz = nozzleDC ? nozzleDC->VelocityProfile().size() : (arcDC ? arcDC->VelocityProfile().size() : 0);
	if (sz == 0)
		return;
	for (int i = 0; i < sz; i++)
	{
		if (!(i % 10))
		{
			if(nozzleDC)
				nozzleV.append(nozzleDC->TimeVelocity(i));
			if(arcDC)
				arcV.append(arcDC->TimeVelocity(i));
		}
	}
	if(nozzleV.size())
		dcPlot->setNozzlePlot(nozzleV);
	if(arcV.size())
		dcPlot->setArcPlot(arcV);
}

unsigned int DMotion::setSystemParameters()
{
	double mm2m = 0.001;
	double degree2radian = M_PI / 180.0;
	double kgmm2kgm = 1 / 1000000.0;
	MATD m_design(8, 3);
	int totalCase = 0;
	if (md->ModelType() == ORIGINAL_CAM_TYPE)
		totalCase = dv_nhcm->setSystemParameters(md);
	if (md->ModelType() == HOLE_CAM_TYPE)
		totalCase = dv_hcm->setSystemParameters(md);

	if (ui.RB_OnlyOne->isChecked())
		odd->setComparisonReactionType(ONLY_ONE);
	else if (ui.RB_SmallerThanFirst->isChecked())
		odd->setComparisonReactionType(SMALLER_FIRST);
	//md->PointFollower()->initialize(md->HardPoints()["cam_ground"]->loc, md->HardPoints()["cam_passive"]->loc);
	md->setSpaceConstraint(ui.LE_Space_Width->text().toDouble() * mm2m, ui.LE_Space_Height->text().toDouble() * mm2m);
	return totalCase;
}

bool DMotion::translate(const QString& file, const int format, const bool import)
{
	static Translate* anTrans = createTranslator();
	bool status;
	if (import)
		status = anTrans->importModel(file, format, myContext);

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

DMotion* DMotion::getApplication()
{
	return stApp;
}

void DMotion::tool_plot()
{
	if (!graph)
		graph = new plotDialog(this);
	if (graph->isVisible())
		return;
	graph->setModel(md);
	graph->show();
}

void DMotion::quitThread()
{
	kin->quit();
	kin->wait();
	disconnect(kin);
	if (kin) delete kin; kin = NULL;
	pBar->hide();
	myAnimationBar->show();
	openResultTable();
	QAction *a = myToolActions.at(SOLVE);
	a->disconnect();
	a->setIcon(QIcon(":/Resources/solve.png"));
	a->setStatusTip(tr("analysis."));
	connect(a, SIGNAL(triggered()), this, SLOT(analysis()));
}

void DMotion::analysisProcess(char c, QString str)
{
	switch (c)
	{
	case '@': cw->write("" + str); break;
	case 'L': cw->printLine(); break;
	case '!': cw->write("Error code " + str + " : " + errors::getErrorString(str.toInt()));
	}

}

void DMotion::updateProgressBar(int count)
{
	if (pBar)
		pBar->setValue(count);
}

void DMotion::analysis()
{
	if (rTable)
	{
		disconnect(ui.TAB_MODELING);
		ui.TAB_MODELING->removeTab(2);
		delete rTable;
		rTable = NULL;
	}
	unsigned int t = this->setSystemParameters();
	double expectTime = t * 0.05;
	int minute = static_cast<int>(expectTime / 60.0);
	int hour = minute / 60;
	if (minute > 60) minute = minute - (60 * hour);
	com::printLine();
	com::write(kor("예상되는 계산시간은 ") + QString("%1").arg(hour) + kor("시간 ") + QString("%1").arg(minute) + kor("분 입니다."));
	if (hour > 1)
	{
		int ret = messageBox::run(kor("해석에 소요되는 시간이 약 ") + QString("%1").arg(hour) + kor("시간 ") + QString("%1").arg(minute) + kor("분으로 예상됩니다."), kor("설계변수 범위 변경없이 해석을 수행하시겠습니까?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		switch (ret)
		{
		case QMessageBox::No:
			return;
		}
	}
	com::printLine();
	file_save(md->ModelPath() + md->ModelName() + ".mde");
	odd->clear();
	kin = new kinematics(md, odd);
	kin->setPlotWindow(plot);
	
	if (!pBar)
		pBar = new QProgressBar;
	pBar->setMaximum(t);
	pBar->show();
	connect(kin, SIGNAL(sendProcess(char, QString)), this, SLOT(analysisProcess(char, QString)));
	connect(kin, SIGNAL(sendCaseCount(int)), this, SLOT(updateProgressBar(int)));
	connect(kin, SIGNAL(finishedThread()), this, SLOT(quitThread()));
	connect(this, SIGNAL(analysisStopSignal()), kin, SLOT(setStopCondition()));
	QAction* a = myToolActions.at(SOLVE);
	a->disconnect();
	a->setIcon(QIcon(":/Resources/stop.png"));
	a->setStatusTip(tr("analysis stop."));
	connect(a, SIGNAL(triggered()), this, SLOT(analysis_stop()));

	kin->setSimulationCondition(0.00001, 0.035);
	kin->init();
	kin->start();
	_isNewAnalysis = true;
}

void DMotion::analysis_stop()
{
	emit analysisStopSignal();
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
		 myToolActions.at(TOOL_TRANSPARENCY)->setEnabled(OneOrMoreInShading);
	 }
	 else
	 {
		 myToolActions.at(TOOL_WIRE_FRAME)->setEnabled(false);
		 myToolActions.at(TOOL_SHADING)->setEnabled(false);
		 myToolActions.at(TOOL_TRANSPARENCY)->setEnabled(false);
	 }
}

void DMotion::onGoToBegin()
{
	animation_controller::initFrame();
	onAnimationPause();
	current_animation = ANIMATION_GO_BEGIN;
	animation_controller::setPlayEnable(false);
	updateAnimationFrame();
}

void DMotion::onGoToEnd()
{
	animation_controller::lastFrame();
	onAnimationPause();
	current_animation = ANIMATION_GO_END;
	animation_controller::setPlayEnable(false);
	updateAnimationFrame();
}

void DMotion::onPrevious2X()
{
	onAnimationPause();
	current_animation = ANIMATION_PREVIOUS_2X;
	onSetPlayAnimation();
}

void DMotion::onPrevious1X()
{
	onAnimationPause();
	current_animation = ANIMATION_PREVIOUS_1X;
	animation_controller::previous();
	animation_controller::setPlayEnable(false);
	updateAnimationFrame();
}

void DMotion::updateAnimationFrame()
{
	optimumCase* oc = odd->SelectedCase();
	unsigned int i = animation_controller::CurrentFrame();
	QMapIterator<QString, rigidBody*> r(md->RigidBodies());
	QMap<QString, Handle(AIS_Shape)> r_objs = doc->getRigidBodies();
	while (r.hasNext())
	{
		rigidBody* rb = r.next().value();
		if (rb->IsGround())
			continue;
		if (rb->ShapePath() == "None")
			continue;
		resultDataType rdt = oc->BodyResults()[rb->Name()].at(i);
		Handle(AIS_Shape) ais = r_objs[rb->Name()];
		gp_Trsf t;
		
		vecd3 pos = 1000.0 * rdt.pos;
		gp_Ax1 ax(gp_Pnt(0,0,0), gp_Vec(0, 0, 1));
		double ang = rdt.ang;
 		t.SetRotation(ax, ang);
 		t.SetTranslation(gp_Vec(pos.X(), pos.Y(), 0.0));
		ais->SetLocalTransformation(t);
	}
	
	QMap<QString, Handle(AIS_Shape)> hps = DMotion::getDocument()->getHardPoints();
	QMapIterator<QString, Handle(AIS_Shape)> ais(hps);
	while (ais.hasNext())
	{
		ais.next();
		QString hpName = ais.key();
		Handle(AIS_Shape) shape = ais.value();
		vecd3 loc0 = oc->HardPointsResults()[hpName].at(i);
		gp_Trsf t;
		t.SetTranslation(1000.0 * gp_Vec(loc0.X(), loc0.Y(), 0.0));
		shape->SetLocalTransformation(t);
	}

	myContext->UpdateCurrentViewer();
	if (animation_controller::IsPlay())
	{
		switch (current_animation)
		{
		case ANIMATION_PLAY: animation_controller::next(); break;
		case ANIMATION_PLAY_BACK: animation_controller::previous(); break;
		case ANIMATION_FORWARD_2X: animation_controller::next2x(); break;
		case ANIMATION_PREVIOUS_2X: animation_controller::previous2x(); break;
		}
	}
		/*animation_controller::next();*/
}

void DMotion::onSetPlayAnimation()
{
	optimumCase* oc = odd->SelectedCase();
	if (oc)
		animation_controller::setTotalFrame(oc->ResultCount());
	else
	{
		messageBox::run("First, select the case in the result table.");
		return;
	}
		
	animation_controller::setPlayEnable(true);
	QAction *a = NULL; //myAnimationActions[ANIMATION_PLAY];
	switch (current_animation)
	{
	case ANIMATION_PREVIOUS_2X: 
		a = myAnimationActions[ANIMATION_PREVIOUS_2X];
		break;
	case ANIMATION_FORWARD_2X:
		a = myAnimationActions[ANIMATION_FORWARD_2X];
		break;
	case ANIMATION_PLAY:
		a = myAnimationActions[ANIMATION_PLAY];
		break;
	case ANIMATION_PLAY_BACK:
		a = myAnimationActions[ANIMATION_PLAY_BACK];
		break;
	}
	a->disconnect();
	a->setIcon(QIcon(":/Resources/ani_pause.png"));
	a->setStatusTip(tr("Restart the animation."));
	connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPause()));
	timer->start(1);
}

void DMotion::onGoFirstStep()
{
	
	animation_controller::initFrame();
	onAnimationPause();
	current_animation = ANIMATION_INIT;
	animation_controller::setPlayEnable(false);
	updateAnimationFrame();
}

void DMotion::onAnimationPause()
{
	
	QAction *a = NULL;
	QString icon_path;
	switch (current_animation)
	{
	case ANIMATION_PLAY: 
		a = myAnimationActions[ANIMATION_PLAY]; 
		icon_path = ":/Resources/ani_play.png";
		break;
	case ANIMATION_PLAY_BACK: 
		a = myAnimationActions[ANIMATION_PLAY_BACK];
		icon_path = ":/Resources/ani_playback.png";
		break;
	case ANIMATION_PREVIOUS_2X:
		a = myAnimationActions[ANIMATION_PREVIOUS_2X];
		icon_path = ":/Resources/ani_moreprevious.png";
		break;
	case ANIMATION_FORWARD_2X:
		a = myAnimationActions[ANIMATION_FORWARD_2X];
		icon_path = ":/Resources/ani_morefast.png";
		break;
	default:
		return;
	}

	a->disconnect();
	a->setIcon(QIcon(icon_path));
	a->setStatusTip(tr("Pause the animation."));
	switch (current_animation)
	{
	case ANIMATION_PLAY:
		connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPlay()));
		break;
	case ANIMATION_PLAY_BACK:
		connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPlayBack()));
		break;
	case ANIMATION_PREVIOUS_2X:
		connect(a, SIGNAL(triggered()), this, SLOT(onPrevious2X()));
		break;
	case ANIMATION_FORWARD_2X:
		connect(a, SIGNAL(triggered()), this, SLOT(onForward2X()));
		break;
	}
	
	timer->stop();
}

void DMotion::onForward1X()
{
	onAnimationPause();
	current_animation = ANIMATION_FORWARD_1X;
	animation_controller::next();
	animation_controller::setPlayEnable(false);
	updateAnimationFrame();
}

void DMotion::onForward2X()
{
	onAnimationPause();
	current_animation = ANIMATION_FORWARD_2X;
	onSetPlayAnimation();
}

void DMotion::onAnimationPlayBack()
{
	onAnimationPause();
	current_animation = ANIMATION_PLAY_BACK;
	onSetPlayAnimation();
}

void DMotion::onAnimationPlay()
{
	onAnimationPause();
	current_animation = ANIMATION_PLAY;
	onSetPlayAnimation();
}

