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
#include "BeginFrame.h"
#include "CBulletListener.h"
#include "RunCommand.h"
#include "CDeathListener.h"
#include "CFireListener.h"

#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"WS2_32.lib")

#include "CHurtListener.h"
#include "CPurchaseListener.h"
#include "CSayListener.h"
namespace Hooks 
{
	std::unique_ptr<HookTable::VFTableHook> client = nullptr;
	std::unique_ptr<HookTable::VFTableHook> studiorender = nullptr;
	std::unique_ptr<HookTable::VFTableHook> modelrender = nullptr;
	std::unique_ptr<HookTable::VFTableHook> vgui = nullptr;
	std::unique_ptr<HookTable::VFTableHook> clientmode = nullptr;
	std::unique_ptr<HookTable::VFTableHook> d3dd9 = nullptr;
	std::unique_ptr<HookTable::VFTableHook> engine = nullptr;
	std::unique_ptr<HookTable::VFTableHook> viewrender = nullptr;
	std::unique_ptr<HookTable::VFTableHook> firebullet = nullptr;
	std::unique_ptr<HookTable::VFTableHook> prediction = nullptr;

	HookTable::VFTableHook *enginetrace = nullptr;
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
	void __fastcall Hooked_ClipRay(void* thisptr, void* edx, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::IHandleEntity *pEnt, NSDK::CGameTrace *pTrace)
	{
		g_fnOriginalClipRay(thisptr, ray, fMask, pEnt, pTrace);
		pTrace->fraction = 1.f;
	}

	typedef void(__thiscall* TraceRay)(void*, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::ITraceFilter *pTraceFilter, NSDK::CGameTrace *pTrace);
	TraceRay g_fnOriginalTraceRay;
	void __fastcall Hooked_TracRay(void* thisptr, void* edx, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::ITraceFilter *pTraceFilter, NSDK::CGameTrace *pTrace) 
	{
		g_fnOriginalTraceRay(thisptr, ray, fMask, pTraceFilter, pTrace);
		pTrace->fraction = 1.f;
	}

	typedef void(__thiscall* RayCollide)(void*, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::ICollideable *pCollide, NSDK::CGameTrace *pTrace);
	RayCollide g_fnOriginalRayCollide;
	void __fastcall Hooked_RayCollide(void* thisptr, void* edx, const NSDK::Ray_t &ray, unsigned int fMask, NSDK::ICollideable *pCollide, NSDK::CGameTrace *pTrace) 
	{
		g_fnOriginalRayCollide(thisptr, ray, fMask, pCollide, pTrace);
		pTrace->fraction = 1.f;
	}
	void Initialize()
	{
		//-----------------------------------------------------------------------------------------------

		NetvarManager::Instance()->CreateDatabase();
		//dumping netvars (in steam folder)
		NetvarManager::Instance()->Dump("nvdump.txt");
		Drawing::InitializeFont();

		//-----------------------------------------------------------------------------------------------
		//Welcome message + config setup
		ConSys->CheckConfigs();
		ConSys->Handle();

		NSDK::I::Engine()->ExecuteClientCmd("cl_showfps 0");
		NSDK::I::Engine()->ExecuteClientCmd("cl_showpos 0");

		NSDK::I::Engine()->ExecuteClientCmd("clear");

		ConSys->LoadConfig();

		std::string welcome = "\n-> Welcome to " cheat_name" " + Local::user + "! \n";
		NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(255, 0, 255), welcome.c_str());
		//-----------------------------------------------------------------------------------------------

		auto dwDevice = **(uint32_t**)(NSDK::O::FindSignature( ("shaderapidx9.dll"),  ("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);
		auto oTE_FireBullets = *reinterpret_cast<NSDK::C_TEFireBullets**>(NSDK::O::FindSignature("client.dll", "55 8B EC 51 53 56 8B F1 BB ? ? ? ? B8") + 0x131);
		//-----------------------------------------------------------------------------------------------

		client = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::Client(), true);
		studiorender = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::StudioRender(), true);
		modelrender = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::ModelRender(), true);
		vgui = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::VGUIPanel(), true);
		clientmode = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::ClientMode(), true);
		d3dd9 = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)dwDevice, true);
		engine = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::Engine(), true);
		viewrender = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::ViewRender(), true);
		firebullet = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)oTE_FireBullets, true);
		prediction = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)NSDK::I::Prediction(), true);

		while (!(DirectX::g_hWindow = FindWindowA( ("Valve001"), NULL))) Sleep(200);

		if (DirectX::g_hWindow)
			DirectX::g_pOldWindowProc = (WNDPROC)SetWindowLongPtr(DirectX::g_hWindow, GWLP_WNDPROC, (LONG_PTR)DirectX::Hooked_WndProc);

		//drawing
		PT::g_fnOriginalPaintTraverse = vgui->Hook(41, (PT::PaintTraverse_t)PT::Hooked_PaintTraverse);
		DirectX::g_fnOriginalReset = d3dd9->Hook(16, DirectX::Hooked_Reset);
		DirectX::g_fnOriginalEndScene = d3dd9->Hook(42, DirectX::Hooked_EndScene);

		//chams
		SceneEnd::g_fnOriginalSceneEnd = viewrender->Hook(9, (SceneEnd::SceneEnd_t)SceneEnd::Hooked_SceneEnd);
		DM::g_fnOriginalDrawModel = studiorender->Hook(29, (DM::DrawModel_t)DM::Hooked_DrawModel);
		DME::g_fnOriginalDrawModelExecute = modelrender->Hook(21, (DME::DrawModelExecute_t)DME::Hooked_DrawModelExecute);

		//FSN
		FSN::g_fnOriginalFrameStageNotify = client->Hook(36, (FSN::FrameStageNotify_t)FSN::Hooked_FrameStageNotify);

		//CM
		CHLCM::g_fnOriginalCreateMoveCHL = client->Hook(21, (CHLCM::CreateMoveCHL_t)HookedCreateMoveNaked);

		//OverrideView hooks
		OView::g_fnOriginalOverrideView = clientmode->Hook(18, (OView::OverrideView_t)OView::Hooked_OverrideView);

		//bullet lines
		BeginFrame::g_fnOriginalBeginFrame = studiorender->Hook(9, (BeginFrame::BeginFrame_t)BeginFrame::Hooked_BeginFrame);

		//firebullets for backtrack to shot
		TEFireBullet::g_fnOriginalFireBullets = firebullet->Hook(7, (TEFireBullet::FireBullets_t)TEFireBullet::HookedTEFireBulletsPostDataUpdate);
		
		//runcommand pred for fixing lagcomp breakers
		RunCommand::g_fnOrigRunCommand = prediction->Hook(19, (RunCommand::RunCommand_t)RunCommand::Hooked_RunCommand);

		//init listeners
		CHurtListener::singleton()->init();
		CPurchaseListener::singleton()->init();
		CSayListener::singleton()->init();
		CBulletListener::singleton()->init();
		CDeathListener::singleton()->init();
		CFireListener::singleton()->init();
	}

	void RestoreAllTable()
	{
		//unhooking

		Sleep(500);
		vgui->Unhook(41);
		d3dd9->Unhook(16);
		d3dd9->Unhook(42);
		studiorender->Unhook(29);
		modelrender->Unhook(21);
		client->Unhook(36);
		client->Unhook(21);
		clientmode->Unhook(18);
		studiorender->Unhook(9);
		firebullet->Unhook(7);
		viewrender->Unhook(9);

		Sleep(500);
		client->RestoreTable();
		modelrender->RestoreTable();
		vgui->RestoreTable();
		clientmode->RestoreTable();
		d3dd9->RestoreTable();
		engine->RestoreTable();
		viewrender->RestoreTable();
		prediction->RestoreTable();
		SetWindowLongPtr(DirectX::g_hWindow, GWLP_WNDPROC, (LONG_PTR)DirectX::g_pOldWindowProc);
	}
}