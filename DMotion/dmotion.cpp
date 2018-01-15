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
	, tx(0)
	, _isNewAnalysis(false)
{
 	ui.setupUi(this);
	userInterface = &ui;

	myNbDocuments = 0;
	stApp = this;
	myIsDocuments = false;
	cw = new commandWindow(this);
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
	connect(ui.CB_Body, SIGNAL(currentIndexChanged(int)), this, SLOT(changeComboBody(int)));
	connect(ui.CB_HardPoint, SIGNAL(currentIndexChanged(int)), this, SLOT(changeComboHardPoint(int)));

	file_new();
}

DMotion::~DMotion()
{
  	if (vp) delete vp; vp = NULL;
  	if (cw) delete cw; cw = NULL;
  	if (kin) delete kin; kin = NULL;
  	if (myView) delete myView; myView = NULL;
// // 	if (graph) delete graph; graph = NULL;
  	if (timer) delete timer; timer = NULL;
  	if (plot) delete plot; plot = NULL;
  	if (doc) delete doc; doc = NULL;
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
	if (dv_nhcm) delete dv_nhcm; dv_nhcm = NULL;
	if (dv_hcm) delete dv_hcm; dv_hcm = NULL;
	if (dcPlot) delete dcPlot; dcPlot = NULL;
	com::clear();

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
	ui.CB_Body->insertItems(0, md->BodyList());
	ui.CB_HardPoint->insertItems(0, md->HardPointList());
	doc = new document(this);
	docu = doc;
	doc->setDisplayDynamicModel(md->RigidBodies(), md->HardPoints());
	plot = new plotWindow(md, this);
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
		md->setModelPath(nd->Directory() + "/");
	}
	else if (ret == 0)
	{
		this->file_open(nd->OpenFilePath());
	}
	
	delete nd;
}

void DMotion::file_open(QString f)
{
	QString fileName;
	if (f.isEmpty())
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
	if (str == "Body_information")
	{
		QString x, y, angle, mass, inertia, shapePath;
		qts >> str >> str >> str >> str >> str >> str >> str;
		qts >> str;
		while (str != "end")
		{
			qts >> x >> y >> angle >> mass >> inertia >> shapePath;
			rigidBody* rb = md->RigidBodies()[str];
			rb->setPosition(x.toDouble(), y.toDouble(), 0.0);
			rb->setAngle(angle.toDouble());
			rb->setMass(mass.toDouble());
			rb->setInertia(inertia.toDouble());
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
			hp->loc = vecd3(x.toDouble(), y.toDouble(), 0.0);
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
		qts << rb_list << " " << rb->Position().X() << " " << rb->Position().Y() << " " << rb->Angle() << " " << rb->Mass() << " " << rb->Inertia() << " " << rb->ShapePath() << endl;
	}
	qts << "end" << endl;

	qts << "HardPoint_information" << endl;
	qts << "HardPoint X Y" << endl;
	foreach(QString hp_list, md->HardPointList())
	{
		hardPoint* hp = md->HardPoints()[hp_list];
		qts << hp_list << " " << hp->loc.X() << " " << hp->loc.Y() << endl;
	}
	qts << "end" << endl;

	qts << "Driving_information" << endl;
	qts << "Target File" << endl;
	qts << "Nozzle " << md->DrivingConstraints()["Nozzle_driving"]->FilePath() << endl
		<< "Arc " << md->DrivingConstraints()["Arc_driving"]->FilePath() << endl;

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
	connect(ui.TAB_MODELING, SIGNAL(tabBarClicked(int)), this, SLOT(clickedTabBar(int)));
	rTable->ResultTable()->sortByColumn(0, Qt::SortOrder::AscendingOrder);
	rTable->ResultTable()->setSortingEnabled(true);
	//rTable->setWindowModality(Qt::NonModal);
	_isNewAnalysis = false;
}

void DMotion::pushActiveVelocityBotton()
{
	QString dir = md->ModelPath();
	QString fileName = QFileDialog::getOpenFileName(this, tr("open"), dir, tr("Model file (*.mde);;Result file binary (*.bin);;All files (*.*)"));
	if (!fileName.isEmpty())
	{
		drivingConstraint* ad = md->DrivingConstraints()["Nozzel_driving"];
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
	QString dir = md->ModelPath();
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
			qts << /*p.y() * 1000.0 << " " << p.x() * (180.0 / M_PI) << " " <<*/ x << " " << y << endl;
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
}

void DMotion::changeComboHardPoint(int idx)
{
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
		double x = sendBy->text().toDouble();
		rb->setPosition(x, rb->Position().Y() * (1.0  / 1000.0), 0);
	}
	
	if (sendBy == myLineEdits.at(LE_Y))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double y = sendBy->text().toDouble();
		rb->setPosition(rb->Position().X() * (1.0 / 1000.0), y, 0);
	}

	if (sendBy == myLineEdits.at(LE_ANGLE))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double angle = sendBy->text().toDouble();
		rb->setAngle(angle * ((double)M_PI / 180.0));
	}

	if (sendBy == myLineEdits.at(LE_MASS))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double mass = sendBy->text().toDouble();
		rb->setMass(mass);
	}

	if (sendBy == myLineEdits.at(LE_INERTIA))
	{
		str = ui.CB_Body->currentText();
		rigidBody* rb = md->RigidBodies()[str];
		double inertia = sendBy->text().toDouble();
		rb->setInertia(inertia * (1.0 / 1000000.0));
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
		double x = sendBy->text().toDouble();
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
		double y = sendBy->text().toDouble();
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
	QMapIterator<QString, QVector<vecd3>> hprs(oc->HardPointsResults());
	while (hprs.hasNext())
	{
		hprs.next();
		srm << qSetFieldWidth(22 + hprs.key().size()) << /*qSetFieldWidth(20) << center <<*/ hprs.key();
	}
	srm << qSetFieldWidth(0) << endl;
	hprs.toFront();
	srm.setFieldAlignment(QTextStream::AlignCenter);
	srm << qSetFieldWidth(30) << oc->Name();
	while (hprs.hasNext())
	{
		hprs.next();
		vecd3 pos = hprs.value().at(0);
		srm << qSetFieldWidth(30) << "[" + QString("%1").arg(pos.X(), 6, 'f', 6) + ", " + QString("%1").arg(pos.Y(), 6, 'f', 6) + "]";
	}
	com::write(info);
	com::printLine();
// 	com::write("| Name : " + )
// 	ui.LE_CaseName->setText(oc->Name());
// 	vecd3 hp_pos0 = oc->HardPointsResults()["active_link"].at(0);
// 	ui.LE_CI_HeadLink_X->setText(QString("%1").arg(hp_pos0.X(), 6, 'f', 6));
// 	ui.LE_CI_HeadLink_Y->setText(QString("%1").arg(hp_pos0.Y(), 6, 'f', 6));
// 
// 	hp_pos0 = oc->HardPointsResults()["link_cam"].at(0);
// 	ui.LE_CI_LinkCam_X->setText(QString("%1").arg(hp_pos0.X(), 6, 'f', 6));
// 	ui.LE_CI_LinkCam_Y->setText(QString("%1").arg(hp_pos0.Y(), 6, 'f', 6));
// 
// 	hp_pos0 = oc->HardPointsResults()["cam_ground"].at(0);
// 	ui.LE_CI_CamRC_X->setText(QString("%1").arg(hp_pos0.X(), 6, 'f', 6));
// 	ui.LE_CI_CamRC_Y->setText(QString("%1").arg(hp_pos0.Y(), 6, 'f', 6));
// 
// 	hp_pos0 = oc->HardPointsResults()["cam_passive"].at(0);
// 	ui.LE_CI_CamPV_X->setText(QString("%1").arg(hp_pos0.X(), 6, 'f', 6));
// 	ui.LE_CI_CamPV_Y->setText(QString("%1").arg(hp_pos0.Y(), 6, 'f', 6));
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

	a = new QAction(QIcon(":/Resources/caseSave.png"), tr("&SaveCase"), this);
	a->setStatusTip(tr("Save the selected case information"));
	connect(a, SIGNAL(triggered()), this, SLOT(pushCaseSave()));
	myToolActions.insert(SAVE_CASE, a);

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

	a = new QAction(QIcon(":/Resources/plot.png"), tr("&velocity profile"), this);
	a->setStatusTip(tr("velocity profile"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(TOOL_PROFILE, a);

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

	a = new QAction(QIcon(":/Resources/ani_init.png"), tr("&animation initialize"), this);
	a->setStatusTip(tr("animation initialize"));
	connect(a, SIGNAL(triggered()), this, SLOT(onGoFirstStep()));
	myAnimationActions.insert(ANIMATION_INIT, a);

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

	if (sentBy == myToolActions.at(TOOL_PROFILE))
		onVelocityProfile();

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
		dv_nhcm = new nhcmDesignVariable(ui.DesignTabFrame);
		dv_nhcm->setInitValue();
	}
	else if (md->ModelType() == HOLE_CAM_TYPE)
	{
		dv_hcm = new hcmDesignVariable(ui.DesignTabFrame);
		dv_hcm->setInitValue();
	}
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
	for (int i = 0; i < nozzleDC->VelocityProfile().size(); i++)
	{
		if (!(i % 10))
		{
			nozzleV.append(nozzleDC->TimeVelocity(i));
			arcV.append(arcDC->TimeVelocity(i));
		}
	}
	dcPlot->setNozzlePlot(nozzleV);
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

	if (ui.RB_OnlyOne->isChecked())
		odd->setComparisonReactionType(ONLY_ONE);
	else if (ui.RB_SmallerThanFirst->isChecked())
		odd->setComparisonReactionType(SMALLER_FIRST);
	md->PointFollower()->initialize(md->HardPoints()["cam_ground"]->loc, md->HardPoints()["cam_passive"]->loc);
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
	//ui.statusBar->removeWidget(pBar);
	pBar->hide();
//	delete pBar; pBar = NULL;
	myAnimationBar->show();
	openResultTable();
}

void DMotion::analysisProcess(char c, QString str)
{
	//QString mode;
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
	file_save(md->ModelPath() + md->ModelName() + ".mde");
	odd->clear();
	kin = new kinematics(md, odd);
	kin->setPlotWindow(plot);
	unsigned int t = this->setSystemParameters();
	if (!pBar)
		pBar = new QProgressBar;

	//ui.statusBar->addWidget(pBar);
	pBar->setMaximum(t);
	pBar->show();
	connect(kin, SIGNAL(sendProcess(char, QString)), this, SLOT(analysisProcess(char, QString)));
	connect(kin, SIGNAL(sendCaseCount(int)), this, SLOT(updateProgressBar(int)));
	connect(kin, SIGNAL(finishedThread()), this, SLOT(quitThread()));
	kin->setSimulationCondition(0.00001, 0.035);
	kin->init();
	kin->start();
	_isNewAnalysis = true;
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
// 	QMapIterator<QString, rigidBody*> r(md->RigidBodies());
// 	QMap<QString, Handle(AIS_Shape)> r_objs = doc->getRigidBodies();
// 	while (r.hasNext())
// 	{
// 		rigidBody* rb = r.next().value();
// 		if (rb->IsGround())
// 			continue;
// 		if (rb->ShapePath().isEmpty())
// 			continue;
// 		resultDataType rdt = rb->ResultData()->at(i);
// 		Handle(AIS_Shape) ais = r_objs[rb->Name()];
// 		gp_Trsf t;
// 		
// 		//gp_Trsf a;
// 		vecd3 pos = 1000.0 * rdt.pos;
// 		gp_Ax1 ax(gp_Pnt(0,0,0), gp_Vec(0, 0, 1));
// 		//gp_Ax3 base(pos, gp_Vec(0, 0, 1), gp_Vec(1, 0, 0));
// 		double ang = rdt.ang;
// 		//t.SetTransformation(base/*.Rotated(gp_Ax1(pos, gp_Dir(0, 0, 1)), ang)*/);
//  		//t.SetRotation(ax, ang);
// 		t.SetValues(
// 			cos(ang), -sin(ang), 0, pos.X(),
// 			sin(ang), cos(ang), 0, pos.Y(),
// 			0, 0, 1, pos.Z());
//  		//t.SetTranslation(gp_Vec(pos.X(), pos.Y(), 0.0));
// 		//gp_TrsfForm f = t.Form();
// 		ais->SetLocalTransformation(t);
// 		//ais->SetLocalTransformation(a);
// 		//
// 		
// 	}
	optimumCase* oc = odd->SelectedCase();
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
// 	QMapIterator<QString, constraint*> c(md->Constraints());
// 	QMap<QString, Handle(AIS_Shape)> objs = doc->getHardPoints();
// 	optimumCase* oc = odd->SelectedCase();   
// 
// 	while (c.hasNext())
// 	{
// 		constraint* cs = c.next().value();
// 		if (cs->JointType() == DRIVING)
// 			continue;
// 		jointResultDataType jrdt = cs->ResultData()->at(i);
// 		hardPoint* hp = cs->BindedHardPoint();
// 		if (!hp) continue;
// 		Handle(AIS_Shape) ais = objs[hp->name];
// 		gp_Trsf t;
// 		vecd3 pos = 1000.0 * jrdt.loc;
// 		t.SetTranslation(gp_Vec(pos.X(), pos.Y(), 0.0));
// 		ais->SetLocalTransformation(t);		
// 	}
	myContext->UpdateCurrentViewer();
	if(animation_controller::IsPlay())
		animation_controller::next();
}

void DMotion::onAnimationPlay()
{
	optimumCase*  oc = odd->SelectedCase();
	if (oc)
		animation_controller::setTotalFrame(oc->ResultCount());
	else
	{
		messageBox::run("First, select the case in the result table.");
		return;
	}
		
	animation_controller::setPlayEnable(true);
	QAction *a = myAnimationActions[ANIMATION_PLAY];
	disconnect(a);
	a->setIcon(QIcon(":/Resources/ani_pause.png"));
	a->setStatusTip(tr("Restart the animation."));
	connect(a, SIGNAL(triggered()), this, SLOT(onAnimationPause()));
	timer->start(1);
}

void DMotion::onGoFirstStep()
{
	animation_controller::initFrame();
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

