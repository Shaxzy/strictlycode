#include "BeginFrame.h"
#include "CBulletListener.h"

namespace BeginFrame
{
	BeginFrame_t g_fnOriginalBeginFrame;
	void __fastcall Hooked_BeginFrame(void* thisptr, void* edx)
	{
		g_fnOriginalBeginFrame(thisptr);

		//CBulletListener::singleton()->OnStudioRender();
	}
}