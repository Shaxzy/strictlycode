#pragma once

#include "SqchSDK\Offsets.h"
#include "NetvarManager.h"
#include <array>

class CBaseAttributableItem;
class CBaseCSGrenade;
class CBaseEntity;

class CBaseCombatWeapon : public NSDK::IClientEntity {
	template<class T>
	T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	int* FallbackPaintKit()
	{
		static int m_nFallbackPaintKit = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_nFallbackPaintKit"));
		return GetFieldPointer<int>(m_nFallbackPaintKit);
	}
	int* FallbackSeed()
	{
		static int m_nFallbackSeed = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_nFallbackSeed"));
		return GetFieldPointer<int>(m_nFallbackSeed);
	}
	float* FallbackWear()
	{
		static int m_flFallbackWear = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_flFallbackWear"));
		return GetFieldPointer<float>(m_flFallbackWear);
	}

	int* FallbackStatTrak()
	{
		static int m_nFallbackStatTrak = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_nFallbackStatTrak"));
		return GetFieldPointer<int>(m_nFallbackStatTrak);
	}
	int* EntityQuality()
	{
		static int m_iEntityQuality = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iEntityQuality"));
		return GetFieldPointer<int>(m_iEntityQuality);
	}
	int* EntityLevel()
	{
		static int m_iEntityLevel = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iEntityLevel"));
		return GetFieldPointer<int>(m_iEntityLevel);
	}
	int* ItemIDHigh()
	{
		static int m_iItemIDHigh = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iItemIDHigh"));
		return GetFieldPointer<int>(m_iItemIDHigh);
	}
	int* ItemIDLow()
	{
		static int m_iItemIDLow = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iItemIDLow"));
		return GetFieldPointer<int>(m_iItemIDLow);
	}
	int* AccountID()
	{
		static int m_iAccountID = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iAccountID"));
		return GetFieldPointer<int>(m_iAccountID);
	}
	char* CustomName() {
		static int m_szCustomName = NetvarManager::Instance()->GetOffset( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_szCustomName"));
		return GetFieldPointer<char>(m_szCustomName);
	}
	int* GetAmmoClip() {
		static int GetAmmoClip = GET_NETVAR( ("DT_BaseCombatWeapon"),  ("m_iClip1"));
		return GetFieldPointer<int>(GetAmmoClip);
	}
	int* GetAmmoReserve() {
		static int GetAmmoReserve = GET_NETVAR( ("DT_BaseCombatWeapon"),  ("m_iPrimaryReserveAmmoCount"));
		return GetFieldPointer<int>(GetAmmoReserve);
	}

	int *GetModelIndex()
	{
		static int m_nModelIndex = GET_NETVAR( ("DT_BaseViewModel"),  ("m_nModelIndex"));
		return GetFieldPointer<int>(m_nModelIndex);
	}

	int *GetWorldModelIndex()
	{
		static int WorldModelIndex = GET_NETVAR( ("DT_BaseCombatWeapon"),  ("m_iWorldModelIndex"));
		return GetFieldPointer<int>(WorldModelIndex);
	}

	int *GetViewModelIndex()
	{
		static int ViewModelIndex = GET_NETVAR( ("DT_BaseCombatWeapon"),  ("m_iViewModelIndex"));
		return GetFieldPointer<int>(ViewModelIndex);
	}

	float NextPrimaryAttack() {
		static int m_flNextPrimaryAttack = GET_NETVAR( ("DT_BaseCombatWeapon"),  ("LocalActiveWeaponData"),  ("m_flNextPrimaryAttack"));
		return GetFieldValue<float>(m_flNextPrimaryAttack);
	}
	float GetAccuracy() {
		static int m_fAccuracyPenalty = GET_NETVAR( ("DT_WeaponCSBase"),  ("m_fAccuracyPenalty"));
		return GetFieldValue<float>(m_fAccuracyPenalty);
	}
	int GetState() {
		static int m_iState = GET_NETVAR( ("DT_BaseCombatWeapon"),  ("m_iState"));
		return GetFieldValue<int>(m_iState);
	}
	int* GetItemDefinitionIndex() {
		static int m_iItemDefinitionIndex = GET_NETVAR( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iItemDefinitionIndex"));
		return GetFieldPointer<int>(m_iItemDefinitionIndex);
	}
	float PostponeFireReady()
	{
		static int offset = GET_NETVAR( ("DT_WeaponCSBase"),  ("m_flPostponeFireReadyTime"));
		return GetFieldValue<float>(offset);
	}
	const char* GetName() {
		typedef const char* (__thiscall* tGetName)(void*);
		return NSDK::CallVFunction<tGetName>(this, 378)(this);
	}
	int GetId() {
		typedef int(__thiscall* tGetId)(void*);
		return NSDK::CallVFunction<tGetId>(this, 458)(this);
	}
	float GetCone() {
		typedef float(__thiscall* OriginFN)(void*);
		return NSDK::CallVFunction<OriginFN>(this, 470)(this);
	}
	float GetSpread() {
		typedef float(__thiscall* OriginFN)(void*);
		return NSDK::CallVFunction<OriginFN>(this, 439)(this);
	}
	void UpdateAccuracy() {
		typedef void(__thiscall* OriginFN)(void*);
		NSDK::CallVFunction<OriginFN>(this, 471)(this);
	}
	CBaseEntity* GetOwner()
	{
		static int m_hOwnerEntity = GET_NETVAR( ("DT_BaseEntity"),  ("m_hOwnerEntity"));
		return (CBaseEntity*)NSDK::I::EntityList()->GetClientEntityFromHandle(m_hOwnerEntity);
	}
	NSDK::WeaponInfo_t* GetCSWpnData()
	{
		typedef NSDK::WeaponInfo_t*(__thiscall* OriginalFn)(void*);
		return NSDK::CallVFunction<OriginalFn>(this, 447)(this);
	}

	bool isGrenade() 
	{
		return this->GetCSWpnData()->iWeaponType == NSDK::CSWeaponType::WEAPONTYPE_GRENADE || *this->GetItemDefinitionIndex() == NSDK::weapon_hegrenade || *this->GetItemDefinitionIndex() == NSDK::weapon_incgrenade || *this->GetItemDefinitionIndex() == NSDK::weapon_smokegrenade;
	}

	CBaseCSGrenade *getGrenade() {
		return (CBaseCSGrenade*)this;
	}
	int GetMaxClip1() {
		typedef int(__thiscall* OriginalFn)(void*);
		return NSDK::CallVFunction<OriginalFn>(this, 367)(this);
	}
	int GetCurrentAmmo() {
		static int m_iClip1 = GET_NETVAR( ("DT_BaseCombatWeapon"),  ("m_iClip1"));
		return GetFieldValue<int>(m_iClip1);
	}
	bool IsReloading() 
	{
		static int m_bReloadVisuallyComplete = GET_NETVAR( ("DT_WeaponCSBase"),  ("m_bReloadVisuallyComplete"));
		return !GetFieldValue<bool>(m_bReloadVisuallyComplete);
	}

	bool IsReloadingLocal() 
	{
		return GetFieldValue<bool>(0x3235);
	}

	bool CanShoot()
	{
		if (this->IsReloading()) return false;
		if (this->GetAmmoClip() == 0) return false;
		return true;
	}

	bool isWeaponScope()
	{
		int id = *this->GetItemDefinitionIndex();

		switch (id)
		{
		case NSDK::EItemDefinitionIndex::weapon_aug:
		case NSDK::EItemDefinitionIndex::weapon_awp:
		case NSDK::EItemDefinitionIndex::weapon_g3sg1:
		case NSDK::EItemDefinitionIndex::weapon_sg556:
		case NSDK::EItemDefinitionIndex::weapon_ssg08:
		case NSDK::EItemDefinitionIndex::weapon_scar20:
			return true;
		default:
			return false;
		}
	}

	bool isValidWeapon()
	{
		int id = *this->GetItemDefinitionIndex();

		switch (id)
		{
		case NSDK::EItemDefinitionIndex::weapon_deagle:
		case NSDK::EItemDefinitionIndex::weapon_elite:
		case NSDK::EItemDefinitionIndex::weapon_fiveseven:
		case NSDK::EItemDefinitionIndex::weapon_glock:
		case NSDK::EItemDefinitionIndex::weapon_ak47:
		case NSDK::EItemDefinitionIndex::weapon_aug:
		case NSDK::EItemDefinitionIndex::weapon_awp:
		case NSDK::EItemDefinitionIndex::weapon_famas:
		case NSDK::EItemDefinitionIndex::weapon_g3sg1:
		case NSDK::EItemDefinitionIndex::weapon_galilar:
		case NSDK::EItemDefinitionIndex::weapon_m249:
		case NSDK::EItemDefinitionIndex::weapon_m4a4:
		case NSDK::EItemDefinitionIndex::weapon_mac10:
		case NSDK::EItemDefinitionIndex::weapon_p90:
		case NSDK::EItemDefinitionIndex::weapon_ump:
		case NSDK::EItemDefinitionIndex::weapon_xm1014:
		case NSDK::EItemDefinitionIndex::weapon_bizon:
		case NSDK::EItemDefinitionIndex::weapon_mag7:
		case NSDK::EItemDefinitionIndex::weapon_negev:
		case NSDK::EItemDefinitionIndex::weapon_sawedoff:
		case NSDK::EItemDefinitionIndex::weapon_tec9:
			return true;
		case NSDK::EItemDefinitionIndex::weapon_taser:
			return false;
		case NSDK::EItemDefinitionIndex::weapon_hkp2000:
		case NSDK::EItemDefinitionIndex::weapon_mp7:
		case NSDK::EItemDefinitionIndex::weapon_mp9:
		case NSDK::EItemDefinitionIndex::weapon_nova:
		case NSDK::EItemDefinitionIndex::weapon_p250:
		case NSDK::EItemDefinitionIndex::weapon_scar20:
		case NSDK::EItemDefinitionIndex::weapon_sg556:
		case NSDK::EItemDefinitionIndex::weapon_ssg08:
			return true;
		case NSDK::EItemDefinitionIndex::weapon_knife:
		case NSDK::EItemDefinitionIndex::weapon_flashbang:
		case NSDK::EItemDefinitionIndex::weapon_hegrenade:
		case NSDK::EItemDefinitionIndex::weapon_smokegrenade:
		case NSDK::EItemDefinitionIndex::weapon_molotov:
		case NSDK::EItemDefinitionIndex::weapon_decoy:
		case NSDK::EItemDefinitionIndex::weapon_incgrenade:
		case NSDK::EItemDefinitionIndex::weapon_c4:
		case NSDK::EItemDefinitionIndex::weapon_knife_t:
			return false;
		case NSDK::EItemDefinitionIndex::weapon_m4a1_silencer:
		case NSDK::EItemDefinitionIndex::weapon_usp_silencer:
		case NSDK::EItemDefinitionIndex::weapon_cz75a:
		case NSDK::EItemDefinitionIndex::weapon_revolver:
			return true;
		default:
			return false;
		}
	}

	bool isPistol()
	{
		int id = *this->GetItemDefinitionIndex();

		switch (id)
		{
		case NSDK::EItemDefinitionIndex::weapon_deagle:
		case NSDK::EItemDefinitionIndex::weapon_elite:
		case NSDK::EItemDefinitionIndex::weapon_fiveseven:
		case NSDK::EItemDefinitionIndex::weapon_glock:
			return true;
		case NSDK::EItemDefinitionIndex::weapon_ak47:
		case NSDK::EItemDefinitionIndex::weapon_aug:
		case NSDK::EItemDefinitionIndex::weapon_awp:
		case NSDK::EItemDefinitionIndex::weapon_famas:
		case NSDK::EItemDefinitionIndex::weapon_g3sg1:
		case NSDK::EItemDefinitionIndex::weapon_galilar:
		case NSDK::EItemDefinitionIndex::weapon_m249:
		case NSDK::EItemDefinitionIndex::weapon_m4a4:
		case NSDK::EItemDefinitionIndex::weapon_mac10:
		case NSDK::EItemDefinitionIndex::weapon_p90:
		case NSDK::EItemDefinitionIndex::weapon_ump:
		case NSDK::EItemDefinitionIndex::weapon_xm1014:
		case NSDK::EItemDefinitionIndex::weapon_bizon:
		case NSDK::EItemDefinitionIndex::weapon_mag7:
		case NSDK::EItemDefinitionIndex::weapon_negev:
		case NSDK::EItemDefinitionIndex::weapon_sawedoff:
			return false;
		case NSDK::EItemDefinitionIndex::weapon_tec9:
		case NSDK::EItemDefinitionIndex::weapon_taser:
		case NSDK::EItemDefinitionIndex::weapon_hkp2000:
			return true;
		case NSDK::EItemDefinitionIndex::weapon_mp7:
		case NSDK::EItemDefinitionIndex::weapon_mp9:
		case NSDK::EItemDefinitionIndex::weapon_nova:
			return false;
		case NSDK::EItemDefinitionIndex::weapon_p250:
			return true;
		case NSDK::EItemDefinitionIndex::weapon_scar20:
		case NSDK::EItemDefinitionIndex::weapon_sg556:
		case NSDK::EItemDefinitionIndex::weapon_ssg08:
		case NSDK::EItemDefinitionIndex::weapon_knife:
		case NSDK::EItemDefinitionIndex::weapon_flashbang:
		case NSDK::EItemDefinitionIndex::weapon_hegrenade:
		case NSDK::EItemDefinitionIndex::weapon_smokegrenade:
		case NSDK::EItemDefinitionIndex::weapon_molotov:
		case NSDK::EItemDefinitionIndex::weapon_decoy:
		case NSDK::EItemDefinitionIndex::weapon_incgrenade:
		case NSDK::EItemDefinitionIndex::weapon_c4:
		case NSDK::EItemDefinitionIndex::weapon_knife_t:
		case NSDK::EItemDefinitionIndex::weapon_m4a1_silencer:
			return false;
		case NSDK::EItemDefinitionIndex::weapon_usp_silencer:
			return true;
		case NSDK::EItemDefinitionIndex::weapon_cz75a:
			return true;
		case NSDK::EItemDefinitionIndex::weapon_revolver:
			return false;
		default:
			return false;
		}
	}


};

class CBaseViewModel {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	int *GetViewModelIndex() {
		static int m_iViewModelIndex = GET_NETVAR( ("DT_BaseViewModel"),  ("m_nViewModelIndex"));
		return GetFieldPointer<int>(m_iViewModelIndex);
	}

	int *GetModelIndex() {
		static int m_nModelIndex = GET_NETVAR( ("DT_BaseViewModel"),  ("m_nModelIndex"));
		return GetFieldPointer<int>(m_nModelIndex);
	}

	DWORD GetWeapon() {
		static DWORD m_hWeapon = GET_NETVAR( ("DT_BaseViewModel"),  ("m_hWeapon"));
		return GetFieldValue<DWORD>(m_hWeapon);
	}

	void SetWeaponModel(const char* Filename, CBaseAttributableItem* Weapon) {
		return NSDK::CallVFunction<void(__thiscall*)(void*, const char*, CBaseAttributableItem*)>(this, 242)(this, Filename, Weapon);
	}
};

class CBaseEntity : public NSDK::IClientEntity {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	static CBaseEntity* GetLocalPlayer() 
	{
		return (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(NSDK::I::Engine()->GetLocalPlayer());
	}

	bool SetupBones(NSDK::matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) {
		//Invalidate cache PVSFIX
		//static uintptr_t m_nWritableBones = GET_NETVAR( ("DT_BaseAnimating"),  ("m_nForceBone")) + 0x20;
		//static uintptr_t m_dwOcclusionArray = *(uintptr_t*)(NSDK::O::FindSignature( ("client.dll"),  ("A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8")) + 0x1);
		//static uintptr_t m_bDidCheckForOcclusion = *(uintptr_t*)(NSDK::O::FindSignature( ("client.dll"),  ("A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8")) + 0xE);
		//static uintptr_t InvalidateBoneCache = NSDK::O::FindSignature( ("client.dll"),  ("80 3D ? ? ? ? 00 74 16 A1"));
		//*(int*)((uintptr_t)this + m_nWritableBones) = 0;
		//*(int*)((uintptr_t)this + m_bDidCheckForOcclusion) = reinterpret_cast<int*>(m_dwOcclusionArray)[1];
		//reinterpret_cast<void(__fastcall*)(void*)>(InvalidateBoneCache)(pEntity);

		__asm
		{
			mov edi, this
			lea ecx, DWORD ptr ds : [edi + 0x4]
			mov edx, DWORD ptr ds : [ecx]
			push currentTime
			push boneMask
			push nMaxBones
			push pBoneToWorldOut
			call DWORD ptr ds : [edx + 0x34]
		}
	}

	void SetAngle(NSDK::Vector wantedang)
	{
		typedef void(__thiscall* SetAngleFn)(void*, const NSDK::Vector &);
		static SetAngleFn SetAngle = (SetAngleFn)(NSDK::O::FindSignature(("client.dll"), ("55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1")));
		SetAngle(this, wantedang);
	}

	void SetAbsOrigin(const NSDK::Vector &origin)
	{
		using SetAbsOriginFn = void(__thiscall*)(void*, const NSDK::Vector &origin);
		static SetAbsOriginFn SetAbsOrigin = (SetAbsOriginFn)NSDK::O::FindSignature( ("client.dll"), "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
		SetAbsOrigin(this, origin);
	}

	CBaseCombatWeapon* GetActiveWeapon() {
		static int m_hActiveWeapon = GET_NETVAR( ("DT_BaseCombatCharacter"),  ("m_hActiveWeapon"));
		return (CBaseCombatWeapon*)NSDK::I::EntityList()->GetClientEntityFromHandle(GetFieldValue<NSDK::CBaseHandle>(m_hActiveWeapon));
	}

	int *GetModelIndex() {
		static int m_nModelIndex = GET_NETVAR( ("DT_BaseEntity"),  ("m_nModelIndex"));
		return GetFieldPointer<int>(m_nModelIndex);
	}

	int GetShotFired() {
		static int m_iShotsFired = GET_NETVAR( ("DT_CSPlayer"),  ("cslocaldata"),  ("m_iShotsFired"));
		return GetFieldValue<int>(m_iShotsFired);
	}

	NSDK::QAngle *GetEyeAngles() {
		static int m_angEyeAngles = GET_NETVAR( ("DT_CSPlayer"),  ("m_angEyeAngles[0]"));
		return GetFieldPointer<NSDK::QAngle>(m_angEyeAngles);
	}
	int GetHealth() {
		static int m_iHealth = GET_NETVAR( ("DT_BasePlayer"),  ("m_iHealth"));
		return GetFieldValue<int>(m_iHealth);
	}

	int GetNumAnimOverlays()
	{
		return *(int*)((DWORD)this + 0x297C);
	}


	NSDK::AnimationLayer *GetAnimOverlays()
	{
		// to find offset: use 9/12/17 dll
		// sig: 55 8B EC 51 53 8B 5D 08 33 C0
		return *(NSDK::AnimationLayer**)((DWORD)this + 10608);
	}

	NSDK::AnimationLayer& GetAnimOverlay(int index)
	{
		return (*(NSDK::AnimationLayer**)((DWORD)this + 0x2970))[index];
	}

	int GetSequenceActivity(int sequence)
	{
		auto hdr = NSDK::I::ModelInfo()->GetStudiomodel(this->GetModel());

		if (!hdr)
			return -1;

		static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, NSDK::studiohdr_t*, int)>(NSDK::O::FindSignature( ("client.dll"),  ("55 8B EC 83 7D 08 FF 56 8B F1 74 3D")));

		return GetSequenceActivity(this, hdr, sequence);
	}

	int GetMoveType()
	{
		return GetFieldValue<int>(0x258);
	}
	int GetArmor() {
		static int m_ArmorValue = GET_NETVAR( ("DT_CSPlayer"),  ("m_ArmorValue"));
		return GetFieldValue<int>(m_ArmorValue);
	}

	bool HasHelmet() {
		static int m_bHasHelmet = GET_NETVAR( ("DT_CSPlayer"),  ("m_bHasHelmet"));
		return GetFieldValue<bool>(m_bHasHelmet);
	}

	bool* GetSpotted() {
		static int m_bSpotted = GET_NETVAR( ("DT_BaseEntity"),  ("m_bSpotted"));
		return GetFieldPointer<bool>(m_bSpotted);
	}

	int *GetTickBase() {
		static int m_nTickBase = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_nTickBase"));
		return GetFieldPointer<int>(m_nTickBase);
	}

	bool IsAlive() 
	{
		static int m_lifeState = GET_NETVAR( ("DT_BasePlayer"),  ("m_lifeState"));
		return GetFieldValue<int>(m_lifeState) == 0 && this->GetHealth() > 0;
	}

	const NSDK::matrix3x4_t& m_rgflCoordinateFrame()
	{
		static int m_rgflCoordinateFrame = GET_NETVAR( ("DT_BaseEntity"),  ("m_CollisionGroup")) - 48;
		return GetFieldValue<NSDK::matrix3x4_t>(m_rgflCoordinateFrame);
	}

	int *GetTeamNum() {
		static int m_iTeamNum = GET_NETVAR( ("DT_BaseEntity"),  ("m_iTeamNum"));
		return GetFieldPointer<int>(m_iTeamNum);
	}

	void* GetClientRenderable()
	{
		return reinterpret_cast<void*>(this + 0x4);
	}

	int DrawModel(int flags, uint8_t alpha)
	{
		using OrigFn = int(__thiscall*)(void*, int, uint8_t);
		return NSDK::CallVFunction<OrigFn>(GetClientRenderable(), 9)(GetClientRenderable(), flags, alpha);
	}

	int *GetFlags() {
		static int m_fFlags = GET_NETVAR( ("DT_BasePlayer"),  ("m_fFlags"));
		return GetFieldPointer<int>(m_fFlags);
	}

	CBaseEntity* GetObserved() 
	{
		static int m_hObserverTarget = GET_NETVAR( ("DT_BasePlayer"),  ("m_hObserverTarget"));
		return (CBaseEntity*)NSDK::I::EntityList()->GetClientEntityFromHandle(GetFieldValue<NSDK::CBaseHandle>(m_hObserverTarget));
	}

	UINT* GetWeapons() {
		static UINT m_hMyWeapons = GET_NETVAR( ("DT_BaseCombatCharacter"),  ("m_hMyWeapons"));
		return GetFieldPointer<UINT>(m_hMyWeapons);
	}

	CBaseViewModel* GetViewModel() {
		static int m_hViewModel = GET_NETVAR( ("DT_BasePlayer"),  ("m_hViewModel[0]"));
		return (CBaseViewModel*)NSDK::I::EntityList()->GetClientEntityFromHandle(GetFieldValue<int>(m_hViewModel));
	}

	NSDK::Vector* GetViewOffset() {
		static int m_vecViewOffset = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_vecViewOffset[0]"));
		return GetFieldPointer<NSDK::Vector>(m_vecViewOffset);
	}

	NSDK::Vector* GetOrigin() {
		static int m_vecOrigin = GET_NETVAR( ("DT_BaseEntity"),  ("m_vecOrigin"));
		return GetFieldPointer<NSDK::Vector>(m_vecOrigin);
	}

	NSDK::Vector GetEyePos() {
		return *GetOrigin() + *GetViewOffset();
	}

	NSDK::CUserCmd*& m_pCurrentCommand()
	{
		static auto currentCommand = *(uint32_t*)(NSDK::O::FindSignature("client.dll", "89 BE ? ? ? ? E8 ? ? ? ? 85 FF") + 2);
		return *(NSDK::CUserCmd**)((uintptr_t)this + currentCommand);
	}

	NSDK::Vector* ViewPunch() 
	{
		static int m_viewPunchAngle = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_Local"),  ("m_viewPunchAngle"));
		return GetFieldPointer<NSDK::Vector>(m_viewPunchAngle);
	}

	NSDK::Vector* AimPunch() 
	{
		static int m_aimPunchAngle = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_Local"),  ("m_aimPunchAngle"));
		return GetFieldPointer<NSDK::Vector>(m_aimPunchAngle);
	}

	int* iFov() {
		static int m_iFOV = GET_NETVAR( ("DT_BasePlayer"),  ("m_iFOV"));
		return GetFieldPointer<int>(m_iFOV);
	}

	float* flashDuration() {
		static int m_flFlashDuration = GET_NETVAR( ("DT_CSPlayer"),  ("m_flFlashDuration"));
		return GetFieldPointer<float>(m_flFlashDuration);
	}

	bool isVisible()
	{
		NSDK::Trace_t tr;
		NSDK::Ray_t ray;
		NSDK::CTraceFilter filter;
		filter.pSkip = CBaseEntity::GetLocalPlayer();

		NSDK::matrix3x4_t boneMatrix[128];

		if (!this->SetupBones(boneMatrix, 128, 256, NSDK::I::Engine()->GetLastTimeStamp()))
			return false;

		NSDK::matrix3x4_t hitbox = boneMatrix[NSDK::ECSPlayerBones::HEAD_0];
		//-------------------------

		ray.Init(this->GetLocalPlayer()->GetEyePos(), NSDK::Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]));
		NSDK::I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

		return tr.m_pEnt == this || tr.fraction > 0.97f;
	}

	bool isVectorVisible(NSDK::Vector vec) 
	{
		NSDK::Trace_t tr;
		NSDK::Ray_t ray;
		NSDK::CTraceFilter filter;
		filter.pSkip = CBaseEntity::GetLocalPlayer();

		ray.Init(this->GetLocalPlayer()->GetEyePos(), vec);
		NSDK::I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

		return tr.m_pEnt == this;
	}

	bool canHit(NSDK::Vector end, CBaseEntity* ent) 
	{
		NSDK::Ray_t ray;

		NSDK::Trace_t tr;

		NSDK::CTraceFilter traceFilter;
		traceFilter.pSkip = this;

		ray.Init(this->GetEyePos(), end);

		NSDK::I::EngineTrace()->ClipRayToEntity(ray, MASK_SHOT, (NSDK::IHandleEntity*)ent, &tr); // ignore grate

		if (!tr.m_pEnt)
			return false;

		CBaseEntity *pEnt = (CBaseEntity*)tr.m_pEnt;

		if (*pEnt->GetTeamNum() != *this->GetTeamNum())
			return true;

		return false;
	}

	bool isMoving() 
	{
		return GetVelocity()->Length() > 1;
	}

	DWORD glowIndex() {
		static int m_glowIndex = GET_NETVAR( ("DT_CSPlayer"),  ("m_flFlashDuration")) + 0x18;
		return GetFieldValue<DWORD>(m_glowIndex);
	}

	NSDK::CBaseAnimState* GetAnimState()
	{
		return *reinterpret_cast<NSDK::CBaseAnimState**>(uintptr_t(this) + 0x3874);
	}
	
	NSDK::Vector *GetVelocity() {
		static int m_vecVelocity = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_vecVelocity[0]"));
		return GetFieldPointer<NSDK::Vector>(m_vecVelocity);
	}
	NSDK::Vector GetAbsOrigin() {
		__asm {
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX]
			CALL DWORD PTR DS : [EAX + 0x28]
		}
	}
	NSDK::Vector* GetOriginPtr() {
		static int m_vecOrigin = GET_NETVAR( ("DT_BaseEntity"),  ("m_vecOrigin"));
		return GetFieldPointer<NSDK::Vector>(m_vecOrigin);
	}
	NSDK::Vector *GetBaseVelocity() {
		static int m_vecBaseVelocity = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_vecBaseVelocity"));
		return GetFieldPointer<NSDK::Vector>(m_vecBaseVelocity);
	}

	bool isScoped()
	{
		static int m_bIsScoped = GET_NETVAR( ("DT_CSPlayer"),  ("m_bIsScoped"));
		return GetFieldValue<bool>(m_bIsScoped);
	}

	float *GetLowerBodyYaw()
	{
		static int m_flLowerBodyYawTarget = GET_NETVAR( ("DT_CSPlayer"),  ("m_flLowerBodyYawTarget"));
		return GetFieldPointer<float>(m_flLowerBodyYawTarget);
	}

	float *GetSimulationTime()
	{
		static int m_flSimulationTime = GET_NETVAR( ("DT_BaseEntity"),  ("m_flSimulationTime"));
		return GetFieldPointer<float>(m_flSimulationTime);
	}

	float *GetAnimTime()
	{
		static int m_flAnimTime = 0x0;
		return GetFieldPointer<float>(m_flAnimTime);
	}

	std::array<float, 24> &m_flPoseParameter()
	{
		static int _m_flPoseParameter = GET_NETVAR(("DT_BaseAnimating"), ("m_flPoseParameter"));
		return *(std::array<float, 24>*)((uintptr_t)this + _m_flPoseParameter);
	}

	bool *GetDucked()
	{
		static int m_bDucked = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_Local"),  ("m_bDucked"));
		return GetFieldPointer<bool>(m_bDucked);
	}

	bool *GetDucking()
	{
		static int m_bDucking = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_Local"),  ("m_bDucking"));
		return GetFieldPointer<bool>(m_bDucking);
	}

	float *GetDuckSpeed()
	{
		static int m_flDuckSpeed = GET_NETVAR( ("DT_BasePlayer"),  ("m_flDuckSpeed"));
		return GetFieldPointer<float>(m_flDuckSpeed);
	}

	bool *GetDuckOverride()
	{
		static int m_bDuckOverride = GET_NETVAR( ("DT_CSPlayer"),  ("cslocaldata"),  ("m_bDuckOverride"));
		return GetFieldPointer<bool>(m_bDuckOverride);
	}

	float *GetDuckAmount() {
		static int m_flDuckAmount = GET_NETVAR( ("DT_BasePlayer"),  ("m_flDuckAmount"));
		return GetFieldPointer<float>(m_flDuckAmount);
	}

	bool InBuyZone() {
		static int m_bInBuyZone = GET_NETVAR( ("DT_CSPlayer"),  ("m_bInBuyZone"));
		return GetFieldValue<bool>(m_bInBuyZone);
	}

	bool isDucking() {
		return (bool)(*this->GetFlags() & (int)NSDK::EntityFlags::FL_DUCKING);
	}

	NSDK::Vector *GetMin() {
		static int m_vecMins = GET_NETVAR( ("DT_BaseEntity"),  ("m_Collision"),  ("m_vecMins"));
		return GetFieldPointer<NSDK::Vector>(m_vecMins);
	}

	NSDK::Vector *GetMax() {
		static int m_vecMaxs = GET_NETVAR( ("DT_BaseEntity"),  ("m_Collision"),  ("m_vecMaxs"));
		return GetFieldPointer<NSDK::Vector>(m_vecMaxs);
	}

	void UpdateClientSideAnimation() 
	{
		NSDK::CallVFunction<void(__thiscall*)(void*)>(this, 218)(this);
	}

	void InvalidateBoneCache()
	{
		//nice gladz paste idiot
		DWORD invalKostCache = NSDK::O::FindPattern("client.dll", (BYTE*)"\x80\x3D\x00\x00\x00\x00\x00\x74\x16\xA1\x00\x00\x00\x00\x48\xC7\x81", "xx?????xxx????xxx");
		unsigned long g_iModelBoneCounter = **(unsigned long**)(invalKostCache + 10);
		*(unsigned int*)((DWORD)this + 0x2914) = 0xFF7FFFFF;
		*(unsigned int*)((DWORD)this + 0x2680) = (g_iModelBoneCounter - 1);
	}
	bool isValidPlayer(bool isLocalPlayer = false) {
		if (!this)
			return false;

		//35U is CCSPlayer
		if (this->GetClientClass()->m_ClassID != 35U)
			return false;

		if (!this->IsAlive())
			return false;

		if (this->IsDormant())
			return false;

		if (this->isSpawnImmune())
			return false;

		if (!isLocalPlayer)
		{
			if (this->EntIndex() == CBaseEntity::GetLocalPlayer()->EntIndex())
				return false;
		}

		return true;
	}

	bool isValidWeapon()
	{
		if (!this)
			return false;
		if (strstr(this->GetClientClass()->m_pNetworkName,  ("CWeapon")) ||
			strstr(this->GetClientClass()->m_pNetworkName,  ("CAK47")))
			return true;
		return false;
	}

	NSDK::Vector GetEntityHitbox(int iHitBox) 
	{
		NSDK::matrix3x4_t boneMatrix[128];

		if (!this->SetupBones(boneMatrix, 128, 256, NSDK::I::Engine()->GetLastTimeStamp()))
			return NSDK::Vector();

		NSDK::studiohdr_t* hdr = NSDK::I::ModelInfo()->GetStudiomodel(this->GetModel());
		NSDK::mstudiohitboxset_t* set = hdr->pHitboxSet(0);

		NSDK::matrix3x4_t hitbox = boneMatrix[set->pHitbox(iHitBox)->bone];

		return NSDK::Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}

	bool isSpawnImmune() 
	{
		static int m_bGunGameImmunity = GET_NETVAR( ("DT_CSPlayer"),  ("m_bGunGameImmunity"));
		return GetFieldValue<bool>(m_bGunGameImmunity);
	}

	float *GetFallVelocity() 
	{
		static int m_flFallVelocity = GET_NETVAR( ("DT_BasePlayer"),  ("localdata"),  ("m_Local"),  ("m_flFallVelocity"));
		return GetFieldPointer<float>(m_flFallVelocity);
	}

	NSDK::Vector WorldSpaceCenter() {
		NSDK::Vector Max = *this->GetMax() + *this->GetOrigin();
		NSDK::Vector Min = *this->GetMin() + *this->GetOrigin();
		NSDK::Vector Size = Max - Min;
		Size /= 2;
		Size += Min;
		return Size;
	}

	int *GetRenderMode() {
		static int m_nRenderMode = GET_NETVAR( ("DT_BaseEntity"),  ("m_nRenderMode"));
		return GetFieldPointer<int>(m_nRenderMode);
	}

	int *GetEffects() {
		static int m_fEffects = GET_NETVAR( ("DT_BaseEntity"),  ("m_fEffects"));
		return GetFieldPointer<int>(m_fEffects);
	}

	NSDK::Color *GetColorRender() {
		static int m_clrRender = GET_NETVAR( ("DT_BaseEntity"),  ("m_clrRender"));
		return GetFieldPointer<NSDK::Color>(m_clrRender);
	}

	int *GetTextureIndex() {
		static int m_iTextureFrameIndex = GET_NETVAR( ("DT_BaseEntity"),  ("m_iTextureFrameIndex"));
		return GetFieldPointer<int>(m_iTextureFrameIndex);
	}

	float *GetFadeMax() {
		static int m_fadeMaxDist = GET_NETVAR( ("DT_BaseEntity"),  ("m_fadeMaxDist"));
		return GetFieldPointer<float>(m_fadeMaxDist);
	}

	float *GetFadeScale() {
		static int m_flFadeScale = GET_NETVAR( ("DT_BaseEntity"),  ("m_flFadeScale"));
		return GetFieldPointer<float>(m_flFadeScale);
	}

};

class CBaseAttributableItem : public CBaseEntity {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	int* GetItemDefinitionIndex()
	{
		static int m_iItemDefinitionIndex = GET_NETVAR( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iItemDefinitionIndex"));
		return GetFieldPointer<int>(m_iItemDefinitionIndex);
	}

	int* GetItemIDHigh()
	{
		static int m_iItemIDHigh = GET_NETVAR( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iItemIDHigh"));
		return GetFieldPointer<int>(m_iItemIDHigh);
	}

	int* GetEntityQuality() 
	{
		static int m_iEntityQuality = GET_NETVAR( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_iEntityQuality"));
		return GetFieldPointer<int>(m_iEntityQuality);
	}

	char* GetCustomName() 
	{
		static int m_szCustomName = GET_NETVAR( ("DT_BaseAttributableItem"),  ("m_AttributeManager"),  ("m_Item"),  ("m_szCustomName"));
		return GetFieldPointer<char>(m_szCustomName);
	}

	int* GetFallbackPaintKit() 
	{
		static int m_nFallbackPaintKit = GET_NETVAR( ("DT_BaseAttributableItem"),  ("m_nFallbackPaintKit"));
		return GetFieldPointer<int>(m_nFallbackPaintKit);
	}

	float* GetFallbackWear() 
	{
		static int m_flFallbackWear = GET_NETVAR( ("DT_BaseAttributableItem"),  ("m_flFallbackWear"));
		return GetFieldPointer<float>(m_flFallbackWear);
	}

	int* GetFallbackStatTrak() 
	{
		static int m_bSpotted = GET_NETVAR( ("DT_BaseAttributableItem"),  ("m_nFallbackStatTrak"));
		return GetFieldPointer<int>(m_bSpotted);
	}
};

class CBaseCSGrenade : CBaseCombatWeapon {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	float GetThrowTime()
	{
		static int m_fThrowTime = GET_NETVAR( ("DT_BaseCSGrenade"),  ("m_fThrowTime"));
		return GetFieldValue<float>(m_fThrowTime);
	}
};