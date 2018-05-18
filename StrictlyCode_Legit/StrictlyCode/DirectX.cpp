#pragma once
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#include "DirectX.h"
#include <fstream>
#include "04b.h"
#include "CNotify.h"
#include "ConfigManager.h"
#include "Globals.h"
#include "CSkinChanger.h"

const char *confname = "1";

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
		style.Colors[ImGuiCol_Button] = ImVec4(1, .37f, .20f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1, .37f, .20f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(1, .37f, .20f, 1.00f);
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
		style.Colors[ImGuiCol_Text] = ImVec4(.5, .5, .5, 1.00f);
	}
}

void InitializeTheme()
{
	ImGuiStyle * style = &ImGui::GetStyle();

	style->Alpha = .8f;
	style->WindowPadding = ImVec2(8, 8);
	style->WindowMinSize = ImVec2(32, 32);
	style->WindowRounding = 0.0f;
	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style->ChildWindowRounding = 0.0f;
	style->FramePadding = ImVec2(4, 3);
	style->FrameRounding = 0;
	style->ItemSpacing = ImVec2(6, 3);
	style->ItemInnerSpacing = ImVec2(4, 4);
	style->TouchExtraPadding = ImVec2(0, 0);
	style->IndentSpacing = 21.0f;
	style->ColumnsMinSpacing = 3.0f;
	style->ScrollbarSize = 8.f;
	style->ScrollbarRounding = 0.0f;
	style->GrabMinSize = 20;
	style->GrabRounding = 16;
	style->ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style->DisplayWindowPadding = ImVec2(22, 22);
	style->DisplaySafeAreaPadding = ImVec2(4, 4);
	style->AntiAliasedLines = true;
	style->AntiAliasedShapes = true;
	style->CurveTessellationTol = 1.25f;

	style->Colors[ImGuiCol_Text] = ImVec4(.5, .5, .5, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.176, 0.219, 0.239, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.176, 0.219, 0.239, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ComboBg] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(1, .37f, .20f, 1.00f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.176, 0.219, 0.239, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.176, 0.219, 0.239, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_CloseButton] = ImVec4(0.176, 0.219, 0.239, 0.16f);
	style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.176, 0.219, 0.239, 0.39f);
	style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.176, 0.219, 0.239, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.176, 0.219, 0.239, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.176, 0.219, 0.239, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.176, 0.219, 0.239, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.176, 0.219, 0.239, 0.73f);

	ImGuiIO& io = ImGui::GetIO();
	ImFont* font0 = io.Fonts->AddFontFromMemoryTTF(blocky, blocky_size, 8);
}

void AimbotGeneral()
{
	ImGui::Checkbox(("aimbot##CHECKBOX"), &Options.bAimbot);
	ImGui::Checkbox(("luckshots"), &Options.bLuckShot);
	ImGui::Checkbox(("smoothing"), &Options.bSmoothing);
	ImGui::Checkbox(("backtracking"), &Options.bBacktracking);
}

void AimbotHitboxes()
{
	static const char *hitboxList[] = {
		("Head"), ("Neck"), ("Lower Neck"), ("Pelvis"), ("Stomach"),
		("Upper Stomach"), ("Chest"), ("Upper Chest"), ("Left Thigh"), ("Right Thigh"),
		("Left Shin"), ("Right Shin"), ("Left foot"), ("Right Foot"), ("Left Hand"), ("Right Hand"),("Left Upper Arm"), ("Left Forearm"), ("Right Upper Arm"), ("Right Forearm")
	};
	ImGui::Combo(("hitbox"), &Options.iHitbox, hitboxList, ARRAYSIZE(hitboxList));
}

void AimbotSmoothing()
{
	ImGui::SliderFloat(("aim smoothing"), &Options.fSmoothing, .1f, 1.f);
	ImGui::SliderFloat(("aim fov"), &Options.fNormalFov, 0, 180.f);
	ImGui::SliderInt(("luck shot rate"), &Options.iLuckShotRate, 1, 100);
}

void AimbotRenderTab()
{
	const char* tabs[] = {
		"general",
		"hitboxes",
		"legit",
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
	}
}

void ConfigRenderTab()
{
	static const char *szConfigs[] = { ("legit 1"), ("legit 2") };
	ImGui::Combo(("config"), &Options.iConfig, szConfigs, ARRAYSIZE(szConfigs));
	if (ImGui::Button("save config"))
	{
		ConSys->SaveConfig();
		PushNotifications::Push("Saved Config!");
	}

	if (ImGui::Button("load config"))
	{
		ConSys->LoadConfig();
		PushNotifications::Push("Loaded Config!");
	}
}

void OldMiscTab()
{
	ImGui::Checkbox(("clantag"), &Options.bClantagchanger);
	ImGui::Checkbox(("bhop"), &Options.bBhop);
	ImGui::Checkbox(("chatspam"), &Options.bChatSpam);
}

void MiscRenderTab()
{
	const char* tabs[] = {
		"extras",
		"configs",
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
	ImGui::Checkbox(("health"), &Options.bHealthBar);
	ImGui::Checkbox(("name"), &Options.bPlayerName);
	ImGui::Checkbox(("bone"), &Options.bBoneESP);
	ImGui::Checkbox(("box"), &Options.bBoxESP);
	ImGui::Checkbox(("weapon"), &Options.bWeaponESP);
	ImGui::Checkbox(("sound"), &Options.bSoundESP);
}

void ETCTab()
{
	/*
	ImGui::ColorPicker("team box color", &Options.box_team_color);
	ImGui::ColorPicker("enemy box color", &Options.box_enemy_color);
	ImGui::ColorPicker("enemy name color", &Options.player_name_enemy_color);
	ImGui::ColorPicker("team name color", &Options.player_name_team_color);
	ImGui::ColorPicker("enemy weapon name color", &Options.weapon_enemy_color);
	ImGui::ColorPicker("team weapon name color", &Options.weapon_team_color);
	ImGui::ColorPicker("fov ring color", &Options.fov_ring_color);
	*/
}

void SelfTab()
{
	ImGui::Checkbox(("draw aim fov"), &Options.bFovring);
	ImGui::Checkbox(("skinchanger"), &Options.bSkinchanger);
	if (ImGui::Button("night sky"))
	{
		if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected())
		{
			auto LoadNamedSky = reinterpret_cast<void(__fastcall*)(const char*)>(NSDK::O::FindSignature(("engine.dll"), ("55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45")));
			LoadNamedSky("sky_csgo_night02");
		}
	}
	if (Options.bSkinchanger && NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected())
	{
		auto g_Local = CBaseEntity::GetLocalPlayer();
		if (g_Local->IsAlive() && g_Local)
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
	ImGui::SliderInt("fov changer", &Options.iLocalFov, 0, 120);
}

void GeneralVisualsTab()
{
	const char* tabs[] = {
		"esp",
		"self",
		"colors",
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

	bool g_IsInitialized = false;

	HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice)
	{
		if (!g_IsInitialized)
		{
			ImGui_ImplDX9_Init(g_hWindow, pDevice);

			InitializeTheme();

			g_IsInitialized = true;
		}
		else
		{
			ImGui::GetIO().MouseDrawCursor = Options.bShowMenu;

			//Begins a new ImGui frame.
			ImGui_ImplDX9_NewFrame();

			if (Options.bShowMenu)
			{
				ImGui::SetNextWindowSize(ImVec2(600, 400));
				if (ImGui::Begin(cheat_name, &Options.bShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
				{
					const char* tabs[] = {
						"aim",
						"visuals",
						"misc",
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

		auto hr = g_fnOriginalReset(pDevice, pPresentationParameters);
		ImGui_ImplDX9_CreateDeviceObjects();
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