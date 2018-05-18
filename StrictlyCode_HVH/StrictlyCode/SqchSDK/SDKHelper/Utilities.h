#pragma once

#include <windows.h>
#include <Psapi.h>

namespace NSDK {
	template<typename FuncType>
	inline FuncType CallVFunction(void* ppClass, DWORD index) {
		PDWORD pVTable = *(PDWORD*)ppClass;
		DWORD dwAddress = pVTable[index];
		return (FuncType)(dwAddress);
	}

	struct Stack
	{
		Stack *next;
		char  *ret;

		template<typename T> inline T arg(unsigned int i)
		{
			return *(T *)((void **)this + i + 2);
		}
	};
}