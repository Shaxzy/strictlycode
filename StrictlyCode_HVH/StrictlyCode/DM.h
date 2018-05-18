#pragma once

#include <fstream>

#include "SqchSDK\Interfaces.h"
#include "EntityStructs.h"

namespace DM {
	typedef void(__thiscall* DrawModel_t)(void*, NSDK::DrawModelResults_t *pResults, const NSDK::DrawModelInfo_t& info,
		NSDK::matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const NSDK::Vector &modelOrigin, int flags);

	extern DrawModel_t g_fnOriginalDrawModel;

	void __fastcall Hooked_DrawModel(void* thisptr, void* edx, NSDK::DrawModelResults_t *pResults, const NSDK::DrawModelInfo_t& info,
		NSDK::matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const NSDK::Vector &modelOrigin, int flags = 0);

	void InitChams();
}