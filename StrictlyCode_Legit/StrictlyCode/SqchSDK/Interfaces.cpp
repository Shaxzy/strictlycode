#include "Interfaces.h"

namespace NSDK {
	IVEngineClient *I::m_pEngine = nullptr;
	IClientEntityList *I::m_pEntityList = nullptr;
	ICvar *I::m_pCvar = nullptr;
	IBaseClientDLL *I::m_pClient = nullptr;
	IVModelRender *I::m_pModelRender = nullptr;
	IVModelInfo *I::m_pModelInfo = nullptr;
	IMaterialSystem *I::m_pMatSystem = nullptr;
	IPanel *I::m_pVGuiPanel = nullptr;
	ISurface *I::m_pVGuiSurface = nullptr;
	IVDebugOverlay *I::m_pDebugOverlay = nullptr;
	IClientMode *I::m_pClientMode = nullptr;
	IEngineTrace *I::m_pEngineTrace = nullptr;
	IVRenderView *I::m_pRenderView = nullptr;
	IMDLCache *I::m_pMDLCache = nullptr;
	IPhysicsSurfaceProps *I::m_pPhysicsProps = nullptr;
	IGlobalVarsBase *I::m_pGlobalVars = nullptr;
	IGameMovement *I::m_pGameMovement = nullptr;
	CPrediction *I::m_pPrediction = nullptr;
	IInput *I::m_pInput = nullptr;
	IViewRender *I::m_pViewRender = nullptr;
	IStudioRender *I::m_pStudioRender = nullptr;
	C_TEFireBullets *I::m_pTE_FireBullets = nullptr;
	IGameEventManager2 *I::m_pGameEvents = nullptr;

	IVEngineClient* I::Engine() {
		if (!m_pEngine) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("engine.dll")));
			m_pEngine = CaptureInterface<IVEngineClient>(pfnFactory, XorStr("VEngineClient014"));
		}
		return m_pEngine;
	}

	IClientEntityList* I::EntityList() {
		if (!m_pEntityList) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("client.dll")));
			m_pEntityList = CaptureInterface<IClientEntityList>(pfnFactory, XorStr("VClientEntityList003"));
		}
		return m_pEntityList;
	}

	ICvar* I::CVar() {
		if (!m_pCvar) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("vstdlib.dll")));
			m_pCvar = CaptureInterface<ICvar>(pfnFactory, XorStr("VEngineCvar007"));
		}
		return m_pCvar;
	}

	IBaseClientDLL* I::Client() {
		if (!m_pClient) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("client.dll")));
			m_pClient = CaptureInterface<IBaseClientDLL>(pfnFactory, XorStr("VClient018"));
		}
		return m_pClient;
	}

	IVModelRender* I::ModelRender() {
		if (!m_pModelRender) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("engine.dll")));
			m_pModelRender = CaptureInterface<IVModelRender>(pfnFactory, XorStr("VEngineModel016"));
		}
		return m_pModelRender;
	}

	IVModelInfo* I::ModelInfo() {
		if (!m_pModelInfo) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("engine.dll")));
			m_pModelInfo = CaptureInterface<IVModelInfo>(pfnFactory, XorStr("VModelInfoClient004"));
		}
		return m_pModelInfo;
	}

	IMaterialSystem* I::MatSystem() {
		if (!m_pMatSystem) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("materialsystem.dll")));
			m_pMatSystem = CaptureInterface<IMaterialSystem>(pfnFactory, XorStr("VMaterialSystem080"));
		}
		return m_pMatSystem;
	}

	IPanel* I::VGUIPanel() {
		if (!m_pVGuiPanel) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("vgui2.dll")));
			m_pVGuiPanel = CaptureInterface<IPanel>(pfnFactory, XorStr("VGUI_Panel009"));
		}
		return m_pVGuiPanel;
	}

	ISurface* I::MatSurface() {
		if (!m_pVGuiSurface) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("vguimatsurface.dll")));
			m_pVGuiSurface = CaptureInterface<ISurface>(pfnFactory, XorStr("VGUI_Surface031"));
		}
		return m_pVGuiSurface;
	}

	IVDebugOverlay* I::DebugOverlay() {
		if (!m_pDebugOverlay) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("engine.dll")));
			m_pDebugOverlay = CaptureInterface<IVDebugOverlay>(pfnFactory, XorStr("VDebugOverlay004"));
		}
		return m_pDebugOverlay;
	}

	IClientMode* I::ClientMode() {
		if (!m_pClientMode) {
			m_pClientMode = **(IClientMode***)((*(DWORD**)I::Client())[10] + 0x5);
		}
		return m_pClientMode;
	}

	IEngineTrace* I::EngineTrace() {
		if (!m_pEngineTrace) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("engine.dll")));
			m_pEngineTrace = CaptureInterface<IEngineTrace>(pfnFactory, XorStr("EngineTraceClient004"));
		}
		return m_pEngineTrace;
	}

	IVRenderView *I::RenderView() {
		if (!m_pRenderView) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("engine.dll")));
			m_pRenderView = CaptureInterface<IVRenderView>(pfnFactory, XorStr("VEngineRenderView014"));
		}
		return m_pRenderView;
	}

	IMDLCache* I::MDLCache() {
		if (!m_pMDLCache) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("datacache.dll")));
			m_pMDLCache = CaptureInterface<IMDLCache>(pfnFactory, XorStr("MDLCache004"));
		}
		return m_pMDLCache;
	}

	IPhysicsSurfaceProps* I::PhysicsProps() {
		if (!m_pPhysicsProps) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("vphysics.dll")));
			m_pPhysicsProps = CaptureInterface<IPhysicsSurfaceProps>(pfnFactory, XorStr("VPhysicsSurfaceProps001"));
		}
		return m_pPhysicsProps;
	}

	IGlobalVarsBase* I::GlobalVars() {
		if (!m_pGlobalVars) {
			m_pGlobalVars = **(IGlobalVarsBase***)((*(DWORD**)I::Client())[0] + 0x1B);
		}
		return m_pGlobalVars;
	}

	IGameMovement* I::GameMovement() {
		if (!m_pGameMovement) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("client.dll")));
			m_pGameMovement = CaptureInterface<IGameMovement>(pfnFactory, XorStr("GameMovement001"));
		}
		return m_pGameMovement;
	}

	CPrediction* I::Prediction() {
		if (!m_pPrediction) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("client.dll")));
			m_pPrediction = CaptureInterface<CPrediction>(pfnFactory, XorStr("VClientPrediction001"));
		}
		return m_pPrediction;
	}

	IInput* I::Input() {
		if (!m_pInput) {
			m_pInput = *(IInput**)((*(DWORD**)Client())[15] + 0x1);
		}
		return m_pInput;
	}

	IViewRender* I::ViewRender() {
		if (!m_pViewRender) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("engine.dll")));
			m_pViewRender = CaptureInterface<IViewRender>(pfnFactory, XorStr("VEngineRenderView014"));
		}
		return m_pViewRender;
	}

	IStudioRender* I::StudioRender() {
		if (!m_pStudioRender) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("studiorender.dll")));
			m_pStudioRender = CaptureInterface<IStudioRender>(pfnFactory, XorStr("VStudioRender026"));
		}
		return m_pStudioRender;
	}

	IGameEventManager2* I::GameEvents() {
		if (!m_pGameEvents) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA(XorStr("engine.dll")));
			m_pGameEvents = CaptureInterface<IGameEventManager2>(pfnFactory, XorStr("GAMEEVENTSMANAGER002"));
		}
		return m_pGameEvents;
	}
}