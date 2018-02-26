#include "pointFollower.h"
//#include <QFile>
#include <QPointF>
#include <QTextStream>

pointFollower::pointFollower(QString _name)
	: constraint(_name, POINTFOLLOWER)
	//, mch(NULL)
	, cur(0)
	, sr(0)
	, ds(0)
	//, dds(0)
	, pre_theta(0)
	, isSetVariableMarker(false)
	, result_s(0)
	, result_theta(0)
	, maxDistance(0)
	, incAngle(0)
{
	constraint::nDimension += 0;// 2;
	constraint::nrow = 2;
	constraint::nnz = 8;
	constraint::nTotalNNZ += constraint::nnz;
	jrforce = new double[constraint::nrow];
	rot_s = vecd3(0.29739, 0, 0) - vecd3(0.262163603372142, -0.030311213723227, 0.0);
	memset(jrforce, 0, sizeof(double) * constraint::nrow);
}

pointFollower::~pointFollower()
{
	//if (mch) delete mch; mch = NULL;
	//if (iqf.isOpen()) iqf.close();
}

void pointFollower::initialize(vecd3& hp0, vecd3& hp1)
{
	action_hp = hp0;
	vecd3 dp = hp1 - hp0;
	double len = math::length(dp);
	double ang = acos(dp.X() / len);
	if (dp.Y() < 0)
		ang = M_PI + (M_PI - ang);
	setInitialAngle(ang);
	initializeCurveData();
	setCM2HardPoint();
	updateBaseMarker();
	setLocalFromBaseBody();
	maxDistance = 0.0;
	incAngle = 0.0;
}

void pointFollower::setBaseMarker(vecd3 q, vecd3 r)
{
	baseMarker.s = math::global2local(ib->TM(), pos - ib->Position());
	baseMarker.actionAxis = math::cross(q, r);
}

void pointFollower::setLocalFromBaseBody()
{
	local_vector = pos - ib->Position();
}

void pointFollower::setCurrentStep(unsigned int cid)
{
	current_step = cid;
}

vecd3 pointFollower::LocalFromBaseBody()
{
	return local_vector;
}

void pointFollower::appendProfileData(double th, double s)
{ 
// 	if (s > maxDistance)
// 		maxDistance = s;
	ss.push_back(QPointF(th, s));
	double _ds;
	double _dth;
	unsigned int sz = ss.size();
	if (sz == 2)
	{
		_ds = ss.at(sz - 1).y() - ss.at(sz - 2).y();
		_dth = ss.at(sz - 1).x() - ss.at(sz - 2).x();
		ds.push_back(_ds / _dth);
		//dthdt.push_back(_dth / 0.00001);
		//ds.push_back(0.0);
	}
	else if (sz > 2)
	{
		_ds = ss.at(sz - 1).y() - ss.at(sz - 3).y();
	//	uble _dds = ss.at(sz - 1).y() - 2.0 * ss.at(sz - 2).y() + ss.at(sz - 3).y();
		_dth = ss.at(sz - 1).x() - ss.at(sz - 3).x();
		//double _ddth = (ss.at(sz - 1).x() - ss.at(sz - 2).x()) * (ss.at(sz - 2).x() - ss.at(sz - 3).x());
		if (_dth == 0)
			ds.push_back(0);
		else
		{
			ds.push_back(_ds / _dth);
			//dthdt.push_back(0.5 * _dth / 0.00001);
		}
	}
}

void pointFollower::saveProfileData(QString _path)
{
	QFile qf(_path);
	qf.open(QIODevice::WriteOnly);
	QTextStream qts(&qf);
	foreach(QPointF p, ss)
	{
		qts << p.x() << " " << p.y() << " " << p.y() * cos(p.x()) << " " << p.y() * sin(p.x()) << endl;
	}
	qf.close();
}

// void pointFollower::defineFollower(QString _path, vecd3 cp)
// {
// 	if (!mch)
// 		mch = new MCHSpline;
// 	profile_path = _path;
// 	QFile qf(profile_path);
// 	qf.open(QIODevice::ReadOnly);
// 	QTextStream qts(&qf);
// 	double x = 0.0;
// 	double y = 0.0;
// 	while (!qts.atEnd())
// 	{
// 		qts >> x;
// 		rdata.push_back(vecd3(0.001*x, y, 0.0));
// 	}
// 	qf.close();
// 	double th[25] =
// 	{ 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70,
// 	75, 80, 85, 90, 95, 100, 105, 110, 115, 119.74 };
// 	double dist[25] =
// 	{ 120, 120, 120, 120, 120, 120, 120, 120, 120, 119.9, 119.4, 117.7, 113.6, 104.7,
// 	87.7, 70.0, 60.6, 55.8, 51.4, 47.2, 43.2, 39.4, 35.8, 32.6, 29.9 };
// 
// 	for (unsigned int i = 0; i < 25; i++)
// 	{
// 		mch->monotonic_cubic_Hermite_spline(QPointF((th[i] + 180) * M_PI / 180, 0.001 * dist[i]));
// 	}
// 	QVector<QPointF> data;
// 	mch->calculate_curve_auto(data);
// 
// // 	QFile qff("C:/DMotion/ccc.txt");
// // 	qff.open(QIODevice::WriteOnly);
// // 	qf.open(QIODevice::ReadOnly);
// 	iqf.setFileName("C:/DMotion/data/inverpolation_data.txt");
// 	iqf.open(QIODevice::WriteOnly);
// 	QTextStream q1ts(&iqf);
// 	for (unsigned int i = 0; i < data.size(); i++)
// 	{
// 		q1ts << data.at(i).x() << " " << data.at(i).y() << endl;
// 	}
// 	iqf.close();
// 
// // 	QTextStream qts(&qf);
// // 	QTextStream qqts(&qff);
// // 	double x = 0;
// // 	double y = 0;
// // 	//vecd3 iLoc = cp - ib->Position();
// // 	QPointF rp;
// // 	vecd3 r;
// // 	while (!qts.atEnd())
// // 	{
// // 		qts >> x >> y;
// // 		double radian = x * M_PI / 180;
// // 		deg.push_back(radian);
// // 		double rx = cp.X() - (0.001 * y) * cos(radian);
// // 		double ry = cp.Y() - (0.001 * y) * sin(radian);
// // 		qqts << rx << " " << ry << endl;
// // 		r.SetX(rx);
// // 		r.SetY(ry);
// // 		r.SetZ(0.0);
// // 		r = math::global2local(TM(ib->Angle()), r - ib->Position());
// // 		xdata.push_back(r.X());
// // 	//	mch->monotonic_cubic_Hermite_spline(QPointF(r.X(), r.Y()));
// // 		mch->monotonic_cubic_Hermite_spline(QPointF(radian, 0.001 * y));
// // 	}
// // 	qf.close();
// // 	qff.close();
// }

// void pointFollower::defineDegreeLength(QString path)
// {
// 	QFile qf(path);
// 	qf.open(QIODevice::ReadOnly);
// 	QTextStream qts(&qf);
// 	while (! qts.atEnd())
// 	{
// 		double th = 0.0;
// 		double len = 0.0;
// 		qts >> th >> len;
// 		ss.push_back(QPointF(th, len));
// 	}
// 	qf.close();
// 	ds.push_back(0.0);
// 	//dds.push_back(0.0);
// 	for (unsigned int i = 1; i < ss.size()-1; i++)
// 	{
// 		double _ds = ss.at(i + 1).y() - ss.at(i - 1).y();
// 		double _dth = ss.at(i + 1).x() - ss.at(i - 1).x();
// 		if (_dth == 0)
// 			ds.push_back(0);
// 		else
// 			ds.push_back(_ds / _dth);
// 	}
// 	ds.push_back(0.0);
// // 	QFile qf_dds("C:/DMotion/data/acc2.txt");
// // 	qf_dds.open(QIODevice::ReadOnly);
// // 	QTextStream qtss(&qf_dds);
// // 	while (!qtss.atEnd())
// // 	{
// // 		double _dds = 0;
// // 		qtss >> _dds;
// // 		dds.push_back(_dds);
// // 	}
// // 	qf_dds.close();
// 	dds.push_back((ds.at(1) - ds.at(0)) / (ss.at(1).x() - ss.at(0).x()));
// 	for (unsigned int i = 1; i < ss.size() - 1; i++)
// 	{
//  		double _ds = ss.at(i + 1).y() - 2.0 * ss.at(i).y() + ss.at(i - 1).y();
//  		double _dth = (ss.at(i + 1).x() - ss.at(i).x()) * (ss.at(i).x() - ss.at(i - 1).x());
// // 		double _ds = ss.at(i + 1).y() - ss.at(i - 1).y();
// // 		double _dth = ss.at(i + 1).x() - ss.at(i - 1).x();
// 		if (_dth == 0)
// 			dds.push_back(0);
// 		else
// 			dds.push_back(_ds / (/*2.0 * */_dth));
// 	}
// 	unsigned int sz = ss.size();
// 	dds.push_back((ds.at(sz - 1) - ds.at(sz - 2)) / (ss.at(sz - 1).x() - ss.at(sz - 2).x()));
// 
// }

int pointFollower::constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul)
{
	unsigned int ci = ib->ID() * 3 + 1;
	unsigned int cj = jb->ID() * 3;
	transformationMatrix Ai = TM(q(ci + 2));
	transformationMatrix Aj = TM(q(cj + 2));
	vecd3 pi(q(ci), q(ci + 1), 0.0);
	vecd3 pj(q(cj), q(cj + 1), 0.0);
	double theta = q(cj + 3);
	double deg_theta = theta * 180 / M_PI;
	double s0 = ss.at(s_step).y();//mch->getInterpValue(theta);
	double s_r = math::length(s - pj);
	//double rx = (xdata.at(cur) * (angle - deg.at(cur + 1)) - xdata.at(cur + 1) * (angle - deg.at(cur))) / (deg.at(cur) - deg.at(cur + 1));
	//double ry = mch->getInterpValue(cur, rx);
	//QTextStream qts(&iqf);
	actionMarker.s.SetX(rot_s.X() + s0 * cos(theta));
	actionMarker.s.SetY(rot_s.Y() + s0 * sin(theta));
	//vecd3 r = rdata.at(s_step);
// 	if (!isSetVariableMarker)
// 	{ 		
// 		actionMarker.s = math::global2local(Aj, r - pj);
//  		isSetVariableMarker = true;
// 	}

	//baseMarker.s.SetX(rx);
	//baseMarker.s.SetY(ry);
	//vecd3 pp = pj + math::local2global(Aj, actionMarker.s);
	//qts << pp.X() << " " << pp.Y() << endl;
	vecd3 ce = pi + math::local2global(Ai, baseMarker.s) - pj - math::local2global(Aj, actionMarker.s);// pi + math::local2global(Ai, baseMarker.s) - r;
	rhs(i) = mul * ce.X();
	rhs(i + 1) = mul * ce.Y();
	return 0;
}

//void pointFollower::setDistance2Curve(VECD &q)
// {
// 	unsigned int cj = jb->ID() * 3;
// 	transformationMatrix Aj = TM(q(cj + 2));
// 	vecd3 pj(q(cj), q(cj + 1), 0.0);
// 	//vecd3 r = rdata.at(s_step);
// 	s = rdata.at(s_step);
// 	sr = math::length(s - pj);
// 	//s = math::length(r);
// 	for_s = rdata.at(s_step + 1);
// 	//s = math::length(r - pj);//actionMarker.s = math::global2local(Aj, r - pj);
// 	pre_theta = q(cj + 3);
// }

// void pointFollower::setDerivative2Curve(VECD &q)
// {
// // 	unsigned int cj = jb->ID() * 3;
// // 	double theta = q(cj + 3);
// // 	double d_theta = theta - pre_theta;
// // 	double pre_s = math::length(rdata.at(s_step - 1) - pj)
// }

// void pointFollower::timeDistance(VECD& rhs, VECD& q)
// {
// 	unsigned int ci = ib->ID() * 3 + 1;
// 	unsigned int cj = jb->ID() * 3;
// 	//setSinCos(qd(ci + 2), qd(cj + 2));
// 	transformationMatrix dAi = derivateTM(q(ci + 2));
// 	transformationMatrix dAj = derivateTM(q(cj + 2));
// 	double angj = q(cj + 2);
// 	double theta = q(cj + 3);
// 	vecd3 pj = vecd3(q(cj), q(cj + 1), 0.0);
// 	//double srr = math::length(s - pj);
// 	double dtheta = theta - pre_theta;
// 	double for_sr = math::length(for_s - pj);
// 	double dsdt = (for_sr - sr) / 0.00001;
// 	//if (dtheta)
// 	rhs(10) = dsdt * (-cos(angj)*cos(theta)) + dsdt*(sin(angj) * sin(theta));
// 	rhs(11) = dsdt * (-sin(angj)*cos(theta)) - dsdt*(cos(angj) * sin(theta));
// }

void pointFollower::followerJacobian(VECD& q, SMATD& lhs, unsigned int r, unsigned int c)
{
	unsigned int cj = jb->ID() * 3;
	transformationMatrix dAj = derivateTM(q(cj + 2));
	double angj = q(cj + 2);
	double theta = ss.at(current_step).x();
	vecd3 pj = vecd3(q(cj), q(cj + 1), 0.0);
	double s0 = ss.at(current_step).y();
	double dsdtheta = ds.at(current_step);
	lhs(r, c) = ((-cos(angj) * (dsdtheta * cos(theta) - s0 * sin(theta)) + sin(angj) * (dsdtheta * sin(theta) + s0 * cos(theta))));
	lhs(r + 1, c) = ((-sin(angj) * (dsdtheta * cos(theta) - s0 * sin(theta)) - cos(angj) * (dsdtheta * sin(theta) + s0 * cos(theta))));
}

void pointFollower::initializeCurveData()
{
	cpXY.clear();
	ss.clear();
	ds.clear();
	endXY.clear();
}

void pointFollower::setCM2HardPoint()
{
	rot_s = action_hp - jb->Position();
}

QVector<QPointF>& pointFollower::ProfileData()
{
	return cpXY;
}

QVector<QPointF>& pointFollower::LastProfileData()
{
	return endXY;
}

void pointFollower::updateBaseMarker()
{
	baseMarker.s = math::global2local(ib->TM(), pos - ib->Position());
}

void pointFollower::constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int r, bool isjp)
{
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;
	//setSinCos(qd(ci + 2), qd(cj + 2));
	transformationMatrix dAi = derivateTM(q(ci + 2));
	transformationMatrix dAj = derivateTM(q(cj + 2));
	double angj = q(cj + 2);
	double theta = ss.at(current_step).x();// q(cj + 3);
	vecd3 pj = vecd3(q(cj), q(cj + 1), 0.0);
	//double srr = math::length(s - pj);
	double dtheta = theta - pre_theta;
	//double for_sr = math::length(for_s - pj);
	double s0 = ss.at(current_step).y();// mch->getInterpValue(theta);
	double dsdtheta = ds.at(current_step);// mch->calculate_derivative(theta);
	result_s = s0;
	result_dsdt = dsdtheta;
	result_theta = theta;
	//double sx = s0 * cos(theta);
	//double sy = s0 * sin(theta);
	double s_x = rot_s.X() + s0 * cos(theta);
	double s_y = rot_s.Y() + s0 * sin(theta);
	//actionMarker.s.SetX(s_x);
	//actionMarker.s.SetY(s_y);
	//double s_x = cpXY.at(current_step).x();
	//double s_y = cpXY.at(current_step).y();
	//double rs_x = s_x + rot_s.X();
	//double rs_y = s_y + rot_s.Y();
	//if (dtheta)
		//dsdtheta = (for_sr - sr) / 0.00001;
// 	else
// 		dsdtheta = 0;
// 	if (s_step == 0)
// 		dsdtheta = 0;
// 	actionMarker.s.SetX(sr * cos(theta));
// 	actionMarker.s.SetY(sr * sin(theta));
// 	// Constraint jacobian of base body
	///double s0c = s0 * cos(theta);
	//double s0s = s0 * sin(theta);
	////double s_r = math::length(s - pj);
	if (ci)
	{
		ci -= 3;
		lhs(r, ci) = -1;
		lhs(r + 1, ci + 1) = -1;
		vecd3 up = math::local2global(dAi, baseMarker.s);
		lhs(r, ci + 2) = -up.X();
		lhs(r + 1, ci + 2) = -up.Y();
	}
	if (cj)
	{
		cj -= 3;
		lhs(r, cj) = 1;
		lhs(r + 1, cj + 1) = 1;
		//vecd3 up = math::local2global(dAj, actionMarker.s);
		lhs(r, cj + 2) = -(sin(angj) * (s_x) + cos(angj) * (s_y));
		lhs(r + 1, cj + 2) = -(-cos(angj) * (s_x) + sin(angj) * (s_y));
// 		lhs(r, cj + 3) = cos(angj) * (sr * sin(theta)/* - dsdtheta * cos(theta)*/) + sin(angj) * (sr * cos(theta)/* - dsdtheta * sin(theta)*/);
// 		lhs(r + 1, cj + 3) = sin(angj) * (sr * sin(theta)/* - dsdtheta * cos(theta)*/) - cos(angj) * (sr * cos(theta)/* - dsdtheta * sin(theta)*/);
//  		lhs(r, cj + 3) = -(-cos(angj) * (dsdtheta * cos(theta) - s0 * sin(theta)) + sin(angj) * (dsdtheta * sin(theta) + s0 * cos(theta)));
//  		lhs(r + 1, cj + 3) = -(-sin(angj) * (dsdtheta * cos(theta) - s0 * sin(theta)) - cos(angj) * (dsdtheta * sin(theta) + s0 * cos(theta)));
	}
}

void pointFollower::derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i)
{
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;
	//setSinCos(q(ci + 2), q(cj + 2));
	//setSinCos(ib->Angle(), jb->Angle());
	transformationMatrix Ai = TM(q(ci + 2));
	transformationMatrix Aj = TM(q(cj + 2));
	double thi = q(ci + 2);
	double thj = q(cj + 2);
	double wi = qd(ci + 2);
	double wj = qd(cj + 2);
	vecd3 Qd = wi * wi * math::local2global(Ai, baseMarker.s) - wj * wj * math::local2global(Aj, actionMarker.s);
	double Qd1
		= wi * wi * (cos(thi) * baseMarker.s.X() - sin(thi) * baseMarker.s.Y())
		- wj * wj * (cos(thj) * actionMarker.s.X() - sin(thj) * actionMarker.s.Y());
	double Qd2
		= wi * wi * (sin(thi) * baseMarker.s.X() + cos(thi) * baseMarker.s.Y())
		- wj * wj * (sin(thj) * actionMarker.s.X() + cos(thj) * actionMarker.s.Y());
	// 	double Qd1 = wi * wi * (Ai[0] * baseMarker.s.X() + Ai[1] * baseMarker.s.Y()) -
	// 		         wj * wj * (Aj[0] * actionMarker.s.X() + Aj[1] * actionMarker.s.Y());
	// 	double Qd2 = wi * wi * (Ai[2] * baseMarker.s.X() + Ai[3] * baseMarker.s.Y()) -
	// 				 wj * wj * (Aj[2] * actionMarker.s.X() + Aj[3] * actionMarker.s.Y());
	rhs(i) = Qd.X();
	rhs(i + 1) = Qd.Y();
}

void pointFollower::lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1, double mul)
{
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;

	if (ci)
	{
		vecd3 _up = baseMarker.s;
		double th = q(ci + 2);
		ci -= 3;
		lhs(ci + 2, ci + 2)
			+= mul * (lm0 * (-_up.X() * cos(th) + _up.Y()*sin(th))
			+ lm1 * (-_up.X() * sin(th) - _up.Y()*cos(th)));
	}
	if (cj)
	{
		vecd3 _up = actionMarker.s;
		double th = q(cj + 2);
		cj -= 3;
		lhs(cj + 2, cj + 2)
			+= mul * (lm0 * (_up.X() * cos(th) - _up.Y() * sin(th))
			+ lm1 * (-_up.X() * sin(th) + _up.Y() * cos(th)));
	}
}

void pointFollower::setInitialAngle(double a)
{
	base_angle = a;
}

void pointFollower::setActionHardPoint(vecd3 hp)
{
	action_hp = hp;
}

void pointFollower::defineOnePointFollower()
{
	unsigned int step = ss.size();
	double passive_angle = ib->Angle();
	double cam_angle = jb->Angle();
	vecd3 passive_pos = ib->Position();
	vecd3 cam_passive_pos = passive_pos + math::local2global(TM(passive_angle), local_vector);
	vecd3 dp = cam_passive_pos - action_hp;
	//vecd3 dp = hp1 - hp0;
// 	double ms = abs( + action_hp.Y());
// 	if (ms > maxDistance)
// 		maxDistance = ms;
	vecd3 cp = math::global2local(TM(cam_angle), dp);
	double len = math::length(cp);
	double ang = acos(cp.X() / len);
	if (cp.Y() < 0)
		ang = M_PI + (M_PI - ang);
// 	double ms = abs(action_hp.Y() + cp.Y());
// 	if (ms > maxDistance)
// 		maxDistance = ms;
// 	if (abs(cam_angle) > M_PI * 0.5)
// 	{
// 		ms = ss.at(incAngle++).y() + action_hp.Y();
// 		if (ms > maxDistance)
// 			maxDistance = ms;
// 	}
	
	this->appendRealCamProfileXY(cp);
	this->appendProfileData(/*base_angle - cam_angle*/ang, len);
}

void pointFollower::appendRealCamProfileXY(vecd3 xy)
{
	cpXY.push_back(QPointF(xy.X(), xy.Y()));
}

double pointFollower::MaxDistance()
{

	return maxDistance;
}

// double pointFollower::currentDthDt()
// {
// // 	double ddth = 0.0;
// // 	if (current_step == 0)
// // 	{
// // 		ddth = dthdt.at(1) - dthdt.at(0);
// // 	}
// // 	else if (current_step == 3500)
// // 	{
// // 		ddth = dthdt.at(current_step) - dthdt.at(current_step - 1);
// // 	}
// // 	else
// // 	{
// // 		ddth = dthdt.at(current_step + 1) - dthdt.at(current_step - 1);
// // 	}
// // 	return 0.5 * ddth / 0.00001;
// }

void pointFollower::defineLast()
{
	double cam_angle = jb->Angle();
	double th = 0;
	double s = 0;
	double rx = 0;
	double ry = 0;
	double x = 0;
	double y = 0;
	int sz = ss.size();
	for (int i = 0; i < sz; i++)
	{
		th = ss.at(i).x();
		s = ss.at(i).y();
		rx = s * cos(th);
		ry = s * sin(th);
		x = action_hp.X() + (cos(cam_angle) * rx - sin(cam_angle) * ry);
		y = action_hp.Y() + (sin(cam_angle) * rx + cos(cam_angle) * ry);
		if (y > maxDistance)
			maxDistance = y;
		endXY.push_back(QPointF(x, y));
	}
	//maxDistance = maxDistance + action_hp.Y();
// 	unsigned int sz = ss.size();
// 	double _ds = ss.at(sz - 1).y() - ss.at(sz - 2).y();
// 	double _dth = ss.at(sz - 1).x() - ss.at(sz - 2).x();
// 	ds.push_back(_ds / _dth);
	//dthdt.push_back(_dth / 0.00001);
}
