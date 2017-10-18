#ifndef SLIDER_CRANK_HPP
#define SLIDER_CRANK_HPP

#include "model.h"

class slider_crank : public model
{
public:
	slider_crank() : model() { init(); }
	~slider_crank(){}

	virtual void init()
	{
		model::setModelName("slider crank");
		hardPoint *hp0 = createHardPoint("hp0", 0, 0, 0);
		hardPoint *hp1 = createHardPoint("hp1", 0.3, 0.3, 0);
		hardPoint *hp2 = createHardPoint("hp2", 1.2, 0, 0);
		rigidBody *ground = createRigidBody("ground");
		ground->setGround(true);
		rigidBody *crank = createRigidBody("crank");
		crank->setMass(4);
		crank->setInertia(0.07);
		double ang = getAngleBetween2HP(hp0, hp1);
		crank->setAngle(ang);
		gp_Pnt pos = getHalfBetween2HP(hp0, hp1);
		crank->setPosition(pos.X(), pos.Y(), pos.Z());
		
		rigidBody *cbody = createRigidBody("connecting body");
		cbody->setMass(52);
		cbody->setInertia(4);
		ang = getAngleBetween2HP(hp1, hp2);
		cbody->setAngle(ang);
		pos = getHalfBetween2HP(hp1, hp2);
		cbody->setPosition(pos.X(), pos.Y(), pos.Z());
		
		rigidBody *slider = createRigidBody("slider");
		slider->setMass(93);
		slider->setInertia(0.7);
		slider->setPosition(1.2, 0, 0);
		slider->setAngle(0);

		revoluteJoint *ground_crank_rev = createRevoluteJoint("ground_crank_rev");
		pos = hp0->loc;
		ground_crank_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		ground_crank_rev->setBaseBody(ground);
		ground_crank_rev->setActionBody(crank);
		ground_crank_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		double len = getLengthBetween2HP(hp0, hp1);
		ground_crank_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		ground_crank_rev->bindHardPoint(hp0);

		revoluteJoint *crank_connecting_rev = createRevoluteJoint("crank_connecting_rev");
		pos = hp1->loc;
		crank_connecting_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		crank_connecting_rev->setBaseBody(crank);
		crank_connecting_rev->setActionBody(cbody);
		crank_connecting_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		crank_connecting_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		crank_connecting_rev->bindHardPoint(hp1);

		revoluteJoint *connecting_slider_rev = createRevoluteJoint("connecting_slider_rev");
		pos = hp2->loc;
		connecting_slider_rev->setPosition(pos.X(), pos.Y(), pos.Z());
		connecting_slider_rev->setBaseBody(cbody);
		connecting_slider_rev->setActionBody(slider);
		connecting_slider_rev->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 1.0, 0));
		connecting_slider_rev->setActionMarker(vecd3(-1.0, 0, 0), vecd3(0, 1.0, 0));
		connecting_slider_rev->bindHardPoint(hp2);

		translateJoint *ground_slider_tra = createTraslateJoint("ground_slider_tra");
		ground_slider_tra->setPosition(pos.X(), pos.Y(), pos.Z());
		ground_slider_tra->setBaseBody(ground);
		ground_slider_tra->setActionBody(slider);
		ground_slider_tra->setBaseMarker(vecd3(1.0, 0, 0), vecd3(0, 0, -1.0));
		ground_slider_tra->setActionMarker(vecd3(0, 0, -1.0), vecd3(0, 1.0, 0));
		ground_slider_tra->defineAngleConstraint();
	}
};
#endif