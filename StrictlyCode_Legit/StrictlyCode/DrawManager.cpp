#include "DrawManager.h"
NSDK::Color enemyColor = NSDK::Color(255, 0, 0, 255);
NSDK::Color teamColor = NSDK::Color(0, 0, 255, 255);

NSDK::HFont DrawManager::hEspFont = 0;
NSDK::HFont DrawManager::hNotificationFont = 0;
NSDK::HFont DrawManager::hStrictlyFont = 0;
NSDK::HFont DrawManager::hAimwareFont = 0;

void DrawManager::InitializeFont() 
{
	hEspFont = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hEspFont, "Bell Gothic", 11, 400, 0, 0, (int)NSDK::FontFlags::FONTFLAG_OUTLINE);

	hNotificationFont = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hNotificationFont, "Bell Gothic", 12, 500, 0, 0, (int)NSDK::FontFlags::FONTFLAG_OUTLINE);

	hStrictlyFont = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hStrictlyFont, "Tahoma", 12, 400, 0, 0, (int)NSDK::FontFlags::FONTFLAG_OUTLINE);

	hAimwareFont = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hAimwareFont, "Tahoma", 11, FW_EXTRABOLD, 0, 0, (int)NSDK::FontFlags::FONTFLAG_ANTIALIAS | (int)NSDK::FontFlags::FONTFLAG_DROPSHADOW);
}

void DrawManager::DrawString(NSDK::Color cColor, NSDK::HFont font, const char* chString, int x, int y)
{
	wchar_t formated[512] = { '\0' };
	wsprintfW(formated, L"%S", chString);
	NSDK::I::MatSurface()->DrawSetTextPos(x, y);
	NSDK::I::MatSurface()->DrawSetTextColor(cColor);
	NSDK::I::MatSurface()->DrawSetTextFont(font);
	NSDK::I::MatSurface()->DrawPrintText(formated, wcslen(formated));
}

void DrawManager::DrawFilledRect(int x, int y, int w, int h, NSDK::Color c)
{
	NSDK::I::MatSurface()->DrawSetColor(c);
	NSDK::I::MatSurface()->DrawFilledRect(x, y, x + w, y + h);
}

void DrawManager::DrawStringValue(NSDK::Color cColor, int x, int y, NSDK::HFont font, const char* chString, ...) {
	char buffer[512];
	va_list list;
	va_start(list, chString);
	vsprintf_s(buffer, chString, list);
	va_end(list);
	wchar_t formated[512] = { '\0' };
	wsprintfW(formated, L"%S", buffer);
	NSDK::I::MatSurface()->DrawSetTextPos(x, y);
	NSDK::I::MatSurface()->DrawSetTextColor(cColor);
	NSDK::I::MatSurface()->DrawSetTextFont(font);
	NSDK::I::MatSurface()->DrawPrintText(formated, wcslen(formated));
}

void DrawManager::DrawOutlinedRect(NSDK::Color cColor, float x0, float y0, float x1, float y1) {
	NSDK::I::MatSurface()->DrawSetColor(cColor);
	NSDK::I::MatSurface()->DrawOutlinedRect(x0, y0, x1, y1);
}

void DrawManager::DrawHealthBar(CBaseEntity* entity, float bottom, float top, float left)
{
	auto hp = entity->GetHealth();
	float box_h = (float)fabs(bottom - top);

	float off = 8;

	auto height = (((box_h * hp) / 100));

	int red = int(255 - (hp * 2.55f));
	int green = int(hp * 2.55f);

	int x = left - off;
	int y = top;
	int w = 4;
	int h = box_h;

	NSDK::I::MatSurface()->DrawSetColor(NSDK::Color(0, 0, 0, 255));
	NSDK::I::MatSurface()->DrawFilledRect(x, y, x + w, y + h);

	NSDK::I::MatSurface()->DrawSetColor(NSDK::Color(red, green, 0, 255));
	NSDK::I::MatSurface()->DrawFilledRect(x + 1, y + 1, x + w - 1, y + height - 2);

	DrawManager::DrawString(NSDK::Color(255, 255, 255, 255), hEspFont, std::to_string(hp).c_str(), left - 16, y + height - 2);
	NSDK::I::MatSurface()->DrawSetColor(NSDK::Color(0, 0, 0, 255));
}

void DrawManager::DrawBoxESP(CBaseEntity *pEntity, float x0, float y0, float x1, float y1) 
{
	//TheirTeam
	switch (*pEntity->GetTeamNum() == *CBaseEntity::GetLocalPlayer()->GetTeamNum()) 
	{
	case true:
		DrawManager::DrawOutlinedRect(Options.box_team_color, x0, y0, x1, y1);
		DrawManager::DrawOutlinedRect(NSDK::Color(0, 0, 0), x0 + 1.f, y0 + 1.f, x1 - 1.f, y1 - 1.f);
		DrawManager::DrawOutlinedRect(NSDK::Color(0, 0, 0), x0 - 1.f, y0 - 1.f, x1 + 1.f, y1 + 1.f);
		break;
	case false:
		DrawManager::DrawOutlinedRect(Options.box_enemy_color, x0, y0, x1, y1);
		DrawManager::DrawOutlinedRect(NSDK::Color(0, 0, 0), x0 + 1.f, y0 + 1.f, x1 - 1.f, y1 - 1.f);
		DrawManager::DrawOutlinedRect(NSDK::Color(0, 0, 0), x0 - 1.f, y0 - 1.f, x1 + 1.f, y1 + 1.f);
		break;
	default:
		break;
	}
}

void DrawManager::DrawPlayerName(int entIndex, int x, int y) 
{
	NSDK::PlayerInfo entityInfos;
	NSDK::I::Engine()->GetPlayerInfo(entIndex, &entityInfos);

	wchar_t formated[512] = { '\0' };
	wsprintfW(formated, L"%S", entityInfos.szName);
	CBaseEntity* pEntity = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(entIndex);
	int tall;
	int size;
	NSDK::I::MatSurface()->GetTextSize(hEspFont, formated, size, tall);
	x -= size / 2;
	y -= tall / 2;

	NSDK::I::MatSurface()->DrawSetTextPos(x, y);
	NSDK::I::MatSurface()->DrawSetTextColor(*pEntity->GetTeamNum() == *CBaseEntity::GetLocalPlayer()->GetTeamNum() ? Options.player_name_team_color : Options.player_name_enemy_color);
	NSDK::I::MatSurface()->DrawSetTextFont(hEspFont);
	NSDK::I::MatSurface()->DrawPrintText(formated, wcslen(formated));
}

void DrawManager::DrawWeaponESP(CBaseEntity *pEntity,int x, int y) 
{
	if (!pEntity) return;
	CBaseCombatWeapon *activeWeapon = pEntity->GetActiveWeapon();
	if (activeWeapon) 
	{
		char weaponName[256];
		std::string ammo = std::to_string(activeWeapon->GetCurrentAmmo());
		sprintf_s(weaponName, "%s", activeWeapon->GetName());
		std::string wname;
		wname = weaponName;
		wname.erase(0, 13);
		wname.append(" [ " + ammo + " ] ");
		DrawManager::DrawString(*pEntity->GetTeamNum() == *CBaseEntity::GetLocalPlayer()->GetTeamNum() ? Options.weapon_team_color : Options.weapon_enemy_color, hEspFont, wname.c_str(), x - 1, y + 10);
	}
}

void DrawManager::SpectatorList()
{
	int count = 0;
	CBaseEntity* g_LocalPlayer = CBaseEntity::GetLocalPlayer();

	if (!g_LocalPlayer->isValidPlayer(true) || !NSDK::I::Engine()->isConnected() || !NSDK::I::Engine()->isInGame())
		return;

	for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); i++)
	{
		CBaseEntity *player = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

		if (!player || player == g_LocalPlayer || player->IsAlive() || player->IsDormant())
			continue;

			NSDK::PlayerInfo player_info;

			if (NSDK::I::Engine()->GetPlayerInfo(i, &player_info))
			{
				//GetObserved returns a CBaseEntity
				auto observer_target = player->GetObserved();

				if (!observer_target)
					continue;

				if (observer_target == g_LocalPlayer)
				{
					char player_name[512] = { 0 };
					sprintf_s(player_name, "%s", player_info.szName);

					int w, h;
					NSDK::I::Engine()->GetScreenSize(w, h);
					DrawManager::DrawString(NSDK::Color(255, 255, 255, 255), DrawManager::hAimwareFont, player_name, w - 1910, 7 + (10 * count) );
					++count;
				}
			}
	}
}

void DrawManager::DrawBoneLine(NSDK::Color cColor, CBaseEntity* pEntity, int p1, int p2) 
{
	NSDK::Vector screenPos1;
	NSDK::Vector screenPos2;
	if (Utilities::W2S(Utilities::GetEntityBone(pEntity, p1), screenPos1) &
		Utilities::W2S(Utilities::GetEntityBone(pEntity, p2), screenPos2)) {
		NSDK::I::MatSurface()->DrawSetColor(cColor);
		NSDK::I::MatSurface()->DrawLine(screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y);
	}
}

void DrawManager::DrawBoneESP(NSDK::Color cColor, CBaseEntity* pEnt) 
{
	NSDK::studiohdr_t* pStudioModel = NSDK::I::ModelInfo()->GetStudiomodel(pEnt->GetModel());
	if (pStudioModel)
	{
		for (int i = 0; i < pStudioModel->numbones; ++i)
		{
			NSDK::mstudiobone_t* pBone = pStudioModel->pBone(i);
			if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
				continue;

			DrawBoneLine(cColor, pEnt, i, pBone->parent);
		}
	}
}