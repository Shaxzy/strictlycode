#include "FSN.h"
#include "CSkinChanger.h"
#include "CNotify.h"
#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10

float Distance(NSDK::Vector a, NSDK::Vector b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

namespace FSN
{
	FrameStageNotify_t g_fnOriginalFrameStageNotify;
	VOID __fastcall Hooked_FrameStageNotify(void* thisptr, void* edx, NSDK::ClientFrameStage_t curStage) {

		CBaseEntity *g_Local = CBaseEntity::GetLocalPlayer();

		float serverTime = *CBaseEntity::GetLocalPlayer()->GetTickBase() * NSDK::I::GlobalVars()->interval_per_tick;
		if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected()) 
		{
			SkinChanger::FrameStageNotify_Pre(curStage);

			if (curStage == NSDK::ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START) 
			{
				if (Options.bSoundESP && g_Local->IsAlive()) 
				{
					float dist = 9999999;
					//last curtime

					static float lastBeep = 0;
					for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); i++)
					{
						auto pEntity = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);
						if (!pEntity->isValidPlayer()) continue;
						int localTeam = *g_Local->GetTeamNum();
						int playerTeam = *pEntity->GetTeamNum();

						if (localTeam == playerTeam) continue;

							if (Distance(g_Local->GetEyePos(), pEntity->GetEyePos()) < dist) 
							{
								dist = Distance(g_Local->GetEyePos(), pEntity->GetEyePos());
							}

					}
					//play the beep after (x) time
					if (lastBeep + (dist / 850) <= NSDK::I::GlobalVars()->curtime) 
					{
						NSDK::I::Engine()->ClientCmd_Unrestricted("play buttons\\bell1.wav");
						lastBeep = NSDK::I::GlobalVars()->curtime;
					}

				}
			}

			if (curStage == NSDK::ClientFrameStage_t::FRAME_RENDER_START) 
			{
				if (g_Local && g_Local->IsAlive())
				{
					*(int*)((uintptr_t)g_Local + 0xA30) = NSDK::I::GlobalVars()->framecount; //we'll skip occlusion checks now
					*(int*)((uintptr_t)g_Local + 0xA28) = 0;//clear occlusion flags
				}
				static NSDK::QAngle vecAngles;
				NSDK::I::Engine()->GetViewAngles(vecAngles);

				if (Options.bClantagchanger)
				{
					static std::string cur_clantag = cheat_name "     ";

					static int i = 0;

					if (NSDK::I::Engine()->isInGame()) 
					{
						if (i > 32)
						{
							Utilities::marquee(cur_clantag);
							Utilities::SetClanTag(cur_clantag.c_str(), cur_clantag.c_str());
							i = 0;
						}
						else
						{
							i++;
						}
					}
				}


			}
		}

		//Original
		g_fnOriginalFrameStageNotify(thisptr, curStage);

		if (curStage == NSDK::ClientFrameStage_t::FRAME_RENDER_END) 
		{

		}
	}
}