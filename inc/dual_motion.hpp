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
	dual_motion() : model() { init(); }
	~dual_motion(){}

	virtual void init()
	{
		model::setModelName("dual motion");
		hardPoint *active_link = createHardPoint("active_link", 1.043, 0, 0);
		hardPoint *link_cam = createHardPoint("link_cam", 1.42724496697479, -0.0495610265684507, 0);
		hardPoint *cam_ground = createHardPoint("cam_ground", 1.340390464239, 0, 0);
		rigidBody *ground = createRigidBody("ground");
		ground->setGround(true);

		rigidBody *active = createRigidBody("active");
		active->setMass(1.93);
		active->setInertia(0.002253619676);
		//double ang = getAngleBetween2HP(hp0, hp1);
		active->setAngle(0.0);
		//gp_Pnt pos = getHalfBetween2HP(hp0, hp1);
		active->setPosition(1.00165423949275, 0.000002362435193444, 0.0);
		active->setShapePath("C:/DMotion/data/active1.igs");
		

		rigidBody *link = createRigidBody("link");
		link->setMass(1.886852634);
		link->setInertia(0.028338286);
		//ang = getAngleBetween2HP(hp1, hp2);
		link->setAngle(0);
		//pos = getHalfBetween2HP(hp1, hp2);
		link->setPosition(1.2318071684038, -0.0349156464194469, 0.0);
		link->setShapePath("C:/DMotion/data/active2.igs");
		

		rigidBody *cam = createRigidBody("cam");
		cam->setMass(3.154198326);
		cam->setInertia(0.01808158862);
		cam->setPosition(1.31074640346896, -0.0199427734315464, 0.0);
		cam->setAngle(0);
		cam->setShapePath("C:/DMotion/data/Cam part.igs");

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
		//double len = getLengthBetween2HP(hp0, hp1);
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

		drivingConstraint *active_driving = createDrivingConstraint("active_driving");
		active_driving->setTargetBody(active, AXIS_X);
		//active_driving->setConstantVelocity(-0.1);
		active_driving->setVelocityProfile("C:/DMotion/data/main_velocity.txt");
	}
};
#endif