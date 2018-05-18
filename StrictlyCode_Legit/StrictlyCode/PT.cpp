#include "PT.h"
#include "CNotify.h"
#include "CHurtListener.h"
#include <time.h>
#include "Globals.h"
double deg2rad(double degrees) 
{
	return degrees * 4.0 * atan(1.0) / 180.0;
}

std::string GetTimeString()
{
	time_t current_time;
	struct tm *time_info;
	static char timeString[10];
	time(&current_time);
	time_info = localtime(&current_time);
	strftime(timeString, sizeof(timeString), "%X", time_info);
	return timeString;
}

namespace PT 
{
	PaintTraverse_t g_fnOriginalPaintTraverse;
	void __fastcall Hooked_PaintTraverse(void* thisptr, void* edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce) 
	{

		g_fnOriginalPaintTraverse(thisptr, vguiPanel, forceRepaint, allowForce);

		static unsigned int iSelectedPanelMat = 0;

		if (!iSelectedPanelMat) 
		{

			if (strstr(NSDK::I::VGUIPanel()->GetName(vguiPanel), ("FocusOverlayPanel")))
				iSelectedPanelMat = vguiPanel;

		} 
		
		else if (vguiPanel == iSelectedPanelMat) 
		{

			int iScreenWidth, iScreenHeight;
			NSDK::I::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

			if (Options.bFovring)
			{

				int x;
				int y;
				float Radius;
				NSDK::Vector center;
				NSDK::I::Engine()->GetScreenSize(x, y);

				center.x = x / 2;
				center.y = y / 2;
				Radius = tanf((deg2rad(Options.fNormalFov)) / 6) / tanf(97) * x;
				NSDK::I::MatSurface()->DrawSetColor(Options.fov_ring_color);
				NSDK::I::MatSurface()->DrawOutlinedCircle(center.x / 1, center.y / 1, Radius, Options.fNormalFov * 20);
			}
		
			std::string info = cheat_name " | " __DATE__ " | " + GetTimeString();

			DrawManager::DrawString(Options.logo_text_color, DrawManager::hStrictlyFont, info.c_str(), iScreenWidth - 168, 10);
			NSDK::I::MatSurface()->DrawSetColor(Options.logo_box_color);
			NSDK::I::MatSurface()->DrawFilledRect(iScreenWidth - 172, 7, iScreenWidth - 5, 27);

			PushNotifications::Update();
			if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected()) 
			{
				
				int iScreenWidth, iScreenHeight;
				NSDK::I::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

				CBaseEntity *g_Local = CBaseEntity::GetLocalPlayer();

				DrawManager::SpectatorList();

				for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); ++i) 
				{

					CBaseEntity *pEntity = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

					if (!pEntity)
						continue;

					if (pEntity->isValidPlayer()) 
					{
						//ESP
						NSDK::Vector vecHeadHitBox = pEntity->GetAbsOrigin() + NSDK::Vector(0, 0, pEntity->GetCollideable()->OBBMaxs().z), vecOrigin = *pEntity->GetOrigin();
						NSDK::Vector vecHeadHitBox2D, vecOrigin2D;

						//just so the boxes dont look retarded
						vecOrigin.z -= 1;
						vecHeadHitBox.z -= 10;
						vecOrigin.x -= 2;

						if (Utilities::W2S(vecHeadHitBox, vecHeadHitBox2D) && Utilities::W2S(vecOrigin, vecOrigin2D)) 
						{
							float height = vecOrigin2D.y - vecHeadHitBox2D.y;
							float width = height * 0.45f;

							if (Options.bHealthBar) 
							{
								DrawManager::DrawHealthBar(pEntity, vecHeadHitBox2D.y + (height * 1.21f), vecHeadHitBox2D.y - (height * .2), vecHeadHitBox2D.x + (width * -.74));
							}

							if (Options.bBoxESP) 
							{
								DrawManager::DrawBoxESP(pEntity, vecHeadHitBox2D.x - (width * 0.75), vecHeadHitBox2D.y - (height * 0.2), vecHeadHitBox2D.x + (width * 0.75), vecHeadHitBox2D.y + (height * 1.2));
							}

							if (Options.bPlayerName) 
							{
								DrawManager::DrawPlayerName(pEntity->EntIndex(), vecHeadHitBox2D.x, vecHeadHitBox2D.y + (height * 1.10));
							}

							if (Options.bBoneESP) 
							{
								DrawManager::DrawBoneESP(NSDK::Color(255, 255, 255), pEntity);
							}

							if (Options.bWeaponESP) 
							{
								DrawManager::DrawWeaponESP(pEntity, vecHeadHitBox2D.x - (width * -.750), vecHeadHitBox2D.y + (height * -0.23));
							}
						}

					}
				}
			}
		}

		CHurtListener::singleton()->OnPaint();
	}
}