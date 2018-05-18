#include "CBacktracking.h"
std::deque<BacktrackRecord> records[65];

namespace Backtracking
{
	void log_entity(CBaseEntity* pEntity, NSDK::CUserCmd* cmd)
	{
		int idx = pEntity->EntIndex();
		BacktrackRecord push_rec;

		push_rec.head = pEntity->GetEntityHitbox(NSDK::HEAD_0);
		push_rec.origin = *pEntity->GetOrigin();
		push_rec.eye_angs = *pEntity->GetEyeAngles();
		push_rec.tick = cmd->tick_count;

		records[idx].push_back(push_rec);
	}

	void get_best_record(CBaseEntity* g_Player, CBaseEntity* g_Local, NSDK::CUserCmd* cmd)
	{
		int idx = g_Player->EntIndex();
		float best_fov = FLT_MAX;
		int best_rec = 1337;
		for (size_t i = 0; i < records[idx].size(); i++)
		{
			NSDK::QAngle final_ang = Utilities::CalcAngle(g_Local->GetEyePos(), records[idx].at(i).head);
			float cur_fov = Utilities::GetFov(cmd->viewangles, final_ang);
			if (cur_fov < best_fov)
			{
				best_fov = cur_fov;
				best_rec = i;
			}
		}

		if (best_rec == 1337)
			return;

		BacktrackRecord best_record = records[idx].at(best_rec);
		
		*g_Player->GetOrigin() = best_record.origin;
		cmd->tick_count = best_record.tick;
		*g_Player->GetEyeAngles() = best_record.eye_angs;
		g_Player->UpdateClientSideAnimation();
	}
}