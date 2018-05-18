#pragma once

namespace NSDK{
	class IClientMode {
	public:
		bool ShouldDrawEntity(IClientEntity *pEnt) {
			typedef bool(__thiscall *OrigFn)(void*, IClientEntity*);
			return CallVFunction<OrigFn>(this, 14)(this, pEnt);
		}

	};
}