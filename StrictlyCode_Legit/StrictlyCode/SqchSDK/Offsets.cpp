#include "Offsets.h"

namespace NSDK {
	CGlowObjectManager *O::m_pGlowManager = nullptr;
	IMoveHelper *O::m_pMoveHelper = nullptr;
	IViewRender *O::m_pViewRender = nullptr;

	CGlowObjectManager* O::GlowManager() {
		if (!m_pGlowManager) {
			m_pGlowManager = (CGlowObjectManager*)(*(DWORD*)(FindSignature(XorStr("client.dll"), XorStr("A1 ? ? ? ? A8 01 75 4B")) + 0x4));
		}
		return m_pGlowManager;
	}

	IMoveHelper* O::MoveHelper() {
		if (!m_pMoveHelper) {
			m_pMoveHelper = **(IMoveHelper***)(FindSignature(XorStr("client.dll"), XorStr("8B 0D ? ? ? ? 8B 46 08 68")) + 0x2);
		}
		return m_pMoveHelper;
	}

	IViewRender* O::ViewRender() {
		if (!m_pViewRender) {
			DWORD dwViewRender = FindSignature(XorStr("client.dll"), XorStr("FF 50 14 E8 ? ? ? ? 5D"));
			m_pViewRender = **(IViewRender***)(dwViewRender - 7);
		}
		return m_pViewRender;
	}
}