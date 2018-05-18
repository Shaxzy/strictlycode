#pragma once

#include <iostream>
#include "..\SDKHelper\Utilities.h"
#include "Color.h"

namespace NSDK {
	class ConCommandBase;
	class ConCommand;
	class ConVar;

	typedef int CVarDLLIdentifier_t;

	class ICvar {
	public:
		CVarDLLIdentifier_t AllocateDLLIdentifier() {
			typedef CVarDLLIdentifier_t(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 9)(this);
		}

		void RegisterConCommand(ConCommandBase *pCommandBase) {
			typedef void(__thiscall *OrigFn)(void*, ConCommandBase *);
			CallVFunction<OrigFn>(this, 10)(this, pCommandBase);
		}

		void UnregisterConCommand(ConCommandBase *pCommandBase) {
			typedef void(__thiscall *OrigFn)(void*, ConCommandBase *);
			CallVFunction<OrigFn>(this, 11)(this, pCommandBase);
		}

		void UnregisterConCommands(CVarDLLIdentifier_t id) {
			typedef void(__thiscall *OrigFn)(void*, CVarDLLIdentifier_t);
			CallVFunction<OrigFn>(this, 12)(this, id);
		}

		ConVar* FindVar(const char *var_name) {
			typedef ConVar*(__thiscall *OrigFn)(void*, const char *);
			return CallVFunction<OrigFn>(this, 16)(this, var_name);
		}

		void CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) {
			typedef void(__thiscall *OrigFn)(void*, ConVar *, const char *, float);
			CallVFunction<OrigFn>(this, 22)(this, var, pOldString, flOldValue);
		}

		void ConsoleColorPrintf(const Color& clr, const char *pFormat, ...)
		{
			char buffer[1024];
			va_list list;
			va_start(list, pFormat);
			vsprintf_s(buffer, pFormat, list);
			va_end(list);
			typedef void(__cdecl *OrigFn)(void*, const Color&, const char *, va_list);
			CallVFunction<OrigFn>(this, 25)(this, clr, buffer, list);
		}

		void ConsolePrintf(const char *pFormat, ...)
		{
			char buffer[1024];
			va_list list;
			va_start(list, pFormat);
			vsprintf_s(buffer, pFormat, list);
			va_end(list);
			typedef void(__cdecl *OrigFn)(void*, const char *, va_list);
			CallVFunction<OrigFn>(this, 26)(this, buffer, list);
		}
	};
}