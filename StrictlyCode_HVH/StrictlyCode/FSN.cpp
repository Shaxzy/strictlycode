#include "FSN.h"
#include "CSkinChanger.h"
#include "CNotify.h"
#include "Globals.h"
#include "CBulletListener.h"
#include "CResolver.h"
#include "CInterpFix.h"
CLagcompensation lagcompensation;
#define TICK_INTERVAL			( NSDK::I::GlobalVars()->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( NSDK::I::GlobalVars()->interval_per_tick *( t ) )

namespace FSN
{
	FrameStageNotify_t g_fnOriginalFrameStageNotify;
	VOID __fastcall Hooked_FrameStageNotify(void* thisptr, void* edx, NSDK::ClientFrameStage_t cur_stage)
	{

		CBaseEntity *g_Local = CBaseEntity::GetLocalPlayer();
		if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected())
		{
			g_fnOriginalFrameStageNotify(thisptr, cur_stage);

			SkinChanger::FrameStageNotify_Pre(cur_stage);

			lagcompensation.anim_fix(cur_stage);

			if (cur_stage == NSDK::ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			{
				//resolver
				static float last_moving_lby[65];
				if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected())
				{
					for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); ++i)
					{
						CBaseEntity *pClient = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);
						if (!pClient->isValidPlayer()) continue;

						lagcompensation.disable_interp(pClient);

						/* general defs */
						int idx = pClient->EntIndex();
						auto animstate = pClient->GetAnimState();
						float velocity = animstate->speed_2d;

						/* lby related defs */
						info::isFakeWalk[idx] = NSDK::I::GlobalVars()->curtime - info::last_lby_update[idx] > .22 && velocity > 1;
						float lby = *pClient->GetLowerBodyYaw();
						float moving_lby = info::MovingLBY[idx];
						float standing_lby = info::StandingLBY[idx];
						int lby_delta = Resolver::Delta(standing_lby, moving_lby);

						/* resolver stages */
						bool is_moving = !info::isFakeWalk[idx] && velocity > 1;
						bool is_standing = velocity == 0;
						bool is_fakewalk = info::isFakeWalk[idx];

						/* anti jitter memes */
						int delta_max = 0;
						int delta_min = 0;
						int delta_avg = 0;

						info::lby_delta[idx].push_back(lby_delta);

						while (info::lby_delta[idx].size() > 32)
						{
								info::lby_delta[idx].pop_front();
						}

						//this gets the avg jitter (jitter amount basically)
						Resolver::jitter_avg(info::lby_delta[idx], delta_max, delta_min, delta_avg);

						Resolver::triggers_979(pClient);

						info::delta_avg[idx] = delta_avg;

						if (velocity > 1)
						{
							if (lby != last_moving_lby[idx])
							{
								last_moving_lby[idx] = lby;
								info::last_lby_update[idx] = NSDK::I::GlobalVars()->curtime;
							}
						}

						if (is_standing || is_fakewalk)
						{
							info::StandingLBY[idx] = lby;

							if (Backtracking::tick_is_valid[idx] && Options.bLBYBacktrack)
							{
								pClient->GetEyeAngles()->x = Backtracking::last_pitch[idx];
								pClient->GetEyeAngles()->y = Backtracking::last_lby[idx];
								info::resolvemode[idx] = LBY_FLICK;
							}

							if(!Backtracking::tick_is_valid[idx] || !Options.bLBYBacktrack)
							{
								pClient->GetEyeAngles()->y = Resolver::BasicResolver(pClient, g_Local);
							}

						}

						if (is_moving)
						{
							info::MovingLBY[idx] = lby;
							pClient->GetEyeAngles()->y = lby;
							info::resolvemode[idx] = MOVING_LBY;
						}

						if (GetAsyncKeyState(VK_MENU))
						{
							info::should_baim[idx] = true;
						}
						else
						{
							info::should_baim[idx] = false;
						}

						pClient->UpdateClientSideAnimation();
					}
				}
			}

			if (cur_stage == NSDK::ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
			{
				//backtracking memes
				static float moving_lby[65];
				static float old_lby[65];
				if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected())
				{
					for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); ++i)
					{
						CBaseEntity *pClient = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

						if (!pClient->isValidPlayer()) continue;

						/* general vars */
						int idx = pClient->EntIndex();
						auto animstate = pClient->GetAnimState();
						float velocity = animstate->speed_2d;
						bool is_moving = !info::isFakeWalk[idx] && velocity > 1;
						bool is_standing = velocity == 0;
						bool is_fakewalk = info::isFakeWalk[idx];
						float lby = *pClient->GetLowerBodyYaw();
						float upd_time = Backtracking::was_moving[idx] ? .22 : 1.1;
						Backtracking::tick_is_valid[idx] = NSDK::I::GlobalVars()->tickcount - Backtracking::best_lby_tick[idx] < TIME_TO_TICKS(.2);

						/* lby backtrack / lby pred */
						//something in here is messed up, it always says backtracking
						if (is_standing || is_fakewalk)
						{

							if (*pClient->GetSimulationTime() - Backtracking::last_lbyt[idx] >= upd_time)
							{
								Backtracking::last_lbyt[idx] = *pClient->GetSimulationTime() + NSDK::I::GlobalVars()->interval_per_tick;
								Backtracking::best_lby_tick[idx] = TIME_TO_TICKS(*pClient->GetSimulationTime());

								Backtracking::last_pitch[idx] = pClient->GetEyeAngles()->x;
								Backtracking::last_lby[idx] = *pClient->GetLowerBodyYaw();
							}

							Backtracking::was_moving[idx] = false;
						}

						if (is_moving)
						{
							Backtracking::was_moving[idx] = true;
							Backtracking::last_lbyt[idx] = *pClient->GetSimulationTime() + NSDK::I::GlobalVars()->interval_per_tick;

							Backtracking::last_pitch[idx] = pClient->GetEyeAngles()->x;
							Backtracking::last_lby[idx] = *pClient->GetLowerBodyYaw();

							Backtracking::best_lby_tick[idx] = TIME_TO_TICKS(*pClient->GetSimulationTime());
						}

					}
				}
			}

			if (cur_stage == NSDK::ClientFrameStage_t::FRAME_RENDER_START)
			{
				if (g_Local && g_Local->IsAlive())
				{
					*(int*)((uintptr_t)g_Local + 0xA30) = NSDK::I::GlobalVars()->framecount; //we'll skip occlusion checks now
					*(int*)((uintptr_t)g_Local + 0xA28) = 0;//clear occlusion flags
				}

				if (Options.iTracer == 1)
				{
					CBulletListener::singleton()->OnStudioRender();
				}

				if (*(bool*)((DWORD)NSDK::I::Input() + 0xA5))
					*(NSDK::QAngle*)((DWORD)g_Local + 0x031C8) = NSDK::QAngle(g_Local->GetEyeAngles()->x, Local::Fake, 0);

				/* cool nosmoke */
				std::vector<const char*> vistasmoke_mats =
				{
					"particle/vistasmokev1/vistasmokev1_fire",
					"particle/vistasmokev1/vistasmokev1_smokegrenade",
					"particle/vistasmokev1/vistasmokev1_emods",
					"particle/vistasmokev1/vistasmokev1_emods_impactdust",
				};
				static auto smoke_count = *reinterpret_cast<uint32_t**>(NSDK::O::FindSignature("client.dll", "A3 ? ? ? ? 57 8B CB") + 1);

				for (auto mat_s : vistasmoke_mats)
				{
					NSDK::IMaterial* mat = NSDK::I::MatSystem()->FindMaterial(mat_s, TEXTURE_GROUP_OTHER);
					mat->SetMaterialVarFlag(NSDK::MATERIAL_VAR_WIREFRAME, true);
				}

				*(int*)(smoke_count) = 0;

				if (g_Local->IsAlive() && Options.bThirdperson)
				{
					NSDK::Vector vecAngles;
					NSDK::I::Engine()->GetViewAngles(vecAngles);
					NSDK::I::Input()->m_fCameraInThirdPerson = true;
					if (NSDK::I::Input()->m_fCameraInThirdPerson)
					{
						NSDK::I::Input()->m_vecCameraOffset = NSDK::Vector(vecAngles.x, vecAngles.y, 176);
					}
				}
				else
				{
					NSDK::I::Input()->m_fCameraInThirdPerson = false;
				}

				if (Options.bClantagchanger)
				{
					static std::string cur_clantag = cheat_name "     ";

					static int i = 0;

					if (NSDK::I::Engine()->isInGame())
					{
						if (NSDK::I::GlobalVars()->tickcount % 64 == 63)
						{
							Utilities::marquee(cur_clantag);
							Utilities::SetClanTag(cur_clantag.c_str(), cur_clantag.c_str());
						}
					}
				}
				else
				{
					Utilities::SetClanTag("", "");
				}

			}

		}

	}
}
