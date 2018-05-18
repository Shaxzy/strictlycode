#pragma once

#include "SqchSDK\Interfaces.h"
#include "EntityStructs.h"
#include "Globals.h"
#include "OptionsManager.h"
//#include "CBacktracking.h"
namespace SceneEnd
{
	typedef void(__thiscall* SceneEnd_t)(NSDK::IVRenderView*);

	extern SceneEnd_t g_fnOriginalSceneEnd;

	void __stdcall Hooked_SceneEnd();
}