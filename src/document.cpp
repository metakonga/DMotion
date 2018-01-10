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
	if (hpTable) delete hpTable; hpTable = NULL;
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

void document::setDisplayDynamicModel(QMap<QString, rigidBody*>& r, QMap<QString, hardPoint*>& d)
{
	QMapIterator<QString, hardPoint*> hps(d);
	while (hps.hasNext())
	{
		hardPoint* hp = hps.next().value();
		TopoDS_Shape s;
		s = BRepPrimAPI_MakeSphere(4);

		Handle(AIS_Shape) ais_s = new AIS_Shape(s);
		gp_Trsf t;
		vecd3 p = 1000.0 * hp->loc;
		t = ais_s->LocalTransformation();
		t.SetTranslation(gp_Vec(p.X(), p.Y(), 0.0));

		ais_s->SetLocalTransformation(t);
		t = ais_s->LocalTransformation();
		hardPoints[hp->name] = ais_s;
		DMotion::getAISContext()->Display(ais_s, false);
		DMotion::getAISContext()->SetDisplayMode(ais_s, 1, false);
		//DMotion::getAISContext()->EraseAll(false);
	}
	//DMotion::getAISContext()->ClearLocalContext(AIS_CM_All);
// 	DMotion::getAISContext()->UpdateCurrentViewer();
	//hardPoints.erase(hardPoints.begin());
	//DMotion::getAISContext()->Delete();
	/*qDeleteAll(hardPoints);*/
	QMapIterator<QString, rigidBody*> rbs(r);
	while (rbs.hasNext())
	{
		rigidBody* rb = rbs.next().value();
		QString shapePath = rb->ShapePath();
		if (shapePath == "None")
			continue;
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
}

void document::setDesignVariableInterface()
{

}