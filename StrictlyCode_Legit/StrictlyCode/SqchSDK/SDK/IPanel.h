#pragma once

namespace NSDK {
	class IPanel {
	public:
		const char *GetName(unsigned int vguiPanel) {
			typedef const char *(__thiscall* OrigFn)(void*, unsigned int);
			return CallVFunction<OrigFn>(this, 36)(this, vguiPanel);
		}
	};
}