#include "DynaMic.h"
#include "commandWindow.h"
#include "animation_controller.h"
#include "plotWindow.h"
#include <QMutexLocker>
#include <QTextStream>
#include <QTime>

DynaMic::DynaMic(model *_md)
	: QThread()
	, md(_md)
	, nStep(0)
	, cStep(0)
	, ct(0)
	, dt(0)
	, et(0)
	, alpha(-0.3)
	, gamma(0)
	, beta(0)
	, permutation(NULL)
	, _isKinematicModel(false)
	//, TM(NULL)
{

}

DynaMic::~DynaMic()
{
	//if (md) delete md; md = NULL;
	if (permutation) delete[] permutation; permutation = NULL;
// 	this->quit();
// 	this->wait();
	//if (TM) delete[] TM; TM = NULL;
}

void DynaMic::setModel(model* _md)
{
	md = _md;
}

void DynaMic::setPlotWindow(plotWindow* pw)
{
	plot = pw;
}

int DynaMic::init()
{
	emit sendProcess('@', "Dynamic solver is initializing.");
	nStep = static_cast<unsigned int>((et / dt) + 1e-9);
	emit sendProcess('@', "    Total step : " + QString("%1").arg(nStep));
	g.x = 0.0; g.y = -9.80665; g.z = 0.0;
	emit sendProcess('@', "    Gravity : [" + QString("%1, %2, %3").arg(g.x).arg(g.y).arg(g.z) + "]");
	nCoord = md->nBody() * 3 - (md->hasGround() ? 3 : 0) + constraint::NDimension();
	mdim = nCoord - constraint::NDimension();
	if (mdim == constraint::NDimension())
		_isKinematicModel = true;
		
	lhs.alloc(nCoord, nCoord);
	rhs.alloc(nCoord);
	q.alloc(nCoord - constraint::NDimension() + (md->hasGround() ? 3 : 0));
	qd.alloc(nCoord - constraint::NDimension() + (md->hasGround() ? 3 : 0));
	qdd.alloc(nCoord);
	if (_isKinematicModel == false)
	{
		ipp.alloc(nCoord - constraint::NDimension() + (md->hasGround() ? 3 : 0));
		ipv.alloc(nCoord - constraint::NDimension() + (md->hasGround() ? 3 : 0));
		pre.alloc(mdim);
	}
	jacobi.alloc(constraint::NTotalNonZero(), constraint::NDimension(), q.sizes());

	QVectorIterator<rigidBody*> b(md->RigidBodies());
	QVectorIterator<constraint*> c(md->Constraints());

	while (b.hasNext())
	{
		rigidBody* rb = b.next();
		if (rb->IsGround())
			continue;
		rb->clearResultData();
		unsigned int i = rb->ID() * 3;
		q(i) = rb->Position().X();
		qd(i) = rb->Velocity().X();
		q(i + 1) = rb->Position().Y();
		qd(i + 1) = rb->Velocity().Y();
		q(i + 2) = rb->Angle();
		qd(i + 2) = rb->AngularVelocity();
		rb->setGeneralCoordinatePointer(q.get_ptr() + i, qd.get_ptr() + i);
	}

	unsigned int srow = q.sizes();
	while (c.hasNext())
	{
		constraint* cs = c.next();
		cs->setRowLocation(srow);
	}
	beta = (1 - alpha) * (1 - alpha) / 4.0;
	gamma = 0.5 - alpha;
	dt2accp = dt * dt * (1 - 2 * beta) * 0.5;
	dt2accv = dt * (1 - gamma);
	dt2acc = dt * dt * beta;
	divBeta = -1.0 / (beta * dt * dt);
	lapack_one = 1;
	lapack_info = 0;
	ptDof = (MKL_INT*)&nCoord;
	permutation = new MKL_INT[nCoord];
	if (_isKinematicModel)
	{
		QVectorIterator<drivingConstraint*> dr(md->DrivingConstraints());
		while (dr.hasNext())
		{
			drivingConstraint* _dr = dr.next();
			_dr->bindGeneralizedCoordinate(q);
			_dr->setPreviousPosition();
			_dr->bindTime(dt, &ct, &cStep);
		}
		kinematicAnalysis();
		jointReactionForceFromEOM();
		dr.toFront();
	}
	else
	{
		oneStepAnalysis(0);
	}
	
	return 0;
}

void DynaMic::setSimulationCondition(double _dt, double _et)
{
	dt = _dt;
	et = _et;
}

void DynaMic::oneStepAnalysis(double ct)
{
	// Mass matrix initializing
	unsigned int i = 0;
	rigidBody* rb;
	lhs.zeros();
	rhs.zeros();
	QVectorIterator<rigidBody*> b(md->RigidBodies());
	QVectorIterator<constraint*> c(md->Constraints());
	double mul = ct ? (1 / alpha) : 1.0;
	while (b.hasNext())
	{		
		rb = b.next();
		if (rb->IsGround()) continue;
		lhs(i, i) = lhs(i + 1, i + 1) = mul * rb->Mass();
		lhs(i + 2, i + 2) = mul * rb->Inertia();
		rhs(i) = g.x;
		rhs(i + 1) = rb->Mass() * g.y;
		rhs(i + 2) = g.z;
		i += 3;
	}
	jacobi.zeroCount();
	// Gernealized force initializing
	while (c.hasNext())
	{		
		constraint* cs = c.next();
// 		if (cs->JointType() == DRIVING)
// 			continue;
		cs->constraintJacobian(q, qd, jacobi, i);
		cs->derivative(q, qd, rhs, i);
		switch (cs->JointType())
		{
		case REVOLUTE:
		case TRANSLATION:
			i += 2;
			break;
		case DRIVING:
			i += 1;
			break;
		}
	}
	for (i = 0; i < jacobi.nnz(); i++)
	{
		lhs(jacobi.ridx[i], jacobi.cidx[i]) = lhs(jacobi.cidx[i], jacobi.ridx[i])
			= jacobi.value[i];
	}
	lhs.display();
	dgesv_(ptDof, &lapack_one, lhs.getDataPointer(), ptDof, permutation, rhs.get_ptr(), ptDof, &lapack_info);
	qdd = rhs;
}

void DynaMic::jointReactionForceFromEOM()
{
	unsigned int i = 0;
	rigidBody* rb;
	lhs.zeros();
	rhs.zeros();
	QVectorIterator<rigidBody*> b(md->RigidBodies());
	QVectorIterator<constraint*> c(md->Constraints());
	while (b.hasNext())
	{
		rb = b.next();
		if (rb->IsGround()) continue;
		lhs(i, i) = lhs(i + 1, i + 1) = rb->Mass();
		lhs(i + 2, i + 2) = rb->Inertia();
		rhs(i) = g.x;
		rhs(i + 1) = rb->Mass() * g.y;
		rhs(i + 2) = g.z;
		i += 3;
	}
	jacobi.zeroCount();
	// Gernealized force initializing
	while (c.hasNext())
	{
		constraint* cs = c.next();
		cs->constraintJacobian(q, qd, jacobi, i);
		cs->derivative(q, qd, rhs, i);
		switch (cs->JointType())
		{
		case REVOLUTE:
		case TRANSLATION:
			i += 2;
			break;
		case DRIVING:
			i += 1;
			break;
		}
	}
	for (i = 0; i < jacobi.nnz(); i++)
	{
		lhs(jacobi.ridx[i], jacobi.cidx[i]) = lhs(jacobi.cidx[i], jacobi.ridx[i])
			= jacobi.value[i];
	}
	dgesv_(ptDof, &lapack_one, lhs.getDataPointer(), ptDof, permutation, rhs.get_ptr(), ptDof, &lapack_info);
	c.toFront();
	unsigned int r = mdim;
	while (c.hasNext())
	{
		constraint* cs = c.next();
		cs->calcJointReactionForce(rhs, r);
	}
}

void DynaMic::predictionStep()
{
	QVectorIterator<rigidBody*> b(md->RigidBodies());
	QVectorIterator<constraint*> c(md->Constraints());
	unsigned int i = 0;
	while (b.hasNext())
	{
		rigidBody* rb = b.next();
		if (rb->IsGround()) continue;
		pre(i) = g.x;
		pre(i + 1) = rb->Mass() * g.y;
		pre(i + 2) = g.z;
		i += 3;
	}
	jacobi.zeroCount();
	while (c.hasNext())
	{
		constraint* cs = c.next();
		cs->constraintJacobian(q, qd, jacobi, i);
		switch (cs->JointType())
		{
		case REVOLUTE:
		case TRANSLATION:
			i += 2;
			break;
		case DRIVING:
			i += 1;
			break;
		}
	}
	for (i = 0; i < jacobi.nnz(); i++)
	{
		pre(jacobi.cidx[i]) -= jacobi.value[i] * qdd(jacobi.ridx[i]);
	}
	pre *= alpha / (1 + alpha);
	unsigned int ig = md->hasGround() * 3;
	for (i = 0; i < mdim; i++)
	{
		unsigned int ni = i + ig;
		ipp(ni) = q(ni) + qd(ni) * dt + qdd(i) * dt2accp;
		ipv(ni) = qd(ni) + qdd(i) * dt2accv;
	}
	for (i = 0; i < mdim; i++)
	{
		unsigned int ni = i + ig;
		q(ni) = ipp(ni) + qdd(i) * dt2acc;
		qd(ni) = ipv(ni) + qdd(i) * dt * gamma;
	}
}

unsigned int DynaMic::correctionStep()
{
	double norm = 0;
	unsigned int niteration = 0;
	while (1)
	{
		niteration++;
		QVectorIterator<rigidBody*> b(md->RigidBodies());
		QVectorIterator<constraint*> c(md->Constraints());
		unsigned int i = 0;
		lhs.zeros();
		double mul = 1 / (1 + alpha);
		while (b.hasNext())
		{
			rigidBody* rb = b.next();
			if (rb->IsGround()) continue;
			lhs(i, i) = lhs(i + 1, i + 1) = mul * rb->Mass();
			lhs(i + 2, i + 2) = mul * rb->Inertia();
			rhs(i) = g.x;
			rhs(i + 1) = rb->Mass() * g.y;
			rhs(i + 2) = g.z;
			i += 3;
		}
		jacobi.zeroCount();
	//	lhs.display();
		while (c.hasNext())
		{
			constraint* cs = c.next();
			cs->constraintJacobian(q, qd, jacobi, i);
			cs->lagrangianJacobian(q, lhs, i, qdd(i), qdd(i + 1), beta * dt * dt);
			cs->constraintEquation(q, rhs, i, divBeta);
			switch (cs->JointType())
			{
			case REVOLUTE:
			case TRANSLATION:
				i += 2;
				break;
			case DRIVING:
				i += 1;
			}
		}
		//lhs.display();
		for (i = 0; i < jacobi.nnz(); i++)
		{
			rhs(jacobi.cidx[i]) -= jacobi.value[i] * qdd(jacobi.ridx[i]);
			lhs(jacobi.ridx[i], jacobi.cidx[i]) = lhs(jacobi.cidx[i], jacobi.ridx[i])
				= jacobi.value[i];
		}
		for (i = 0; i < mdim; i++)
		{
			double v = 0;
			for (unsigned int j = 0; j < mdim; j++)
			{
				v += lhs(i, j) * qdd(j);
			}
			rhs(i) -= v;
			rhs(i) -= pre(i);
		}
		norm = rhs.norm();
		dgesv_(ptDof, &lapack_one, lhs.getDataPointer(), ptDof, permutation, rhs.get_ptr(), ptDof, &lapack_info);
		qdd += rhs;
		unsigned int ig = md->hasGround() * 3;

		for (i = 0; i < mdim; i++)
		{
			unsigned int ni = i + ig;
// 			if (isFixed[i])
// 				continue;
			q(ni) = ipp(ni) + qdd(i) * dt2acc;
			qd(ni) = ipv(ni) + qdd(i) * dt * gamma;
		}
		if (norm <= 1e-5)
		{
			tNormValue += norm;
			return niteration;
		}
			
	}
}

bool DynaMic::saveResultData(double ct)
{
	QVectorIterator<rigidBody*> r(md->RigidBodies());
	while (r.hasNext())
	{
		rigidBody *rb = r.next();
		if (rb->IsGround()) continue;
		resultDataType rdt;
		unsigned int id1 = rb->ID() * 3;
		unsigned int id2 = (rb->ID() - md->hasGround()) * 3;
		rdt.time = ct;
		rdt.pos = vecd3(q(id1), q(id1 + 1), 0.0);
		rdt.vel = vecd3(qd(id1), qd(id1 + 1), 0.0);
		rdt.acc = vecd3(qdd(id2), qdd(id2 + 1), 0.0);
		rdt.ang = q(id1 + 2);
		rdt.angv = qd(id1 + 2);
		rdt.anga = qdd(id2 + 2);
		rb->appendResultData(rdt);
		if (rb->Name() == "active")
			plot->appendData("active", ct, rdt.pos.X());
	}
 	QVectorIterator<constraint*> c(md->Constraints());
 	int i = mdim;

	while (c.hasNext())
	{
		constraint *cs = c.next();
		jointResultDataType trdt = { 0, };
		trdt.time = ct;
		switch (cs->JointType())
		{
		case REVOLUTE:
			trdt.fx = cs->ReactionForce()[0];
			trdt.fy = cs->ReactionForce()[1];
			trdt.fm = sqrt(trdt.fx * trdt.fx + trdt.fy * trdt.fy);
			break;
		case TRANSLATION:
			break;
		case DRIVING:
			continue;
		}
		unsigned int b_id = cs->BaseBody()->ID() * 3;
		vecd3 b_loc_pos = cs->BaseMarker().s;
		vecd3 i_pos(q(b_id), q(b_id + 1), 0.0);
		transformationMatrix A = TM(q(b_id + 2));
		trdt.loc = i_pos + math::local2global(A, b_loc_pos);
		cs->appendResultData(trdt);
	}

	return true;
}

void DynaMic::run()
{
	QString msg;
	QTextStream qs(&msg);
	QTime tme;
	ct = 0;
	double pt = 0;
	cStep = 0;
	int part = 0;
	tIteration = 0;
	tNormValue = 0;
	sendProcess('L');

	if (saveResultData(ct))
	{
		qs 
			<< qSetFieldWidth(20) 
			<< center
			<< "TIME" 
			<< "STEPSIZE" 
			<< "AVG_NORM" 
			<< "NJACOBI";
		sendProcess('@', msg); msg.clear();
		part++;
	}
	tme.start();
	QTime startingTime = tme.currentTime();
	QDate startingDate = QDate::currentDate();
	while (cStep < nStep)
	{
		cStep++;
		pt = ct;
		ct = cStep * dt;
		QMutexLocker locker(&m_mutex);
		if (_isKinematicModel)
		{
			tIteration += kinematicAnalysis();
			jointReactionForceFromEOM();
		}
		else
		{
			predictionStep();
			tIteration += correctionStep();
		}
		if (!(cStep % 10))
		{
			double avg_norm = tNormValue / cStep;
			if (saveResultData(ct))
			{
				qs
					<< qSetFieldWidth(20)
					<< center
					<< QString("%1").arg(ct, 11, 'E', 6)
					<< QString("%1").arg(dt, 10, 'E', 6)
					<< QString("%1").arg(avg_norm, 14, 'E', 6)
					<< right
					<< QString("%1").arg(tIteration, 13);
				sendProcess('@', msg); msg.clear();
				part++;
				msleep(10);
			}
		}

	}

	sendProcess('L');
	QTime endingTime = tme.currentTime();
	QDate endingDate = QDate::currentDate();
	double dtime = tme.elapsed() * 0.001;
	int minute = static_cast<int>(dtime / 60.0);
	int hour = static_cast<int>(minute / 60.0);
	qs.setFieldWidth(0);
	int cgtime = endingTime.second() - startingTime.msec();
	qs << "     Starting time/date     = " << startingTime.toString() << " / " << startingDate.toString() << endl
		<< "     Ending time/date      = " << endingTime.toString() << " / " << endingDate.toString() << endl
		<< "     CPU + GPU time       = " << dtime << " second  ( " << hour << " h. " << minute << " m. " << dtime << " s. )";
	sendProcess('@', msg);
	sendProcess('L');
	animation_controller::setTotalFrame(part - 1);
	emit finishedThread();
}

unsigned int DynaMic::kinematicAnalysis()
{
	// position analysis
	MATD _lhs(constraint::NDimension(), constraint::NDimension());
	VECD _rhs(constraint::NDimension());
	double norm = 1;
	MKL_INT _ptDof = 9;
	MKL_INT *_perm = new MKL_INT[9];
	unsigned int niteration = 0;
	while (1)
	{
		niteration++;
		QVectorIterator<constraint*> c(md->Constraints());
		unsigned int i = 0;
		_lhs.zeros();
		jacobi.zeroCount();
		while (c.hasNext())
		{
			constraint* cs = c.next();
			cs->constraintJacobian(q, qd, jacobi, i);
			cs->constraintEquation(q, _rhs, i, 1.0);
			switch (cs->JointType())
			{
			case REVOLUTE:
			case TRANSLATION:
				i += 2;
				break;
			case DRIVING:
				i += 1;
			}
		}
		for (i = 0; i < jacobi.nnz(); i++)
		{
			_lhs(jacobi.ridx[i], jacobi.cidx[i]) = jacobi.value[i];
		}
		//_lhs.display();
		for (unsigned int j = 0; j < mdim; j++)
			_rhs(j) = -_rhs(j);
		dgesv_(&_ptDof, &lapack_one, _lhs.getDataPointer(), &_ptDof, _perm, _rhs.get_ptr(), &_ptDof, &lapack_info);
		norm = _rhs.norm();
		for (unsigned int j = 0; j < mdim; j++)
		{
			q(j + 3) += _rhs(j);
		}
		if (norm <= 1e-5)
		{
			tNormValue += norm;
			break;
		}
	}

	// velocity analysis
	_lhs.zeros();
	_rhs.zeros();
	QVectorIterator<constraint*> c(md->Constraints());
	unsigned int i = 0;
	jacobi.zeroCount();
	while (c.hasNext())
	{
		constraint* cs = c.next();
		cs->constraintJacobian(q, qd, jacobi, i);
		switch (cs->JointType())
		{
		case REVOLUTE:
		case TRANSLATION:
			i += 2;
			break;
		case DRIVING:
			_rhs(i) = dynamic_cast<drivingConstraint*>(cs)->ConstantVelocity();
			dynamic_cast<drivingConstraint*>(cs)->setPreviousPosition();
			i += 1;
			break;
		}
	}
	for (i = 0; i < jacobi.nnz(); i++)
	{
		_lhs(jacobi.ridx[i], jacobi.cidx[i]) = jacobi.value[i];
	}
	//_rhs(8) = -0.1;
	dgesv_(&_ptDof, &lapack_one, _lhs.getDataPointer(), &_ptDof, _perm, _rhs.get_ptr(), &_ptDof, &lapack_info);
	for (unsigned int j = 0; j < mdim; j++)
	{
		qd(j + 3) = _rhs(j);
	}

	// acceleration analysis
	_lhs.zeros();
	_rhs.zeros();
	c.toFront();
	i = 0;
	jacobi.zeroCount();
	while (c.hasNext())
	{
		constraint* cs = c.next();
		cs->constraintJacobian(q, qd, jacobi, i);
		cs->derivative(q, qd, _rhs, i);
		switch (cs->JointType())
		{
		case REVOLUTE:
		case TRANSLATION:
			i += 2;
			break;
		case DRIVING:
			i += 1;
		}
	}
	for (i = 0; i < jacobi.nnz(); i++)
	{
		_lhs(jacobi.ridx[i], jacobi.cidx[i]) = jacobi.value[i];
	}
	dgesv_(&_ptDof, &lapack_one, _lhs.getDataPointer(), &_ptDof, _perm, _rhs.get_ptr(), &_ptDof, &lapack_info);
	for (unsigned int j = 0; j < mdim; j++)
	{
		qdd(j) = _rhs(j);
	}
	delete[] _perm;
	return niteration;
}