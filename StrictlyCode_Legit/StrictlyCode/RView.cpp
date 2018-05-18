#include "RView.h"

namespace RView {
	RenderView_t g_fnOriginalRenderView;
	void __fastcall Hooked_RenderView(void* thisptr, void* edx, NSDK::CViewSetup &view, NSDK::CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw)
	{

		g_fnOriginalRenderView(thisptr, view, hudViewSetup, nClearFlags, whatToDraw);
	}
}