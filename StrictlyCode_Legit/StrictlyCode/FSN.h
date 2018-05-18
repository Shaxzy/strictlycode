#pragma once

#include <vector>
#include <cmath>

#include "SqchSDK\Interfaces.h"
#include "EntityStructs.h"
#include "Utilities.h"
#include "OptionsManager.h"

namespace FSN
{
	typedef void(__thiscall* FrameStageNotify_t)(void*, NSDK::ClientFrameStage_t);

	extern FrameStageNotify_t g_fnOriginalFrameStageNotify;

	VOID __fastcall Hooked_FrameStageNotify(void* thisptr, void* edx, NSDK::ClientFrameStage_t curStage);
}