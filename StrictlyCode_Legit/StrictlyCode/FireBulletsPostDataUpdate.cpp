#include "FireBulletsPostDataUpdate.h"

namespace TEFireBullet 
{
	FireBullets_t g_fnOriginalFireBullets;

	// Used For Resolving
	void __stdcall FireBullets_PostDataUpdate(NSDK::C_TEFireBullets* thisptr, DataUpdateType_t updateType)
	{
		g_fnOriginalFireBullets(thisptr, updateType);
	}

	__declspec (naked) void __stdcall HookedTEFireBulletsPostDataUpdate(DataUpdateType_t updateType)
	{
		__asm
		{
			push[esp + 4]
			push ecx
			call FireBullets_PostDataUpdate
			retn 4
		}
	}
}