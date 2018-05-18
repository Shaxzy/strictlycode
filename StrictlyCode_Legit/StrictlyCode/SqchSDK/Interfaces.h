#pragma once
#include <Windows.h>

#include "SDKHelper\XorStr.h"

#include "SDK\AllDef.h"
#include "SDK\CInput.h"
#include "SDK\IVEngineClient.h"
#include "SDK\IVModelRender.h"
#include "SDK\IVDebugOverlay.h"
#include "SDK\IVModelInfo.h"
#include "SDK\IVRenderView.h"
#include "SDK\ICvar.h"
#include "SDK\IClientEntityList.h"
#include "SDK\IBaseClientDLL.h"
#include "SDK\IClientMode.h"
#include "SDK\IMaterial.h"
#include "SDK\IMaterialSystem.h"
#include "SDK\IPanel.h"
#include "SDK\ISurface.h"
#include "SDK\ICollideable.h"
#include "SDK\IEngineTrace.h"
#include "SDK\IMDLCache.h"
#include "SDK\IPhysicsSurfaceProps.h"
#include "SDK\IGlobalVarsBase.h"
#include "SDK\IGameMovement.h"
#include "SDK\INetChannelInfo.h"
#include "SDK\IInput.h"
#include "SDK\IStudioRender.h"
#include "SDK\IViewRender.h"
#include "SDK\CPrediction.h"
#include "SDK\PlayerInfo.h"
#include "SDK\Color.h"
#include "SDK\CRecv.h"
#include "SDK\CViewSetup.h"
#include "SDK\CUtlVector.h"
#include "SDK\Vector.h"
#include "SDK\Studio.h"
#include "SDK\CWeaponInfo.h"
#include "SDK\Convar.h"
#include "SDK\SpoofedConVar.h"
#include "SDK\CTEFireBullets.h"
#include "../IGameEventManager.h"

namespace NSDK {
	class I {
	private:
		typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
		typedef void* (*InstantiateInterfaceFn)();

		static CreateInterfaceFn GetFactory(HMODULE hMod) {
			return (CreateInterfaceFn)GetProcAddress(hMod, XorStr("CreateInterface"));
		}

		template<typename T>
		static T* CaptureInterface(CreateInterfaceFn f, const char* szInterfaceVersion) {
			return (T*)f(szInterfaceVersion, NULL);
		}

		static IVEngineClient *m_pEngine;
		static IClientEntityList *m_pEntityList;
		static ICvar *m_pCvar;
		static IBaseClientDLL *m_pClient;
		static IVModelRender *m_pModelRender;
		static IVModelInfo *m_pModelInfo;
		static IMaterialSystem *m_pMatSystem;
		static IPanel *m_pVGuiPanel;
		static ISurface *m_pVGuiSurface;
		static IVDebugOverlay *m_pDebugOverlay;
		static IClientMode *m_pClientMode;
		static IEngineTrace *m_pEngineTrace;
		static IVRenderView *I::m_pRenderView;
		static IMDLCache *I::m_pMDLCache;
		static IPhysicsSurfaceProps *I::m_pPhysicsProps;
		static IGlobalVarsBase *I::m_pGlobalVars;
		static IGameMovement *I::m_pGameMovement;
		static CPrediction *I::m_pPrediction;
		static IInput *I::m_pInput;
		static IViewRender *I::m_pViewRender;
		static IStudioRender *I::m_pStudioRender;
		static C_TEFireBullets *I::m_pTE_FireBullets;
		static IGameEventManager2 *I::m_pGameEvents;
	public:
		static IVEngineClient* I::Engine();
		static IClientEntityList* I::EntityList();
		static ICvar* I::CVar();
		static IBaseClientDLL* I::Client();
		static IVModelRender* I::ModelRender();
		static IVModelInfo* I::ModelInfo();
		static IMaterialSystem* I::MatSystem();
		static IPanel* I::VGUIPanel();
		static ISurface* I::MatSurface();
		static IVDebugOverlay* I::DebugOverlay();
		static IClientMode* I::ClientMode();
		static IEngineTrace* I::EngineTrace();
		static IVRenderView *I::RenderView();
		static IMDLCache *I::MDLCache();
		static IPhysicsSurfaceProps *I::PhysicsProps();
		static IGlobalVarsBase *I::GlobalVars();
		static IGameMovement *I::GameMovement();
		static CPrediction *I::Prediction();
		static IInput *I::Input();
		static IViewRender *I::ViewRender();
		static IStudioRender *I::StudioRender();
		static C_TEFireBullets *I::TE_FireBullets;
		static IGameEventManager2 *I::GameEvents();
	};
}