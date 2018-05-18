#include "EntityStructs.h"
#include "Utilities.h"
#include <deque>
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / NSDK::I::GlobalVars()->interval_per_tick ) )
#define TICKS_TO_TIME( t )		( NSDK::I::GlobalVars()->interval_per_tick *( t ) )

struct BacktrackRecord
{
	NSDK::Vector head;
	NSDK::Vector origin;
	NSDK::Vector eye_angs;
	unsigned int tick;
};

namespace Backtracking
{
	void log_entity(CBaseEntity* pEntity, NSDK::CUserCmd* cmd);
	void get_best_record(CBaseEntity* g_Player, CBaseEntity* g_Local, NSDK::CUserCmd* cmd);
}


extern std::deque<BacktrackRecord> records[65];