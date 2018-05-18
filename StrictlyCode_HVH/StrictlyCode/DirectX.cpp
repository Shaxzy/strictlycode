#pragma once
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#include "DirectX.h"
#include "CParticles.h"
#include <fstream>
#include "04b.h"
#include "qsl.h"
#include "CNotify.h"
#include "ConfigManager.h"
#include "Globals.h"
#include "CSkinChanger.h"
#include "edition.h"
#include <chrono>
ImFont* font0;

typedef void(*CL_FullUpdate_t) (void);
CL_FullUpdate_t CL_FullUpdate = nullptr;

void FullUpdate()
{
	static auto CL_FullUpdate = reinterpret_cast<CL_FullUpdate_t>(NSDK::O::FindPattern("engine.dll", reinterpret_cast<PBYTE>("\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56\xFF\x50\x14\x8B\x34\x85"), "x????x????xxxxxxx"));
	CL_FullUpdate();
}

bool is_file_exist(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void buttonColor(bool bActive)
{
	ImGuiStyle& style = ImGui::GetStyle();

	if (bActive)
	{
		style.Colors[ImGuiCol_Button] = ImVec4(0.863, 0.145, 0.322, 0.83f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(.863, 0.145, 0.322, 0.83f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.863, 0.145, 0.322, 0.83f);
	}
	else
	{
		style.Colors[ImGuiCol_Button] = ImVec4(0.176, 0.219, 0.239, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.176, 0.219, 0.239, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	}
}


void textColor(bool bActive)
{
	ImGuiStyle& style = ImGui::GetStyle();

	if (bActive)
	{
		style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
	}
	else
	{
		style.Colors[ImGuiCol_Text] = ImVec4(0.521, 0.521, 0.521, 1);
	}
}

void InitializeTheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImColor mainColor = ImColor(int(54), int(54), int(54), 255);
	ImColor bodyColor = ImColor(int(24), int(24), int(24), 255);
	ImColor fontColor = ImColor(int(255), int(255), int(255), 255);
	ImVec4 mainColorHovered = ImVec4(mainColor.Value.x + 0.1f, mainColor.Value.y + 0.1f, mainColor.Value.z + 0.1f, mainColor.Value.w);
	ImVec4 mainColorActive = ImVec4(mainColor.Value.x + 0.2f, mainColor.Value.y + 0.2f, mainColor.Value.z + 0.2f, mainColor.Value.w);
	ImVec4 menubarColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w - 0.8f);
	ImVec4 frameBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .1f);
	ImVec4 tooltipBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .05f);

	style.Alpha = .8f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 3);
	style.FrameRounding = 0;
	style.ItemSpacing = ImVec2(6, 3);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 8.f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 20;
	style.GrabRounding = 16;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.109, 0.125, 0.141, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.18f, 0.18f, 0.18f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.05f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.10f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.863, 0.145, 0.322, 0.83f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.863, 0.145, 0.322, 0.83f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.09f, 0.09f, 0.20f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.10f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.77f, 0.21f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.10f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.651, 0.157, 0.282, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.21f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

	ImGuiIO& io = ImGui::GetIO();
	font0 = io.Fonts->AddFontFromMemoryTTF(blocky, blocky_size, 8);
}

void AimbotGeneral()
{
	ImGui::Checkbox(("Aimbot##BUTTON"), &Options.bAimbot);
	ImGui::Checkbox(("Auto Shoot"), &Options.bAutoShoot);
	ImGui::Checkbox(("Auto Scope"), &Options.bAutoScope);
	ImGui::Checkbox(("Auto Slow"), &Options.bAutoSlow);
	ImGui::Separator();
	ImGui::Checkbox(("LBY Backtrack"), &Options.bLBYBacktrack);
	if (Options.bLBYBacktrack)
	{
		ImGui::Checkbox(("Accurate LBY History"), &Options.bLBYUpdate);
	}
	ImGui::Separator();
}

void AimbotHitboxes()
{
	static const char *hitboxList[] = {
		("Head"), ("Neck"), ("Lower Neck"), ("Pelvis"), ("Stomach"),
		("Upper Stomach"), ("Chest"), ("Upper Chest"), ("Left Thigh"), ("Right Thigh"),
		("Left Shin"), ("Right Shin"), ("Left foot"), ("Right Foot"), ("Left Hand"), ("Right Hand"),("Left Upper Arm"), ("Left Forearm"), ("Right Upper Arm"), ("Right Forearm"),
	};
	ImGui::Combo(("Main Hitbox"), &Options.iHitbox, hitboxList, ARRAYSIZE(hitboxList));

	ImGui::Checkbox(("Hitscan Selected"), &Options.bHitscan);
	if (Options.bHitscan)
	{
		ImGui::Text("Hitscan:");
		ImGui::BeginChild("#multipoint", ImVec2(0, 200), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
		for (int i = 0; i < ARRAYSIZE(hitboxList); ++i)
		{
			ImGui::Selectable(hitboxList[i], &Options.HitscanBoxes[i]);
		}
		ImGui::EndChild();
	}
}

void AimbotSmoothing()
{
	ImGui::SliderFloat(("Aimbot FOV"), &Options.fAimbotFov, 0, 180.f);
	ImGui::SliderFloat("Minimum Autowall Damage", &Options.fAwall, 0, 100);
	ImGui::SliderInt("Hitchance", &Options.iHitchance, 0, 100);
}

void AntiAimTab()
{
	static const char *AntiAims[] = {
		"Manual", "LBY", "Freestanding"
	};

	ImGui::Combo(("Anti Aim Type"), &Options.iAntiAim, AntiAims, ARRAYSIZE(AntiAims));

	static const char *LbyTypes[] = {
		"Fake", "Delta"
	};

	ImGui::Combo(("LBY Fake Type"), &Options.iLBYType, LbyTypes, ARRAYSIZE(LbyTypes));
	if (Options.iLBYType == 1)
	{
		ImGui::SliderFloat("LBY Delta", &Options.fLBYDelta, 0, 180);
	}
}

void AimbotRenderTab()
{
	const char* tabs[] = {
		"General",
		"Hitboxes",
		"Etc",
		"HVH"
	};

	//Checkboxes tab
	static int aimbotIndex = 0;
	 
	for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
	{
		int distance = i == aimbotIndex ? 0 : i > aimbotIndex ? i - aimbotIndex : aimbotIndex - i;

		buttonColor(aimbotIndex == i);
		textColor(aimbotIndex == i);

		if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
			aimbotIndex = i;

		textColor(true);
		buttonColor(false);
		if (i < IM_ARRAYSIZE(tabs) - 1)
			ImGui::SameLine();
	}
	 
	ImGui::Separator();
	switch (aimbotIndex)
	{
	case 0:
		AimbotGeneral();
		break;
	case 1:
		AimbotHitboxes();
		break;
	case 2:
		AimbotSmoothing();
		break;
	case 3:
		AntiAimTab();
		break;
	}
}

void ConfigRenderTab()
{
	static const char *szConfigs[] = { ("HVH 1"), ("HVH 2") };
	ImGui::Combo(("Config"), &Options.iConfig, szConfigs, ARRAYSIZE(szConfigs));
	if (ImGui::Button("Save Config"))
	{
		ConSys->SaveConfig();
		PushNotifications::Push("Saved Config!");
	}

	if (ImGui::Button("Load Config"))
	{
		ConSys->LoadConfig();
		PushNotifications::Push("Loaded Config!");
	}
}

void OldMiscTab()
{
	ImGui::Checkbox(("Enable clantags"), &Options.bClantagchanger);
	ImGui::Checkbox(("Bhop"), &Options.bBhop);
	ImGui::Checkbox(("Chatspam"), &Options.bChatSpam);
	ImGui::Checkbox(("Chat Settings"), &Options.bTextSettings);
	ImGui::Checkbox(("Trashtalk"), &Options.bTrashTalk);
}

void MiscRenderTab()
{
	const char* tabs[] = {
		"Extras",
		"Configs",
	};
	static int miscIndex = 0;
	 
	for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
	{
		int distance = i == miscIndex ? 0 : i > miscIndex ? i - miscIndex : miscIndex - i;

		buttonColor(miscIndex == i);
		textColor(miscIndex == i);

		if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
			miscIndex = i;

		textColor(true);
		buttonColor(false);
		if (i < IM_ARRAYSIZE(tabs) - 1)
			ImGui::SameLine();
	}
	 
	ImGui::Separator();
	switch (miscIndex)
	{
	case 0:
		OldMiscTab();
		break;
	case 1:
		ConfigRenderTab();
		break;
	}
}

void ESPTab()
{
		ImGui::Checkbox(("Health"), &Options.bHealthBar);
		ImGui::Checkbox(("Name"), &Options.bPlayerName);
		ImGui::Checkbox(("Bone"), &Options.bBoneESP);
		ImGui::Checkbox(("Box"), &Options.bBoxESP);
		ImGui::Checkbox(("Weapon"), &Options.bWeaponESP);
		ImGui::Checkbox(("Resolver"), &Options.bResolverESP);
		ImGui::Checkbox(("Info"), &Options.bInfoESP);
}

void ETCTab()
{
	static const char *tracers[] = { ("Line"), ("Beam") };
	ImGui::Combo(("Tracer Type"), &Options.iTracer, tracers, ARRAYSIZE(tracers));
	ImGui::Checkbox(("Thirdperson"), &Options.bThirdperson);
}

void SelfTab()
{
	ImGui::Checkbox(("Draw Aimbot FOV"), &Options.bFovring);
	ImGui::Checkbox(("Skinchanger"), &Options.bSkinchanger);
	if (Options.bSkinchanger && NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected())
	{
		auto g_Local = CBaseEntity::GetLocalPlayer();
		if(g_Local->IsAlive() && g_Local)
		{
			auto curWep = g_Local->GetActiveWeapon();
			if (curWep)
			{
				ImGui::Separator();
				int idx = *curWep->GetItemDefinitionIndex();
				ImGui::InputInt("PaintKit ID", &g_SkinChangerCfg[idx].nFallbackPaintKit, 1, 3);
				ImGui::SliderFloat("Wear", &g_SkinChangerCfg[idx].flFallbackWear, .000001f, .999999f);
				ImGui::InputInt("Seed", &g_SkinChangerCfg[idx].nFallbackSeed, 1, 3);
				if (idx == NSDK::weapon_knife_t || idx == NSDK::weapon_knife)
				{
					//add knife changer options (no knife changer yet)
					//ImGui::InputInt("Knife Model", &g_SkinChangerCfg[idx].modelIndex, 1, 3);
					//idk any knife models so gg
					static const char *szKnife[] = { ("Knife"), ("Knife T"), ("Bayonet"), ("Flip"), ("Gut"), ("Karambit"), ("M9 Bayonet") };
					ImGui::Combo(("Knife"), &g_SkinChangerCfg[idx].knifeType, szKnife, ARRAYSIZE(szKnife));
				}
				if (ImGui::Button("Update Skins")) 
				{
					FullUpdate();
				}
				ImGui::Separator();
			}

		}
	}
	ImGui::SliderInt("FOV Changer", &Options.iLocalFov, 0, 120);
}

void GeneralVisualsTab()
{
	const char* tabs[] = {
		"ESP",
		"SELF",
		"ETC",
	};
	static int visualsIndex = 0;
	 
	for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
	{
		int distance = i == visualsIndex ? 0 : i > visualsIndex ? i - visualsIndex : visualsIndex - i;

		buttonColor(visualsIndex == i);
		textColor(visualsIndex == i);

		if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
			visualsIndex = i;

		textColor(true);
		buttonColor(false);

		if (i < IM_ARRAYSIZE(tabs) - 1)
			ImGui::SameLine();
	}
	 
	ImGui::Separator();
	switch (visualsIndex)
	{
	case 0:
		ESPTab();
		break;
	case 1:
		SelfTab();
		break;
	case 2:
		ETCTab();
		break;
	}
}


namespace DirectX
{
	EndScene_t g_fnOriginalEndScene;
	Reset_t g_fnOriginalReset;

	WNDPROC g_pOldWindowProc;
	HWND g_hWindow;

	static bool g_IsInitialized = false;

	HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice)
	{
		if (!g_IsInitialized)
		{
			ImGui_ImplDX9_Init(g_hWindow, pDevice);

			InitializeTheme();

			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->Build();

			g_IsInitialized = true;
		}
		else
		{
			ImGui::GetIO().MouseDrawCursor = Options.bShowMenu;

			//Begins a new ImGui frame.
			ImGui_ImplDX9_NewFrame();

			if (Options.bShowMenu)
			{
				//broken
				//dot_draw();
				ImGui::SetNextWindowSize(ImVec2(480, 320));
				if (ImGui::Begin(cheat_name, &Options.bShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
				{
					const char* tabs[] = {
						"Aimbot",
						"Visuals",
						"Misc",
					};
					static int page = 0;
					for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
					{
							int distance = i == page ? 0 : i > page ? i - page : page - i;
							
							buttonColor(page == i);
							textColor(page == i);
							if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
							{
								page = i;
							}
							textColor(true);
							buttonColor(false);
						if (i < IM_ARRAYSIZE(tabs) - 1)
							ImGui::SameLine();
					}
					ImGui::Separator();
					switch (page)
					{
					case 0:
						AimbotRenderTab();
						break;
					case 1:
						GeneralVisualsTab();
						break;
					case 2:
						MiscRenderTab();
						break;
					}

					ImGui::End();
				}
			}

			ImGui::Render();
		}

		return g_fnOriginalEndScene(pDevice);
	}

	HRESULT __stdcall Hooked_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{
		if (!g_IsInitialized) return g_fnOriginalReset(pDevice, pPresentationParameters);

		ImGui_ImplDX9_InvalidateDeviceObjects();

		_drawList = nullptr;

		auto hr = g_fnOriginalReset(pDevice, pPresentationParameters);
		ImGui_ImplDX9_CreateDeviceObjects();

		_drawList = new ImDrawList();

		return hr;
	}

	LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
			Options.vecPressedKeys[VK_LBUTTON] = true;
			break;
		case WM_LBUTTONUP:
			Options.vecPressedKeys[VK_LBUTTON] = false;
			break;
		case WM_RBUTTONDOWN:
			Options.vecPressedKeys[VK_RBUTTON] = true;
			break;
		case WM_RBUTTONUP:
			Options.vecPressedKeys[VK_RBUTTON] = false;
			break;
		case WM_KEYDOWN:
			Options.vecPressedKeys[wParam] = true;
			break;
		case WM_KEYUP:
			Options.vecPressedKeys[wParam] = false;
			break;
		default: break;
		}

		static NSDK::ConVar *conMouseEnable = NSDK::I::CVar()->FindVar(("cl_mouseenable"));
		static bool isDown = false;
		static bool isClicked = false;

		if (Options.vecPressedKeys[VK_INSERT])
		{
			isClicked = false;
			isDown = true;
		}

		else if (!Options.vecPressedKeys[VK_INSERT] && isDown)
		{
			isClicked = true;
			isDown = false;
		}

		else
		{
			isClicked = false;
			isDown = false;
		}

		if (isClicked)
		{
			Options.bShowMenu = !Options.bShowMenu;
			conMouseEnable->SetValue(!Options.bShowMenu);
		}


		if (g_IsInitialized && Options.bShowMenu && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		return CallWindowProc(g_pOldWindowProc, hWnd, uMsg, wParam, lParam);
	}
}