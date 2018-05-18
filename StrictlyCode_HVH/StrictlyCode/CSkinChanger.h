#pragma once
#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"

#include "DrawManager.h"

#include "EntityStructs.h"
#include <map>
#include "Utilities.h"
#define WEAPON_KNIFE_BAYONET "models/weapons/v_knife_bayonet.mdl"
#define WEAPON_KNIFE_FLIP "models/weapons/v_knife_flip.mdl"
#define WEAPON_KNIFE_GUT "models/weapons/v_knife_gut.mdl"
#define WEAPON_KNIFE_KARAMBIT "models/weapons/v_knife_karam.mdl"
#define WEAPON_KNIFE_M9_BAYONET "models/weapons/v_knife_m9_bay.mdl"

static bool bOnce = false;
struct EconomyItemCfg 
{
	int knifeType = -1;
	int nFallbackPaintKit = 0;
	int nFallbackSeed = 0;
	int nFallbackStatTrak = -1;
	int iEntityQuality = 4;
	char* szCustomName = nullptr;
	float flFallbackWear = 0.00001f;
};

extern std::unordered_map<int, EconomyItemCfg> g_SkinChangerCfg;

class SkinChanger
{
public:
	static void FrameStageNotify_Pre(NSDK::ClientFrameStage_t stage)
	{
		if (!IsEnabled())
			return;
		if (!bOnce)
		{
			InitSkins();
			bOnce = true;
		}
		if (stage != NSDK::ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			return;

		auto pLocal = CBaseEntity::GetLocalPlayer();
		if (!pLocal || !pLocal->IsAlive())
			return;

		auto pWeapon = pLocal->GetActiveWeapon();
		if (!pWeapon)
			return;

		ApplySkin(pWeapon);
	}

	static bool ApplySkin(CBaseCombatWeapon* pWeapon) 
	{
		if (!pWeapon)
			return false;

		auto nWeaponIndex = *pWeapon->GetItemDefinitionIndex();
		if (g_SkinChangerCfg.find(nWeaponIndex) == g_SkinChangerCfg.end())
			return false;

		// Apply our changes to the fallback variables.
		*pWeapon->FallbackPaintKit() = g_SkinChangerCfg[nWeaponIndex].nFallbackPaintKit;
		*pWeapon->EntityQuality() = g_SkinChangerCfg[nWeaponIndex].iEntityQuality;
		*pWeapon->FallbackSeed() = g_SkinChangerCfg[nWeaponIndex].nFallbackSeed;
		*pWeapon->FallbackStatTrak() = g_SkinChangerCfg[nWeaponIndex].nFallbackStatTrak;
		*pWeapon->FallbackWear() = g_SkinChangerCfg[nWeaponIndex].flFallbackWear;
		if (g_SkinChangerCfg[nWeaponIndex].knifeType != -1)
		{
			switch (g_SkinChangerCfg[nWeaponIndex].knifeType)
			{
			case 0:
			case 1:break;
			case 2:
				*pWeapon->GetModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_BAYONET);
				*pWeapon->GetViewModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_BAYONET);
				*pWeapon->GetWorldModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_BAYONET) +1;
				break;
			case 3:
				*pWeapon->GetModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_FLIP);
				*pWeapon->GetViewModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_FLIP);
				*pWeapon->GetWorldModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_FLIP) + 1;
				break;
			case 4:
				*pWeapon->GetModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_GUT);
				*pWeapon->GetViewModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_GUT);
				*pWeapon->GetWorldModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_GUT) + 1;
				break;
			case 5:
				*pWeapon->GetModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_KARAMBIT);
				*pWeapon->GetViewModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_KARAMBIT);
				*pWeapon->GetWorldModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_KARAMBIT) + 1;
				break;
			case 6:
				*pWeapon->GetModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_M9_BAYONET);
				*pWeapon->GetViewModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_M9_BAYONET);
				*pWeapon->GetWorldModelIndex() = NSDK::I::ModelInfo()->GetModelIndex(WEAPON_KNIFE_M9_BAYONET) + 1;
				break;
			}
		}
		if (g_SkinChangerCfg[nWeaponIndex].szCustomName)
			sprintf_s(pWeapon->CustomName(), 128, "%s", g_SkinChangerCfg[nWeaponIndex].szCustomName);

		// Edit "m_iItemIDHigh" so fallback values will be used.
		*pWeapon->ItemIDHigh() = -1;
		return true;
	}

	static void InitSkins()
	{
		g_SkinChangerCfg[NSDK::weapon_awp].nFallbackPaintKit = 344;           // Dragon Lore
		g_SkinChangerCfg[NSDK::weapon_ak47].nFallbackPaintKit = 302;          // Vulkan
		g_SkinChangerCfg[NSDK::weapon_m4a4].nFallbackPaintKit = 309;          // Howl
		g_SkinChangerCfg[NSDK::weapon_m4a1_silencer].nFallbackPaintKit = 587; // Mecha Industries (M4A1-S)
		g_SkinChangerCfg[NSDK::weapon_ssg08].nFallbackPaintKit = 222;         // Blood in the Water
		g_SkinChangerCfg[NSDK::weapon_p90].nFallbackPaintKit = 359;           // Asiimov (P90)
		g_SkinChangerCfg[NSDK::weapon_glock].nFallbackPaintKit = 38;          // Fade (Glock-18)
		g_SkinChangerCfg[NSDK::weapon_usp_silencer].nFallbackPaintKit = 313;  // Orion
		g_SkinChangerCfg[NSDK::weapon_p250].nFallbackPaintKit = 551;          // Asiimov (P250)
		g_SkinChangerCfg[NSDK::weapon_scar20].nFallbackPaintKit = 597;        // Bloodsport
		g_SkinChangerCfg[NSDK::weapon_mag7].nFallbackPaintKit = 39;           // Bulldozer
		g_SkinChangerCfg[NSDK::weapon_mp9].nFallbackPaintKit = 39;            // Bulldozer
		g_SkinChangerCfg[NSDK::weapon_g3sg1].nFallbackPaintKit = 493;         // Bulldozer
		g_SkinChangerCfg[NSDK::weapon_deagle].nFallbackPaintKit = 351;        // Conspiracy
		g_SkinChangerCfg[NSDK::weapon_revolver].nFallbackPaintKit = 683;      // llama cannon (revolver)
	}
private:
	static bool IsEnabled()
	{
		if (!Options.bSkinchanger)
			return false;

		return true;
	}
};