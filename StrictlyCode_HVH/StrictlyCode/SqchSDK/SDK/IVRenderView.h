#pragma once

#include "..\SDKHelper\Utilities.h"

namespace NSDK {
	class IVRenderView {
	public:
		void SetColorModulation(float const* blend){
			typedef void(__thiscall *OrigFn)(void*, float const*);
			CallVFunction<OrigFn>(this, 6)(this, blend);
		}

		void SetBlend(float alpha) {
			typedef void(__thiscall *OrigFn)(void*, float);
			CallVFunction<OrigFn>(this, 4)(this, alpha);
		}
	};
}