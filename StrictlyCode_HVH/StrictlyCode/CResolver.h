#pragma once
#include "EntityStructs.h"
#include <deque>

namespace Resolver
{
	void triggers_979(CBaseEntity * entity);
	float BasicResolver(CBaseEntity* pEntity, CBaseEntity* g_Local);
	int Delta(float f1, float f2);
	void jitter_avg(std::deque<int> deltas, int delta_max, int delta_min, int delta_avg);
	bool is_fakewalk(CBaseEntity* pEntity);
}

struct TickRecord
{
	float lby;
	float curtime;
	float speed;
	int moving_delta;
	int fake_delta;
};

extern std::deque<TickRecord> ticks[65];