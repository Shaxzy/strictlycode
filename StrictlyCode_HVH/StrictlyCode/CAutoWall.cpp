#include "CAutoWall.h"
#define	DAMAGE_NO				0
#define DAMAGE_EVENTS_ONLY		1		// Call damage functions, but don't modify health
#define	DAMAGE_YES				2
#define	DAMAGE_AIM				3

enum {
	CHAR_TEX_ANTLION = 'A',
	CHAR_TEX_BLOODYFLESH = 'B',
	CHAR_TEX_CONCRETE = 'C',
	CHAR_TEX_DIRT = 'D',
	CHAR_TEX_EGGSHELL = 'E',
	CHAR_TEX_FLESH = 'F',
	CHAR_TEX_GRATE = 'G',
	CHAR_TEX_ALIENFLESH = 'H',
	CHAR_TEX_CLIP = 'I',
	CHAR_TEX_PLASTIC = 'L',
	CHAR_TEX_METAL = 'M',
	CHAR_TEX_SAND = 'N',
	CHAR_TEX_FOLIAGE = 'O',
	CHAR_TEX_COMPUTER = 'P',
	CHAR_TEX_SLOSH = 'S',
	CHAR_TEX_TILE = 'T',
	CHAR_TEX_CARDBOARD = 'U',
	CHAR_TEX_VENT = 'V',
	CHAR_TEX_WOOD = 'W',
	CHAR_TEX_GLASS = 'Y',
	CHAR_TEX_WARPSHIELD = 'Z',
};

float CAutowall::GetDamageFreeStand(const NSDK::Vector& point, CBaseEntity* g_player)
{
	float damage = 0.f;
	NSDK::Vector dst = point;
	FireBulletData data(g_player->GetEyePos());
	data.filter.pSkip = g_player;

	NSDK::QAngle angles = Utilities::CalcAngle(data.src, dst);
	Utilities::AngleVectors(angles, &data.direction);

	data.direction.NormalizeInPlace();

	CBaseCombatWeapon* activeWeapon = g_player->GetActiveWeapon();

	if (!activeWeapon)
		return 0.f;

	if (SimulateFireBullet(activeWeapon, data))
	{
		damage = data.current_damage;
	}

	return damage;
}

bool CAutowall::SimulateFireBulletFS(CBaseCombatWeapon* pWeapon, FireBulletData &data, CBaseEntity* entity)
{
	CBaseEntity* localplayer = CBaseEntity::GetLocalPlayer();
	NSDK::WeaponInfo_t* weaponInfo = pWeapon->GetCSWpnData();

	data.penetrate_count = 4;
	data.trace_length = 0.0f;
	data.current_damage = (float)weaponInfo->iDamage;

	while (data.penetrate_count > 0 && data.current_damage >= 1.0f)
	{
		data.trace_length_remaining = weaponInfo->flRange - data.trace_length;

		NSDK::Vector end = data.src + data.direction * data.trace_length_remaining;

		// data.enter_trace
		CAutowall::UTIL_TraceLine(data.src, end, MASK_SHOT, entity, &data.enter_trace);
		CAutowall::UTIL_ClipTraceToPlayers(data.src, end * 40.f, MASK_SHOT, &data.filter, &data.enter_trace);

		if (data.enter_trace.fraction == 1.0f)
			break;

		if (data.enter_trace.hitgroup <= HITGROUP_RIGHTLEG && data.enter_trace.hitgroup > HITGROUP_GENERIC)
		{
			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
			data.current_damage *= powf(weaponInfo->flRangeModifier, data.trace_length * 0.002f);

			CBaseEntity* player = (CBaseEntity*)data.enter_trace.m_pEnt;

			//		if (*player->GetTeamNum() == *localplayer->GetTeamNum())
			//			return false;

			CAutowall::ScaleDamage(data.enter_trace.hitgroup, player, weaponInfo->flArmorRatio, data.current_damage);

			return true;
		}

		if (!CAutowall::HandleBulletPenetration(weaponInfo, data))
			break;
	}

	return false;
}

bool IsWorldEntity(NSDK::IClientEntity* m_pEnt)
{
	return m_pEnt != NULL && m_pEnt->EntIndex() == 0;
}

bool isBreakableEntity(NSDK::IClientEntity *pEntity)
{

	if (pEntity == NULL)
		return false;

	if (pEntity->EntIndex() == 0)
		return false;

	static DWORD dwEntBreakable = NULL;

	if (dwEntBreakable == NULL)
	{
		dwEntBreakable = NSDK::O::FindSignature( ("client.dll"),  ("55 8B EC 51 56 8B F1 85 F6 74 68"));
	}
	bool bRet;

	__asm
	{
		MOV ECX, pEntity
		CALL dwEntBreakable
		MOV bRet, AL
	}

	return bRet;
}
inline NSDK::vec_t VectorNormalize(NSDK::Vector& v)
{
	NSDK::vec_t l = v.Length();

	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f; v.z = 1.0f;
	}

	return l;
}

void CAutowall::UTIL_TraceLine(const NSDK::Vector& vecAbsStart, const NSDK::Vector& vecAbsEnd, unsigned int mask, CBaseEntity* ignore, NSDK::Trace_t* ptr)
{
	NSDK::Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	NSDK::CTraceFilter filter;
	filter.pSkip = ignore;

	NSDK::I::EngineTrace()->TraceRay(ray, mask, &filter, ptr);
}


bool CAutowall::CanWallbang(float &dmg)
{
	CBaseEntity *local = CBaseEntity::GetLocalPlayer();
	if (!local)
		return false;
	//local geteyepos
	FireBulletData data(local->GetEyePos());
	data.filter.pSkip = local;

	NSDK::Vector EyeAng;
	NSDK::I::Engine()->GetViewAngles(EyeAng);

	NSDK::Vector dst, forward;

	Utilities::AngleVectors(EyeAng, &forward);
	dst = data.src + (forward * 8196.f);

	NSDK::Vector angles;
	angles = Utilities::CalcAngle(data.src, dst);
	Utilities::AngleVectors(angles, &data.direction);
	VectorNormalize(data.direction);

	CBaseCombatWeapon* weapon = local->GetActiveWeapon();

	if (!weapon)
		return false;

	data.penetrate_count = 1;
	data.trace_length = 0.0f;

	NSDK::WeaponInfo_t *weaponData = weapon->GetCSWpnData();

	if (!weaponData)
		return false;

	data.current_damage = (float)weaponData->iDamage;

	data.trace_length_remaining = weaponData->flRange - data.trace_length;

	NSDK::Vector end = data.src + data.direction * data.trace_length_remaining;

	CAutowall::UTIL_TraceLine(data.src, end, MASK_SHOT | CONTENTS_GRATE, local, &data.enter_trace);

	if (data.enter_trace.fraction == 1.0f)
		return false;

	if (CAutowall::HandleBulletPenetration(weaponData, data))
	{
		dmg = data.current_damage;
		return true;
	}

	return false;
}

float DistanceToRay(const NSDK::Vector &pos, const NSDK::Vector &rayStart, const NSDK::Vector &rayEnd, float *along = NULL, NSDK::Vector *pointOnRay = NULL)
{
	NSDK::Vector to = pos - rayStart;
	NSDK::Vector dir = rayEnd - rayStart;
	float length = dir.NormalizeInPlace();

	float rangeAlong = dir.Dot(to);
	if (along)
	{
		*along = rangeAlong;
	}

	float range;

	if (rangeAlong < 0.0f)
	{
		// off start point
		range = -(pos - rayStart).Length();

		if (pointOnRay)
		{
			*pointOnRay = rayStart;
		}
	}
	else if (rangeAlong > length)
	{
		// off end point
		range = -(pos - rayEnd).Length();

		if (pointOnRay)
		{
			*pointOnRay = rayEnd;
		}
	}
	else // within ray bounds
	{
		NSDK::Vector onRay = rayStart + (dir.operator*(rangeAlong));
		range = (pos - onRay).Length();

		if (pointOnRay)
		{
			*pointOnRay = onRay;
		}
	}

	return range;
}

void TraceLine(NSDK::Vector& vecAbsStart, NSDK::Vector& vecAbsEnd, unsigned int mask, NSDK::IClientEntity* ignore, NSDK::CGameTrace* ptr)
{
	NSDK::Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	NSDK::CTraceFilter filter;
	filter.pSkip = ignore;

	NSDK::I::EngineTrace()->TraceRay(ray, mask, &filter, ptr);
}

void CAutowall::UTIL_ClipTraceToPlayers(NSDK::Vector& vecAbsStart, NSDK::Vector& vecAbsEnd, unsigned int mask, NSDK::ITraceFilter* filter, NSDK::Trace_t* tr)
{
	NSDK::Trace_t playerTrace;
	NSDK::Ray_t ray;
	float smallestFraction = tr->fraction;
	const float maxRange = 60.0f;

	ray.Init(vecAbsStart, vecAbsEnd);

	for (int k = 1; k <= NSDK::I::GlobalVars()->maxClients; ++k)
	{
		CBaseEntity *player = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(k);

		if (!player || !player->IsAlive())
			continue;

		if (player->IsDormant())
			continue;


		if (filter && filter->ShouldHitEntity((NSDK::IHandleEntity*)player, mask) == false)
			continue;

		float range = DistanceToRay(player->WorldSpaceCenter(), vecAbsStart, vecAbsEnd);
		if (range < 0.0f || range > maxRange)
			continue;

		NSDK::I::EngineTrace()->ClipRayToEntity(ray, mask | CONTENTS_HITBOX, (NSDK::IHandleEntity*)player, &playerTrace);
		if (playerTrace.fraction < smallestFraction)
		{
			// we shortened the ray - save off the trace
			*tr = playerTrace;
			smallestFraction = playerTrace.fraction;
		}
	}

}

float inline CAutowall::GetHitgroupDamageMultiplier(int iHitGroup)
{
	switch (iHitGroup)
	{
	case HITGROUP_HEAD:
	{
		return 4.0f;
	}
	case HITGROUP_STOMACH:
	{
		return 1.25f;
	}
	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
	{
		return 0.75f;
	}
	}
	return 1.0f;
}

void CAutowall::ScaleDamage(int hitgroup, CBaseEntity *enemy, float weapon_armor_ratio, float &current_damage)
{
	current_damage *= CAutowall::GetHitgroupDamageMultiplier(hitgroup);
	float m_flArmor = (float)enemy->GetArmor();
	if (m_flArmor > 0.0f && hitgroup < HITGROUP_LEFTLEG)  //don't do gear, or legs
	{
		if (hitgroup == HITGROUP_HEAD && !enemy->HasHelmet())
			return;

		float armorscaled = (weapon_armor_ratio * 0.5f) * current_damage;
		if ((current_damage - armorscaled) * 0.5f > m_flArmor)
			armorscaled = current_damage - (m_flArmor * 2.0f);
		current_damage = armorscaled;
	}
}



bool CAutowall::TraceToExit1(NSDK::CGameTrace *enterTrace, NSDK::Vector vecStartPosition, NSDK::Vector vecDir, NSDK::CGameTrace *exitTrace)
{
	NSDK::Vector vecEnd;
	float flDistance = 0.f;
	signed int iDistanceCheck = 23;
	int iFirstContents = 0;

	do // We want to call the code once before checking for distance
	{
		flDistance += 4.f;
		vecEnd = vecStartPosition + vecDir * flDistance;

		if (!iFirstContents)
			iFirstContents = NSDK::I::EngineTrace()->GetPointContents(vecEnd, MASK_SHOT | CONTENTS_GRATE, NULL); /*0x4600400B*/
		int iPointContents = NSDK::I::EngineTrace()->GetPointContents(vecEnd, MASK_SHOT | CONTENTS_GRATE, NULL);

		if (!(iPointContents & (MASK_SHOT_HULL | CONTENTS_HITBOX)) || iPointContents & CONTENTS_HITBOX && iPointContents != iFirstContents) /*0x600400B, *0x40000000*/
		{
			NSDK::Vector vecNewEnd = vecEnd - (vecDir * 4.f);

			NSDK::Ray_t ray;
			ray.Init(vecEnd, vecNewEnd);

			NSDK::I::EngineTrace()->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, nullptr, exitTrace);

			if (exitTrace->startsolid && exitTrace->surface.flags & SURF_HITBOX) //A Hitbox is infront of the enemy and the enemy is behind a solid wall
			{
				TraceLine(vecEnd, vecStartPosition, MASK_SHOT_HULL | CONTENTS_HITBOX, exitTrace->m_pEnt, exitTrace);

				if ((exitTrace->fraction < 1.f || exitTrace->allsolid) && !exitTrace->startsolid) //DidHit() && !startsolid
					return true;
				continue;
			}

			if ((exitTrace->fraction < 1.f || exitTrace->allsolid) && !exitTrace->startsolid)
			{
				if (enterTrace->surface.flags & SURF_NODRAW || !(exitTrace->surface.flags & SURF_NODRAW))
				{
					if (exitTrace->plane.normal.Dot(vecDir) <= 1.f)
						return true;
					continue;
				}

				//For some reason, Skeet's pesudo claims this is || but if you use ||, you will spam windowsils. I would have to look into this.
				if (isBreakableEntity(enterTrace->m_pEnt) && isBreakableEntity(exitTrace->m_pEnt))
					return true;
				continue;
			}

			if (exitTrace->surface.flags & SURF_NODRAW)
			{
				if (isBreakableEntity(enterTrace->m_pEnt) && isBreakableEntity(exitTrace->m_pEnt))
					return true;
				else if (!(enterTrace->surface.flags & SURF_NODRAW))
					continue;
			}

			if (IsWorldEntity(enterTrace->m_pEnt) && (isBreakableEntity(enterTrace->m_pEnt)))
			{
				exitTrace = enterTrace;
				exitTrace->endpos = vecStartPosition + vecDir;
				return true;
			}
			continue;
		}
		--iDistanceCheck;
	} while (iDistanceCheck); //Distance check

	return false;
}

bool CAutowall::HandleBulletPenetration(NSDK::WeaponInfo_t *wpn_data, FireBulletData &data)
{
	NSDK::CGameTrace trace_exit;
	NSDK::surfacedata_t *enterSurfaceData = NSDK::I::PhysicsProps()->GetSurfaceData(data.enter_trace.surface.surfaceProps);
	int iEnterMaterial = enterSurfaceData->game.material;

	float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;
	float flFinalDamageModifier = 0.16f;
	float flCombinedPenetrationModifier = 0.f;
	bool isSolidSurf = ((data.enter_trace.contents >> 3) & CONTENTS_SOLID);
	bool isLightSurf = ((data.enter_trace.surface.flags >> 7) & SURF_LIGHT);

	if (data.penetrate_count <= 0
		|| (!data.penetrate_count && !isLightSurf && !isSolidSurf && iEnterMaterial != CHAR_TEX_GLASS && iEnterMaterial != CHAR_TEX_GRATE)
		|| wpn_data->flPenetration <= 0.f
		|| !TraceToExit1(&data.enter_trace, data.enter_trace.endpos, data.direction, &trace_exit)
		&& !(NSDK::I::EngineTrace()->GetPointContents(data.enter_trace.endpos, MASK_SHOT_HULL | CONTENTS_HITBOX, NULL) & (MASK_SHOT_HULL | CONTENTS_HITBOX)))
		return false;

	NSDK::surfacedata_t *exitSurfaceData = NSDK::I::PhysicsProps()->GetSurfaceData(trace_exit.surface.surfaceProps);
	int iExitMaterial = exitSurfaceData->game.material;
	float exitSurfPenetrationModifier = exitSurfaceData->game.flPenetrationModifier;

	if (iEnterMaterial == CHAR_TEX_GLASS || iEnterMaterial == CHAR_TEX_GRATE)
	{
		flCombinedPenetrationModifier = 3.f;
		flFinalDamageModifier = 0.05f;
	}

	else if (isLightSurf || isSolidSurf)
	{
		flCombinedPenetrationModifier = 1.f;
		flFinalDamageModifier = 0.16f;
	}
	else
	{
		flCombinedPenetrationModifier = (enterSurfPenetrationModifier + exitSurfPenetrationModifier) * 0.5f;
		flFinalDamageModifier = 0.16f;
	}

	if (iEnterMaterial == iExitMaterial)
	{
		if (iExitMaterial == CHAR_TEX_CARDBOARD || iExitMaterial == CHAR_TEX_WOOD)
			flCombinedPenetrationModifier = 3.f;
		else if (iExitMaterial == CHAR_TEX_PLASTIC)
			flCombinedPenetrationModifier = 2.0f;
	}

	float flThickness = (trace_exit.endpos - data.enter_trace.endpos).LengthSqr();
	float flModifier = fmaxf(0.f, 1.f / flCombinedPenetrationModifier);

	float flLostDamage = fmaxf(
		((flModifier * flThickness) / 24.f) //* 0.041666668
		+ ((data.current_damage * flFinalDamageModifier)
			+ (fmaxf(3.75 / wpn_data->flPenetration, 0.f) * 3.f * flModifier)), 0.f);

	if (flLostDamage > data.current_damage)
		return false;

	if (flLostDamage > 0.f)
		data.current_damage -= flLostDamage;

	if (data.current_damage < 1.f)
		return false;

	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}

bool CAutowall::SimulateFireBullet(CBaseCombatWeapon* pWeapon, FireBulletData &data)
{
	CBaseEntity* localplayer = CBaseEntity::GetLocalPlayer();
	NSDK::WeaponInfo_t* weaponInfo = pWeapon->GetCSWpnData();

	data.penetrate_count = 4;
	data.trace_length = 0.0f;
	data.current_damage = (float)weaponInfo->iDamage;

	while (data.penetrate_count > 0 && data.current_damage >= 1.0f)
	{
		data.trace_length_remaining = weaponInfo->flRange - data.trace_length;

		NSDK::Vector end = data.src + data.direction * data.trace_length_remaining;

		// data.enter_trace
		UTIL_TraceLine(data.src, end, MASK_SHOT, localplayer, &data.enter_trace);
		UTIL_ClipTraceToPlayers(data.src, end * 40.f, MASK_SHOT, &data.filter, &data.enter_trace);

		if (data.enter_trace.fraction == 1.0f)
			break;

		if (data.enter_trace.hitgroup <= HITGROUP_RIGHTLEG && data.enter_trace.hitgroup > HITGROUP_GENERIC)
		{
			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
			data.current_damage *= powf(weaponInfo->flRangeModifier, data.trace_length * 0.002f);

			CBaseEntity* player = (CBaseEntity*)data.enter_trace.m_pEnt;

			if (*player->GetTeamNum() == *localplayer->GetTeamNum())
				return false;

			ScaleDamage(data.enter_trace.hitgroup, player, weaponInfo->flArmorRatio, data.current_damage);

			return true;
		}

		if (!HandleBulletPenetration(weaponInfo, data))
			break;
	}

	return false;
}

float CAutowall::GetDamage(const NSDK::Vector& point)
{
	float damage = 0.f;
	NSDK::Vector dst = point;
	CBaseEntity* localplayer = CBaseEntity::GetLocalPlayer();
	FireBulletData data(localplayer->GetEyePos());
	data.filter.pSkip = localplayer;

	NSDK::QAngle angles = Utilities::CalcAngle(data.src, dst);
	Utilities::AngleVectors(angles, &data.direction);

	data.direction.NormalizeInPlace();

	CBaseCombatWeapon* activeWeapon = localplayer->GetActiveWeapon();

	if (!activeWeapon)
		return 0.f;

	if (SimulateFireBullet(activeWeapon, data))
	{
		damage = data.current_damage;
	}

	return damage;
}

NSDK::Trace_t CAutowall::trace;
NSDK::Trace_t CAutowall::trace2;

float CAutowall::BestHitPoint(CBaseEntity* pEntity, int iPrioritized, float flMinDmg, NSDK::mstudiohitboxset_t* hitset, NSDK::matrix3x4a_t matrix[], NSDK::Vector& vecOut) {
	NSDK::mstudiobbox_t *hitbox = hitset->pHitbox(iPrioritized);

	if (!hitbox)
		return 0.f;

	NSDK::Vector vecArray[5];
	float flHigherDamage = 0.f;

	NSDK::Vector max;
	NSDK::Vector min;
	Utilities::VectorTransform(hitbox->bbmax, matrix[hitbox->bone], max);
	Utilities::VectorTransform(hitbox->bbmin, matrix[hitbox->bone], min);

	auto center = (min + max) * 0.5f;

	NSDK::QAngle CurrentAngles = Utilities::CalcAngle(center, CBaseEntity::GetLocalPlayer()->GetEyePos());

	NSDK::Vector Forward;
	Utilities::AngleVectors(CurrentAngles, &Forward);

	NSDK::Vector Right = Forward.Cross(NSDK::Vector(0, 0, 1));
	NSDK::Vector Left = NSDK::Vector(-Right.x, -Right.y, Right.z);

	NSDK::Vector Top = NSDK::Vector(0, 0, 1);
	NSDK::Vector Bot = NSDK::Vector(0, 0, -1);

	//pSetts
	//Head : 0.8 -> Non. C'est 0.783
	//Arms : 0.7 
	const static auto point_scale = .8;
	NSDK::Vector RightPoint = Right * (hitbox->m_flRadius * (point_scale)) + center;
	NSDK::Vector LeftPoint = Left * (hitbox->m_flRadius * (point_scale)) + center;
	NSDK::Vector TopPoint = Top * (hitbox->m_flRadius * (point_scale)) + center;
	NSDK::Vector BotPoint = Bot * (hitbox->m_flRadius * (point_scale)) + center;

	switch (iPrioritized)
	{
	case NSDK::HitboxEnum_t::HITBOX_HEAD:
		vecArray[0] = TopPoint;
		vecArray[1] = RightPoint;
		vecArray[2] = LeftPoint;
		vecArray[3] = BotPoint;
		break;
	case NSDK::HitboxEnum_t::HITBOX_NECK:
		vecArray[0] = TopPoint;
		vecArray[1] = RightPoint;
		vecArray[2] = LeftPoint;
		vecArray[3] = BotPoint;
		break;
	case NSDK::HitboxEnum_t::HITBOX_LOWER_NECK:
		vecArray[0] = TopPoint;
		vecArray[1] = RightPoint;
		vecArray[2] = LeftPoint;
		vecArray[3] = BotPoint;
		break;
	case NSDK::HitboxEnum_t::HITBOX_PELVIS:
		vecArray[0] = TopPoint;
		vecArray[1] = RightPoint;
		vecArray[2] = LeftPoint;
		vecArray[3] = BotPoint;
		break;
	default:
		vecArray[0] = TopPoint;
		vecArray[1] = RightPoint;
		vecArray[2] = LeftPoint;
		break;
	}

	for (NSDK::Vector cur : vecArray) {
		if (!cur.IsValid())
			continue;

		float flCurDamage = GetDamage(cur);

		if (!flCurDamage)
			continue;

		if (!(flCurDamage > 0.f))
			continue;

		if ((flCurDamage > flHigherDamage) && (flCurDamage > flMinDmg)) {
			flHigherDamage = flCurDamage;
			vecOut = cur;
		}
	}
	return flHigherDamage;
}

NSDK::Vector CAutowall::CalculateBestPoint(CBaseEntity* pEntity, int prioritized, float minDmg, bool onlyPrioritized) 
{
	NSDK::matrix3x4a_t matrix[128];

	if (!pEntity->SetupBones(matrix, 128, 256, NSDK::I::Engine()->GetLastTimeStamp()))
		return false;

	NSDK::studiohdr_t* hdr = NSDK::I::ModelInfo()->GetStudiomodel(pEntity->GetModel());
	NSDK::mstudiohitboxset_t* set = hdr->pHitboxSet(0);
	NSDK::Vector best_vec;

	float real_min_dmg = minDmg >= 100 ? pEntity->GetHealth() : minDmg;

	if (BestHitPoint(pEntity, prioritized, real_min_dmg, set, matrix, best_vec) >= real_min_dmg && onlyPrioritized)
	{
		return best_vec;
	}
	else
	{
		float fl_highest_vec_dmg = 0.f;
		NSDK::Vector vecCurVec;

		static int hitboxesLoop[] = {
			NSDK::HitboxEnum_t::HITBOX_HEAD,
			NSDK::HitboxEnum_t::HITBOX_NECK,
			NSDK::HitboxEnum_t::HITBOX_LOWER_NECK,
			NSDK::HitboxEnum_t::HITBOX_PELVIS,
			NSDK::HitboxEnum_t::HITBOX_STOMACH,
			NSDK::HitboxEnum_t::HITBOX_UPPER_STOMACH,
			NSDK::HitboxEnum_t::HITBOX_CHEST,
			NSDK::HitboxEnum_t::HITBOX_UPPER_CHEST,
			NSDK::HitboxEnum_t::HITBOX_LEFT_THIGH,
			NSDK::HitboxEnum_t::HITBOX_RIGHT_THIGH,
			NSDK::HitboxEnum_t::HITBOX_LEFT_SHIN,
			NSDK::HitboxEnum_t::HITBOX_RIGHT_SHIN,
			NSDK::HitboxEnum_t::HITBOX_LEFT_FOOT,
			NSDK::HitboxEnum_t::HITBOX_RIGHT_FOOT,
			NSDK::HitboxEnum_t::HITBOX_LEFT_HAND,
			NSDK::HitboxEnum_t::HITBOX_RIGHT_HAND,
			NSDK::HitboxEnum_t::HITBOX_LEFT_UPPER_ARM,
			NSDK::HitboxEnum_t::HITBOX_LEFT_FOREARM,
			NSDK::HitboxEnum_t::HITBOX_RIGHT_UPPER_ARM,
			NSDK::HitboxEnum_t::HITBOX_RIGHT_FOREARM
		};

		int loopSize = ARRAYSIZE(hitboxesLoop);

		bool bVisPart = false;

		for (int i = 0; i < loopSize; ++i) 
		{
			if (!Options.HitscanBoxes[i])
				continue;

			float fl_cur_vec_dmg = BestHitPoint(pEntity, hitboxesLoop[i], real_min_dmg, set, matrix, vecCurVec);

			if (!fl_cur_vec_dmg)
				continue;

			bool shouldHitscan = Options.bHitscan;

			if (shouldHitscan) 
			{
				if (pEntity->isVectorVisible(vecCurVec)) 
				{
					bVisPart = true;
					if (fl_cur_vec_dmg > fl_highest_vec_dmg)
					{
						fl_highest_vec_dmg = fl_cur_vec_dmg;
						best_vec = vecCurVec;
					}
					continue;
				}
			}

			if (!bVisPart && fl_cur_vec_dmg > fl_highest_vec_dmg)
			{
				fl_highest_vec_dmg = fl_cur_vec_dmg;
				best_vec = vecCurVec;
			}
		}
		return best_vec;
	}
}