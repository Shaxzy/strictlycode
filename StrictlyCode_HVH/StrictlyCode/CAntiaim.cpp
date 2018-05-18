#include "CAntiaim.h"

#define TICK_INTERVAL			( NSDK::I::GlobalVars()->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( NSDK::I::GlobalVars()->interval_per_tick *( t ) )
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#include "CAutoWall.h"
namespace Antiaim
{

	int Antiaim::LBYUpdate(NSDK::CUserCmd* cmd, bool& bSendPacket, CBaseEntity* g_Local)
	{
		static auto get_fixed_curtime = [=](NSDK::CUserCmd* cmd) {
			static auto fixed_ticks = 0;
			static NSDK::CUserCmd* last_cmd{};

			if (!last_cmd || last_cmd->hasbeenpredicted)
				fixed_ticks = *g_Local->GetTickBase();
			else
				++fixed_ticks;

			last_cmd = cmd;

			return TICKS_TO_TIME(fixed_ticks);
		};

		auto nci = NSDK::I::Engine()->GetNetChannel();

		if (!nci)
			return NOTHING;

		static auto last_lby_update = 0.0f;
		static auto last_lby = 0.f;
		static auto first_lby_break = false, was_on_ground = false;
		auto curtime = get_fixed_curtime(cmd);
		auto velocity = g_Local->GetVelocity()->Length2D();
		auto landed = !was_on_ground && *g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND;
		auto time_until_update = last_lby_update - curtime + (first_lby_break ? 0.22f : 1.125f);

		if (!(*g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND))
			was_on_ground = false;

		if (((*g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND && velocity > 0.5f) || landed)) 
		{
			first_lby_break = true;
			last_lby_update = curtime;

			if (landed)
				was_on_ground = true;

			if (landed)
				return FULLBREAK;

			if ((*g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND && velocity > 0.5f))
				return NOTHING;
		}

		if (!nci->m_nChokedPackets)
		{
			first_lby_break = false;

			if (time_until_update <= TICKS_TO_TIME(1)) 
			{ 
				last_lby_update = curtime;
				return FULLBREAK;
			}
				return NOTHING;
		}
		else if (time_until_update <= TICKS_TO_TIME(2) && time_until_update > TICKS_TO_TIME(1) && *g_Local->GetFlags() & (int)NSDK::EntityFlags::FL_ONGROUND && velocity <= 0.5f) 
		{ 
			// tick before lby updates
			bSendPacket = true; // fixes fakelag to work with fast lby flick
								
			return PREBREAK;
		}

		return NOTHING;
	}

	void Manual(CBaseEntity* g_Local, NSDK::CUserCmd* cmd, bool bSendPacket)
	{
		int lby_status = LBYUpdate(cmd, bSendPacket, g_Local);

		if (!bSendPacket)
		{
				//real
			float rand = Utilities::RandomFloat(-7, 7);
			cmd->viewangles.y += Local::headSide ? 90 + rand : -90 + rand;

			if (lby_status == FULLBREAK)
			{
				if (Options.iLBYType == 0)
					cmd->viewangles.y = Local::Fake;

				if(Options.iLBYType == 1)
					cmd->viewangles.y = Local::Real + Options.fLBYDelta;
			}
		}

		else
		{
			float rand = Utilities::RandomFloat(-15, 15);
			cmd->viewangles.y += Local::headSide ? -90 + rand : 90 + rand;
		}
	}

	void LBY_AA(CBaseEntity* g_Local, NSDK::CUserCmd* cmd, bool bSendPacket)
	{
		static float old_lby = 0;
		float ns_num = 0;
		if (*g_Local->GetLowerBodyYaw() != old_lby)
		{
			old_lby = *g_Local->GetLowerBodyYaw();
			ns_num = Utilities::RandomFloat(75, 110);
		}

		if (!bSendPacket)
		{
			cmd->viewangles.y += (*g_Local->GetLowerBodyYaw() + ns_num);
		}

		else 
		{
			cmd->viewangles.y += *g_Local->GetLowerBodyYaw();
		}
	}


	void Freestanding(CBaseEntity* g_Local, NSDK::CUserCmd* cmd, bool bSendPacket)
	{
		auto eyepos = g_Local->GetEyePos();
		auto headpos = g_Local->GetEntityHitbox(NSDK::HITBOX_HEAD);
		auto origin = g_Local->GetAbsOrigin();
		float bestrotation = 0.f;
		float highestthickness = 0.f;
		int lby_status = LBYUpdate(cmd, bSendPacket, g_Local);

		if (!bSendPacket)
		{
			cmd->viewangles.y += 180;
			if (lby_status == FULLBREAK)
			{
				if (Options.iLBYType == 0)
					cmd->viewangles.y = Local::Fake;

				if (Options.iLBYType == 1)
					cmd->viewangles.y = Local::Real + Options.fLBYDelta;
			}
		}
		else
		{
			cmd->viewangles.y += Local::Real + 180;
		}
	}

	void Antiaim::Main(CBaseEntity* local, NSDK::CUserCmd* cmd, bool bSendPacket)
	{
		if (!local)
			return;

		if (!local->IsAlive())
			return;

		if (!local->GetActiveWeapon())
			return;

		if (*local->GetActiveWeapon()->GetItemDefinitionIndex() != NSDK::EItemDefinitionIndex::weapon_revolver && cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE)
			return;

		if (local->GetMoveType() == NSDK::MOVETYPE_NOCLIP || local->GetMoveType() == NSDK::MOVETYPE_LADDER)
			return;

		if (local->GetActiveWeapon()->isGrenade() && cmd->buttons & IN_ATTACK || local->GetActiveWeapon()->isGrenade() && cmd->buttons & IN_ATTACK2)
			return;

		if (*local->GetActiveWeapon()->GetItemDefinitionIndex() == NSDK::EItemDefinitionIndex::weapon_knife_t || *local->GetActiveWeapon()->GetItemDefinitionIndex() == NSDK::EItemDefinitionIndex::weapon_knife)
		{
			if (cmd->buttons & IN_ATTACK2)
				return;
		}

		cmd->viewangles.x = 89;

		if (Options.iAntiAim == 0)
		{
			Manual(local, cmd, bSendPacket);
		}

		if (Options.iAntiAim == 1)
		{
			LBY_AA(local, cmd, bSendPacket);
		}

		if (Options.iAntiAim == 2)
		{
			Freestanding(local, cmd, bSendPacket);
		}
	}
}