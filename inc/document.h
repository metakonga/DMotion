#ifndef DOCUMENT_H 
#define DOCUMENT_H

#include <QObject.h>
#include <QString>
#include <QMap>
#include <QTableWidget>
#include <TopoDS_Shape.hxx>
#include <AIS_Shape.hxx>
#include <TopTools_HSequenceOfShape.hxx>

class DMotion;
class rigidBody;
class geometry;
struct hardPoint;

class document : public QObject
{
	Q_OBJECT
	enum { HARD_POINT_DISPLAY = 0, SHAPE_DISPLAY = 1 };
public:
	document(DMotion*);
	~document();

	//virtual Translate* createTranslator();
	//virtual int translationFormat(QString& fileName);
	QMap<QString, Handle(AIS_Shape)>& getHardPoints() { return hardPoints; }
	QMap<QString, Handle(AIS_Shape)> getRigidBodies() { return rigidBodies; }
	QTableWidget* getHPTable() { return hpTable; }
	void setDisplayDynamicModel(QMap<QString, rigidBody*>& r, QMap<QString, hardPoint*>& d);
	void DisplayShape(rigidBody* obj, QString shapePath);
	//bool translate(const QString& file, const int format, const bool import);

private:
	Handle(TopTools_HSequenceOfShape) importIGES(const QString&);
	Handle(TopTools_HSequenceOfShape) importSTEP(const QString&);
	void setDesignVariableInterface();

private:
	QMap<QString, Handle(AIS_Shape)> hardPoints;
	QMap<QString, Handle(AIS_Shape)> rigidBodies;
	QMap<QString, geometry*> geometries;
	QTableWidget *hpTable;
};

#endif