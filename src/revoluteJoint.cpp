#include "revoluteJoint.h"

revoluteJoint::revoluteJoint(QString _name)
	: constraint(_name, REVOLUTE)
{
	constraint::nDimension += 2;
	constraint::nrow = 2;
	constraint::nnz = 8;
	constraint::nTotalNNZ += constraint::nnz;
	jrforce = new double[constraint::nrow];
	memset(jrforce, 0, sizeof(double) * constraint::nrow);
}

revoluteJoint::~revoluteJoint()
{

}

// void revoluteJoint::setBaseMarker(vecd3 q, vecd3 r)
// {
// 	baseMarker.s = math::global2local(ib->TM(), pos - ib->Position());
// 	baseMarker.actionAxis = math::cross(q, r);
// }
// 
// void revoluteJoint::setActionMarker(vecd3 q, vecd3 r)
// {
// 	actionMarker.s = math::global2local(jb->TM(), pos - jb->Position());
// 	actionMarker.actionAxis = math::cross(q, r);
// }

void revoluteJoint::constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int r, bool isjp)
{
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;
	//setSinCos(qd(ci + 2), qd(cj + 2));
	transformationMatrix dAi = derivateTM(q(ci + 2));
	transformationMatrix dAj = derivateTM(q(cj + 2));
	
	
	// Constraint jacobian of base body
	if (ci)
	{
		ci -= 3;
		lhs(r, ci) = 1;
		lhs(r + 1, ci + 1) = 1;
		vecd3 up = math::local2global(dAi, baseMarker.s);
		lhs(r, ci + 2) = up.X();
		lhs(r + 1, ci + 2) = up.Y();
	}
	if (cj)
	{
		// Constraint jacobian of action body
		cj -= 3;
		lhs(r, cj) = -1;
		lhs(r + 1, cj + 1) = -1;
		vecd3 up = math::local2global(dAj, actionMarker.s);
		lhs(r, cj + 2) = -up.X();
		lhs(r + 1, cj + 2) = -up.Y();
	}
	
	
}

int revoluteJoint::constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul)
{
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;
	//setSinCos(q(ci + 2), q(cj + 2));
	transformationMatrix Ai = TM(q(ci + 2));
	transformationMatrix Aj = TM(q(cj + 2));
	vecd3 pi(q(ci), q(ci + 1), q(ci + 2));
	vecd3 pj(q(cj), q(cj + 1), q(cj + 2));
	vecd3 p1 = pi + math::local2global(Ai, baseMarker.s);
	vecd3 p2 = pj + math::local2global(Aj, actionMarker.s);
	vecd3 ce = pi + math::local2global(Ai, baseMarker.s) - pj - math::local2global(Aj, actionMarker.s);
	rhs(i) = mul * ce.X();
	rhs(i + 1) = mul * ce.Y();
	return 0;
}

void revoluteJoint::derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i)
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

void revoluteJoint::lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1, double mul)
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