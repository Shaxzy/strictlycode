#pragma once

#include "IMoveHelper.h"

namespace NSDK {
	class CPrediction{
	public:
		//might not be proper
		void RunCommand(IClientEntity *player, CUserCmd *ucmd, IMoveHelper *pHelper) {
			typedef void(__thiscall *OrigFn)(void*, IClientEntity*, CUserCmd*, IMoveHelper*);
			CallVFunction<OrigFn>(this, 19)(this, player, ucmd, pHelper);
		}

		void SetupMove(IClientEntity *player, CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move) {
			typedef void(__thiscall *OrigFn)(void*, IClientEntity*, CUserCmd*, IMoveHelper*, CMoveData*);
			CallVFunction<OrigFn>(this, 20)(this, player, ucmd, pHelper, move);
		}

		void FinishMove(IClientEntity *player, CUserCmd *ucmd, CMoveData *move) {
			typedef void(__thiscall *OrigFn)(void*, IClientEntity*, CUserCmd*, CMoveData*);
			CallVFunction<OrigFn>(this, 21)(this, player, ucmd, move);
		}
	};
}