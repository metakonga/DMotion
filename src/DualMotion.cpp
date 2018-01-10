#include "DualMotion.h"

DualMotion::DualMotion()
	: model()
{
}

DualMotion::~DualMotion()
{

}

void DualMotion::init()
{
	model::setModelName("Dual Motion");
	hardPoint *active_link = createHardPoint("active_link", 0, 0, 0);
	hardPoint *link_cam = createHardPoint("link_cam", 0.38424, -0.04956, 0);
	hardPoint *cam_ground = createHardPoint("cam_ground", 0.29739, 0, 0);
	hardPoint *cam_passive = createHardPoint("cam_passive", 0.17739, 0.0, 0.0);

	rigidBody *ground = createRigidBody("ground");
	ground->setGround(true);

	rigidBody *active = createRigidBody("active");
	active->setMass(1.930655807);
	active->setInertia(0.002253619676);
	active->setAngle(0.0);
	active->setCoordinateNumber(3);
	active->setPosition(-0.0414557605072536, 0.00000236243519342979, 0.0);
	active->setShapePath("C:/DMotion/data/ver2/Active head.step");

	rigidBody *link = createRigidBody("link");
	link->setMass(1.886852634);
	link->setInertia(0.028338286);
	link->setAngle(0);
	link->setCoordinateNumber(3);
	link->setPosition(0.188697168403797, -0.0349156464194469, 0.0);
	link->setShapePath("C:/DMotion/data/ver2/Active_link.step");

	rigidBody *cam = createRigidBody("cam");
	cam->setMass(3.8124);
	cam->setInertia(0.0230813979);
	cam->setPosition(0.262163603372142, -0.030311213723227, 0.0);
	cam->setAngle(0);
	cam->setCoordinateNumber(3);
	cam->setShapePath("C:/DMotion/data/ver2/CAM.step");

	rigidBody *passive = createRigidBody("passive");
	passive->setMass(4.11545567);
	passive->setInertia(0.05849749842);
	passive->setPosition(0.000509901920295489, 0.00773584919364184, 0.0);
	passive->setAngle(0);
	passive->setCoordinateNumber(3);
	passive->setShapePath("C:/DMotion/data/ver2/Passive.step");

	translateJoint *ground_active_tra = createTraslateJoint("ground_active_tra");
	gp_Pnt pos = active->Position();
	ground_active_tra->setPosition(pos.X(), pos.Y(), pos.Z());
	ground_active_tra->setBaseBody(ground);
	ground_active_tra->setActionBody(active);
	ground_active_tra->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
	ground_active_tra->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, -1.0, 0));
	ground_active_tra->defineAngleConstraint();

	revoluteJoint *active_link_rev = createRevoluteJoint("active_link_rev");
	pos = active_link->loc;
	active_link_rev->setPosition(pos.X(), pos.Y(), pos.Z());
	active_link_rev->setBaseBody(active);
	active_link_rev->setActionBody(link);
	active_link_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
	active_link_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
	active_link_rev->bindHardPoint(active_link);

	revoluteJoint *link_cam_rev = createRevoluteJoint("link_cam_rev");
	pos = link_cam->loc;
	link_cam_rev->setPosition(pos.X(), pos.Y(), pos.Z());
	link_cam_rev->setBaseBody(link);
	link_cam_rev->setActionBody(cam);
	link_cam_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
	link_cam_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
	link_cam_rev->bindHardPoint(link_cam);

	revoluteJoint *cam_ground_rev = createRevoluteJoint("cam_ground_rev");
	pos = cam_ground->loc;
	cam_ground_rev->setPosition(pos.X(), pos.Y(), pos.Z());
	cam_ground_rev->setBaseBody(cam);
	cam_ground_rev->setActionBody(ground);
	cam_ground_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
	cam_ground_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
	cam_ground_rev->bindHardPoint(cam_ground);

	translateJoint *ground_passive_tra = createTraslateJoint("ground_passive_tra");
	pos = passive->Position();
	ground_passive_tra->setPosition(pos.X(), pos.Y(), pos.Z());
	ground_passive_tra->setBaseBody(ground);
	ground_passive_tra->setActionBody(passive);
	ground_passive_tra->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
	ground_passive_tra->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, -1.0, 0));
	ground_passive_tra->defineAngleConstraint();

	drivingConstraint *active_driving = createDrivingConstraint("active_driving");
	active_driving->setTargetBody(active, AXIS_X);
	//active_driving->setConstantVelocity(-0.1);
	active_driving->setVelocityProfile("C:/DMotion/data/main_velocity.txt");

	drivingConstraint *passive_driving = createDrivingConstraint("arc_driving");
	passive_driving->setTargetBody(passive, AXIS_X);
	passive_driving->setVelocityProfile("C:/DMotion/data/passive_velocity.txt");

	pointFollower* pf = createPointFollower("cam_profile");
	pos = cam_passive->loc;
	pf->setPosition(pos.X(), pos.Y(), pos.Z());
	pf->setBaseBody(passive);
	pf->setActionBody(cam);
	pf->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
	pf->setLocalFromBaseBody();

	bodyList.push_back(ground->Name());
	bodyList.push_back(active->Name());
	bodyList.push_back(link->Name());
	bodyList.push_back(cam->Name());
	bodyList.push_back(passive->Name());

	constList.push_back(ground_active_tra->Name());
	constList.push_back(active_link_rev->Name());
	constList.push_back(link_cam_rev->Name());
	constList.push_back(cam_ground_rev->Name());
	constList.push_back(ground_passive_tra->Name());
	constList.push_back(active_driving->Name());
	constList.push_back(passive_driving->Name());

// 	dt = 0.00001;
// 	et = 0.035;

	s_c = 15;
	s_k = 12;
	s_d = 26;
	m_kj.alloc(s_k, s_k);
	v_kv.alloc(s_k);
	m_d.alloc(s_d, s_d);
	v_d.alloc(s_d);
	q.alloc(s_c);
	qd.alloc(s_c);
	qdd.alloc(s_c);

	unsigned int i = 0;
	foreach(QString str, bodyList)
	{
		rigidBody* rb = bodies[str];
		q(i) = rb->Position().X(); qd(i) = rb->Velocity().X(); qdd(i) = rb->Acceleration().X();
		q(i + 1) = rb->Position().Y(); qd(i + 1) = rb->Velocity().Y(); qdd(i + 1) = rb->Acceleration().Y();
		q(i + 2) = rb->Angle(); qd(i + 2) = rb->AngularVelocity(); qdd(i + 2) = rb->AngularAcceleration();
		i += 3;
	}
}

unsigned int DualMotion::kinematicAnalysis()
{
	MKL_INT lapack_info = 0;
	MKL_INT lapack_one = 1;
	MKL_INT ptDof = s_k;
	MKL_INT *permutation = new MKL_INT[s_k];
	double norm = 1.0;
	unsigned int r = 0;
	unsigned int niter = 0;
	SMATD spar;
	spar.alloc(constraint::NTotalNonZero(), constraint::NDimension(), q.sizes());
	while (1)
	{
		niter++;
		foreach(QString str, constList)
		{
			constraint* cs = cons[str];
			cs->constraintJacobian(q, qd, spar, r);
			cs->constraintEquation(q, v_kv, r, 1.0);
			r += cs->NRow();
		}
		for (unsigned int i = 0; i < spar.nnz(); i++)
		{
			m_kj(spar.ridx[i], spar.cidx[i]) = spar.value[i];
		}

		for (unsigned int i = 0; i < s_k; i++)
			v_kv(i) = -v_kv(i);


		dgesv_(&ptDof, &lapack_one, m_kj.getDataPointer(), &ptDof, permutation, v_kv.get_ptr(), &ptDof, &lapack_info);
		norm = v_kv.norm();
		for (unsigned int i = 0; i < s_k; i++)
			q(i + 3) += v_kv(i);

		if (norm <= 1e-5)
		{
			tNormValue += norm;
			break;
		}
	}
	
	// velocity analysis
	m_kj.zeros();
	v_kv.zeros();
	r = 0;
	spar.zeroCount();
	foreach(QString str, constList)
	{
		constraint* cs = cons[str];
		cs->constraintJacobian(q, qd, spar, r);
		if (cs->JointType() == DRIVING)
		{
			drivingConstraint *dc = drivings[str];
			v_kv(r) = dc->ConstantVelocity();
			dc->setPreviousPosition();
		}		
		r += cs->NRow();
	}
	for (unsigned int i = 0; i < spar.nnz(); i++)
	{
		m_kj(spar.ridx[i], spar.cidx[i]) = spar.value[i];
	}

	dgesv_(&ptDof, &lapack_one, m_kj.getDataPointer(), &ptDof, permutation, v_kv.get_ptr(), &ptDof, &lapack_info);
	for (unsigned int i = 0; i < s_k; i++)
		qd(i + 3) += v_kv(i);

	// acceleration analysis
	m_kj.zeros();
	v_kv.zeros();
	r = 0;
	spar.zeroCount();
	foreach(QString str, constList)
	{
		constraint* cs = cons[str];
		cs->constraintJacobian(q, qd, spar, r);
		cs->derivative(q, qd, v_kv, r);
		r += cs->NRow();
	}
	for (unsigned int i = 0; i < spar.nnz(); i++)
	{
		m_kj(spar.ridx[i], spar.cidx[i]) = spar.value[i];
	}
	dgesv_(&ptDof, &lapack_one, m_kj.getDataPointer(), &ptDof, permutation, v_kv.get_ptr(), &ptDof, &lapack_info);
	for (unsigned int i = 0; i < s_k; i++)
		qdd(i + 3) += v_kv(i);

	foreach(QString str, bodyList)
	{
		rigidBody *rb = bodies[str];
		resultDataType rdt;
		//rdt.time = 
	}

	delete[] permutation;
	return niter;
}
