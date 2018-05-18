#include "DrawManager.h"
#include "Globals.h"

NSDK::Color enemyColor = NSDK::Color(255, 0, 0, 255);
NSDK::Color teamColor = NSDK::Color(0, 0, 255, 255);

NSDK::HFont Drawing::hEspFont = 0;
NSDK::HFont Drawing::hNotificationFont = 0;
NSDK::HFont Drawing::hStrictlyFont = 0;
NSDK::HFont Drawing::hAimwareFont = 0;
NSDK::HFont Drawing::hFontIndicator = 0;

void Drawing::InitializeFont() 
{
	hEspFont = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hEspFont, "Bell Gothic", 10, 450, 0, 0, (int)NSDK::FontFlags::FONTFLAG_OUTLINE);

	hNotificationFont = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hNotificationFont, "Bell Gothic", 12, 500, 0, 0, (int)NSDK::FontFlags::FONTFLAG_OUTLINE);

	hStrictlyFont = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hStrictlyFont, "Tahoma", 12, 400, 0, 0, (int)NSDK::FontFlags::FONTFLAG_OUTLINE);

	hAimwareFont = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hAimwareFont, "Tahoma", 11, FW_EXTRABOLD, 0, 0, (int)NSDK::FontFlags::FONTFLAG_ANTIALIAS | (int)NSDK::FontFlags::FONTFLAG_DROPSHADOW);

	hFontIndicator = NSDK::I::MatSurface()->CreateFont();
	NSDK::I::MatSurface()->SetFontGlyphSet(hFontIndicator, "Tahoma", 32, 900, NULL, NULL, (int)NSDK::FontFlags::FONTFLAG_DROPSHADOW | (int)NSDK::FontFlags::FONTFLAG_ANTIALIAS);
}

void Drawing::DrawString(NSDK::Color cColor, NSDK::HFont font, const char* chString, int x, int y)
{
	wchar_t formated[512] = { '\0' };
	wsprintfW(formated, L"%S", chString);
	NSDK::I::MatSurface()->DrawSetTextPos(x, y);
	NSDK::I::MatSurface()->DrawSetTextColor(cColor);
	NSDK::I::MatSurface()->DrawSetTextFont(font);
	NSDK::I::MatSurface()->DrawPrintText(formated, wcslen(formated));
}

void Drawing::DrawFilledRect(int x, int y, int w, int h, NSDK::Color c)
{
	NSDK::I::MatSurface()->DrawSetColor(c);
	NSDK::I::MatSurface()->DrawFilledRect(x, y, x + w, y + h);
}

void Drawing::DrawStringValue(NSDK::Color cColor, int x, int y, NSDK::HFont font, const char* chString, ...) {
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

void Drawing::DrawOutlinedRect(NSDK::Color cColor, float x0, float y0, float x1, float y1) 
{
	NSDK::I::MatSurface()->DrawSetColor(cColor);
	NSDK::I::MatSurface()->DrawOutlinedRect(x0, y0, x1, y1);
}

void Drawing::DrawHealthBar(CBaseEntity* entity, float bottom, float top, float left)
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

	Drawing::DrawString(NSDK::Color(255, 255, 255, 255), hEspFont, std::to_string(hp).c_str(), left - 16, y + height - 2);

	NSDK::I::MatSurface()->DrawSetColor(NSDK::Color(0, 0, 0, 255));
}

void Drawing::DrawBoxESP(CBaseEntity *pEntity, float x0, float y0, float x1, float y1) 
{
	//TheirTeam
	switch (*pEntity->GetTeamNum() == *CBaseEntity::GetLocalPlayer()->GetTeamNum()) 
	{
	case true:
		Drawing::DrawOutlinedRect(teamColor, x0, y0, x1, y1);
		Drawing::DrawOutlinedRect(NSDK::Color(20, 20, 20), x0 + 1.f, y0 + 1.f, x1 - 1.f, y1 - 1.f);
		Drawing::DrawOutlinedRect(NSDK::Color(20, 20, 20), x0 - 1.f, y0 - 1.f, x1 + 1.f, y1 + 1.f);
		break;
	case false:
		Drawing::DrawOutlinedRect(enemyColor, x0, y0, x1, y1);
		Drawing::DrawOutlinedRect(NSDK::Color(20, 20, 20), x0 + 1.f, y0 + 1.f, x1 - 1.f, y1 - 1.f);
		Drawing::DrawOutlinedRect(NSDK::Color(20, 20, 20), x0 - 1.f, y0 - 1.f, x1 + 1.f, y1 + 1.f);
		break;
	default:
		break;
	}
}

void Drawing::DrawPlayerName(int entIndex, int x, int y) 
{
	NSDK::PlayerInfo entityInfos;
	NSDK::I::Engine()->GetPlayerInfo(entIndex, &entityInfos);

	wchar_t formated[512] = { '\0' };
	wsprintfW(formated, L"%S", entityInfos.szName);

	int tall;
	int size;
	NSDK::I::MatSurface()->GetTextSize(hEspFont, formated, size, tall);
	x -= size / 2;
	y -= tall / 2;

	NSDK::I::MatSurface()->DrawSetTextPos(x, y);
	NSDK::I::MatSurface()->DrawSetTextColor(NSDK::Color(255, 255, 255));
	NSDK::I::MatSurface()->DrawSetTextFont(hEspFont);
	NSDK::I::MatSurface()->DrawPrintText(formated, wcslen(formated));
}

void Drawing::DrawWeaponESP(CBaseEntity *pEntity, int x, int y)
{
	if (!pEntity->isValidPlayer()) return;
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
		Drawing::DrawString(NSDK::Color(255, 255, 255, 255), hEspFont, wname.c_str(), x - 1, y + 10);
	}
}

//not sure if this is properly aligned
void Drawing::DrawResolverESP(CBaseEntity *pEntity, int x, int y)
{
	if (!pEntity->isValidPlayer()) return;

		int idx = pEntity->EntIndex();
		std::string resolvermode;

		switch (info::resolvemode[idx])
		{
		case MOVING_LBY: resolvermode = "lby (0/2)"; break;
		case LBY_FLICK: resolvermode = "backtrack"; break;
		case LOW_DELTA: resolvermode = "lby (1/2)"; break;
		case HIGH_DELTA: resolvermode = "lby (2/2)"; break;
		}

		Drawing::DrawString(NSDK::Color(255, 255, 255, 255), hEspFont, resolvermode.c_str(), x - 1, y + 20);
}

void Drawing::SpectatorList()
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
					Drawing::DrawString(NSDK::Color(255, 255, 255, 255), Drawing::hAimwareFont, player_name, w - 1910, 7 + (10 * count) );
					++count;
				}
			}
	}
}

void Drawing::DrawBoneLine(NSDK::Color cColor, CBaseEntity* pEntity, int p1, int p2) 
{
	NSDK::Vector screenPos1;
	NSDK::Vector screenPos2;
	if (Utilities::W2S(Utilities::GetEntityBone(pEntity, p1), screenPos1) &
		Utilities::W2S(Utilities::GetEntityBone(pEntity, p2), screenPos2)) {
		NSDK::I::MatSurface()->DrawSetColor(cColor);
		NSDK::I::MatSurface()->DrawLine(screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y);
	}
}

void Drawing::DrawBoneESP(NSDK::Color cColor, CBaseEntity* pEnt) 
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

static float degrees_to_radians(float deg)
{
	return deg * (M_PI / 180.f);
}

void Drawing::draw_aa_indic()
{
	NSDK::Vector client_viewangles;
	int screen_width = 0, screen_height = 0;
	NSDK::I::Engine()->GetViewAngles(client_viewangles);
	NSDK::I::Engine()->GetScreenSize(screen_width, screen_height);
	
	screen_width /= 2;
	screen_height /= 2;

	constexpr auto radius = 60;
	constexpr auto text_radius = radius/2;
	constexpr auto circle_size = 15;

	float lby = *CBaseEntity::GetLocalPlayer()->GetLowerBodyYaw();

	const auto real_rot = degrees_to_radians(client_viewangles.y - Local::Real - 90);
	const auto fake_rot = degrees_to_radians(client_viewangles.y - Local::Fake - 90);
	const auto lby_rot = degrees_to_radians(client_viewangles.y - lby - 90);

	int realint = static_cast<int>(std::ceilf(Local::Real));
	int fakeint = static_cast<int>(std::ceilf(Local::Fake));
	int lbyint = static_cast<int>(std::ceilf(lby));

	std::string realString = "real (" + std::to_string(realint) + ")";
	std::string fakeString = "fake (" + std::to_string(fakeint) + ")";
	std::string lbyString = "lby (" + std::to_string(lbyint) + ")";
	 
	NSDK::Color lbyColor = NSDK::Color(255, 165, 0, 255);
	NSDK::Color realColor = NSDK::Color(0, 255, 0, 255);
	NSDK::Color fakeColor = NSDK::Color(255, 0, 0, 255);

	NSDK::I::MatSurface()->DrawSetColor(realColor);
	Drawing::DrawString(realColor, hEspFont, realString.c_str(), screen_width + cosf(real_rot) * text_radius, screen_height + sinf(real_rot) * text_radius);
	NSDK::I::MatSurface()->DrawOutlinedCircle(screen_width + cosf(real_rot) * radius, screen_height + sinf(real_rot) * radius, circle_size, 500);

	NSDK::I::MatSurface()->DrawSetColor(fakeColor);
	Drawing::DrawString(fakeColor, hEspFont, fakeString.c_str(), screen_width + cosf(fake_rot) * text_radius, screen_height + sinf(fake_rot) * text_radius);
	NSDK::I::MatSurface()->DrawOutlinedCircle(screen_width + cosf(fake_rot) * radius, screen_height + sinf(fake_rot) * radius, circle_size, 500);

	NSDK::I::MatSurface()->DrawSetColor(lbyColor);
	Drawing::DrawString(lbyColor, hEspFont, lbyString.c_str(), screen_width + cosf(lby_rot) * text_radius, screen_height + sinf(lby_rot) * text_radius);
	NSDK::I::MatSurface()->DrawOutlinedCircle(screen_width + cosf(lby_rot) * radius, screen_height + sinf(lby_rot) * radius, circle_size, 500);
}

void Drawing::DrawHitboxesFromCache(CBaseEntity* g_Local, int r, int g, int b, int a)
{
	//local player fake angle hitboxes
	//this shit is broken af
	NSDK::matrix3x4_t local_matrix[128];
	g_Local->SetupBones(local_matrix, 128, 0x00000100, NSDK::I::GlobalVars()->curtime);

	auto pStudioModel = NSDK::I::ModelInfo()->GetStudiomodel(g_Local->GetModel());

	NSDK::Vector BonePos;
	NSDK::Vector OutPos;

	for (int i = 0; i < 128; i++)
	{
		Utilities::AngleMatrix(NSDK::Vector(0, Local::Fake, 0), local_matrix[i]);
		BonePos = NSDK::Vector(local_matrix[i][0][3], local_matrix[i][1][3], local_matrix[i][2][3]) - g_Local->GetAbsOrigin();
		Utilities::VectorRotate(BonePos, NSDK::Vector(0, Local::Fake, 0), OutPos);
		OutPos += g_Local->GetAbsOrigin();
		local_matrix[i][0][3] = OutPos.x;
		local_matrix[i][1][3] = OutPos.y;
		local_matrix[i][2][3] = OutPos.z;
	}

	//actual drawing
	for (int i = 0; i < 20; i++)
	{
		auto pHitbox = pStudioModel->pHitboxSet(0)->pHitbox(i);
		if (pHitbox)
		{
				NSDK::Vector vMin, vMax;
				Utilities::VectorTransform(pHitbox->bbmin, local_matrix[pHitbox->bone], vMin);
				Utilities::VectorTransform(pHitbox->bbmax, local_matrix[pHitbox->bone], vMax);

				NSDK::I::DebugOverlay()->AddCapsuleOverlay(vMin, vMax, pHitbox->m_flRadius, r, g, b, a, 3);
			}
		}
	}

void Drawing::DrawHitboxes(CBaseEntity* pEntity, int r, int g, int b, int a)
{
	if (!pEntity->isValidPlayer())
		return;

	NSDK::matrix3x4_t matrix[128];
	if (pEntity->SetupBones(matrix, 128, 0x00000100, NSDK::I::GlobalVars()->curtime))
	{
		auto pStudioModel = NSDK::I::ModelInfo()->GetStudiomodel(pEntity->GetModel());
		if (pStudioModel)
		{
			for (size_t i = 0; i < 20; i++)
			{
				auto pHitbox = pStudioModel->pHitboxSet(0)->pHitbox(i);
				if (pHitbox)
				{
					NSDK::Vector min, max;
					Utilities::VectorTransform(pHitbox->bbmin, matrix[pHitbox->bone], min);
					Utilities::VectorTransform(pHitbox->bbmax, matrix[pHitbox->bone], max);
					//addpill doesnt work properly
					//add capsule works fine
					NSDK::I::DebugOverlay()->AddCapsuleOverlay(min, max, pHitbox->m_flRadius, r, g, b, a, .1);
				}
			}
		}
	}
}

void DrawBox(NSDK::Color clr, float left, float bottom, float top, float right)
{
	NSDK::I::MatSurface()->DrawSetColor(clr);
	NSDK::I::MatSurface()->DrawLine(left, bottom, left, top);
	NSDK::I::MatSurface()->DrawLine(left, top, right, top);
	NSDK::I::MatSurface()->DrawLine(right, top, right, bottom);
	NSDK::I::MatSurface()->DrawLine(right, bottom, left, bottom);
}

void DrawPlayerBox(CBaseEntity* pEntity, NSDK::Color clr)
{
	if (!pEntity)
		return;

	const NSDK::matrix3x4_t& trans = pEntity->m_rgflCoordinateFrame();

	NSDK::ICollideable* collision = pEntity->GetCollideable();

	if (!collision)
		return;

	NSDK::Vector min = collision->OBBMins();
	NSDK::Vector max = collision->OBBMaxs();

	NSDK::Vector points[] = { NSDK::Vector(min.x, min.y, min.z),
		NSDK::Vector(min.x, max.y, min.z),
		NSDK::Vector(max.x, max.y, min.z),
		NSDK::Vector(max.x, min.y, min.z),
		NSDK::Vector(max.x, max.y, max.z),
		NSDK::Vector(min.x, max.y, max.z),
		NSDK::Vector(min.x, min.y, max.z),
		NSDK::Vector(max.x, min.y, max.z) };

	/*
	.6-------5					        blb = 0
	.' |       .' |					        brb = 1
	7---+--4'   |		0 = min		  frb = 2
	|   |    |    |		4 = max		 flb = 3
	y |  ,0---+---1					        frt = 4
	|.'       | .'  z					       brt = 5
	3------2						          blt = 6
	x						                flt = 7

	blt------brt		blt = back-left-top
	.' |        .'|			brt = back-right-top
	flt---+--frt  |			brb = back-right-bottom
	|   |     |   |			blb = back-left-bottom
	y |  blb---+--brb		flt = front-left-top
	|.'        | .'  z		frt = front-right-top
	flb------frb			frb = front-right-bottom
	x					flb = front-left-bottom

	*/

	NSDK::Vector pointsTransformed[8];
	for (int i = 0; i < 8; i++)
	{
		//vector transform definition wrong or smth
		Utilities::VectorTransform(points[i], trans, pointsTransformed[i]);
	}

	NSDK::Vector pos = pEntity->GetAbsOrigin();
	NSDK::Vector flb;
	NSDK::Vector brt;
	NSDK::Vector blb;
	NSDK::Vector frt;
	NSDK::Vector frb;
	NSDK::Vector brb;
	NSDK::Vector blt;
	NSDK::Vector flt;


	if (!Utilities::W2S(pointsTransformed[3], flb) || !Utilities::W2S(pointsTransformed[5], brt)
		|| !Utilities::W2S(pointsTransformed[0], blb) || !Utilities::W2S(pointsTransformed[4], frt)
		|| !Utilities::W2S(pointsTransformed[2], frb) || !Utilities::W2S(pointsTransformed[1], brb)
		|| !Utilities::W2S(pointsTransformed[6], blt) || !Utilities::W2S(pointsTransformed[7], flt))
		return;

	NSDK::Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;		// left
	float top = flb.y;		// top
	float right = flb.x;	// right
	float bottom = flb.y;	// bottom

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	//actual color
	DrawBox(clr, left, bottom, top, right);

	//outlines
	DrawBox(NSDK::Color(0, 0, 0), left + 1, bottom + 1, top - 1, right - 1);
	DrawBox(NSDK::Color(0, 0, 0), left - 1, bottom - 1, top + 1, right + 1);
}

void Drawing::DrawInfo(CBaseEntity *pEntity, int x, int y)
{
	if (!pEntity->isValidPlayer()) return;

	int position = 0;
	int idx = pEntity->EntIndex();

	//$$$ pAutoAlign

	if (info::should_baim[idx])
	{
		Drawing::DrawString(NSDK::Color(255, 255, 255, 255), hEspFont, "baiming", x - 1, y + 30);
		position++;
	}

	if (pEntity->isScoped())
	{
		Drawing::DrawString(NSDK::Color(255, 255, 255, 255), hEspFont, "scoped", x - 1, y + 30 + (position * 10));
		position++;
	}

	if (pEntity->GetAnimOverlay(1).m_nSequence == 967 && pEntity->GetAnimOverlay(1).m_flWeight != 0)
	{
		Drawing::DrawString(NSDK::Color(255, 255, 255, 255), hEspFont, "reloading", x - 1, y + 30 + (position * 10));
		position++;
	}

}