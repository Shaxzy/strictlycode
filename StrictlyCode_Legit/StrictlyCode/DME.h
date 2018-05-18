#pragma once

#include <fstream>

#include "SqchSDK\Interfaces.h"
#include "EntityStructs.h"

namespace DME {
	typedef void(__thiscall* DrawModelExecute_t)(void*, NSDK::IMatRenderContext*, const NSDK::DrawModelState_t&, const NSDK::ModelRenderInfo_t&, NSDK::matrix3x4_t*);

	extern DrawModelExecute_t g_fnOriginalDrawModelExecute;

	//Funcs
	void __fastcall Hooked_DrawModelExecute(void* thisptr, void* edx, NSDK::IMatRenderContext* ctx, const NSDK::DrawModelState_t& state, const NSDK::ModelRenderInfo_t& pInfo, NSDK::matrix3x4_t* pCustomBoneToWorld);
}