#pragma once

#include "Utilities.h"
#include "SqchSDK\Interfaces.h"

class CFixMove 
{
public:
	void Start(NSDK::CUserCmd*);
	void Stop(NSDK::CUserCmd*);
	NSDK::QAngle GetOldAngle();
private:
	NSDK::QAngle old;
	float oldFowardMove;
	float oldSideMove;

	void CorrectMovement(NSDK::QAngle vOldAngles, NSDK::CUserCmd* pCmd, float fOldForward, float fOldSidemove);
};