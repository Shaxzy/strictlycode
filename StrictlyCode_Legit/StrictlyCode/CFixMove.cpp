#include "CFixMove.h"

void CFixMove::CorrectMovement(NSDK::QAngle vOldAngles, NSDK::CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
	//side/forward move correction
	float deltaView = pCmd->viewangles.y - vOldAngles.y;
	float f1;
	float f2;

	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;

	if (pCmd->viewangles.y < 0.0f)
		f2 = 360.0f + pCmd->viewangles.y;
	else
		f2 = pCmd->viewangles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);
	deltaView = 360.0f - deltaView;

	pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}

void CFixMove::Start(NSDK::CUserCmd* pCmd) 
{
	old = pCmd->viewangles;
	oldFowardMove = pCmd->forwardmove;
	oldSideMove = pCmd->sidemove;
}

void CFixMove::Stop(NSDK::CUserCmd* pCmd) 
{
	CorrectMovement(old, pCmd, oldFowardMove, oldSideMove);
}

NSDK::QAngle CFixMove::GetOldAngle() {
	return old;
}