#include "CFakewalk.h"

#include <time.h>
#include <iostream>

void rotate_movement(float yaw, NSDK::CUserCmd* cmd)
{
	NSDK::Vector viewangles;
	NSDK::I::Engine()->GetViewAngles(viewangles);

	float rotation = DEG2RAD(viewangles.y - yaw);

	float cos_rot = cos(rotation);
	float sin_rot = sin(rotation);

	float new_forwardmove = (cos_rot * cmd->forwardmove) - (sin_rot * cmd->sidemove);
	float new_sidemove = (sin_rot * cmd->forwardmove) + (cos_rot * cmd->sidemove);

	cmd->forwardmove = new_forwardmove;
	cmd->sidemove = new_sidemove;
}

void CFakewalk::do_fakewalk(NSDK::CUserCmd* cmd)
{
	if (GetAsyncKeyState(VK_SHIFT)) //make sure fakelag is set to max when u trigger fakewalk!
	{
		auto local_player = CBaseEntity::GetLocalPlayer();

		if (!local_player || local_player->GetHealth() <= 0)
			return;

		auto net_channel = NSDK::I::Engine()->GetNetChannel();
		if (!net_channel)
			return;

		auto animstate = local_player->GetAnimState();
		if (!animstate)
			return;

		int choked_ticks = net_channel->m_nChokedPackets;

		if (choked_ticks < 8)
		{
			cmd->sidemove = 0;
			cmd->forwardmove = 450;
		}
		else
		{
			cmd->forwardmove = 0;
			rotate_movement(Utilities::CalcAngle(NSDK::Vector(0, 0, 0), *local_player->GetVelocity()).y + 180.f, cmd);
		}
	}
}