#ifndef DUAL_MOTION_HOLE_HPP
#define DUAL_MOTION_HOLE_HPP

#include "model.h"

class dual_motion_hole : public model
{
public:
	dual_motion_hole() : model(HOLE_CAM_TYPE) { init(); }
	~dual_motion_hole(){}

	virtual void init()
	{
		// 		model::setModelName("baseModel");
		// 		QString userPath = getenv("USERPROFILE");
		// 		userPath += "/Documents/dualMotion/";
		// 		model::setModelPath(userPath);
		hardPoint *nozzle_link = createHardPoint("nozzle_link", 0.0553, 0, 0);
		hardPoint *link_hinge = createHardPoint("link_hinge", 0.3423, 0, 0);
		hardPoint *hinge_cam = createHardPoint("hinge_cam", 0.47953, -0.10592, 0);
		hardPoint *cam_ground = createHardPoint("cam_ground", 0.40523, -0.01, 0.0);
		hardPoint *cam_arc = createHardPoint("cam_arc", 0.29512, 0.035, 0.0);
		//hardPoint *passive_dummy = createHardPoint("passive_dummy", 0.000509901920295489, 0.00773584919364184, 0.0);
		rigidBody *ground = createRigidBody("Ground");
		ground->setGround(true);

		rigidBody *nozzle = createRigidBody("Nozzle");
		nozzle->setMass(1.78);
		nozzle->setInertia(0.002837);
		//double ang = getAngleBetween2HP(hp0, hp1);
		nozzle->setAngle(0.0);
		nozzle->setCoordinateNumber(3);
		//gp_Pnt pos = getHalfBetween2HP(hp0, hp1);
		nozzle->setPosition(0, 0, 0);
		//	active->setShapePath("C:/DMotion/data/ver2/Active head.step");


		rigidBody *link = createRigidBody("Link");
		link->setMass(1.59);
		link->setInertia(0.013875);
		//ang = getAngleBetween2HP(hp1, hp2);
		link->setAngle(0);
		//pos = getHalfBetween2HP(hp1, hp2);
		link->setCoordinateNumber(3);
		link->setPosition(0.18564, 0.0, 0);
		//	link->setShapePath("C:/DMotion/data/ver2/Active_link.step");


		rigidBody *hinge = createRigidBody("Hinge");
		hinge->setMass(0.76);
		hinge->setInertia(0.002398);
		hinge->setPosition(0.41740, -0.06222, 0);
		hinge->setAngle(0);
		hinge->setCoordinateNumber(3);
		//		cam->setShapePath("C:/DMotion/data/ver2/CAM.step");

		rigidBody *cam = createRigidBody("Cam");
		cam->setMass(3.46);
		cam->setInertia(0.020547);
		cam->setPosition(0.37586, -0.01532, 0);
		cam->setAngle(0);
		cam->setCoordinateNumber(3);

// 		rigidBody *roller = createRigidBody("roller");
// 		roller->setMass(3.47);
// 		roller->setInertia(0.032325);
// 		roller->setPosition(0.29512, 0.035, 0.0);
// 		roller->setAngle(0);
// 		roller->setCoordinateNumber(3);

		rigidBody *arc = createRigidBody("Arc");
		arc->setMass(3.47);
		arc->setInertia(0.032325);
		arc->setPosition(0.11028, 0.00709, 0);
		arc->setAngle(0);
		arc->setCoordinateNumber(3);
		//	passive->setShapePath("C:/DMotion/data/ver2/Passive.step");

		translateJoint *nozzle_trans = createTraslateJoint("Nozzle Trans.");
		gp_Pnt pos = nozzle->Position();
		nozzle_trans->setPosition(pos.X(), pos.Y(), pos.Z());
		nozzle_trans->setBaseBody(ground);
		nozzle_trans->setActionBody(nozzle);
		nozzle_trans->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
		nozzle_trans->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, -1.0, 0));
		nozzle_trans->defineAngleConstraint();
		nozzle_trans->setReactionForceTypes(NOZZLE_TRANS_FY, NOZZLE_TRANS_TR);
		//	ground_active_tra->setIgnoreRotationConstraint(false);

		revoluteJoint *nozzle_link_rev = createRevoluteJoint("Nozzle-Link Rev.");
		pos = nozzle_link->loc;
		nozzle_link_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		nozzle_link_rev->setBaseBody(nozzle);
		nozzle_link_rev->setActionBody(link);
		nozzle_link_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		//double len = getLengthBetween2HP(hp0, hp1);
		nozzle_link_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		nozzle_link_rev->bindHardPoint(nozzle_link);
		nozzle_link_rev->setReactionForceTypes(NOZZLE_LINK_REV_FX, NOZZLE_LINK_REV_FY);

		revoluteJoint *link_hinge_rev = createRevoluteJoint("Link-Hinge Rev.");
		pos = link_hinge->loc;
		link_hinge_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		link_hinge_rev->setBaseBody(link);
		link_hinge_rev->setActionBody(hinge);
		link_hinge_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		link_hinge_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		link_hinge_rev->bindHardPoint(link_hinge);
		link_hinge_rev->setReactionForceTypes(LINK_HINGE_REV_FX, LINK_HINGE_REV_FY);

// 		translateJoint *link_trans = createTraslateJoint("Link Trans.");
// 		pos = link->Position();
// 		link_trans->setPosition(pos.X(), pos.Y(), pos.Z());
// 		link_trans->setBaseBody(ground);
// 		link_trans->setActionBody(link);
// 		link_trans->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
// 		link_trans->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, -1.0, 0));
// 		link_trans->defineAngleConstraint();
// 		link_trans->setReactionForceTypes(LINK_TRANS_FY, LINK_TRANS_TR);
		simplifiedConstraint *link_simple = createSimplifiedConstraint("Link Simple");
		pos = link->Position();
		link_simple->setPosition(pos.X(), pos.Y(), pos.Z());
		link_simple->setBaseBody(link);
		//link_simple->setBaseMarker(vecd3)
		link_simple->setConstantValue(pos.Y());
		link_simple->bindHardPoint(link_hinge);
		link_simple->setDirection(simplifiedConstraint::VERTICAL);
		link_simple->setReactionForceTypes(LINK_SIMPLE_FY, NO_REACTION_TYPE);

		revoluteJoint *hinge_cam_rev = createRevoluteJoint("Hinge-Cam Rev.");
		pos = hinge_cam->loc;
		hinge_cam_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		hinge_cam_rev->setBaseBody(hinge);
		hinge_cam_rev->setActionBody(cam);
		hinge_cam_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		hinge_cam_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		hinge_cam_rev->bindHardPoint(hinge_cam);
		hinge_cam_rev->setReactionForceTypes(HINGE_CAM_REV_FX, HINGE_CAM_REV_FY);

		revoluteJoint *cam_ground_rev = createRevoluteJoint("Cam-Ground Rev.");
		pos = cam_ground->loc;
		cam_ground_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		cam_ground_rev->setBaseBody(cam);
		cam_ground_rev->setActionBody(ground);
		cam_ground_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		cam_ground_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		cam_ground_rev->bindHardPoint(cam_ground);
		cam_ground_rev->setReactionForceTypes(CAM_GROUND_REV_FX, CAM_GROUND_REV_FY);
		
// 		revoluteJoint *arc_roller_rev = createRevoluteJoint("Arc-Roller_Rev.");
// 		pos = cam_arc->loc;
// 		arc_roller_rev->setPosition(pos.X(), pos.Y()-0.1, pos.Z());
// 		arc_roller_rev->setBaseBody(roller);
// 		arc_roller_rev->setActionBody(arc);
// 		arc_roller_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
// 		arc_roller_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
// 		arc_roller_rev->bindHardPoint(cam_arc);
// 		arc_roller_rev->setReactionForceTypes(ARC_ROLLER_REV_FX, ARC_ROLLER_REV_FY);
// 		arc_roller_rev->setFixedWhelKinematicAnalysis(true);

		simplifiedConstraint *arc_vertical = createSimplifiedConstraint("Arc Vertical");
		pos = cam_arc->loc;
		arc_vertical->setPosition(pos.X(), pos.Y(), pos.Z());
		arc_vertical->setBaseBody(arc);
		arc_vertical->setConstantValue(cam_arc->loc.Y());
		arc_vertical->bindHardPoint(cam_arc);
		arc_vertical->setDirection(simplifiedConstraint::VERTICAL);
		arc_vertical->setReactionForceTypes(ARC_SIMPLE_FY, NO_REACTION_TYPE);

		simplifiedConstraint *arc_rotation = createSimplifiedConstraint("Arc Rotation");
		pos = arc->Position();
		arc_rotation->setPosition(pos.X(), pos.Y(), pos.Z());
		arc_rotation->setBaseBody(arc);
		arc_rotation->setConstantValue(arc->Angle());
		arc_rotation->setDirection(simplifiedConstraint::ROTATION);
		arc_rotation->setReactionForceTypes(ARC_SIMPLE_TR, NO_REACTION_TYPE);

		//arc_trans->setActionBody(arc);
// 		arc_trans->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
// 		arc_trans->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, -1.0, 0));
// 		arc_trans->defineAngleConstraint();
// 		arc_trans->setReactionForceTypes(ARC_TRANS_FY, ARC_TRANS_TR);
// 		translateJoint *arc_trans = createTraslateJoint("Arc Trans.");
// 		pos = arc->Position();
// 		arc_trans->setPosition(pos.X(), pos.Y(), pos.Z());
// 		arc_trans->setBaseBody(ground);
// 		arc_trans->setActionBody(arc);
// 		arc_trans->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
// 		arc_trans->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, -1.0, 0));
// 		arc_trans->defineAngleConstraint();
// 		arc_trans->setReactionForceTypes(ARC_TRANS_FY, ARC_TRANS_TR);

		drivingConstraint *nozzle_driving = createDrivingConstraint("Nozzle_driving");
		nozzle_driving->setTargetBody(nozzle, AXIS_X);
		// 		//active_driving->setConstantVelocity(-0.1);
		nozzle_driving->setVelocityProfile("../data/NozzleVelocityProfile.txt");
		//nozzle_driving->setVelocityProfile("C:/DMotion/data/untitled2.txt");

		drivingConstraint *arc_driving = createDrivingConstraint("Arc_driving");
		arc_driving->setTargetBody(arc, AXIS_X);
		arc_driving->setVelocityProfile("../data/ArcVelocityProfile_avoid.txt");
		//arc_driving->setVelocityProfile("C:/DMotion/data/untitled.txt");

		pointFollower* pf = createPointFollower("Arc-Cam PF");
		pos = cam_arc->loc;
		pf->setPosition(pos.X(), pos.Y(), pos.Z());
		pf->setBaseBody(arc);
		pf->setActionBody(cam);
		pf->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		pf->initialize(cam_ground->loc, cam_arc->loc);
		//pf->setLocalFromBaseBody();
// 		pf->setActionHardPoint(cam_ground->loc);
// 		pf->setInitialAngle(M_PI);
// 		pf->setCM2HardPoint();
// 		pf->updateBaseMarker();
		pf->bindHardPoint(cam_arc);
		pf->setReactionForceTypes(PROFILE_FX, PROFILE_FY);

		hpList.push_back(nozzle_link->name);
		hpList.push_back(link_hinge->name);
		hpList.push_back(hinge_cam->name);
		hpList.push_back(cam_ground->name);
		hpList.push_back(cam_arc->name);

		bodyList.push_back(ground->Name());
		bodyList.push_back(nozzle->Name());
		bodyList.push_back(link->Name());
		bodyList.push_back(hinge->Name());
		bodyList.push_back(cam->Name());
		//bodyList.push_back(roller->Name());
		bodyList.push_back(arc->Name());

		constList.push_back(nozzle_trans->Name());
		constList.push_back(nozzle_link_rev->Name());
		constList.push_back(link_simple->Name());
		constList.push_back(link_hinge_rev->Name());
		constList.push_back(hinge_cam_rev->Name());
		constList.push_back(cam_ground_rev->Name());
		//constList.push_back(arc_roller_rev->Name());
	//	constList.push_back(arc_trans->Name());
		constList.push_back(arc_vertical->Name());
		constList.push_back(arc_rotation->Name());
		constList.push_back(nozzle_driving->Name());
		constList.push_back(arc_driving->Name());

		designVariable* dv_nozzleLink = createDesignVariable("nozzleLink_x");
		dv_nozzleLink->setConstraint(nozzle_link_rev);
		dv_nozzleLink->setDirection(AXIS_X);

		designVariable* dv_linkHingex = createDesignVariable("linkHinge_x");
		dv_linkHingex->setConstraint(link_hinge_rev);
		dv_linkHingex->setDirection(AXIS_X);

		designVariable* dv_hingeCamx = createDesignVariable("hingeCam_x");
		dv_hingeCamx->setConstraint(hinge_cam_rev);
		dv_hingeCamx->setDirection(AXIS_X);

		designVariable* dv_camGroundx = createDesignVariable("camGround_x");
		dv_camGroundx->setConstraint(cam_ground_rev);
		dv_camGroundx->setDirection(AXIS_X);

		designVariable* dv_arcCamx = createDesignVariable("arcCam_x");
		dv_arcCamx->setConstraint(pf);
		dv_arcCamx->setDirection(AXIS_X);

		designVariable* dv_nozzleLinky = createDesignVariable("nozzleLink_y");
		dv_nozzleLinky->setConstraint(nozzle_link_rev);
		dv_nozzleLinky->setDirection(AXIS_Y);

		designVariable* dv_linkHingey = createDesignVariable("linkHinge_y");
		dv_linkHingey->setConstraint(link_hinge_rev);
		dv_linkHingey->setDirection(AXIS_Y);

		designVariable* dv_hingeCamy = createDesignVariable("hingeCam_y");
		dv_hingeCamy->setConstraint(hinge_cam_rev);
		dv_hingeCamy->setDirection(AXIS_Y);

		designVariable* dv_camGroundy = createDesignVariable("camGround_y");
		dv_camGroundy->setConstraint(cam_ground_rev);
		dv_camGroundy->setDirection(AXIS_Y);

		designVariable* dv_arcCamy = createDesignVariable("arcCam_y");
		dv_arcCamy->setConstraint(pf);
		dv_arcCamy->setDirection(AXIS_Y);

		distanceConstraint* dc_dist = createDistanceDesignConstraint("dc_dist");
		dc_dist->setTwoHardPoints(cam_arc, cam_ground);
		dc_dist->setcheckUpper();
		dc_dist->setConstraintValue(0.035);
		dc_dist->setComparisonTarget(designConstraint::DC_VERTICAL);

		reactionMap[0] = NOZZLE_TRANS_FY;// "Nozzle Trans.(FY)";
		reactionMap[1] = NOZZLE_TRANS_TR;// "Nozzle Trans.(TR)";
		
		reactionMap[2] = NOZZLE_LINK_REV_FX;// "Nozzle-Link Rev.(FX)";
		reactionMap[3] = NOZZLE_LINK_REV_FY;//"Nozzle-Link Rev.(FY)";
		reactionMap[4] = LINK_SIMPLE_FY;
		//reactionMap[4] = LINK_TRANS_FY;
	///	reactionMap[5] = LINK_TRANS_TR;
		reactionMap[5] = LINK_HINGE_REV_FX;// "Link-Hinge Rev.(FX)";
		reactionMap[6] = LINK_HINGE_REV_FY;// "Link-Hinge Rev.(FY)";
		reactionMap[7] = HINGE_CAM_REV_FX;// "Hinge-Cam Rev.(FX)";
		reactionMap[8] = HINGE_CAM_REV_FY;// "Hinge-Cam Rev.(FY)";
		reactionMap[9] = CAM_GROUND_REV_FX;// "Cam-Ground Rev.(FX)";
		reactionMap[10] = CAM_GROUND_REV_FY;// "Cam-Ground Rev.(FY)";
		//reactionMap[11] = ARC_ROLLER_REV_FX;
		//reactionMap[12] = ARC_ROLLER_REV_FY;
		reactionMap[11] = ARC_SIMPLE_FY;// "Arc Trans.(FY)";
		reactionMap[12] = ARC_SIMPLE_TR;// "Arc Trans.(TR)";
		reactionMap[13] = PROFILE_FX;// "Arc-Cam PF(FX)";
		reactionMap[14] = PROFILE_FY;// "Arc-Cam PF(FY)";
	}
};
#endif