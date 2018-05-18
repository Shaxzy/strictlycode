#pragma once

#include "CHandle.h"
#include "IEngineTrace.h"
#include "IClientEntity.h"
#include "IPhysicsSurfaceProps.h"

namespace NSDK {
	typedef CBaseHandle EntityHandle_t;

	struct soundlevel_t;
	class PLAYER_ANIM;

	class IMoveHelper{
	public:
		void SetHost(IClientEntity* host) {
			typedef void(__thiscall *OrigFn)(void*, IClientEntity*);
			CallVFunction<OrigFn>(this, 1)(this, host);
		}
	};
}