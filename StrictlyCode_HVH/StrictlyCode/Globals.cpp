#include "Globals.h"
#include "SqchSDK\SDK\Vector.h"
#include <deque>

namespace Backtracking
{
	float last_lbyt[65];
	float last_lby[65];
	float last_pitch[65];
	bool was_moving[65];
	int best_lby_tick[65];
	bool tick_is_valid[65];
}

namespace info
{
	int shots[65];
	bool shot_fired[65];
	bool shot_hit[65];

	bool isFakeWalk[65];
	float StandingLBY[65];
	float MovingLBY[65];
	int delta_avg[65];
	int hurt_avg[65];
	std::deque<int> lby_delta[65];

	int resolvemode[65];
	float last_lby_update[65];

	bool should_baim[65];
	bool is_fake[65];
}

namespace Local
{
	bool headSide;
	float Fake;
	float Real;
	float fakePos[3];
	int cur_target;
	std::string user;
}