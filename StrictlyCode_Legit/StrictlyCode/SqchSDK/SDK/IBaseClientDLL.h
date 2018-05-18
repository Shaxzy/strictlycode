#pragma once

#include "CClientClass.h"

namespace NSDK {
	class IBaseClientDLL {
	public:
		ClientClass* GetAllClasses() {
			typedef ClientClass*(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 8)(this);
		}
	};
	class CHudChat
	{
	public:
		void ChatPrintf(int iPlayerIndex, int iFilter, const char* fmt, ...)
		{
			CallVFunction<void(__cdecl*)(void*, int, int, const char*, ...)>(this, 26)(this, iPlayerIndex, iFilter, fmt);
		}
	};
}