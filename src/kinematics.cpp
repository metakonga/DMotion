#include "kinematics.h"
#include "optimumDesignDoc.h"
#include "commandWindow.h"
#include "animation_controller.h"
#include "plotWindow.h"
#include "linearSolver.hpp"
#include <QDebug>
#include <QMutexLocker>
#include <QTextStream>
#include <QTime>
// #include "lapack/f2c.h"
// #include "lapack/clapack.h"

kinematics::kinematics(model *_md, optimumDesignDoc* _odd)
	: QThread()
	, md(_md)
	, odd(_odd)
	, nStep(0)
	, cStep(0)
	, reaction_step(0)
	, ct(0)
	, dt(0)
	, et(0)
{

}

kinematics::~kinematics()
{

}

void kinematics::setModel(model* _md)
{
	md = _md;
}

void kinematics::setPlotWindow(plotWindow* pw)
{
	plot = pw;
}

int kinematics::init()
{
	QMapIterator<QString, rigidBody*> b(md->RigidBodies());
	QMapIterator<QString, constraint*> c(md->Constraints());

	emit sendProcess('@', "Dynamic solver is initializing.");
	nStep = static_cast<unsigned int>((et / dt) + 1e-9);
	emit sendProcess('@', "    Total step : " + QString("%1").arg(nStep));
	g.x = 0.0; g.y = -9.80665; g.z = 0.0;
	emit sendProcess('@', "    Gravity : [" + QString("%1, %2, %3").arg(g.x).arg(g.y).arg(g.z) + "]");
	s_d = md->nBody() * 3 - (md->hasGround() ? 3 : 0) + constraint::NDimension();
	s_c = md->nBody() * 3 - (md->hasGround() ? 3 : 0);
	s_k = s_c;
	if (s_c != constraint::NDimension())
	{
		emit sendProcess('@', "This is not kinematics system");
		return -1;
	}
	unsigned int nCoord = md->nBody() * 3;
	q.alloc(nCoord);
	qd.alloc(nCoord);
	qdd.alloc(nCoord);

	unsigned int i = 0;
	foreach(QString str, md->BodyList())
	{
		rigidBody* rb = md->RigidBodies()[str];
		rb->clearResultData();
		rb->setPosition0();
		q(i) = rb->Position().X(); qd(i) = rb->Velocity().X(); qdd(i) = rb->Acceleration().X();
		q(i + 1) = rb->Position().Y(); qd(i + 1) = rb->Velocity().Y(); qdd(i + 1) = rb->Acceleration().Y();
		q(i + 2) = rb->Angle(); qd(i + 2) = rb->AngularVelocity(); qdd(i + 2) = rb->AngularAcceleration();
		i += 3;
	}
	unsigned int srow = q.sizes();
	while (c.hasNext())
	{
		constraint* cs = c.next().value();
		cs->setRowLocation(srow);
		if (cs->JointType() != DRIVING)
			cs->initializeConstraint();
	}
	QMapIterator<QString, drivingConstraint*> dr(md->DrivingConstraints());
	while (dr.hasNext())
	{
		drivingConstraint* _dr = dr.next().value();
		_dr->bindGeneralizedCoordinate(q);
		_dr->setPreviousPosition();
		_dr->bindTime(dt, &ct, &cStep);
		_dr->initializeDrivingPosition();
	}	
	saveBodyResults();
	md->PointFollower()->initializeCurveData();
	md->PointFollower()->defineOnePointFollower();
	return 0;
}

void kinematics::saveBodyResults()
{
	unsigned int i = 0;
	foreach(QString str, md->BodyList())
	{
		rigidBody* rb = md->RigidBodies()[str];
		resultDataType rdt;
		rdt.time = ct;
		rdt.pos = vecd3(q(i), q(i + 1), 0);
		rdt.vel = vecd3(qd(i), qd(i + 1), 0);
		rdt.acc = vecd3(qdd(i), qdd(i + 1), 0);
		rdt.ang = q(i + 2);
		rdt.angv = qd(i + 2);
		rdt.anga = qdd(i + 2);
		rb->setPosition(q(i), q(i + 1), 0);
		rb->setVelocity(qd(i), qd(i + 1), 0);
		rb->setAcceleration(qdd(i), qdd(i + 1), 0);
		rb->setAngle(q(i + 2));
		rb->setAngularVelocity(qd(i + 2));
		rb->setAngularAcceleration(qdd(i + 2));
		rb->appendResultData(rdt);
		i += 3;
	}
}

void kinematics::setSimulationCondition(double _dt, double _et)
{
	dt = _dt;
	et = _et;
}

void kinematics::jointReactionForce()
{
	pointFollower *pf = md->PointFollower();
	if (cStep < 2)
		return;

	unsigned int m_size = s_d + (pf ? 1 : 0) * 2;
	unsigned int nCoord = s_c + (md->hasGround() ? 3 : 0) + (pf ? 1 : 0);
	unsigned int m_s = s_c + (pf ? 1 : 0);
	linearSolver ls(LAPACK_COL_MAJOR, m_size, 1, m_size, m_size);
//  	MKL_INT lapack_info = 0;
//  	MKL_INT lapack_one = 1;
// //	integer lapack_one = 1;
// // 	doublereal lapack_zero = 0;
// // 	doublereal lapack_mone = -1;
// //	integer lapack_info = 0;
// 	//integer ptDof = 10;
// //	integer *permutation = new integer[m_size];
// 	MKL_INT ptDof = m_size;
// 	MKL_INT *permutation = new MKL_INT[m_size];
	MATD lhs(m_size, m_size);
	VECD rhs(m_size);
	if(pf)
		pf->setCurrentStep(reaction_step);
	VECD m_q(nCoord);
	VECD m_qd(nCoord);
	VECD m_qdd(nCoord);
	SMATD spar;
	spar.alloc(constraint::NTotalNonZero(), constraint::NDimension(), q.sizes());
	md->setGeneralizedCoordinate(reaction_step ,m_q, m_qd, m_qdd);
	unsigned int i = 0;
	i = 0;
	QMapIterator<QString, rigidBody*> b(md->RigidBodies());
	foreach(QString str, md->BodyList())
	{
		rigidBody *rb = md->RigidBodies()[str];
		if (rb->IsGround()) continue;
		lhs(i, i) = lhs(i + 1, i + 1) = rb->Mass();
		lhs(i + 2, i + 2) = rb->Inertia();
		rhs(i) = g.x;
		rhs(i + 1) = rb->Mass() * g.y;
		rhs(i + 2) = 0.0;
		i += 3;
	}
	spar.zeroCount();
	i = 0;
	foreach(QString str, md->ConstraintList())
	{
		constraint* cs = md->Constraints()[str];
		if (cs->Name() == "Arc_driving")
			continue;
		cs->constraintJacobian(m_q, m_qd, spar, i);
		cs->derivative(m_q, m_qd, rhs, m_s + i);
		i += cs->NRow();
	}
	pf->constraintJacobian(m_q, m_qd, spar, i);
	unsigned int j = 0;
	for (j = 0; j < spar.nnz(); j++)
	{
		if (spar.ridx[j] == 11 || spar.ridx[j] == 12)
			rhs(m_s + spar.ridx[j]) += spar.value[j] * m_qdd(spar.cidx[j] + 3);
		lhs(m_s + spar.ridx[j], spar.cidx[j]) = lhs(spar.cidx[j], m_s + spar.ridx[j]) = spar.value[j];
	}
	if (pf)
	{
		pf->followerJacobian(m_q, spar, i, s_k);
		unsigned int id = (pf->ActionBody()->ID() + int(md->hasGround())) * 3 - (md->hasGround() ? 3 : 0);
		for (j; j < spar.nnz(); j++)
		{
			rhs(m_s + spar.ridx[j]) += spar.value[j] * (-m_qdd(id + 2));
			lhs(m_s + spar.ridx[j], spar.cidx[j]) = lhs(spar.cidx[j], m_s + spar.ridx[j]) = spar.value[j];
		}
	}
	int info = ls.solve(lhs.getDataPointer(), rhs.get_ptr());
	//dgesv_(&ptDof, &lapack_one, lhs.getDataPointer(), &ptDof, permutation, rhs.get_ptr(), &ptDof, &lapack_info);
	//delete[] permutation;
	unsigned int r = m_s;
	foreach(QString str, md->ConstraintList())
	{
		constraint* cs = md->Constraints()[str];
		if (cs->Name() == "Arc_driving")
			continue;
		cs->calcJointReactionForce(rhs, r);
	}
	pf->calcJointReactionForce(rhs, r);
	reaction_step++;
}

void kinematics::initGeneralizedCoordinates()
{
	unsigned int i = 0;
	foreach(QString str, md->BodyList())
	{
		rigidBody* rb = md->RigidBodies()[str];
		//rb->setPosition0();
		q(i) = rb->Position().X(); qd(i) = rb->Velocity().X(); qdd(i) = rb->Acceleration().X();
		q(i + 1) = rb->Position().Y(); qd(i + 1) = rb->Velocity().Y(); qdd(i + 1) = rb->Acceleration().Y();
		q(i + 2) = rb->Angle(); qd(i + 2) = rb->AngularVelocity(); qdd(i + 2) = rb->AngularAcceleration();
		i += 3;
	}
}

void kinematics::setDesignVariables(MATD& m_design)
{
	if (design.sizes() == 0)
		design.alloc(m_design.rows(), m_design.cols());
	design = m_design;
}

void kinematics::run()
{
	QString msg;
	QTextStream qs(&msg);
	QTime tme;
	ct = 0;
	double pt = 0;
	int part = 0;
	tIteration = 0;
	tNormValue = 0;
	sendProcess('L');
	tme.start();
	QTime startingTime = tme.currentTime();
	QDate startingDate = QDate::currentDate();
	unsigned int caseCount = 0;
	unsigned int validCase = 0;
	bool isOver = false;
	bool interupt = false;
	QFile qfCase(md->ModelPath() + "caseResults.bin");
	qfCase.open(QIODevice::WriteOnly);
	md->initializeDesignVariable();
	while (!isOver)
	{
		sendCaseCount(caseCount);
		int ret = 0;
		QString hps;
		cStep = 0;
		reaction_step = 0;
		ct = 0.0;
		part = 0;
		interupt = false;
		if (caseCount)
		{
			isOver = md->updateDesignVariable(hps, !caseCount ? true : false);
		}			
		if (isOver)
			break;
		if (caseCount && !md->IsSatisfyCamAngle())
		{
			caseCount++;
			continue;
		}
		initGeneralizedCoordinates();
		optimumCase* oc = odd->createOptimumCase(QString("Case%1").arg(caseCount, 8, 10, QChar('0')));
		oc->appendBodyResults(md, ct, q, qd, qdd);
		oc->appendReactionResults(md, ct);
		oc->appendHardPointResult(md, ct);
		part++;
		saveBodyResults();
		if (md->PointFollower())
			md->PointFollower()->defineOnePointFollower();
		while (cStep < nStep)
		{
			cStep++;

			m_id = cStep % 3;
			pt = ct;
			ct = cStep * dt;
			constraint::setSolverStep(cStep);
			QMutexLocker locker(&m_mutex);
			ret = kinematicAnalysis();
			if (ret)
			{
				delete oc; oc = NULL;
				interupt = true;
				if(ret < 0)
					sendProcess('!', QString("%1").arg(ret));
				
				break;
			}
				
			saveBodyResults();
			if (md->PointFollower())
				md->PointFollower()->defineOnePointFollower();
			jointReactionForce();

			if (!(cStep % 10))
			{
				double avg_norm = tNormValue / cStep;
				oc->appendBodyResults(md, ct, q, qd, qdd);
				oc->appendReactionResults(md, ct);
				oc->appendHardPointResult(md, ct);
				part++;
			}
		}
		if (!interupt)
		{
			jointReactionForce();
			double mdist = md->PointFollower()->MaxDistance();
			bool b_lca = md->verifyLastCamAngleConstraint(oc->HardPointsResults());
			if ((caseCount && !odd->checkMinumumThisCase(oc)) || mdist >= md->SpaceConstraintHeight() || !b_lca)
			{
				//qDebug() << "Failed case(" << caseCount << ") : " << mdist;// md->PointFollower()->MaxDistance();
				delete oc; oc = NULL;
			}
			else
			{
			//	qDebug() << "This case is valid - " << validCase;
				QTime endingTime = tme.currentTime();
				QDate endingDate = QDate::currentDate();
				double dtime = tme.elapsed() * 0.001;
				int minute = static_cast<int>(dtime / 60.0);
				int hour = static_cast<int>(minute / 60.0);
				int cgtime = endingTime.second() - startingTime.msec();
				qs.setFieldWidth(0);
				qs << oc->Name() << " : " << "CPU time = " << dtime << " second  ( " << hour << " h. " << minute << " m. " << dtime << " s. )";
				sendProcess('@', msg);
				sendProcess('L');
				msg.clear();
				oc->appendCamProfileResult(md->PointFollower(), ct);
				odd->appendOptimumCase(oc);
				oc->setResultCount(part - 1);
				oc->saveCase(qfCase, caseCount);
				validCase++;
			}
		}
		if (ret < 0)
			break;
		if (caseCount && md->IsEmptyEnableDesignVariable())
			break;	
		caseCount++;
	}
	qs << "Optimum design analysis is completed." << endl 
		<< "Total number of case : " << caseCount << endl
		<< "The number of valid case : " << validCase;
	sendProcess('@', msg);
	qfCase.close();
	emit finishedThread();
}

int kinematics::kinematicAnalysis()
{
	//integer lapack_one = 1;
//  	doublereal lapack_zero = 0;
//  	doublereal lapack_mone = -1;
	///integer lapack_info = 0;
	//integer ptDof = s_k;
	//integer *permutation = new integer[s_k];
	linearSolver ls(LAPACK_COL_MAJOR, s_k, 1, s_k, s_k);
// 	MKL_INT lapack_info = 0;
// 	MKL_INT lapack_one = 1;
// 	MKL_INT ptDof = s_k;
// 	MKL_INT *permutation = new MKL_INT[s_k];
	double norm = 1.0;
	unsigned int r = 0;
	unsigned int niter = 0;
	SMATD spar;
	MATD lhs(s_k, s_k);
	VECD rhs(s_k);
	spar.alloc(constraint::NTotalNonZero(), constraint::NDimension(), q.sizes());
	
	while (1)
	{
		niter++;
		if (niter == 100)
		{
			//delete[] permutation; permutation = NULL;
			return 1;
		}
			
		lhs.zeros();
		rhs.zeros();
		spar.zeroCount();
		r = 0;
		foreach(QString str, md->ConstraintList())
		{
			constraint* cs = md->Constraints()[str];
			cs->constraintJacobian(q, qd, spar, r);
			int ret = cs->constraintEquation(q, rhs, r, 1.0);
			if (ret)
				return ret;
			r += cs->NRow();
		}
		for (unsigned int i = 0; i < spar.nnz(); i++)
		{
			lhs(spar.ridx[i], spar.cidx[i]) = spar.value[i];
		}

		for (unsigned int i = 0; i < s_k; i++)
			rhs(i) = -rhs(i);

		int info = ls.solve(lhs.getDataPointer(), rhs.get_ptr());
		//dgesv_(&ptDof, &lapack_one, lhs.getDataPointer(), &ptDof, permutation, rhs.get_ptr(), &ptDof, &lapack_info);
		norm = rhs.norm();
		for (unsigned int i = 0; i < s_k; i++)
			q(i + 3) += rhs(i);

		if (norm <= 1e-5)
		{
			tNormValue += norm;
			break;
		}
	}
	// velocity analysis
	lhs.zeros();
	rhs.zeros();
	r = 0;
	spar.zeroCount();
	foreach(QString str, md->ConstraintList())
	{
		constraint* cs = md->Constraints()[str];
		cs->constraintJacobian(q, qd, spar, r);
		if (cs->JointType() == DRIVING)
		{
			drivingConstraint *dc = md->DrivingConstraints()[str];
			rhs(r) = dc->ConstantVelocity();
			dc->setPreviousPosition();
		}
		r += cs->NRow();
	}
	for (unsigned int i = 0; i < spar.nnz(); i++)
	{
		lhs(spar.ridx[i], spar.cidx[i]) = spar.value[i];
	}
	int info = ls.solve(lhs.getDataPointer(), rhs.get_ptr());
	//dgesv_(&ptDof, &lapack_one, lhs.getDataPointer(), &ptDof, permutation, rhs.get_ptr(), &ptDof, &lapack_info);
	for (unsigned int i = 0; i < s_k; i++)
		qd(i + 3) = rhs(i);

	// acceleration analysis
	lhs.zeros();
	rhs.zeros();
	r = 0;
	spar.zeroCount();
	foreach(QString str, md->ConstraintList())
	{
		constraint* cs = md->Constraints()[str];
		cs->constraintJacobian(q, qd, spar, r);
		cs->derivative(q, qd, rhs, r);
		r += cs->NRow();
	}
	for (unsigned int i = 0; i < spar.nnz(); i++)
	{
		lhs(spar.ridx[i], spar.cidx[i]) = spar.value[i];
	}
	info = ls.solve(lhs.getDataPointer(), rhs.get_ptr());
	//dgesv_(&ptDof, &lapack_one, lhs.getDataPointer(), &ptDof, permutation, rhs.get_ptr(), &ptDof, &lapack_info);
	for (unsigned int i = 0; i < s_k; i++)
		qdd(i + 3) = rhs(i);
	//delete[] permutation;
	return 0;
}