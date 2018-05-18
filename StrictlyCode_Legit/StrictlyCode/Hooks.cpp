#include "Hooks.h"

#include "SqchSDK\Interfaces.h"
#include <wininet.h>
#include <cstring>
#include <windows.h>
#include <iostream>
#include <urlmon.h>
#include <ctype.h>
#include "ConfigManager.h"
#include "Globals.h"
#include "SceneEnd.h"

#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"WS2_32.lib")

#include "CHurtListener.h"
#include "CPurchaseListener.h"
#include "CSayListener.h"
namespace Hooks {
	std::unique_ptr<HookTable::VFTableHook> g_pClientHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pStudioRenderHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pModelRenderHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pVGuiHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pClientModeHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pD3DDevice9Hook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pEngineHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pViewRenderHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pFireBulletHook = nullptr;

	HookTable::VFTableHook *g_pEngineTraceHook = nullptr;
	void __declspec(naked) __stdcall HookedCreateMoveNaked(int sequence_number, float input_sample_frametime, bool active)
	{
		__asm
		{
			PUSH EBX				// push sendpacket from ebx
			PUSH ESP				// push address of sendpackt
			PUSH[ESP + 0x14]		// push active
			PUSH[ESP + 0x14]		// push input_sample_frametime
			PUSH[ESP + 0x14]		// push sequence_number
			CALL CHLCM::Hooked_CreateMove_CHL	// call our own CreateMove function
			POP EBX					// pop sendpacket to ebx
			RET 0x0C				// remove 3 agruments from stack and return
		}
	}

	typedef void(__thiscall* ClipRay)(void*, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::IHandleEntity *pEnt, NSDK::CGameTrace *pTrace);
	ClipRay g_fnOriginalClipRay;
	void __fastcall Hooked_ClipRay(void* thisptr, void* edx, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::IHandleEntity *pEnt, NSDK::CGameTrace *pTrace) {
		g_fnOriginalClipRay(thisptr, ray, fMask, pEnt, pTrace);
		pTrace->fraction = 1.f;
	}

	typedef void(__thiscall* TraceRay)(void*, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::ITraceFilter *pTraceFilter, NSDK::CGameTrace *pTrace);
	TraceRay g_fnOriginalTraceRay;
	void __fastcall Hooked_TracRay(void* thisptr, void* edx, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::ITraceFilter *pTraceFilter, NSDK::CGameTrace *pTrace) {
		/*NSDK::Ray_t ray2;
		NSDK::Vector vec = CBaseEntity::GetLocalPlayer()->GetEyePos();
		vec.z += 20.f;
		NSDK::Vector vec2 = CBaseEntity::GetLocalPlayer()->GetEyePos();
		vec.z += 25.f;
		ray2.Init(vec, vec2);*/
		g_fnOriginalTraceRay(thisptr, ray, fMask, pTraceFilter, pTrace);
		pTrace->fraction = 1.f;
	}

	typedef void(__thiscall* RayCollide)(void*, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::ICollideable *pCollide, NSDK::CGameTrace *pTrace);
	RayCollide g_fnOriginalRayCollide;
	void __fastcall Hooked_RayCollide(void* thisptr, void* edx, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::ICollideable *pCollide, NSDK::CGameTrace *pTrace) {
		g_fnOriginalRayCollide(thisptr, ray, fMask, pCollide, pTrace);
		pTrace->fraction = 1.f;
	}
	void Initialize()
	{
		//-----------------------------------------------------------------------------------------------

		NetvarManager::Instance()->CreateDatabase();

		DrawManager::InitializeFont();

		//-----------------------------------------------------------------------------------------------
		//Welcome message + config setup
		ConSys->CheckConfigs();
		ConSys->Handle();

		NSDK::I::Engine()->ExecuteClientCmd("cl_showfps 0");
		NSDK::I::Engine()->ExecuteClientCmd("cl_showpos 0");

		NSDK::I::Engine()->ExecuteClientCmd("clear");

		ConSys->LoadConfig();

		std::string welcome = "\n-> Welcome to " cheat_name "! \n";
		NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(155, 0, 155, 255), welcome.c_str());
		//-----------------------------------------------------------------------------------------------

		auto dwDevice = **(uint32_t**)(NSDK::O::FindSignature(XorStr("shaderapidx9.dll"), XorStr("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);
		//-----------------------------------------------------------------------------------------------

		g_pClientHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::Client(), true);
		g_pStudioRenderHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::StudioRender(), true);
		g_pModelRenderHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::ModelRender(), true);
		g_pVGuiHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::VGUIPanel(), true);
		g_pClientModeHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::ClientMode(), true);
		g_pD3DDevice9Hook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)dwDevice, true);
		g_pEngineHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::Engine(), true);
		//g_pViewRenderHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::ViewRender(), true);

		while (!(DirectX::g_hWindow = FindWindowA(XorStr("Valve001"), NULL))) Sleep(200);

		if (DirectX::g_hWindow)
			DirectX::g_pOldWindowProc = (WNDPROC)SetWindowLongPtr(DirectX::g_hWindow, GWLP_WNDPROC, (LONG_PTR)DirectX::Hooked_WndProc);

		//Drawing hooks
		PT::g_fnOriginalPaintTraverse = g_pVGuiHook->Hook(41, (PT::PaintTraverse_t)PT::Hooked_PaintTraverse);
		DirectX::g_fnOriginalReset = g_pD3DDevice9Hook->Hook(16, DirectX::Hooked_Reset);
		DirectX::g_fnOriginalEndScene = g_pD3DDevice9Hook->Hook(42, DirectX::Hooked_EndScene);
		DM::g_fnOriginalDrawModel = g_pStudioRenderHook->Hook(29, (DM::DrawModel_t)DM::Hooked_DrawModel);

		DME::g_fnOriginalDrawModelExecute = g_pModelRenderHook->Hook(21, (DME::DrawModelExecute_t)DME::Hooked_DrawModelExecute);

		//Update hooks
		FSN::g_fnOriginalFrameStageNotify = g_pClientHook->Hook(36, (FSN::FrameStageNotify_t)FSN::Hooked_FrameStageNotify);

		//Move hooks
		CHLCM::g_fnOriginalCreateMoveCHL = g_pClientHook->Hook(21, (CHLCM::CreateMoveCHL_t)HookedCreateMoveNaked);

		//OverrideMouseInput 
		//OMI::g_fnOriginalMouseInput = g_pClientModeHook->Hook(23, (OMI::MouseInput_t)OMI::Hooked_MouseInput);

		//SceneEnd::g_fnOriginalSceneEnd = g_pViewRenderHook->Hook(9, (SceneEnd::SceneEnd_t)SceneEnd::Hooked_SceneEnd);

		//RenderView hook -> Can't hook this, it crashes even if correct meh
		//RView::g_fnOriginalRenderView = g_pViewRenderHook->Hook(6, (RView::RenderView_t)RView::Hooked_RenderView);

		//OverrideView hooks
		OView::g_fnOriginalOverrideView = g_pClientModeHook->Hook(18, (OView::OverrideView_t)OView::Hooked_OverrideView);

		//------------------------------------------------------------------------------------------------

		//initialize the listeners.
		CHurtListener::singleton()->init();
		CPurchaseListener::singleton()->init();
		CSayListener::singleton()->init();
	}

	void RestoreAllTable()
	{
		g_pClientHook->RestoreTable();
		g_pModelRenderHook->RestoreTable();
		g_pVGuiHook->RestoreTable();
		g_pClientModeHook->RestoreTable();
		g_pD3DDevice9Hook->RestoreTable();
		g_pEngineHook->RestoreTable();

		SetWindowLongPtr(DirectX::g_hWindow, GWLP_WNDPROC, (LONG_PTR)DirectX::g_pOldWindowProc);
	}
}