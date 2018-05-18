#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "rayGUI\imgui.h"
#include "rayGUI\DX9\imgui_impl_dx9.h"

#include "EntityStructs.h"
#include "Utilities.h"

#include "OptionsManager.h"

#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace DirectX {
	typedef long(__stdcall* EndScene_t)(IDirect3DDevice9* device);
	typedef long(__stdcall* Reset_t)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp);

	extern EndScene_t g_fnOriginalEndScene;
	extern Reset_t g_fnOriginalReset;

	extern WNDPROC g_pOldWindowProc;
	extern HWND g_hWindow;

	HRESULT   __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice);
	HRESULT   __stdcall Hooked_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	LRESULT   __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}