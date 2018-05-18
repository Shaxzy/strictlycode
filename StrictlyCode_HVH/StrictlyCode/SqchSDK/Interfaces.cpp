#include "Interfaces.h"
#include "Offsets.h"
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
	IViewRenderBeams *I::m_pRenderBeams = nullptr;
	CHudChat *I::m_pHudChat = nullptr;
	CCenterPrint *I::m_pToastAlert = nullptr;
	CClientState *I::m_pClientState = nullptr;

	IVEngineClient* I::Engine() {
		if (!m_pEngine) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("engine.dll")));
			m_pEngine = CaptureInterface<IVEngineClient>(pfnFactory,  ("VEngineClient014"));
		}
		return m_pEngine;
	}

	IClientEntityList* I::EntityList() {
		if (!m_pEntityList) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("client.dll")));
			m_pEntityList = CaptureInterface<IClientEntityList>(pfnFactory,  ("VClientEntityList003"));
		}
		return m_pEntityList;
	}

	ICvar* I::CVar() {
		if (!m_pCvar) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("vstdlib.dll")));
			m_pCvar = CaptureInterface<ICvar>(pfnFactory,  ("VEngineCvar007"));
		}
		return m_pCvar;
	}

	IBaseClientDLL* I::Client() {
		if (!m_pClient) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("client.dll")));
			m_pClient = CaptureInterface<IBaseClientDLL>(pfnFactory,  ("VClient018"));
		}
		return m_pClient;
	}

	IVModelRender* I::ModelRender() {
		if (!m_pModelRender) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("engine.dll")));
			m_pModelRender = CaptureInterface<IVModelRender>(pfnFactory,  ("VEngineModel016"));
		}
		return m_pModelRender;
	}

	IVModelInfo* I::ModelInfo() {
		if (!m_pModelInfo) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("engine.dll")));
			m_pModelInfo = CaptureInterface<IVModelInfo>(pfnFactory,  ("VModelInfoClient004"));
		}
		return m_pModelInfo;
	}

	IMaterialSystem* I::MatSystem() {
		if (!m_pMatSystem) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("materialsystem.dll")));
			m_pMatSystem = CaptureInterface<IMaterialSystem>(pfnFactory,  ("VMaterialSystem080"));
		}
		return m_pMatSystem;
	}

	IPanel* I::VGUIPanel() {
		if (!m_pVGuiPanel) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("vgui2.dll")));
			m_pVGuiPanel = CaptureInterface<IPanel>(pfnFactory,  ("VGUI_Panel009"));
		}
		return m_pVGuiPanel;
	}

	ISurface* I::MatSurface() {
		if (!m_pVGuiSurface) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("vguimatsurface.dll")));
			m_pVGuiSurface = CaptureInterface<ISurface>(pfnFactory,  ("VGUI_Surface031"));
		}
		return m_pVGuiSurface;
	}

	IVDebugOverlay* I::DebugOverlay() {
		if (!m_pDebugOverlay) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("engine.dll")));
			m_pDebugOverlay = CaptureInterface<IVDebugOverlay>(pfnFactory,  ("VDebugOverlay004"));
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
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("engine.dll")));
			m_pEngineTrace = CaptureInterface<IEngineTrace>(pfnFactory,  ("EngineTraceClient004"));
		}
		return m_pEngineTrace;
	}

	/*CGlowObjectManager *I::GlowManager() {
		if (!m_pGlowPointer) {
			m_pGlowPointer = (CGlowObjectManager*)(*(DWORD*)(NSDK::O::FindSignature("client.dll", "0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00") + 0x3));
		}
		return m_pGlowPointer;
	}
	*/

	IVRenderView *I::RenderView() {
		if (!m_pRenderView) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("engine.dll")));
			m_pRenderView = CaptureInterface<IVRenderView>(pfnFactory,  ("VEngineRenderView014"));
		}
		return m_pRenderView;
	}

	IMDLCache* I::MDLCache() {
		if (!m_pMDLCache) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("datacache.dll")));
			m_pMDLCache = CaptureInterface<IMDLCache>(pfnFactory,  ("MDLCache004"));
		}
		return m_pMDLCache;
	}

	IPhysicsSurfaceProps* I::PhysicsProps() {
		if (!m_pPhysicsProps) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("vphysics.dll")));
			m_pPhysicsProps = CaptureInterface<IPhysicsSurfaceProps>(pfnFactory,  ("VPhysicsSurfaceProps001"));
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
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("client.dll")));
			m_pGameMovement = CaptureInterface<IGameMovement>(pfnFactory,  ("GameMovement001"));
		}
		return m_pGameMovement;
	}

	CPrediction* I::Prediction() {
		if (!m_pPrediction) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("client.dll")));
			m_pPrediction = CaptureInterface<CPrediction>(pfnFactory,  ("VClientPrediction001"));
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
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("engine.dll")));
			m_pViewRender = CaptureInterface<IViewRender>(pfnFactory,  ("VEngineRenderView014"));
		}
		return m_pViewRender;
	}

	IStudioRender* I::StudioRender() {
		if (!m_pStudioRender) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("studiorender.dll")));
			m_pStudioRender = CaptureInterface<IStudioRender>(pfnFactory,  ("VStudioRender026"));
		}
		return m_pStudioRender;
	}

	IGameEventManager2* I::GameEvents() {
		if (!m_pGameEvents) {
			CreateInterfaceFn pfnFactory = GetFactory(GetModuleHandleA( ("engine.dll")));
			m_pGameEvents = CaptureInterface<IGameEventManager2>(pfnFactory,  ("GAMEEVENTSMANAGER002"));
		}
		return m_pGameEvents;
	}

	IViewRenderBeams* I::RenderBeams() {
		if (!m_pRenderBeams) {
			m_pRenderBeams = *(IViewRenderBeams**)(NSDK::O::FindSignature("client.dll", "B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9") + 1);
		}
		return m_pRenderBeams;
	}

	CHudChat* I::HudChat() {
		if (!m_pHudChat) {
			m_pHudChat = FindHudElement<CHudChat>("CHudChat");
		}
		return m_pHudChat;
	}

	CCenterPrint* I::ToastAlert() {
		if (!m_pToastAlert) {
			m_pToastAlert = *(CCenterPrint**)(NSDK::O::FindSignature("client.dll", "A1 ? ? ? ? B9 ? ? ? ? FF 50 1C E8")+ 6);
		}
		return m_pToastAlert;
	}

	CClientState* I::ClientState() {
		if (!m_pClientState) {
			m_pClientState = **reinterpret_cast< CClientState*** > ((*reinterpret_cast< uintptr_t** > (NSDK::I::Engine()))[12] + 0x10);
		}
		return m_pClientState;
	}
}