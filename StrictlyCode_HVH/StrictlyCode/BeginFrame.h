#pragma once

#include "SqchSDK\Interfaces.h"
#include "EntityStructs.h"

namespace BeginFrame
{
	typedef void(__thiscall* BeginFrame_t)(void*);

	extern BeginFrame_t g_fnOriginalBeginFrame;

	void __fastcall Hooked_BeginFrame(void* thisptr, void* edx);
}