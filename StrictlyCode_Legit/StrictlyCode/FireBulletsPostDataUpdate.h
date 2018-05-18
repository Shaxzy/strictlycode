#pragma once

#include "SqchSDK\Interfaces.h"
#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Utilities.h"

enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,
	//	DATA_UPDATE_ENTERED_PVS,
	DATA_UPDATE_DATATABLE_CHANGED
	//	DATA_UPDATE_LEFT_PVS,
	//DATA_UPDATE_DESTROYED,
};

namespace TEFireBullet
{
	typedef void(__thiscall* FireBullets_t)(NSDK::C_TEFireBullets*, DataUpdateType_t);

	extern FireBullets_t g_fnOriginalFireBullets;

	void __stdcall FireBullets_PostDataUpdate(NSDK::C_TEFireBullets* thisptr, DataUpdateType_t updateType);
	void __stdcall HookedTEFireBulletsPostDataUpdate(DataUpdateType_t updateType);
}