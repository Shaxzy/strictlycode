#pragma once

#include "CClientClass.h"
#include "../../CClientState.h"
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
		/*
		Default: \x01
		Dark Red: \x02
		Purple: \x03
		Green: \x04
		Light Green: \x05
		Lime Green: \x06
		Red: \x07
		Grey: \x08
		Orange: \x09
		*/
		void ChatPrintf(int iPlayerIndex, int iFilter, const char* fmt, ...)
		{
				std::string logo = " \x02 [strictlycode] \x05";
				logo += fmt;
				const char *final_text = logo.c_str();

			CallVFunction<void(__cdecl*)(void*, int, int, const char*, ...)>(this, 26)(this, iPlayerIndex, iFilter, final_text);
		}
	};

	class CCenterPrint
	{
	public:
		virtual void* Create(unsigned long long unknown) = 0;
		virtual int Destroy() = 0;
		virtual int	SetTextColor(int, int, int, int) = 0;
		virtual void Print(char16_t*) = 0;
		virtual int	PrintW(wchar_t*) = 0;
		virtual void ColorPrint(int, int, int, int, char16_t *) = 0;
		virtual int	 ColorPrintW(int, int, int, int, wchar_t*) = 0;
		virtual int	Clear() = 0;
	};
}