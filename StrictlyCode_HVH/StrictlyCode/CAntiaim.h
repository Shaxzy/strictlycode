#pragma once
#include "EntityStructs.h"
#include "Globals.h"
#include "Utilities.h"
namespace Antiaim
{
	void Main(CBaseEntity* local, NSDK::CUserCmd* cmd, bool bSendPacket);
	int LBYUpdate(NSDK::CUserCmd* cmd, bool& bSendPacket, CBaseEntity* g_Local);
}