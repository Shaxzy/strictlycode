#pragma once

#include "SqchSDK\Interfaces.h"

#include "EntityStructs.h"

#include "Utilities.h"

namespace OView {
	typedef void(__thiscall* OverrideView_t)(void*, NSDK::CViewSetup*);

	extern OverrideView_t g_fnOriginalOverrideView;

	void __fastcall Hooked_OverrideView(void* thisptr, int edx, NSDK::CViewSetup* pSetup);
}