 #include "OView.h"

namespace OView 
{
	OverrideView_t g_fnOriginalOverrideView;
	void __fastcall Hooked_OverrideView(void* thisptr, int edx, NSDK::CViewSetup* pSetup) 
	{
		CBaseEntity *pLocal = CBaseEntity::GetLocalPlayer();
		if (!pLocal || !pLocal->isValidPlayer(true) || !pLocal->GetActiveWeapon()) return;

			if (!pLocal->isScoped())
			{
				pSetup->fov += Options.iLocalFov;
			}

		g_fnOriginalOverrideView(thisptr, pSetup);
	}
}