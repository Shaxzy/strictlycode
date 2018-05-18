#include "CHLCM.h"
#include <time.h>
#include "IGameEventManager.h"
#include "FSN.h"
#include "CNotify.h"
#include "CFixMove.h"
#include "CBacktracking.h"
#include <vector>
#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / NSDK::I::GlobalVars()->interval_per_tick ) )
#define TICKS_TO_TIME( t )		( NSDK::I::GlobalVars()->interval_per_tick *( t ) )

#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif


void SayInChat(const char *text)
{
	char buffer[420];
	sprintf_s(buffer, "say \"%s\"", text);
	NSDK::I::Engine()->ClientCmd_Unrestricted(buffer);
}

void ChatSpamRegular()
{
	static bool bFlip = false;
	// Don't spam it too fast so you can still do stuff
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;

	if (timeSoFar < 1)
		return;

	std::vector<std::string> spam_msg = 
	{
	cheat_name " - refund your paste",
	cheat_name " - superior legit hack",
	cheat_name "- cya later pastes",
	cheat_name "- bye bye blatant!"
	};

	std::string spam = spam_msg.at(rand() % spam_msg.size());

	SayInChat(spam.c_str());

	start_t = clock();
}

namespace CHLCM
{
	static CFixMove *FixMoveManager = new CFixMove();
	CreateMoveCHL_t g_fnOriginalCreateMoveCHL;
	void __stdcall Hooked_CreateMove_CHL(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket) {
		g_fnOriginalCreateMoveCHL((void*)NSDK::I::Client(), sequence_number, input_sample_frametime, active);

		if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected())
		{

			CBaseEntity *g_Local = CBaseEntity::GetLocalPlayer();

			if (!g_Local || !g_Local->IsAlive() || !g_Local->GetActiveWeapon())
				return;

			CBaseCombatWeapon* activeWep = g_Local->GetActiveWeapon();

			NSDK::CVerifiedUserCmd* pVerif = &(*(NSDK::CVerifiedUserCmd**)((DWORD)NSDK::I::Input() + 0xF0))[sequence_number % 150];
			NSDK::CUserCmd *pCmd = &(*(NSDK::CUserCmd**)((DWORD)NSDK::I::Input() + 0xEC))[sequence_number % 150];

			if (pCmd && pVerif)
			{

				if (Options.bBacktracking)
				{
					for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); i++)
					{
						CBaseEntity *pClient = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);
						if (!pClient || !pClient->isValidPlayer()) continue;
						int idx = pClient->EntIndex();
						Backtracking::log_entity(pClient, pCmd);
					
						while (records[idx].size() > TIME_TO_TICKS(.2))
						{
							records[idx].pop_front();
						}

					}
				}

				if (Options.bChatSpam)
				{
					ChatSpamRegular();
				}

				if (Options.bBhop)
				{
					if (pCmd->buttons & IN_JUMP && !(*g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND))
					{
						pCmd->buttons &= ~IN_JUMP;
					}

				}

				FixMoveManager->Start(pCmd);

				//generate random number from 0 to 100
				int current_luck = rand() % 101;
				CBaseEntity* best_targ = nullptr;
				if (Options.bAimbot)
				{
					if (Options.bLuckShot && (current_luck > Options.iLuckShotRate) || !Options.bLuckShot)
					{
						bool bHasTarget = false;
						for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); i++)
						{
							CBaseEntity *pClient = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);
							if (!pClient || !pClient->isValidPlayer()) continue;
							int myTeam = *g_Local->GetTeamNum();
							int theirTeam = *pClient->GetTeamNum();
							if (myTeam == theirTeam) continue;
							if (!pClient->isVisible()) continue;
							int idx = pClient->EntIndex();

							NSDK::Vector enemy_hitbox = pClient->GetEntityHitbox(Options.iHitbox);

							//getting locations
							NSDK::Vector  local_pos = g_Local->GetEyePos();

							//calcing aimAngle
							NSDK::QAngle final_angle = Utilities::CalcAngle(local_pos, enemy_hitbox);

							//fov checks + grabbing local viewangles
							NSDK::Vector local_view;
							NSDK::I::Engine()->GetViewAngles(local_view);
							float fov = Utilities::GetFov(local_view, final_angle);

							if (fov > Options.fNormalFov) continue;

							CBaseEntity* best_targ = pClient;
							NSDK::Vector delta = final_angle - pCmd->viewangles;

							//smoothing
							if (Options.bSmoothing && Options.fSmoothing > 0)
							{
								float smooth = powf(Options.fSmoothing, 0.4f);
								smooth = min(0.99f, smooth);
								NSDK::Vector toChange;

								float coeff = (1.0f - smooth) / delta.Length() * 4.f;
								//uncomment next for faster end
								//coeff = powf(coeff, 2.f) * 10.f;

								coeff = min(1.f, coeff);
								toChange = delta * coeff;

								//setting and clamping
								pCmd->viewangles += toChange;
								bHasTarget = true;
							}

							if (!Options.bSmoothing || Options.fSmoothing <= 0)
							{
								pCmd->viewangles = final_angle;
								bHasTarget = true;
							}
						}

						if (bHasTarget)
						{
							NSDK::I::Engine()->SetViewAngles(pCmd->viewangles);
						}
					}
				}

				if (best_targ) 
				{
					Backtracking::get_best_record(best_targ, g_Local, pCmd);
				}
				Utilities::Clamp(pCmd->viewangles);

				//bottom of createmove:
				FixMoveManager->Stop(pCmd);
				pVerif->m_cmd = *pCmd;
				pVerif->m_crc = pCmd->GetChecksum();
			}
		}
	}
}