#pragma once

#include "SqchSDK\Interfaces.h"
#include "EntityStructs.h"
#include "Utilities.h"

class Drawing 
{
public:
	static NSDK::HFont hEspFont, hNotificationFont, hStrictlyFont, hAimwareFont, hFontIndicator;

	static void InitializeFont();
	static void DrawString(NSDK::Color cColor, NSDK::HFont font, const char* chString, int x, int y);
	static void DrawFilledRect(int x, int y, int w, int h, NSDK::Color c);
	static void DrawStringValue(NSDK::Color cColor, int x, int y, NSDK::HFont font, const char* chString, ...);
	static void DrawOutlinedRect(NSDK::Color cColor, float x0, float y0, float x1, float y1);
	static void DrawHealthBar(CBaseEntity* entity, float bottom, float top, float left);
	static void DrawBoxESP(CBaseEntity *pEntity, float x0, float y0, float x1, float y1);
	static void DrawPlayerName(int entIndex, int x, int y);
	static void DrawWeaponESP(CBaseEntity *pEntity,int x, int y);
	static void SpectatorList();
	static void DrawBoneLine(NSDK::Color cColor, CBaseEntity* pEntity, int p1, int p2);
	static void DrawBoneESP(NSDK::Color cColor, CBaseEntity* pEnt);
	static void DrawResolverESP(CBaseEntity *pEntity, int x, int y);
	static void DrawHitboxes(CBaseEntity* pEntity, int r, int g, int b, int a);
	static void DrawInfo(CBaseEntity * pEntity, int x, int y);
	static void draw_aa_indic();
	static void DrawHitboxesFromCache(CBaseEntity * g_Local, int r, int g, int b, int a);
};