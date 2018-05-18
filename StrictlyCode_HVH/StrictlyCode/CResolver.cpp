#include "CResolver.h"
#include "Globals.h"
#include "Utilities.h"
namespace Resolver
{
	bool triggers_981(CBaseEntity* entity)
	{
		int seq_activity[64];

		// for loop for all 13 anim layers.
		for (int j = 0; j < 13; j++)
		{
			seq_activity[entity->EntIndex()] = entity->GetSequenceActivity(entity->GetAnimOverlay(j).m_nSequence);

			if (seq_activity[entity->EntIndex()] == 981 && entity->GetAnimOverlay(j).m_flWeight == 1)
			{
				return true;
			}
		}

		return false;
	}

	void Resolver::triggers_979(CBaseEntity* entity)
	{
		int seq_activity[64];

		// for loop for all 13 anim layers.
		for (int j = 0; j < 13; j++)
		{
			seq_activity[entity->EntIndex()] = entity->GetSequenceActivity(entity->GetAnimOverlay(j).m_nSequence);

			if (seq_activity[entity->EntIndex()] == 979 && entity->GetAnimOverlay(j).m_flWeight == 0.f && entity->GetAnimOverlay(j).m_flCycle > .92f)
			{
				info::is_fake[entity->EntIndex()] = true;
			}
		}
	}

	float Resolver::BasicResolver(CBaseEntity* pEntity, CBaseEntity* g_Local)
	{
		int idx = pEntity->EntIndex();
		int shots = info::shots[idx] % 6;
		int deltalby = Delta(info::MovingLBY[idx], info::StandingLBY[idx]);
		float lby = *pEntity->GetLowerBodyYaw();
		float at_targ = Utilities::CalcAngle(pEntity->GetEyePos(), g_Local->GetEyePos()).y;
		float resolved_yaw;

		switch (shots)
		{
		case 0:resolved_yaw = lby + deltalby; if (deltalby > 120) info::resolvemode[idx] = HIGH_DELTA; break; // + moving lby delta
		case 1:resolved_yaw = lby - deltalby; if (deltalby > 120) info::resolvemode[idx] = HIGH_DELTA; break; // - moving lby delta
		case 2:resolved_yaw = lby + 180; if (deltalby > 120) info::resolvemode[idx] = HIGH_DELTA; break;
		case 3:resolved_yaw = lby - 110; info::resolvemode[idx] = LOW_DELTA; break;
		case 4:resolved_yaw = lby + 110; info::resolvemode[idx] = LOW_DELTA; break;
		case 5:resolved_yaw = at_targ - 180; info::resolvemode[idx] = HIGH_DELTA; break;
		}

		return resolved_yaw;
	}

	int Resolver::Delta(float f1, float f2)
	{
		int delta = f1 - f2;
		int actual_delta = ((delta + 180) % 360 + 360) % 360 - 180;
		return actual_delta;
	}

	void Resolver::jitter_avg(std::deque<int> deltas, int delta_max, int delta_min, int delta_avg)
	{
		for (int i = 0; i < deltas.size(); i++)
		{
			auto cur = deltas.at(i);

			if (cur > delta_max)
			{
				delta_max = cur;
			}

			if (cur < delta_min)
			{
				delta_min = cur;
			}

			delta_avg = delta_max - delta_min;
		}
	}

	bool Resolver::is_fakewalk(CBaseEntity* pEntity)
	{
		auto animstate = pEntity->GetAnimState();
		if (triggers_981(pEntity))
		{
			if (pEntity->GetAnimOverlay(12).m_flWeight > 0)
			{
				if (pEntity->GetAnimOverlay(6).m_flPlaybackRate < .0001)
				{
					return true;
				}
			}
		}
		return false;
	}
}