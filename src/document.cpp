#include "document.h"
#include "dmotion.h"
#include "rigidBody.h"
#include "translate.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include "geometry_wedge.h"
#include <BRepPrimAPI_MakeSphere.hxx>
#include <IGESControl_Reader.hxx>
#include <IGESControl_Writer.hxx>
#include <IGESControl_Controller.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
#include <STEPControl_StepModelType.hxx>


document::document(DMotion* _dm)
	: QObject(_dm)
	, hpTable(NULL)
{
	//dm = _dm;
}

document::~document()
{
	if (geometries.size())
		qDeleteAll(geometries);
}

Handle(TopTools_HSequenceOfShape) document::importIGES(const QString& file)
{
	Handle(TopTools_HSequenceOfShape) aSequence;
	TCollection_AsciiString  aFilePath = file.toUtf8().data();

	IGESControl_Reader Reader;
	int status = Reader.ReadFile(aFilePath.ToCString());

	if (status == IFSelect_RetDone)
	{
		aSequence = new TopTools_HSequenceOfShape();
		Reader.TransferRoots();
		TopoDS_Shape aShape = Reader.OneShape();
		aSequence->Append(aShape);
	}
	return aSequence;
}

Handle(TopTools_HSequenceOfShape) document::importSTEP(const QString& file)
{
	Handle(TopTools_HSequenceOfShape) aSequence;
	TCollection_AsciiString  aFilePath = file.toUtf8().data();
	STEPControl_Reader aReader;
	IFSelect_ReturnStatus status = aReader.ReadFile(aFilePath.ToCString());
	if (status == IFSelect_RetDone)
	{
		//Interface_TraceFile::SetDefault();
		bool failsonly = false;
		aReader.PrintCheckLoad(failsonly, IFSelect_ItemsByEntity);

		int nbr = aReader.NbRootsForTransfer();
		aReader.PrintCheckTransfer(failsonly, IFSelect_ItemsByEntity);
		for (Standard_Integer n = 1; n <= nbr; n++)
		{
			bool ok = aReader.TransferRoot(n);
			int nbs = aReader.NbShapes();
			if (ok == true && nbs > 0)
			{
				aSequence = new TopTools_HSequenceOfShape();
				for (int i = 1; i <= nbs; i++)
				{
					TopoDS_Shape shape = aReader.Shape(i);
					aSequence->Append(shape);
				}
			}
		}
	}
	return aSequence;
}

void document::setDisplayDynamicModel(QVector<rigidBody*>& r, QVector<hardPoint*>& d)
{
	//geometry_wedge *w = new geometry_wedge("wedge");
	//geometries["wedge"] = w;
	//w->Make(10, 10, 10, 5);
	//DMotion::getAISContext()->Display(w->AIS(), false);
	//DMotion::getAISContext()->SetDisplayMode(w->AIS(), 1, false);
	
	
	hpTable = new QTableWidget(0, 3);
	QFrame *frame = new QFrame;
	QGridLayout *grid = new QGridLayout;
	QVBoxLayout *hpTable_layout = new QVBoxLayout;
	QLabel *L_hpTable = new QLabel("Hard Point Data");
	hpTable->setSelectionBehavior(QAbstractItemView::SelectItems);
	QStringList labels;
	labels << "Name" << "X Data" << "Y Data";
	hpTable->setHorizontalHeaderLabels(labels);
	hpTable->verticalHeader()->hide();
	hpTable->setShowGrid(true);
	hpTable->horizontalHeader()->setDefaultSectionSize(70);
	//hpTable->setTextElideMode(Qt::ElideMiddle);
	
	
	int nr = 0;
	QVectorIterator<hardPoint*> hps(d);
	while (hps.hasNext())
	{
		hardPoint* hp = hps.next();
		TopoDS_Shape s;
		s = BRepPrimAPI_MakeSphere(2);

		Handle(AIS_Shape) ais_s = new AIS_Shape(s);
		gp_Trsf t;
		vecd3 p = 1000.0 * hp->loc;
		t = ais_s->LocalTransformation();
		t.SetTranslation(gp_Vec(p.X(), p.Y(), 0.0));
		
		//ais_s->SetTr
		ais_s->SetLocalTransformation(t);
		t = ais_s->LocalTransformation();
		hardPoints[hp->name] = ais_s;
		DMotion::getAISContext()->Display(ais_s, false);
		DMotion::getAISContext()->SetDisplayMode(ais_s, 1, false);
		hpTable->insertRow(nr);
		hpTable->setItem(nr, 0, new QTableWidgetItem(hp->name));
		hpTable->setItem(nr, 1, new QTableWidgetItem(QString("%1").arg(p.X(), 4, 'f', 2, '0')));
		hpTable->setItem(nr, 2, new QTableWidgetItem(QString("%1").arg(p.Y(), 4, 'f', 2, '0')));
		nr++;
		//QLineEdit *LE_X = new QLineEdit;
	}

	QVectorIterator<rigidBody*> rbs(r);
	while (rbs.hasNext())
	{
		rigidBody* rb = rbs.next();
		QString shapePath = rb->ShapePath();
		if (!shapePath.isEmpty())
		{
			int type = -1;
			Handle(TopTools_HSequenceOfShape) shapes;
			int begin = shapePath.lastIndexOf(".");
			QString ext = shapePath.mid(begin);
			if (ext == ".igs" || ext == ".iges")
			{
				shapes = importIGES(shapePath);
			}
			else if (ext == ".step" || ext == ".stp")
			{
				shapes = importSTEP(shapePath);
			}
			Handle(AIS_Shape) ais_s = new AIS_Shape(shapes->Value(1));
			gp_Trsf t;
			vecd3 p = 1000.0 * rb->Position();
			t.SetTranslation(gp_Vec(p.X(), p.Y(), 0.0));
			ais_s->SetLocalTransformation(t);
			ais_s->SetMaterial(Graphic3d_NOM_STEEL);
			
			rigidBodies[rb->Name()] = ais_s;
			DMotion::getAISContext()->Display(ais_s, false);
			DMotion::getAISContext()->SetDisplayMode(ais_s, 1, false);
		}
	}

	hpTable->selectAll();
	QListIterator<QTableWidgetItem*> tw(hpTable->selectedItems());
	while (tw.hasNext())
	{
		tw.next()->setTextAlignment(Qt::AlignCenter);
	}
	hpTable->clearSelection();
	hpTable_layout->addWidget(L_hpTable);
	hpTable_layout->addWidget(hpTable);
	grid->addLayout(hpTable_layout, 0, 0);
	frame->setLayout(grid);
	grid->setMargin(0);
	DMotion::getApplicationUI()->DW_Modeling->setWidget(frame);
}

// Translate* document::createTranslator()
// {
// 	Translate* anTrans = new Translate(this/*, "Translator"*/);
// 	return anTrans;
// }

// int DMotion::translationFormat(QString& fileName)
// {
// 	int type = -1;
// 	int begin = fileName.lastIndexOf(".");
// 	QString ext = fileName.mid(begin);
// 	if (ext == ".igs" || ext == ".iges")
// 	{
// 		type = Translate::FormatIGES;
// 	}
// 	else if (ext == ".step" || ext == ".stp")
// 	{
// 		type = Translate::FormatSTEP;
// 	}
// 	return type;
// }

// bool document::translate(const QString& file, const int format, const bool import)
//{
//	static Translate* anTrans = createTranslator();
//	// 	DocumentCommon* doc = qobject_cast<MDIWindow*>(getWorkspace()->activeSubWindow()->widget())->getDocument();
//	// 	Handle(AIS_InteractiveContext) context = doc->getContext();
//	bool status;
//	if (import)
//		status = anTrans->importModel(file, format, DMotion::getAISContext());
//	//	else
//	//		status = anTrans->exportModel(file, format, myContext);
//
//	if (!status)
//	{
//		QString msg = QObject::tr("Translation error");
//		if (!anTrans->info().isEmpty())
//			msg += QString("\n") + anTrans->info();
//		//QMessageBox::critical(this, QObject::tr("Error"), msg, QObject::tr("Ok"), QString::null, QString::null, 0, 0);
//	}
//
//	return status;
//}