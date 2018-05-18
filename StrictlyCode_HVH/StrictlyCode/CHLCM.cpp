#include "CHLCM.h"
#include <time.h>
#include "IGameEventManager.h"
#include "FSN.h"
#include "CNotify.h"
#include "CFixMove.h"
#include "CAutoWall.h"
#include "Globals.h"
#include "CFakewalk.h"
#include "CAntiaim.h"
#include "DrawManager.h"

NSDK::Color lbyColor = NSDK::Color(255, 165, 0, 255);
NSDK::Color realColor = NSDK::Color(0, 255, 0, 255);
NSDK::Color fakeColor = NSDK::Color(255, 0, 0, 255);

int StepCounter = 0;

void Normalize(NSDK::QAngle &ang)
{
	ang.x = Utilities::clip(ang.x, -89, 89);
	ang.y = fmod(ang.y + 180, 360) - 180;
	ang.z = 0;
}

bool ShouldShoot(int idx)
{

	if (!Options.bLBYBacktrack)
		return true;

	if (!Options.bLBYUpdate)
		return true;

	if (Backtracking::tick_is_valid[idx] && Options.bLBYBacktrack)
		return true;

	if (Backtracking::tick_is_valid[idx] && Options.bLBYUpdate)
		return true;

	return false;
}

std::unique_ptr<CFakewalk> fakewalk(new CFakewalk());
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

CBaseEntity* best_entity(CBaseEntity* g_Local)
{
	float bestFov = 999999;
	int bestIdx = 42069;
	for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); i++)
	{
		CBaseEntity *pClient = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

		if (!pClient || !pClient->isValidPlayer()) continue;

		int myTeam = *g_Local->GetTeamNum();
		int theirTeam = *pClient->GetTeamNum();

		if (myTeam == theirTeam) continue;

		int idx = pClient->EntIndex();
		NSDK::Vector targ_vec = CAutowall::CalculateBestPoint(pClient, Options.iHitbox, Options.fAwall, !Options.bHitscan);
		if (targ_vec.IsValid())
		{
			NSDK::Vector PlayerCalc = Utilities::CalcAngle(g_Local->GetEyePos(), targ_vec);
			Utilities::Clamp(PlayerCalc);

			//fov checks + grabbing local viewangles
			NSDK::Vector view_angs;
			NSDK::I::Engine()->GetViewAngles(view_angs);
			float fov = Utilities::GetFov(view_angs, PlayerCalc);

			if (fov > Options.fAimbotFov || fov > bestFov) continue;

			bestFov = fov;
			bestIdx = idx;
		}
	}

	if (bestIdx != 42069)
	{
		return (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(bestIdx);
	}
	else
	{
		return nullptr;
	}
}

int GetLerpTime()
{
	int ud_rate = NSDK::I::CVar()->FindVar("cl_updaterate")->GetInt();
	NSDK::ConVar *min_ud_rate = NSDK::I::CVar()->FindVar("sv_minupdaterate");
	NSDK::ConVar *max_ud_rate = NSDK::I::CVar()->FindVar("sv_maxupdaterate");

	if (min_ud_rate && max_ud_rate)
		ud_rate = max_ud_rate->GetInt();

	float ratio = NSDK::I::CVar()->FindVar("cl_interp_ratio")->GetFloat();

	if (ratio == 0)
		ratio = 1.0f;

	float lerp = NSDK::I::CVar()->FindVar("cl_interp")->GetFloat();
	NSDK::ConVar *c_min_ratio = NSDK::I::CVar()->FindVar("sv_client_min_interp_ratio");
	NSDK::ConVar *c_max_ratio = NSDK::I::CVar()->FindVar("sv_client_max_interp_ratio");

	if (c_min_ratio && c_max_ratio && c_min_ratio->GetFloat() != 1)
	{
		if (ratio < c_min_ratio->GetFloat())
			ratio = c_min_ratio->GetFloat();

		if (ratio > c_max_ratio->GetFloat())
			ratio = c_max_ratio->GetFloat();
	}

	return TIME_TO_TICKS(max(lerp, (ratio / ud_rate)));
}

void SayInChat(const char *text)
{
	char buffer[420];
	sprintf_s(buffer, "say \"%s\"", text);
	NSDK::I::Engine()->ClientCmd_Unrestricted(buffer);
}

float clip(float n, float lower, float upper)
{
	return max(lower, min(n, upper));
}

int FakeLagBreak()
{
	CBaseEntity *g_Local = CBaseEntity::GetLocalPlayer();
	auto Velocity = g_Local->GetVelocity()->Length2D();
	auto Interval = NSDK::I::GlobalVars()->interval_per_tick;
	auto Speed = Velocity * Interval;
	int flag = clip(ceil(66 / Speed), 1, 14);
	return flag;
}

void ChatSpamRegular()
{
	static bool bFlip = false;
	// Don't spam it too fast so you can still do stuff
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;

	if (timeSoFar < 1)
		return;

	bFlip = !bFlip;
	std::string spam = bFlip ? cheat_name " - refund ur shit paste" : cheat_name " superior hvh hack";

	SayInChat(spam.c_str());

	start_t = clock();
}

namespace CHLCM
{
	static CFixMove *FixMoveManager = new CFixMove();
	CreateMoveCHL_t g_fnOriginalCreateMoveCHL;
	void __stdcall Hooked_CreateMove_CHL(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket)
	{

		g_fnOriginalCreateMoveCHL((void*)NSDK::I::Client(), sequence_number, input_sample_frametime, active);

		if (NSDK::I::Engine()->isInGame() && NSDK::I::Engine()->isConnected())
		{

			CBaseEntity *g_Local = CBaseEntity::GetLocalPlayer();
			if (g_Local)
			{

				NSDK::CVerifiedUserCmd* pVerif = &(*(NSDK::CVerifiedUserCmd**)((DWORD)NSDK::I::Input() + 0xF0))[sequence_number % 150];
				NSDK::CUserCmd *pCmd = &(*(NSDK::CUserCmd**)((DWORD)NSDK::I::Input() + 0xEC))[sequence_number % 150];

				bSendPacket = pCmd->tick_count % 2;

				for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); i++)
				{
					CBaseEntity *pClient = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

					if (!pClient || pClient->GetClientClass()->m_ClassID != 35U) continue;

					//shot related stuff

					int idx = pClient->EntIndex();

					bool shot_missed = info::shot_fired[idx] && !info::shot_hit[idx];
					bool shot_hit = info::shot_fired[idx] && info::shot_hit[idx];
					if (shot_hit)
					{
						if (info::resolvemode[idx] != LBY_FLICK)
						{
							info::shots[idx]--;
						}
						else
						{
							if (info::resolvemode[idx] == LBY_FLICK)
							{
								NSDK::I::HudChat()->ChatPrintf(0, 0, "hit lby flick!");
							}
						}
					}
					if (shot_missed)
					{
						std::string Message;
						switch (info::resolvemode[idx])
						{
						case LBY_FLICK: Message = "missed due to bad backtrack record!"; break;
						case LOW_DELTA:Message = "missed due to bad resolve!"; break;
						case HIGH_DELTA:Message = "missed due to bad resolve!"; break;
						case MOVING_LBY: Message = "missed due to fakelag!"; break;
						}
						PushNotifications::Push(Message);
					}

					info::shot_fired[idx] = false;
					info::shot_hit[idx] = false;
				}

				if (GetAsyncKeyState(VK_LEFT))
				{
					//left
					Local::headSide = true;
				}

				if (GetAsyncKeyState(VK_RIGHT))
				{
					//right 
					Local::headSide = false;
				}

				if (Options.bChatSpam)
				{
					ChatSpamRegular();
				}

				if (g_Local->IsAlive())
				{
					CBaseCombatWeapon* activeWep = g_Local->GetActiveWeapon();
					if (Options.bBhop && g_Local->GetMoveType() != NSDK::MOVETYPE_NOCLIP && g_Local->GetMoveType() != NSDK::MOVETYPE_LADDER)
					{
						if (pCmd->buttons & IN_JUMP && !(*g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND))
						{
							pCmd->buttons &= ~IN_JUMP;
						}

						if (!(*g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND))
						{

							if (pCmd->mousedx > 1 || pCmd->mousedx < -1)
								pCmd->sidemove = pCmd->mousedx < 0.0f ? -450.f : 450.f;
							else
							{
								pCmd->forwardmove = 4200.0f / g_Local->GetVelocity()->Length();
								pCmd->sidemove = (pCmd->command_number % 2) == 0 ? -450.f : 450.f;
								if (pCmd->forwardmove > 450)
									pCmd->forwardmove = 450;
							}
						}
					}

					if (g_Local->isMoving())
					{
						int ticks = NSDK::I::Engine()->GetNetChannel()->m_nChokedPackets;
						if (*g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND)
						{
							//step on ground (scout memes)
							if (ticks >= StepCounter)
							{
								StepCounter++;
								if (StepCounter >= 14)
								{
									bSendPacket = true;
									StepCounter = 0;
								}
							}
							else
							{
								bSendPacket = false;
							}
						}
						if (!(*g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND))
						{
							//adaptive in air (nospread)
							if (ticks < FakeLagBreak() && ticks < 15)
							{
								bSendPacket = false;
							}
							else
							{
								bSendPacket = true;
								ticks = 0;
							}
						}
					}

					if (activeWep)
					{

						if (pCmd->buttons & IN_ATTACK)
						{
							static bool FlipPistol = false;

							if (FlipPistol)
								pCmd->buttons &= ~IN_ATTACK;

							FlipPistol = !FlipPistol;
						}

						if (*activeWep->GetItemDefinitionIndex() == NSDK::EItemDefinitionIndex::weapon_revolver)
						{
							float flPostponeFireReady = activeWep->PostponeFireReady();

							pCmd->buttons |= IN_ATTACK;

							if (flPostponeFireReady > 0 && flPostponeFireReady <= (*g_Local->GetTickBase() * NSDK::I::GlobalVars()->interval_per_tick))
								pCmd->buttons &= ~IN_ATTACK;

						}
					}

					FixMoveManager->Start(pCmd);
					float curtime = *g_Local->GetTickBase() * NSDK::I::GlobalVars()->interval_per_tick;

					if (Options.bAimbot && activeWep->GetCurrentAmmo() > 0)
					{
						auto pClient = best_entity(g_Local);
						if (pClient->isValidPlayer())
						{

							int idx = pClient->EntIndex();
							Local::cur_target = idx;
							NSDK::Vector targ_vec = info::should_baim[idx] ? CAutowall::CalculateBestPoint(pClient, NSDK::HITBOX_PELVIS, Options.fAwall, true) : CAutowall::CalculateBestPoint(pClient, Options.iHitbox, Options.fAwall, !Options.bHitscan);

							if (targ_vec.IsValid())
							{
								NSDK::Vector player_calc = Utilities::CalcAngle(g_Local->GetEyePos(), targ_vec);

								//fov checks + grabbing local viewangles
								NSDK::Vector view_angs;
								NSDK::I::Engine()->GetViewAngles(view_angs);
								float fov = Utilities::GetFov(view_angs, player_calc);

								pCmd->viewangles = player_calc - *g_Local->AimPunch() * 2;

								if (Utilities::HitChance(g_Local, activeWep, Options.iHitchance))
								{

									if (!g_Local->isScoped() && activeWep->isWeaponScope() && Options.bAutoScope)
										pCmd->buttons |= IN_ATTACK2;

									else if (Options.bAutoShoot)
									{

										if (Options.bAutoSlow)
										{
											NSDK::Vector velocity = *g_Local->GetVelocity();
											NSDK::Vector direction = velocity.Angle(0);
											float speed = velocity.Length();

											direction.y = pCmd->viewangles.y - direction.y;

											NSDK::Vector negated_direction = direction * -speed;

											if (velocity.Length() >= (activeWep->GetCSWpnData()->flMaxPlayerSpeed * .34f))
											{
												pCmd->forwardmove = negated_direction.x;
												pCmd->sidemove = negated_direction.y;
											}

										}

										if (Options.bLBYBacktrack && Backtracking::tick_is_valid[idx])
										{
												pCmd->tick_count = Backtracking::best_lby_tick[idx] + GetLerpTime() + 1;
										}
										else
										{
											pCmd->tick_count = TIME_TO_TICKS(*pClient->GetSimulationTime()) + GetLerpTime() + 1;
										}

										if (ShouldShoot(pClient->EntIndex()))
										{
											pCmd->buttons |= IN_ATTACK;
										}

									}
								}
							}

						}
					}

					//omg fakewalk paste
					fakewalk->do_fakewalk(pCmd);

					//antiaim memes
					Antiaim::Main(g_Local, pCmd, bSendPacket);

					FixMoveManager->Stop(pCmd);

				}

				Utilities::Clamp(pCmd->viewangles);

				if (!bSendPacket)
				{
					Local::Real = pCmd->viewangles.y;
				}

				if (bSendPacket)
				{
					Local::fakePos[0] = g_Local->GetOrigin()->x;
					Local::fakePos[1] = g_Local->GetOrigin()->y;
					Local::fakePos[2] = g_Local->GetOrigin()->z;

					Local::Fake = pCmd->viewangles.y;
				}

				pVerif->m_cmd = *pCmd;
				pVerif->m_crc = pCmd->GetChecksum();
			}
		}
	}
}