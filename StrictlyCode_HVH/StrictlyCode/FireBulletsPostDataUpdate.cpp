#include "FireBulletsPostDataUpdate.h"
#include "Globals.h"
#define TICK_INTERVAL			( NSDK::I::GlobalVars()->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( NSDK::I::GlobalVars()->interval_per_tick *( t ) )
namespace TEFireBullet 
{
	FireBullets_t g_fnOriginalFireBullets;

	// Used For Resolving
	void __stdcall FireBullets_PostDataUpdate(NSDK::C_TEFireBullets* thisptr, DataUpdateType_t updateType)
	{
		g_fnOriginalFireBullets(thisptr, updateType);

		int idx = thisptr->m_iPlayer + 1;

		if (idx < 64)
		{
			CBaseEntity* player = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(idx);

			if (!player)
				return;

			if (!player->isValidPlayer())
				return;
		}
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