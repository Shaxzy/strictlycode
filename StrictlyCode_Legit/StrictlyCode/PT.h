#pragma once

#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"

#include "DrawManager.h"

#include "EntityStructs.h"

#include "Utilities.h"

namespace PT{
	typedef void* (__thiscall* PaintTraverse_t)(void*, unsigned int, bool, bool);
	
	extern PaintTraverse_t g_fnOriginalPaintTraverse;

	VOID __fastcall Hooked_PaintTraverse(void* thisptr, void* edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
}