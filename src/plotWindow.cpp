#include "plotWindow.h"
#include "optimumDesignDoc.h"
#include <QHBoxLayout>
#include "model.h"

plotWindow::plotWindow(model* _md, QWidget* parent)
	: QDockWidget(parent)
	, vcht(NULL)
	, m_min_y(DBL_MAX)
	, m_max_y(-DBL_MAX)
	, m_min_x(DBL_MAX)
	, m_max_x(-DBL_MAX)
	, cb_plot_object(NULL)
	, cb_plot_coord(NULL)
	, odd(NULL)
	, inObjectComboBox(false)
	, md(_md)
	, currentDataType(-1)
{
	vcht = new chartView(this);
	QFrame *plotFrame = new QFrame(this);
	plotFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	cb_plot_coord = new QComboBox(this);
	cb_plot_object = new QComboBox(this);
	cb_plot_coord->insertItem(0, "None");
	QHBoxLayout* combo_layout = new QHBoxLayout;
	combo_layout->addWidget(cb_plot_object);
	combo_layout->addWidget(cb_plot_coord);
	QVBoxLayout* plot_layout = new QVBoxLayout;
	plot_layout->addLayout(combo_layout);
	plot_layout->addWidget(vcht);
	plot_layout->setMargin(0);
	plotFrame->setLayout(plot_layout);
	
	//setLayout(plot_layout);
	setWidget(plotFrame);
	setMinimumSize(400, 400);
	setPlotComboBox();
	connect(cb_plot_object, SIGNAL(currentIndexChanged(int)), this, SLOT(changeObjectComboBox(int)));
	connect(cb_plot_coord, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCoordinateComboBox(int)));
}

plotWindow::~plotWindow()
{
	qDeleteAll(seriesMap);
}

void plotWindow::setPlotComboBox()
{
	if (!md)
		return;
	unsigned int idx = 1;
	cb_plot_object->insertItem(0, "None");
	foreach(QString str, md->BodyList())
	{
		rigidBody* rb = md->RigidBodies()[str];
		if (rb->IsGround())
			continue;
		cb_plot_object->insertItem(idx++, rb->Name());
	}

	foreach(QString str, md->ConstraintList())
	{
		constraint* cs = md->Constraints()[str];
		cb_plot_object->insertItem(idx++, cs->Name());
	}

	pointFollower* pf = md->PointFollower();
	if (pf)
	{
		cb_plot_object->insertItem(idx++, pf->Name());
	}
}

void plotWindow::bindOptimumDesignDoc(optimumDesignDoc* _odd)
{
	odd = _odd;
}

void plotWindow::updatePlotData()
{
	qDeleteAll(seriesMap);
	seriesMap.clear();
	pInfo.clear();
	//y_range.clear();
	currentSeries = "";
	changeCoordinateComboBox(currentDataType);
}

void plotWindow::updateByModelChange()
{
	cb_plot_object->clear();
	cb_plot_coord->clear();
	qDeleteAll(seriesMap);
	seriesMap.clear();
	pInfo.clear();
	//y_range.clear();
	currentSeries = "";
	setPlotComboBox();

}

void plotWindow::adjustAxisRange(QString str)
{
	//seriesMap[str]->show();
	//QPointF xRange = x_range[str];
	plotInfo *pi = &(pInfo[str]);
	double new_y_min = math::roundv(pi->y_range.x(), false);
	double new_y_max = math::roundv(pi->y_range.y(), true);
	if (new_y_min == 0) new_y_min = -1;
	if (new_y_max == 0) new_y_max = 1;
	pi->y_range = QPointF(new_y_min, new_y_max);
}

void plotWindow::showSeries(QString str)
{
	seriesMap[str]->show();
	plotInfo pi = pInfo[str];
	QPointF xRange = pi.x_range;
	QPointF yRange = pi.y_range;
	//if (xRange)
	vcht->setAxisRange(xRange.x(), xRange.y(), yRange.x(), yRange.y(), true);
	vcht->Chart()->axisX()->setTitleText(pi.x_title);
	vcht->Chart()->axisY()->setTitleText(pi.y_title);
	vcht->setTickCountY(7);
	currentSeries = str;
}

void plotWindow::hideSeries(QString str /* = "" */)
{
	if (str == "" && currentSeries == "")
		return;
	if (str != "") seriesMap[str]->hide();
	else seriesMap[currentSeries]->hide();
}

void plotWindow::setXRange(QString str, double mi, double ma)
{
	pInfo[str].x_range = QPointF(mi, ma);
}

void plotWindow::setYRange(QString str, double mi, double ma)
{
	pInfo[str].y_range = QPointF(mi, ma);
}

void plotWindow::setAxisTitle(QString str, QString xt, QString yt)
{
	pInfo[str].x_title = xt;
	pInfo[str].y_title = yt;
}

QLineSeries* plotWindow::createSeries(QString n)
{
	QLineSeries* lineSeries = new QLineSeries;
	lineSeries->setName(n);
	vcht->addSeries(lineSeries);
seriesMap[n] = lineSeries;
return lineSeries;
}

void plotWindow::appendData(QString n, double x, double y, bool urange)
{
	m_min_x = (m_min_x > x) ? x : m_min_x;
	m_max_x = (m_max_x < x) ? x : m_max_x;
	m_min_y = (m_min_y > y) ? y : m_min_y;
	m_max_y = (m_max_y < y) ? y : m_max_y;
	if (abs(m_min_y) < 0.0001)
		m_min_y = -0.0001;
	if (abs(m_max_y) < 0.0001)
		m_max_y = 0.0001;
	seriesMap[n]->append(x, y);
	// 	int r = round(m_min_y);
	// 	QString s_min_y = QString("%1").arg(r);
	// 	if (s_min_y.size() >= 3)
	// 	{
	// 		QString as;
	// 		for (int i = 1; i < s_min_y.size(); i++)
	// 			as.append('0');
	// 		s_min_y.replace(1, s_min_y.size() - 1, as);
	// 		s_min
	// 	}
	//s_min_y.replace(1, s_min_y.size() - 1, '0');
	//QString s_max_y = QString("%1").arg(round(m_max_y));
	// 	if (s_max_y.size() >= 3)
	// 		s_max_y.replace(2, s_max_y.size() - 1, '0');
	//r = round(r, -sc.size() + 1);
	setXRange(n, m_min_x, m_max_x);
	setYRange(n, m_min_y, m_max_y);

	// 	
	// 	if(urange)
	// 		vcht->setAxisRange(m_min_x, m_max_x, m_min_y, m_max_y);
}

void plotWindow::changeCoordinateComboBox(int)
{
	if (!odd)
		return;
	if (inObjectComboBox)
		return;
	this->hideSeries();
	m_min_y = DBL_MAX;
	m_max_y = -DBL_MAX;
	m_min_x = DBL_MAX;
	m_max_x = -DBL_MAX;
	QString x_title;
	QString y_title;
	QString objectName = cb_plot_object->currentText();
	QString coordName = cb_plot_coord->currentText();
	vcht->setTickCountX(8);
	int idx = cb_plot_coord->currentIndex();
	if (idx < 1)
		return;
	rigidBody* rb = md->RigidBodies()[objectName];
	double time = 0.0;
	double data = 0.0;
	QString plotName = objectName + "_" + coordName;
	if (seriesMap[plotName])
	{

		this->showSeries(plotName);
		return;
	}
	//pointFollower 
	if (!rb && md->PointFollower())
	{

		if (!odd->SelectedCase())
			return;
		pointFollower *pf = md->PointFollower();
		if (pf->Name() == objectName)
		{
			QVector<jointResultDataType> jrdts = odd->SelectedCase()->ReactionResults()[pf->Name()];
			if (jrdts.size() == 0)
				return;
			QLineSeries* series = this->createSeries(plotName);
			if (idx == 4)
			{
				x_title = "Horizontal(mm)";
				y_title = "Vertical(mm)";
				unsigned int cnt = 0;
				foreach(QPointF p, odd->SelectedCase()->CamProfileResults())
				{
					if (!(cnt % 10))
					{
						double x = p.x() * 1000;//s * cos(ang);
						double y = p.y() * 1000;//s * sin(ang);
						this->appendData(plotName, x, y, true);
					}
					cnt++;
				}
			}
			else if (idx == 5)
			{
				x_title = "Horizontal(mm)";
				y_title = "Vertical(mm)";
				unsigned int cnt = 0;
				foreach(QPointF p, odd->SelectedCase()->LastCamProfileResults())
				{
					if (!(cnt % 10))
					{
						double x = p.x() * 1000;
						double y = p.y() * 1000;
						this->appendData(plotName, x, y, true);
					}
					cnt++;
				}
			}
			else
			{
				x_title = "Time(sec)";
				y_title = "Force(kgf)";
				foreach(jointResultDataType jrdt, jrdts/**(cs->ResultData())*/)
				{
					time = jrdt.time;
					switch (idx)
					{
					case 1: data = jrdt.fx; break;
					case 2: data = jrdt.fy; break;
					case 3: data = 0; break;
					}
					this->appendData(plotName, time, data, true);
				}
			}

			this->hideSeries();
			this->setAxisTitle(plotName, x_title, y_title);
			this->adjustAxisRange(plotName);
			this->showSeries(plotName);
			return;
		}
	}

	if (rb)
	{
		if (!odd->SelectedCase())
			return;
		QLineSeries* series = this->createSeries(plotName);	
		unsigned int i = 0;
		QVector<resultDataType> rdts = odd->SelectedCase()->BodyResults()[rb->Name()];
		if (rdts.size() == 0)
			return;
		foreach(resultDataType rdt, rdts)
		{
// 			if (i % 10)
// 				continue;
			time = rdt.time;
			x_title = "Time(sec)";
			switch (idx)
			{
			case 1: data = rdt.pos.X() * 1000; y_title = "Pos X(mm)"; break;
			case 2: data = rdt.pos.Y() * 1000; y_title = "Pos Y(mm)"; break;
			case 3: data = rdt.ang; y_title = "Angle(rad)"; break;
			case 4: data = rdt.vel.X() * 1000; y_title = "Vel X(mm/s)"; break;
			case 5: data = rdt.vel.Y() * 1000; y_title = "Vel Y(mm/s)"; break;
			case 6: data = rdt.angv; y_title = "Rot. Vel.(rad/s)"; break;
			case 7: data = rdt.acc.X() * 1000; y_title = "Acc X(mm/s^2)"; break;
			case 8: data = rdt.acc.Y() * 1000; y_title = "Acc Y(mm/s^2)"; break;
			case 9: data = rdt.anga; y_title = "Rot. Acc.(rad/s^2) "; break;
			}
			this->appendData(plotName, time, data, true);
			i++;
		}
		this->hideSeries();
		this->setAxisTitle(plotName, x_title, y_title);
		this->adjustAxisRange(plotName);
		this->showSeries(plotName);
	}
	else
	{
		QLineSeries* series = this->createSeries(plotName);
		constraint* cs = md->Constraints()[objectName];
		if (cs->JointType() == DRIVING)
		{
			drivingConstraint* ds = md->DrivingConstraints()[objectName];
			if (idx == 1)
			{
				unsigned int i = 0;
				x_title = "Time(sec)";
				y_title = "Vel X(mm/s)";
				foreach(double m, ds->VelocityProfile())
				{
					if (!(i % 10))
					{
						time = 0.00001 * i;
						data = ds->VelocityProfile().at(i) * 1000;
						this->appendData(plotName, time, data, true);
					}
					i++;
				}
			}
			else if (idx == 2)
			{
				if (!odd->SelectedCase())
					return;
				if (ds->ResultData()->size() == 0)
					return;
				unsigned int i = 0;
				QVector<jointResultDataType> jrdts = odd->SelectedCase()->ReactionResults()[ds->Name()];
				if (jrdts.size() == 0)
					return;
				x_title = "Time(sec)";
				y_title = "Force(kgf)";
				foreach(jointResultDataType jrdt, *(ds->ResultData()))
				{
// 					if (i % 10)
// 						continue;
					time = jrdt.time;
					data = jrdt.fx;
					this->appendData(plotName, time, data, true);
					i++;
				}
			}
		}
		else if (cs->JointType() == SIMPLIFIED)
		{
			if (!odd->SelectedCase())
				return;
			simplifiedConstraint* sc = dynamic_cast<simplifiedConstraint*>(cs);
			QVector<jointResultDataType> jrdts = odd->SelectedCase()->ReactionResults()[cs->Name()];
			if (jrdts.size() == 0)
				return;
			x_title = "Time(sec)";
			y_title = "Force(kgf)";
			foreach(jointResultDataType jrdt, jrdts/**(cs->ResultData())*/)
			{
				time = jrdt.time;
				switch (idx)
				{
				case 1: data = sc->Direction() == simplifiedConstraint::HORIZONTAL ? jrdt.fx : (sc->Direction() == simplifiedConstraint::VERTICAL ? jrdt.fy : jrdt.tr); break;
				//case 3: data = jrdt.fy; break;
					//				case 3: data = jrdt.rz; break;
				}
				this->appendData(plotName, time, data, true);
			}
		}
		else
		{
			if (!odd->SelectedCase())
				return;
			QVector<jointResultDataType> jrdts = odd->SelectedCase()->ReactionResults()[cs->Name()];
			if (jrdts.size() == 0)
				return;
			x_title = "Time(sec)";
			y_title = "Force(kgf)";
			foreach(jointResultDataType jrdt, jrdts/**(cs->ResultData())*/)
			{
				time = jrdt.time;
				switch (idx)
				{
				case 1: data = jrdt.fx; break;
				case 2: data = jrdt.fy; break;
				case 3: data = jrdt.tr; break;
				}
				this->appendData(plotName, time, data, true);
			}
		}
		this->hideSeries();
		this->setAxisTitle(plotName, x_title, y_title);
		this->adjustAxisRange(plotName);
		this->showSeries(plotName);
	}
}

void plotWindow::changeObjectComboBox(int)
{
// 	if (!odd)
// 		return;
	inObjectComboBox = true;
	QString objectName = cb_plot_object->currentText();
	//cb_plot_coord->clear();
	rigidBody* rb = md->RigidBodies()[objectName];
	if (rb)
	{
		if (currentDataType != 0)
		{
			if (cb_plot_coord->count())
				cb_plot_coord->clear();
		}			
		else
		{
			inObjectComboBox = false;
			changeCoordinateComboBox(cb_plot_coord->currentIndex());			
			return;
		}
		cb_plot_coord->insertItem(0, "None");
		cb_plot_coord->insertItem(1, "X");
		cb_plot_coord->insertItem(2, "Y");
		cb_plot_coord->insertItem(3, "R");
		cb_plot_coord->insertItem(4, "VX");
		cb_plot_coord->insertItem(5, "VY");
		cb_plot_coord->insertItem(6, "VR");
		cb_plot_coord->insertItem(7, "AX");
		cb_plot_coord->insertItem(8, "AY");
		cb_plot_coord->insertItem(9, "AR");
		currentDataType = 0;
	}
	else
	{
		
		constraint* cs = md->Constraints()[objectName];
		if (!cs && objectName == md->PointFollower()->Name())
		{
			if (currentDataType != 3)
			{
				if (cb_plot_coord->count())
					cb_plot_coord->clear();
			}
			else
			{
				inObjectComboBox = false;
				changeCoordinateComboBox(cb_plot_coord->currentIndex());
				return;
			}
			cb_plot_coord->insertItem(0, "None");
			cb_plot_coord->insertItem(1, "FX");
			cb_plot_coord->insertItem(2, "FY");
			cb_plot_coord->insertItem(3, "TR");
			cb_plot_coord->insertItem(4, "CP");
			cb_plot_coord->insertItem(5, "LP");

			currentDataType = 3;
			inObjectComboBox = false;
			return;
		}
		if (cs->JointType() == DRIVING)
		{
			if (currentDataType != 1)
			{
				if (cb_plot_coord->count())
					cb_plot_coord->clear();
			}
			else
			{
// 				this->hideSeries();
// 				this->showSeries(objectName + "_" + cb_plot_coord->currentText());
				inObjectComboBox = false;
				changeCoordinateComboBox(cb_plot_coord->currentIndex());				
				return;
			}
			cb_plot_coord->insertItem(0, "None");
			cb_plot_coord->insertItem(1, "MOTION");
			cb_plot_coord->insertItem(2, "FD");
			currentDataType = 1;
		}
		else if (cs->JointType() == SIMPLIFIED)
		{
			simplifiedConstraint* sc = dynamic_cast<simplifiedConstraint*>(cs);
			//if (currentDataType != 2)
			//{
				if (cb_plot_coord->count())
					cb_plot_coord->clear();
// 			}
// 			else
// 			{
// 				inObjectComboBox = false;
// 				changeCoordinateComboBox(cb_plot_coord->currentIndex());
// 				return;
// 			}
			cb_plot_coord->insertItem(0, "None");
			cb_plot_coord->insertItem(1, sc->Direction() == simplifiedConstraint::HORIZONTAL ? "FX" : (sc->Direction() == simplifiedConstraint::VERTICAL ? "FY" : "TR"));
// 			cb_plot_coord->insertItem(2, "FY");
// 			cb_plot_coord->insertItem(3, "TR");
			currentDataType = 2;
		}
		else
		{
			if (currentDataType != 4)
			{
				if (cb_plot_coord->count())
					cb_plot_coord->clear();
			}
			else
			{
				inObjectComboBox = false;
				changeCoordinateComboBox(cb_plot_coord->currentIndex());
				return;
			}
			cb_plot_coord->insertItem(0, "None");
			cb_plot_coord->insertItem(1, "FX");
			cb_plot_coord->insertItem(2, "FY");
			cb_plot_coord->insertItem(3, "TR");
			currentDataType = 4;
		}
	}

	inObjectComboBox = false;
}