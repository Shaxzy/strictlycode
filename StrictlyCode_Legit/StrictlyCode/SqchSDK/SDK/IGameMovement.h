#pragma once

#include "IClientEntity.h"
#include "Vector.h"
#include "QAngle.h"

namespace NSDK {
	typedef CBaseHandle EntityHandle_t;

	class CMoveData
	{
	public:
		bool m_bFirstRunOfFunctions : 1;
		bool m_bGameCodeMovedPlayer : 1;
		int m_nPlayerHandle; // edict index on server, client entity handle on client=
		int m_nImpulseCommand; // Impulse command issued.
		Vector m_vecViewAngles; // Command view angles (local space)
		Vector m_vecAbsViewAngles; // Command view angles (world space)
		int m_nButtons; // Attack buttons.
		int m_nOldButtons; // From host_client->oldbuttons;
		float m_flForwardMove;
		float m_flSideMove;
		float m_flUpMove;
		float m_flMaxSpeed;
		float m_flClientMaxSpeed;
		Vector m_vecVelocity; // edict::velocity // Current movement direction.
		Vector m_vecAngles; // edict::angles
		Vector m_vecOldAngles;
		float m_outStepHeight; // how much you climbed this move
		Vector m_outWishVel; // This is where you tried 
		Vector m_outJumpVel; // This is your jump velocity
		Vector m_vecConstraintCenter;
		float m_flConstraintRadius;
		float m_flConstraintWidth;
		float m_flConstraintSpeedFactor;
		float m_flUnknown[5];
		Vector m_vecAbsOrigin;
	};

	class IGameMovement
	{
	public:
		void ProcessMovement(IClientEntity *pPlayer, CMoveData *pMove) {
			typedef void(__thiscall *OrigFn)(void*, IClientEntity*, CMoveData*);
			CallVFunction<OrigFn>(this, 1)(this, pPlayer, pMove);
		}
		void StartTrackPredictionErrors(IClientEntity *pPlayer) {
			typedef void(__thiscall *OrigFn)(void*, IClientEntity*);
			CallVFunction<OrigFn>(this, 3)(this, pPlayer);
		}
		void FinishTrackPredictionErrors(IClientEntity *pPlayer) {
			typedef void(__thiscall *OrigFn)(void*, IClientEntity*);
			CallVFunction<OrigFn>(this, 4)(this, pPlayer);
		}

		void DecayPunchAngle()
		{
			typedef void(__thiscall* DecayPunchAngle_t)(void*);
			CallVFunction<DecayPunchAngle_t>(this, 76)(this);
		}
	};
}