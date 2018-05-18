#pragma once

#include "SDKHelper\Utilities.h"
#include "SDK\CGlowObjectManager.h"
#include "SDK\IMoveHelper.h"
#include "SDK\IViewRender.h"
#include "SDKHelper\XorStr.h"

#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

namespace NSDK {
	class O {
	private:
		static bool bCompare(const BYTE* Data, const BYTE* Mask, const char* szMask)
		{
			for (; *szMask; ++szMask, ++Mask, ++Data)
			{
				if (*szMask == 'x' && *Mask != *Data)
				{
					return false;
				}
			}
			return (*szMask) == 0;
		}

		static CGlowObjectManager *O::m_pGlowManager;
		static IMoveHelper *O::m_pMoveHelper;
		static DWORD *O::m_dwOcclusionArray;
		static IViewRender *O::m_pViewRender;

	public:
		static DWORD FindPattern(const char *moduleName, BYTE* Mask, char* szMask)
		{
			DWORD dwAddress = (DWORD)GetModuleHandleA(moduleName);

			MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)dwAddress, &miModInfo, sizeof(MODULEINFO));
			DWORD dwLength = miModInfo.SizeOfImage;
			for (DWORD i = 0; i < dwLength; i++)
			{
				if (bCompare((BYTE*)(dwAddress + i), Mask, szMask))
				{
					return (DWORD)(dwAddress + i);
				}
			}
			return 0;
		}

		static DWORD FindSignature(const char* szModule, const char* szSignature) {
			//CREDITS: learn_more

			MODULEINFO modInfo;
			GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
			DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
			DWORD endAddress = startAddress + modInfo.SizeOfImage;
			const char* pat = szSignature;
			DWORD firstMatch = 0;
			for (DWORD pCur = startAddress; pCur < endAddress; pCur++) {
				if (!*pat) return firstMatch;
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
					if (!firstMatch) firstMatch = pCur;
					if (!pat[2]) return firstMatch;
					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
					else pat += 2;    //one ?
				}
				else {
					pat = szSignature;
					firstMatch = 0;
				}
			}
			return NULL;
		}

		static CGlowObjectManager *O::GlowManager();
		static IMoveHelper *O::MoveHelper();
		static IViewRender *O::ViewRender();
	};
}