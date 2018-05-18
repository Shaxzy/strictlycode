#include "PT.h"
#include "CNotify.h"
#include "CHurtListener.h"
#include <time.h>
#include "Globals.h"
#include "CResolver.h"
#include "CParticles.h"
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

		static unsigned int iSelectedPanelZoom = 0;
		if (!iSelectedPanelZoom)
		{
			if (strstr(NSDK::I::VGUIPanel()->GetName(vguiPanel),  ("HudZoom")))
				iSelectedPanelZoom = vguiPanel;
		}
		else if (vguiPanel == iSelectedPanelZoom) 
		{
			return;
		}

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
		
			std::string info = cheat_name " | " __DATE__ " | " + GetTimeString();

			Drawing::DrawString(NSDK::Color(105, 105, 105, 230), Drawing::hStrictlyFont, info.c_str(), iScreenWidth - 168, 10);
			NSDK::I::MatSurface()->DrawSetColor(NSDK::Color(51, 153, 200, 35));
			NSDK::I::MatSurface()->DrawFilledRect(iScreenWidth - 172, 7, iScreenWidth - 5, 27);

			if (Options.bShowMenu)
			{
				//dot_draw();
			}

			PushNotifications::Update();
			if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected()) 
			{
				
				int iScreenWidth, iScreenHeight;
				NSDK::I::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

				CBaseEntity *g_Local = CBaseEntity::GetLocalPlayer();

				if (!g_Local)
					return;

				if (g_Local->IsAlive())
				{
					Drawing::SpectatorList();

					if (Local::Fake && Local::Real)
					{
						Drawing::draw_aa_indic();
					}

					CHurtListener::singleton()->OnPaint();

					Drawing::DrawString(Resolver::Delta(*CBaseEntity::GetLocalPlayer()->GetLowerBodyYaw(), Local::Real) > 35 ? NSDK::Color(0, 255, 0) : NSDK::Color(255, 0, 0), Drawing::hFontIndicator,  ("LBY"), (iScreenWidth / 2) - 950, (iScreenHeight / 2) + 425);
				}

				for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); ++i) 
				{

					CBaseEntity *pEntity = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

					if (!pEntity)
						continue;

					if (!pEntity->isValidPlayer())
						continue;

					//skip spectating player
					if (!g_Local->IsAlive() && g_Local->GetObserved() == pEntity)
						continue;

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
								Drawing::DrawHealthBar(pEntity, vecHeadHitBox2D.y + (height * 1.21f - 10), vecHeadHitBox2D.y - (height * .2 + 1), vecHeadHitBox2D.x + (width * -.74));
							}

							if (Options.bBoxESP) 
							{
								Drawing::DrawBoxESP(pEntity, vecHeadHitBox2D.x - (width * 0.75), vecHeadHitBox2D.y - (height * 0.2), vecHeadHitBox2D.x + (width * 0.75), vecHeadHitBox2D.y + (height * 1.2));
							}

							if (Options.bPlayerName) 
							{
								Drawing::DrawPlayerName(pEntity->EntIndex(), vecHeadHitBox2D.x, vecHeadHitBox2D.y + (height * 1.10));
							}

							if (Options.bBoneESP) 
							{
								Drawing::DrawBoneESP(NSDK::Color(255, 255, 255), pEntity);
							}

							if (Options.bWeaponESP) 
							{
								Drawing::DrawWeaponESP(pEntity, vecHeadHitBox2D.x - (width * -.750), vecHeadHitBox2D.y + (height * -0.23));
							}

							if (Options.bResolverESP)
							{
								Drawing::DrawResolverESP(pEntity, vecHeadHitBox2D.x - (width * -.750), vecHeadHitBox2D.y + (height * -0.23));
							}

							if (Options.bInfoESP)
							{
								Drawing::DrawInfo(pEntity, vecHeadHitBox2D.x - (width * -.750), vecHeadHitBox2D.y + (height * -0.23));
							}

						}

					}
				}
			}
		}

}