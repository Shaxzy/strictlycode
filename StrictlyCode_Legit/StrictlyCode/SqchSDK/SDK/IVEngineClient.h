#pragma once

#include "..\SDKHelper\Utilities.h"
#include "VMatrix.h"
#include "PlayerInfo.h"
#include "INetChannelInfo.h"

namespace NSDK {
	class IVEngineClient {
	public:
		void GetScreenSize(int& width, int& height) {
			typedef int(__thiscall *OrigFn)(void*, int&, int&);
			CallVFunction<OrigFn>(this, 5)(this, width, height);
		}

		bool GetPlayerInfo(int ent_num, PlayerInfo *pinfo) {
			typedef bool(__thiscall *OrigFn)(void*, int, PlayerInfo*);
			return CallVFunction<OrigFn>(this, 8)(this, ent_num, pinfo);
		}
		int GetPlayerUserID(int userID) {
			typedef int(__thiscall *OrigFn)(void*, int);
			return CallVFunction<OrigFn>(this, 9)(this, userID);
		}

		int GetLocalPlayer() {
			typedef int(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 12)(this);
		}

		float GetLastTimeStamp() {
			typedef float(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 14)(this);
		}

		void GetViewAngles(QAngle& va) {
			typedef void(__thiscall *OrigFn)(void*, QAngle&);
			CallVFunction<OrigFn>(this, 18)(this, va);
		}

		void SetViewAngles(QAngle& va) {
			typedef void(__thiscall *OrigFn)(void*, QAngle&);
			CallVFunction<OrigFn>(this, 19)(this, va);
		}

		int GetMaxClients() {
			typedef int(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 20)(this);
		}

		bool isInGame() {
			typedef bool(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 26)(this);
		}

		bool isConnected() {
			typedef bool(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 27)(this);
		}

		const VMatrix& WorldToScreenMatrix() {
			typedef const VMatrix&(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 37)(this);
		}

		INetChannelInfo	*GetNetChannelInfo() {
			typedef INetChannelInfo*(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 78)(this);
		}

		void ExecuteClientCmd(const char* szCmdString) {
			typedef void(__thiscall *OrigFn)(void*, const char *);
			CallVFunction<OrigFn>(this, 108)(this, szCmdString);
		}

		unsigned int GetEngineBuildNumber()

		{
			typedef unsigned int(__thiscall* OrigFn)(PVOID);
			return CallVFunction<OrigFn>(this, 104)(this);

		}
		void ClientCmd_Unrestricted(const char* szCmdString)
		{
			typedef void(__thiscall* OrigFn)(void*, const char*, char);
			CallVFunction<OrigFn>(this, 114)(this, szCmdString, 1);
		}
	};
}