#include "translateJoint.h"

translateJoint::translateJoint(QString _name)
	: constraint(_name, TRANSLATION)
	, dangle(0)
{
	constraint::nDimension += 2;
	constraint::nrow = 2;
	constraint::nnz = 8;
	constraint::nTotalNNZ += constraint::nnz;
	jrforce = new double[constraint::nrow];
}

translateJoint::~translateJoint()
{

}

void translateJoint::setBaseMarker(vecd3 q, vecd3 r)
{
	baseMarker.s = math::global2local(ib->TM(), pos - ib->Position());
	baseMarker.actionAxis = math::cross(q, r);
}

void translateJoint::setActionMarker(vecd3 q, vecd3 r)
{
	actionMarker.s = math::global2local(jb->TM(), pos - jb->Position());
	actionMarker.actionAxis = math::cross(q, r);
}

void translateJoint::defineAngleConstraint()
{
	dangle = ib->Angle() - jb->Angle();
}

void translateJoint::constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul)
{
	//setSinCos(ib->Angle(), jb->Angle());
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;
	double thi = q(ci + 2);
	double thj = q(cj + 2);
	transformationMatrix Ai = TM(thi);
	transformationMatrix Aj = TM(thj);
	vecd3 hi = math::local2global(Ai, baseMarker.actionAxis);
// 	double hix = Ai[0] * baseMarker.actionAxis.X() + Ai[1] * baseMarker.actionAxis.Y();
// 	double hiy = Ai[2] * baseMarker.actionAxis.X() + Ai[3] * baseMarker.actionAxis.Y();
	vecd3 pi = ib->Position();
	vecd3 pj = jb->Position();
	vecd3 rij
		= pi
		+ math::local2global(Ai, baseMarker.s)
		- pj
		- math::local2global(Aj, actionMarker.s);
	rhs(i) = mul * (thi - thj - dangle);
	rhs(i + 1) = mul * math::dot(hi, rij);// hix * rij.X() + hiy * rij.Y();
}

void translateJoint::constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i)
{	
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;
	double thi = q(ci + 2);
	double thj = q(cj + 2);
	//setSinCos(thi, thj);
	transformationMatrix Ai = TM(thi);
	transformationMatrix Aj = TM(thj);
	/*setSinCos(qd(ci + 2), qd(cj + 2));*/
	transformationMatrix dAi = derivateTM(qd(ci + 2));
	transformationMatrix dAj = derivateTM(qd(cj + 2));
	
	vecd3 pi(q(ci), q(ci + 1), q(ci + 2));
	vecd3 pj(q(cj), q(cj + 1), q(cj + 2));
	vecd3 hi = math::local2global(Ai, baseMarker.actionAxis);
	vecd3 rij
		= pi
		+ math::local2global(Ai, baseMarker.s)
		- pj
		- math::local2global(Aj, actionMarker.s);
	if (ci)
	{
		ci -= 3;
		lhs(i, ci + 2) = 1;
		lhs(i + 1, ci) = hi.X();
		lhs(i + 1, ci + 1) = hi.Y();
		lhs(i + 1, ci + 2)
			= math::dot(rij, math::local2global(dAi, baseMarker.actionAxis))
			+ math::dot(hi, math::local2global(dAi, baseMarker.s));
	}
	if (cj)
	{
		cj -= 3;
		lhs(i, cj + 2) = -1;
		lhs(i + 1, cj) = -hi.X();
		lhs(i + 1, cj + 1) = -hi.Y();
		lhs(i + 1, cj + 2) = -math::dot(hi, math::local2global(dAj, actionMarker.s));
	}
	
}

void translateJoint::derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i)
{
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;
	double wi = qd(ci + 2);
	double wj = qd(cj + 2);
	//setSinCos(q(ci + 2), q(cj + 2));
	transformationMatrix Ai = TM(q(ci + 2));
	transformationMatrix Aj = TM(q(cj + 2));
	//setSinCos(wi, wj);
	transformationMatrix dAi = derivateTM(q(ci + 2));
	transformationMatrix dAj = derivateTM(q(cj + 2));
	vecd3 pi(q(ci), q(ci + 1), q(ci + 2));
	vecd3 pj(q(cj), q(cj + 1), q(cj + 2));
	vecd3 vi(qd(ci), qd(ci + 1), qd(ci + 2));
	vecd3 vj(qd(cj), qd(cj + 1), qd(cj + 2));
	vecd3 _hi = baseMarker.actionAxis;
	vecd3 hi = math::local2global(Ai, _hi);
	vecd3 _upi = baseMarker.s;
	vecd3 upi = math::local2global(Ai, _upi);
	vecd3 _upj = actionMarker.s;
	vecd3 upj = math::local2global(Aj, _upj);
	vecd3 rij
		= pi
		+ math::local2global(Ai, baseMarker.s)
		- pj
		- math::local2global(Aj, actionMarker.s);
	double Qd1 = 0.0;
	double Qd2
		= -2.0 * wi * math::dot(math::local2global(dAi, _hi), vi - vj)
		- wi * wi * (math::dot(_upi, _hi) - math::dot(rij, hi) - math::dot(upi, hi))
		+ 2.0 * wi * wj * math::dot(math::local2global(dAi, _hi), math::local2global(dAj, _upj))
		- wj * wj * math::dot(hi, upj);
	rhs(i) = Qd1;
	rhs(i + 1) = Qd2;
} 

void translateJoint::lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 /* = 0 */, double mul)
{
	unsigned int ci = ib->ID() * 3;
	unsigned int cj = jb->ID() * 3;
	double thi = q(ci + 2);
	double thj = q(cj + 2);
	transformationMatrix Ai = TM(thi);
	transformationMatrix Aj = TM(thj);
	transformationMatrix dAi = derivateTM(thi);
	transformationMatrix dAj = derivateTM(thj);
	vecd3 _hi = baseMarker.actionAxis;
	vecd3 hi = math::local2global(Ai, _hi);
	vecd3 _upi = baseMarker.s;
	vecd3 _upj = actionMarker.s;
	vecd3 pi(q(ci), q(ci + 1), q(ci + 2));
	vecd3 pj(q(cj), q(cj + 1), q(cj + 2));
	vecd3 rij
		= pi
		+ math::local2global(Ai, baseMarker.s)
		- pj
		- math::local2global(Aj, actionMarker.s);
	ci = ci ? ci - 3 : 0;
	cj = cj ? cj - 3 : 0;
	if (ci)
	{
		lhs(ci, ci + 2) = lhs(ci + 2, ci)
			+= mul * lm1 * (-sin(thi) * _hi.X() - cos(thi) * _hi.Y());
		lhs(ci + 1, ci + 2) = lhs(ci + 2, ci + 1)
			+= mul * lm1 * (cos(thi) * _hi.X() - sin(thi) * _hi.Y());
		lhs(ci + 2, ci + 2)
			+= mul * lm1 * (math::dot(_upi, _hi) - math::dot(rij, hi));
		if (cj)
		{
			lhs(ci + 2, cj + 2)
				+= -mul * lm1 * math::dot(math::local2global(dAj, _upj), math::local2global(dAi, _hi));
		}
	}
	if (cj)
	{
		if (ci)
		{
			lhs(cj, ci + 2) 
				+= -mul * lm1 * (-sin(thi) * _hi.X() - cos(thi) * _hi.Y());
			lhs(cj + 1, ci + 2)
				+= -mul * lm1 * (cos(thi) * _hi.X() - sin(thi) * _hi.Y());
			lhs(cj + 2, ci + 2)
				+= -mul * lm1 * math::dot(math::local2global(dAi, _hi), math::local2global(dAj, _upj));
		}
		lhs(cj + 2, cj + 2)
			+= mul * lm1 * math::dot(hi, math::local2global(Aj, _upj));
	}
}