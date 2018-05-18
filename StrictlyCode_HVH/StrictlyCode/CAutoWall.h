#pragma once

#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"

#include "EntityStructs.h"
#include "OptionsManager.h"

#include "Utilities.h"

#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10

struct FireBulletData
{
	FireBulletData(const NSDK::Vector &eye_pos)
		: src(eye_pos)
	{
	}

	NSDK::Vector           src;
	NSDK::Trace_t          enter_trace;
	NSDK::Vector           direction;
	NSDK::CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};

class CAutowall
{
public:
	static void UTIL_TraceLine(const NSDK::Vector& vecAbsStart, const NSDK::Vector& vecAbsEnd, unsigned int mask, CBaseEntity* ignore, NSDK::Trace_t* ptr);
	static void UTIL_ClipTraceToPlayers(NSDK::Vector& vecAbsStart, NSDK::Vector& vecAbsEnd, unsigned int mask, NSDK::ITraceFilter* filter, NSDK::Trace_t* tr);
	static void ScaleDamage(int hitgroup, CBaseEntity *enemy, float weapon_armor_ratio, float &current_damage);
	static bool TraceToExit1(NSDK::CGameTrace *enterTrace, NSDK::Vector vecStartPosition, NSDK::Vector vecDir, NSDK::CGameTrace *exitTrace);
	static float GetHitgroupDamageMultiplier(int iHitGroup);
	static bool HandleBulletPenetration(NSDK::WeaponInfo_t* weaponInfo, FireBulletData &data);
	static bool SimulateFireBullet(CBaseCombatWeapon* pWeapon, FireBulletData &data);
	static float GetDamage(const NSDK::Vector& point);
	static float GetDamageFreeStand(const NSDK::Vector & point, CBaseEntity * g_player);
	static bool SimulateFireBulletFS(CBaseCombatWeapon* pWeapon, FireBulletData &data, CBaseEntity* entity);
	//2
	static bool CanWallbang(float &dmg);
	static float BestHitPoint(CBaseEntity* pEntity, int prioritized, float minDmg, NSDK::mstudiohitboxset_t* hitset, NSDK::matrix3x4a_t matrix[], NSDK::Vector& vecOut);
	static NSDK::Vector CalculateBestPoint(CBaseEntity* pEntity, int prioritized, float minDmg, bool onlyPrioritized = true);
private:
	static NSDK::Trace_t trace;
	static NSDK::Trace_t trace2;
};