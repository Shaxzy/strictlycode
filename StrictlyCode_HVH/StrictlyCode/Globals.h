#pragma once
#include <deque>
namespace Backtracking
{
	extern float last_lbyt[65];
	extern float last_lby[65];
	extern float last_pitch[65];
	extern bool was_moving[65];
	extern int best_lby_tick[65];
	extern bool tick_is_valid[65];
}

namespace info
{
	extern int shots[65];
	extern bool shot_fired[65];
	extern bool shot_hit[65];

	/* resolver stuff */
	extern bool isFakeWalk[65];
	extern float StandingLBY[65];
	extern float MovingLBY[65];
	extern int delta_avg[65];
	extern int hurt_avg[65];
	extern std::deque<int> lby_delta[65];
	/* etc memes */
	extern int resolvemode[65];
	extern float last_lby_update[65];

	extern bool should_baim[65];
	extern bool is_fake[65];
}

enum ResolverModes : int
{
	LOW_DELTA,
	HIGH_DELTA,
	MOVING_LBY,
	LBY_FLICK
};

namespace Local
{
	extern bool headSide;
	extern float Fake;
	extern float Real;
	extern float fakePos[3];
	extern std::string user;
	extern int cur_target;
}

enum lby_breaker_modes : int
{
	NOTHING,
	PREBREAK,
	FULLBREAK
};