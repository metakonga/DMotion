#ifndef DUAL_MOTION_HPP
#define DUAL_MOTION_HPP

#include "model.h"

double motion(double t)
{
	return 0.1 * t;
}

class dual_motion : public model
{
public:
	dual_motion() : model(ORIGINAL_CAM_TYPE) { init(); }
	~dual_motion(){}

	virtual void init()
	{
// 		model::setModelName("baseModel");
// 		QString userPath = getenv("USERPROFILE");
// 		userPath += "/Documents/dualMotion/";
// 		model::setModelPath(userPath);
		hardPoint *active_link = createHardPoint("nozzle_link", 0, 0, 0);
		hardPoint *link_cam = createHardPoint("link_cam", 0.38424, -0.04956, 0);
		hardPoint *cam_ground = createHardPoint("cam_ground", 0.29739, 0, 0);
		hardPoint *cam_passive = createHardPoint("cam_arc", 0.17739, 0.0, 0.0);
		//hardPoint *passive_dummy = createHardPoint("passive_dummy", 0.000509901920295489, 0.00773584919364184, 0.0);
		rigidBody *ground = createRigidBody("Ground");
		ground->setGround(true);

		rigidBody *active = createRigidBody("Nozzle");
		active->setMass(1.8);
		active->setInertia(0.002253619676);
		//double ang = getAngleBetween2HP(hp0, hp1);
		active->setAngle(0.0);
		active->setCoordinateNumber(3);
		//gp_Pnt pos = getHalfBetween2HP(hp0, hp1);
		active->setPosition(-0.0414557605072536, 0.00000236243519342979, 0.0);
	//	active->setShapePath("C:/DMotion/data/ver2/Active head.step");


		rigidBody *link = createRigidBody("Link");
		link->setMass(2.3);
		link->setInertia(0.028338286);
		//ang = getAngleBetween2HP(hp1, hp2);
		link->setAngle(0);
		//pos = getHalfBetween2HP(hp1, hp2);
		link->setCoordinateNumber(3);
		link->setPosition(0.188697168403797, -0.0349156464194469, 0.0);
	//	link->setShapePath("C:/DMotion/data/ver2/Active_link.step");


		rigidBody *cam = createRigidBody("Cam");
		cam->setMass(2.7);
		cam->setInertia(0.0230813979);
		cam->setPosition(0.262163603372142, -0.030311213723227, 0.0);
		cam->setAngle(0);
		cam->setCoordinateNumber(3);
//		cam->setShapePath("C:/DMotion/data/ver2/CAM.step");

  		rigidBody *passive = createRigidBody("Arc");
  		passive->setMass(7.0);
  		passive->setInertia(0.05849749842);
  		passive->setPosition(0.000509901920295489, 0.00773584919364184, 0.0);
  		passive->setAngle(0);
  		passive->setCoordinateNumber(3);
  	//	passive->setShapePath("C:/DMotion/data/ver2/Passive.step");

		translateJoint *ground_active_tra = createTraslateJoint("Nozzle Trans.");
		gp_Pnt pos = active->Position();
		ground_active_tra->setPosition(pos.X(), pos.Y(), pos.Z());
		ground_active_tra->setBaseBody(ground);
		ground_active_tra->setActionBody(active);
		ground_active_tra->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
		ground_active_tra->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, -1.0, 0));
		ground_active_tra->defineAngleConstraint();
		ground_active_tra->setReactionForceTypes(NOZZLE_TRANS_FY, NOZZLE_TRANS_TR);
		//	ground_active_tra->setIgnoreRotationConstraint(false);

		revoluteJoint *active_link_rev = createRevoluteJoint("Nozzle-Link Rev.");
		pos = active_link->loc;
		active_link_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		active_link_rev->setBaseBody(active);
		active_link_rev->setActionBody(link);
		active_link_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		//double len = getLengthBetween2HP(hp0, hp1);
		active_link_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		active_link_rev->bindHardPoint(active_link);
		active_link_rev->setReactionForceTypes(NOZZLE_LINK_REV_FX, NOZZLE_LINK_REV_FY);

		revoluteJoint *link_cam_rev = createRevoluteJoint("Link-Cam Rev.");
		pos = link_cam->loc;
		link_cam_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		link_cam_rev->setBaseBody(link);
		link_cam_rev->setActionBody(cam);
		link_cam_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		link_cam_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		link_cam_rev->bindHardPoint(link_cam);
		link_cam_rev->setReactionForceTypes(LINK_CAM_REV_FX, LINK_CAM_REV_FY);

		revoluteJoint *cam_ground_rev = createRevoluteJoint("Cam-Ground Rev.");
		pos = cam_ground->loc;
		cam_ground_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		cam_ground_rev->setBaseBody(cam);
		cam_ground_rev->setActionBody(ground);
		cam_ground_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		cam_ground_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		cam_ground_rev->bindHardPoint(cam_ground);
		cam_ground_rev->setReactionForceTypes(CAM_GROUND_REV_FX, CAM_GROUND_REV_FY);

		translateJoint *ground_passive_tra = createTraslateJoint("Arc Trans.");
		pos = passive->Position();
		ground_passive_tra->setPosition(pos.X(), pos.Y(), pos.Z());
		ground_passive_tra->setBaseBody(ground);
		ground_passive_tra->setActionBody(passive);
		ground_passive_tra->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
		ground_passive_tra->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, -1.0, 0));
		ground_passive_tra->defineAngleConstraint();
		ground_passive_tra->setReactionForceTypes(ARC_TRANS_FY, ARC_TRANS_TR);

		drivingConstraint *active_driving = createDrivingConstraint("Nozzle_driving");
 		active_driving->setTargetBody(active, AXIS_X);
// 		//active_driving->setConstantVelocity(-0.1);
 		active_driving->setVelocityProfile("../data/NozzleVelocityProfile.txt");

		drivingConstraint *passive_driving = createDrivingConstraint("Arc_driving");
		passive_driving->setTargetBody(passive, AXIS_X);
		passive_driving->setVelocityProfile("../data/ArcVelocityProfile_avoid.txt");

		pointFollower* pf = createPointFollower("Arc-Cam PF");
		pos = cam_passive->loc;
		pf->setPosition(pos.X(), pos.Y(), pos.Z());
		pf->setBaseBody(passive);
		pf->setActionBody(cam);
		pf->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		pf->initialize(cam_ground->loc, cam_passive->loc);
// 		pf->setLocalFromBaseBody();
// 		pf->setActionHardPoint(cam_ground->loc);
// 		pf->setInitialAngle(M_PI);
// 		pf->setCM2HardPoint();
// 		pf->updateBaseMarker();
		pf->bindHardPoint(cam_passive);
		pf->setReactionForceTypes(PROFILE_FX, PROFILE_FY);

		hpList.push_back(active_link->name);
		hpList.push_back(link_cam->name);
		hpList.push_back(cam_ground->name);
		hpList.push_back(cam_passive->name);
	
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

		designVariable* dv_headLinkx = createDesignVariable("headLink_x");
		dv_headLinkx->setConstraint(active_link_rev);
		dv_headLinkx->setDirection(AXIS_X);

		designVariable* dv_linkCamx = createDesignVariable("linkCam_x");
		dv_linkCamx->setConstraint(link_cam_rev);
		dv_linkCamx->setDirection(AXIS_X);

		designVariable* dv_camGroundx = createDesignVariable("camGround_x");
		dv_camGroundx->setConstraint(cam_ground_rev);
		dv_camGroundx->setDirection(AXIS_X);

		designVariable* dv_camPVx = createDesignVariable("camPV_x");
		dv_camPVx->setConstraint(pf);
		dv_camPVx->setDirection(AXIS_X);

		designVariable* dv_headLinky = createDesignVariable("headLink_y");
		dv_headLinky->setConstraint(active_link_rev);
		dv_headLinky->setDirection(AXIS_Y);

		designVariable* dv_linkCamy = createDesignVariable("linkCam_y");
		dv_linkCamy->setConstraint(link_cam_rev);
		dv_linkCamy->setDirection(AXIS_Y);

		designVariable* dv_camGroundy = createDesignVariable("camGround_y");
		dv_camGroundy->setConstraint(cam_ground_rev);
		dv_camGroundy->setDirection(AXIS_Y);

		designVariable* dv_camPVy = createDesignVariable("camPV_y");
		dv_camPVy->setConstraint(pf);
		dv_camPVy->setDirection(AXIS_Y);

// 		distanceConstraint* dc_dist = createDistanceDesignConstraint("dc_dist");
// 		dc_dist->setTwoHardPoints(cam_passive, cam_ground);
// 		dc_dist->setcheckUpper();
// 		dc_dist->setConstraintValue(0.035);
// 		dc_dist->setComparisonTarget(designConstraint::DC_VERTICAL);

		reactionMap[0] = NOZZLE_TRANS_FY;
		reactionMap[1] = NOZZLE_TRANS_TR;// "Nozzle Trans.(TR)";
		reactionMap[2] = NOZZLE_LINK_REV_FX;// "Nozzle-Link Rev.(FX)";
		reactionMap[3] = NOZZLE_LINK_REV_FY;// "Nozzle-Link Rev.(FY)";
		reactionMap[4] = LINK_CAM_REV_FX;// "Link-Cam Rev.(FX)";
		reactionMap[5] = LINK_CAM_REV_FY;// "Link-Cam Rev.(FY)";
		reactionMap[6] = CAM_GROUND_REV_FX;// "Cam-Ground Rev.(FX)";
		reactionMap[7] = CAM_GROUND_REV_FY;// "Cam-Ground Rev.(FY)";
		reactionMap[8] = ARC_TRANS_FY;// "Arc Trans.(FY)";
		reactionMap[9] = ARC_TRANS_TR;// "Arc Trans.(TR)";
		reactionMap[10] = PROFILE_FX;// "Arc-Cam PF(FX)";
		reactionMap[11] = PROFILE_FY;// "Arc-Cam PF(FY)";
	}
};
#endif